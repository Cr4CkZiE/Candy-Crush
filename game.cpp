#include "game.h"

// --- FONCTIONS GESTION ---
// Gestion entrée utilisateur

/**
*@brief Récupère une saisie utilisateur de n'importe quel caractère
** Elle lit les caractères un par un et limite la longueur de la chaîne grâce à sizeMax,
* Elle gère aussi l'effacement des caractères sur le terminal
** @param sizeMax La longueur maximale de la chaîne
** @return string La chaîne saisie
** @details
* - ASCII 10 correspond à 'Entrée'
* - ASCII 127 correspond à 'Supprimer'
* - '\b \b' pour effacer le caractère sur le terminal
*/
string inputUser(unsigned sizeMax){
    string input = "";
    char c;

    while (cin.get(c) && c!=10) {
        if (c!= 127 && input.size()<sizeMax){
            input += c;
            cout << c << flush;
        }
        else if ( c == 127 && !input.empty()) {
            input.pop_back();
            cout << "\b \b" << flush;
        }
    }
    cout << endl;
    return input;
}

/**
*@brief Récupère une saisie utilisateur composée uniquement de chiffre
** Elle lit les caractères un par un et limite la longueur de la chaîne grâce à sizeMax,
* Elle gère aussi l'effacement des caractères sur le terminal
** @param sizeMax La longueur maximale de la chaîne
** @return string La chaîne numérique saisie
** @details
* - caractères non numériques ignorés
* - ASCII 10 correspond à 'Entrée'
* - ASCII 127 correspond à 'Supprimer'
* - '\b \b' pour effacer le caractère sur le terminal
*/
string inputDigitUser(unsigned sizeMax){
    string input = "";
    char c;

    while (cin.get(c) && c!=10) {
        if (isdigit(c) && input.size()<sizeMax){
            input += c;
            cout << c << flush;
        }
        else if ( c == 127 && !input.empty()) {
            input.pop_back();
            cout << "\b \b" << flush;
        }
    }
    cout << endl;
    return input;
}

// Gestion score (Tristan)

/**
 *@brief Lit les scores enregistrés depuis un fichier texte portant le nom du mode de jeu
 ** Ouvre le fichier correspondant au mode de jeu spécifié et extrait le nom du joueur ainsi que son score : "Nom : Score".
 ** @param mode Le nom du mode de jeu (utilisé pour déterminer le nom du fichier .txt).
 *@return std::vector<Joueur> Vecteur contenant tous les objets @ref Joueur
 **@note Si le fichier n'existe pas, la fonction retourne un vecteur vide.
 ** @see Joueur
 */
vector<Joueur> lire_score(string mode) {
    string fname = mode + ".txt";
    ifstream file(fname);
    vector<Joueur> s;
    string line;

    while (getline(file, line)) {
        string nom;
        string score;
        bool flag = true;

        for (char c : line) {
            if (flag) {
                if (c == ':') {
                    flag = false;
                } else if (c != ' ') {
                    nom += c;
                }
            } else {
                if (isdigit(c)) {
                    score += c;
                }
            }
        }

        Joueur j;
        j.nom = nom;
        j.score = stoi(score);
        s.push_back(j);
    }

    return s;
}

/**
 *@brief Ajoute ou met à jour le score d'un joueur dans le classement.
 **@param mode Le nom du mode de jeu
 *@param nom Le nom du joueur
 *@param score Le score obtenu par le joueur
 */
void ajouter_score(string mode, string nom, size_t score) {
    if (nom.empty()) {
        cout << "Pas d'enregistrement effectué, bonne journée à vous" << endl;
        return;
    }

    vector<Joueur> s = lire_score(mode);
    bool flag = false;
    size_t i = 0;

    while (i < s.size()) {
        if (s[i].nom == nom) {
            char a;
            cout << "Un score est deja associé à ce nom, est-ce bien vous ? (y/n) : ";
            cin >> a;
            a = tolower(a);

            if (a == 'y') {
                if (score > s[i].score) {
                    cout << "Bien joué, nouveau record !" << endl;
                    s[i].score = score;
                } else {
                    cout << "Vous n'avez pas battu votre record" << endl;
                }
                flag = true;
                break;
            } else {
                cout << "Entrez un autre nom : ";
                nom = inputUser(20);
                i = -1;
            }
        }
        i++;
    }

    if (!flag) {
        Joueur j;
        j.nom = nom;
        j.score = score;
        s.push_back(j);
    }

    ofstream file(mode + ".txt");
    for (Joueur& j : s) {
        file << j.nom << " : " << j.score << endl;
    }
    cout << "Score enregistré !" << endl;
}

/**
*@brief Trie la struct @ref Joueur par score décroissant
** Elle utilise l'algorithme de tri par sélection
**@param s Référence vers le vecteur de @ref Joueur à trier
*@see Joueur
*/
void tri_score(vector<Joueur>& s) {
    size_t n = s.size();

    for (size_t i = 0; i < n - 1; i++) {
        size_t max_ind = i;

        for (size_t j = i + 1; j < n; j++) {
            if (s[j].score > s[max_ind].score) {
                max_ind = j;
            }
        }

        if (max_ind != i) {
            Joueur tmp = s[i];
            s[i] = s[max_ind];
            s[max_ind] = tmp;
        }
    }
}

// --- FONCTIONS JEU ---
// Grille

/**
*@brief Initialise la grille de jeu avec des valeurs aléatoires
** Remplit une matrice carrée avec des nombres compris entre 1 et @p KNbCandies
**@param grid La matrice ( type @ref mat) à initialiser
*@param matSize La taille du côté de la grille
*@param KNbCandies Le nombre de types de bonbons différents
**@details
* - Utilise @c srand(time(0)) pour réinitialiser la graine du générateur de nombres aléatoires
 */
void initGrid (mat &grid, const size_t & matSize, const unsigned  &KNbCandies){
    srand(time(0)); //Clé de génération nombre aléatoire

    for (unsigned int i = 0; i < matSize; i++){
        line ligne (matSize);
        for (unsigned int y = 0; y < matSize; y++){
            unsigned int randomNum = rand() % KNbCandies + 1; //Calcul du nombre aléatoire

            ligne[y] = randomNum;
        }
        grid[i] = ligne;
    }
}

//Mouvement

/**
*@brief Gère le déplacement du curseur de sélection sur la grille
*à l'aide des touches directionnelles (Z, Q, S, D)
*elle empêche aussi le curseur de sortir de la matrice.
**@param grid La matrice de jeu
*@param pos La position actuelle du curseur
*@param c Le caractère saisi par l'utilisateur
*/
void inPosMakeAMove(mat & grid, maPosition & pos, char &c){
    switch(c){

    case 'q':
        if (pos.abs==0){
        }
        else{
            pos.abs -= 1;
        }

        break;

    case 'd':
            if (pos.abs==grid.size()-1){
            }
            else{
                pos.abs += 1;
            }

            break;

        case 'z':
        if (pos.ord==0){
        }
        else{
            pos.ord -= 1;
        }

        break;

    case 's':
        if (pos.ord==grid.size()-1){
        }

        else{
            pos.ord += 1;
        }

        break;
    }
}

/**
*@brief échange de deux éléments dans la grille selon une direction
**Cette fonction calcule la position cible (@p target) à partir de la position actuelle (@p pos)
* puis les permutes dans la matrice selon la direction
**@param grid La matrice de jeu
*@param pos La position actuelle
*@param direction Caractère ('z','q','s','d')
** @note La fonction vérifie les limites de la matrice avant d'échanger
*/
void makeAMove (mat & grid, maPosition & pos, const char & direction){
    maPosition target = pos;

    switch(direction){

    case 'q':
        if (pos.abs==0){
            cout << "Valeur impossible" << endl;
        }
        else{
            target.abs -= 1;
            cout << "Valeur possible vers : " << grid[target.ord][target.abs] << endl;
        }

        break;

    case 'd':
        if (pos.abs==grid.size()-1){
            cout << "Valeur impossible" << endl;
        }
        else{
            target.abs += 1;
            cout << "Valeur possible vers : " << grid[target.ord][target.abs] << endl;
        }

        break;

    case 'z':
        if (pos.ord==0){
            cout << "Valeur impossible" << endl;
        }
        else{
            target.ord -= 1;
            cout << "Valeur possible vers : " << grid[target.ord][target.abs] << endl;
        }

        break;

    case 's':
        if (pos.abs==grid.size()-1){
            cout << "Valeur impossible" << endl;
        }

        else{
            target.ord += 1;
            cout << "Valeur possible vers : " << grid[target.ord][target.abs] << endl;
        }

        break;
    }

    // CHANGEMENT DES POSITIONS SANS TEMP
    grid[pos.ord][pos.abs] += grid[target.ord][target.abs];
    grid[target.ord][target.abs] = grid[pos.ord][pos.abs] - grid[target.ord][target.abs];
    grid[pos.ord][pos.abs] -= grid[target.ord][target.abs];

    pos.ord = target.ord;
    pos.abs = target.abs;
}

// Detection streak

/**
*@brief Détecte la présence d'une streak dans une colonne
**@param grid La matrice de jeu
*@param pos La position de départ
*@param howMany Le nombre total d'éléments alignés
**@return true si un alignement est trouvé, false sinon.
**@note La position @p pos.ord retournée correspond à l'index de la première case de la suite.
*/
bool atLeastThreeInAColumn(const mat &grid, maPosition &pos, unsigned &howMany){
    size_t x = 0;
    while (x < grid.size()){
        size_t y = 0;
        howMany = 1;
        while (y < grid.size()-1){
            if (grid[y][x]==grid[y+1][x] && grid[y][x]!=0) ++howMany;
            else howMany=1;

            ++y;
            if (howMany == 3){
                pos.abs=x;
                pos.ord=y-2;
                while (y < grid.size()-1){
                    if (grid[y][x]!=grid[y+1][x]) break;
                    ++howMany;
                    ++y;
                }
                return true;
            }
        }

        ++x;
    }
    cout << "false" << endl;
    return false;
}

/**
*@brief Détecte la présence d'une streak dans une ligne
**@param grid La matrice de jeu
*@param pos La position de départ
*@param howMany Le nombre total d'éléments alignés
**@return true si un alignement est trouvé, false sinon.
**@note La position @p pos.abs retournée correspond à l'index de la première case de la suite.
*/
bool atLeastThreeInARow(const mat &grid, maPosition &pos, unsigned &howMany){
    size_t y = 0;
    while (y < grid.size()){
        size_t x = 0;
        howMany = 1;
        while (x < grid.size()-1){
            if (grid[y][x]==grid[y][x+1] && grid[y][x] != 0) ++howMany;
            else howMany=1;

            ++x;
            if (howMany == 3){
                pos.abs=x-2;
                pos.ord=y;
                while (x < grid.size()-1){
                    if (grid[y][x]!=grid[y][x+1]) break;
                    ++howMany;
                    ++x;
                }
                return true;
            }
        }
        ++y;
    }
    return false;
}

//Remove streak

/**
*@brief Supprime un alignement vertical et fait monter les éléments situés au-dessous.
** Remplace les bonbons alignés par des zéros
**@param grid La matrice de jeu à modifier.
*@param pos La position de départ (haut) de l'alignement à supprimer.
*@param howMany Le nombre d'éléments à supprimer.
 */
void removalInColumn (mat &grid, maPosition &pos, const unsigned &howMany){
    for (size_t i = 0; i < howMany; ++i){
        grid[pos.ord+i][pos.abs]=0;
    }

    // -- Méthode double Index

    size_t yNonNul = pos.ord;

    //On remonte
    for (size_t y = pos.ord; y < grid.size(); ++y){
        if (grid[y][pos.abs]!=0){
            grid[yNonNul][pos.abs] = grid[y][pos.abs];

            ++yNonNul;
        }
    }

    // On remplit le bas par des 0
    for (size_t y = yNonNul; y < grid.size(); ++y){
        grid[y][pos.abs] = 0;
    }
}

/**
*@brief Supprime un alignement horizontal et fait monter les éléments situés au-dessous.
** Remplace les bonbons alignés par des zéros graĉe a la fonction @ref removalInColumn
**@param grid La matrice de jeu à modifier.
*@param pos La position de départ (haut) de l'alignement à supprimer.
*@param howMany Le nombre d'éléments à supprimer.
 */
void removalInRow (mat &grid, maPosition &pos, const unsigned  &howMany){

    for (size_t i = 0; i < howMany; ++i){
        maPosition courant;
        courant.abs = pos.abs + i;
        courant.ord = pos.ord;

        removalInColumn(grid, courant, 1);
    }
}

// Refill Grille

/**
*@brief Remplit les cases vides de la grille par des nombres aléatoires
**@param grid La matrice de jeu
*@param KNbCandies Le nombre de types de bonbons possible à générer
*/
void refill(mat &grid, unsigned KNbCandies){
    // grid est carrée
    size_t i =0;
    bool flag;
    while (i<grid.size()){
        flag = false;
        if(grid[grid.size()-1][i]==0){
            grid[grid.size()-1][i]= rand() % KNbCandies + 1;
        }
        size_t j = grid.size()-1;
        while (j>0){
            if (grid[j-1][i]==0){
                flag = true;
                grid[j-1][i]=grid[j][i];
                grid[j][i]=0;
            }
            j-=1;
        }
        if (!flag){
            i+=1;
        }

    }
}

