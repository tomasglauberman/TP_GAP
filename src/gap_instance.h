#ifndef GAP_INSTANCE_H
#define GAP_INSTANCE_H

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class GapInstance{
    public:
    GapInstance();
    GapInstance(string filename);
    ~GapInstance();
    //Me da la cantidad de depositos
    int getM() const;
    //Me da la cantidad de vendedores
    int getN() const;

    int getSupply(int store, int seller);
    int getCapacity(int store);
    float getCost(int store, int seller);
    float getDMax();

    private:
    int _stores;
    int _sellers;

    // posicion ij representa la cant de 
    //unidades a utilizar en el deposito i por el vendedor j
    vector<vector<int>> _supply;
    //Posicion i representa la capacidad del deposito i
    vector<int> _capacities;
    //posicion ij representa el costo de asignar el deposito i al vendedor j
    vector<vector<float>> _costs;
    float _d_max;
};

#endif