#ifndef LS_SWAP_H
#define LS_SWAP_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "random.h"
#include "genAlg.h"



class LocalSearchSwap{
    public:
    enum InitialSolution {RANDOM, GREEDY1, GREEDY2, CUSTOM, GENETIC};

    LocalSearchSwap();
    LocalSearchSwap(GapInstance instance, InitialSolution initialSolution);
    ~LocalSearchSwap();
    void solve();
    tuple<int,int> getBestSwap();
    void setSolution(GapSolution solution);
    GapSolution getSolution();

    
    private:
    GapInstance _instance;
    GapSolution _solution;
};


#endif