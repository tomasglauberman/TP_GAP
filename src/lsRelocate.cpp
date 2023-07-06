#include "lsRelocate.h"
#include <chrono>


LocalSearchRelocate::LocalSearchRelocate(){}

LocalSearchRelocate :: LocalSearchRelocate(GapInstance instance, InitialSolution initialSolution){
    this->_instance = instance;

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
    else if (initialSolution == InitialSolution::GENETIC) {
        GeneticAlgorithmSolver genetic = GeneticAlgorithmSolver(instance, 100, 100);
        genetic.solve();
        this->_solution = genetic.getSolution();
    }

};

LocalSearchRelocate::~LocalSearchRelocate(){}

void LocalSearchRelocate::solve(){
    auto start = std::chrono::high_resolution_clock::now();
    bool search = true;

    while(search) {
        tuple<float, int, int, int>  vr = getBestRelocate();
        float mejora = std::get<0>(vr);
        int change_seller = std::get<1>(vr);
        int initial_store = std::get<2>(vr);
        int final_store = std::get<3>(vr);

        //cout<< mejora << " " << change_seller << " " << initial_store << " " << final_store << endl;

        if (mejora < 0) {
            if(this->_solution.isSellerAssign(change_seller)) {
                this->_solution.unassign(initial_store, change_seller);
            }
            this->_solution.assign(final_store, change_seller);
        } 
        else {
            search = false;
        }

    }


    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));

    //std::cout << this->_solution.getObjVal() << std::endl;

    // std::cout << this->_solution << std::endl;

    // for(int i = 0; i<this->_instance.getM(); i++){
    //     std::cout << "Store " << i << " remaining capacity: " << this->_remaining_capacity[i] << std::endl;
    // }

    //std::cout << this->_solution.checkFeasibility(this->_instance) << std::endl;
} 

GapSolution LocalSearchRelocate::getSolution(){
    return this->_solution;
}

tuple<float, int, int, int> LocalSearchRelocate::getBestRelocate() {
    // Dada la solución actual, devuelve la mejor solucion de su vecindario
    // vr = [mejora(en negativo F-I), vendedor a cambiar, depo_inicial, depo_final]
    tuple<float, int, int, int>  vr = std::make_tuple(0, 0, 0, 0);
    //Mejora en negativo
    float mejora = 0;
    for(int j=0; j < this->_instance.getN(); j++) {

        float costo_inicial = this->_instance.getCost(this->_solution.getStoreAssigned(j), j);

        for(int i=0; i < this->_instance.getM()-1; i++) {
            if (this->_instance.getCost(i, j) < costo_inicial && 
            this->_solution.getRemainingCapacity(i) >= this->_instance.getDemand(i, j)) {
                if(this->_instance.getCost(i, j)-costo_inicial < mejora){
                    vr = std::make_tuple(this->_instance.getCost(i, j) - costo_inicial, j, this->_solution.getStoreAssigned(j), i);
                    mejora = this->_instance.getCost(i, j) - costo_inicial;
                }
            }
        }
    }
    return vr;
}

void LocalSearchRelocate::setSolution(GapSolution solution){
    this->_solution = solution;
}