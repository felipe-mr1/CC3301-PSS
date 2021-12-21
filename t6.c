#include <pthread.h>

#include "t6.h"

// *** Esta implementacion no funciona porque no respeta orden de llegada ***


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int num = 0;
int visor = 0;

void ocupar() {
  pthread_mutex_lock(&m);
  int turno = num;
  num++;
  pthread_cond_broadcast(&c);
  while (turno != visor){
    pthread_cond_wait(&c, &m);
  }
  pthread_mutex_unlock(&m);
}

void desocupar() {
  pthread_mutex_lock(&m);
  visor++;
  pthread_cond_broadcast(&c);
  pthread_mutex_unlock(&m);
}
