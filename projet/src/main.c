#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "../include/projet.h"
#include "../include/lecture.h"
#include "../include/algo.h" //prototype des fonctions de tri



void afficheMEM(InfoMem mem){
    printf("Memoire alloue cumule: %lu octets\n", (unsigned long)mem.cumul_alloc);
    printf("Memoire desaoulloue cumule: %lu octets\n", (unsigned long)mem.cumul_desalloc);
    printf("Memoire Max utilise : %lu octets\n", (unsigned long)mem.max_alloc);
    printf("Memoire utilise actuellement: %lu octets\n", (unsigned long)mem.current_alloc);
    printf("\n");
}


int main(int argc, char *argv[]) { //argv c'est les mots que tu mets en + lors de l'éxécution c'est un peu une liste des mots que t'as entré séparé par un espace
                                    //argv[0] = nom du fichier main.c ; argv[1] le nom du fichier à lire 
    InfoMem mem = {0}; 
    Liste ma_liste = NULL;
    Tableau mon_tableau;

    ListeBan liste_interdite = {0};
    ListeBan liste_désiré = {0};
    
    char *mot_lu;
    int n, choix = 0;
    int type_struct = 0; // 0 = Simple, 1 = Double, 2 = Tableau 
    int nombre_mot_ban,mot_voulu,taille_mot;
    clock_t debut, fin;
    double temps_exec;
    
    init_tab(&mon_tableau);

    if (argc <2) {
        printf("Erreur: AUCUN FICHIER SPECIFIE ");
        return 1;
    }

//----------------------------------------------------------------------------------


if (argc >= 8) {        // ./projet fichier type_struct choix_algo nb_bannis taille_max nb_voulus n
        type_struct = atoi(argv[2]);    // Structure (0, 1, 2)
        choix = atoi(argv[3]);          // Algo (1, 2)

  
        nombre_mot_ban = atoi(argv[4]); // Combien de mots bannis
        taille_mot = atoi(argv[5]);     // Taille max
        mot_voulu = atoi(argv[6]);      // Combien de mots ciblés


        n = atoi(argv[7]);              // Combien de mots afficher à la fin

        if(nombre_mot_ban > 0) saisir_mots_bannis(&liste_interdite, nombre_mot_ban);
        if(mot_voulu > 0) saisir_mots_bannis(&liste_désiré, mot_voulu);

    } else {

        printf("Type de structure : (0) Simple , (1) Double, (2) Tableau ? ");
        scanf("%d", &type_struct); 

        if(type_struct != 2){
            printf("Veuillez choisir l'algo de tri à utiliser :\n");
            printf("-1 Tri a Fusion \n");
            printf("-2 Tri a Bulle \n");
            scanf(" %d", &choix);      
        } else {
            printf("Veuillez choisir l'algo de tri à utiliser :\n");
            printf("-1 Tri a Bulle \n");
            printf("-2 QUICKSORT \n");
            scanf(" %d", &choix);      
        }


        
        // Mots à exclure 
        printf("Combien de mots voulez-vous bannir/exclure ? (0 pour RIEN) : \n");
        scanf("%d", &nombre_mot_ban);
        saisir_mots_bannis(&liste_interdite, nombre_mot_ban);

        // Taille maximum des mots
        printf("Taille minimum des mots a garder ? (0 pour ignorer la taille) : \n");
        scanf("%d", &taille_mot);

        // Liste blanche 
        printf("Combien de mots specifiques voulez-vous cibler ? (0 pour traiter TOUT le texte) : \n");
        scanf("%d", &mot_voulu);
        saisir_mots_bannis(&liste_désiré, mot_voulu);

    
     
        printf("Combien de mots voulez-vous afficher a la fin ? (0 pour TOUT afficher) : \n");
        scanf(" %d", &n);
    }
    




    //-------------------Partie Fichier lecture---------------------------------------
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", argv[1]);
        return 1;
    }

    printf("--- Lecture du fichier... ---\n");
    

    while ((mot_lu = lire_mot_dynamique(f, &mem)) != NULL) {
            
            size_t taille_chaine = strlen(mot_lu) + 1;


            int est_vip = (mot_voulu > 0 && est_mot_banni(mot_lu, &liste_désiré));

            if (est_mot_banni(mot_lu, &liste_interdite)) {
                myFree(mot_lu, &mem, taille_chaine); 
                continue; 
            }


            if(taille_mot > 0 && strlen(mot_lu) < taille_mot && !est_vip){
                myFree(mot_lu, &mem, taille_chaine); 
                continue; 
            }
        

            if(mot_voulu > 0 && !est_vip) {
                myFree(mot_lu, &mem, taille_chaine);
                continue;
            }

            // 4. Si on arrive ici, on garde le mot !
            if(type_struct == 2){
                ajouter_dans_tableau(&mon_tableau, mot_lu);
            } else {
                ajouter_dans_liste(&ma_liste, mot_lu, &mem, type_struct); 
            }
        }
    fclose(f);
    printf("Lecture terminee.\n");


    debut = clock();
    if(type_struct == 2){
        switch(choix){
            case 1:
                printf("Tri a Bulle sur Tableau en cours...---\n");
                tri_bulle_tab(&mon_tableau);
                break;
            case 2:
                printf("Tri avec QUICKSORT sur Tableau en cours...\n");
                tri_rapide_tab(&mon_tableau);
                break;
            default:
                printf("Existe pas CIAOOO !");
                return 1;
        }
    }else{

    switch (choix){
    case 1:
        printf("\n--- Tri a Fusion en cours... ---\n");
        triFusion(&ma_liste, type_struct); 
        break;
    case 2:
        printf("\n--- Tri a Bulle en cours... ---\n");
        tri_bulle(&ma_liste, type_struct); 
        break;
    default:
        printf("Algo n'existe pas !!!");
        return 1;
    }
}
    fin = clock();
    temps_exec = ((double)(fin-debut))/CLOCKS_PER_SEC;
    
    printf("--- Resultat du tri ---\n");

    printf("L'execution a pris %f secondes \n", temps_exec);
    if(type_struct == 2){
        printf("Structure : Tableau");
        afficheMEM(mem);
        afficher_tableau(&mon_tableau,n);

    }else{
        printf("Structure  : Liste %s\n", (type_struct == 1 ? "Doublement Chainee" : "Simple"));
        afficheMEM(mem);
        afficher_liste(ma_liste,n);
    }
    
    char *nom_algo_str = "Inconnu";
    char *nom_struct_str = "Inconnu";

    if (type_struct == 2) {
        nom_struct_str = "Tableau";
        if (choix == 1) nom_algo_str = "Bulle";
        else if (choix == 2) nom_algo_str = "QuickSort";
    } else {
        nom_struct_str = (type_struct == 1) ? "Liste_Double" : "Liste_Simple";
        if (choix == 1) nom_algo_str = "Fusion";
        else if (choix == 2) nom_algo_str = "Bulle";
    }

    FILE *f_stats = fopen("stats.txt", "a"); // "a" ajoute à la fin du fichier si des infos existent déjà, sinon crée le fichier

    if (f_stats == NULL) {
        printf("Erreur : Impossible d'ecrire dans stats.txt\n");
    } else {
        fprintf(f_stats, "%s; %s; %s; %f; %lu\n", 
                argv[1],              // Fichier
                nom_algo_str,         // Algo
                nom_struct_str,       // Structure
                temps_exec,           // Temps
                (unsigned long)mem.max_alloc // RAM Max
        );
        fclose(f_stats);
        printf("Performances enregistrees dans stats.txt\n");
    }

    return 0;
}

