#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class GapInstance{
    public:
    GapInstance();
    GapInstance(string filename);
    //Me da la cantidad de depositos
    int getM();
    //Me da la cantidad de vendedores
    int getN();
    // posicion ij representa la cant de 
    //unidades a utilizar en el deposito i por el vendedor j
    vector<vector<int>> supply;
    //Posicion i representa la capacidad del deposito i
    vector<int> capacities;
    //posicion ij representa el costo de asignar el deposito i al vendedor j
    vector<vector<float>> costs;
    float d_max;

    private:
    int _stores;
    int _sellers;
};