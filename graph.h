#ifndef GRAPH
#define GRAPH


#include <vector>

#include "functional.h"


class Graph
{
public:
    Graph(Function func, int numberOfSplits=256, double OXRange=20);
    
    double getOXRange();
    void setOXRange(double newOXRange);
    std::vector<double> getxValues();
    std::vector<double> getyValues();
    void calculate();

private:
    Function func;
    int numberOfSplits;
    double OXRange;
    std::vector<double> xValues;
    std::vector<double> yValues;
};


#endif