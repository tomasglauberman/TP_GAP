#include <string>
#include <iostream>
#include <ostream>
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "lsRelocate.h"
#include "lsSwap.h"
#include "genAlg.h"
#include "random.h"

int main(int argc, char** argv) {
    //std::string filename = "instances/gap/gap_a/a20200";
    std::string filename = "instances/real/real_instance";
    std::cout << "Reading file " << filename << std::endl;
    GapInstance instancia = GapInstance(filename);

    // GreedySolver1 greedySolver1 = GreedySolver1(instancia);    
    // greedySolver1.solve();
    // GapSolution solucion1 = greedySolver1.getSolution();
    // std::cout<< "GREEDY 1" << std::endl << solucion1;
    // std::cout<<"Factbilidad: " << solucion1.checkFeasibility(instancia)<<std::endl;
     
    // GreedySolver2 greedySolver2 = GreedySolver2(instancia);
    // greedySolver2.solve();
    // GapSolution solucion2 = greedySolver2.getSolution();
    // std::cout<< "GREEDY 2" << std::endl << solucion2;
    // std::cout<<"Factbilidad: " << solucion2.checkFeasibility(instancia)<<std::endl;
   
    // LocalSearchRelocate lsRelocate = LocalSearchRelocate(instancia, LocalSearchRelocate::InitialSolution::RANDOM);
    // lsRelocate.solve();
    // GapSolution solucion3 = lsRelocate.getSolution();
    // std::cout<< "LS RELOCATE" << std::endl << solucion3;
    // std::cout<<"Factbilidad: " << solucion3.checkFeasibility(instancia)<<std::endl;

    
    
    // LocalSearchSwap lsSwap = LocalSearchSwap(instancia, LocalSearchSwap::InitialSolution::GREEDY2);
    // lsSwap.solve(); 
    // GapSolution solucion4 = lsSwap.getSolution();
    // std::cout<< "LS SWAP" << std::endl << solucion4; 
    // std::cout<<"Factbilidad: " << solucion4.checkFeasibility(instancia)<<std::endl;
    
    Random random = Random(instancia);
    random.solve();
    GapSolution solucion5 = random.getSolution();
    std::cout<< "Random" << std::endl<< solucion5;
    std::cout<<"Factbilidad: " << solucion5.checkFeasibility(instancia)<<std::endl;



    LocalSearchSwap lsSwap1 = LocalSearchSwap(instancia, LocalSearchSwap::InitialSolution::RANDOM);
    lsSwap1.solve(); 
    GapSolution solucion6 = lsSwap1.getSolution();
    std::cout<< "LS SWAP" << std::endl << solucion6;
    std::cout<<"Factbilidad: " << solucion6.checkFeasibility(instancia)<<std::endl;



    LocalSearchRelocate lsRelocate1 = LocalSearchRelocate(instancia, LocalSearchRelocate::InitialSolution::RANDOM);
    lsRelocate1.solve();
    GapSolution solucion7 = lsRelocate1.getSolution();
    std::cout<< "LS RELOCATE" << std::endl << solucion7;
    std::cout<<"Factbilidad: " << solucion7.checkFeasibility(instancia)<<std::endl;
    return 0;
}