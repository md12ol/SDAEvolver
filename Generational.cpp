#include <iostream>
#include "SDA.h"
#include <bits/stdc++.h>

using namespace std;

double genCalcFitness(SDA &member);
int genPrintPopFits(ostream &outStrm, vector<double> &popFits);
bool genCompareFitness(int popIdx1, int popIdx2);
vector<int> genTournSelect(int size, bool decreasing);
int genMatingEvent(SDA *currentPop, SDA *newPop);

int genSDANumChars = 2;
int genSDAResponseLength = 2;
int genPopSize = 100;
int genTournSize = 7;
int tournCandidates = 4;
int tournMaxRepeats = 10;
int elitism = 2;
bool genLowerBetter = false;
double genMutationRate = 0.1;
int numGenerations = 100;
int genNumMutations = 1;

vector<double> genPopFits;

/**
 * Generates the next generation's population by performing tournament selection on currentPop,
 * crossover on copies of members of random members of the tournament, and potentially mutation of these
 * copies.  The new population is stored in newPop.
 *
 * @param currentPop the current generation's population
 * @param newPop the next generation's population
 * @return
 */
int genMatingEvent(SDA *currentPop, SDA *newPop) {
    // Tournament Selection
    vector<int> tournIdxs = genTournSelect(genTournSize, genLowerBetter);
    SDA parent1, parent2, child1, child2;

    for (int event = elitism; event < genPopSize; event += 2) {
        do {
            parent1 = currentPop[tournIdxs[(int) lrand48() % genTournSize]];
            parent2 = currentPop[tournIdxs[(int) lrand48() % genTournSize]];
        } while (parent1 == parent2); // TODO: Ensure this check works

        child1.copy(parent1);
        child2.copy(parent2);

        // Crossover
        child1.crossover(child2);

        // Mutation
        if (drand48() < genMutationRate) {
            child1.mutate(genNumMutations);
            child2.mutate(genNumMutations);
        }

        // Add to new population
        newPop[event] = child1;
        newPop[event + 1] = child2;

        // Calculate fitness
        genPopFits[event] = genCalcFitness(child1);
        genPopFits[event + 1] = genCalcFitness(child2);
    }
    return 0;
}

/**
 * Performs a tournament selection deciding which members from the population, of the
 * current generation, are candidates for creating the next generation's population.
 * The indices are sorted by their fitness, depending on the value of decreasing.
 * Can be used to sort the entire population if size == popSize.
 *
 * @param size of the returned vector of indices from the tournament selection
 * @param decreasing is a boolean determining the ordering of the indices in the returned vector based on their fitness
 * @return a vector of indices for members of the population sorted based on fitness
 */
vector<int> genTournSelect(int size, bool decreasing) {
    vector<int> tournIdxs;
    int idxToAdd, idxToCheck;

    tournIdxs.reserve(size);
    // If we want to sort the population, we call tournSelect with size == popsize
    if (size == genPopSize) {
        for (int idx = 0; idx < size; idx++) {
            tournIdxs.push_back(idx);
        }
    } else {
        // For each member we want to add to the tournament
        for (int mem = 0; mem < size; mem++) {
            // Find an index that's not in the tournament tournMaxRepeats times
            do {
                idxToAdd = (int) lrand48() % genPopSize;
            } while (count(tournIdxs.begin(), tournIdxs.end(), idxToAdd) >= tournMaxRepeats);

            // Compare this index to tournCandidates - 1 other indexes
            for (int check = 1; check < tournCandidates; check++) {
                // Find an index that's not in the tournament tournMaxRepeats times
                do {
                    idxToCheck = (int) lrand48() % genPopSize;
                } while (count(tournIdxs.begin(), tournIdxs.end(), idxToCheck) >= tournMaxRepeats);

                // If this test index has better fitness, replace the index to add with it
                if ((genPopFits[idxToCheck] > genPopFits[idxToAdd] && !genLowerBetter) ||
                    (genPopFits[idxToCheck] < genPopFits[idxToAdd] && genLowerBetter)) {
                    idxToAdd = idxToCheck;
                }
            }

            // Add the index to the tournament
            tournIdxs.push_back(idxToAdd);
        }
    }

    // Sort the indexes, default is ascending
    sort(tournIdxs.begin(), tournIdxs.end(), genCompareFitness);
    // Flip the sort to descending
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
bool genCompareFitness(int popIdx1, int popIdx2) {
    if (genPopFits[popIdx1] <= genPopFits[popIdx2]) {
        return true;
    }
    if (genPopFits[popIdx1] > genPopFits[popIdx2]) {
        return false;
    }
    cout << "ERROR: compare fitness not working as intended!" << endl;
    return false;
}

double genCalcFitness(SDA &member){
    // KEVINDO: (Later) complete fitness functions.

    // Temporary fitness function to test the evolutionary algorithm
    int val = 0;
    for (vector<vector<int>> stateResp : member.getResponses()){
        for (vector<int> transResp: stateResp){
            for (int resp: transResp){
                val += resp;
            }
        }
    }
    return val;
}

int genPrintPopFits(ostream &outStrm, vector<double> &popFits) {
    outStrm << "Fitness Values: ";
    int count = 0;
    bool first = true;
    for (double fit: popFits) {
        // This ensures commas after each fitness value other than the last
        if (!first) {
            outStrm << ", ";
        }
        outStrm << fit;
        if (fit > 150){
            count++;
        }
        first = false;
    }
    outStrm << "\n";
    outStrm << "Above 0.5: " << count << "\n";
    return 0;
}

int genEvolver(int SDANumStates, int SDAOutputLen, int numGenerations) {
    SDA *currentPop, *newPop;
    currentPop = new SDA[genPopSize];
    newPop = new SDA[genPopSize];
    genPopFits.reserve(genPopSize);

    // Step 1: initialize the population
    for (int i = 0; i < genPopSize; ++i) {
        currentPop[i] = SDA(SDANumStates, genSDANumChars, genSDAResponseLength, SDAOutputLen);
        newPop[i] = SDA(SDANumStates, genSDANumChars, genSDAResponseLength, SDAOutputLen);
        genPopFits.push_back(genCalcFitness(currentPop[i]));
    }

    genPrintPopFits(cout, genPopFits);

    // Step 2: Evolution
    for (int gen = 0; gen < numGenerations; ++gen) {
        // Keep the most elite members
        vector<int> sortedIdxs = genTournSelect(genPopSize, genLowerBetter);
        vector<double> oldFits;
        for (int elite = 0; elite < elitism; ++elite) {
            newPop[elite].copy(currentPop[sortedIdxs[elite]]);
            oldFits.push_back(genPopFits[sortedIdxs[elite]]);
        }
        // Store the fitness of the most elite members in popFits
        for (int mem = 0; mem < elitism; mem++){
            genPopFits[mem] = oldFits[mem];
        }

        // Generate the new population
        genMatingEvent(currentPop, newPop);

        // Replace current population with new population
        for (int mem = 0; mem < genPopSize; mem++){
            currentPop[mem] = newPop[mem];
        }
        genPrintPopFits(cout, genPopFits);
    }
    genPrintPopFits(cout, genPopFits);
    return 0;
}

int Generational() {
    genEvolver(100, 10, 20);
    return 0;
}