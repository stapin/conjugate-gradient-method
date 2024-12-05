#include "area.hpp"

double Interval::intersect(double x0, double v) const {
    return std::max((b - x0) / v, (a - x0) / v);
}

void Interval::set_bounds(double left, double right) {
    a = left;
    b = right;
}

std::pair<double, double> Interval::get_bounding_box() const {
    return std::pair<double, double>(a, b);
}

double Interval::sample_random_point(std::mt19937& gen) const  {
    std::uniform_real_distribution<> dist(a, b);
    return dist(gen);
}


Rectangle::Rectangle(std::vector<std::pair<double, double>> bounds) :
    bounds(std::move(bounds)) {}

double Rectangle::intersect(const std::vector<double>& x0, const std::vector<double>& v) const {
    double res = std::numeric_limits<double>::max();
    for (size_t i=0; i < bounds.size(); ++i) {
        double r = (bounds[i].second - x0[i]) / v[i];
        double l = (bounds[i].first - x0[i]) / v[i];
        res = std::min(res, std::max(r, l));
    }
    return res;
}

const std::vector<std::pair<double, double>>& Rectangle::get_bounding_box() const {
    return bounds;
}

std::vector<double> Rectangle::sample_random_point(std::mt19937& gen) const {
    std::uniform_real_distribution<> dist(0., 1.);
    std::vector<double> res;
    res.reserve(bounds.size());
    for (size_t i = 0; i < bounds.size(); ++i) {
        double alpha = dist(gen);
        res.push_back(bounds[i].first + (bounds[i].second - bounds[i].first) * alpha);
    }
    return res;
} 