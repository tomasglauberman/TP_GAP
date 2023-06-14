#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<set>
using namespace std;


class GapSolution{
    public:
    GapSolution(int store, int seller);
    void assign(int store, int seller);
    bool isSellerAssign(int seller);
    int remainingCapacity(int store);
    float getObjetiveValue();





    private:
    int _sellers;
    int _stores;
    //posicion j nos dice a que deposito fue asignado el vendedor j
    vector<int> _sellers_assignment;
    //posicion i tiene un set con los vendedores asignados al deposito i
    vector<set<int>> _stroe_assignment;
    //Posicion i nos dice la capacidad remanente del deposito i
    vector<int> _remaining_capacity;
    float _objetive_value;
};