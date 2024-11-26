#include <vector>

class Criterion {
public:
    virtual bool check(std::vector<double> trajectory) const = 0;
};

class IterationCriterion : public Criterion {
private:
    size_t max_iter;
public:
    IterationCriterion(size_t max_iter) : max_iter(max_iter) {}

    bool check(std::vector<double> trajectory) const override {
        if (trajectory.size() >= max_iter) return true;
        return false;
    }
};
