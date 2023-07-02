#ifndef GAP_SOLUTION_H
#define GAP_SOLUTION_H

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<ostream>
#include<set>
#include"gap_instance.h"
using namespace std;


class GapSolution{
    public:
    GapSolution();
    GapSolution(GapInstance &instance);
    ~GapSolution();

    void assign(int store, int seller);
    void unassign(int store, int seller);

    bool isSellerAssign(int seller) const;
    int getStoreAssigned(int seller) const;

    void outputSolution(string filename);
    //Falta hacer output solution
    void setTime(double time);
    double getTime() const;

    float getObjVal() const;
    int getRemainingCapacity(int store) const;
    bool checkFeasibility(GapInstance &instance) const;
    int getNotAssigned() const;

    static GapSolution randomSolution(GapInstance instance, int seed=0);
    
    friend std::ostream& operator<<(std::ostream& os, const GapSolution& solution);

    private:
    GapInstance _instance;
    float _obj_value;
    double _time;
    //posicion j nos dice a que deposito fue asignado el vendedor j
    vector<int> _sellers_assignment;
    //posicion i tiene un set con los vendedores asignados al deposito i
    vector<int> _remaining_capacity;
    int _not_assigned;
};

#endif