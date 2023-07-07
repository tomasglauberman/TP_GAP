#ifndef GRASP_1_H
#define GRASP_1_H

#include<vector>
#include<string>
#include<iostream>
#include <random>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"
#include "vnd.h"

class GRASP{
    public:
    GRASP();
    GRASP(GapInstance instance);   
    ~GRASP();
    void solve(int iterations);
    GapSolution getSolution();


    private:
    GapInstance _instance;
    GapSolution _solution;
    GapSolution _generateSolution(int seed);
};

#endif