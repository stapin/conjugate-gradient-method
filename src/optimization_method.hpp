#pragma once

#include <memory>

#include "area.hpp"
#include "function.hpp"
#include "stop_criterion.hpp"

/**
 * @brief Struct that contains best params
 * for OptimizationMethos class
 * 
 */
struct BestParams {
    std::vector<double> minimum_point;
    double minimum_value;
    size_t iter_number;
};

template <typename T = std::vector<double>>
class OptimizationMethod {
public:
    virtual ~OptimizationMethod() = default;

    /**
     * @brief Start optimization algorithm for received area, function
     * and criterion.
     * 
     * @param area 
     * @param func 
     * @param criterion 
     * @return T 
     */
    virtual T optimize(const Rectangle& area, const Function<T>& func,
        const Criterion& criterion) = 0;

    BestParams get_best_params() {return best_params;}
    virtual std::string get_name() const = 0;

    /**
     * @brief Sets the starting point for optimization algorithm.
     * Point must lie into the area given to optimize method.
     * 
     * @param starting_point 
     */
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

    /**
     * @brief Construct a new Random Search object
     * 
     * @param delta0 radius for neighborhood of x_n
     * @param p probability to sample from neighborhood of x_n
     * @param max_iters 
     * @param alpha helps to compute delta_n = alpha * delta_{n-1}
     * @param min_delta minimum radius for neighborhood
     */
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