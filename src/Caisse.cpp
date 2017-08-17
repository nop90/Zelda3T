/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Texte.h"
#include "Projectile.h"
#include "Caisse.h"
#include "Jeu.h"

Caisse::Caisse(Jeu* jeu, int type, int i, int j, int r, int revie) : gpJeu(jeu), id(type),
pousseX(0), pousseY(0), vitesse(1), direction(N), reste(r), reviable(revie), rdep(r) {
    x=i; y=j; w=16; h=16; xdep=x; ydep=y;
    image = IMG_Load("romfs:/images/objet/caisse.png");
    SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,0,255));
    sx = ((type-1)%3)*w;
    sy = ((type-1)/3)*h;
    if (id == 6) vitesse=5;
}

Caisse::~Caisse() {}

void Caisse::draw(SDL_Surface* gpScreen) {
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    
    if (vie && id && x+w > phg[0] && x <= phg[0]+320 && y+h > phg[1] && y <= phg[1]+240) {
        
        bouge();
    
        SDL_Rect src;
        SDL_Rect dst;
        
        src.x=sx; src.y=sy; src.w=w; src.h=h; dst.x=x-phg[0]; dst.y=y-phg[1];
        
        SDL_BlitSurface(image, &src, gpScreen, &dst);
        
        if (reste>=0) gpJeu->getStatut()->drawNombre(gpScreen, reste, -1,x-phg[0]+4,y-phg[1]+4,1);
    }
    
    if (suivant != NULL) ((Caisse*)suivant)->draw(gpScreen);
}

bool Caisse::pousse(Direction dir) {
    if (pousseX!=0 || pousseY!=0 || reste==0) return false;
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    switch (dir) {
        case N :
            for (int i = 0; i < vitesse; i++) {
                if (y+pousseY > phg[1]+32
                && gpJeu->isMarchable(x, y-16+pousseY, 1, 1, 0, 1)
                && gpJeu->isMarchable(x+15, y-16+pousseY, 1, 1, 0, 1) 
                && gpJeu->isMarchable(x, y-1+pousseY, 1, 1, 0, 1)
                && gpJeu->isMarchable(x+15, y-1+pousseY, 1, 1, 0, 1)) pousseY+=-16;
            }
            /*if (y > phg[1]+32
            && gpJeu->isMarchable(x, y-16, 1, 1, 0, 1)
            && gpJeu->isMarchable(x+15, y-16, 1, 1, 0, 1) 
            && gpJeu->isMarchable(x, y-1, 1, 1, 0, 1)
            && gpJeu->isMarchable(x+15, y-1, 1, 1, 0, 1)) pousseY=-16*vitesse; */
            break;
        case S :
            for (int i = 0; i < vitesse; i++) {
                if (y+pousseY < phg[1]+240-32
                && gpJeu->isMarchable(x, y+16+pousseY, 1, 1, 0, 1)
                && gpJeu->isMarchable(x+15, y+16+pousseY, 1, 1, 0, 1) 
                && gpJeu->isMarchable(x, y+31+pousseY, 1, 1, 0, 1)
                && gpJeu->isMarchable(x+15, y+31+pousseY, 1, 1, 0, 1)) pousseY+=16;
            }
            break;
        case O :
            for (int i = 0; i < vitesse; i++) {
                if (x+pousseX > phg[0]+32
                && gpJeu->isMarchable(x-16+pousseX, y, 1, 1, 0, 1)
                && gpJeu->isMarchable(x-1+pousseX, y, 1, 1, 0, 1) 
                && gpJeu->isMarchable(x-16+pousseX, y+15, 1, 1, 0, 1)
                && gpJeu->isMarchable(x-1+pousseX, y+15, 1, 1, 0, 1)) pousseX+=-16;
            }
            break;
        case E :
            for (int i = 0; i < vitesse; i++) {
                if (x+pousseX < phg[0]+320-32
                && gpJeu->isMarchable(x+16+pousseX, y, 1, 1, 0, 1)
                && gpJeu->isMarchable(x+31+pousseX, y, 1, 1, 0, 1) 
                && gpJeu->isMarchable(x+16+pousseX, y+15, 1, 1, 0, 1)
                && gpJeu->isMarchable(x+31+pousseX, y+15, 1, 1, 0, 1)) pousseX+=16;
            }
            break;
    }
    if (pousseX!=0 || pousseY!=0) {
        direction = dir;
        gpJeu->getAudio()->playSound(39);
        if (reste > 0) reste--;
    }
    return true;
}

void Caisse::moveX(int i) {
    x+=i;
}

void Caisse::moveY(int i) {
    y+=i;
}

void Caisse::bouge() {
    if (pousseX==0 && pousseY==0) return;
    if (pousseX>0) {
        pousseX-=2;
        moveX(2);
    }
    if (pousseX<0) {
        pousseX+=2;
        moveX(-2);
    }
    if (pousseY>0) {
        pousseY-=2;
        moveY(2);
    }
    if (pousseY<0) {
        pousseY+=2;
        moveY(-2);
    }
    if (pousseX==0 && pousseY==0) {
        if (gpJeu->isVide(x, y, 16, 16)) {
            vie = 0;
            gpJeu->getAudio()->playSound(6);
        }
        else if (gpJeu->isWater(x, y, 16, 16)) {
            vie = 0;
            gpJeu->ajouteProjectile(8, direction, x, y, 0);
        }
        gpJeu->testAnim();
    }
    if (vie) gpJeu->testEpee(x, y, w, h, CAISSE, 999, direction);
}

void Caisse::revie() {
    if (reviable) {vie = 1; x = xdep; y = ydep; pousseX=0; pousseY=0;}
    reste = rdep;
    if (suivant != NULL) getSuivant()->revie();
}

Caisse* Caisse::getSuivant() {
    return (Caisse*)suivant;
}

bool Caisse::isActif() {
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    return (vie && id && x+w > phg[0] && x <= phg[0]+320 && y+h > phg[1] && y <= phg[1]+240);
}

int Caisse::getNombre() {return reste;}

void Caisse::setNombre(int i) {reste = i;}

void Caisse::fond() {
    if (id == 6 && vie > 0) {
        vie = 0;
        gpJeu->ajouteProjectile(8, direction, x, y, 0);
    }
}
