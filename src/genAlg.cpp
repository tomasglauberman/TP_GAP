#include "genAlg.h"

GeneticAlgorithmSolver::GeneticAlgorithmSolver() {}

GeneticAlgorithmSolver::GeneticAlgorithmSolver(GapInstance instance, int populationSize, int generations) {
    this->_instance = instance;
    this->_solution = GapSolution(instance);

    this->_populationSize = populationSize;
    this->_generations = generations;
    this->_population = std::vector<GapSolution>(populationSize);
    this->_fitness = std::vector<float>(populationSize);
    this->_unfitness = std::vector<float>(populationSize);

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

void GeneticAlgorithmSolver::solve() {
    for (int i = 0; i < this->_generations * this->_populationSize; i++)
    {
        this->_replacement();
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

};


void GeneticAlgorithmSolver::_replacement() {
        // Choose parents
    GapSolution parent1 = this->_binaryTournament();
    GapSolution parent2 = this->_binaryTournament();

    // Crossover
    GapSolution child = this->_crossOver(parent1, parent2);

    // Mutation
    child = this->_mutation(child);

    // Improve feasibility
    for (int i = 0; i < this->_instance.getM()-1; i++)
    {
        int remaining_capacity = child.getRemainingCapacity(i);
        if (remaining_capacity < 0) {
            // Choose first seller assigned to i and assign it to first store with capacity
            for (int j = 0; j < this->_instance.getN(); j++)
            {
                if (child.getStoreAssigned(j) == i) {
                    child.unassign(i, j);
                    for (int i2 = 0; i2 < this->_instance.getM()-1; i2++)
                    {
                        if(child.getRemainingCapacity(i2) > 0) {
                            child.assign(i2, j);
                            goto next;
                            
                        }
                    }
                }
            }
        }
        next:
        continue;
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


    //  Check identical solutions in population

    if(highestUnfitness != 0) {
        this->_population[highestUnfitnessIndex] = child;
        this->_unfitness[highestUnfitnessIndex] = this->_unfitnessFunction(child);
        this->_fitness[highestUnfitnessIndex] = child.getObjVal();
    } else {
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
    int i = rand() % this->_populationSize;
    int j = rand() % this->_populationSize;
    if (this->_fitness[i] < this->_fitness[j]) {
        return this->_population[i];
    } else {
        return this->_population[j];
    }
}

GapSolution GeneticAlgorithmSolver::_crossOver(GapSolution parent1, GapSolution parent2) {
    GapSolution child = GapSolution(this->_instance);
    int p = rand() % this->_instance.getN();

    // Assign first p stores from parent1, rest from parent2
    for (int j = 0; j < p; j++) {
        child.assign(parent1.getStoreAssigned(j), j);
    }
    for (int j = p; j < this->_instance.getN(); j++) {
        child.assign(parent2.getStoreAssigned(j), j);
    }

    return child;
}

GapSolution GeneticAlgorithmSolver::_mutation(GapSolution solution) {
    int j1 = rand() % this->_instance.getN();
    int j2 = rand() % this->_instance.getN();

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

    solution.assign(store1, j2);
    solution.assign(store2, j1);
    return solution;
}