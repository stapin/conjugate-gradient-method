#pragma once

#include <memory>

#include "area.hpp"
#include "function.hpp"
#include "stop_criterion.hpp"

struct BestParams {
    std::vector<double> minimum_point;
    double minimum_value;
    size_t iter_number;
};

template <typename T = std::vector<double>>
class OptimizationMethod {
public:
    virtual ~OptimizationMethod() = default;
    virtual T optimize(const Rectangle& area, const Function<T>& func,
        const Criterion& criterion) = 0;

    BestParams get_best_params() {return best_params;}
    virtual std::string get_name() const = 0;
    void set_starting_point(std::vector<double> starting_point) {
        this->starting_point = std::move(starting_point);
    } 
protected:
    std::vector<double> starting_point;
    BestParams best_params;
};


class OneDimentionalOptimization : public OptimizationMethod<> {
    double epsilon;

public:
    OneDimentionalOptimization(
        double epsilon = 1e-4
    );

    std::vector<double> optimize(const Rectangle& area, const Function<>& func,
        const Criterion& criterion) override;
    std::string get_name() const override {
        return "One dimentional optimization";
    }
};

class ConjugateGradientMethod : public OptimizationMethod<> {
public:
    std::vector<double> optimize(const Rectangle& area, const Function<>& func,
        const Criterion& criterion) override;
    std::string get_name() const override {
        return "Conjugate gradient method";
    }
};

class RandomSearch : public OptimizationMethod<> {
public:
    RandomSearch(double delta0, double p, size_t max_iters, double alpha=0.9, double min_delta=1e-2) : 
        delta0(delta0), p(p), max_iters(max_iters), min_delta(min_delta), alpha(alpha) {};
    std::vector<double> optimize(const Rectangle& area, const Function<>& func,
        const Criterion& criterion) override;
    std::string get_name() const override {
        return "Random search";
    }

private:
    double delta0;
    double p;
    size_t max_iters;
    double min_delta;
    double alpha;
};