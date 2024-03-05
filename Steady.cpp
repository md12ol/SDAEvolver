#include <iostream>
#include "SDA.h"
#include <bits/stdc++.h>

using namespace std;

double calcFitness(SDA &member);
int printPopFits(ostream &outStrm, vector<double> &popFits);
bool compareFitness(int popIdx1, int popIdx2);
vector<int> tournSelect(int size, bool decreasing);
int matingEvent(SDA* population);

int SDANumChars = 2;
int SDAResponseLength = 2;
int popSize;
int tournSize = 7;
bool lowerBetter = false;
double mutationRate = 0.1;
int numMutations = 1;

vector <double> popFits;

int evolver(int SDANumStates, int SDAOutputLen, int numMatingEvents){
    SDA* population;
    population = new SDA[popSize];
    popFits.reserve(popSize);

    // Step 1: initialize the population
    for (int i = 0; i < popSize; ++i) {
        population[i] = SDA(SDANumStates, SDANumChars, SDAResponseLength, SDAOutputLen);
        popFits[i] = calcFitness(population[i]);
    }

    printPopFits(cout, popFits);

    // Step 2: Evolution
    for (int gen = 0; gen < numMatingEvents; ++gen) {
        matingEvent(population);
    }

    // Step 3: Reporting
    printReport(cout, popFits, population);

    delete[] population;
    return 0;
}

/**
 * Performs a single mating event in the population by performing tournament selection,
 * crossover on copies of the two most-fit members of the tournament, and mutation of these
 * copies.  Afterwards, the two least-fit members of the tournament are replaced with
 * the mutated children.
 *
 * @param population the population undergoing evolution
 * @return
 */
int matingEvent(SDA* population){
    // Tournament Selection
    vector<int> tournIdxs = tournSelect(tournSize, lowerBetter);
    SDA parent1, parent2, child1, child2;
    parent1 = population[tournIdxs[0]];
    parent2 = population[tournIdxs[1]];
    child1.copy(parent1);
    child2.copy(parent2);

    // Crossover
    child1.crossover(child2);

    // Mutation
    child1.mutate(numMutations);
    child1.mutate(numMutations);

    // Update population with genrated children
    population[tournIdxs[tournSize - 1]] = child1;
    population[tournIdxs[tournSize - 2]] = child2;

    // Update fitness of worst two members of the tournament
    popFits[tournIdxs[tournSize-1]] = calcFitness(child1);
    popFits[tournIdxs[tournSize-2]] = calcFitness(child2); 
}

/**
 * Performs a tournament selection deciding which members from the population, of the
 * current generation, will undergo a mating event to produce the children that will
 * populate the new population for the next generation
 *
 * KEVINDO: Update to work with Steady
 *
 * @param size of the returned vector of indicies from the tournament selection
 * @param decreasing is a boolean determining the ordering of the indicies in the returned vector based on their fitness
 * @return a vector of indices for members of the population sorted based on fitness
 */
vector<int> tournSelect(int size, bool decreasing) {
    vector<int> tournIdxs;
    int idxToAdd;

    tournIdxs.reserve(size);
    // If we want to sort the population, we call tournSelect with size == popsize
    if (size == popSize) {
        for (int idx = 0; idx < size; idx++) {
            tournIdxs.push_back(idx);
        }
    } else {
        do {
            idxToAdd = (int) lrand48() % popSize;
            // If this index is not already in tournIdxs
            if (count(tournIdxs.begin(), tournIdxs.end(), idxToAdd) == 0) {
                // Then add it
                tournIdxs.push_back(idxToAdd);
            }
        } while (tournIdxs.size() < size);
    }

    sort(tournIdxs.begin(), tournIdxs.end(), compareFitness);
    if (decreasing) {
        reverse(tournIdxs.begin(), tournIdxs.end());
    }
    return tournIdxs;
}

/**
 * This method compares the fitness of two members of the population and returns a boolean determining
 * which member had the greatest fitness
 *
 * @param popIdx1 an index representing a member of the population
 * @param popIdx2 a second index representing a member of the population whos fitness is being compared to the previous member
 * @return a boolean determing which member had the greatest fitness
 */
bool compareFitness(int popIdx1, int popIdx2) {
    if (popFits[popIdx1] < popFits[popIdx2]) {
        return true;
    }
    if (popFits[popIdx1] > popFits[popIdx2]) {
        return false;
    }
    cout << "ERROR: compare fitness not working as intended!" << endl;
    return false;
}

double calcFitness(SDA &member){
    // KEVINDO: (Later) complete fitness functions.
    return drand48();
}

int printPopFits(ostream &outStrm, vector<double> &popFits) {
    outStrm << "Fitness Values: ";
    bool first = true;
    for (double fit: popFits) {
        // This ensures commas after each fitness value other than the last
        if (!first) {
            outStrm << ", ";
        }
        outStrm << fit;
        first = false;
    }
    outStrm << "\n";
    return 0;
}

/**
 * This method prints out the information of the best SDA
 * from the EA algorithm such as its fitness, the SDA, average fitness
 * and the best netowrk layout (Will come later when heurestic is complete)
 * 
 * @param outStrm is the designated output stream for the report
 * @param popFits is the vector holding the firness for the population
 * @param population is the population produced by the Genetic Algorithm
 * @return 
*/

int printReport(ostream &outStrm, vector<double> &popFits, SDA* population){
    double avgFit = 0;// Holds the average fitness
    int bestIdx = 0;// Stores the best member of populations location

    for (int x = 0; x < popFits.size(); x++){// For each entry
        avgFit += popFits[x];// Add to average sum
        if(popFits[bestIdx] < popFits[x]) bestIdx = x;// Get best population index
    }

    // Report the best SDA from GA
    outStrm << "Mutation Rate: " << mutationRate * 100 << "%" << endl;
    outStrm << "Best SDA: " << population[bestIdx].print(outStrm) << endl;
    outStrm << "Best Layout: " << "Coming Soon" << endl;
    outStrm << "Best Fitness: " << popFits[bestIdx] << endl;
    outStrm << "Average Fitness: " << avgFit/popFits.size() << endl;

    return 0;
}

int main() {
    evolver(100, 10, 20);
    return 0;
}