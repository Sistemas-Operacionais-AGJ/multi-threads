#include "Customer.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>
#include "Buffet.h"
#include "time.h"
#include <iostream>
#include <vector>

// g++ -o myprogram noMutexTimer.cpp Buffet.cpp Customer.cpp -lpthread 
// salada, sobremesa, arroz, feijao, complemento e carne
// vector<float> chanceToTake = {0.8, 0.6, 0.8, 0.7, 0.4, 0.9};
// vector<float> varianceToTake = {0.1, 0.1, 0.3, 0.2, 0.2, 0.05};
// vector<float> quantityToTake = {0.03, 0.08, 0.1, 0.07, 0.1, 0.08};
// vector<float> varianceQuantity = {0.02, 0.000001, 0.003, 0.002, 0.005, 0.01};


#define N 6
volatile int buffer[N];
volatile int count;

Buffet buffet;

void timer(clock_t startTime){
  vector<float> temporaryBuffet;
  do
  {
    temporaryBuffet = buffet.getBuffet();
  } while (temporaryBuffet[0] > 0 || temporaryBuffet[1] > 0 || temporaryBuffet[2] > 0 || temporaryBuffet[3] > 0 || temporaryBuffet[4] > 0 || temporaryBuffet[5] > 0);
  
  cout << endl << endl << endl << endl; 

  clock_t endTime = clock();
  cout << "Tempo = " << (float)(((endTime - startTime)/CLOCKS_PER_SEC)/10000) << endl;

  cout << endl << endl << endl << endl;

  exit(1);
}

void buffetSet(int i, float quantity){
  float temporaryBuffet = buffet.getBuffet(i);
  printf("item %d consumed\n", i);
  buffet.setBuffet(i, temporaryBuffet > quantity ? (temporaryBuffet - quantity) : 0);
  buffet.printBuffet();
}

void *consumidorTeste(void *arg) {

  Customer cliente;

  for (int i = 0; i < 5000; i++) {
    for (int j = 0; j < 6; j++) {
      cliente.takeItems(j);
      buffetSet(j, cliente.getItemsTaken(j));
    }
  }
  return NULL;
}

int main() {
  pthread_t consumer0, consumer1, consumer2, consumer3, consumer4, consumer5, consumer6, consumer7, consumer8, consumer9;
<<<<<<< HEAD

=======
  clock_t inicioTempo, fimTempo;
  float tempo = 0.0;
>>>>>>> timeTests
  buffet.printBuffet();
  pthread_create(&consumer0, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer1, NULL, &consumidorTeste, NULL);
  pthread_create(&consumer2, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer3, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer4, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer5, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer6, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer7, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer8, NULL, &consumidorTeste, NULL);
  // pthread_create(&consumer9, NULL, &consumidorTeste, NULL);

<<<<<<< HEAD
  clock_t startTime = clock();
  timer(startTime);
=======
  inicioTempo = clock();
  timer(inicioTempo);
>>>>>>> timeTests
  pthread_join(consumer0, NULL);
  pthread_join(consumer1, NULL);
  pthread_join(consumer2, NULL);
  // pthread_join(consumer3, NULL);
  // pthread_join(consumer4, NULL);
  // pthread_join(consumer5, NULL);
  // pthread_join(consumer6, NULL);
  // pthread_join(consumer7, NULL);
  // pthread_join(consumer8, NULL);
  // pthread_join(consumer9, NULL);

  sleep(1);
  printf("Threads finalizadas \n");
<<<<<<< HEAD
=======
  fimTempo = clock();

  tempo = (float)(((fimTempo - inicioTempo) + 0.0) / CLOCKS_PER_SEC);
  cout << tempo;
  
>>>>>>> timeTests
  return 0;
}