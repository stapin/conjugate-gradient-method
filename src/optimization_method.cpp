#include "optimization_method.hpp"

OneDimentionalOptimization::OneDimentionalOptimization(
    double epsilon
) : epsilon(epsilon) {}

double OneDimentionalOptimization::optimize(const Area<double>& area, const Function<double>& func, const Criterion& criterion) {
    std::pair<double, double> bounds = area.get_bounding_box();
    double ri = bounds.second;
    double li = bounds.first;
    while (ri - li > epsilon) {
        double mi = (li + ri) / 2;
        double derivative = func.get_gradient(mi);
        if (derivative < 0) {
            li = mi;
        } else {
            ri = mi;
        }
    }
    return (li + ri) / 2;
    
}

std::vector<double> ConjugateGradientMethod::optimize(
    const Area<>& area, 
    const Function<>& func, 
    const Criterion& criterion
) 
{
    std::vector<double> x0 = area.sample_random_point();

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
        double alpha_n = optim_method.optimize(interval, function, criterion);


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