#ifndef GREEDY_SOLVER_2_H
#define GREEDY_SOLVER_2_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"

class GreedySolver2{
    public:
    GreedySolver2();
    GreedySolver2(GapInstance instance);
    ~GreedySolver2();
    void solve();
    GapSolution getSolution();


    private:
    GapInstance _instance;
    GapSolution _solution;
};

#endif