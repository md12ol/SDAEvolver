#include <iostream>
#include "SDA.h"
#include "Topology.h"
#include <bits/stdc++.h>

using namespace std;

void testing(){

    int outputLen = 20;
    int numStates = 3;
    int numChars = 2;

    cout << "stuff worked" << endl;

    Topology T;

    exit(1);

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

int main() {
    testing();
    return 0;
}