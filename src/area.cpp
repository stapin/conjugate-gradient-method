#include "area.hpp"
#include <algorithm>

void Interval::set_bounds(double left, double right) {
    bounds = {{left, right}};
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
    // for (size_t i = 0; i < bounds.size(); ++i) {
    //     double alpha = dist(gen);
    //     res.push_back(bounds[i].first + (bounds[i].second - bounds[i].first) * alpha);
    // }
    for (auto it = bounds.begin(); it != bounds.end(); ++it) {
        double alpha = dist(gen);
        res.push_back((*it).first + ((*it).second - (*it).first) * alpha);
    }
    return res;
} 

Rectangle Rectangle::intersect_rectangle(const Rectangle& other) const {
    if (other.bounds.size() != bounds.size())
        throw "Rectangle sizes are incompatible";
    std::vector<std::pair<double, double>> res;
    res.reserve(bounds.size());
    for (size_t i = 0; i < bounds.size(); ++i) {
        double left = std::max(bounds[i].first, other.bounds[i].first);
        double right = std::min(bounds[i].second, other.bounds[i].second);
        if (left >= right) {
            return Rectangle();
        }
        res.push_back(std::pair<double, double>(left, right));
    }

    return Rectangle(std::move(res));
}

bool Rectangle::is_empty() const {
    if (bounds.size()) return false;
    return true;
}

size_t Rectangle::get_dim() const {
    return bounds.size();
}

Cube::Cube(const std::vector<double>& x0, double a, bool neighborhood) {
    if (a <= 0) throw "Cube can`t have negative or zero side length."; 
    bounds.reserve(x0.size());
    if (neighborhood) {
        // for (size_t i = 0; i < x0.size(); ++i) {
        //     bounds.push_back(std::pair<double, double>(x0[i] - a/2, x0[i] + a/2));
        // }
        for (auto it = x0.begin(); it < x0.end(); ++it) {
            bounds.push_back(std::pair<double, double>(*it - a/2, *it + a/2));
        }
    } else {
        // for (size_t i = 0; i < x0.size(); ++i) {
        //     bounds.push_back(std::pair<double, double>(x0[i], x0[i] + a));
        // }
        for (auto it = x0.begin(); it < x0.end(); ++it) {
            bounds.push_back(std::pair<double, double>(*it, *it + a));
        }
    }
}