#include "optim_method_cli.hpp"

OptimMethodCLI::OptimMethodCLI() : running(true) {
    functions.push_back(std::make_shared<Func1>());
    functions.push_back(std::make_shared<Func2>());
    functions.push_back(std::make_shared<Func3>());

    curr_func = functions[0];
}

void OptimMethodCLI::start() {
    init_params();
    while (running)
    {
        print_current_params();
        print_action_selection();
        while (true) {
            try {
                int choice;
                if (std::cin >> choice) {
                    make_choice(choice);
                    break;
                } else {
                    throw std::invalid_argument("Incorrect input. Enter the number 1-7.");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
        } 
    }
}

void OptimMethodCLI::print_current_params() {
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
}

void OptimMethodCLI::print_action_selection() {
    std::cout << "Choose action:\n";
    std::cout << "1) Change function\n";
    std::cout << "2) Change area\n";
    std::cout << "3) Change stop criterion\n";
    std::cout << "4) Change optimization method\n";
    std::cout << "5) Change starting point\n";
    std::cout << "6) Optimize function\n";
    std::cout << "7) Turn off programm\n";
}

void OptimMethodCLI::init_params() {
    make_choice(EMenuItem::FUNC);
    make_choice(EMenuItem::AREA);
    make_choice(EMenuItem::CRITERION);
    make_choice(EMenuItem::METHOD);
    make_choice(EMenuItem::START_POINT);
    make_choice(EMenuItem::START_OPTIM);
}

void OptimMethodCLI::print_stdvec(const std::vector<double>& vec) {
    for (auto& el : vec) {
        std::cout << el << " ";
    }
}

void OptimMethodCLI::print_area() {
    for (auto& el : curr_area->get_bounding_box()) {
        std::cout << "[" << el.first << " " << el.second << "]\n";
    }
}

void OptimMethodCLI::make_choice(int choice) {
    
    switch (choice)
    {
    case EMenuItem::FUNC:
        func_menu();
        break;
    case EMenuItem::AREA:
        area_menu();
        break;
    case EMenuItem::CRITERION:
        criterion_menu();
        break;
    case EMenuItem::METHOD:
        method_menu();
        break;
    case EMenuItem::START_POINT:
        starting_point_menu();
        break;
    case EMenuItem::START_OPTIM:
        start_optim_menu();
        break;
    case EMenuItem::EXIT:
        running = false;
        break;
    default:
        throw std::invalid_argument("Incorrect input. Enter the number 1-7.\n");
        break;
    }
}

void OptimMethodCLI::starting_point_menu() {
    bool end = false;
    while (!end) {
        end = true;
        std::cout << "Enter starting point:\n";
        std::cout << "Example: 3.5 -1 0.1\n";
        curr_starting_point.clear();
        curr_starting_point.resize(curr_func->get_dim());
        std::vector<std::pair<double, double>> bounds = curr_area->get_bounding_box();
        for (size_t i = 0; i < curr_func->get_dim(); ++i) {
            try {
                if (std::cin >> curr_starting_point[i]) {
                    if (curr_starting_point[i] > bounds[i].second ||
                        curr_starting_point[i] < bounds[i].first) {
                            throw std::invalid_argument("Point out of area bounds.");
                        }
                } 
                else {
                    throw std::invalid_argument("Incorrect input");
                }
                
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                end = false;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            
        }
    }
}

void OptimMethodCLI::start_optim_menu() {
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

void OptimMethodCLI::validate_uint_input(int& choice, int max_int) {
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

void OptimMethodCLI::method_menu() {
    std::cout << "Choose optimization method:\n";
    std::cout << "1) Conjugate gradient method.\n";
    std::cout << "2) Random search.\n";
    int choice;
    validate_uint_input(choice, 2);
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
        throw "Enter the number (1-2) for optimization method.";
        break;
    }   
}

void OptimMethodCLI::criterion_menu() {
    std::cout << "Choose stop criterion:\n";
    std::cout << "1) Iteration criterion\n";
    std::cout << "2) Epsilon criterion\n";
    int choice;
    validate_uint_input(choice, 2);

    switch (choice)
    {
    case ITER:
        size_t max_iter;
        std::cout << "Enter max iteration number:\n";
        while (true) {
            if (std::cin >> max_iter) {
                break;
            } else {
                std::cerr << "Enter the integer number > 0\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        curr_criterion = std::make_shared<IterationCriterion>(max_iter);
        break;

    case EPS:
        double eps;
        std::cout << "Enter epsilon:\n";
        while (true) {
            if (std::cin >> eps && eps > 0) {
                break;
            } else {
                std::cerr << "Enter the double number > 0\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        curr_criterion = std::make_shared<EpsilonCriterion>(eps);
        break;

    default:
        break;
    }
}

void OptimMethodCLI::set_func(int choice) {
    curr_func = functions[choice-1];
}

void OptimMethodCLI::func_menu() {
    std::cout << "Choose function from the list:\n";
    for (size_t i = 0; i < functions.size(); ++i) {
        std::cout << i+1 << ") " << functions[i]->get_name() << "\n";
    }
    int choice;
    validate_uint_input(choice, functions.size());
    set_func(choice);
}

void OptimMethodCLI::area_menu() {
    std::cout << "Set area bounds:\n";
    std::cout << "Function dim " << curr_func->get_dim() << "\n";
    std::cout << "Enter rectangle bounds:\n";
    
    std::vector<std::pair<double, double>> bounds;
    bool correct = false;
    while (!correct) {
        correct = true;
        bounds.clear();
        for (size_t i=0; i < curr_func->get_dim(); ++i) {
            
            try {
                double a, b;
                if (std::cin >> a) {
                } else {
                    throw std::invalid_argument("Incorrect input. Enter 2 numbers for each dimention.");
                }

                if (std::cin >> b) {
                    if (b > a) {
                        bounds.push_back({a, b});
                    } else {
                        throw std::invalid_argument("Bounds have negative or zero size. Enter two numbers a, b (b > a).");
                    }
                } else {
                    throw std::invalid_argument("Incorrect input. Enter two numbers for each dimention");
                }
                
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                correct = false;
                break;
            }
        }
        curr_area = std::make_shared<Rectangle>(bounds);
    }
}
