/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/
#ifndef __STATUT_H__
#define __STATUT_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Jeu;

class Statut {
    public :
        Statut(Jeu* jeu);
        ~Statut();
        void draw(SDL_Surface* gpScreen);
        bool getJauge();
        void setJauge(bool b);
        void setValJauge(int i);
        void setMaxJauge(int i);
        void setValJauge2(int i);
        void setMaxJauge2(int i);
        void drawNombre(SDL_Surface* gpScreen, int val, int max, int x, int y, int nb);
        void drawSeparateur(SDL_Surface* gpScreen, int x, int y, int max=0);
        SDL_Surface* getImageTroc();
        SDL_Surface* getImageGemmes();
    private :
        void drawBoss(SDL_Surface* gpScreen);
        void drawVie(SDL_Surface* gpScreen);
        void drawItems(SDL_Surface* gpScreen);
        void drawMagie(SDL_Surface* gpScreen);
        SDL_Surface* imageStatut;
        SDL_Surface* imageChiffre;
        SDL_Surface* imageInventaire;
        SDL_Surface* imageTroc;
        SDL_Surface* imageGemmes;
        Jeu* gpJeu;
        bool jauge; // jauge activée
        int valjauge;
        int maxjauge;
        int nivjauge; // hauteur 
        int valjauge2;
        int maxjauge2;
        int nivjauge2; // hauteur 
        int dec;
};

#endif  // Statut.h
