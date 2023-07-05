#ifndef LS_RELOCATE_H
#define LS_RELOCATE_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "random.h"
#include <tuple>

class LocalSearchRelocate{
    public:
    enum InitialSolution {GREEDY1, GREEDY2, RANDOM};

    LocalSearchRelocate();
    LocalSearchRelocate(GapInstance instance, InitialSolution initialSolution);
    ~LocalSearchRelocate();
    void solve();
    GapSolution getSolution();
    tuple<float, int, int, int> getBestRelocate();


    private:
    GapInstance _instance;
    GapSolution _solution;
};

#endif