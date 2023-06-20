#ifndef GREEDY_SOLVER_1_H
#define GREEDY_SOLVER_1_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"

class GreedySolver1{
    public:
    GreedySolver1();
    GreedySolver1(GapInstance &instance);
    void solve();
    float getObjetiveValue();
    int getRemainingCapacity(int store);
    GapSolution getSolution();


    private:
    float _objective_value;
    vector<int> _remaining_capacity;
    GapInstance _instance;
    GapSolution _solution;
};

#endif