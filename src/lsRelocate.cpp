#include "lsRelocate.h"
#include "greedy1.h"
#include <chrono>

LocalSearchRelocate::LocalSearchRelocate(){}


LocalSearchRelocate :: LocalSearchRelocate(GapInstance &instance){
    this->_instance = instance;
    this->_objective_value = 0;
    this->_remaining_capacity = vector<int>(this->_instance.getM());

    for (int i = 0; i < this->_instance.getM(); i++)
    {
        this->_remaining_capacity[i] = this->_instance.getCapacity(i);
    }  
};

LocalSearchRelocate::~LocalSearchRelocate(){}

void LocalSearchRelocate :: solve(GapSolution &solution){

    this->_solution = solution;
    this->_objective_value = solution.getObjVal();
    bool search = true;

    while(search) {
        vector<int> vr = getBestRelocate();
        float mejora = vr[0];
        int change_seller = vr[1];
        int initial_store = vr[2];
        int final_store = vr[3];

        cout<< mejora << " " << change_seller << " " << initial_store << " " << final_store << endl;

        // if (mejora < 0) {
        //     this->_solution.unassign(initial_store, change_seller);
        //     // if(!this->_solution.isSellerAssign(change_seller)) {
        //     //     this->_solution.assign(final_store, change_seller);
        //     //     // La mejora es negatviva 
        //     //     this->_objective_value += mejora;
        //     // }
        // } else {
        //     search = false;
        // }

    }

    auto start = std::chrono::high_resolution_clock::now();

    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -start).count();
    this->_solution.setTime(double(duration));

    this->_solution.setObjVal(this->_objective_value);

    std::cout << this->_solution.getObjVal() << std::endl;

    // std::cout << this->_solution << std::endl;

    for(int i = 0; i<this->_instance.getM(); i++){
        std::cout << "Store " << i << " remaining capacity: " << this->_remaining_capacity[i] << std::endl;
    }

    std::cout << this->_solution.checkFeasibility(this->_instance) << std::endl;
} 

GapSolution LocalSearchRelocate::getSolution(){
    return this->_solution;
}

vector<int> LocalSearchRelocate::getBestRelocate() {
    // Dada la solución actual, devuelve la mejor solucion de su vecindario
    // vr = [mejora(en negativo F-I), vendedor a cambiar, depo_inicial, depo_final]

    vector<int> vr = {0, 0, 0, 0};

    for(int j=0; j < this->_instance.getN(); j++) {
        float dist_assigned = this->_instance.getCost(this->_solution.getStoreAssigned(j), j);
        for(int i=0; i < this->_instance.getM(); i++) {
            if (dist_assigned > this->_instance.getCost(i, j)) {
                if (this->_remaining_capacity[i] >= this->_instance.getSupply(i, j)) {
                    vr[0] = this->_instance.getCost(i, j) - dist_assigned;
                    vr[1] = j;
                    vr[2] = this->_solution.getStoreAssigned(j);
                    vr[3] = i;
                }
            }
        }
    }

    return vr;
}

