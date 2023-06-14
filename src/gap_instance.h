#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class GapInstance{
    public:
    GapInstance(string filename);
    //numero de depositos
    int depositos;
    //numero de vendedores
    int vendedores;
    // posicion ij representa la cant de 
    //unidades a utilizar en el deposito i por el vendedor j
    vector<vector<int>> demandas;
    //Posicion i representa la capacidad del deposito i
    vector<int> capacidades;
    //posicion ij representa el costo de asigna el deposito i al vendedor j
    vector<vector<float>> costos;
    float d_max;
    
};