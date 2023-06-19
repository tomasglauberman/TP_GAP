#include "greedy2.h"
#include <chrono>

GreedySolver2::GreedySolver2(){}

GreedySolver2 :: GreedySolver2(GapInstance &instance){
    this->_instance = instance;
    this->_objective_value = 0;
    this->_remaining_capacity = vector<int>(this->_instance.getM());
    this->_solution = GapSolution(this->_instance);

    for (int i = 0; i < this->_instance.getM(); i++)
    {
        this->_remaining_capacity[i] = this->_instance.getCapacity(i);
    }  
};

void GreedySolver2::solve(){

    auto start = std::chrono::high_resolution_clock::now();

    // ORDERNARLOS POR COSTO MIN EN ALGUN VECTOR
    vector<int> sellers_sort = vector<int>(this->_instance.getN());
    vector<bool> min_found = vector<bool>(this->_instance.getN());

    // BUSCO N VECES EL MINIMO EN LA MATRIZ DE COSTO
    for(int ind=0; ind<this->_instance.getN(); ind++) {
        float min_dist = 100000;
        int min_seller = -1;
        for(int j=0; j<this->_instance.getN(); j++){
            for(int i=0; i<this->_instance.getM(); i++) {
                if(min_dist > this->_instance.getCost(i,j) && !min_found[j]){
                    min_dist = this->_instance.getCost(i,j);
                    min_seller = j;
                }
            }
        }
        sellers_sort[ind] = min_seller;
        min_found[min_seller] = true;
    }

    for (int j = 0; j < this->_instance.getN(); j++)
    {   
        int min_store = -1;
        float min_dist = 100000;
        for (int i = 0; i < this->_instance.getM(); i++)
        {
            if((this->_instance.getCost(i, sellers_sort[j]) < min_dist) && (this->_remaining_capacity[i] >= this->_instance.getSupply(i,sellers_sort[j]))){
                min_store = i;
                min_dist = this->_instance.getCost(i, sellers_sort[j]);
            }
        }
        if(min_store == -1){
            this->_objective_value += this->_instance.getDMax() * 3;   
        } else {
            this->_solution.assign(min_store, sellers_sort[j]);
            this->_objective_value += min_dist;
            this->_remaining_capacity[min_store] -= this->_instance.getSupply(min_store,sellers_sort[j]);
        }
          
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));

    this->_solution.setObjVal(this->_objective_value);

    std::cout << this->_solution.getObjVal() << std::endl;
    // std::cout << this->_solution << std::endl;

    for(int i = 0; i<this->_instance.getM(); i++){
        std::cout << "Store " << i << " remaining capacity: " << this->_remaining_capacity[i] << std::endl;
    }

    std::cout << this->_solution.checkFeasibility(this->_instance) << std::endl;
} 

GapSolution GreedySolver2::getSolution(){
    return this->_solution;
}
