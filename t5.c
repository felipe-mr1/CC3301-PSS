#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "maleta.h"

typedef struct {
    double *w;
    double *v;
    int *z;
    int n;
    double maxW;
    int k;
    double best;
} Args;

void *thread_function(void *p){
    Args *args = p;
    double *w = args->w;
    double *v = args->v;
    int *z = args->z;
    int n = args->n;
    double maxW = args->maxW;
    int k = args->k;
    args->best = llenarMaletaSec(w, v, z, n, maxW, k);
    return NULL;
}

double llenarMaletaPar(double w[], double v[], int z[], int n, double maxW, int k){
    pthread_t pid[8];
    Args args[8];
    for(int t = 0; t < 8; t++){
        args[t].w = w;
        args[t].v = v;
        args[t].n = n;
        args[t].maxW = maxW;
        args[t].k = k/8;
        int *Zeta = malloc(n*sizeof(int));
        args[t].z = Zeta;
        pthread_create(&pid[t], NULL, thread_function, &args[t]);
    }
    double bestPog = -1;
    for(int f = 0; f<8; f++){
        pthread_join(pid[f],NULL);
        if (args[f].best > bestPog){
            bestPog = args[f].best;
            for(int i=0; i<n; i++){
                z[i]=args[f].z[i];
            }
            free(args[f].z);
        } else {
            free(args[f].z);
        }
    }
    return bestPog;
}

