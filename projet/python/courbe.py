import matplotlib.pyplot as plt

couleur = ["red","blue","green","brown","pink","yellow"]
temps = {}
taille_fichier = []
i = 0

with open("stats.txt","r") as resul: #pas besoin d'ouvrir ou fermer le fichier, with le fait automatiquement c'est un tonton de reddit qui l'a dit 
    l = resul.readlines() #transforme en liste toute les lignes ! docstring.fr 
    for ligne in l:
        ligne = ligne.strip()

        parti = ligne.split(";") 

        fichier = parti[0]
        algo = parti[1].strip()
        structure = parti[2].strip() #ta modifié stat du coup y a un décalage et une nouvelle variable pour double ou simple
        tps = float(parti[3])

        nom = algo + " " + structure

        if nom not in temps:
            temps[nom] = []
        temps[nom].append(tps)

        if fichier not in taille_fichier:
            taille_fichier.append(fichier)


plt.figure(figsize=(12, 6))

i = 0
for nom, t_exec in temps.items():
    plt.plot(taille_fichier, t_exec, 'x-', linewidth=1, label=nom, c=couleur[i])
    i += 1

plt.title("Vue d'ensemble ")
plt.xlabel("Fichiers")
plt.ylabel("Temps en secondes")
plt.legend()


plt.tight_layout() 
plt.show()