#include <vector>
#include <exception>
#include <iostream>

class VectorDouble : public std::vector<double> {
    using std::vector<double>::vector;
public:

    VectorDouble& operator+=(VectorDouble other);

    VectorDouble& operator-=(VectorDouble other);
    
};

VectorDouble operator+(VectorDouble v1, VectorDouble v2);

VectorDouble operator-(VectorDouble v);

VectorDouble operator-(VectorDouble v1, VectorDouble v2);

VectorDouble operator*(double a, VectorDouble other);

void print_vec(const VectorDouble& vec);