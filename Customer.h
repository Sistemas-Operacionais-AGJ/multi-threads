#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <random>
#include <vector>
using namespace std;

class Customer {
public:
  Customer()
      : gen(rd()), dis(0.0, 1.0), itemsTaken(6, 0.0f),
        chanceToTake({0.8, 0.6, 0.8, 0.7, 0.4, 0.9}),
        varianceToTake({0.1, 0.1, 0.3, 0.2, 0.2, 0.05}),
        quantityToTake({0.03, 0.08, 0.1, 0.07, 0.1, 0.08}),
        varianceQuantity({0.02, 0.000001, 0.003, 0.002, 0.005, 0.01}) {}

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
  void takeItems(int index);

  void setItemsTaken(int index, float value);
  vector<float> getItemsTaken() const;
  // void getItemsTaken(vector<float>& result) const;

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