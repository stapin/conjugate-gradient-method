#include "stop_criterion.hpp"

IterationCriterion::IterationCriterion(size_t max_iter) : max_iter(max_iter) {}

bool IterationCriterion::done(const std::vector<std::vector<double>>& trajectory) const {
    if (trajectory.size() >= max_iter) return true;
    return false;
}


EpsilonCriterion::EpsilonCriterion(double epsilon) : epsilon(epsilon) {}

bool EpsilonCriterion::done(const std::vector<std::vector<double>>& trajectory) const {
    if (trajectory.size() < 2) throw "trajectory size twoo small";

    double dist = 0;
    for (size_t i=0; i < trajectory[0].size(); ++i) {
        dist += trajectory[trajectory.size()-1][i] - trajectory[trajectory.size()-2][i];
    }
    if (dist < epsilon) return true;
    return false;
}