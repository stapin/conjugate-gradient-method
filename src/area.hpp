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
    virtual std::vector<std::pair<double, double>> get_bounding_box() const = 0;
    virtual V sample_random_point() const = 0;

    virtual ~Area() = default;
    
};

template<>
class Area<double> {
public:
    virtual double intersect(double x0, double v) const = 0;
    virtual std::pair<double, double> get_bounding_box() const = 0;
    virtual double sample_random_point() const = 0;

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

    double sample_random_point() const override;

};

class Rectangle : public Area<> {
private:
    std::vector<double> left;
    std::vector<double> right;

public:
    Rectangle(std::vector<double> left, std::vector<double> right);

    double intersect(const std::vector<double>& x0, const std::vector<double>& v) const override;

    std::vector<std::pair<double, double>> get_bounding_box() const override;

    std::vector<double> sample_random_point() const override;
};

