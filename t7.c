#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double viajante_par(int z[], int n, double **m, int nperm, int p){
    int pids[8];
    int fds_aux[8];
    int number = nperm/p;
    double min = DBL_MAX;

    for(int k = 0; k < p; k++){
        int fds[2];
        pipe(fds);

        init_rand_seed(random());
        pids[k] = fork();

        if(pids[k] == 0){ // es el hijo
            close(fds[0]);
            double min_sec = viajante(z, n, m, number);

            write(fds[1], &min_sec, sizeof(double));
            write(fds[1], &z[0], (n+1)*sizeof(int));
            
            exit(0);
        } else { // es el padre
            close(fds[1]);
            fds_aux[k] = fds[0];
        }
    }

    for(int j = 0; j < p; j++){
        double res;
        int *zeta = malloc((n+1)*sizeof(int));
        leer(fds_aux[j], &res, sizeof(double));
        leer(fds_aux[j], zeta, (n+1) * sizeof(int));
        waitpid(pids[j], NULL, 0);
        close(fds_aux[j]);
        if (res < min){
            min = res;
            for (int h = 0; h < n + 1; h++){
                z[h] = zeta[h];
            }
        }
        free(zeta);
    }
    return min;
}