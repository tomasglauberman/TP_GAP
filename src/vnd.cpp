#include "vnd.h"
#include <chrono>


VND::VND(){}

VND::VND(GapInstance instance, InitialSolution initialSolution, FirstNeighborhood firstNeighborhood){
    this->_instance = instance;
    this->_firstNeighborhood = firstNeighborhood;

    if(initialSolution == InitialSolution::GREEDY1) {
        GreedySolver1 greedySolver1 = GreedySolver1(instance);    
        greedySolver1.solve();
        this->_solution = greedySolver1.getSolution();
    }
    else if(initialSolution == InitialSolution::GREEDY2) {
        GreedySolver2 greedySolver2 = GreedySolver2(instance);
        greedySolver2.solve();
        this->_solution = greedySolver2.getSolution();
    } 
    else if(initialSolution == InitialSolution::RANDOM) {
        Random random = Random(instance);
        random.solve();
        this->_solution = random.getSolution();
    }   
    else if(initialSolution == InitialSolution::GENETIC) {
        GeneticAlgorithmSolver genetic = GeneticAlgorithmSolver(instance, 100, 100);
        genetic.solve();
        this->_solution = genetic.getSolution();
    } 
};

VND::~VND(){};

void VND::solve() { 

    auto start = std::chrono::high_resolution_clock::now();
    bool search = true;

    LocalSearchSwap lsSwap = LocalSearchSwap(this->_instance, LocalSearchSwap::InitialSolution::CUSTOM);
    LocalSearchRelocate lsRelocate = LocalSearchRelocate(this->_instance, LocalSearchRelocate::InitialSolution::CUSTOM);

    if(this->_firstNeighborhood == FirstNeighborhood::SWAP) {
        bool search = true;
        while(search) {

            lsSwap.setSolution(this->_solution);
            lsSwap.solve();

            lsRelocate.setSolution(lsSwap.getSolution());
            lsRelocate.solve();

            if (lsRelocate.getSolution().getObjVal() >= lsSwap.getSolution().getObjVal()) {
                search = false;
            }
            this->_solution = lsRelocate.getSolution();
        }

    } else if(this->_firstNeighborhood == FirstNeighborhood::RELOCATE) {
        bool search = true;
        while(search) {

            lsRelocate.setSolution(this->_solution);
            lsRelocate.solve();

            lsSwap.setSolution(lsRelocate.getSolution());
            lsSwap.solve();

            if (lsSwap.getSolution().getObjVal() >= lsRelocate.getSolution().getObjVal()) {
                search = false;
            }
            this->_solution = lsSwap.getSolution();
        }

    }

    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));


}

GapSolution VND::getSolution() {
    return this->_solution;
};
