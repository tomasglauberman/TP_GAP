#include "GRASP.h"
#include <chrono>
#include <algorithm>

GRASP::GRASP(){}

GRASP :: GRASP(GapInstance instance){
    this->_instance = instance;
    this->_solution = GapSolution(this->_instance);
};

GRASP::~GRASP(){}

void GRASP::solve(int iterations){

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++)
    {
        GapSolution solution = this->_generateSolution(i);
        VND vnd = VND(this->_instance, VND::InitialSolution::CUSTOM, VND::FirstNeighborhood::RELOCATE);
        vnd.setSolution(this->_generateSolution((i+1)*15));
        vnd.solve();

        if (vnd.getSolution().getObjVal() < this->_solution.getObjVal()) {
            this->_solution = vnd.getSolution();
        }

        std::cout << "Iteration " << i+1 << " of " << iterations;
        std::cout << " Best solution: " << this->_solution.getObjVal() << std::endl;
    }

    
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));

}


GapSolution GRASP::_generateSolution(int seed) {

    std::mt19937 randGen2;
    randGen2.seed(seed);

    GapSolution solution = GapSolution(this->_instance);

    for (int j = 0; j < this->_instance.getN(); j++)
    {
        
        vector<pair<float, int>> costs_j = vector<pair<float, int>>(this->_instance.getM()-1);

        for (int i = 0; i < this->_instance.getM()-1; i++)
        {
            costs_j[i] = make_pair(this->_instance.getCost(i, j), i);
        }

        sort(costs_j.begin(), costs_j.end());

        // SELECCIONAR DENTRO DE LOS PRIMEROS 16% PERO
        // HAY QUE HACER FINE TUNING DE ESTE PARAMETRO
        int first_p = this->_instance.getM()/6;
        std::uniform_int_distribution<int> dist(0, first_p);
        
        for (int i = 0; i < 15; i++)
        {
            int p = dist(randGen2);
            int store = costs_j[p].second;
            if (solution.getRemainingCapacity(store) >= this->_instance.getDemand(store,j)) {
                solution.assign(store, j);
                break;
            }
        }
    }

    return solution;
}


GapSolution GRASP::getSolution(){
    return this->_solution;
}
