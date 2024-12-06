#pragma once

#include "optimization_method.hpp"
#include <memory>

class OptimMethodCLI {
private:
    bool running;

    std::vector<std::shared_ptr<Function<>>> functions;
    std::shared_ptr<Function<>> curr_func;
    std::shared_ptr<Rectangle> curr_area;
    std::shared_ptr<Criterion> curr_criterion;
    std::shared_ptr<OptimizationMethod<>> curr_method;
    std::vector<double> curr_starting_point;

    enum {
        FUNC,
        AREA,
        CRITERION,
        METHOD,
        START_POINT,
        START_OPTIM,
        EXIT
    } MENU_PUNCT;

    enum {
        FUNC1,
        FUNC2,
        FUNC3,
        FUNC4
    } FUNC;

    enum  {
        ITER,
        EPS
    } CRITERION;

    enum {
        CONJ,
        RANDOM
    } S_METHOD;
    
public:
    OptimMethodCLI();
    ~OptimMethodCLI();

    void start() {

        while (running)
        {
            std::cout << "Оптимизация многомерных функций.\n";
            std::cout << "Заданы параметры по умолчанию:\n";
            std::cout << "1) Функция: " << curr_func->get_name() << "\n";
            std::cout << "2) Область: ";
            print_area();
            std::cout << "3) Критерий остановки: " << curr_criterion->get_name() << "\n";
            std::cout << "4) Метод оптимизации: " << curr_method->get_name() << "\n";
            std::cout << "5) Начальная точка: ";
            print_stdvec(curr_starting_point);
            std::cout << "\n";
            std::cout << "Выберите действие:\n";
            std::cout << "1) Изменить функцию\n";
            std::cout << "2) Изменить область\n";
            std::cout << "3) Изменить критерий остановки\n";
            std::cout << "4) Изменить метод оптимизации\n";
            std::cout << "5) Изменить начальную точку\n";
            std::cout << "6) Запустить оптимизацию\n";
            std::cout << "7) Выключить программу\n";
            int choice;
            std::cin >> choice;
            make_choice(choice);
        }
        

    }

private:
    void print_stdvec(const std::vector<double>& vec) {
        for (auto& el : vec) {
            std::cout << el << " ";
        }
    }

    void print_area() {
        for (auto& el : curr_area->get_bounding_box()) {
            std::cout << "[" << el.first << " " << el.second << "]\n";
        }
    }

    void make_choice(int choice) {
        switch (choice)
        {
        case FUNC:
            func_menu();
            break;
        case AREA:
            area_menu();
            break;
        case CRITERION:
            criterion_menu();
            break;
        case METHOD:
            method_menu();
            break;
        case START_POINT:
            starting_point_menu();
            break;
        case START_OPTIM:
            start_optim_menu();
            break;
        case EXIT:
            running = false;
            break;
        default:
            break;
        }
    }

    void starting_point_menu() {
        std::cout << "Enter starting point:\n";
        std::cout << "Example: 3.5 -1 0.1\n";
        curr_starting_point.clear();
        curr_starting_point.resize(curr_func->get_dim());
        for (size_t i = 0; i < curr_func->get_dim(); ++i) {
            std::cin >> curr_starting_point[i];
        }
    }

    void start_optim_menu() {
        curr_method->optimize(*curr_area, *curr_func, *curr_criterion);
        BestParams best_params = curr_method->get_best_params();
        std::cout << "Minimum point: ";
        for (size_t i = 0; i < best_params.minimum_point.size(); ++i) {
            std::cout << best_params.minimum_point[i] << " ";
        }
        std::cout << "\nMinimum value: " << best_params.minimum_value << "\n";
        std::cout << "Iteration number: " << best_params.iter_number << "\n";

    }

    void method_menu() {
        std::cout << "Выберите метод оптимизации:\n";
        std::cout << "1) Метод сопряженных градиентов.\n";
        std::cout << "2) Случайный поиск.\n";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case CONJ:
            curr_method = std::make_shared<ConjugateGradientMethod>();
            break;
        case RANDOM:
            double delta, p;
            size_t max_iters;
            std::cout << "Enter delta:\n";
            std::cin >> delta;
            std::cout << "Enter p:\n";
            std::cin >> p;
            std::cout << "Enter max iteration number:\n";
            std::cin >> max_iters;

            curr_method = std::make_shared<RandomSearch>(delta, p, max_iters);
            break;
        default:
            break;
        }
    }

    void criterion_menu() {
        std::cout << "Выберите критерий остановки из списка:\n";
        std::cout << "1) Число итераций\n";
        std::cout << "2) ||x_{n+1} - x_n||\n";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case ITER:
            size_t max_iter;
            std::cout << "Введите максимальное число итерациий:\n";
            std::cin >> max_iter;
            curr_criterion = std::make_shared<IterationCriterion>(max_iter);
            break;

        case EPS:
            double eps;
            std::cout << "Введите epsilon:\n";
            std::cin >> eps;
            curr_criterion = std::make_shared<EpsilonCriterion>(eps);
            break;

        default:
            break;
        }

    }


    void set_func(int choice) {
        curr_func = functions[choice-1];
    }

    void func_menu() {
        std::cout << "Выберите функцию из списка:\n";
        for (size_t i = 0; i < functions.size(); ++i) {
            std::cout << i+1 << ") " << functions[i]->get_name() << "\n";
        }
        int choice;
        std::cin >> choice;
        set_func(choice);
    }

    void area_menu() {
        std::cout << "Установите границы области:\n";
        std::cout << "Размерность функции " << curr_func->get_dim() << "\n";
        std::cout << "Введите границы прямоугольной области:\n";
        std::vector<std::pair<double, double>> bounds;
        for (size_t i=0; i < curr_func->get_dim(); ++i) {
            double a, b;
            std::cin >> a >> b;
            bounds.push_back({a, b});
        }
        curr_area = std::make_shared<Rectangle>(bounds);
    }
};

OptimMethodCLI::OptimMethodCLI() {
    functions.push_back(std::make_shared<Func1>());
    functions.push_back(std::make_shared<Func2>());
    functions.push_back(std::make_shared<Func3>());

    curr_func = functions[0];
}

OptimMethodCLI::~OptimMethodCLI()
{
}
