#pragma once

#include "optimization_method.hpp"
#include <memory>

/**
 * @brief Implements cli for optimization for custom functions,
 * areas and criterions.
 * 
 */
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
    } FUNCTION;

    enum  {
        ITER,
        EPS
    } CRITERIA;

    enum {
        CONJ,
        RANDOM
    } S_METHOD;
    
public:
    OptimMethodCLI();
    ~OptimMethodCLI() = default;

    /**
     * @brief Starts CLI for function optimization.
     * 
     */
    void start() {
        init_params();
        while (running)
        {
            std::cout << "Function Optimization CLI.\n";
            std::cout << "Current parameters:\n";
            std::cout << "1) Function: " << curr_func->get_name() << "\n";
            std::cout << "2) Area: ";
            print_area();
            std::cout << "3) Stop criterion: " << curr_criterion->get_name() << "\n";
            std::cout << "4) Optimization method: " << curr_method->get_name() << "\n";
            std::cout << "5) Starting point: ";
            print_stdvec(curr_starting_point);
            std::cout << "\n";
            std::cout << "Choose action:\n";
            std::cout << "1) Change function\n";
            std::cout << "2) Change area\n";
            std::cout << "3) Change stop criterion\n";
            std::cout << "4) Change optimization method\n";
            std::cout << "5) Change starting point\n";
            std::cout << "6) Optimize function\n";
            std::cout << "7) Turn off programm\n";
            while (true) {
                int choice;
                if (std::cin >> choice) {
                    make_choice(choice);
                    break;
                } else {
                    std::cout << "Incorrect input. Enter the number 1-7.";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            
        }
        

    }

private:
    void init_params() {
        make_choice(FUNC);
        make_choice(AREA);
        make_choice(CRITERION);
        make_choice(METHOD);
        make_choice(START_POINT);
        make_choice(START_OPTIM);
    }

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
        switch (choice-1)
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
            std::cout << "Incorrect input. Enter the nuber 1-7.\n";
            break;
        }
    }

    void starting_point_menu() {
        bool end = false;
        while (!end) {
            end = true;
            std::cout << "Enter starting point:\n";
            std::cout << "Example: 3.5 -1 0.1\n";
            curr_starting_point.clear();
            curr_starting_point.resize(curr_func->get_dim());
            for (size_t i = 0; i < curr_func->get_dim(); ++i) {
                if (!(std::cin >> curr_starting_point[i])) {
                    std::cout << "Incorrect input\n";
                    end = false;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
            }
        }
    }

    void start_optim_menu() {
        curr_method->set_starting_point(curr_starting_point);
        curr_method->optimize(*curr_area, *curr_func, *curr_criterion);
        BestParams best_params = curr_method->get_best_params();
        std::cout << "Minimum point: ";
        for (size_t i = 0; i < best_params.minimum_point.size(); ++i) {
            std::cout << best_params.minimum_point[i] << " ";
        }
        std::cout << "\nMinimum value: " << best_params.minimum_value << "\n";
        std::cout << "Iteration number: " << best_params.iter_number << "\n";

    }

    void validate_int_input(int& choice, int max_int) {
        while (true) {
            if (!(std::cin >> choice) || choice < 1 || choice > max_int) {
                std::cout << "Incorrect input. Enter the number 1-" << max_int <<".\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } 
            else {
                break;
            }
        }
    }

    void method_menu() {
        std::cout << "Choose optimization method:\n";
        std::cout << "1) Conjugate gradient method.\n";
        std::cout << "2) Random search.\n";
        int choice;
        validate_int_input(choice, 2);
        switch (choice-1)
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
            std::cout << "Enter the number (1-2)\n";
            break;
        }
        
    }

    void criterion_menu() {
        std::cout << "Choose stop criterion:\n";
        std::cout << "1) Iteration criterion\n";
        std::cout << "2) Epsilon criterion\n";
        int choice;
        validate_int_input(choice, 2);

        switch (choice-1)
        {
        case ITER:
            size_t max_iter;
            std::cout << "Enter max iteration number:\n";
            std::cin >> max_iter;
            curr_criterion = std::make_shared<IterationCriterion>(max_iter);
            break;

        case EPS:
            double eps;
            std::cout << "Enter epsilon:\n";
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
        std::cout << "Choose function from the list:\n";
        for (size_t i = 0; i < functions.size(); ++i) {
            std::cout << i+1 << ") " << functions[i]->get_name() << "\n";
        }
        int choice;
        validate_int_input(choice, functions.size());
        set_func(choice);
    }

    void area_menu() {
        std::cout << "Set area bounds:\n";
        std::cout << "Function dim " << curr_func->get_dim() << "\n";
        std::cout << "Enter rectangle bounds:\n";
        
        std::vector<std::pair<double, double>> bounds;
        bool correct = false;
        while (!correct) {
            correct = true;
            bounds.clear();
            for (size_t i=0; i < curr_func->get_dim(); ++i) {
                double a, b;
                if (std::cin >> a >> b || a >= b) {
                    bounds.push_back({a, b});
                } else {
                    std::cout << "Incorrect input. Enter 2 numbers for each dimention.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    correct = false;
                    break;
                }
            }
        }
        curr_area = std::make_shared<Rectangle>(bounds);
    }
};

OptimMethodCLI::OptimMethodCLI() : running(true) {
    functions.push_back(std::make_shared<Func1>());
    functions.push_back(std::make_shared<Func2>());
    functions.push_back(std::make_shared<Func3>());

    curr_func = functions[0];
}
