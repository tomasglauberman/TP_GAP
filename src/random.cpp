#include "random.h"
#include <chrono>
#include "gap_solution.h"

Random::Random(){}

Random :: Random(GapInstance instance){
    this->_instance = instance;
    this->_solution = GapSolution(this->_instance);
};

Random::~Random(){}

void Random::solve(){

    auto start = std::chrono::high_resolution_clock::now();
    //VER TEMA DE SEMILLA. SI NO PONGO HAY CASOS EN LOS QUE EL RELOCATE EMPEORA LA SOLUCION. RARO!!
    srand(1);
    for (int j = 0; j < this->_instance.getN(); j++)
    {
        //En pero caso hago 20 busquedas random de store para cada vendedor
        //En caso de que no encuentre ninguno factible, lo dejo desasignado
        for(int attempt = 0; attempt <=20; attempt++){
            int random_store = rand() % (this->_instance.getM()-1);
            if (this->_solution.getRemainingCapacity(random_store) >= this->_instance.getDemand(random_store,j)){
                this->_solution.assign(random_store, j);
                break;
            }
        }
          
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));

}

GapSolution Random::getSolution(){
    return this->_solution;
}