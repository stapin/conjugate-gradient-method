#pragma once

#include <vector>
#include <exception>
#include <memory>
#include <iostream>
#include <cmath>
#include <string>

/**
 * @brief Base class for all functions
 * 
 * @tparam T arbitrary vector space
 */
template <typename T = std::vector<double>>
class Function {
protected:
    size_t dim;
public:
    Function(size_t dim) : dim(dim) {};
    virtual ~Function() = default;

    virtual size_t get_dim() const {return dim;};
    virtual double operator()(const T& x) const = 0;
    virtual T get_gradient(const T& x) const = 0;
    /**
     * @brief Creates shared_ptr of current object to base class
     * 
     * @return std::shared_ptr<Function> 
     */
    virtual std::shared_ptr<Function> create_instance() const = 0;
    virtual std::string get_name() const = 0;
};

class LinearFunction : public Function<> {
private:
    std::vector<double> coeffs;
public:
    LinearFunction(std::vector<double> coeffs);

    double operator()(const std::vector<double>& x) const override;

    std::vector<double> get_gradient(const std::vector<double>& x) const override;

    std::shared_ptr<Function> create_instance() const override;
    std::string get_name() const override;
};

class Func1 : public Function<> {
public:
    Func1() : Function(2) {}

    double operator()(const std::vector<double>& x) const override {
        return (x[0] + 1) * (x[1] - 1);
    }

    std::vector<double> get_gradient(const std::vector<double>& x) const override  {
        return std::vector<double>({x[1] - 1, x[0] + 1});
    }

    std::shared_ptr<Function> create_instance() const override {
        return std::make_shared<Func1>(*this);
    }

    std::string get_name() const override;
};

class Func2 : public Function<> {
public:
    Func2() : Function(2) {}

    double operator()(const std::vector<double>& x) const override {
        return std::sin(x[0]) * std::cos(x[1]);
    }

    std::vector<double> get_gradient(const std::vector<double>& x) const override {
        return std::vector<double>({std::cos(x[0]) * std::cos(x[1]), -std::sin(x[0]) * std::sin(x[1])});
    }

    std::shared_ptr<Function> create_instance() const override {
        return std::make_shared<Func2>(*this);
    }

    std::string get_name() const override;
};


class Func3 : public Function<> {
public:
    Func3() : Function(2) {}

    double operator()(const std::vector<double>& x) const override {
        return std::sin(x[0]) + std::cos(x[1]);
    }

    std::vector<double> get_gradient(const std::vector<double>& x) const override {
        return std::vector<double>({std::cos(x[0]), - std::sin(x[1])});
    }

    std::shared_ptr<Function> create_instance() const override {
        return std::make_shared<Func3>(*this);
    }

    std::string get_name() const override;
};

using Mat = std::vector<std::vector<double>>;

class QuadraticForm : public Function<> {
private:
    Mat A;

public:
    QuadraticForm(Mat A);
    
    double operator()(const std::vector<double>& x) const override;

    std::vector<double> get_gradient(const std::vector<double>& x) const override;


    std::shared_ptr<Function> create_instance() const override;

    std::string get_name() const override;
};

class AuxiliaryFunction : public Function<> {
    std::vector<double> x;
    std::vector<double> v;
    std::shared_ptr<Function<>> func;    

public:
    AuxiliaryFunction(std::vector<double> x, std::vector<double> v, const std::shared_ptr<Function<>>& func);

    double operator()(const std::vector<double>& alpha) const override;

    std::vector<double> get_gradient(const std::vector<double>& alpha) const override;

    void set_vectors(std::vector<double> x0, std::vector<double> v0);

    std::shared_ptr<Function> create_instance() const override;

    std::string get_name() const override;
};


class Func4 : public Function<> {
public:
    Func4();

    double operator()(const std::vector<double>& x) const override;

    std::vector<double> get_gradient(const std::vector<double>& x) const override;

    std::shared_ptr<Function> create_instance() const override;

    std::string get_name() const override;
};

class Poly1 : public Function<> {
public:
    Poly1();
    double operator()(const std::vector<double>& x) const override;

    std::vector<double> get_gradient(const std::vector<double>& x) const override;

    std::shared_ptr<Function> create_instance() const override;

    std::string get_name() const override;
};