#pragma once

#include <vector>
#include <limits>
#include <random>
#include <iostream>

template <typename V = std::vector<double>>
class Area
{
private:
    
public:
    Area() = default;


    virtual double intersect(const V& x0, const V& v) const = 0;
    virtual const std::vector<std::pair<double, double>>& get_bounding_box() const = 0;
    virtual V sample_random_point(std::mt19937& gen) const = 0;
    virtual Rectangle intersect_cube(const Cube& other) const = 0;

    virtual ~Area() = default;
    
};

template<>
class Area<double> {
public:
    virtual double intersect(double x0, double v) const = 0;
    virtual std::pair<double, double> get_bounding_box() const = 0;
    virtual double sample_random_point(std::mt19937& gen) const = 0;

};

class Interval : public Area<double> {
private:
    double a;
    double b;
public:
    Interval(double a, double b) : a(a), b(b) {};
    Interval() : a(0), b(0) {}

    double intersect(double x0, double v) const override;

    void set_bounds(double left, double right);

    virtual std::pair<double, double> get_bounding_box() const override;

    double sample_random_point(std::mt19937& gen) const override;

};

class Rectangle : public Area<> {
protected:
    std::vector<std::pair<double, double>> bounds;

public:
    Rectangle() = default;
    Rectangle(std::vector<std::pair<double, double>> bounds);

    double intersect(const std::vector<double>& x0, const std::vector<double>& v) const override;

    const std::vector<std::pair<double, double>>& get_bounding_box() const override;

    std::vector<double> sample_random_point(std::mt19937& gen) const override;

    Rectangle intersect_cube(const Cube& other) const override{
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

class Cube : public Rectangle {
public:
    Cube(const std::vector<double>& x0, double a, bool neighborhood=false) {
        if (a <= 0) throw "Cube can`t have negative or zero side length."; 
        bounds.reserve(x0.size());
        if (neighborhood) {
            for (size_t i = 0; i < x0.size(); ++i) {
                bounds[i] = std::pair<double, double>(x0[i] - a/2, x0[i] + a/2);
            }
        } else {
            for (size_t i = 0; i < x0.size(); ++i) {
                bounds[i] = std::pair<double, double>(x0[i], x0[i] + a);
            }
        }
    }
};

