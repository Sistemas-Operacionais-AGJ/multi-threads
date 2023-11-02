#include "Cozinha.h"
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

int main(){
    Cozinha cozinha;

    // Acredito que no começo do restaurante as comidas estão todas prontas
  cozinha.setSalad(1);
  cozinha.setDessert(1);
  cozinha.setRice(1);
  cozinha.setBean(1);
  cozinha.setComplement(1);
  cozinha.setMeat(1);
    // setando elas
  int salad = cozinha.getSalad();
  int dessert = cozinha.getDessert();
  int rice = cozinha.getRice();
  int bean = cozinha.getBean();
  int complement = cozinha.getComplement();
  int meat = cozinha.getMeat();



}