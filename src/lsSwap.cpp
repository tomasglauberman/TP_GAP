#include "lsSwap.h"
#include <tuple>
#include <chrono>


//Heuristica random pero factible, la usamos como solucion incial
//para ver la mejora de los operadores de busqueda local

LocalSearchSwap::LocalSearchSwap(){}

LocalSearchSwap::~LocalSearchSwap(){}

LocalSearchSwap::LocalSearchSwap(GapInstance instance, InitialSolution initialSolution){
    this->_instance = instance;
    if (initialSolution == InitialSolution::RANDOM){
        Random random = Random(instance);
        random.solve();
        this->_solution = random.getSolution();
    }
    else if (initialSolution == InitialSolution::GREEDY1){
        GreedySolver1 greedySolver1 = GreedySolver1(instance);    
        greedySolver1.solve();
        this->_solution = greedySolver1.getSolution();
    }
    else if (initialSolution == InitialSolution::GREEDY2){
        GreedySolver2 greedySolver2 = GreedySolver2(instance);
        greedySolver2.solve();
        this->_solution = greedySolver2.getSolution();
    }
    else if (initialSolution == InitialSolution::GENETIC) {
        GeneticAlgorithmSolver genetic = GeneticAlgorithmSolver(instance, 100, 100, 15);
        genetic.solve();
        this->_solution = genetic.getSolution();
    }

}

void LocalSearchSwap::solve(){
    auto start = std::chrono::high_resolution_clock::now();
    bool search = true;
    while(search){
        tuple<int, int> vr = getBestSwap();
        int j1 = std::get<0>(vr);
        int j2 = std::get<1>(vr);
        int storej1 = this->_solution.getStoreAssigned(j1);
        int storej2 = this->_solution.getStoreAssigned(j2);

        if(j1 == -1 || j2 == -1){
            //No hay swaps posibles
            search = false;
        }
        else{
            //Tengo que verificar que los sellers no esten desasignados/asignados al fantasma
            //antes de desasignarlos
            if(this->_solution.isSellerAssign(j1)) {
                this->_solution.unassign(storej1, j1);
            }
            if (this->_solution.isSellerAssign(j2)) {
                this->_solution.unassign(storej2, j2);
            }
            
            //Tengo que verificar que los stores no sean el fantasma para poder asignar
            if (storej1 != this->_instance.getM()-1){
                this->_solution.assign(storej1, j2);
            }
            if (storej2 != this->_instance.getM()-1)
            {
                this->_solution.assign(storej2, j1);
            }

        }
       
    }
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));
}


//GetBestSwap no devuelve nunca 2 vendedores sin asignar
//Devuelve un swap factible

tuple<int, int> LocalSearchSwap::getBestSwap(){
    float mejora = 10000;
    tuple<int, int> vr = std::make_tuple(-1,-1);

    for(int j1=0; j1<this->_instance.getN(); j1++) {
        for (int j2 = j1+1; j2 < this->_instance.getN(); j2++)
        {
            int store_j1 = this->_solution.getStoreAssigned(j1);
            int store_j2 = this->_solution.getStoreAssigned(j2);

            float current_cost = this->_instance.getCost(store_j1, j1) + this->_instance.getCost(store_j2, j2);
            float new_cost = this->_instance.getCost(store_j1, j2) + this->_instance.getCost(store_j2, j1);

            int cap_rem_store_j1 = this->_solution.getRemainingCapacity(store_j1) + this->_instance.getDemand(store_j1, j1) - this->_instance.getDemand(store_j1,j2);
            int cap_rem_store_j2 = this->_solution.getRemainingCapacity(store_j2) + this->_instance.getDemand(store_j2, j2) - this->_instance.getDemand(store_j2,j1);

            if(new_cost < current_cost && cap_rem_store_j1 >= 0 && cap_rem_store_j2 >= 0){
                if(new_cost - current_cost < mejora){
                    mejora = new_cost - current_cost;
                    vr = std::make_tuple(j1,j2);
                }
            }
        } 
    }
 
    return vr;
}

GapSolution LocalSearchSwap::getSolution(){
    return this->_solution;
}

void LocalSearchSwap::setSolution(GapSolution solution){
    this->_solution = solution;
}