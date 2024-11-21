#include <vector>
#include <limits>
/*
    Хранит область.
*/

template <typename V = std::vector<double>>
class Area
{
private:
    
public:
    Area();

    bool is_out_of_bounds(V x);
    // Или сделать расстояние от точки до множества

    virtual double intersect(const V& x0, const V& v) const = 0;
    virtual std::vector<std::pair<double, double>> get_bounding_box() const = 0;

    ~Area();
    
};

template<>
class Area<double> {
public:
    bool is_out_of_bounds(double x);
    // Или сделать расстояние от точки до множества

    virtual double intersect(double x0, double v) const = 0;
    virtual std::pair<double, double> get_bounding_box() const = 0;

};

class Interval : public Area<double> {
private:
    double a;
    double b;
public:
    Interval(double a, double b) : a(a), b(b) {};

    double intersect(double x0, double v) const override {
        return 0;
    }

    void set_bounds(double left, double right) {
        a = left;
        b = right;
    }

    virtual std::pair<double, double> get_bounding_box() const {
        return std::pair<double, double>(a, b);
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
        for (int i=0; i < left.size(); ++i) {
            double r = (right[i] - x0[i]) / v[i];
            double l = (left[i] - x0[i]) / v[i];
            res = std::min(res, std::max(r, l));
        }
        return res;
    }
};

