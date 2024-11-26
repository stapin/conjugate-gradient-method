#include <memory>

#include "area.hpp"
#include "function.hpp"
#include "stop_criterion.hpp"

template <typename T = std::vector<double>>
class OptimizationMethod {
protected:

std::shared_ptr<Area<T>> area;
std::shared_ptr<Function<T>> function;
std::shared_ptr<Criterion> criterion;

public:
    OptimizationMethod(
        std::shared_ptr<Area<T>> area,
        std::shared_ptr<Function<T>> function,
        std::shared_ptr<Criterion> criterion
    ) : 
        area(area),
        function(function),
        criterion(criterion)
    {}

    virtual T optimize() = 0;
};


class OneDimentionalOptimization : public OptimizationMethod<double> {
    double epsilon;
    size_t n;

public:
    OneDimentionalOptimization(
        std::shared_ptr<Interval> interval,
        std::shared_ptr<AuxiliaryFunction> function,
        std::shared_ptr<Criterion> criterion,
        double epsilon = 1e-2,
        size_t n = 100
    ) :
        OptimizationMethod(interval, function, criterion), epsilon(epsilon), n(n) {}

    double optimize() override {
        std::pair<double, double> bounds = area->get_bounding_box();
        // double eps = (bounds.second - bounds.first) / n;

        // for (size_t i = 0; i < n; ++i)
        // {
            

        // }
        double ri = bounds.second;
        double li = bounds.first;
        while (ri - li > epsilon) {
            double mi = (li + ri) / 2;
            double derivative = function->get_gradient(mi);
            if (derivative < 0) {
                li = mi;
            } else {
                ri = mi;
            }
        }
        return (li + ri) / 2;
        
    }
};

class ConjugateGradientMethod : public OptimizationMethod<> {

public:
    ConjugateGradientMethod(
        std::shared_ptr<Area<>> area,
        std::shared_ptr<Function<>> function,
        std::shared_ptr<Criterion> criterion
    ) :
        OptimizationMethod(area, function, criterion) {}

    std::vector<double> optimize() override {
        std::vector<double> x0( function->get_dim(), 0.5);
        std::vector<double> xn = x0;
        std::vector<double> p0 = function->get_gradient(x0);
        std::vector<double> pn = p0;
        std::vector<double> trajecory;

        std::shared_ptr<Interval> interval;
        std::shared_ptr<AuxiliaryFunction> func = std::make_shared<AuxiliaryFunction>(xn, pn, function);

        for (auto &el : p0) el = -el;
        


        while (criterion->check(trajecory)) {

            double distance = area->intersect(xn, pn); //Должно возвращать расстояние до границы в направлении pn.
            interval->set_bounds(0, distance);
            OneDimentionalOptimization optim_method(
                interval,
                func,
                criterion
                );

            double alpha_n = optim_method.optimize();

            std::vector<double> fn_grad = function->get_gradient(xn);

            for (int i = 0; i < x0.size(); ++i) {
                xn[i] = xn[i] + alpha_n * pn[i];
            }

            std::vector<double> fn1_grad = function->get_gradient(xn);

            double numerator = 0, denominator = 0;
            for (int i = 0; i < fn1_grad.size(); ++i) {
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