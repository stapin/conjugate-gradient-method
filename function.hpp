#include <vector>
#include <exception>
// Будем делать градиент аналитическим, поэтому для каждой функции будем делать класс
// и переопределять метод с градиентом.

template <typename T = std::vector<double>>
class Function {
protected:
    size_t dim;
public:
    Function(size_t dim) : dim(dim) {};

    virtual size_t get_dim() const;
    virtual double operator()(const T& x) const = 0;
    virtual T get_gradient(const T& x) const = 0;
};

class LinearFunction : public Function<> {
private:
    std::vector<double> coeffs;
public:
    LinearFunction(std::vector<double> coeffs) :
        Function(coeffs.size()),
        coeffs(std::move(coeffs)) {} 

    double operator()(const std::vector<double>& x) const override {
        double result = 0;
        for (size_t i=0; i < coeffs.size(); ++i) {
            result += coeffs[i] * x[i];
        }
        return result;
    }

    std::vector<double> get_gradient(const std::vector<double>& x) const override {
        return coeffs;
    }
};

using Mat = std::vector<std::vector<double>>;

class QuadraticForm : public Function<> {
private:
    Mat A;

public:
    QuadraticForm(Mat A) : Function(A.size()), A(A) {};
    
    double operator()(const std::vector<double>& x) const override {
        double result = 0;
        for (int i = 0; i < A.size(); ++i) {
            double tmp = 0;
            for (int j = 0; j < x.size(); ++j) {
                tmp += x[j] * A[i][j];
            }
            result += x[i] * tmp;
        }
        return result;
    }

    std::vector<double> get_gradient(const std::vector<double>& x) const override {
        std::vector<double> result(A.size());
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                result[i] += x[j] * (A[i][j] + A[j][i]);
            }
        }
        return result;
    }

};


class OneDimentionalFunction : public Function<double> {
    double (*function)(double);
public:
    OneDimentionalFunction(double (*function)(double)) : 
        Function(1), function(function) {}

    double operator()(const double& x) const override {
        return function(x);
    }

    double get_gradient(const double& x) const override {
        throw std::exception("OneDimentionalFunction get_gradient not implemented");
    }

};