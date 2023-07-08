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
        // Random random = Random(instance);
        // random.solve();
        // this->_population[i] = random.getSolution();
        this->_population[i] = GapSolution::randomSolution(instance, i);
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
        if(this->_population[p].getObjVal() < bestSolution.getObjVal() && this->_population[p].checkFeasibility(this->_instance)) {
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

    // Improve feasibility of solution
    // for (int i = 0; i < this->_instance.getM()-1; i++)
    // {
    //     if (child.getRemainingCapacity(i) < 0)
    //     {
    //         for (int j = 0; j < this->_instance.getN(); j++)
    //         {
    //             if (child.getStoreAssigned(j) == i)
    //             {
    //                 child.unassign(i, j);
    //                 for (int k = 0; k < this->_instance.getM()-1; k++)
    //                 {
    //                     if (child.getRemainingCapacity(k) >= this->_instance.getDemand(k, j))
    //                     {
    //                         child.assign(k, j);
    //                         goto next;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     next:
    //     continue;

    // }

    // Improve quality of solution
    for (int j = 0; j < this->_instance.getN(); j++)
    {
        int min_store = this->_instance.getM()-1;
        float min_cost = 100000;

        for (int i = 0; i < this->_instance.getM()-1; i++)
        {
            if((this->_instance.getCost(i, j) < min_cost) && 
               (child.getRemainingCapacity(i) >= this->_instance.getDemand(i,j))) {
                min_store = i;
                min_cost = this->_instance.getCost(i, j);
            }
        }

        if(!(min_store == this->_instance.getM()-1)){   
            if(child.getStoreAssigned(j) != this->_instance.getM()-1) {
                child.unassign(child.getStoreAssigned(j), j);
            }

            child.assign(min_store, j);
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
    } else {
        this->_population[highestFitnessIndex] = child;
        this->_unfitness[highestFitnessIndex] = this->_unfitnessFunction(child);
        this->_fitness[highestFitnessIndex] = child.getObjVal();
    }

    // std::cout << "Inserted solution: " << child.getObjVal() << std::endl;
}

float GeneticAlgorithmSolver::_unfitnessFunction(GapSolution solution) {
    float unfitness = 0;
    for (int i = 0; i < this->_instance.getM()-1; i++) {
        unfitness += std::max(0, -solution.getRemainingCapacity(i));
    }
    return unfitness;
}

GapSolution GeneticAlgorithmSolver::_binaryTournament() {
    std::uniform_int_distribution<int> dist(0, this->_populationSize-1);
    int i = dist(this->_randGen);
    int j = dist(this->_randGen);

    if (this->_fitness[i] < this->_fitness[j]) {
        return this->_population[i];
    } else {
        return this->_population[j];
    }
}

GapSolution GeneticAlgorithmSolver::_crossOver(GapSolution parent1, GapSolution parent2) {
    GapSolution child = GapSolution(this->_instance);
    std::uniform_int_distribution<int> dist(0, this->_instance.getN()-1);
    int p = dist(this->_randGen);

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
    std::uniform_int_distribution<int> dist(0, this->_instance.getN()-1);

    for (int s=0; s < 3; s++) {
        int j1 = dist(this->_randGen);
        int j2 = dist(this->_randGen);

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
    }

    // solution.assign(store1, j2);
    // solution.assign(store2, j1);
    return solution;
}
