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

sem_t full;
sem_t empty;
sem_t mutex;

#define N 6
volatile int buffer[N];
volatile int count;

Buffet buffet;

void timer(clock_t inicioTempo){
  vector<float> tempBuffet = buffet.getBuffet();
  cout << "Timer =" << tempBuffet[0] << tempBuffet[1] << tempBuffet[2] << tempBuffet[3] << tempBuffet[4] << tempBuffet[5] ;
  while (true)
  {
    tempBuffet = buffet.getBuffet();
    if (tempBuffet[0] <= 0 && tempBuffet[1] <= 0 && tempBuffet[2] <= 0 && tempBuffet[3] <= 0 && tempBuffet[4] <= 0 && tempBuffet[5] <= 0)
    {
      clock_t fimTempo = clock();
      printf("Tempo de execução = %f\n", (float)(((fimTempo - inicioTempo) + 0.0) / CLOCKS_PER_SEC));
      exit(1);
    }
    
  }
  
}

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
    sem_wait(&empty);
    sem_wait(&mutex);
    buffet.setBuffet(0, 1.0);
    printf("Salada Feita\n");
    sem_post(&full);
    sem_post(&mutex);
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
    sem_wait(&empty);
    sem_wait(&mutex);
    buffet.setBuffet(1, 1.0);
    printf("Sobremesa Feita\n");
    sem_post(&full);
    sem_post(&mutex);
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
    sem_wait(&empty);
    sem_wait(&mutex);
    buffet.setBuffet(2, 1.0);
    printf("Arroz Feito\n");
    sem_post(&full);
    sem_post(&mutex);
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
    sem_wait(&empty);
    sem_wait(&mutex);
    buffet.setBuffet(3, 1.0);
    printf("Feijão Feito\n");
    sem_post(&full);
    sem_post(&mutex);
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
    sem_wait(&empty);
    sem_wait(&mutex);
    buffet.setBuffet(4, 1.0);
    printf("Complemento Feito\n");
    sem_post(&full);
    sem_post(&mutex);
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
    sem_wait(&empty);
    sem_wait(&mutex);
    buffet.setBuffet(5, 1.0);
    printf("Carne Feita\n");
    sem_post(&full);
    sem_post(&mutex);
  }
  return NULL;
}

void *consumidorTeste(void *arg) {

  for (int i = 0; i < 10; i++) {
    Customer cliente;
    for (int j = 0; j < 6; j++) {
      cliente.takeItems(j);
    }
    vector<float> tempBuffet;
    vector<float> tempConsumo;
    sem_wait(&full);
    sem_wait(&mutex);
    buffet.printBuffet();
    tempBuffet = buffet.getBuffet();
    tempConsumo = cliente.getItemsTaken();
    for (int j = 0; j < 6; j++) {
      if(tempBuffet > tempConsumo) {
        tempBuffet[j] = tempBuffet[j] - tempConsumo[j];
      } else {
        tempBuffet[j] = 0;
      }
      buffet.setBuffet(j, tempBuffet[j]);
      cout << "Consumiu" << endl;
    }

    sem_post(&mutex);
    sem_post(&empty);

    buffet.printBuffet();
  }
  return NULL;
}


int main() {
  pthread_t consumer0, consumer1, consumer2, consumer3, consumer4, consumer5,
    consumer6, consumer7, consumer8, consumer9;
  pthread_t KitchenSalad, KitchenDessert, KitchenRice, KitchenBean,
      KitchenComplement, KitchenMeat;

  clock_t inicioTempo, fimTempo;
  float tempo = 0.0;

  
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, N);
  sem_init(&mutex, 0, 1);

  buffet.printBuffet();
  pthread_create(&consumer0, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer1, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer2, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer3, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer4, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer5, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer6, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer7, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer8, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer9, NULL, &consumidorTeste, NULL);

  pthread_create(&KitchenSalad, NULL, &produtorSalad, NULL);
  pthread_create(&KitchenDessert, NULL, &produtorDessert, NULL);
  pthread_create(&KitchenRice, NULL, &produtorRice, NULL);
  pthread_create(&KitchenBean, NULL, &produtorBean, NULL);
  pthread_create(&KitchenComplement, NULL, &produtorComplement, NULL);
  pthread_create(&KitchenMeat, NULL, &produtorMeat, NULL);

  inicioTempo = clock();
  timer(inicioTempo);
  pthread_join(KitchenSalad, NULL);
  pthread_join(KitchenDessert, NULL);
  pthread_join(KitchenRice, NULL);
  pthread_join(KitchenBean, NULL);
  pthread_join(KitchenComplement, NULL);
  pthread_join(KitchenMeat, NULL);

  pthread_join(consumer0, NULL);
  pthread_join(consumer1, NULL);
  // pthread_join(consumer2, NULL);
  // pthread_join(consumer3, NULL);
  // pthread_join(consumer4, NULL);
  // pthread_join(consumer5, NULL);
  // pthread_join(consumer6, NULL);
  // pthread_join(consumer7, NULL);
  // pthread_join(consumer8, NULL);
  // pthread_join(consumer9, NULL);

  buffet.printBuffet();
  printf("Threads finalizadas \n");
  fimTempo = clock();
  sleep(1);

  tempo = (float)(((fimTempo - inicioTempo) + 0.0) / CLOCKS_PER_SEC);
  cout << tempo;
  
  return 0;
}