#include <string>
#include <iostream>
#include <ostream>
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "lsRelocate.h"


int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;
    
    GapInstance instancia = GapInstance(filename);
    GreedySolver1 greedySovler1 = GreedySolver1(instancia);

    greedySovler1.solve();
    GapSolution solucion = greedySovler1.getSolution();

    LocalSearchRelocate localSearch = LocalSearchRelocate(instancia);
    localSearch.solve(solucion);

    std::cout << "Objetive value: " << localSearch.getSolution() << std::endl;


    return 0;
}