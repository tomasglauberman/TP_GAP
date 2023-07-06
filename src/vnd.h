#ifndef VND_H
#define VND_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "random.h"
#include "lsSwap.h"
#include "lsRelocate.h"
#include "genAlg.h"
#include <tuple>

class VND{
    public:
    enum InitialSolution {GREEDY1, GREEDY2, RANDOM, CUSTOM, GENETIC};
    enum FirstNeighborhood {RELOCATE, SWAP};

    VND();
    VND(GapInstance instance, InitialSolution initialSolution, FirstNeighborhood firstNeighborhood);
    ~VND();
    void solve();
    GapSolution getSolution();
    tuple<float, int, int, int> getBestRelocate();


    private:
    GapInstance _instance;
    GapSolution _solution;
    FirstNeighborhood _firstNeighborhood;
};



#endif