#include <string>
#include <iostream>
#include <ostream>
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "lsRelocate.h"
#include "lsSwap.h"


int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a20200";
    std::cout << "Reading file " << filename << std::endl;
    
    GapInstance instancia = GapInstance(filename);
    GreedySolver2 greedySolver2 = GreedySolver2(instancia);
    // GapSolution menos1 = GapSolution(instancia);
    greedySolver2.solve();
    GapSolution solucion = greedySolver2.getSolution();
    std::cout<<"Metodo print: "<<solucion<<std::endl;
     std::cout<<"Factbilidad greedy: "<<solucion.checkFeasibility(instancia)<<std::endl;
    // LocalSearchRelocate localSearch = LocalSearchRelocate(instancia);
    // localSearch.solve(solucion);
    // GapSolution solRel = localSearch.getSolution();
    // std::cout<<solRel.getObjVal()<<" "<<solRel.getTime()<<std::endl;
    // std::cout << "Objetive value: " << localSearch.getSolution() << std::endl;

    LocalSearchSwap lsSwap = LocalSearchSwap(instancia);
    lsSwap.solve(solucion); 
    std::cout<<lsSwap.getSolution()<< std::endl; 
    std::cout<<"Factbilidad: "<<lsSwap.getSolution().checkFeasibility(instancia)<<std::endl;

    return 0;
}