#include "lsRelocate.h"
#include <chrono>

LocalSearchRelocate::LocalSearchRelocate(){}

LocalSearchRelocate :: LocalSearchRelocate(GapInstance &instance){
    this->_instance = instance;
};

LocalSearchRelocate::~LocalSearchRelocate(){}

void LocalSearchRelocate :: solve(GapSolution &solution){
    this->_solution = solution;
    
    bool search = true;

    while(search) {
        tuple<float, int, int, int>  vr = getBestRelocate();
        float mejora = std::get<0>(vr);
        int change_seller = std::get<1>(vr);
        int initial_store = std::get<2>(vr);
        int final_store = std::get<3>(vr);

        //cout<< mejora << " " << change_seller << " " << initial_store << " " << final_store << endl;

        if (mejora < 0) {
            if(initial_store != -1){
                this->_solution.unassign(initial_store, change_seller);
            }
            if(!this->_solution.isSellerAssign(change_seller)) {
                this->_solution.assign(final_store, change_seller);
                // La mejora es negatviva
            }
        } 
        else {
            search = false;
        }

    }

    auto start = std::chrono::high_resolution_clock::now();

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
        float costo_inicial;
        if(this->_solution.getStoreAssigned(j) == -1){
            costo_inicial = this->_instance.getDMax()*3;
        }
        else{
            costo_inicial = this->_instance.getCost(this->_solution.getStoreAssigned(j), j);
        }
        for(int i=0; i < this->_instance.getM(); i++) {
            if (this->_instance.getCost(i, j) < costo_inicial && 
            this->_solution.getRemainingCapacity(i) >= this->_instance.getSupply(i, j)) {
                if(this->_instance.getCost(i, j)-costo_inicial < mejora){
                    vr = std::make_tuple(this->_instance.getCost(i, j) - costo_inicial, j, this->_solution.getStoreAssigned(j), i);
                    mejora = this->_instance.getCost(i, j) - costo_inicial;
                }
            }
        }
    }
    return vr;
}

