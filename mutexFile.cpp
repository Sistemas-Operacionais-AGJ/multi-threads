#include "Kitchen.h"
#include "Customer.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>
#include "Buffet.h"

#include <vector>

//g++ -o myprogram texiste.cpp Kitchen.cpp Buffet.cpp Customer.cpp -lpthread 
// salada, sobremesa, arroz, feijao, complemento e carne
// vector<float> chanceToTake = {0.8, 0.6, 0.8, 0.7, 0.4, 0.9};
// vector<float> varianceToTake = {0.1, 0.1, 0.3, 0.2, 0.2, 0.05};
// vector<float> quantityToTake = {0.03, 0.08, 0.1, 0.07, 0.1, 0.08};
// vector<float> varianceQuantity = {0.02, 0.000001, 0.003, 0.002, 0.005, 0.01};

sem_t fullSalad, fullDessert, fullRice, fullBean, fullComplement, fullMeat;
sem_t emptySalad, emptyDessert, emptyRice, emptyBean, emptyComplement, emptyMeat;
sem_t mutexSalad, mutexDessert, mutexRice, mutexBean, mutexComplement, mutexMeat;

#define N 6
volatile int buffer[N];
volatile int count;

Buffet buffet;

void *produtorSalad(void *arg) {
  Kitchen kitchen;
  bool allGreater;
  for (int i = 0; i < 5000; i++) {
    kitchen.cookingItems(0);
    vector<float> tempBuffet = buffet.getBuffet();
    while(allGreater == false){
        if(tempBuffet[0] == 1){
          allGreater = false;
        } else {
          allGreater = true;
          break;
        }
      }
    sem_wait(&emptySalad);
    sem_wait(&mutexSalad);
    buffet.setBuffet(0, 1.0);
    printf("Salada Feita\n");
    sem_post(&fullSalad);
    sem_post(&mutexSalad);
  }
  return NULL;
}

void *produtorDessert(void *arg) {
  Kitchen kitchen;
  bool allGreater;
  for (int i = 0; i < 5000; i++) {
    kitchen.cookingItems(1);
    vector<float> tempBuffet = buffet.getBuffet();
    while(allGreater == false){
        if(tempBuffet[1] == 1){
          allGreater = false;
        } else {
          allGreater = true;
          break;
        }
      }
    sem_wait(&emptyDessert);
    sem_wait(&mutexDessert);
    buffet.setBuffet(1, 1.0);
    printf("Sobremesa Feita\n");
    sem_post(&fullDessert);
    sem_post(&mutexDessert);
  }
  return NULL;
}

void *produtorRice(void *arg) {
  Kitchen kitchen;
  bool allGreater;
  for (int i = 0; i < 5000; i++) {
    kitchen.cookingItems(2);
    vector<float> tempBuffet = buffet.getBuffet();
    while(allGreater == false){
        if(tempBuffet[2] == 1){
          allGreater = false;
        } else {
          allGreater = true;
          break;
        }
      }
    sem_wait(&emptyRice);
    sem_wait(&mutexRice);
    buffet.setBuffet(2, 1.0);
    printf("Arroz Feito\n");
    sem_post(&fullRice);
    sem_post(&mutexRice);
  }
  return NULL;
}

void *produtorBean(void *arg) {
  Kitchen kitchen;
  bool allGreater;
  for (int i = 0; i < 5000; i++) {
    kitchen.cookingItems(3);
    vector<float> tempBuffet = buffet.getBuffet();
    while(allGreater == false){
        if(tempBuffet[3] == 1){
          allGreater = false;
        } else {
          allGreater = true;
          break;
        }
      }
    sem_wait(&emptyBean);
    sem_wait(&mutexBean);
    buffet.setBuffet(3, 1.0);
    printf("Feijão Feito\n");
    sem_post(&fullBean);
    sem_post(&mutexBean);
  }
  return NULL;
}

void *produtorComplement(void *arg) {
  Kitchen kitchen;
  bool allGreater;
  for (int i = 0; i < 5000; i++) {
   kitchen.cookingItems(4);
    vector<float> tempBuffet = buffet.getBuffet();
    while(allGreater == false){
        if(tempBuffet[4] == 1){
          allGreater = false;
        } else {
          allGreater = true;
          break;
        }
      }
    sem_wait(&emptyComplement);
    sem_wait(&mutexComplement);
    buffet.setBuffet(4, 1.0);
    printf("Complemento Feito\n");
    sem_post(&fullComplement);
    sem_post(&mutexComplement);
  }
  return NULL;
}

void *produtorMeat(void *arg) {
  Kitchen kitchen;
  bool allGreater;
  for (int i = 0; i < 5000; i++) {
    kitchen.cookingItems(5);
    vector<float> tempBuffet = buffet.getBuffet();
    while(allGreater == false){
        if(tempBuffet[5] == 1){
          allGreater = false;
        } else {
          allGreater = true;
          break;
        }
      }
    sem_wait(&emptyMeat);
    sem_wait(&mutexMeat);
    buffet.setBuffet(5, 1.0);
    printf("Carne Feita\n");
    sem_post(&fullMeat);
    sem_post(&mutexMeat);
  }
  return NULL;
}

void *consumidorTeste(void *arg) {

  for (int i = 0; i < 5000; i++) {
    Customer cliente;
    for (int j = 0; j < 6; j++) {
      cliente.takeItems(j);
    }
    vector<float> tempBuffet;
    vector<float> tempConsumo;
    sem_wait(&fullSalad);
    sem_wait(&mutexSalad);
    buffet.printBuffet();
    tempBuffet = buffet.getBuffet();
    tempConsumo = cliente.getItemsTaken();
    if(tempBuffet > tempConsumo) {
      tempBuffet[0] = tempBuffet[0] - tempConsumo[0];
    } else {
      tempBuffet[0] = 0;
    }
    
    
    buffet.setBuffet(0, tempBuffet[0]);
    cout << "Consumiu Salada" << endl;
    
    sem_post(&mutexSalad);
    sem_post(&emptySalad);


    sem_wait(&fullDessert);
    sem_wait(&mutexDessert);
    buffet.printBuffet();
    tempBuffet = buffet.getBuffet();
    tempConsumo = cliente.getItemsTaken();
    if(tempBuffet > tempConsumo) {
      tempBuffet[1] = tempBuffet[1] - tempConsumo[1];
    } else {
      tempBuffet[1] = 0;
    }
    buffet.setBuffet(1, tempBuffet[1]);
    cout << "Consumiu Sobremesa" << endl;
    sem_post(&mutexDessert);
    sem_post(&emptyDessert);

    sem_wait(&fullRice);
    sem_wait(&mutexRice);
    buffet.printBuffet();
    tempBuffet = buffet.getBuffet();
    tempConsumo = cliente.getItemsTaken();
    if(tempBuffet > tempConsumo) {
      tempBuffet[2] = tempBuffet[2] - tempConsumo[2];
    } else {
      tempBuffet[2] = 0;
    }
    
    buffet.setBuffet(2, tempBuffet[2]);
    cout << "Consumiu Arroz" << endl;
    sem_post(&mutexRice);
    sem_post(&emptyRice);


    sem_wait(&fullBean);
    sem_wait(&mutexBean);
    buffet.printBuffet();
    tempBuffet = buffet.getBuffet();
    tempConsumo = cliente.getItemsTaken();
    if(tempBuffet > tempConsumo) {
      tempBuffet[3] = tempBuffet[3] - tempConsumo[3];
    } else {
      tempBuffet[3] = 0;
    }
    buffet.setBuffet(3, tempBuffet[3]);
    cout << "Consumiu Feijão" << endl;
    sem_post(&mutexBean);
    sem_post(&emptyBean);

    sem_wait(&fullComplement);
    sem_wait(&mutexComplement);
    buffet.printBuffet();
    tempBuffet = buffet.getBuffet();
    tempConsumo = cliente.getItemsTaken();
    if(tempBuffet > tempConsumo) {
      tempBuffet[4] = tempBuffet[4] - tempConsumo[4];
    } else {
      tempBuffet[4] = 0;
    }
    buffet.setBuffet(4, tempBuffet[4]);
    cout << "Consumiu Complemento" << endl;
    sem_post(&mutexComplement);
    sem_post(&emptyComplement);

    sem_wait(&fullMeat);
    sem_wait(&mutexMeat);
    buffet.printBuffet();
    tempBuffet = buffet.getBuffet();
    tempConsumo = cliente.getItemsTaken();
    if(tempBuffet > tempConsumo) {
      tempBuffet[5] = tempBuffet[5] - tempConsumo[5];
    } else {
      tempBuffet[5] = 0;
    }
    
    buffet.setBuffet(5, tempBuffet[5]);
    cout << "Consumiu Carne" << endl;
    sem_post(&mutexMeat);
    sem_post(&emptyMeat);

    buffet.printBuffet();
  }
  return NULL;
}


int main() {
  pthread_t consumer0, consumer1, consumer2, consumer3, consumer4, consumer5,
    consumer6, consumer7, consumer8, consumer9;
  pthread_t KitchenSalad, KitchenDessert, KitchenRice, KitchenBean,
      KitchenComplement, KitchenMeat;

  Kitchen Kitchen;
  
  sem_init(&fullSalad, 0, 0);
  sem_init(&emptySalad, 0, N);
  sem_init(&mutexSalad, 0, 1);

  sem_init(&fullDessert, 0, 0);
  sem_init(&emptyDessert, 0, N);
  sem_init(&mutexDessert, 0, 1);

  sem_init(&fullRice, 0, 0);
  sem_init(&emptyRice, 0, N);
  sem_init(&mutexRice, 0, 1);

  
  sem_init(&fullBean, 0, 0);
  sem_init(&emptyBean, 0, N);
  sem_init(&mutexBean, 0, 1);
  
  sem_init(&fullComplement, 0, 0);
  sem_init(&emptyComplement, 0, N);
  sem_init(&mutexComplement, 0, 1);

  sem_init(&fullMeat, 0, 0);
  sem_init(&emptyMeat, 0, N);
  sem_init(&mutexMeat, 0, 1);

  buffet.printBuffet();
  pthread_create(&consumer0, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer1, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer2, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer3, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer4, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer5, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer6, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer7, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer8, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer9, NULL, &consumidorTeste, NULL);

  pthread_create(&KitchenSalad, NULL, &produtorSalad, NULL);
  pthread_create(&KitchenDessert, NULL, &produtorDessert, NULL);
  pthread_create(&KitchenRice, NULL, &produtorRice, NULL);
  pthread_create(&KitchenBean, NULL, &produtorBean, NULL);
  pthread_create(&KitchenComplement, NULL, &produtorComplement, NULL);
  pthread_create(&KitchenMeat, NULL, &produtorMeat, NULL);


  pthread_join(KitchenSalad, NULL);
  pthread_join(KitchenDessert, NULL);
  pthread_join(KitchenRice, NULL);
  pthread_join(KitchenBean, NULL);
  pthread_join(KitchenComplement, NULL);
  pthread_join(KitchenMeat, NULL);

  pthread_join(consumer0, NULL);
  pthread_join(consumer1, NULL);
  pthread_join(consumer2, NULL);
  pthread_join(consumer3, NULL);
  pthread_join(consumer4, NULL);
  pthread_join(consumer5, NULL);
  pthread_join(consumer6, NULL);
  pthread_join(consumer7, NULL);
  pthread_join(consumer8, NULL);
  pthread_join(consumer9, NULL);

  sleep(1);
  buffet.printBuffet();
  printf("Threads finalizadas \n");
  return 0;
}