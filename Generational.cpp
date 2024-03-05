#include <iostream>
#include "SDA.h"
#include <bits/stdc++.h>

using namespace std;

double calcFitness(SDA &member);
int printPopFits(ostream &outStrm, vector<double> &popFits);
bool compareFitness(int popIdx1, int popIdx2);
vector<int> tournSelect(int size, bool decreasing);
int matingEvent(SDA *population);

int SDANumChars = 2;
int SDAResponseLength = 2;
int popSize;
int tournSize = 7;
int tournCandidates = 4;
int tournMaxRepeats = 10;
int eliteism = 2;
bool lowerBetter = false;
double mutationRate = 0.1;
int numGenerations = 100;
int numMutations = 1;

vector<double> popFits;

int evolver(int SDANumStates, int SDAOutputLen, int numGenerations) {
    SDA *currentPop, *newPop;
    currentPop = new SDA[popSize];
    newPop = new SDA[popSize];
    popFits.reserve(popSize);

    // Step 1: initialize the population
    for (int i = 0; i < popSize; ++i) {
        currentPop[i] = SDA(SDANumStates, SDANumChars, SDAResponseLength, SDAOutputLen);
        popFits[i] = calcFitness(currentPop[i]);
    }

    printPopFits(cout, popFits);

    // Step 2: Evolution
    for (int gen = 0; gen < numGenerations; ++gen) {
        vector<int> sortedIdxs = tournSelect(popSize, lowerBetter);
        for (int elite = 0; elite < eliteism; ++elite) {
            newPop[elite] = currentPop[sortedIdxs[elite]];
        }
        matingEvent(currentPop);
    }
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
int matingEvent(SDA *population) {
    // Tournament Selection
    vector<int> tournIdxs = tournSelect(tournSize, lowerBetter);
    SDA parent1, parent2, child1, child2;

    for (int event = eliteism; event < popSize; event += 2){
        do {
            parent1 = population[tournIdxs[(int)lrand48() % tournSize]];
            parent2 = population[tournIdxs[(int)lrand48() % tournSize]];
        } while(parent1 != parent2); // TODO: Ensure this check works


    }
        parent1 = population[tournIdxs[0]];
    parent2 = population[tournIdxs[1]];
    child1.copy(parent1);
    child2.copy(parent2);

    // Crossover
    child1.crossover(child2);

    // Mutation
    child1.mutate(numMutations);
    child1.mutate(numMutations);
}

/**
 * Performs a tournament selection deciding which members from the population, of the
 * current generation, will undergo a mating event to produce the children that will
 * populate the new population for the next generation
 *
 * @param size of the returned vector of indicies from the tournament selection
 * @param decreasing is a boolean determining the ordering of the indicies in the returned vector based on their fitness
 * @return a vector of indices for members of the population sorted based on fitness
 */
vector<int> tournSelect(int size, bool decreasing) {
    vector<int> tournIdxs;
    int idxToAdd, idxToCheck;

    tournIdxs.reserve(size);
    // If we want to sort the population, we call tournSelect with size == popsize
    if (size == popSize) {
        for (int idx = 0; idx < size; idx++) {
            tournIdxs.push_back(idx);
        }
    } else {
        // For each member we want to add to the tournament
        for (int mem = 0; mem < size; mem++) {
            // Find an index that's not in the tournament tournMaxRepeats times
            do {
                idxToAdd = (int) lrand48() % popSize;
            } while (count(tournIdxs.begin(), tournIdxs.end(), idxToAdd) >= tournMaxRepeats);

            // Compare this index to tournCandidates - 1 other indexes
            for (int check = 1; check < tournCandidates; check++) {
                // Find an index that's not in the tournament tournMaxRepeats times
                do {
                    idxToCheck = (int) lrand48() % popSize;
                } while (count(tournIdxs.begin(), tournIdxs.end(), idxToCheck) >= tournMaxRepeats);

                // If this test index has better fitness, replace the index to add with it
                if ((popFits[idxToCheck] > popFits[idxToAdd] && !lowerBetter) ||
                    (popFits[idxToCheck] < popFits[idxToAdd] && lowerBetter)) {
                    idxToAdd = idxToCheck;
                }
            }

            // Add the index to the tournament
            tournIdxs.push_back(idxToAdd);
        }
    }

    // Sort the indexes, default is ascending
    sort(tournIdxs.begin(), tournIdxs.end(), compareFitness);
    // Flip the sort to descending
    if (decreasing) {
        reverse(tournIdxs.begin(), tournIdxs.end());
    }
    return tournIdxs;
}

double calcFitness(SDA &member) {
    // KEVINDO: (Later) complete fitness functions.
    return drand48();
}

int main() {
    evolver(100, 10, 20);
    return 0;
}