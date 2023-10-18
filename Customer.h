#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <random>

class Customer {
public:
    Customer(std::vector<float> chanceToTake, std::vector<float> varianceToTake,
             std::vector<float> quantityToTake, std::vector<float> varianceQuantity);

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
    float takeItems(int index) const;

private:
    std::vector<float> chanceToTake;
    std::vector<float> varianceToTake;
    std::vector<float> quantityToTake;
    std::vector<float> varianceQuantity;

    std::random_device rd;
    mutable std::mt19937 gen;
    mutable std::uniform_real_distribution<float> dis;
};

#endif // CUSTOMER_H