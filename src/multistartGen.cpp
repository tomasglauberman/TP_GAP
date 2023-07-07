#include "multistartGen.h"

GapSolution graspGen(GapInstance instance, int starts) {

    auto start = std::chrono::high_resolution_clock::now();

    GapSolution solution = GapSolution(instance);

    for (int i = 0; i < starts; i++) {
        GeneticAlgorithmSolver genSolver  = GeneticAlgorithmSolver(instance, 5, 100, i*2+1);
        genSolver.solve();
        GapSolution newSolution = genSolver.getSolution();

        VND vnd = VND(instance, VND::InitialSolution::CUSTOM, VND::FirstNeighborhood::RELOCATE);
        vnd.setSolution(newSolution);
        vnd.solve();
        newSolution = vnd.getSolution();

        if (newSolution.getObjVal() < solution.getObjVal()) {
            solution = newSolution;
        }

        std::cout << std::endl << i+1 << "/" << starts <<  "\t Bests current solution: "<< solution.getObjVal() << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::seconds>(end -start).count();
    solution.setTime(double(duration));

    return solution;
}

