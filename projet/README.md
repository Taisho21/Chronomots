# CHRONOMOTS

Ce projet en C permet d'analyser des fichiers textes, de compter les occurrences de mots et de trier les résultats. Il compare les performances de différentes structures de données (Listes chaînées simples/doubles, Tableaux dynamiques) et algorithmes de tri (Bulle, Fusion, QuickSort).

## Organisation des fichiers

Pour que la compilation fonctionne, vos fichiers doivent être organisés ainsi :

projet/

├── include/
│   ├── algo.h
│   ├── lecture.h
│   └── projet.h
├── src/
│   ├── algos.c
│   ├── gererMem.c
│   ├── lecture.c
│   ├── main.c
│   └── tableau.c
├── python/
|   ├──  benchmark.py
|   ├── courbe.py
│   └── stats.txt
|
├──ensemble_fichier.txt
└──README.md



--------------------------- COMPILATION :------------------------------------------
Ouvrez le terminal à la racine du projet et lancez à la commande suivante :

gcc -Wall -Wextra -Iinclude src/main.c src/algos.c src/lecture.c src/gererMem.c src/tableau.c -o projet

## Mode Interactif :
Lancez simplement le programme avec le fichier texte à analyser. Un menu vous guidera.

LINUX : ./projet votre_texte.txt
WINDOWS : ./projet.exe votre_texte.txt

------------------------------------------------------------------------------------
## Mode avec les arguments :

./projet <Fichier> <Struct> <Algo> <Nb_Ban> <Taille_Min> <Nb_Voulu> <N_Affichage> 

Fichier : type texte (ex: livre.txt).

Struct : 0=Liste Simple, 1=Liste Double, 2=Tableau.

Algo :
Si Liste : 1=Fusion, 2=Bulle.

Si Tableau : 1=Bulle, 2=QuickSort.


Nb_Ban : Nombre de mots à exclure (bannis).

Taille_Min : Taille minimale pour garder un mot (0 = tout garder).

Nb_Voulu : Nombre de mots spécifiques à cibler (liste blanche).

N_Affichage : Nombre de mots à afficher à la fin (0 = tout afficher).

EXEMPLE : 
./projet texte.txt 2 2 0 0 0 10

(Analyse texte.txt avec Tableau + QuickSort, sans filtres, affiche les 10 premiers).



Performance & Graphiques
Des scripts Python sont fournis pour automatiser les tests et visualiser les résultats.

Accéder au fichier python dans le terminal et exécutez : 

1.python benchmark.py qui va permettre d'automatiser 
2.python courbe.py