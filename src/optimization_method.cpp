#include "optimization_method.hpp"

OneDimentionalOptimization::OneDimentionalOptimization(
    double epsilon
) : epsilon(epsilon) {}

std::vector<double> OneDimentionalOptimization::optimize(const Rectangle& area, const Function<>& func, const Criterion& criterion) {
    std::pair<double, double> bounds = area.get_bounding_box()[0];
    double ri = bounds.second;
    double li = bounds.first;
    while (ri - li > epsilon) {
        double mi = (li + ri) / 2;
        double derivative = func.get_gradient({mi})[0];
        if (derivative < 0) {
            li = mi;
        } else {
            ri = mi;
        }
    }
    return {(li + ri) / 2};
    
}

std::vector<double> ConjugateGradientMethod::optimize(
    const Rectangle& area, 
    const Function<>& func, 
    const Criterion& criterion
) 
{
    std::random_device device;
    std::mt19937 gen(device());
    std::vector<double> x0 = area.sample_random_point(gen);

    std::vector<double> xn = x0;
    std::vector<double> p0 = func.get_gradient(x0);
    
    for (auto &el : p0) el = -el;
    std::vector<double> pn = p0;
    std::vector<std::vector<double>> trajectory;

    Interval interval;

    std::shared_ptr<Function<>> f = func.create_instance();
    AuxiliaryFunction function(xn, pn, f);

    while (!criterion.done(trajectory)) {
        double distance = area.intersect(xn, pn); //Должно возвращать расстояние до границы в направлении pn.
        interval.set_bounds(0, distance);
        OneDimentionalOptimization optim_method;


        function.set_vectors(xn, pn);
        double alpha_n = optim_method.optimize(interval, function, criterion)[0];


        std::vector<double> fn_grad = func.get_gradient(xn);
        for (size_t i = 0; i < x0.size(); ++i) {
            xn[i] = xn[i] + alpha_n * pn[i];
        }

        trajectory.push_back(xn);
        

        std::vector<double> fn1_grad = func.get_gradient(xn);

        double numerator = 0, denominator = 0;
        for (size_t i = 0; i < fn1_grad.size(); ++i) {
            numerator += fn1_grad[i] * fn1_grad[i];
            denominator += fn_grad[i] * fn_grad[i];
        }

        double beta = numerator / denominator;

        for (size_t i = 0; i < pn.size(); ++i) {
            pn[i] = -fn1_grad[i] + beta * pn[i];
        }

    }

    return xn;
}

std::vector<double> RandomSearch::optimize(const Rectangle& area, const Function<>& func, const Criterion& criterion) {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_real_distribution<double> dist(0., 1.);

    std::vector<double> xn = area.sample_random_point(gen);
    
    //const std::vector<std::pair<double, double>>& D_bounds = area.get_bounding_box();
    std::vector<double> y;
    double delta = delta0;
    std::vector<std::vector<double>> trajectory;
    trajectory.push_back(xn);
    size_t same_point_counter = 0;

    size_t iters = 0;
    while (!criterion.done(trajectory)) {
        if (iters >= max_iters) break;
        double alpha = dist(gen);
        bool neighborhood = false;
        if (alpha < p) {
            y = area.sample_random_point(gen);
        } else {
            y = area.intersect_rectangle(Cube(xn, delta, true)).sample_random_point(gen);
            neighborhood = true;
        }
        if (func(y) < func(xn)) {
            trajectory.push_back(y);
            xn = y;
            if (neighborhood) delta = alpha * delta;
            same_point_counter = 0;
        } else {
            ++same_point_counter;
        }
    }
    return xn;

}