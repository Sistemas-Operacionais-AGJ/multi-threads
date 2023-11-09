#include "Kitchen.h"
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

// números aleatórios
random_device rd;
mt19937 gen(rd());

// getters

int Kitchen::getSalad() { return readyForDelivery[0]; }

int Kitchen::getDessert() { return readyForDelivery[1]; }
int Kitchen::getRice() { return readyForDelivery[2]; }

int Kitchen::getBean() { return readyForDelivery[3]; }

int Kitchen::getComplement() { return readyForDelivery[4]; }

int Kitchen::getMeat() { return readyForDelivery[5]; }

// Setters

void Kitchen::setSalad(int valor) { readyForDelivery[0] = valor; }

void Kitchen::setDessert(int valor) { readyForDelivery[1] = valor; }

void Kitchen::setRice(int valor) { readyForDelivery[2] = valor; }

void Kitchen::setBean(int valor) { readyForDelivery[3] = valor; }

void Kitchen::setComplement(int valor) { readyForDelivery[4] = valor; }

void Kitchen::setMeat(int valor) { readyForDelivery[5] = valor; }

// preparo de itens
void Kitchen::cookingItems(int food) {

  if (readyForDelivery[food] == 0) {
    int min = productionTimeVariance[food] * -1;
    int max = productionTimeVariance[food];
    uniform_int_distribution<int> dist(min, max);
    this_thread::sleep_for(chrono::seconds(productionTime[food] + dist(gen)));
    readyForDelivery[food] = 1;
  }
}

// entrega de itens
int Kitchen::deliveryItems(int food) {
  if (readyForDelivery[food] == 0) {
    return 0;
  } else {
    return 1;
  }
}