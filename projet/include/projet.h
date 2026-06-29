#ifndef PROJET_H
#define PROJET_H
#define MAX_MOT_BAN 50
#define TAILLE_MAX_MOT 50
#include <stddef.h> 
#include <stdio.h>


typedef struct {
    size_t cumul_alloc;
    size_t cumul_desalloc;
    size_t max_alloc; 
    size_t current_alloc; 
} InfoMem;


typedef struct {
    char *mot;
    int occurrences;
} Mot;

typedef struct Noeud {
    Mot mot;
    struct Noeud *suivant;
    struct Noeud *precedent; // pointeur actif ou passif, selon le choix dans le main
} Noeud, *Liste;


typedef struct{
    Mot *tab;
    int taille;
    int capacite;
}Tableau;


typedef struct{
    char tab[MAX_MOT_BAN][TAILLE_MAX_MOT];
    int nombre_mot;
}ListeBan;

void* myMalloc(size_t size, InfoMem* infoMem);
void myFree(void* ptr, InfoMem* infoMem, size_t size);
void* myRealloc(void* ptr, size_t new_size, InfoMem* infoMem, size_t old_size);


#endif