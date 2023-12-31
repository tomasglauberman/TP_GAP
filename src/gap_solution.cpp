#include "gap_solution.h"
#include <random>

GapSolution::GapSolution() {}

GapSolution :: GapSolution (GapInstance &instance){
    this->_instance = instance;
    // Se asignan todos los vendedores al deposito fantasma
    this->_sellers_assignment = vector<int>(instance.getN(),instance.getM()-1);
    this->_remaining_capacity = vector<int>(instance.getM(), 0);
    this->_time = 0;
    for (int i = 0; i < this->_instance.getM(); i++)
    {
        this->_remaining_capacity[i] = this->_instance.getCapacity(i);
    }  

    this->_not_assigned = instance.getN();
    this->_obj_value = instance.getN()*3*instance.getDMax();
}
GapSolution::~GapSolution(){}

void GapSolution::assign(int store, int seller) {

    if(store == this->_instance.getM()-1){
        throw logic_error("No se puede asignar a un deposito fantasma");
    } else if (isSellerAssign(seller)){
        throw logic_error("El vendedor ya esta asignado a un deposito");
    }

    this->_sellers_assignment[seller] = store;
    this->_remaining_capacity[store] -= this->_instance.getDemand(store,seller);

    this->_not_assigned --;
    this->_obj_value =  this->_obj_value - 3* this->_instance.getDMax() + this->_instance.getCost(store, seller);
}

void GapSolution::unassign(int store, int seller) {

    if (store == this->_instance.getM()-1){
        throw logic_error("No se puede desasignar de un deposito fantasma");
    } else if (getStoreAssigned(seller) != store){
        throw logic_error("El vendedor no esta asignado a ese deposito");
    }

    this->_sellers_assignment[seller] = this->_instance.getM()-1;
    this->_remaining_capacity[store] += this->_instance.getDemand(store,seller);

    this->_not_assigned++;
    this->_obj_value =  this->_obj_value + 3 * this->_instance.getDMax() - this->_instance.getCost(store, seller);
}

bool GapSolution::isSellerAssign(int seller) const{
    if (this->_sellers_assignment[seller] == this->_instance.getM()-1){
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

int GapSolution::getStoreAssigned(int seller) const {
    return this->_sellers_assignment[seller];
}


std::ostream& operator<<(std::ostream& os, const GapSolution& solution) {
    os << "Objective Value: " << solution.getObjVal() << std::endl;
    os << "Time: " << solution.getTime() << " microseconds" << std::endl;
    os << "Cant sin asignar: " << solution.getNotAssigned() << std::endl;
    os << "Factibilidad: " << solution.checkFeasibility(solution._instance) << std::endl;

    return os;
}

bool GapSolution::operator==(const GapSolution& other) const {
    
    for (int i = 0; i < this->_instance.getN(); i++) {
        if (this->_sellers_assignment[i] != other._sellers_assignment[i]) {
            return false;
        }
    }

    return true;
}

float GapSolution::getObjVal() const{
    return this->_obj_value;
}

int GapSolution::getNotAssigned() const{
    return this->_not_assigned;
}

bool GapSolution::checkFeasibility(GapInstance const &instance) const {

    vector<int> remaining_capacity = vector<int>(instance.getM());
    for (int i=0; i < instance.getM(); i++) {
        remaining_capacity[i] = instance.getCapacity(i);
    }

    int sin_asignar = 0;
    for (int i = 0; i < instance.getN(); i++) {
        if(this->_sellers_assignment[i] == instance.getM()-1) {
            sin_asignar++;
        } else {
            remaining_capacity[this->_sellers_assignment[i]] -= instance.getDemand(this->_sellers_assignment[i], i);
        };
    }

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


GapSolution GapSolution::randomSolution(GapInstance instance, int seed) {
    std::mt19937 randGen;
    randGen.seed(seed);
    std::uniform_int_distribution<int> dist(0, instance.getM()-2);

    GapSolution solution = GapSolution(instance);

    for (int j = 0; j < instance.getN(); j++) {
        int store = dist(randGen);
        solution.assign(store, j);
    }
    return solution;
}

void GapSolution::outputSolution(string filename) {
    // Abrir el archivo en modo escritura
    std::ofstream archivo(filename);

    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
    }

    // Escribir en el archivo
    for (int i=0; i < this->_instance.getM()-1; i++) {
        for (int j=0; j < this->_instance.getN(); j++) {
            if (this->_sellers_assignment[j] == i) {
                archivo << j << " ";
            }
        }
        archivo << std::endl;  // Nueva línea para cada depósito
    }

    // Cerrar el archivo
    archivo.close();
}