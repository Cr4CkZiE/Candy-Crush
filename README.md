# Candy-Crush
Ce projet est réalisé sous le cadre d'un projet étudiant 
Membre du groupe n°2 :
 - BALBAS Lohann
 - BAYEUX Tristan
 
Voici notre projet pour la SAE101 :
Premierement, on a divisé le projet sous trois fichier .cpp donc il faudra compiler avec :
g++ main.cpp game.cpp grapich.cpp -o CandyCrush

Game.cpp contient tout ce qui est relatif au TP10 et aux fonctions liées à la gestion du jeu
Grapich.cpp contient les fonctions et constantes permettant l'affichage
Main.cpp contient les fonctions logistiques qui assemblent toutes les sous-fonctions

Notre jeu dispose de :
- un écran de chargement 
- un menu interactif
- un mode de jeu "classique"
- un mode de jeu "endless"
- un tableau des scores avec sauvegardes 

(Les sauvegardes sont faites via les fichiers .txt ayant pour nom classic.txt ou endless.txt)

Ainsi on peut jouer au mode de jeu classique :
- On vous demandera de choisir une taille de matrice entre comprise 4 et 100
- De choisir combien de bonbon différents dans le jeu entre 2 et 7
- Votre nom utilisateur 

Vous devez faire le maximum de points avec un nombre de coup attribué.
Le nombre de coup est égal à la taille de la matrice.

Vous pouvez vous déplacer à l'aide des touches 'z', 'q', 's', 'd' comme sur un jeu classique.
Une fois sur la case voulue, appuyez sur entrée pour la maintenir et réalisez un déplacement pour la faire glisser.

Le score est calculé en additionnant la somme des nombres détruits durant la partie

On peut aussi jouer au mode de jeu endless : 
De même, on vous demandera de choisir une taille de matrice, combien de bonbon différents et votre nom utilisateur.

Vous devez faire le maximum de points avec un nombre de coup attribué.
Le nombre de coup est égal à la taille de la matrice mais augmente tout au long de la partie en fonction de votre performance.

Le score est calculé en additionnant la somme des nombres détruits durant la partie.

La différence ici est que la grille est reremplit à chaque tour.

//Les points faibles :
- Il n'y a aucun moyen de revenir en arrière on peut seulement appuyer sur échap pour fermer le jeu.
il faut relancer le jeu entre les parties ou pour voir le leaderboard.

- Lors de la selection du mode de jeu, un input en plus est requis pour lancer l'affichage.
il faut selectionner avec 'Entrée' puis appuyer sur une touche quelquonque.

//Les points forts : 
- La desactivation du mode canonique du terminal nous a permi de rendre le jeu plus vif et immersif

- Éléments graphiques travaillés grâces à divers codes d'échappement ANSI 

- Sauvegarde des meilleurs scores par utilisateur

- Menus graphiques interactifs
