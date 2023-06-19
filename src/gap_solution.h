#ifndef GAP_SOLUTION_H
#define GAP_SOLUTION_H

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<set>
using namespace std;


class GapSolution{
    public:
    GapSolution();
    GapSolution(int store, int seller);
    void assign(int store, int seller);
    bool isSellerAssign(int seller);

    int getStoreAssigned(int seller);
    void outputSolution(string filename);
    void setTime(double time);
    double getTime();

    void setObjVal(float val);
    float getObjVal();

    friend std::ostream& operator<<(std::ostream& os, GapSolution& solution);

    private:
    int _sellers;
    int _stores;
    float _obj_value;
    double _time;
    //posicion j nos dice a que deposito fue asignado el vendedor j
    vector<int> _sellers_assignment;
    //posicion i tiene un set con los vendedores asignados al deposito i
    vector<set<int>> _store_assignment;
};

#endif