#include "function.hpp"

LinearFunction::LinearFunction(std::vector<double> coeffs) :
    Function(coeffs.size()),
    coeffs(std::move(coeffs)) {} 

double LinearFunction::operator()(const std::vector<double>& x) const {
    double result = 0;
    for (size_t i=0; i < coeffs.size(); ++i) {
        result += coeffs[i] * x[i];
    }
    return result;
}

std::vector<double> LinearFunction::get_gradient(const std::vector<double>& x) const {
    return coeffs;
}

std::shared_ptr<Function<>> LinearFunction::create_instance() const {
    return std::make_shared<LinearFunction>(*this);
}


QuadraticForm::QuadraticForm(Mat A) : Function(A.size()), A(A) {};

double QuadraticForm::operator()(const std::vector<double>& x) const {
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

std::vector<double> QuadraticForm::get_gradient(const std::vector<double>& x) const {
    std::vector<double> result(A.size());
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < x.size(); ++j) {
            result[i] += x[j] * (A[i][j] + A[j][i]);
        }
    }
    return result;
}


std::shared_ptr<Function<>> QuadraticForm::create_instance() const  {
    return std::make_shared<QuadraticForm>(*this);
}


AuxiliaryFunction::AuxiliaryFunction(std::vector<double> x, std::vector<double> v, const std::shared_ptr<Function<>>& func) :
    Function(1), x(std::move(x)), v(std::move(v)), func(func) {}

double AuxiliaryFunction::operator()(const double& alpha) const  {
    std::vector<double> res;
    res.reserve(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        res.push_back(x[i] + alpha* v[i]);
    }
    return (*func)(res);
}

double AuxiliaryFunction::get_gradient(const double& alpha) const {
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

void AuxiliaryFunction::set_vectors(std::vector<double> x0, std::vector<double> v0) {
    x = std::move(x0);
    v = std::move(v0);
}

std::shared_ptr<Function<double>> AuxiliaryFunction::create_instance() const {
    return std::make_shared<AuxiliaryFunction>(*this);
}


Func4::Func4() : Function(1) {}

double Func4::operator()(const double& x) const {
    return std::sin(x);
}

double Func4::get_gradient(const double& x) const {
    return std::cos(x);
}

std::shared_ptr<Function<double>> Func4::create_instance() const {
    return std::make_shared<Func4>(*this);
}

Poly1::Poly1() : Function(1) {}
double Poly1::operator()(const double& x) const {
    return (x - 3.5) * (x + 1) * (x - 1);
}

double Poly1::get_gradient(const double& x) const {
    return 3 * x*x - 7 * x - 1;
}

std::shared_ptr<Function<double>> Poly1::create_instance() const {
    return std::make_shared<Poly1>(*this);
}

std::string LinearFunction::get_name() const {
    return "Arbitrary linear f  unction";
}

std::string Func1::get_name() const {
    return "(x + 1)(y - 1)";
}

std::string Func2::get_name() const {
    return "sin(x)cos(y)";
}

std::string Func3::get_name() const {
    return "sin(x) + cos(y)";
}

std::string QuadraticForm::get_name() const {
    return "Arbitrary quadratic form";
}

std::string AuxiliaryFunction::get_name() const {
    return "Auxiliary function";
}

std::string Func4::get_name() const {
    return "sin(x)";
}

std::string Poly1::get_name() const {
    return "(x - 3.5)(x - 1)(x + 1)";
}