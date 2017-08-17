/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CAISSE_H__
#define __CAISSE_H__

#include "Personnage.h"

class Jeu;

class Caisse : public Personnage {
    public :
        Caisse(Jeu* jeu, int type, int i, int j, int r=-1, int revie=1);
        ~Caisse();
        void draw(SDL_Surface* gpScreen);
        void moveX(int i);
        void moveY(int i);
        void revie();
        Caisse* getSuivant();
        bool pousse(Direction dir);
        bool isActif();
        int getNombre();
        void setNombre(int i);
        void fond();
    private :
        void bouge();
        
        Jeu* gpJeu;
        int id;
        int pousseX;
        int pousseY;
        int vitesse;
        Direction direction;
        int reste;
        int reviable;
        int rdep;
        int sx;
        int sy;
};

#endif  // Caisse.h
