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
    //std::string filename = "instances/gap/gap_e/e801600";
    std::string filename = "instances/real/real_instance";
    std::cout << "Reading file " << filename << std::endl;
    GapInstance instancia = GapInstance(filename);

    GreedySolver1 greedySolver1 = GreedySolver1(instancia);    
    greedySolver1.solve();
    GapSolution solucion1 = greedySolver1.getSolution();
    std::cout<< "GREEDY 1" << std::endl << solucion1;
    std::cout<<"Factbilidad: " << solucion1.checkFeasibility(instancia)<<std::endl<< std::endl;
    std::cout<<  solucion1.getObjVal2() << std::endl;

    GreedySolver2 greedySolver2 = GreedySolver2(instancia);
    greedySolver2.solve();
    GapSolution solucion2 = greedySolver2.getSolution();
    std::cout<< "GREEDY 2" << std::endl << solucion2;
    std::cout<<"Factbilidad: " << solucion2.checkFeasibility(instancia)<<std::endl << std::endl;
    std::cout<<  solucion2.getObjVal2() << std::endl;

    LocalSearchRelocate lsRelocate = LocalSearchRelocate(instancia, LocalSearchRelocate::InitialSolution::RANDOM);
    lsRelocate.solve();
    GapSolution solucion3 = lsRelocate.getSolution();
    std::cout<< "LS RELOCATE" << std::endl << solucion3;
    std::cout<<"Factbilidad: " << solucion3.checkFeasibility(instancia)<<std::endl << std::endl;
    std::cout<<  solucion3.getObjVal2() << std::endl;

    LocalSearchSwap lsSwap = LocalSearchSwap(instancia, LocalSearchSwap::InitialSolution::GREEDY2);
    lsSwap.solve(); 
    std::cout<< "LS SWAP" << std::endl << lsSwap.getSolution(); 
    std::cout<<"Factbilidad: " << lsSwap.getSolution().checkFeasibility(instancia)<<std::endl;
     std::cout<<  lsSwap.getSolution().getObjVal2() << std::endl;
    return 0;
}