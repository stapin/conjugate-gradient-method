#include <iostream>
#include "optimization_method.hpp"



int main() {


    Mat A = {{1, 0}, {0, 1}};
    //QuadraticForm func(A);
    //std::cout << "1 dim: " << func.get_dim() << "\n";
    // Func1 func;
    Func2 func;
    // Func3 func;
    std::vector<double> left = {-3, -2};
    std::vector<double> right = {0, 2};
    std::vector<std::pair<double, double>> bounds = {
        {-3, -1}, {-1, 1}
    };

    Rectangle area(bounds);
    IterationCriterion criterion(10);

    ConjugateGradientMethod optim;
    std::vector<double> res;

    try {
        res = optim.optimize(area, func, criterion);
        
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    

    std::cout << "size: " << res.size() << "\n";
    std::cout << "dim: " << func.get_dim() << "\n";
    //std::cout << "vec: " << A.size() << "\n";

    for (size_t i = 0; i < res.size(); ++i) {
        std::cout << res[i] << " ";
    }

    // OneDimentionalOptimization one_optim;
    // Poly1 f4;
    // Interval interval(-4, 4);
    // double ans = one_optim.optimize(interval, f4, criterion);
    // std::cout << "one dim opt: " << ans << "\n"; 

    return 0;
}