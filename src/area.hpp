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
    Rectangle intersect_rectangle(const Rectangle& other) const;

    /**
     * @brief Check, if rectangle is degenerate.
     * 
     * @return true, if area of rectangle equals zero.
     * @return false, otherwise
     */
    bool is_empty() const;

    size_t get_dim() const;
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
    Cube(const std::vector<double>& x0, double a, bool neighborhood=false);
};

