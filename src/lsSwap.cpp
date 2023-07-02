#include "lsSwap.h"
#include <tuple>
#include <chrono>


LocalSearchSwap::LocalSearchSwap(){}

LocalSearchSwap::~LocalSearchSwap(){}

LocalSearchSwap::LocalSearchSwap(GapInstance instance, InitialSolution initialSolution){
    this->_instance = instance;
    if (initialSolution == InitialSolution::RANDOM){
        this->_solution = GapSolution(instance);
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
}

void LocalSearchSwap::solve(){

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

            if(this->_solution.isSellerAssign(j1)) {
                this->_solution.unassign(storej1, j1);
            }
            if (this->_solution.isSellerAssign(j2)) {
                this->_solution.unassign(storej2, j2);
            }

            this->_solution.assign(storej1, j2);
            this->_solution.assign(storej2, j1);
        }
       
    }
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


// void something(){
//        for(int i = 0; i < this->_instance.getN();i++){
//         int store_i = this->_solution.getStoreAssigned(i);
//         for (int j = i ;  j <  this->_instance.getN(); j++){
//             int store_j = this->_solution.getStoreAssigned(j);
//             if(store_i!=-1 && store_j!=-1){
//                 float costo_inicial =  this->_instance.getCost(store_i, i)+ this->_instance.getCost(store_j,j);
//                 float costo_swap = this->_instance.getCost(store_i, j)+ this->_instance.getCost(store_j,i);
//                 int cap_rem_store_i = this->_solution.getRemainingCapacity(store_i) + this->_instance.getDemand(store_i, i) - this->_instance.getDemand(store_i,j);
//                 int cap_rem_store_j = this->_solution.getRemainingCapacity(store_j) + this->_instance.getDemand(store_j, j) - this->_instance.getDemand(store_j,i);
//                 if(costo_swap < costo_inicial && cap_rem_store_i >=0 && cap_rem_store_j>=0){
//                     if(costo_swap - costo_inicial < mejora){
//                         mejora = costo_swap - costo_inicial;
//                         vr = std::make_tuple(i,j);
//                     }
//                 }
//             }
//             else if( store_i == -1 && store_j !=-1){
//                 float costo_inicial =  this->_instance.getDMax()*3+ this->_instance.getCost(store_j,j);
//                 float costo_swap = this->_instance.getDMax()*3+ this->_instance.getCost(store_j,i);
//                 int cap_rem_store_j = this->_solution.getRemainingCapacity(store_j) + this->_instance.getDemand(store_j, j) - this->_instance.getDemand(store_j,i);
//                 if(costo_swap < costo_inicial  && cap_rem_store_j>=0){
//                     if(costo_swap - costo_inicial < mejora){
//                         mejora = costo_swap - costo_inicial;
//                         vr = std::make_tuple(i,j);
//                     }
//                 }
//             }
//             else if(store_i != -1 && store_j == -1){
//                 float costo_inicial =  this->_instance.getCost(store_i, i)+ this->_instance.getDMax()*3;
//                 float costo_swap = this->_instance.getCost(store_i, j)+ this->_instance.getDMax()*3;
//                 int cap_rem_store_i = this->_solution.getRemainingCapacity(store_i) + this->_instance.getDemand(store_i, i) - this->_instance.getDemand(store_i,j);
//                 if(costo_swap < costo_inicial && cap_rem_store_i >=0){
//                     if(costo_swap - costo_inicial < mejora){
//                         mejora = costo_swap - costo_inicial;
//                         vr = std::make_tuple(i,j);
//                     }
//                 }
//             }

//         }
//     }
// }