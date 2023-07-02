#include "gap_instance.h"

GapInstance::GapInstance() {}

GapInstance :: GapInstance(string filename){
    ifstream input_file(filename);
    
    char delim = ' ';
    string line;
    input_file >> line;
    // 1 deposito mas para la penalizcion por no asignar
    this->_stores = stoi(line) + 1;
    input_file >> line;
    this->_sellers = stoi(line);
    this->_demand = vector<vector<int>>(this->_stores, vector<int>(this->_sellers));
    this->_costs = vector<vector<float>>(this->_stores, vector<float>(this->_sellers));
    this->_capacities = vector<int>(this->_stores);
    this->_d_max = 0;

    // Costos de asignacion 
    for( int i = 0; i<this->_stores-1; i++){
        for (int j = 0; j < this->_sellers; j++)
        {
            input_file >> line;
            this->_costs[i][j] = stof(line);
            if (stof(line) > this->_d_max){
                this->_d_max = stof(line);
            }
        }
    }

    // Costos de penalizacion
    for (int j = 0; j < this->_sellers; j++)
    {
        this->_costs[this->_stores-1][j] = this->_d_max;
    }

    // Demandas
    for( int i = 0; i<this->_stores-1; i++){
        for (int j = 0; j < this->_sellers; j++)
        {
            input_file >> line;
            this->_demand[i][j] = stof(line);
        }
    }

    // Demandas de deposito 'fantasma'
    // Siempre es 0, por lo que siempre se puede asignar a ese deposito
    for (int j = 0; j < this->_sellers; j++)
    {
        this->_demand[this->_stores-1][j] = 0;
    }

    for (int i = 0; i < this->_stores-1; i++)
    {
        input_file >> line;
        this->_capacities[i] = stoi(line);
    }
    this->_capacities[this->_stores-1] = 1;

}

GapInstance::~GapInstance(){}

int GapInstance :: getM() const {
    return this->_stores;
};

int GapInstance :: getN() const{
    return this->_sellers;
};

int GapInstance::getDemand(int store, int seller) const{
    return this->_demand[store][seller];
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

void GapInstance::summary() const {
    int64_t capacidad_total = 0;
    for (int i = 0; i < getM()-1; i++)
    {
        capacidad_total += getCapacity(i);
    }

    int64_t demanda_total = 0;
    for (int j = 0; j < getN(); j++)
    {
        int demanda = 0;
        for (int i = 0; i < getM()-1; i++)
        {
            demanda += getDemand(i,j);
        }

        demanda_total += (demanda/(getM()-1));
    }

    std::cout << "Capacidad total: " << capacidad_total << std::endl;
    std::cout << "Demandas promedio total: " << demanda_total << std::endl;
}







