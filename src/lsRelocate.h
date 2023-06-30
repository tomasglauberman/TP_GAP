#ifndef LS_RELOCATE_H
#define LS_RELOCATE_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"
#include <tuple>

class LocalSearchRelocate{
    public:
    LocalSearchRelocate();
    LocalSearchRelocate(GapInstance &instance);
    ~LocalSearchRelocate();
    void solve(GapSolution &solution);
    GapSolution getSolution();
    tuple<float, int, int, int> getBestRelocate();


    private:
    GapInstance _instance;
    GapSolution _solution;
};

#endif