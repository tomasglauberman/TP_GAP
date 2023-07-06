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
#include "vnd.h"
#include <filesystem>

vector<string> archivos = {};
vector<string> processFiles(const std::string& folderPath) {
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (std::filesystem::is_directory(entry)) {
            // Si es un directorio, llamamos recursivamente a la función para procesar los archivos dentro de él
            processFiles(entry.path().string());
        } else if (std::filesystem::is_regular_file(entry) && entry.path().extension() != ".json" && entry.path().extension() != ".ipynb") {
            // Si es un archivo regular, lo procesamos
            //Por algun motivo no me estaba excluyendo los ds_store
            if(!(entry.path().string() == "instances/.DS_Store") && !(entry.path().string() == "instances/gap/.DS_Store")){
                archivos.push_back(entry.path());
                //std::cout<< entry.path() << std::endl;
            }
        }
    }
    return archivos;
}

int main(int argc, char** argv) {
    // std::string folderPath = "instances";

    // vector<string> files = processFiles(folderPath);
    
    // std::fstream file;
    
    // // Open file and write header
    // file.open ("results.csv");
    // file << "filename, tipo, stores, selles, greedy1_cost, greedy2_cost, random_cost, relocate(random)_cost, swap(greedy2)_cost, genetic_cost, vnd_cost, g1_time, g2_time, rand_time, rel_time, swap_time, gen_time, vnd_time"<< std::endl; 

    // for(int i = 0; i < files.size(); i++){
    //     std::string filename = files[i];
    //     //Creo intancia
    //     GapInstance instance = GapInstance(filename);
        
    //     GreedySolver1 greedySolver1 = GreedySolver1(instance);
    //     GreedySolver2 greedySolver2 = GreedySolver2(instance);
    //     Random random = Random(instance);
    //     LocalSearchRelocate lsRelocate = LocalSearchRelocate(instance, LocalSearchRelocate::InitialSolution::RANDOM);
    //     LocalSearchSwap lsSwap = LocalSearchSwap(instance,LocalSearchSwap::InitialSolution::GREEDY2);

    //     greedySolver1.solve();
    //     greedySolver2.solve();
    //     random.solve();
    //     lsRelocate.solve();
    //     lsSwap.solve();

    //     GapSolution greedy1_sol = greedySolver1.getSolution();
    //     GapSolution greedy2_sol = greedySolver2.getSolution();
    //     GapSolution random_sol = random.getSolution();
    //     GapSolution relocate_sol = lsRelocate.getSolution();
    //     GapSolution swap_sol = lsSwap.getSolution();
    //     file << filename << "," << filename << "," << instance.getM()-1 << "," << instance.getN() << 
    //     "," << greedy1_sol.getObjVal() << "," << greedy2_sol.getObjVal() << "," << random_sol.getObjVal()
    //     << "," << relocate_sol.getObjVal()<< "," << swap_sol.getObjVal()<<","<<"gen_cost"<<","<<
    //     "vnd_cost"<< "," <<greedy1_sol.getTime() << "," << greedy2_sol.getTime() << "," << 
    //     random_sol.getTime()<< "," << relocate_sol.getTime()<< "," << swap_sol.getTime()
    //     <<","<<"gen_time"<<","<<"vnd_time"<< std::endl;

    // }
    
    // std::string filename = "instances/gap/gap_a/a05100";
    std::string filename = "instances/real/real_instance";
    // std::cout << "Reading file " << filename << std::endl;
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
    
    // Random random = Random(instancia);
    // random.solve();
    // GapSolution solucion5 = random.getSolution();
    // std::cout<< "Random" << std::endl<< solucion5;
    // std::cout<<"Factbilidad: " << solucion5.checkFeasibility(instancia)<<std::endl;

    // LocalSearchSwap lsSwap1 = LocalSearchSwap(instancia, LocalSearchSwap::InitialSolution::RANDOM);
    // lsSwap1.solve(); 
    // GapSolution solucion6 = lsSwap1.getSolution();
    // std::cout<< "LS SWAP" << std::endl << solucion6;
    // std::cout<<"Factbilidad: " << solucion6.checkFeasibility(instancia)<<std::endl;

    // LocalSearchRelocate lsRelocate1 = LocalSearchRelocate(instancia, LocalSearchRelocate::InitialSolution::RANDOM);
    // lsRelocate1.solve();
    // GapSolution solucion7 = lsRelocate1.getSolution();
    // std::cout<< "LS RELOCATE" << std::endl << solucion7;
    // std::cout<<"Factbilidad: " << solucion7.checkFeasibility(instancia)<<std::endl;

    // VND vnd = VND(instancia, VND::InitialSolution::RANDOM, VND::FirstNeighborhood::SWAP);
    // vnd.solve();
    // GapSolution solucionVnd = vnd.getSolution();
    // std::cout<< "VND" << std::endl << solucionVnd;
    // std::cout<<"Factbilidad: " << solucionVnd.checkFeasibility(instancia)<<std::endl;

    GeneticAlgorithmSolver genetic = GeneticAlgorithmSolver(instancia, 100, 500);
    genetic.solve();
    GapSolution solucionGenetic = genetic.getSolution();
    std::cout<< std::endl <<"GENETIC" << std::endl << solucionGenetic;
    std::cout<<"Factbilidad: " << solucionGenetic.checkFeasibility(instancia)<<std::endl;

    return 0;
}
