#include "area.hpp"
#include "function.hpp"
#include "stop_criterion.hpp"
#include <memory>

class OptimizationMethod {
private:
    std::shared_ptr<Area> area;
    std::shared_ptr<Function> function;
    std::shared_ptr<Criterion> criterion;

public:
    OptimizationMethod(
        std::shared_ptr<Area> area,
        std::shared_ptr<Function> function, 
        std::shared_ptr<Criterion> criterion) :
        area(area),
        function(function),
        criterion(criterion) 
        {}


    OptimizationMethod(const Area& area, const Function& func,
                         const Criterion& criterion) {}

    virtual void optimize(const Area& area, const Function& func,
                         const Criterion& criterion) = 0;
};