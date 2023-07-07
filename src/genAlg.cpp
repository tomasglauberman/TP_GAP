#include "genAlg.h"

GeneticAlgorithmSolver::GeneticAlgorithmSolver() {}

GeneticAlgorithmSolver::GeneticAlgorithmSolver(GapInstance instance, int populationSize, int generations, int seed) {
    this->_instance = instance;
    this->_solution = GapSolution(instance);

    this->_populationSize = populationSize;
    this->_generations = generations;
    this->_population = std::vector<GapSolution>(populationSize);
    this->_fitness = std::vector<float>(populationSize);
    this->_unfitness = std::vector<float>(populationSize);

    this->_randGen.seed(seed);

    // Randomly generate initial population
    for (int i = 0; i < populationSize; i++) {
        this->_population[i] = GapSolution::randomSolution(instance);

        this->_fitness[i] = this->_population[i].getObjVal();
        this->_unfitness[i] = this->_unfitnessFunction(this->_population[i]);
    }

};

GeneticAlgorithmSolver::~GeneticAlgorithmSolver() {};

GapSolution GeneticAlgorithmSolver::getSolution() {
    return this->_solution;
};

void GeneticAlgorithmSolver::printProgressBar(int iteration, int totalIterations, int barWidth) {
    float progress = static_cast<float>(iteration) / totalIterations;
    int progressWidth = static_cast<int>(progress * barWidth);

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < progressWidth)
            std::cout << "#";
        else
            std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(progress * 100.0) << "%\r";
    std::cout.flush();

    if (iteration == totalIterations)
        std::cout << std::endl;
};

void GeneticAlgorithmSolver::solve() {
     auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < this->_generations * this->_populationSize; i++)
    {
        this->_replacement();
        printProgressBar(i, this->_generations * this->_populationSize);
    }
    
    // Find best solution
    GapSolution bestSolution = this->_population[0];
    for (int p = 0; p < this->_populationSize; p++)
    {
        if(this->_population[p].getObjVal() < bestSolution.getObjVal()) {
            bestSolution = this->_population[p];
        }
    }
    this->_solution = bestSolution;
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    this->_solution.setTime(double(duration));

};

void GeneticAlgorithmSolver::_replacement() {
    // Choose parents
    GapSolution parent1 = this->_binaryTournament();
    GapSolution parent2 = this->_binaryTournament();

    // Crossover
    GapSolution child = this->_crossOver(parent1, parent2);

    // Mutation
    child = this->_mutation(child);

    // Improve quality of solution
    for (int j = 0; j < this->_instance.getN(); j++)
    {
        int min_store = this->_instance.getM()-1;
        float min_cost = 100000;

        for (int i = 0; i < this->_instance.getM()-1; i++)
        {
            if((this->_instance.getCost(i, j) < min_cost) && 
               (this->_solution.getRemainingCapacity(i) >= this->_instance.getDemand(i,j))) {
                min_store = i;
                min_cost = this->_instance.getCost(i, j);
            }
        }

        if(!(min_store == this->_instance.getM()-1)){   
            if(this->_solution.getStoreAssigned(j) != this->_instance.getM()-1) {
                this->_solution.unassign(this->_solution.getStoreAssigned(j), j);
            }

            this->_solution.assign(min_store, j);
        }
          
    }

    //  Check identical solutions in population
    for (int i = 0; i < this->_populationSize; i++)
    {
        if (this->_population[i] == child) {
            return;
        }
    }
    
    // Update population
    float highestUnfitness = 0;
    float highestFitness = 0;
    int highestUnfitnessIndex = 0;
    int highestFitnessIndex = 0;
    for(int p=0; p<this->_populationSize; p++) {
        if (this->_unfitness[p] > highestUnfitness) {
            highestUnfitness = this->_unfitness[p];
            highestUnfitnessIndex = p;
        }
        if(this->_fitness[p] > highestFitness) {
            highestFitness = this->_fitness[p];
            highestFitnessIndex = p;
        }
    }


    if(highestUnfitness != 0) {
        this->_population[highestUnfitnessIndex] = child;
        this->_unfitness[highestUnfitnessIndex] = this->_unfitnessFunction(child);
        this->_fitness[highestUnfitnessIndex] = child.getObjVal();
    } else if (child.getObjVal() < highestFitness) {
        // std::cout << "Child solution inserted: " << child.getObjVal() << std::endl;
        this->_population[highestFitnessIndex] = child;
        this->_unfitness[highestFitnessIndex] = this->_unfitnessFunction(child);
        this->_fitness[highestFitnessIndex] = child.getObjVal();
    }
}

float GeneticAlgorithmSolver::_unfitnessFunction(GapSolution solution) {
    float unfitness = 0;
    for (int i = 0; i < this->_instance.getM()-1; i++) {
        int capacity = this->_instance.getCapacity(i);
        int used = 0;

        // Podria usarse remainingCapacity creo
        for (int j = 0; j < this->_instance.getN(); j++) {
            if (solution.getStoreAssigned(j) == i) {
                used += this->_instance.getDemand(i, j);
            }
        }
        unfitness += std::max(0, used - capacity);
    }
    return unfitness;
}

GapSolution GeneticAlgorithmSolver::_binaryTournament() {
    int i = this->_randGen() % this->_populationSize;
    int j = this->_randGen() % this->_populationSize;
    if (this->_fitness[i] < this->_fitness[j]) {
        return this->_population[i];
    } else {
        return this->_population[j];
    }
}

GapSolution GeneticAlgorithmSolver::_crossOver(GapSolution parent1, GapSolution parent2) {
    GapSolution child = GapSolution(this->_instance);
    int p = this->_randGen() % this->_instance.getN();

    // Assign first p stores from parent1, rest from parent2
    for (int j = 0; j < p; j++) {
        if(parent1.isSellerAssign(j)) {
            child.assign(parent1.getStoreAssigned(j), j);
        }
    }
    for (int j = p; j < this->_instance.getN(); j++) {
        if(parent2.isSellerAssign(j)) {
            child.assign(parent2.getStoreAssigned(j), j);
        }
    }

    return child;
}

GapSolution GeneticAlgorithmSolver::_mutation(GapSolution solution) {
    int j1 = this->_randGen() % this->_instance.getN();
    int j2 = this->_randGen() % this->_instance.getN();

    if (j1 == j2) {
        return solution;
    }

    int store1 = solution.getStoreAssigned(j1);
    int store2 = solution.getStoreAssigned(j2);

    // Swap stores assigned to j1 and j2
    if (solution.isSellerAssign(j1)) {
        solution.unassign(store1, j1);
    }
    if (solution.isSellerAssign(j2)) {
        solution.unassign(store2, j2);
    }

    if (store1 != this->_instance.getM()-1 ) {
        solution.assign(store1, j2);
    }
    if (store2 != this->_instance.getM()-1 ) {
        solution.assign(store2, j1);
    }

    // solution.assign(store1, j2);
    // solution.assign(store2, j1);
    return solution;
}
