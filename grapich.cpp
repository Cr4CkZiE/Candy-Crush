#include "grapich.h"

// --- DECLARATION ELEMENTS GRAPHIQUES TERMINAL ---
/** @name Element graphiques
* Vecteurs permettants l'affichage d'éléments visuels
* @{ */
const vector <string> KCandyCrush{ ///< Logo Candy Crush
    "||       _____          ____  _____   ______        _____    _____      _____             _____        _____    ____   ____          ______   ____   ____ ",
    "||   ___|\\    \\    ____|\\   \\|\\    \\ |\\     \\   ___|\\    \\  |\\    \\    /    /|        ___|\\    \\   ___|\\    \\  |    | |    |     ___|\\     \\ |    | |    |",
    "||  /    /\\    \\  /    /\\    \\\\\\    \\| \\     \\ |    |\\    \\ | \\    \\  /    / |       /    /\\    \\ |    |\\    \\ |    | |    |    |    |\\     \\|    | |    |",
    "|| |    |  |    ||    |  |    |\\|    \\  \\     ||    | |    ||  \\____\\/    /  /      |    |  |    ||    | |    ||    | |    |    |    |/____/||    |_|    |",
    "|| |    |  |____||    |__|    | |     \\  |    ||    | |    | \\ |    /    /  /       |    |  |____||    |/____/ |    | |    | ___|    \\|   | ||    .-.    |",
    "|| |    |   ____ |    .--.    | |      \\ |    ||    | |    |  \\|___/    /  /        |    |   ____ |    |\\    \\ |    | |    ||    \\    \\___|/ |    | |    |",
    "|| |    |  |    ||    |  |    | |    |\\ \\|    ||    | |    |      /    /  /         |    |  |    ||    | |    ||    | |    ||    |\\     \\    |    | |    |",
    "|| |\\ ___\\/    /||____|  |____| |____||\\_____/||____|/____/|     /____/  /          |\\ ___\\/    /||____| |____||\\___\\_|____||\\ ___\\|_____|   |____| |____|",
    "|| | |   /____/ ||    |  |    | |    |/ \\|   |||    /    | |    |`    | /           | |   /____/ ||    | |    || |    |    || |    |     |   |    | |    |",
    "||  \\|___|    | /|____|  |____| |____|   |___|/|____|____|/     |_____|/             \\|___|    | /|____| |____| \\|____|____| \\|____|_____|   |____| |____|",
    "||    \\( |____|/   \\(      )/     \\(       )/    \\(    )/          )/                  \\( |____|/   \\(     )/      \\(   )/      \\(    )/       \\(     )/  ",
    "||     '   )/       '      '       '       '      '    '           '                    '   )/       '     '        '   '        '    '         '     '   ",
    "||         '                                                                                '                                                             ",
};

const vector<string> KGrandeCase{ ///< Grande case
    "   ________________________________________________________________________________________",
    " .                                                                                          .",
    "|                                                                                            |",
    "|                                                                                            |",
    "|                                                                                            |",
    "|                                                                                            |",
    "|                                                                                            |",
    " ' _________________________________________________________________________________________'",
};

const vector<string> KPetiteCase{ ///< Petite case
    "       ________________________________________________________________________________",
    "     .                                                                                  .",
    "    |                                                                                    |",
    "    |                                                                                    |",
    "    |                                                                                    |",
    "    |                                                                                    |",
    "     ' _________________________________________________________________________________'",
};

const vector <string> KPressEnter{ ///< Texte "Press Enter"
    "                                                        _____                    _____     _           ",
    "                                                       |  _  |___ ___ ___ ___   |   __|___| |_ ___ ___ ",
    "                                                       |   __|  _| -_|_ -|_ -|  |   __|   |  _| -_|  _|",
    "                                                       |__|  |_| |___|___|___|  |_____|_|_|_| |___|_|  "
};

const vector<string> KPLAY{ ///< Texte "KPLAY"
    " _____ __    _____ __ __ ",
    "|  _  |  |  |  _  |  |  |",
    "|   __|  |__|     |_   _|",
    "|__|  |_____|__|__| |_|  ",
};

const vector<string> KEndless{ ///< Texte "Endless"
    " _____       _ _",
    "|   __|___ _| | |___ ___ ___",
    "|   __|   | . | | -_|_ -|_ -|",
    "|_____|_|_|___|_|___|___|___|",
};

const vector<string> KLeaderboard{ ///< Texte "Leaderboard"
    " __              _         _                 _ ",
    "|  |   ___ ___ _| |___ ___| |_ ___ ___ ___ _| |",
    "|  |__| -_| .'| . | -_|  _| . | . | .'|  _| . |",
    "|_____|___|__,|___|___|_| |___|___|__,|_| |___|",
};

const vector <string> Montagne1{ ///< Grande Montagne
    "      _ _ _ _",
    "    .         .",
    "  /             \\",
    " /      --    ---\\",
    "|--   -    ---    |",
    "|  ---            |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
};

const vector <string> Montagne2{ ///< Petite Montagne
    "  _ _ _",
    ".       .",
    "-  ---   |",
    " --   -  |",
    "       --|",
    "         |",
    "         |",
    "         |",
    "         |",
    "         |",
    "         |",
    "         |",
};

const vector <string> Candy{ ///< Bonbon
    "               .",
    "              /   .",
    "         =  =     . .",
    "      =        = '    .",
    "     =          =  __ .",
    ". __ =          =",
    " .    =        =",
    "  .  ;   =  =",
    "    .   /",
    "       .",
};

const vector <string> Montagne4{ ///< Petite Montagne
    "   _ _ _",
    " .       .",
    "|--  --   ",
    "|  --  ---",
    "|         ",
    "|         ",
    "|         ",
    "|         ",
    "|         ",
    "|         ",
    "|         ",
    "|         ",
};

const vector <string> Montagne5{ ///< Grande Montagne
    "      _ _ _ _",
    "    .         .",
    "  /             \\",
    " /            ---\\",
    "|   ----  ---     |",
    "|---    --        |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
    "|                 |",
};
/** @} */

// --- AFFICHAGE ---

/**
* @brief Déplace le curseur dans le terminal
** Utilise les codes d'échappements ANSI pour positionner le curseur sur le terminal
** @param x Coordonnée horizontale
* @param y Coordonnée verticale
*/
void goTo (unsigned x, unsigned y) {
    cout << "\033[" << y << ";" << x << "H" << flush;
}

/**
* @brief Vide l'affichage sur la console
** Utilise des codes ANSI pour nettoyer l'affichage
*/
void clearScreen () {
    cout << "\033[H\033[2J" << flush;
}

/**
* @brief Change la couleur ou le style d'écriture sur le terminal
** Utilise des codes ANSI pour mettre de la couleur
** @param coul Le code ANSI d'une couleur
** @details
* - 1 = gras
* - 5 = clignotement
* - 7 = Inversion de la couleur avec le fond
*/
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

/**
* @brief Change la fond d'écriture sur le terminal
** Utilise des codes ANSI pour mettre de la couleur en fond
** @param coul Le code ANSI d'une couleur
*/
void fond (const unsigned & coul) {
    cout << "\033[" << coul+10 <<"m";
}

/**
* @brief Affiche un vecteur de unsigned
** Les éléments sont séparés par une tabulation
** @param v Le vecteur (type @ref line) contenant les entiers à afficher
* @see line
*/
void affichVectUInt(vector<unsigned> &v){
    for (unsigned int &elem : v){
        cout << elem << "\t";
    }
    cout << endl;
}

/**
* @brief Affiche un vecteur de string
** Les chaine de caractere sont affichées ligne par ligne avec 0.03s de délai pour créer un effet d'animation
** @param v Le vecteur string à afficher
*/
void affichVectStr(const vector<string> & v){
    for (const string &elem : v){
        cout << elem << endl;
        usleep(30000);
    }
    cout << endl;
}

/**
* @brief Affiche un vecteur de string multicolore
** Les chaine de caractere sont affichées ligne par ligne avec 0.03s de délai pour créer un effet d'animation
* Utilise @ref couleur pour changer la couleur de l'affichage dans le terminal
** @param v Le vecteur string à afficher
*/
void affichVectCoulStr(const vector<string> & v){
    vector<int> colors = {31, 33, 32, 34, 35, 36, 0};

    unsigned i =0;
    for (const string &elem : v){
        couleur(colors[i % colors.size()]);

        cout << elem << endl;
        usleep(30000);

        i++;
    }
    cout << endl;
}

/**
* @brief Affiche un élément de décor de façon animé de bas vers le haut à un endroit précis
** Utilise @ref goTo pour repositionner le curseur sur chaque ligne
** @param Element vecteur de string représentant l'objet à afficher
* @param x Coordonnée horizontale de départ
* @param y Coordonnée verticale de depart
* @param Delay Délai en microsecondes entre l'affichage de chaque ligne
** @note L'inverse de @ref affichElemDecor
*/
void popElemDecor(const vector<string> &Element,size_t x,size_t y, size_t Delay){
    for (size_t i = 0; i < Element.size(); ++i){
        goTo(x,y-i);
        cout << Element[Element.size()-1-i] << flush;
        usleep(Delay);
    }
}

/**
* @brief Affiche un élément de décor de façon animée de haut vers le bas à un endroit précis
** Utilise @ref goTo pour repositionner le curseur sur chaque ligne
** @param Element vecteur de string représentant l'objet à afficher
* @param x Coordonnée horizontale de départ
* @param y Coordonnée verticale de depart
* @param Delay Délai en microsecondes entre l'affichage de chaque ligne
** @note L'inverse de @ref popElemDecor
*/
void affichElemDecor(const vector<string> &Element,size_t x,size_t y, size_t Delay){
    for (size_t i = 0; i < Element.size(); ++i){
        goTo(x,y+i);
        cout << Element[i] << flush;
        usleep(Delay);
    }
}

/**
* @brief Affiche l'ensemble du décor
** - Affichage de l'élément "Candy" avec un cycle de couleurs
*  - Apparition animée des montagnes via @ref popElemDecor.
** @param Delay Délai d'animation en passé à @ref popElemDecor pour l'effet de "pop"
** @note Les positions sont optimisées pour un terminal en plein écran
** @see popElemDecor, couleur, goTo
*/
void affichDecor(size_t Delay){
    vector<int> colors = {31, 33, 32, 34, 35, 36, 0};
    couleur(1);
    for (size_t i = 0; i < Candy.size(); ++i){
        couleur(colors[i % colors.size()]);
        goTo(68,30+i);
        cout << Candy[i] << flush;
    }

    couleur(KMAgenta);
    popElemDecor(Montagne1,25,42,Delay);
    if (Delay !=0) usleep(300000);

    couleur(KRouge);
    popElemDecor(Montagne5,117,42,Delay);
    if (Delay !=0) usleep(300000);

    couleur(KVert);
    popElemDecor(Montagne2,44,42,Delay);
    if (Delay !=0) usleep(300000);

    couleur(KCyan);
    popElemDecor(Montagne4,107,42,Delay);

    couleur(KReset);
}

