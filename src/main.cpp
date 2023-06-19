#include <string>
#include <iostream>
#include <ostream>
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "lsRelocate.h"


int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_e/e10100";
    std::cout << "Reading file " << filename << std::endl;
    
    GapInstance instancia = GapInstance(filename);
    std:: cout << instancia.getSupply(0, 0) << std::endl;

    GreedySolver1 greedySovler1 = GreedySolver1(instancia);
    // GreedySolver2 greedySovler2 = GreedySolver2(instancia);
    // GapSolution solution2 = greedySovler2.getSolution();

    // int dem = 0;
    // for (int i = 0; i < instancia.getM(); i++)
    // {
    //     for (int j = 0; j < instancia.getN(); j++)
    //     {
    //         dem += instancia.getSupply(i,j);
    //     }
    // }

    // std:: cout << dem/(instancia.getM()*instancia.getN()) << std::endl;
    
    // greedySovler1.solve();

    // GapSolution solution1 = greedySovler1.getSolution();
    // LocalSearchRelocate localSearch = LocalSearchRelocate(instancia);
    // localSearch.solve(solution1);

    // std::cout << localSearch.getSolution() << std::endl;

    // std::cout << solution1;

    // greedySovler2.solve();
    
    return 0;
}