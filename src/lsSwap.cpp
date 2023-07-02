#include "lsSwap.h"
#include <tuple>
#include <chrono>


LocalSearchSwap::LocalSearchSwap(){}

LocalSearchSwap::~LocalSearchSwap(){}

LocalSearchSwap::LocalSearchSwap(GapInstance &instance){
    this->_instance = instance;
}

void LocalSearchSwap::solve(GapSolution &solution){
    this->_solution = solution;
    bool search = true;
    while(search){
        tuple<int, int> vr = getBestSwap(); 
        if(std::get<0>(vr) == -1 || std::get<1>(vr) == -1){
            //No hay swaps posibles
            search = false;
        }
        else{
            int store0 = this->_solution.getStoreAssigned(std::get<0>(vr));
            int store1 = this->_solution.getStoreAssigned(std::get<1>(vr));
            if(store0 != -1 && store1 != -1){
                this->_solution.unassign(store0,std::get<0>(vr));
                this->_solution.assign(store0, std::get<1>(vr));
                this->_solution.unassign(store1,std::get<1>(vr));
                this->_solution.assign(store1, std::get<0>(vr));
            }
            else if(store0 != -1 && store1 == -1){
                this->_solution.unassign(store0,std::get<0>(vr));
                this->_solution.assign(store0, std::get<1>(vr));
            }
            else if(store0 == -1 && store1 != -1){
                this->_solution.unassign(store1,std::get<1>(vr));
                this->_solution.assign(store1, std::get<0>(vr));
            }
        }
       
    }
}


//GetBestSwap no devuelve nunca 2 vendedores sin asignar
//Devuelve un swap factible

tuple<int, int> LocalSearchSwap::getBestSwap(){
    float mejora = 10000;
    tuple<int, int> vr = std::make_tuple(-1,-1);
    for(int i = 0; i < this->_instance.getN();i++){
        int store_i = this->_solution.getStoreAssigned(i);
        for (int j = i ;  j <  this->_instance.getN(); j++){
            int store_j = this->_solution.getStoreAssigned(j);
            if(store_i!=-1 && store_j!=-1){
                float costo_inicial =  this->_instance.getCost(store_i, i)+ this->_instance.getCost(store_j,j);
                float costo_swap = this->_instance.getCost(store_i, j)+ this->_instance.getCost(store_j,i);
                int cap_rem_store_i = this->_solution.getRemainingCapacity(store_i) + this->_instance.getSupply(store_i, i) - this->_instance.getSupply(store_i,j);
                int cap_rem_store_j = this->_solution.getRemainingCapacity(store_j) + this->_instance.getSupply(store_j, j) - this->_instance.getSupply(store_j,i);
                if(costo_swap < costo_inicial && cap_rem_store_i >=0 && cap_rem_store_j>=0){
                    if(costo_swap - costo_inicial < mejora){
                        mejora = costo_swap - costo_inicial;
                        vr = std::make_tuple(i,j);
                    }
                }
            }
            else if( store_i == -1 && store_j !=-1){
                float costo_inicial =  this->_instance.getDMax()*3+ this->_instance.getCost(store_j,j);
                float costo_swap = this->_instance.getDMax()*3+ this->_instance.getCost(store_j,i);
                int cap_rem_store_j = this->_solution.getRemainingCapacity(store_j) + this->_instance.getSupply(store_j, j) - this->_instance.getSupply(store_j,i);
                if(costo_swap < costo_inicial  && cap_rem_store_j>=0){
                    if(costo_swap - costo_inicial < mejora){
                        mejora = costo_swap - costo_inicial;
                        vr = std::make_tuple(i,j);
                    }
                }
            }
            else if(store_i != -1 && store_j == -1){
                float costo_inicial =  this->_instance.getCost(store_i, i)+ this->_instance.getDMax()*3;
                float costo_swap = this->_instance.getCost(store_i, j)+ this->_instance.getDMax()*3;
                int cap_rem_store_i = this->_solution.getRemainingCapacity(store_i) + this->_instance.getSupply(store_i, i) - this->_instance.getSupply(store_i,j);
                if(costo_swap < costo_inicial && cap_rem_store_i >=0){
                    if(costo_swap - costo_inicial < mejora){
                        mejora = costo_swap - costo_inicial;
                        vr = std::make_tuple(i,j);
                    }
                }
            }

        }
    }
    return vr;
}

GapSolution LocalSearchSwap::getSolution(){
    return this->_solution;
}