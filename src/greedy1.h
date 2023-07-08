#ifndef GREEDY_SOLVER_1_H
#define GREEDY_SOLVER_1_H

#include<vector>
#include<string>
#include<iostream>
#include <chrono>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"


class GreedySolver1{
    public:
    GreedySolver1();
    GreedySolver1(GapInstance instance);   
    ~GreedySolver1();
    void solve();
    GapSolution getSolution();


    private:
    GapInstance _instance;
    GapSolution _solution;
};

#endif