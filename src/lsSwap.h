#ifndef LS_SWAP_H
#define LS_SWAP_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"



class LocalSearchSwap{
    public:
    LocalSearchSwap();
    LocalSearchSwap(GapInstance &instance);
    ~LocalSearchSwap();
    void solve(GapSolution &solution);
    tuple<int,int> getBestSwap();
    GapSolution getSolution();

    
    private:
    GapInstance _instance;
    GapSolution _solution;
};


#endif