#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reducir(char *s){
    char *aux = s;
    char *p1 = s + 1;
    char *p2 = s + 1;
    while(*p1 != '\0'){
        if ((*p1 != ' ')&&(*p2 != ' ')){
            aux++;
            p1++;
            p2++;
        } else if ((*aux == ' ')&&(*p1 == ' ')){
            p1++;
        } else if(*p1 != ' ') {
            *p2 = *p1;
            aux++;
            *p1 = ' ';
            p1++;
            p2++;
        } else {
            aux++;
            p2++;
            p1++;
        }
    }
    *p2 = '\0';
}

char *reduccion(char *s){
    int cont = 0;
    char *p2 = s + 1;
    char *p1 = s;
    while(*p1 != '\0'){
        if((*p1 == ' ')&&(*p2 == ' ')){
            p1++;
            p2++;
        } else {
            cont++;
            p1++;
            p2++;
        }
    }
    char *r = malloc((cont+1)*sizeof(char));
    char *ptr2 = s + 1;
    char *ptr1 = s;
    char *r1 = r;
    while(*ptr1 != '\0'){
        if((*ptr1 == ' ')&&(*ptr2 == ' ')){
            ptr1++;
            ptr2++;
        } else {
            *r1 = *ptr1;
            r1++;
            ptr1++;
            ptr2++;
        }
    }
    *r1 = '\0';
    return r;
}
