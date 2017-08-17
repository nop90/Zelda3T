/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Joueur.h"
#include "Monde.h"
#include "Menu.h"
#include "Texte.h"
#include "Projectile.h"
#include "Objet.h"
#include "Jeu.h"

#include <iostream>

Objet::Objet(Jeu* jeu, int i, int j, int typ, int num, int persistant) : Listable(), 
gpJeu(jeu), vie(1), x(i), y(j), type(typ), id(num), vanim(120), anim(0), w(16), 
h(17), max(0), persist(persistant) {
    if (type==I_RUBIS_VERT) {
        if (gpJeu->getEpoque()==T_PASSE) type=I_PIECE_1;
        if (gpJeu->getEpoque()==T_FUTUR) type=I_GANON_1;
    }
    if (type==I_RUBIS_BLEU) {
        if (gpJeu->getEpoque()==T_PASSE) type=I_PIECE_2;
        if (gpJeu->getEpoque()==T_FUTUR) type=I_GANON_2;
    }
    if (type==I_RUBIS_ROUGE) {
        if (gpJeu->getEpoque()==T_PASSE) type=I_PIECE_3;
        if (gpJeu->getEpoque()==T_FUTUR) type=I_GANON_5;
    }
    if (type < 4) max=2;
    if (type == I_CRISTAL) max=7; //graal
    if (type == I_GEMME_JAUNE || type == I_GEMME_VERTE 
    || type == I_GEMME_BLEUE || type == I_GEMME_ROUGE) {
        max=7;
    } /*else {*/
        image = gpJeu->getImageObjets();
    //}
    lastAnimTime = SDL_GetTicks();
}

Objet::~Objet() {}

void Objet::draw(SDL_Surface* gpScreen) {
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    Monde* gpMonde = gpJeu->getMonde();
    int val = gpMonde->motifValue(x+8,y+8);
    
    if (type && vie && (val<30 || val>39) && val!=26 && val!=4360 && val!=4399 && val!=4401 
    && val!=4403 && val!=1213 && val!=385 && val!=191 && val!=192 && val!=1687 && val!=48) {
            
        SDL_Rect src; src.h = h; src.w = w;
        SDL_Rect dst; dst.x = x-phg[0]; dst.y = y-phg[1];    
       
        
        switch(type) {                
            case I_RUBIS_VERT : src.x = anim*16; src.y = 17; break;
            case I_RUBIS_BLEU : src.x = 48 + anim*16; src.y = 17; break;
            case I_RUBIS_ROUGE : src.x = anim*16; src.y = 34; break;
            case I_PETIT_COEUR : src.x = 48; src.y = 34; break;
            case I_FLECHE : if (gpJoueur->hasObjet(O_ARC) < 5) {src.x = 64; src.y = 34;}
                if (gpJoueur->hasObjet(O_ARC) == 5) {src.x = 208; src.y = 17;} break;
            case I_BOMBE : src.x = 0; src.y = 0; break;
            case I_MAGIE_PEU : src.x = 80; src.y = 34; break;
            case I_MAGIE_BCP : src.x = 96; src.y = 34; break;
            case I_QUART_COEUR : src.x = 80; src.y = 0; break;
            case I_COEUR : src.x = 64; src.y = 0; break;
            case I_EPEE : src.x = 96; src.y = 17; break;
            case I_CRISTAL : src.x = anim*16; src.y = 51; break;
            case I_EXCALIBUR : src.x = 160;src.y = 0; src.h = 22; src.w = 16; break;
            case I_PETITE_CLE : src.x = 32; src.y = 0; break;
            case I_TRIFORCE : src.x = 166; src.y = 26; src.h = 25;src.w = 26; break;
            case I_ARC : src.x = 144; src.y = 34; break;
            case I_GEMME : src.x = 177; src.y = 69; src.h=16; break;
            case I_PLANCHES : src.x = 193; src.y = 69; src.w=48; src.h=16; break;
            case I_DETECTEUR : src.x = 240; src.y = 85; src.w=16; src.h=16; break;
            case I_BOUTEILLE : src.w = 16; src.h = 16; src.x=24; src.y=69; break;
            case I_BONUS_FORCE : src.w = 16; src.h = 16; src.x=240; src.y=17; break;
            case I_BONUS_DEFENSE : src.w = 16; src.h = 16; src.x=240; src.y=34; break;
            case I_PIECE_1 : src.x = 240; src.y = 52; src.h=16; break;
            case I_PIECE_2 : src.x = 208; src.y = 136; src.h=16; break;
            case I_PIECE_3 : src.x = 224; src.y = 136; src.h=16; break;
            case I_GANON_1 : src.x = 160; src.y = 136; src.h=16; break;
            case I_GANON_2 : src.x = 176; src.y = 136; src.h=16; break;
            case I_GANON_5 : src.x = 192; src.y = 136; src.h=16; break;
            case I_PENDENTIF_V : src.x = 192; src.y = 0; src.h=16; break;
            case I_PENDENTIF_B : src.x = 192; src.y = 17; src.h=16; break;
            case I_PENDENTIF_R : src.x = 192; src.y = 34; src.h=16; break;
            case I_CLE_TEMPS : src.x = 224; src.y = 52; src.h=16; break;
            case I_GEMME_JAUNE : src.x = anim*16; src.y = 32; break;
            case I_GEMME_VERTE : src.x = anim*16; src.y = 48; break;
            case I_GEMME_BLEUE : src.x = anim*16; src.y = 16; break;
            case I_GEMME_ROUGE : src.x = anim*16; src.y = 0; break;
        }
        
        w=src.w; h=src.h;
    
        if (type == I_GEMME_JAUNE || type == I_GEMME_VERTE 
        || type == I_GEMME_BLEUE || type == I_GEMME_ROUGE) 
            image=gpJeu->getStatut()->getImageGemmes();
        SDL_BlitSurface(image, &src, gpScreen, &dst);
    
        if(max){    
            if(SDL_GetTicks() > lastAnimTime + vanim) {
            lastAnimTime = SDL_GetTicks();
                anim++;
                if (anim > max) anim = 0;
            }
        }
    }
    
    if (suivant != NULL) 
        if (((Objet*)suivant)->vie == 0) enleve(suivant);
    if (suivant != NULL) ((Objet*)suivant)->draw(gpScreen);
}

void Objet::revie() {
    if (suivant != NULL) 
        if (((Objet*)suivant)->persist == 0) enleve(suivant);
    if (suivant != NULL) ((Objet*)suivant)->revie();
}

void Objet::ramasse() {
    Joueur* gpJoueur = gpJeu->getJoueur();
    switch(type) {                
        case I_RUBIS_VERT : 
            gpJoueur->setRubis(gpJoueur->getRubis()+1); 
            gpJeu->getAudio()->playSound(14);
            break;
        case I_RUBIS_BLEU : 
            gpJoueur->setRubis(gpJoueur->getRubis()+5); 
            gpJeu->getAudio()->playSound(14);
            break;
        case I_RUBIS_ROUGE : 
            gpJoueur->setRubis(gpJoueur->getRubis()+20); 
            gpJeu->getAudio()->playSound(14);
            break;
        case I_PETIT_COEUR : 
            gpJoueur->setBoostVie(gpJoueur->getBoostVie()+2);
            if (gpJoueur->getVie()==gpJoueur->getVieMax()) gpJeu->getAudio()->playSound(15);
            break;
        case I_FLECHE : 
            gpJoueur->setFleche(gpJoueur->getFleche()+5); 
            gpJeu->getAudio()->playSound(13);
            break;
        case I_BOMBE : 
            gpJoueur->setBombe(gpJoueur->getBombe()+1); 
            gpJeu->getAudio()->playSound(13);
            break;
        case I_MAGIE_PEU : 
            gpJoueur->setBoostMagie(gpJoueur->getBoostMagie()+gpJoueur->getMagieMax()/8);
            //if (gpJoueur->getMagie()<gpJoueur->getMagieMax())
            gpJeu->getAudio()->playSound(13);
            break;
        case I_MAGIE_BCP :
            gpJoueur->setBoostMagie(gpJoueur->getBoostMagie()+gpJoueur->getMagieMax()/4);
            if (gpJoueur->getMagie()<gpJoueur->getMagieMax())
                gpJeu->getAudio()->playSound(37);
            else gpJeu->getAudio()->playSound(13);
            break;
        case I_QUART_COEUR : gpJoueur->setCoeur(id); gpJeu->trouve(C_QUART_COEUR); break;
        case I_COEUR : 
            if (gpJeu->getZone() < 57) 
                gpJoueur->setCoeur(gpJeu->getZone()-46);
            else 
                gpJoueur->setCoeur(gpJeu->getZone()-46-1); 
            gpJeu->trouve(C_COEUR); break;
        case I_EPEE : gpJeu->trouve(C_EPEE); break;
        /*case I_CRISTAL : 
            switch (gpJeu->getZone()) {
                case 15 : gpJoueur->setCristal(0); break;
                case 17 : gpJoueur->setCristal(1); break;
                case 19 : gpJoueur->setCristal(2); break;
                case 21 : gpJoueur->setCristal(3); break;
                case 22 : gpJoueur->setCristal(4); break;
                default : vie = 0; return;
            }gpJeu->trouve(C_CRISTAL); break;*/
        case I_PENDENTIF_V : gpJeu->trouve(C_MEDAILLON); gpJoueur->trouveMedaillon(0); break;
        case I_PENDENTIF_B : gpJeu->trouve(C_MEDAILLON); gpJoueur->trouveMedaillon(1); break;
        case I_PENDENTIF_R : gpJeu->trouve(C_MEDAILLON); gpJoueur->trouveMedaillon(2); break;
        case I_CLE_TEMPS : gpJeu->trouve(C_CLE_TEMPS); gpJoueur->trouveObjet(O_CLE_TEMPS); break;
        case I_GEMME_JAUNE : gpJeu->trouve(C_GEMME_JAUNE); gpJoueur->trouveObjet(O_TROC3); break;
        case I_GEMME_VERTE : gpJeu->trouve(C_GEMME_VERTE); gpJoueur->trouveObjet(O_TROC4); break;
        case I_GEMME_BLEUE : gpJeu->trouve(C_GEMME_BLEUE); gpJoueur->trouveObjet(O_TROC2); break;
        case I_GEMME_ROUGE : gpJeu->trouve(C_GEMME_ROUGE); gpJoueur->trouveObjet(O_TROC1); break;
        case I_EXCALIBUR : gpJeu->trouve(C_EXCALIBUR); gpJoueur->setCoeur(7); break;
        case I_TRIFORCE : gpJeu->trouve(C_TRIFORCE); break;
        case I_ARC : gpJeu->trouve(C_ARC); break;
        case I_PETITE_CLE : 
            gpJeu->trouve(C_CLE); 
            //int zone; zone = gpJeu->getZone();
            //int region[2]; 
            //region[0] = gpJeu->getMonde()->regionValue(0);
            //region[1] = gpJeu->getMonde()->regionValue(1);
            /*if (zone==16 && region[0]==120*16 && region[1]==15*16) gpJoueur->setCoffre(1,28); 
            if (zone==16 && region[0]==280*16 && region[1]==60*16) gpJoueur->setCoffre(1,29); 
            if (zone==20 && region[0]==0 && region[1]==45*16) gpJoueur->setCoffre(5,1); 
            if (zone==20 && region[0]==20*16 && region[1]==0) gpJoueur->setCoffre(5,3); 
            if (zone==20 && region[0]==60*16 && region[1]==45*16) gpJoueur->setCoffre(5,4); 
            if (zone==20 && region[0]==60*16 && region[1]==60*16) gpJoueur->setCoffre(5,5); 
            if (zone==20 && region[0]==80*16 && region[1]==45*16) gpJoueur->setCoffre(5,6); 
            if (zone==20 && region[0]==100*16 && region[1]==45*16) gpJoueur->setCoffre(5,7); 
            if (zone==20 && region[0]==100*16 && region[1]==60*16) gpJoueur->setCoffre(5,8); 
            if (zone==20 && region[0]==120*16 && region[1]==15*16) gpJoueur->setCoffre(5,9); 
            if (zone==20 && region[0]==120*16 && region[1]==75*16) gpJoueur->setCoffre(5,10); 
            if (zone==20 && region[0]==160*16 && region[1]==0) gpJoueur->setCoffre(5,11); 
            if (zone==20 && region[0]==160*16 && region[1]==60*16) gpJoueur->setCoffre(5,12); 
            if (zone==20 && region[0]==220*16 && region[1]==0) gpJoueur->setCoffre(5,13); 
            if (zone==20 && region[0]==220*16 && region[1]==60*16) gpJoueur->setCoffre(5,14); 
            if (zone==23) gpJoueur->setCoffre(8,16); 
            if (zone==28) gpJoueur->setCoffre(13,8);*/
            break;
        case I_GEMME : gpJoueur->trouveGemme(id); gpJeu->trouve(C_GEMME); break;
        case I_PLANCHES : gpJeu->trouve(C_PLANCHES); break;
        case I_GANON_1 : 
            gpJoueur->setGanon(gpJoueur->getGanon()+1); 
            gpJeu->getAudio()->playSound(14);
            break;
        case I_GANON_2 : 
            gpJoueur->setGanon(gpJoueur->getGanon()+2); 
            gpJeu->getAudio()->playSound(14);
            break;
        case I_GANON_5 : 
            gpJoueur->setGanon(gpJoueur->getGanon()+5); 
            gpJeu->getAudio()->playSound(14);
            break;
        case I_PIECE_1 : 
            gpJoueur->setPiece(gpJoueur->getPiece()+1); 
            gpJeu->getAudio()->playSound(14);
            break;
        case I_PIECE_2 : 
            gpJoueur->setPiece(gpJoueur->getPiece()+2); 
            gpJeu->getAudio()->playSound(14);
            break;
        case I_PIECE_3 : 
            gpJoueur->setPiece(gpJoueur->getPiece()+3); 
            gpJeu->getAudio()->playSound(14);
            break;
        /*case I_PETITE_CLE : src.x = 32; src.y = 0; break;
        case I_TRIFORCE : src.x = 166; src.y = 26; src.h = 25;src.w = 26; break;
        case I_ARC : src.x = 144; src.y = 34; break;*/
    }
    vie=0;
}

int Objet::getX() {return x;}
int Objet::getY() {return y;}
int Objet::getW() {return w;}
int Objet::getH() {return h;}
int Objet::getVie() {return vie;}
void Objet::setVie(int v) {vie=v;}
int Objet::getType() {return type;}

Objet* Objet::getSuivant() {
    return (Objet*)suivant;
}
