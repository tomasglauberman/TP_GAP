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

    void setTime(double time);
    double getTime() const;

    //float getObjVal_aux() const;
    int getRemainingCapacity(int store) const;
    bool checkFeasibility(GapInstance const &instance) const;
    //int getNotAssigned_aux() const;

    static GapSolution randomSolution(GapInstance instance, int seed=0);
    float getObjVal() const;
    int getNotAssigned() const;
    friend std::ostream& operator<<(std::ostream& os, const GapSolution& solution);
    bool operator==(const GapSolution& other) const;

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