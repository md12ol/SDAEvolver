#include <iostream>
#include "SDA.h"

using namespace std;

double calcFitness(SDA &member);
int printPopFits(ostream &outStrm, vector<double> &popFits);

int SDANumChars = 2;
int SDAResponseLength = 2;

int evolver(int popsize, int SDANumStates, int SDAOutputLen){
    SDA* population;
    population = new SDA[popsize];
    vector <double> popFits(popsize);

    for (int i = 0; i < popsize; ++i) {
        population[i] = SDA(SDANumStates, SDANumChars, SDAResponseLength, SDAOutputLen);
        popFits[i] = calcFitness(population[i]);
    }

    printPopFits(cout, popFits);

    delete[] population;
    return 0;
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

int main() {
    evolver(100, 10, 20);
    return 0;
}

void testing(){
        int outputLen = 20;
    int numStates = 3;
    int numChars = 2;

    SDA firstSDA(numStates, numChars, 2, outputLen, 0, true);
    SDA secondSDA(numStates, numChars, 2, outputLen, 0, true);
    vector<int> firstOutput;
    vector<int> secondOutput;
    firstOutput.reserve(outputLen);
    secondOutput.reserve(outputLen);

    cout << "First SDA:" << endl;
    firstSDA.print(cout);
    firstSDA.fillOutput(firstOutput, true, cout);
    cout << "Second SDA:" << endl;
    secondSDA.print(cout);
    secondSDA.fillOutput(secondOutput, true, cout);

    firstSDA.crossover(secondSDA);

    cout << "First SDA:" << endl;
    firstSDA.print(cout);
    firstSDA.fillOutput(firstOutput, true, cout);
    firstSDA.mutate(2);
    cout << "First SDA:" << endl;
    firstSDA.print(cout);
    firstSDA.fillOutput(firstOutput, true, cout);

    cout << "Second SDA:" << endl;
    secondSDA.print(cout);
    secondSDA.fillOutput(secondOutput, true, cout);
    secondSDA.mutate(2);
    cout << "Second SDA:" << endl;
    secondSDA.print(cout);
    secondSDA.fillOutput(secondOutput, true, cout);
}