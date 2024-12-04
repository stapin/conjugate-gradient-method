#include <vector>
#include <limits>
#include <random>
#include <iostream>
/*
    Хранит область.
*/

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

    double intersect(double x0, double v) const override {
        return std::max((b - x0) / v, (a - x0) / v);
    }

    void set_bounds(double left, double right) {
        a = left;
        b = right;
    }

    virtual std::pair<double, double> get_bounding_box() const override {
        return std::pair<double, double>(a, b);
    }

    double sample_random_point() const override {
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_real_distribution<> dist(a, b);
        return dist(gen);
    }

};

class Rectangle : public Area<> {
private:
    std::vector<double> left;
    std::vector<double> right;

public:
    Rectangle(std::vector<double> left, std::vector<double> right) :
        left(std::move(left)), right(std::move(right)) {}

    double intersect(const std::vector<double>& x0, const std::vector<double>& v) const override {
        double res = std::numeric_limits<double>::max();
        // std::cout << "x0: " << x0.size() << " v: " << v.size() << " left: " << left.size() << "right: " << right.size() << "\n";
        for (size_t i=0; i < left.size(); ++i) {
            double r = (right[i] - x0[i]) / v[i];
            double l = (left[i] - x0[i]) / v[i];
            res = std::min(res, std::max(r, l));
        }
        return res;
    }

    std::vector<std::pair<double, double>> get_bounding_box() const override {
        return std::vector<std::pair<double, double>>({std::pair<double, double>(1, 2)});
    }

    std::vector<double> sample_random_point() const override{
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
};

