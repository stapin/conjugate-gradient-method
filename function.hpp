#include <vector>
#include <exception>
#include <memory>
#include <iostream>
#include <cmath>
// Будем делать градиент аналитическим, поэтому для каждой функции будем делать класс
// и переопределять метод с градиентом.

template <typename T = std::vector<double>>
class Function {
protected:
    size_t dim;
public:
    Function(size_t dim) : dim(dim) {};

    virtual size_t get_dim() const {return dim;};
    virtual double operator()(const T& x) const = 0;
    virtual T get_gradient(const T& x) const = 0;
    virtual std::shared_ptr<Function> create_instance() const = 0;
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

    std::shared_ptr<Function> create_instance() const override {
        return std::make_shared<LinearFunction>(*this);
    }

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
};

using Mat = std::vector<std::vector<double>>;

class QuadraticForm : public Function<> {
private:
    Mat A;

public:
    QuadraticForm(Mat A) : Function(A.size()), A(A) {
        std::cout << "Quad constructor, dim: " << dim << "\n";
    };
    
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
        //std::cout << "A.size " << A.size() << " x.size " << x.size() << "\n";
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                result[i] += x[j] * (A[i][j] + A[j][i]);
                // std::cout << "i:" << i << " j:" << j << " res: " << result[i] << " x[j]: "<< x[j] <<
                // " Aij: " << A[i][j] << " Aji: " << A[j][i] << "\n";
            }
        }
        return result;
    }


    std::shared_ptr<Function> create_instance() const override {
        return std::make_shared<QuadraticForm>(*this);
    }

};

class AuxiliaryFunction : public Function<double> {
    std::vector<double> x;
    std::vector<double> v;
    std::shared_ptr<Function<>> func;    

public:
    AuxiliaryFunction(std::vector<double> x, std::vector<double> v, const std::shared_ptr<Function<>>& func) :
        x(std::move(x)), v(std::move(v)), Function(1), func(func) {}

    double operator()(const double& alpha) const override {
        std::vector<double> res;
        res.reserve(x.size());
        for (size_t i = 0; i < x.size(); ++i) {
            res.push_back(x[i] + alpha* v[i]);
        }
        return (*func)(res);
    }

    double get_gradient(const double& alpha) const override {
        //throw std::exception("not implemented");
        std::vector<double> point;
        point.reserve(x.size());
        for (size_t i = 0; i < x.size(); ++i) {
            point.push_back(x[i] + alpha* v[i]);
        }
        std::vector<double> grad = func->get_gradient(point);
        double res = 0;
        for (size_t i = 0; i < grad.size(); ++i) {
            res += grad[i] * v[i];
        }
        
        return res;
    };

    void set_vectors(std::vector<double> x0, std::vector<double> v0) {
        x = std::move(x0);
        v = std::move(v0);
    }

    std::shared_ptr<Function> create_instance() const override {
        return std::make_shared<AuxiliaryFunction>(*this);
    }
};


class Func4 : public Function<double> {
public:
    Func4() : Function(1) {}

    double operator()(const double& x) const override {
        return std::sin(x);
    }

    double get_gradient(const double& x) const override {
        return std::cos(x);
    }

    std::shared_ptr<Function> create_instance() const override {
        return std::make_shared<Func4>(*this);
    }
};

class Poly1 : public Function<double> {
public:
    Poly1() : Function(1) {}
    double operator()(const double& x) const override {
        return (x - 3.5) * (x + 1) * (x - 1);
    }

    double get_gradient(const double& x) const override {
        return 3 * x*x - 7 * x - 1;
    }

    std::shared_ptr<Function> create_instance() const override {
        return std::make_shared<Poly1>(*this);
    }
};

// class Sin1 : public Function<double> {
//     Sin1() : Function(1) {}
//     double operator()(const double& x) const override {
//         return std::sin(x);
//     }

//     double get_gradient(const double& x) const override {
//         return std:;
//     }

//     std::shared_ptr<Function> create_instance() const override {
//         return std::make_shared<Poly1>(*this);
//     }
// }