#ifndef GRAPICH_H
#define GRAPICH_H

/** @file grapich.cpp */

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

using namespace std;

// --- ELEMENTS GRAPHIQUES ---
extern const vector <string> KCandyCrush;

extern const vector<string> KGrandeCase;
extern const vector<string> KPetiteCase;

extern const vector <string> KPressEnter;
extern const vector<string> KPLAY;
extern const vector<string> KEndless;
extern const vector<string> KLeaderboard;

extern const vector <string> Montagne1;
extern const vector <string> Montagne1;
extern const vector <string> Montagne2;
extern const vector <string> Montagne4;
extern const vector <string> Montagne5;
extern const vector <string> Candy;

// --- DECLARATION COULEURS TERMINAL ---
const unsigned KReset   (0);
const unsigned KFlash   (5);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

// --- AFFICHAGE ---
void goTo (unsigned x, unsigned y);

void clearScreen ();
void couleur (const unsigned & coul);
void fond (const unsigned & coul);

void affichVectUInt(vector<unsigned> v);
void affichVectStr(const vector<string> & v);
void affichVectCoulStr(const vector<string> & v);

void popElemDecor(const vector<string> &Element,size_t x,size_t y, size_t Delay = 0);
void affichElemDecor(const vector<string> &Element,size_t x,size_t y, size_t Delay = 0);
void affichDecor(size_t Delay = 0);

#endif // GRAPICH_H
