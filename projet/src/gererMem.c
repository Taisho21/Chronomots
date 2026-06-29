#include <stdlib.h>
#include <stdio.h>
#include "../include/projet.h"


void* myMalloc(size_t size, InfoMem* infoMem) {
    void* ptr = malloc(size);
    
    if (ptr != NULL) {  // on verfie que le malloc a bien reussi
        infoMem->cumul_alloc += size;  // on ajustes les accumulateurs en consequences 
        infoMem->current_alloc += size;

        if (infoMem->current_alloc > infoMem->max_alloc)infoMem->max_alloc = infoMem->current_alloc;  // on change la taille du max si necessaire
        
    } else fprintf(stderr, "Erreur : Impossible d'allouer %zu octets.\n", size); // error si ca fonctionne pas ( desole jai un qwerty jai pas les accents)

    return ptr;
}



void myFree(void* ptr, InfoMem* infoMem, size_t size) {
    if (ptr != NULL) {
        free(ptr);  // si le ponteur est null on libere directement
        
        infoMem->cumul_desalloc += size; // sinon on ajuste l'acc de desallocation
        
        if (infoMem->current_alloc >= size) { // ainsi que celui d'allocations
            infoMem->current_alloc -= size;
        } else {
            infoMem->current_alloc = 0; // gestion d'erreur -- memoire negative 
            printf("Attention : Tentative de désallouer plus que ce qui est alloué.\n");
        }
    }
}


void* myRealloc(void* ptr, size_t new_size, InfoMem* infoMem, size_t old_size) {

    // si le pointeur est NULL on agit comme un malloc()
    if (ptr == NULL) {
        return myMalloc(new_size, infoMem);//lien avec le ajouter liste et FREE c'est ICI !!
    }
    if (new_size == 0) { // si la taille demandee est 0 on agit comme un free()
        myFree(ptr, infoMem, old_size);
        return NULL;
    }

    void* new_ptr = realloc(ptr, new_size);

    if (new_ptr != NULL) {
        //on verifie si on est a la meme adresse memoire
        if (ptr == new_ptr) { // si oui on calcule la nouvelle taille pour ajuster le compteur (retrecicement ou aggrandissement de la zone memoire)
            if (new_size > old_size) {
                infoMem->cumul_alloc += (new_size - old_size);
            } 
            else {
                infoMem->cumul_desalloc += (old_size - new_size);
            }
        }
        else {  // sinon, Si le bloc est déplacé à une nouvelle adresse, on considere l'ancienne taille comme libérée et la nouvelle comme allouée.
        // on ajustes les accumulateurs en consequneces
            infoMem->cumul_desalloc += old_size;
            infoMem->cumul_alloc += new_size;
        }

        if (infoMem->current_alloc >= old_size) { // on verifie que la taille actuelle est bien plus importante que l'ancienne pour ne pas se retrouver avec un acc negatif
            infoMem->current_alloc -= old_size;
        }
        infoMem->current_alloc += new_size; // mise a jour de la taille actuelle

        if (infoMem->current_alloc > infoMem->max_alloc) {  // on verfie si la nouvelle occupation memoire depasse le dernier max enregistre si oui on l'augmente 
            infoMem->max_alloc = infoMem->current_alloc;
        }

    } else {
        printf("Erreur : Echec de réallocation.\n");
    }

    return new_ptr;
}