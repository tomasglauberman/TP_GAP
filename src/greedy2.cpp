#include "greedy2.h"
#include <chrono>

GreedySolver2::GreedySolver2(){}

GreedySolver2 :: GreedySolver2(GapInstance instance){
    this->_instance = instance;
    this->_solution = GapSolution(this->_instance);
};

GreedySolver2::~GreedySolver2(){}

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
            for(int i=0; i<this->_instance.getM()-1; i++) {
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
        int min_store = this->_instance.getM()-1;
        float min_dist = 100000;
        for (int i = 0; i < this->_instance.getM()-1; i++)
        {
            if((this->_instance.getCost(i, sellers_sort[j]) < min_dist) && (this->_solution.getRemainingCapacity(i) >= this->_instance.getDemand(i,sellers_sort[j]))){
                min_store = i;
                min_dist = this->_instance.getCost(i, sellers_sort[j]);
            }
        }

        if(!(min_store == this->_instance.getM()-1)){  
            this->_solution.assign(min_store, sellers_sort[j]);
        }
          
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));
} 

GapSolution GreedySolver2::getSolution(){
    return this->_solution;
}
