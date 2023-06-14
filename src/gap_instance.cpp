#include "gap_instance.h"
GapInstance :: GapInstance(string filename){
    ifstream input_file(filename);
    
    char delim = ' ';
    string line;
    input_file >> line;
    this->depositos = stoi(line);
    input_file >> line;
    this->vendedores = stoi(line);
    this->demandas = vector<vector<int>>(this->depositos, vector<int>(this->vendedores));
    this->costos = vector<vector<float>>(this->depositos, vector<float>(this->vendedores));
    this->capacidades = vector<int>(this->depositos);
    this->d_max = 0;
    for( int i = 0; i<this->depositos; i++){
        for (int j = 0; j < this->vendedores; j++)
        {
            input_file >> line;
            this->costos[i][j] = stof(line);
            if (stof(line) > this->d_max){
                this->d_max = stof(line);
            }
        }
        
    }
    for( int i = 0; i<this->depositos; i++){
        for (int j = 0; j < this->vendedores; j++)
        {
            input_file >> line;
            this->demandas[i][j] = stof(line);
        }
        
    }
    for (int i = 0; i < this->depositos; i++)
    {
        input_file >> line;
        this->capacidades[i] = stoi(line);
    }
    

}








