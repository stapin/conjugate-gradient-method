#include <memory>

#include "area.hpp"
#include "function.hpp"
#include "stop_criterion.hpp"

template <typename T = std::vector<double>>
class OptimizationMethod {
public:
    virtual T optimize(const Area<T>& area, const Function<T>& func, const Criterion& criterion) = 0;
};


class OneDimentionalOptimization : public OptimizationMethod<double> {
    double epsilon;
    size_t n;

public:
    OneDimentionalOptimization(
        double epsilon = 1e-4,
        size_t n = 100
    ) :
        epsilon(epsilon), n(n) {}

    double optimize(const Area<double>& area, const Function<double>& func, const Criterion& criterion) override {
        std::pair<double, double> bounds = area.get_bounding_box();
        // double eps = (bounds.second - bounds.first) / n;

        // for (size_t i = 0; i < n; ++i)
        // {
            

        // }
        double ri = bounds.second;
        double li = bounds.first;
        while (ri - li > epsilon) {
            // std::cout << "li: " << li << " ri: " << ri << "\n";
            double mi = (li + ri) / 2;
            // std::cout << "ri: " << ri << " li: " << li << " mi: " << mi << "\n";
            double derivative = func.get_gradient(mi);
            // std::cout << "grad: " << derivative << "\n";
            if (derivative < 0) {
                li = mi;
            } else {
                ri = mi;
            }
        }
        return (li + ri) / 2;
        
    }
};

void print_vec(const std::vector<double>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

class ConjugateGradientMethod : public OptimizationMethod<> {

public:
    std::vector<double> optimize(const Area<>& area, const Function<>& func, const Criterion& criterion) override {
        std::vector<double> x0 = area.sample_random_point();

        std::cout << "x0: ";
        print_vec(x0);
        
        std::vector<double> xn = x0;
        std::vector<double> p0 = func.get_gradient(x0);
        
        std::cout << "p0: ";
        print_vec(p0);

        for (auto &el : p0) el = -el;
        std::vector<double> pn = p0;
        std::vector<std::vector<double>> trajectory;

        Interval interval;

        std::shared_ptr<Function<>> f = func.create_instance();
        AuxiliaryFunction function(xn, pn, f);

        

        int i=0;
        while (!criterion.done(trajectory)) {
            // for (int i = 0; i < pn.size(); ++i) {
            //     std::cout << pn[i] << " ";
            // }
            // std::cout<< "\n";

            std::cout << "\niter: " << i++ << "\n";
            double distance = area.intersect(xn, pn); //Должно возвращать расстояние до границы в направлении pn.
            std::cout << "distance: " << distance << "\n";
            interval.set_bounds(0, distance);
            OneDimentionalOptimization optim_method;


            std::cout << "xn: ";
            print_vec(xn);
            std::cout << "pn: ";
            print_vec(pn);
            function.set_vectors(xn, pn);
            double alpha_n = optim_method.optimize(interval, function, criterion);
            std::cout << "alpha = " << alpha_n << "\n";


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
            std::cout << "fn_grad: ";
            print_vec(fn_grad);
            std::cout << "fn1_grad: ";
            print_vec(fn1_grad);
            std::cout << "num: " << numerator << "\n";
            std::cout << "den: " << denominator << "\n";

            double beta = numerator / denominator;

            for (size_t i = 0; i < pn.size(); ++i) {
                pn[i] = -fn1_grad[i] + beta * pn[i];
            }

        }

        return xn;
    }
};