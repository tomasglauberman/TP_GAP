#include <string>
#include <iostream>
#include"gap_instance.h"


int main(int argc, char** argv) {
    std::string filename = "instances/real/real_instance";
    std::cout << "Reading file " << filename << std::endl;
    
    GapInstance instancia = GapInstance(filename);



    // Aca empieza la magia.

    return 0;
}