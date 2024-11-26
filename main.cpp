#include <iostream>
#include "optimization_method.hpp"



int main() {


    Mat A = {{1, 0}, {0, 1}};
    std::shared_ptr<Function<>> func = std::make_shared<QuadraticForm>(A);
    std::vector<double> left = {-1, -1};
    std::vector<double> right = {1, 1};

    std::shared_ptr<Area<>> area = std::make_shared<Rectangle>(left, right);
    std::shared_ptr<Criterion> criterion = std::make_shared<IterationCriterion>(100);

    ConjugateGradientMethod optim(area, func, criterion);
    std::vector<double> res = optim.optimize();

    std::cout << "size: " << res.size() << "\n";
    std::cout << "dim: " << func->get_dim() << "\n";
    std::cout << "vec: " << A.size() << "\n";

    for (size_t i = 0; i < res.size(); ++i) {
        std::cout << res[i] << " ";
    }

    return 0;
}