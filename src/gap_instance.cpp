#include "gap_instance.h"

GapInstance::GapInstance() {}

GapInstance :: GapInstance(string filename){
    ifstream input_file(filename);
    
    char delim = ' ';
    string line;
    input_file >> line;
    this->_stores = stoi(line);
    input_file >> line;
    this->_sellers = stoi(line);
    this->_supply = vector<vector<int>>(this->_stores, vector<int>(this->_sellers));
    this->_costs = vector<vector<float>>(this->_stores, vector<float>(this->_sellers));
    this->_capacities = vector<int>(this->_stores);
    this->_d_max = 0;
    for( int i = 0; i<this->_stores; i++){
        for (int j = 0; j < this->_sellers; j++)
        {
            input_file >> line;
            this->_costs[i][j] = stof(line);
            if (stof(line) > this->_d_max){
                this->_d_max = stof(line);
            }
        }
        
    }
    for( int i = 0; i<this->_stores; i++){
        for (int j = 0; j < this->_sellers; j++)
        {
            input_file >> line;
            this->_supply[i][j] = stof(line);
        }
        
    }
    for (int i = 0; i < this->_stores; i++)
    {
        input_file >> line;
        this->_capacities[i] = stoi(line);
    }
    //std::cout << this->_d_max<<std::endl;
}

GapInstance::~GapInstance(){}

int GapInstance :: getM() const {
    return this->_stores;
};
int GapInstance :: getN() const{
    return this->_sellers;
};

int GapInstance::getSupply(int store, int seller) const{
    return this->_supply[store][seller];
}

int GapInstance::getCapacity(int store) const{
    return this->_capacities[store];
}

float GapInstance::getCost(int store, int seller) const{
    return this->_costs[store][seller];
}

float GapInstance::getDMax() const{
    return this->_d_max;
}







