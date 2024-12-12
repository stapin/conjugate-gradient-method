#pragma once

#include <vector>
#include <string>

/**
 * @brief Implements stop criteria for optimization methods
 * 
 */
class Criterion {
public:
    virtual ~Criterion() = default;

    /**
     * @brief 
     * 
     * @param trajectory successive approximations of the extremum
     * @return true, if criterion met
     * @return false, otherwise
     */
    virtual bool done(const std::vector<std::vector<double>>& trajectory) const = 0;
    virtual std::string get_name() const = 0;
};

/**
 * @brief Criterion stops, when number of iterations exceeded some 
 * preinstalled number
 * 
 */
class IterationCriterion : public Criterion {
private:
    size_t max_iter;
public:
    IterationCriterion(size_t max_iter);
    bool done(const std::vector<std::vector<double>>& trajectory) const override;
    std::string get_name() const override {
        return "Iteration Criterion";
    }
};

/**
 * @brief Criterion stops, when two adjacent approximations differ by
 * less than epsilon
 * 
 */
class EpsilonCriterion : public Criterion {
private:
    double epsilon;

public:
    EpsilonCriterion(double epsilon);

    bool done(const std::vector<std::vector<double>>& trajectory) const override;
    std::string get_name() const override {
        return "Epsilon Criterion";
    }
};