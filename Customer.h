#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <random>
using namespace std;

class Customer {
public:
    Customer(vector<float> chanceToTake, vector<float> varianceToTake,
                   vector<float> quantityToTake, vector<float> varianceQuantity) : gen(rd()), dis(0.0, 1.0){}

    float getChanceToTake(int index) const;
    void setChanceToTake(int index, float value);

    float getVarianceToTake(int index) const;
    void setVarianceToTake(int index, float value);

    float getQuantityToTake(int index) const;
    void setQuantityToTake(int index, float value);

    float getVarianceQuantity(int index) const;
    void setVarianceQuantity(int index, float value);

    bool decideToTakeItem(int index) const;
    float determineQuantityToTake(int index) const;
    float takeItems(int index) ;

    void setItemsTaken(int index, float value)  ;
    vector<float> getItemsTaken() const;

private:
    vector<float> chanceToTake;
    vector<float> varianceToTake;
    vector<float> quantityToTake;
    vector<float> varianceQuantity;
    vector<float> itemsTaken;

    random_device rd;
    mutable mt19937 gen;
    mutable uniform_real_distribution<float> dis;
};

#endif // CUSTOMER_H