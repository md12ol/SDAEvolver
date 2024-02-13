#include <iostream>
#include "SDA.h"

using namespace std;

int main() {
    int outputLen = 20;

    SDA firstSDA(10, 3, 2, outputLen);
    SDA secondSDA(10, 3, 2, outputLen);
    vector<int> firstOutput;
    vector<int> secondOutput;
    firstOutput.reserve(outputLen);
    secondOutput.reserve(outputLen);

    firstSDA.fillOutput(firstOutput, true, cout);
    secondSDA.fillOutput(secondOutput, true, cout);

    firstSDA.crossover(secondSDA);

    firstSDA.fillOutput(firstOutput, true, cout);
    secondSDA.fillOutput(secondOutput, true, cout);
    return 0;
}