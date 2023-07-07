#include <iostream>
#include <ostream>
#include <filesystem>

#include <string>
#include <unordered_map>

#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "greedy2.h"
#include "lsRelocate.h"
#include "lsSwap.h"
#include "genAlg.h"
#include "random.h"
#include "vnd.h"

#include "grasp.h"

enum Algorithm {GREEDY1, GREEDY2, LS_RELOCATE, LS_SWAP, VND_S, VND_R, GENETIC, MULTISTART_GEN};

int main(int argc, char* argv[]) {

    std::string filename = argv[1];
    std::string outputFile = argv[2];
    

    if(filename == "real_instance") {
        filename = "instances/real/real_instance";
    } else {
        char type = argv[1][0];
        filename = "instances/gap/gap_";
        filename += type;
        filename += "/";
        filename += argv[1];
    }

    std::unordered_map<std::string, Algorithm> enumMap = {
        {"GREEDY1", GREEDY1},
        {"GREEDY2", GREEDY2},
        {"LS_RELOCATE", LS_RELOCATE},
        {"LS_SWAP", LS_SWAP},
        {"VND_S", VND_S},
        {"VND_R", VND_R},
        {"GENETIC", GENETIC}
    };

    if (argc < 3) {
        std::cout << "No se especifico algoritmo. Uso: ./program <algoritmo>" << std::endl;
        return 0;
    }

    std::cout << "Reading file " << filename << std::endl;
    GapInstance instancia = GapInstance(filename);
    std::string enumName = argv[3];
    if (enumMap.find(enumName) == enumMap.end()) {
        std::cout << "Algoritmo incorrecto: " << enumName << std::endl;
        return 0;
    }

    Algorithm enumValue = enumMap[enumName];

    // Example usage
    switch (enumValue) {
        case GREEDY1: {
            GreedySolver1 greedySolver1 = GreedySolver1(instancia);    
            greedySolver1.solve();
            GapSolution solucion = greedySolver1.getSolution();
            solucion.outputSolution(outputFile);
            std::cout<< "GREEDY 1" << std::endl << solucion;
            break;
        }
        case GREEDY2: {
            GreedySolver2 greedySolver2 = GreedySolver2(instancia);
            greedySolver2.solve();
            GapSolution solucion = greedySolver2.getSolution();
            solucion.outputSolution(outputFile);
            std::cout<< "GREEDY 2" << std::endl << solucion;
            break;
        }
        case LS_RELOCATE: {
            LocalSearchRelocate::InitialSolution initialSolution;
            std::string intSol = argv[4];
            if (intSol == "RANDOM") {
                initialSolution = LocalSearchRelocate::InitialSolution::RANDOM;
            } else if (intSol == "GREEDY1") {
                initialSolution = LocalSearchRelocate::InitialSolution::GREEDY1;
            } else if (intSol == "GREEDY2") {
                initialSolution = LocalSearchRelocate::InitialSolution::GREEDY2;
            } else {
                std::cout << "Solucion inicial incorrecta: " << argv[3] << std::endl;
                return 0;
            }
            LocalSearchRelocate lsRelocate = LocalSearchRelocate(instancia, initialSolution);
            lsRelocate.solve();
            GapSolution solucion = lsRelocate.getSolution();
            solucion.outputSolution(outputFile);
            std::cout<< "LS RELOCATE" << std::endl << solucion;
            break;
        }
        case LS_SWAP: {
            LocalSearchSwap::InitialSolution initialSolution;
            std::string intSol = argv[4];
            if (intSol == "RANDOM") {
                initialSolution = LocalSearchSwap::InitialSolution::RANDOM;
            } else if (intSol == "GREEDY1") {
                initialSolution = LocalSearchSwap::InitialSolution::GREEDY1;
            } else if (intSol == "GREEDY2") {
                initialSolution = LocalSearchSwap::InitialSolution::GREEDY2;
            } else {
                std::cout << "Solucion inicial incorrecta: " << argv[3] << std::endl;
                return 0;
            }
            LocalSearchSwap lsRelocate = LocalSearchSwap(instancia, initialSolution);
            lsRelocate.solve();
            GapSolution solucion = lsRelocate.getSolution();
            solucion.outputSolution(outputFile);
            std::cout<< "LS SWAP" << std::endl << solucion;
            break;
        }
        case VND_S: {
            VND::InitialSolution initialSolutionVnd;
            std::string intSol = argv[4];
            if (intSol == "RANDOM") {
                initialSolutionVnd = VND::InitialSolution::RANDOM;
            } else if (intSol == "GREEDY1") {
                initialSolutionVnd = VND::InitialSolution::GREEDY1;
            } else if (intSol == "GREEDY2") {
                initialSolutionVnd = VND::InitialSolution::GREEDY2;
            } else if (intSol == "GENETIC") {
                initialSolutionVnd = VND::InitialSolution::GENETIC;
            } else {
                std::cout << "Solucion inicial incorrecta: " << argv[3] << std::endl;
                return 0;
            }
            VND vnd = VND(instancia, initialSolutionVnd, VND::FirstNeighborhood::SWAP);
            vnd.solve();
            GapSolution solucionVnd = vnd.getSolution();
            solucionVnd.outputSolution(outputFile);
            std::cout<< "VND" << std::endl << solucionVnd;
            break;
        }

        case VND_R: {
            VND::InitialSolution initialSolutionVnd;
            std::string intSol = argv[4];
            if (intSol == "RANDOM") {
                initialSolutionVnd = VND::InitialSolution::RANDOM;
            } else if (intSol == "GREEDY1") {
                initialSolutionVnd = VND::InitialSolution::GREEDY1;
            } else if (intSol == "GREEDY2") {
                initialSolutionVnd = VND::InitialSolution::GREEDY2;
            } else if (intSol == "GENETIC") {
                initialSolutionVnd = VND::InitialSolution::GENETIC;
            } else {
                std::cout << "Solucion inicial incorrecta: " << argv[3] << std::endl;
                return 0;
            }
            VND vnd = VND(instancia, initialSolutionVnd, VND::FirstNeighborhood::RELOCATE);
            vnd.solve();
            GapSolution solucionVnd = vnd.getSolution();
            solucionVnd.outputSolution(outputFile);
            std::cout<< "VND" << std::endl << solucionVnd;
            break;
        }

        case GENETIC: {
            int populationSize = atoi(argv[4]);
            int generations = atoi(argv[5]);
            GeneticAlgorithmSolver genetic = GeneticAlgorithmSolver(instancia, populationSize, generations);
            genetic.solve();
            GapSolution solucionGenetic = genetic.getSolution();
            solucionGenetic.outputSolution("results");
            std::cout<< "GENETIC" << std::endl << solucionGenetic;
            break;
        }

        case MULTISTART_GEN: {
            int starts = atoi(argv[4]);
            GapSolution solution = graspGen(instancia, starts);
            std::cout<< "MULTISTART GENTIC" << std::endl << solution;
            std::cout << solution;
        }

        default:
            std::cout << "ALGORITMO INCORRECTO" << std::endl;
            break;
    }

    return 0;
}
