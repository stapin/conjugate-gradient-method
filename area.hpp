#include <vector>
/*
    Хранит область.
*/
class Area
{
private:
    
public:
    Area();

    bool is_out_of_bounds(std::vector<double> x);
    // Или сделать расстояние от точки до множества

    ~Area();
};

class Interval : public Area {
private:
    double a;
    double b;
public:
    Interval(double a, double b) a(a), b(b) {};

}

