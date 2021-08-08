#include "function.h"


Graph::Graph(Function func, int numberOfSplits=256, double OXRange=20)
    : func(func), numberOfSplits(numberOfSplits), OXRange(OXRange)
{
}


double Graph::getOXRange() { return this->OXRange; }
void Graph::setOXRange(double newOXRange) { this->OXRange = newOXRange; }
std::vector<double> Graph::getxValues() { return this->xValues; }
std::vector<double> Graph::getyValues() { return this->yValues; }


void Graph::calculate() {
    this->xValues.clear()
    this->yValues.clear()

    double delta = this->OXRange*2 / static_cast<double>(this->numberOfSplits - 1);

    for (int i = 0, double arg = -this->OXRange; arg <= this->OXRange; arg += delta, i++) {
        this->xValues.push_back(this->func.calculate_x(arg));
        this->yValues.push_back(this->func.calculate_y(arg));
    }
}