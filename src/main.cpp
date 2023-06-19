#include <string>
#include <iostream>
#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"


int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;
    
    GapInstance instancia = GapInstance(filename);
    GapSolution solution = GapSolution(instancia.getM(), instancia.getN());

    GreedySolver1 greedySovler = GreedySolver1(instancia, solution);

    greedySovler.solve();

    std::cout << solution;


    // Aca empieza la magia.

    return 0;
}