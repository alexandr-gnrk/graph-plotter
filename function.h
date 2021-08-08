#ifndef FUNCTION
#define FUNCTION


#include <functional>


class Function
{
public:
    Function(std::function<double (double)> fx, std::function<double (double)> fy, bool is_polar=false);
    
    double calculate_x(double arg);
    double calculate_y(double arg);

private:
    std::function<double (double)> fx;
    std::function<double (double)> fy;
    bool is_polar;
};


#endif