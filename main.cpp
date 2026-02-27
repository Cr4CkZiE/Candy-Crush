#include "game.h"
#include "grapich.h"

/**
 * @file main.cpp
 * @mainpage Jeu Candy Crush - Projet C++
 * @section description Description du projet
 * Ce projet est une version sur terminal linux du  jeu Candy Crush.
 * @section commands Commandes de jeu
 * - Z / S / Q / D : Déplacement généraux
 * - Entrée : Sélection
 * - Echap : Quitter le programme.
 * @authors Lohann BALBAS & Tristan BAYEUX
 */

#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

// --- STRUCTURE ---
/*
* @class InputManager
* @brief permet d'activer/désactiver le mode "raw" sur le terminal
** @details
* - Le RawMode permet de désactiver l'appuie sur entrée et l'affichage sur le terminal
* - Il rend le jeu plus fluide et immersif.
*/
class InputManager {
public:
    /**
    * @brief active le mode raw du terminal :
    * - desactive le mode canonique
    * - desactive l'echo
    * @details l'ancienne configuration est stockée dans @ref _oldTerm
    */
void enableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    _oldTerm = term;

    term.c_lflag &= ~(ICANON | ECHO); // desactive entrée et affichage
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
    * @brief desactive le mode raw du terminal :
    * L'ancienne configuration est restaurée
    */
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &_oldTerm);
}

private:
/**
*@brief Stockage de la configuration initiale
*/
termios _oldTerm;
};

// --- INITIALISATION ---

/**
*@brief Gère la saisie interactive de la taille de la matrice de jeu.
**@return size_t La taille de la matrice validée (supérieure ou égale à 4).
**@details
* - Utilise @ref affichVectStr pour afficher le cadre ASCII.
* - Utilise @ref inputDigitUser pour garantir que seule une valeur numérique est saisie.
* - En cas d'erreur (saisie vide ou < 4), un message rouge est affiché via @ref couleur.
**@note La saisie est limitée à 2 caractères numériques pour éviter des grilles trop larges.
*@see clearScreen, goTo, inputDigitUser
*/
size_t initMatSize(){
    string input;
    size_t size;
    vector <string> sizeRequest {
        "",
        "",
        "                           ________________________________________________________________________________________",
        "                         .                                                                                           .",
        "                        |                                                                                             |",
        "                        |                         Veuillez saisir la taille de la matrice :                           |",
        "                        |                                                                                             |",
        "                        |                                                                                             |",
        "                        |                                                                                             |",
        "                         ' __________________________________________________________________________________________'",
    };

    clearScreen();
    affichVectStr(sizeRequest);

    while (true){
        goTo(93,6);
        input = inputDigitUser(2);

        if (input.empty()) {
            clearScreen();
            affichVectStr(sizeRequest);

            goTo(60,8);
            couleur(KRouge);
            cout <<"Errreur : Saisie vide ! " <<  flush;
            couleur(KReset);
            continue;
        }

        size = stoi(input);

        if (size < 4){
            clearScreen();
            affichVectStr(sizeRequest);

            goTo(51,8);
            couleur(KRouge);
            cout << "Erreur : Veuillez saisir une taille >= 4 !" <<endl;
            couleur(KReset);
        }
        else break;
    }

    return size;

}

/**
*@brief Gère la saisie interactive du nombre de types de bonbons différents.
**@return unsigned Le nombre de types de bonbons
**@details
* - Utilise @ref affichVectStr pour le rendu du cadre de saisie.
* - Utilise @ref inputDigitUser(1) pour limiter la saisie à un seul chiffre.
* - Boucle tant que la saisie est vide ou hors de l'intervalle [2, 7].
*@see initMatSize, inputDigitUser, couleur
*/
unsigned initNbCandies(){
    string input;
    unsigned nb;
    vector <string> nbRequest {
        "",
        "",
        "                           ________________________________________________________________________________________",
        "                         .                                                                                           .",
        "                        |                                                                                             |",
        "                        |                         Veuillez saisir le nombre de bonbons :                              |",
        "                        |                                                                                             |",
        "                        |                                                                                             |",
        "                        |                                                                                             |",
        "                         ' __________________________________________________________________________________________'",
    };

    clearScreen();
    affichVectStr(nbRequest);
    while (true){
        goTo(90,6);
        input = inputDigitUser(1);

        if (input.empty()) {
            clearScreen();
            affichVectStr(nbRequest);

            goTo(60,8);
            couleur(KRouge);
            cout <<"Errreur : Saisie vide ! " <<  flush;
            couleur(KReset);
            continue;
        }

        nb = stoi(input);

        if (nb > 7 || nb < 2){
            clearScreen();
            affichVectStr(nbRequest);

            goTo(51,8);
            couleur(KRouge);
            cout << "Erreur : Veuillez saisir un nombre compris entre 2 et 7 ! " <<endl;
            couleur(KReset);
        }
        else break;
    }
    return nb;
}

/**
*@brief Gère la saisie interactive du nom du joueur
**@param p Référence vers la structure @ref Joueur
**@details
* - Utilise @ref affichElemDecor pour dessiner le cadre de saisie.
* - Utilise @ref inputUser(20) pour limiter la longueur du nom à 20 caractères.
* - En cas de saisie vide, affiche un message d'alerte en rouge via @ref couleur.
**@note Cette fonction est indispensable avant d'appeler @ref ajouter_score.
*@see inputUser, clearScreen, goTo
*/
void initPName(Joueur &p){
    string input;

    clearScreen();
    affichElemDecor(KGrandeCase, 24,3,30000);
    goTo(57, 6);
    cout << " Entrez votre nom : " << flush;

    while (true){
        goTo(77,6);
        input = inputUser(20);

        if (input.empty()) {
            clearScreen();
            affichElemDecor(KGrandeCase, 24,3,30000);
            goTo(57, 6);
            cout << " Entrez votre nom : " << flush;

            goTo(60,8);
            couleur(KRouge);
            cout <<"Errreur : Saisie vide ! " <<  flush;
            couleur(KReset);
            continue;
        }
        else break;
    }
    p.nom = input;
}

/**
*@brief Gère la sélection interactive du mode de jeu
**@param mode Le nom du mode de jeu
**@details
* - Utilise @ref affichElemDecor pour le cadre visuel.
* - Boucle tant que la saisie ne correspond pas exactement à l'un des trois mots-clés.
* - En cas d'erreur, un message d'alerte rouge s'affiche via @ref couleur.
**@note La saisie est sensible à la casse (minuscules attendues).
*@see initPName, inputUser, lire_score
*/
void initMode(string &mode){
    clearScreen();
    affichElemDecor(KGrandeCase, 24,3,30000);
    goTo(45, 6);
    cout << "Quel mode de jeu (classic, duel, endless) ? : " << flush;

    while (true){
        goTo(91,6);
        mode = inputUser(20);

        if (mode.empty() || (mode != "classic" && mode != "duel" && mode != "endless")) {
            clearScreen();
            affichElemDecor(KGrandeCase, 24,3,30000);
            goTo(45, 6);
            cout << "Quel mode de jeu (classic, duel, endless) ? : " << flush;

            goTo(57,8);
            couleur(KRouge);
            cout <<"Errreur : Saisie invalide ! " <<  flush;
            couleur(KReset);
        }
        else break;
    }
}

// --- DISPLAY GRILLE ---

/**
*@brief Affiche une ligne de la grille
** Cette fonction affiche le numéro de la ligne,
* Un nombre avec sa couleur associé,
* Si une case correspond à la position du curseur, elle est affichée avec un style spécial (clignotant et inversé).
**@param v Le vecteur de type @ref line représentant la ligne à afficher.
*@param numLigne L'indice de la ligne actuelle
*@param pos La position actuelle du curseur (@ref maPosition) pour le rendu spécial.
**@details
* - Gère l'alignement des numéros de ligne (ajout d'un espace pour les chiffres < 9).
* - Utilise @ref couleur pour assigner une couleur unique à chaque valeur de bonbon (@c elem + 29).
* - Les cases vides (@c 0) sont affichées comme des espaces.
* - Le curseur utilise le code ANSI @c \033[5;7;1m (Gras, Inversé, Clignotant).
**@see displayGrid, couleur
*/
void affichVectLine(const line &v, const unsigned int &numLigne, const maPosition &pos){
    cout << numLigne+1;
    if (numLigne < 9){ //arrangement nombre à deux chiffres
        cout << " ";
    }
    cout <<" - | "; //affiche numéro ligne

    for (unsigned int numCol = 0; numCol < v.size(); numCol++){
        unsigned int elem = v[numCol];

        if (numLigne == pos.ord && numCol == pos.abs){
            cout << "\033[5;7;1m";
        }
        if (elem == 0){
            if (numLigne == pos.ord && numCol == pos.abs){
                cout << "\033[5;7;1m";
            }
            else{
                couleur(0);
            }
            cout << " ";
        }
        else{
            couleur(elem + 29);
            cout << elem;
        }

        couleur(0);
        cout << " | ";
    }
    cout << endl;
}

/**
*@brief Affiche une barre de séparation horizontale adaptée à la taille de la grille.
**@param grid La matrice de jeu (type @ref mat) utilisée pour déterminer la largeur.
*/
void affichBarre(mat & grid){
    string barre = "     ";
    for (unsigned int i = 0; i < 4*grid.size()+1; i++){
        if (i%4==0) {
            barre += '+';
        } else {
            barre += '-';
        }
    }
    cout << barre << endl;
}

/**
*@brief Affiche les indices des colonnes (abscisses)
**Cette fonction génère la ligne d'en-tête du tableau.
**@param grid La matrice de jeu (type @ref mat)
*/
void affichAbs(mat & grid){
    unsigned int taille = 9; //ne peut pas affciher à 3 chiffres

    if (grid.size()<9){
        taille = grid.size();
    }

    cout << "     |";
    for (unsigned int i = 1; i < taille+1; i++){
        cout << " " << i << " |";
    }

    if (grid.size()>9){
        for (unsigned int i = 10; i < grid.size()+1; i++){
            cout << i << " |";
        }
    }

    cout << endl;
}

/**
*@brief Gère l'affichage complet de l'interface de jeu dans le terminal.
** la grille de jeu colorée avec le curseur, les numéros de lignes/colonnes,
* le score actuel du joueur et le nombre de coups restants.
**@param grid La matrice de jeu (type @ref mat) à afficher.
*@param pos La position actuelle du curseur pour le rendu spécifique dans @ref affichVectLine.
*@param p L'objet @ref Joueur contenant le nom et le score à afficher.
*@param coup Le nombre de coups restants dans la partie.
*@param KMatSize La taille de la matrice (utilisée pour le calibrage de l'affichage)..
**@see affichVectLine
*/
void displayGrid(mat & grid, maPosition &pos, Joueur p, unsigned coup, size_t KMatSize){
    clearScreen();
    couleur(KReset);

    affichAbs(grid);
    affichBarre(grid);

    for (unsigned int numLigne = 0; numLigne < grid.size(); numLigne++){
        affichVectLine(grid[numLigne],numLigne, pos);
    }

    affichBarre(grid);

    cout << "\r\n|| " << p.nom <<"'s score : " << p.score << endl;
    cout << "|| " << "Nombre de coups restants : " << coup <<endl;
}

/**
*@brief Affiche le menu principal interactif
**@param select Indice de l'option actuellement sélectionnée (0: Play, 1: Endless, 2: Leaderboard).
*/
void displayMenu(const unsigned &select){
    clearScreen();

    if (select==0){
        couleur(1);
        couleur(5);
    }
    couleur(KMAgenta);
    affichElemDecor(KGrandeCase, 35,1);
    affichElemDecor(KPLAY, 70,3);
    couleur(KReset);

    if (select==1){
        couleur(1);
        couleur(5);
    }

    couleur(KCyan);
    affichElemDecor(KPetiteCase, 35,10);
    affichElemDecor(KEndless, 68,11);
    couleur(KReset);

    if (select==2){
        couleur(1);
        couleur(5);
    }
    couleur(KVert);
    affichElemDecor(KPetiteCase, 35,18);
    affichElemDecor(KLeaderboard, 58,19);
    couleur(KReset);

    affichDecor();
}

/**
*@brief Génère et affiche l'écran de chargement animé du jeu.
*/
void loadingScreen(){
    couleur(KReset);
    affichVectCoulStr(KCandyCrush);

    couleur(KFlash);
    couleur(KJaune);
    affichVectStr(KPressEnter);
    couleur(KReset);

    couleur(KCyan);
    affichDecor(15000);
    couleur(KReset);
}

// --- MAIN ---

/**
*@brief Gère la navigation dans les options du menu principal.
**@param c Le caractère saisi par l'utilisateur
*@param select l'entier représentant l'option choisie (0 à 2).
**@details
* - Touche **'z'** : Décrémente l'indice. Si @c select est à 0, il passe à 2.
* - Touche **'s'** : Incrémente l'indice. Si @c select est à 2, il passe à 0.
*/
void moveMenu (const char &c, unsigned &select){
    if (c=='z'){
        if (select==0) select = 2;
        else -- select;
    }
    else if (c=='s'){
        if (select==2) select = 0;
        else ++ select;
    }
}

/**
 * @brief Gère la boucle de jeu principale pour le mode "Classique".
 * - Paramétrage de la taille, des bonbons et du joueur.
 * - Déplacement du curseur sur la grille.
 * - Échange de deux bonbons et décrémentation des coups.
 * - Détection et suppression des combinaisons (streaks) en boucle.
 * - Affichage du score final après épuisement des coups.
 * * @param grid Matrice de jeu
 * @param KMatSize Taille de la matrice
 * @param KNbCandies Nombre de types de bonbons
 * @param pos Position du curseur de sélection.
 * @return Joueur L'objet contenant le nom et le score final pour la sauvegarde des scores
 */
Joueur classicMode(mat &grid, size_t &KMatSize, unsigned &KNbCandies, maPosition &pos){
    char c;
    bool gameStarted = false;
    bool caseSelect = false;

    Joueur p;
     unsigned coup = 1;

    while (coup != 0 && cin.get(c) && c!=27){
        if (!gameStarted){

            KMatSize = initMatSize();
            cout << KMatSize << endl;
            coup = KMatSize;
            usleep(100000);

            KNbCandies = initNbCandies();
            usleep(1000000);

            initPName(p);
            usleep(1000000);

            grid.resize(KMatSize);
            initGrid(grid, KMatSize, KNbCandies);

            displayGrid(grid, pos, p, coup, KMatSize); // affichage 1

            usleep(1000000);

            gameStarted = true;
            continue;
        }
        if (gameStarted){
            if (!caseSelect){
                if (c==10) caseSelect = true;
                else{
                    inPosMakeAMove(grid, pos, c);
                    displayGrid(grid,pos,p, coup, KMatSize);
                }
            } else {
                if ((c=='z' && pos.ord!=0) || (c=='s' && pos.ord!=KMatSize-1) || (c=='q' && pos.abs!=0) || (c=='d' && pos.abs!=KMatSize-1)){
                    char direction = c;
                    makeAMove(grid, pos, direction);
                    coup -= 1;

                    caseSelect = false;
                    displayGrid(grid,pos,p, coup, KMatSize);

                    bool Streak = true;
                    maPosition streakPos;
                    unsigned howMany;
                    while (Streak) {
                        Streak = false;

                        if (atLeastThreeInARow(grid, streakPos, howMany)) {
                            removalInRow(grid, streakPos, howMany);
                            displayGrid(grid, pos,p, coup, KMatSize);
                            usleep(1000000);
                            Streak = true;
                        }

                        if (atLeastThreeInAColumn(grid, streakPos, howMany)) {
                            p.score = p.score + (grid[streakPos.ord][streakPos.abs] * howMany);
                            removalInColumn(grid, streakPos, howMany);
                            displayGrid(grid, pos,p, coup, KMatSize);
                            usleep(1000000);
                            Streak = true;
                        }
                    }
                }
            }
        }
    }

    clearScreen();
    affichElemDecor(KGrandeCase, 35,1);
    goTo(73,4);
    cout << "Congratulations !" << flush;
    goTo(74,5);
    cout << "Your score : " << p.score << flush;
    goTo(1,10);

    return p;
}

/**
 * @brief Gère la boucle de jeu pour le mode "Endless"
 ** chaque alignement réussi rapporte des points qui peuvent restaurer le compteur de coups.
 * * @param grid Matrice de jeu.
 * @param KMatSize Taille de la matrice définie par l'utilisateur.
 * @param KNbCandies Nombre de types de bonbons.
 * @param pos Position du curseur.
 * @return Joueur L'objet contenant les statistiques finales du joueur.
 */
Joueur endlessMode(mat &grid, size_t &KMatSize, unsigned &KNbCandies, maPosition &pos){
    char c;
    bool gameStarted = false;
    bool caseSelect = false;

    Joueur p;
    unsigned coup = 1;

    while (coup != 0 && cin.get(c) && c!=27){
        if (!gameStarted){

            KMatSize = initMatSize();
            usleep(100000);

            KNbCandies = initNbCandies();
            usleep(1000000);

            initPName(p);
            usleep(1000000);

            grid.resize(KMatSize);
            initGrid(grid, KMatSize, KNbCandies);

            coup=KMatSize;
            usleep(1000000);

            displayGrid(grid, pos, p, coup, KMatSize); // affichage 1

            usleep(1000000);

            gameStarted = true;
            continue;
        }
        if (gameStarted){
            if (!caseSelect){
                if (c==10) caseSelect = true;
                else{
                    inPosMakeAMove(grid, pos, c);
                    displayGrid(grid,pos,p, coup, KMatSize);
                }
            } else {
                if ((c=='z' && pos.ord!=0) || (c=='s' && pos.ord!=KMatSize-1) || (c=='q' && pos.abs!=0) || (c=='d' && pos.abs!=KMatSize-1)){
                    char direction = c;
                    makeAMove(grid, pos, direction);
                    coup -= 1;

                    caseSelect = false;
                    displayGrid(grid,pos,p, coup, KMatSize);

                    bool Streak = true;
                    maPosition streakPos;
                    unsigned howMany;
                    int points = 0;
                    while (Streak) {
                        Streak = false;

                        if (atLeastThreeInARow(grid, streakPos, howMany)) {
                            p.score = p.score + (grid[streakPos.ord][streakPos.abs] * howMany);
                            points += (grid[streakPos.ord][streakPos.abs] * howMany);
                            removalInRow(grid, streakPos, howMany);
                            displayGrid(grid, pos,p, coup, KMatSize);
                            usleep(1000000);
                            Streak = true;

                            refill(grid,KNbCandies);

                        }

                        if (atLeastThreeInAColumn(grid, streakPos, howMany)) {
                            p.score = p.score + (grid[streakPos.ord][streakPos.abs] * howMany);
                            points += (grid[streakPos.ord][streakPos.abs] * howMany);
                            removalInColumn(grid, streakPos, howMany);
                            displayGrid(grid, pos,p, coup, KMatSize);
                            usleep(1000000);
                            Streak = true;

                            refill(grid,KNbCandies);

                        }
                    }
                    coup += points%10;
                }
            }
        }
    }

    clearScreen();
    affichElemDecor(KGrandeCase, 35,1);
    goTo(73,4);
    cout << "Congratulations !" << flush;
    goTo(74,5);
    cout << "Your score : " << p.score << flush;
    goTo(1,10);

    return p;
}

int main(){
    // - Déclaration
    mat grid;
    size_t KMatSize;
    unsigned KNbCandies;

    maPosition pos;

    clearScreen();
    loadingScreen();

    InputManager input;
    input.enableRawMode();

    bool loadingScreen = true;

    unsigned select = 0;

    char c;
    while (cin.get(c) && c!=27){
        if (loadingScreen){
            if (c == 10){
                displayMenu(select);
                loadingScreen = false;
            }
        }
        else{
            if (c==10) break;
            moveMenu(c,select);
            displayMenu(select);
        }
    }
    Joueur j;
    if (select == 0) {
        j =classicMode(grid, KMatSize, KNbCandies, pos);
        ajouter_score("classic" , j.nom, j.score);
    }
    else if (select == 1){
        j=endlessMode(grid, KMatSize, KNbCandies, pos);
        ajouter_score("endless", j.nom, j.score);
    }
    else if (select == 2) {
        string mode;
        initMode(mode);
        clearScreen();

        affichVectStr(KLeaderboard);
        cout << endl;

        vector<Joueur> lb = lire_score(mode);
        tri_score(lb);
        if (lb.size() == 0) cout << "Aucun score enregistré";
        else if (lb.size()<10){
            for (size_t i=0; i<lb.size(); ++i){
                cout << "|| " << lb[i].nom << " : " << lb[i].score << endl;
            }
        } else {
            for (size_t i=0; i<10; ++i){
                cout << lb[i].nom << " : " << lb[i].score << endl;
            }
        }
    }
    input.disableRawMode();
    return 0;
}
