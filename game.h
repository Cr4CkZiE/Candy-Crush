#ifndef GAME_H
#define GAME_H

/** @file game.cpp */

// --- INCLUSION ---
#include<iostream>
#include<fstream>
#include <string>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

// --- ALIAS ---
typedef std::vector<unsigned> line;
typedef std::vector<line> mat;

// --- STRUCTURE ---
struct maPosition{
    size_t abs = 0;
    size_t ord = 0;
};

struct Joueur {
    string nom;
    size_t score = 0;
};

// --- FONCTIONS GESTION ---
//Gestion entrée utilisateur
string inputUser(unsigned sizeMax);
string inputDigitUser(unsigned sizeMax);

//Gestion score
vector<Joueur> lire_score(string mode);
void ajouter_score(string mode, string nom, size_t score);
void tri_score(vector<Joueur>& s);

//--- FONCTIONS JEU ---

//Grille
void initGrid (mat & grid, const size_t & matSize, const unsigned &KNbCandies);

//Mouvement
void inPosMakeAMove(mat & grid, maPosition & pos, char &c);
void makeAMove (mat & grid, maPosition & pos, const char & direction);

// Detection streak
bool atLeastThreeInAColumn(const mat & grid, maPosition & pos, unsigned & howMany);
bool atLeastThreeInARow(const mat &grid, maPosition &pos, unsigned &howMany);

//Remove streak
void removalInColumn (mat &grid, maPosition &pos, const unsigned  &howMany);
void removalInRow (mat &grid, maPosition &pos, const unsigned  &howMany);

//Refill Grille
void refill(mat &grid, unsigned KNbCandies);

#endif
