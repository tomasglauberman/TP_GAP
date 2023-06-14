#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "gap_instance.h"
#include "gap_solution.h"

class GreedySolver1{
    public:
    GreedySolver1(GapInstance &instance, GapSolution &solution);
    void solve();
    float getObjetiveValue();
    int getRemainingCapacity(int store);


    private:
    float _obetive_value;
    vector<int> _remaining_capacity;
    GapInstance _instance;
    GapSolution _solution;
};