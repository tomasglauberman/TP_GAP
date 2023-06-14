#include "gap_solution.h"

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
