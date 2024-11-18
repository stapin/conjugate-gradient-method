#include "area.hpp"
#include "function.hpp"
#include "stop_criterion.hpp"
#include <memory>
#include <numbers>

template <typename T = std::vector<double>>
class OptimizationMethod {
protected:

std::shared_ptr<Area> area;
std::shared_ptr<Function<T>> function;
std::shared_ptr<Criterion> criterion;

public:
    OptimizationMethod(
        std::shared_ptr<Area> area,
        std::shared_ptr<Function<T>> function,
        std::shared_ptr<Criterion> criterion
    ) : 
        area(area),
        function(function),
        criterion(criterion)
    {}

    virtual void optimize() = 0;
};


class OneDimentionalOptimization : public OptimizationMethod<double> {


public:
    OneDimentionalOptimization(
        std::shared_ptr<Interval> interval,
        std::shared_ptr<OneDimentionalFunction> function,
        std::shared_ptr<Criterion> criterion 
    ) :
        OptimizationMethod(interval, function, criterion) {}

    void optimize();
};

class ConjugateGradientMethod : public OptimizationMethod<> {

public:
    ConjugateGradientMethod(
        std::shared_ptr<Area> area,
        std::shared_ptr<Function<>> function,
        std::shared_ptr<Criterion> criterion
    ) :
        OptimizationMethod(area, function, criterion) {}

    void optimize() override {
        std::vector<double> x0;
        std::vector<double> xn = x0;
        std::vector<double> p0 = function->get_gradient(x0);
        std::vector<double> pn = p0;
        std::vector<double> trajecory;
        while (criterion->check(trajecory)) {
            auto func = [&xn, &pn](double alpha){
                double res = 0;
                for (size_t i = 0; i < xn.size(); ++i) {
                    res += xn[i] + alpha * pn[i];
                }
                return res;
            };

            // area.intersect(pn); Должно возвращать расстояние до границы в направлении pn.
            // OneDimentionalOptimization optim_method(
            //     OneDimentionalFunction(func),

            //     );
            // optim_method.optimize();
        }

    }
};