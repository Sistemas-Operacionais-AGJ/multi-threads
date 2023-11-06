


#include "Buffet.h"
#include <iostream>
using namespace std;
#include <vector>

Buffet::Buffet() {
    // Initialize the buffet with default values
    buffet = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
}

void Buffet::setBuffet(int index, float value){
        buffet[index] = value;
}

void Buffet::setBuffetCustomer(const vector<float>& newBuffet) {
    buffet = newBuffet;
}

vector<float> Buffet::getBuffet() {
    return buffet;
}

void Buffet::printBuffet() {
    for (int i = 0; i < 6; i++) {
        cout << buffet[i] <<  " ";
    }
    cout << endl;
}
