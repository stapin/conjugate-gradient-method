#pragma once

// #include "optimization_method.hpp"
// #include <memory>

// class OptimMethodCLI {
// private:
//     std::vector<std::shared_ptr<Function<>>> functions;
//     std::shared_ptr<Function<>> curr_func;
//     std::shared_ptr<Rectangle<>> curr_area;
//     std::shared_ptr<Criterion> curr_criterion;
//     std::shared_ptr<OptimizationMethod<>> curr_method;
    
// public:
//     OptimMethodCLI();
//     ~OptimMethodCLI();

//     void start() {
//         std::cout << "Оптимизация многомерных функций.\n";
//         std::cout << "Заданы параметры по умолчанию:\n";
//         std::cout << "1) Функция: " << curr_func->get_name();
//         std::cout << "2) Область: " ;
//         std::cout << "3) Критерий остановки: ";
//         std::cout << "4) Метод оптимизации: ";
//         std::cout << "Хотите поменять параметры? 1-да, 0-нет";
//         int ans;
//         std::cin >> ans;
//         if (ans == 1) {
//             std::cout << "Выберите параметр для изменения: \n";
//             int param;
//             std::cin >> param;

//         }

//     }

//     // void change_param(int param) {
//     //     switch (param)
//     //     {
//     //     case 1:
            
//     //         break;
        
//     //     default:
//     //         break;
//     //     }
//     // }

//     // void set_func() {

//     // }
// };

// OptimMethodCLI::OptimMethodCLI() {
//     functions.push_back(std::make_shared<Func1>());
//     functions.push_back(std::make_shared<Func2>());
//     functions.push_back(std::make_shared<Func3>());

//     curr_func = functions[0];
// }

// OptimMethodCLI::~OptimMethodCLI()
// {
// }
