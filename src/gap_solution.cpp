#include "gap_solution.h"

GapSolution::GapSolution() {}

GapSolution :: GapSolution (int stores, int seller){
    this->_sellers = seller;
    this->_stores = stores;
    this->_sellers_assignment = vector<int>(seller,-1);
    this->_store_assignment = vector<set<int>>(stores);
}

void GapSolution :: assign(int store, int seller){
    this->_sellers_assignment[seller] = store;
    this->_store_assignment[store].insert(seller);
}

bool GapSolution :: isSellerAssign(int seller){
    if (this->_sellers_assignment[seller] == -1){
        return false;
    }
    return true;
}

void GapSolution::setTime(double time) {
    this->_time = time;
}

double GapSolution::getTime() {
    return this->_time;
}

void GapSolution::setObjVal(float val) {
    this->_obj_value = val;
}

float GapSolution::getObjVal() {
    return this->_obj_value;
}

int GapSolution::getStoreAssigned(int seller) {
    return this->_sellers_assignment[seller];
}


std::ostream& operator<<(std::ostream& os, GapSolution& solution) {
    os << "Objective Value: " << solution.getObjVal() << std::endl;

    os << "Seller\tStore" << std::endl;
    for (int i = 0; i < solution._sellers; i++)
        os << i << "-> "<<  solution._sellers_assignment[i] << std::endl;

    return os;
}
