#ifndef BUFFET_H
#define BUFFET_H

#include <vector>
using namespace std;
class Buffet {
private:
    vector<float> buffet;

public:
    Buffet();  // Constructor declaration
    void setBuffet(int index, float value);
    vector<float> getBuffet();
    void printBuffet();
    void setBuffetCustomer(const vector<float>& newBuffet);
};

#endif  // BUFFET_H