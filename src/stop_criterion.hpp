#pragma once

#include <vector>
#include <string>

class Criterion {
public:
    virtual bool done(const std::vector<std::vector<double>>& trajectory) const = 0;
    virtual std::string get_name() const = 0;
};

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