#ifndef RANDOM_H
#define RANDOM_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"

class Random{
    public:
    Random();
    Random(GapInstance instance);
    ~Random();
    void solve();
    GapSolution getSolution();


    private:
    GapInstance _instance;
    GapSolution _solution;
};

#endif