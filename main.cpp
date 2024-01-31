#include <iostream>
#include "SDA.h"

using namespace std;

int main() {
    SDA tom(10, 3, 2, 20);
    vector<int> tomsOpinions;
    tomsOpinions.reserve(20);

    tom.fillOutput(tomsOpinions, true, cout);

    tom.randomize();
    return 0;
}