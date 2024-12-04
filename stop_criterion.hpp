#include <vector>

class Criterion {
public:
    virtual bool done(const std::vector<std::vector<double>>& trajectory) const = 0;
};

class IterationCriterion : public Criterion {
private:
    size_t max_iter;
public:
    IterationCriterion(size_t max_iter) : max_iter(max_iter) {}

    bool done(const std::vector<std::vector<double>>& trajectory) const override {
        if (trajectory.size() >= max_iter) return true;
        return false;
    }
};

class EpsilonCriterion : public Criterion {
private:
    double epsilon;

public:
    EpsilonCriterion(double epsilon) : epsilon(epsilon) {}

    bool done(const std::vector<std::vector<double>>& trajectory) const override {
        if (trajectory.size() < 2) throw "trajectory size twoo small";

        double dist = 0;
        for (size_t i=0; i < trajectory[0].size(); ++i) {
            dist += trajectory[trajectory.size()-1][i] - trajectory[trajectory.size()-2][i];
        }
        if (dist < epsilon) return true;
        return false;
    }
};