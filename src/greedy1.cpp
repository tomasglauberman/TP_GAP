#include "greedy1.h"

GreedySolver1 :: GreedySolver1(GapInstance &instance, GapSolution &solution){
    this->_instance = instance;
    this->_solution = solution;
    this->_obetive_value = 0;
    this->_remaining_capacity = vector<int>(this->_instance.getM());
    for (int i = 0; i < this->_instance.getM(); i++)
    {
        this->_remaining_capacity[i] = this->_instance.capacities[i];
    }  
};

void GreedySolver1 :: solve(){
    for (int j = 0; j < this->_instance.getN(); j++)
    {
        int min_store = -1;
        float min_dist = 100000;
        for (int i = 0; i < this->_instance.getM(); i++)
        {
            if((this->_instance.costs[i][j] < min_dist) && (this->_remaining_capacity[i] >= this->_instance.supply[i][j])){
                min_store = i;
                min_dist = this->_instance.costs[i][j];
            }
        }
        if(min_store == -1){
            
        }
          
    }
    
} 




