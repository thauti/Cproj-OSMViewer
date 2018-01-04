# Conduite de Projet

![Exemple](screenshot.png)

## Compilation

Pour compiler le projet, il faut utiliser la commande "make" dans le dossier courant.

## Execution

Le fichier executable un fois compilé se trouve dans le dossier "bin".
Les fichiers d'exemples se trouvent dans le dossier "example"

Le programme prend un fichier OSM en argument.

Un exemple typique d'execution :
./bin/osm example/03_paris_ile_saint_louis.osm

Le projet implémente : 
- Les rues (avec les différents types associés)
- Les bâtiments
- Les cours d'eau
- Les lacs
- Les espaces verts
- Les rivages

La possibilité d'afficher/masquer des données
L'export en PNG (dans un fichier output.png)