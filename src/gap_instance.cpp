#include "gap_instance.h"
GapInstance :: GapInstance(string filename){
    ifstream input_file(filename);
    
    char delim = ' ';
    string line;
    input_file >> line;
    this->_stores = stoi(line);
    input_file >> line;
    this->_sellers = stoi(line);
    this->supply = vector<vector<int>>(this->_stores, vector<int>(this->_sellers));
    this->costs = vector<vector<float>>(this->_stores, vector<float>(this->_sellers));
    this->capacities = vector<int>(this->_stores);
    this->d_max = 0;
    for( int i = 0; i<this->_stores; i++){
        for (int j = 0; j < this->_sellers; j++)
        {
            input_file >> line;
            this->costs[i][j] = stof(line);
            if (stof(line) > this->d_max){
                this->d_max = stof(line);
            }
        }
        
    }
    for( int i = 0; i<this->_stores; i++){
        for (int j = 0; j < this->_sellers; j++)
        {
            input_file >> line;
            this->supply[i][j] = stof(line);
        }
        
    }
    for (int i = 0; i < this->_stores; i++)
    {
        input_file >> line;
        this->capacities[i] = stoi(line);
    }
    
}

int GapInstance :: getM(){
    return this->_stores;
};
int GapInstance :: getN(){
    return this->_sellers;
};








