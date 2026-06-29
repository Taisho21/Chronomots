import subprocess
import os

dossier_script = os.path.dirname(os.path.abspath(__file__))
racine_projet = os.path.dirname(dossier_script)

nom = os.path.join(racine_projet, "projet")

fichiers = [
    os.path.join(racine_projet, "TheProjectGutenberg.txt"),
    os.path.join(racine_projet, "Harry_Potter_Prisonnier_Azkaban.txt"),
    os.path.join(racine_projet, "Insoutenable.txt"),
    os.path.join(racine_projet, "Dans_les_nuages.txt"),
    os.path.join(racine_projet, "sport_paume.txt")
]

algos = [1, 2] #
struc = [0, 1, 2] #

stats_path = os.path.join(racine_projet, "stats.txt")

if os.path.exists(stats_path):   
    os.remove(stats_path)

for fich in fichiers:
    for n in algos:
        for choix in struc:
            subprocess.run([nom, fich, str(choix), str(n), "0", "0", "0", "0"])