#pragma once

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

public:
    OneDimentionalOptimization(
        double epsilon = 1e-4
    );

    double optimize(const Area<double>& area, const Function<double>& func, const Criterion& criterion) override;
};

class ConjugateGradientMethod : public OptimizationMethod<> {
public:
    std::vector<double> optimize(const Area<>& area, const Function<>& func, const Criterion& criterion) override;
};

class RandomSearch : public OptimizationMethod<> {
public:
    RandomSearch(double delta0, double p, size_t max_iters) : 
        delta0(delta0), p(p), max_iters(max_iters) {};
    std::vector<double> optimize(const Area<>& area, const Function<>& func, const Criterion& criterion) override;

private:
    double delta0;
    double p;
    size_t max_iters;
};