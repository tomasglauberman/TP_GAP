#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "main.cpp"


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

void run_exp() {
    
    std::string folderPath = "instances";

    vector<string> files = processFiles(folderPath);
    
    std::fstream file;
    
    // Open file and write header
    file.open ("results2.csv");
    file << "filename, tipo, stores, selles, greedy1_cost, greedy2_cost, random_cost, relocate(random)_cost, swap(greedy2)_cost, genetic_cost, vnd_cost, g1_time, g2_time, rand_time, rel_time, swap_time, gen_time, vnd_time"<< std::endl; 

    for(int i = 0; i < files.size(); i++){
        std::string filename = files[i];
        //Creo intancia
        GapInstance instance = GapInstance(filename);
        
        // GreedySolver1 greedySolver1 = GreedySolver1(instance);
        // GreedySolver2 greedySolver2 = GreedySolver2(instance);
        // Random random = Random(instance);
        // LocalSearchRelocate lsRelocate = LocalSearchRelocate(instance, LocalSearchRelocate::InitialSolution::RANDOM);
        // LocalSearchSwap lsSwap = LocalSearchSwap(instance,LocalSearchSwap::InitialSolution::GREEDY2);

        // greedySolver1.solve();
        // greedySolver2.solve();
        // random.solve();
        // lsRelocate.solve();
        // lsSwap.solve();

        // GapSolution greedy1_sol = greedySolver1.getSolution();
        // GapSolution greedy2_sol = greedySolver2.getSolution();
        // GapSolution random_sol = random.getSolution();
        // GapSolution relocate_sol = lsRelocate.getSolution();
        // GapSolution swap_sol = lsSwap.getSolution();
        // file << filename << "," << filename << "," << instance.getM()-1 << "," << instance.getN() << 
        // "," << greedy1_sol.getObjVal() << "," << greedy2_sol.getObjVal() << "," << random_sol.getObjVal()
        // << "," << relocate_sol.getObjVal()<< "," << swap_sol.getObjVal()<<","<<"gen_cost"<<","<<
        // "vnd_cost"<< "," <<greedy1_sol.getTime() << "," << greedy2_sol.getTime() << "," << 
        // random_sol.getTime()<< "," << relocate_sol.getTime()<< "," << swap_sol.getTime()
        // <<","<<"gen_time"<<","<<"vnd_time"<< std::endl;


        GRASP grasp = GRASP(instance);
        grasp.solve(10);
        GapSolution grasp_sol = grasp.getSolution();
        file << filename << "," << filename << "," << instance.getM()-1 << "," << instance.getN() <<
        "," << grasp_sol.getObjVal() << "," << grasp_sol.getTime() << std::endl;

    }
}