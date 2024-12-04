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
    );

    double optimize(const Area<double>& area, const Function<double>& func, const Criterion& criterion) override;
};

class ConjugateGradientMethod : public OptimizationMethod<> {

public:
    std::vector<double> optimize(const Area<>& area, const Function<>& func, const Criterion& criterion) override {
        std::vector<double> x0 = area.sample_random_point();

        std::vector<double> xn = x0;
        std::vector<double> p0 = func.get_gradient(x0);
        
        for (auto &el : p0) el = -el;
        std::vector<double> pn = p0;
        std::vector<std::vector<double>> trajectory;

        Interval interval;

        std::shared_ptr<Function<>> f = func.create_instance();
        AuxiliaryFunction function(xn, pn, f);

        

        int i=0;
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
};