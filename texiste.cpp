#include "Cozinha.h"
#include "Customer.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>

#include <vector>
// salada, sobremesa, arroz, feijao, complemento e carne
// vector<float> chanceToTake = {0.8, 0.6, 0.8, 0.7, 0.4, 0.9};
// vector<float> varianceToTake = {0.1, 0.1, 0.3, 0.2, 0.2, 0.05};
// vector<float> quantityToTake = {0.03, 0.08, 0.1, 0.07, 0.1, 0.08};
// vector<float> varianceQuantity = {0.02, 0.000001, 0.003, 0.002, 0.005, 0.01};

sem_t full;
sem_t empty;
sem_t mutex;

#define N 32
volatile int buffer[N];
volatile int count;

class Buffet {
private:
  vector<float> buffet;

public:
  Buffet() : buffet({0, 0, 0, 0, 0, 0}){}
  void setBuffet(int index, float value) { buffet[index] = value; }
  vector<float> getBuffet() {
    return buffet;
}
  void printBuffet() {
    for (int i = 0; i < 6; i++) {
      cout << buffet[i] << " ";
    }
    cout << endl;
  }
};


// void Buffet::getBuffet(vector<float>& result) {
//     result = buffet;
// }
Buffet buffet;
// void *thread_function(void *arg){

//   int tid;
//   tid= syscall(SYS_gettid);

//   int i;
//   sem_wait(&sem)
//   for (i=0; i < 10 ; i++)  {
//       printf(" thread pid %d %d %d\n", tid, i, *(int*)arg);
//       fflush(stdout);
//       usleep(100);
//   }
//   sem_post(&sem)

//   return NULL;
// }

void *produtor(void *arg) {
  int in = 0;
  for (int i = 0; i < 5000; i++) {
    sem_wait(&empty);
    sem_wait(&mutex);
    buffer[in] = i;
    in = (in + 1) % N;
    printf("Produziu %d na posição %d\n", i, in);
    count++;
    sem_post(&full);
    sem_post(&mutex);
  }
  return NULL;
}

void *produtorSalad(void *arg) {
  Cozinha cozinha;
  bool allGreater;
  for (int i = 0; i < 500; i++) {
    cozinha.cookingItems(0);
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
  Cozinha cozinha;
  bool allGreater;
  for (int i = 0; i < 500; i++) {
    cozinha.cookingItems(1);
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
  Cozinha cozinha;
  bool allGreater;
  for (int i = 0; i < 500; i++) {
    cozinha.cookingItems(2);
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
  Cozinha cozinha;
  bool allGreater;
  for (int i = 0; i < 500; i++) {
    cozinha.cookingItems(3);
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
  Cozinha cozinha;
  bool allGreater;
  for (int i = 0; i < 500; i++) {
    cozinha.cookingItems(4);
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
  Cozinha cozinha;
  bool allGreater;
  for (int i = 0; i < 500; i++) {
    cozinha.cookingItems(5);
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

  Customer cliente;
  for (int i = 0; i < 5000; i++) {
    for (int j = 0; j < 6; j++) {
      cliente.takeItems(j);
    }
    bool allGreater;
    vector<float> tempBuffet = buffet.getBuffet();
    vector<float> tempConsumo = cliente.getItemsTaken();
    while(allGreater == false) {
      for(int j = 0; j<6; j++){
        if(tempBuffet[i] < tempConsumo[i]){
          allGreater = true;
        } else {
          allGreater = false;
          break;
        }
      }
      tempBuffet = buffet.getBuffet();
      tempConsumo = cliente.getItemsTaken();
    }
    sem_wait(&full);
    sem_wait(&mutex);
    buffet.printBuffet();

    for (int j = 0; j < 6; j++) {
      tempBuffet[j] = tempBuffet[j] - tempConsumo[j];
    }
    for (int j = 0; j < 6; j++) {
      buffet.setBuffet(j, tempBuffet[j]);
    }
    cout << "Setou Consumidor" << endl;
    
    sem_post(&mutex);
    sem_post(&empty);
    buffet.printBuffet();
  }
  return NULL;
}

// void *consumidorTeste(void *arg) {
//     Customer cliente(chanceToTake, varianceToTake, quantityToTake, varianceQuantity);
//     for (int i = 0; i < 5000; i++) {
//         for (int j = 0; j < 6; j++) {
//             cliente.takeItems(j);
//         }
//         sem_wait(&full);
//         sem_wait(&mutex);
        
//         vector<float> tempBuffet;
//         buffet.getBuffet(tempBuffet);
//         cliente.getItemsTaken(itemsTaken);
//         for (int j = 0; j < 6; j++) {
//             tempBuffet[j] = tempBuffet[j] - itemsTaken[j];
//         }
        
//         buffet.setBuffet(tempBuffet);
//         cout << "Setou Consumidor" << endl << endl;
//         sem_post(&mutex);
//         sem_post(&empty);
//     }
//     return NULL;
// }

// void *consumidor(void *arg) {
//   int out = 0;
//   int dout;
//   Customer Cliente();
//   for (int i = 0; i < 5000; i++) {
//     sem_wait(&full);
//     sem_wait(&mutex);

//     dout = buffer[out];
//     out = (out + 1) % N;
//     printf("Consumiu %d na prosição %d\n", dout, out);
//     count--;

//     sem_post(&mutex);
//     sem_post(&empty);
//   }
//   return NULL;
// }

int main() {
  pthread_t c0, c1, c2, c3, c4, c5;
  pthread_t consumer0, consumer1, consumer2, consumer3, consumer4, consumer5,
      consumer6, consumer7, consumer8, consumer9;
  Cozinha cozinha;
  // int id1, id2;
  // id1 = 1;
  // id2 = 2;
  buffet.printBuffet();
  // sleep(1);
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, N);
  sem_init(&mutex, 0, 1);
  // id, attr, função,         arg

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

  pthread_create(&c0, NULL, &produtorSalad, NULL);
  pthread_create(&c1, NULL, &produtorDessert, NULL);
  pthread_create(&c2, NULL, &produtorRice, NULL);
  pthread_create(&c3, NULL, &produtorBean, NULL);
  pthread_create(&c4, NULL, &produtorComplement, NULL);
  pthread_create(&c5, NULL, &produtorMeat, NULL);



  // int tid;
  // tid = syscall(SYS_gettid);
  // printf(" thread main pid %d %d\n", tid, getpid());

  /*  Quantos threads eu tenho em execução no meu processo? */

  pthread_join(c0, NULL);
  pthread_join(c1, NULL);
  pthread_join(c2, NULL);
  pthread_join(c3, NULL);
  pthread_join(c4, NULL);
  pthread_join(c5, NULL);

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