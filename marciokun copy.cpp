#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>
#include <Cozinha.h>
#include <Customer.h>

#include <vector>
// salada, sobremesa, arroz, feijao, complemento e carne
vector<float> chanceToTake = {0.8, 0.6, 0.8, 0.7, 0.4, 0.9}
vector<float> varianceToTake = {0.1, 0.1, 0.3, 0.2, 0.2}
vector<float> quantityToTake = {0.03, 0.08, 0.1, 0.07, 0.1, 0.08}
vector<float> varianceQuantity = {0.02, 0.0, 0.003, 0.002, 0.005, 0.01}

sem_t full;
sem_t empty;
sem_t mutex;

#define N 32
volatile int buffer[N];
volatile int count;

class Buffet {
  private:
    vector<float> buffet(6);
  public:
      setBuffet(int index, float value){
        buffet[index] = value;
      }
      getBuffet(){
        return buffet;
      }
}
Buffet::Buffet(){}
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

void *produtorSalad(void *arg){
  Cozinha cozinha;
  for(int i = 0; i < 5; i++){
    cozinha.cookingItems(0)
    sem_wait(&empty);
    sem_wait(&mutex);
    Buffet.setBuffet(0, 1.0)
    sem_post(&full);
    sem_post(&mutex);
  }
  return NULL;
}

void *produtorDessert(void *arg){
  Cozinha cozinha;
  for(int i = 0; i < 20; i++){
    cozinha.cookingItems(1)
    sem_wait(&empty);
    sem_wait(&mutex);
    Buffet.setBuffet(1, 1.0)
    sem_post(&full);
    sem_post(&mutex);
  }
  return NULL;
}

void *produtorRice(void *arg){
  Cozinha cozinha;
  for(int i = 0; i < 12; i++){
    cozinha.cookingItems(2)
    sem_wait(&empty);
    sem_wait(&mutex);
    Buffet.setBuffet(2, 1.0)
    sem_post(&full);
    sem_post(&mutex);
  }
  return NULL;
}

void *produtorBean(void *arg){
  Cozinha cozinha;
  for(int i = 0; i < 10; i++){
    cozinha.cookingItems(3)
    sem_wait(&empty);
    sem_wait(&mutex);
    Buffet.setBuffet(3, 1.0)
    sem_post(&full);
    sem_post(&mutex);
  }
  return NULL;
}

void *produtorComplement(void *arg){
  Cozinha cozinha;
  for(int i = 0; i < 20; i++){
    cozinha.cookingItems(4)
    sem_wait(&empty);
    sem_wait(&mutex);
    Buffet.setBuffet(4, 1.0)
    sem_post(&full);
    sem_post(&mutex);
  }
  return NULL;
}

void *produtorMeat(void *arg){
  Cozinha cozinha;
  for(int i = 0; i < 25; i++){
    cozinha.cookingItems(5)
    sem_wait(&empty);
    sem_wait(&mutex);
    Buffet.setBuffet(5, 1.0)
    sem_post(&full);
    sem_post(&mutex);
  }
  return NULL;
}



void *consumidorTeste(void *arg) {
  
  Customer cliente(chanceToTake,
varianceToTake, quantityToTake,
varianceQuantity);
  for (int i = 0; i < 5000; i++) {
    for(int j = 0; j <6; j++){
      cliente.takeItems(j);
    }
    sem_wait(&full);
    sem_wait(&mutex);
    vector<float> tempBuffet = getBuffet();
    vector<float> tempConsumo = cliente.getItemsTaken();
    for(int j = 0; j<6; j++){
      tempBuffet[j] = tempBuffet[j] - tempConsumo[j];
    }

    sem_post(&mutex);
    sem_post(&empty);
  }
  return NULL;
}

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
  pthread_t p1, p2;
  int id1, id2;
  id1 = 1;
  id2 = 2;
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, N);
  sem_init(&mutex, 0, 1);
  // id, attr, função,         arg
  pthread_create(&p1, NULL, &produtor, NULL);
  pthread_create(&p2, NULL, &consumidor, NULL);

  int tid;
  tid = syscall(SYS_gettid);
  printf(" thread main pid %d %d\n", tid, getpid());

  /*  Quantos threads eu tenho em execução no meu processo? */

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  sleep(1);
  printf("Threads finalizadas \n");
  return 0;
}