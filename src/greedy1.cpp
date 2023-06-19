#include "greedy1.h"
#include <chrono>

GreedySolver1 :: GreedySolver1(GapInstance &instance, GapSolution &solution){
    this->_instance = instance;
    this->_solution = solution;
    this->_obetive_value = 0;
    this->_remaining_capacity = vector<int>(this->_instance.getM());

    for (int i = 0; i < this->_instance.getM(); i++)
    {
        this->_remaining_capacity[i] = this->_instance.getCapacity(i);
    }  
};

void GreedySolver1 :: solve(){

    auto start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < this->_instance.getN(); j++)
    {
        
        int min_store = -1;
        float min_dist = 100000;
        for (int i = 0; i < this->_instance.getM(); i++)
        {
            if((this->_instance.getCost(i, j) < min_dist) && (this->_remaining_capacity[i] >= this->_instance.getSupply(i,j))){
                min_store = i;
                min_dist = this->_instance.getCost(i, j);
            }
        }
        if(min_store == -1){
            this->_solution.assign(-1, j);
            this->_obetive_value += this->_instance.getDMax() * 3;   
        } else {
            this->_solution.assign(min_store, j);
            this->_obetive_value += min_dist;
        }
          
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));

    this->_solution.setObjVal(this->_obetive_value);

} 




