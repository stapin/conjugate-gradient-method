#pragma once

#include <vector>
#include <limits>
#include <random>
#include <iostream>

class Rectangle {
protected:
    std::vector<std::pair<double, double>> bounds;

public:
    Rectangle() = default;
    Rectangle(std::vector<std::pair<double, double>> bounds);
    virtual ~Rectangle() = default;

    virtual double intersect(const std::vector<double>& x0, const std::vector<double>& v) const;

    virtual const std::vector<std::pair<double, double>>& get_bounding_box() const;

    virtual std::vector<double> sample_random_point(std::mt19937& gen) const;

    Rectangle intersect_rectangle(const Rectangle& other) const {
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


    bool is_empty() {
        if (bounds.size()) return false;
        return true;
    }
};

class Interval : public Rectangle {
public:
    Interval(double a, double b) : Rectangle({{a, b}}) {};
    Interval() : Rectangle({{0, 0}}) {}

    void set_bounds(double left, double right);

};

class Cube : public Rectangle {
public:
    Cube(const std::vector<double>& x0, double a, bool neighborhood=false) {
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
};

