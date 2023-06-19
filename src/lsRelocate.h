#ifndef LS_RELOCATE_H
#define LS_RELOCATE_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"

class LocalSearchRelocate{
    public:
    LocalSearchRelocate();
    LocalSearchRelocate(GapInstance &instance);
    void solve(GapSolution &solution);
    float getObjetiveValue();
    int getRemainingCapacity(int store);
    GapSolution getSolution();

    vector<int> getBestRelocate();


    private:
    float _objective_value;
    vector<int> _remaining_capacity;
    GapInstance _instance;
    GapSolution _solution;
};

#endif