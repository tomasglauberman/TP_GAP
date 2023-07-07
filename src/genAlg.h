#ifndef GEN_ALG_H
#define GEN_ALG_H

#include "gap_instance.h"
#include "gap_solution.h"
#include "greedy1.h"
#include "vnd.h"
#include <chrono>
#include <vector>
#include <random>



class GeneticAlgorithmSolver  {
    public:
    GeneticAlgorithmSolver();
    GeneticAlgorithmSolver(GapInstance instance, int populationSize, int generations, int seed=1);
    ~GeneticAlgorithmSolver();
    void solve();
    GapSolution getSolution();


    private:
    GapInstance _instance;
    GapSolution _solution;
    int _populationSize;
    int _generations;
    std::vector<GapSolution> _population;
    std::vector<float> _fitness;
    std::vector<float> _unfitness;

    void _replacement();
    float _unfitnessFunction(GapSolution solution);
    GapSolution _binaryTournament();
    GapSolution _crossOver(GapSolution parent1, GapSolution parent2);
    GapSolution _mutation(GapSolution child);
    void printProgressBar(int iteration, int totalIterations, int barWidth = 50);
    std::mt19937 _randGen;

};

#endif