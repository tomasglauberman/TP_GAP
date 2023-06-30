#include "gap_solution.h"

GapSolution::GapSolution() {}

GapSolution :: GapSolution (GapInstance &instance){
    this->_instance = instance;
    this->_not_assigned = instance.getN();
    this->_sellers_assignment = vector<int>(instance.getN(),-1);
    this->_remaining_capacity = vector<int>(instance.getM(), 0);
    this->_obj_value = instance.getN()*3*instance.getDMax();
    for (int i = 0; i < this->_instance.getM(); i++)
    {
        this->_remaining_capacity[i] = this->_instance.getCapacity(i);
    }  
}
GapSolution::~GapSolution(){}

void GapSolution :: assign(int store, int seller) {
    this->_sellers_assignment[seller] = store;
    this->_remaining_capacity[store] -= this->_instance.getSupply(store,seller);
    this->_not_assigned --;
    this->_obj_value =  this->_obj_value - 3* this->_instance.getDMax() + this->_instance.getCost(store, seller);
}

void GapSolution::unassign(int store, int seller) {
    this->_sellers_assignment[seller] = -1;
    //std::cout << this->_remaining_capacity[store] << std::endl;
    this->_remaining_capacity[store] += this->_instance.getSupply(store,seller);
    this->_not_assigned++;
    this->_obj_value =  this->_obj_value + 3 * this->_instance.getDMax() - this->_instance.getCost(store, seller);
}

bool GapSolution :: isSellerAssign(int seller) const{
    if (this->_sellers_assignment[seller] == -1){
        return false;
    }
    return true;
}

void GapSolution::setTime(double time) {
    this->_time = time;
}

double GapSolution::getTime() const{
    return this->_time;
}


float GapSolution::getObjVal() const {
    return this->_obj_value;
}

int GapSolution::getStoreAssigned(int seller) const {
    return this->_sellers_assignment[seller];
}

int GapSolution::getNotAssigned() const{
    return this->_not_assigned;
}

std::ostream& operator<<(std::ostream& os, const GapSolution& solution) {
    os << "Objective Value: " << solution.getObjVal() << std::endl;
    os << "Time: " << solution.getTime() << std::endl;
    os << "Cant sin asignar: " << solution.getNotAssigned() << std::endl;
    // os << "Seller\tStore" << std::endl;
    // for (int i = 0; i < solution._instance.getN(); i++) {
    //     os << i << "-> "<<  solution.getStoreAssigned(i)<< std::endl;
    // }

    return os;
}


bool GapSolution::checkFeasibility(GapInstance &instance) {

    vector<int> remaining_capacity = vector<int>(instance.getM());
    for (int i=0; i < instance.getM(); i++) {
        remaining_capacity[i] = instance.getCapacity(i);
    }

    int sin_asignar = 0;
    for (int i = 0; i < instance.getN(); i++) {
        if(this->_sellers_assignment[i] == -1) {
            sin_asignar++;
        } else {
            remaining_capacity[this->_sellers_assignment[i]] -= instance.getSupply(this->_sellers_assignment[i], i);
        };
    }

    std::cout << "SIN ASIGNAR: "  << sin_asignar << std::endl;

    for (int i = 0; i < instance.getM(); i++) {
        if (remaining_capacity[i] < 0) {
            return false;
        }
    }
    return true;
}

int GapSolution::getRemainingCapacity(int store) const {
    return this->_remaining_capacity[store];
}