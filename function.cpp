#include "function.h"


Function::Function(
    std::function<double (double)> fx, std::function<double (double)> fy, bool is_polar)
    : fx(fx), fy(fy), is_polar(is_polar)
{
}


double Function::calculate_x(double arg) {
    return this->fx(arg);
}


double Function::calculate_y(double arg) {
    return this->fy(arg);
}
