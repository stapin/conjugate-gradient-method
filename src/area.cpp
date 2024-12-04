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

double Interval::sample_random_point() const  {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dist(a, b);
    return dist(gen);
}


Rectangle::Rectangle(std::vector<double> left, std::vector<double> right) :
    left(std::move(left)), right(std::move(right)) {}

double Rectangle::intersect(const std::vector<double>& x0, const std::vector<double>& v) const {
    double res = std::numeric_limits<double>::max();
    for (size_t i=0; i < left.size(); ++i) {
        double r = (right[i] - x0[i]) / v[i];
        double l = (left[i] - x0[i]) / v[i];
        res = std::min(res, std::max(r, l));
    }
    return res;
}

std::vector<std::pair<double, double>> Rectangle::get_bounding_box() const {
    return std::vector<std::pair<double, double>>({std::pair<double, double>(1, 2)});
}

std::vector<double> Rectangle::sample_random_point() const {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dist(0., 1.);
    std::vector<double> res;
    res.reserve(left.size());
    for (size_t i = 0; i < left.size(); ++i) {
        double alpha = dist(gen);
        res.push_back(left[i] + (right[i] - left[i]) * alpha);
    }
    return res;
} 