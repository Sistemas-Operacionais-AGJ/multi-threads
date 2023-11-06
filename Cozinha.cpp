#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include "Cozinha.h"

using namespace std;

// números aleatórios
random_device rd;
mt19937 gen(rd());

// Construtor, esta certo?
Cozinha::~Cozinha(){}

// getters

int Cozinha::getSalad(){
        return readyForDelivery[0];
}

int Cozinha::getDessert(){
        return readyForDelivery[1];
}
int Cozinha::getRice(){
        return readyForDelivery[2];
}

int Cozinha::getBean(){
        return readyForDelivery[3];
}

int Cozinha::getComplement(){
        return readyForDelivery[4];
}

int Cozinha::getMeat(){
        return readyForDelivery[5];
}

// Setters

void Cozinha::setSalad(int valor){
    readyForDelivery[0] = valor;
}

void Cozinha::setDessert(int valor){
    readyForDelivery[1] = valor;
}

void Cozinha::setRice(int valor){
    readyForDelivery[2] = valor;
}

void Cozinha::setBean(int valor){
    readyForDelivery[3] = valor;
}

void Cozinha::setComplement(int valor){
    readyForDelivery[4] = valor;
}

void Cozinha::setMeat(int valor){
    readyForDelivery[5] = valor;
}

// preparo de itens
void Cozinha::cookingItems(int food){

    if(readyForDelivery[food] == 0){
        int min = productionTimeVariance[food] * -1;
        int max = productionTimeVariance[food];
        uniform_int_distribution<int> dist(min, max);
        this_thread::sleep_for(chrono::seconds(productionTime[food]+dist(gen)));
        readyForDelivery[food] = 1;
    }

}

// entrega de itens
int Cozinha::deliveryItems(int food){
    if(readyForDelivery[food] == 0){
        return 0;
    }else{
        return 1;
    }