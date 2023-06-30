#include "greedy1.h"
#include <chrono>

GreedySolver1::GreedySolver1(){}

GreedySolver1 :: GreedySolver1(GapInstance &instance){
    this->_instance = instance;
    this->_solution = GapSolution(this->_instance);
};

GreedySolver1::~GreedySolver1(){}

void GreedySolver1 :: solve(){

    auto start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < this->_instance.getN(); j++)
    {
        
        int min_store = -1;
        float min_dist = 100000;
        for (int i = 0; i < this->_instance.getM(); i++)
        {
            if((this->_instance.getCost(i, j) < min_dist) && (this->_solution.getRemainingCapacity(i) >= this->_instance.getSupply(i,j))){
                min_store = i;
                min_dist = this->_instance.getCost(i, j);
            }
        }
        if(!(min_store == -1)){   
            this->_solution.assign(min_store, j);
        }
          
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));

    // std::cout << this->_solution.getObjVal() << std::endl;

    // for(int i = 0; i<this->_instance.getM(); i++){
    //     std::cout << "Store " << i << " remaining capacity: " << this->_remaining_capacity[i] << std::endl;
    // }

    // std::cout << this->_solution.checkFeasibility(this->_instance) << std::endl;
} 

GapSolution GreedySolver1::getSolution(){
    return this->_solution;
}
