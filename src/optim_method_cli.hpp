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

    enum EMenuItem {
        FUNC = 1,
        AREA,
        CRITERION,
        METHOD,
        START_POINT,
        START_OPTIM,
        EXIT
    };

    enum EFunction {
        FUNC1 = 1,
        FUNC2,
        FUNC3,
        FUNC4
    };

    enum ECriterion {
        ITER = 1,
        EPS
    };

    enum EMethod {
        CONJ = 1,
        RANDOM
    };
    
public:
    OptimMethodCLI();
    ~OptimMethodCLI() = default;

    /**
     * @brief Starts CLI for function optimization.
     * 
     */
    void start();

private:
    void init_params();

    void print_current_params();

    void print_action_selection();

    void print_stdvec(const std::vector<double>& vec);

    void print_area();

    void make_choice(int choice);

    void starting_point_menu();

    void start_optim_menu();

    void validate_uint_input(int& choice, int max_int);

    void method_menu();

    void criterion_menu();


    void set_func(int choice);

    void func_menu();

    void area_menu();
};


