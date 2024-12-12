#pragma once

#include <vector>
#include <limits>
#include <random>
#include <iostream>

/**
 * @brief Base class for the area that implements rectangle.
 * 
 */
class Rectangle {
protected:
    std::vector<std::pair<double, double>> bounds;

public:
    Rectangle() = default;
    Rectangle(std::vector<std::pair<double, double>> bounds);
    virtual ~Rectangle() = default;

    /**
     * @brief Intersects vector v emanating from a point x0 with
     * rectangle bounds and returns coefficient alpha such that
     * alpha * v + x0 lies on bounds, alpha > 0.
     * 
     * @param x0 
     * @param v 
     * @return double 
     */
    virtual double intersect(const std::vector<double>& x0, const std::vector<double>& v) const;

    /**
     * @brief Get the bounding box object
     * 
     * @return const std::vector<std::pair<double, double>>& 
     */
    virtual const std::vector<std::pair<double, double>>& get_bounding_box() const;

    /**
     * @brief Samples random point inside the rectangle.
     * 
     * @param gen 
     * @return std::vector<double> 
     */
    virtual std::vector<double> sample_random_point(std::mt19937& gen) const;

    /**
     * @brief Returns intersection of two rectangles.
     * 
     * @param other 
     * @return Rectangle 
     */
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

    /**
     * @brief Check, if rectangle is degenerate.
     * 
     * @return true, if area of rectangle equals zero.
     * @return false, otherwise
     */
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

    /**
     * @brief Construct a new Cube object
     * 
     * @param x0 left bottom point
     * @param a side length
     * @param neighborhood if true, then x0 - center of a cube
     */
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

