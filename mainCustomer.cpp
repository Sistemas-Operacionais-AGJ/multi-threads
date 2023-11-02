#include "Customer.h"
using namespace std;

float Customer::getChanceToTake(int index) const {
    return chanceToTake[index];
}

void Customer::setChanceToTake(int index, float value) {
    chanceToTake[index] = value;
}

float Customer::getVarianceToTake(int index) const {
    return varianceToTake[index];
}

void Customer::setVarianceToTake(int index, float value) {
    varianceToTake[index] = value;
}

float Customer::getQuantityToTake(int index) const {
    return quantityToTake[index];
}

void Customer::setQuantityToTake(int index, float value) {
    quantityToTake[index] = value;
}

float Customer::getVarianceQuantity(int index) const {
    return varianceQuantity[index];
}

void Customer::setVarianceQuantity(int index, float value) {
    varianceQuantity[index] = value;
}

bool Customer::decideToTakeItem(int index) const {
    float randomValue = dis(gen);
    return randomValue <= (chanceToTake[index] + varianceToTake[index]);
}

float Customer::determineQuantityToTake(int index) const {
    float baseQuantity = quantityToTake[index];
    float randomVariance = varianceQuantity[index] * (2.0 * dis(gen) - 1.0);
    return baseQuantity + randomVariance;
}

float Customer::getItemsTaken(int index) const {
    return varianceQuantity[index];
}

void Customer::setItemsTaken(int index, float value) {
    itemsTaken[index] = value;
}

float Customer::takeItems(int index) {
    if (decideToTakeItem(index)) {
        setItemsTaken(index, determineQuantityToTake(index));

    } else {
        setItemsTaken(index, 0.0);
    } 
}
