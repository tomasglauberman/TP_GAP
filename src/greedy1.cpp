#include "greedy1.h"

GreedySolver1::GreedySolver1(){}

GreedySolver1 :: GreedySolver1(GapInstance instance){
    this->_instance = instance;
    this->_solution = GapSolution(this->_instance);
};

GreedySolver1::~GreedySolver1(){}

void GreedySolver1::solve(){

    auto start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < this->_instance.getN(); j++)
    {
        
        int min_store = this->_instance.getM()-1;
        float min_cost = 100000;

        for (int i = 0; i < this->_instance.getM()-1; i++)
        {
            if((this->_instance.getCost(i, j) < min_cost) && 
               (this->_solution.getRemainingCapacity(i) >= this->_instance.getDemand(i,j))) {
                min_store = i;
                min_cost = this->_instance.getCost(i, j);
            }
        }

        if(!(min_store == this->_instance.getM()-1)){   
            this->_solution.assign(min_store, j);
        }
          
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));

}

GapSolution GreedySolver1::getSolution(){
    return this->_solution;
}
