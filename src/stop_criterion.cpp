#include "stop_criterion.hpp"

IterationCriterion::IterationCriterion(size_t max_iter) : max_iter(max_iter) {}

bool IterationCriterion::done(const std::vector<std::vector<double>>& trajectory) const {
    if (trajectory.size() >= max_iter) return true;
    return false;
}


EpsilonCriterion::EpsilonCriterion(double epsilon) : epsilon(epsilon) {}

bool EpsilonCriterion::done(const std::vector<std::vector<double>>& trajectory) const {
    if (trajectory.size() < 2) return false;

    double dist = 0;
    for (size_t i=0; i < trajectory[0].size(); ++i) {
        double d = trajectory[trajectory.size()-1][i] - trajectory[trajectory.size()-2][i];
        dist += d * d;
    }
    if (dist < epsilon * epsilon) return true;
    return false;
}