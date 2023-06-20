#include <string>
#include <iostream>
#include <ostream>
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "lsRelocate.h"


int main(int argc, char** argv) {
    std::string filename = "instances/real/real_instance";
    std::cout << "Reading file " << filename << std::endl;
    
    GapInstance instancia = GapInstance(filename);
    GreedySolver1 greedySovler1 = GreedySolver1(instancia);

    greedySovler1.solve();
    GapSolution solucion = greedySovler1.getSolution();
    std::cout<<solucion.getObjVal()<<" "<<solucion.getTime()<<std::endl;
    LocalSearchRelocate localSearch = LocalSearchRelocate(instancia);
    localSearch.solve(solucion);
    GapSolution solRel = localSearch.getSolution();
    std::cout<<solRel.getObjVal()<<" "<<solRel.getTime()<<std::endl;
    // std::cout << "Objetive value: " << localSearch.getSolution() << std::endl;


    return 0;
}