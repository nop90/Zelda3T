/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Generique.h"
#include "Jeu.h"
#include "Keyboard.h"

#define BOTTOMOFF 240

Generique::Generique(Jeu* jeu) : gpJeu(jeu), anim(0) {
    imageFin = NULL;
    imageArbre = NULL;
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    imageTitre = IMG_Load("romfs:/images/logos/titre.png");
    SDL_SetColorKey(imageTitre,SDL_SRCCOLORKEY,SDL_MapRGB(imageTitre->format,0,0,255));
    imageCurseur = IMG_Load("romfs:/images/logos/curseur.png");
    SDL_SetColorKey(imageCurseur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCurseur->format,0,0,255));
    imageNiveau = IMG_Load("romfs:/images/logos/niveau.png");
    SDL_SetColorKey(imageNiveau,SDL_SRCCOLORKEY,SDL_MapRGB(imageNiveau->format,0,0,255));
    imageFee = IMG_Load("romfs:/images/logos/fee.png");
    imageCadre = IMG_Load("romfs:/images/logos/cadres.png");
    imageFond1 = NULL;
    imageFond2 = NULL;
    for (int i = 0; i < 5; i++) imageIntro[i]=NULL;

    imageBackground = SDL_CreateRGBSurface(0, 320, 240, 32, 0, 0, 0, 0);

    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, imageBackground, &dst);
        }

}

Generique::~Generique() {
    SDL_FreeSurface(imageFin);
    SDL_FreeSurface(imageArbre);
    SDL_FreeSurface(image);
    SDL_FreeSurface(imageTitre);
    SDL_FreeSurface(imageCurseur);
    SDL_FreeSurface(imageNiveau);
    SDL_FreeSurface(imageFee);
    SDL_FreeSurface(imageCadre);
    SDL_FreeSurface(imageFond1);
    SDL_FreeSurface(imageFond2);
    for (int i = 0; i < 5; i++) SDL_FreeSurface(imageIntro[i]);
    SDL_FreeSurface(imageBackground);
}

void Generique::drawFin(SDL_Surface* gpScreen) {
    if (!imageFin) imageFin = IMG_Load("romfs:/images/logos/fin.png");
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(imageFin, NULL, gpScreen, &dst);
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::initLogo() {
    SDL_Rect dst;
    SDL_Surface* logo = IMG_Load("romfs:/images/logos/logo.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(logo, NULL, image, &dst);
    SDL_FreeSurface(logo);
}

void Generique::initPresent() {
    SDL_Rect dst;
    SDL_Surface* present = IMG_Load("romfs:/images/motifs/present.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(present, NULL, image, &dst);
    SDL_FreeSurface(present);
}

void Generique::drawToPresent(SDL_Surface* gpScreen) {
    draw(gpScreen);
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::initPasse() {
    SDL_Rect dst;
    SDL_Surface* passe = IMG_Load("romfs:/images/motifs/passe.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(passe, NULL, image, &dst);
    SDL_FreeSurface(passe);
}

void Generique::initImageFin() {
    SDL_Rect dst;
    SDL_Surface* fin = IMG_Load("romfs:/images/motifs/fin.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(fin, NULL, image, &dst);
    SDL_FreeSurface(fin);
}

void Generique::initTitre() {
    SDL_Rect dst;
    SDL_Surface* fond = IMG_Load("romfs:/images/logos/fond.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(fond, NULL, image, &dst);
    SDL_FreeSurface(fond);
    SDL_Surface* logo = IMG_Load("romfs:/images/logos/titre.png");
    SDL_SetColorKey(logo,SDL_SRCCOLORKEY,SDL_MapRGB(logo->format,0,0,255));
//    logo = SDL_DisplayFormat(logo);
    dst.x = 76; dst.y = 53; SDL_BlitSurface(logo, NULL, image, &dst);
    SDL_FreeSurface(logo);
}

void Generique::initSelection() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
            
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 6; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 160-32; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 160-32; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 160-32; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,48,288,32);
    cadre(16,96,288,32);
    cadre(16,144,288,32);
    cadre(16,192,136,32);
    cadre(168,192,136,32);
    
    gpJeu->affiche(image, "PLAYER SELECT", 40, 16);
    gpJeu->affiche(image, "1.", 44, 56);
    gpJeu->affiche(image, "2.", 44, 104);
    gpJeu->affiche(image, "3.", 44, 152);
    gpJeu->affiche(image, "OPTIONS", 63, 200);
    gpJeu->affiche(image, "RECORDS", 215, 200);
    
    //stats :
    SDL_Surface* imageStat = IMG_Load("romfs:/images/statut/statut.png");
    SDL_SetColorKey(imageStat,SDL_SRCCOLORKEY,SDL_MapRGB(imageStat->format,0,0,255));
    SDL_Surface* inventaire = IMG_Load("romfs:/images/statut/inventaire.png");
    SDL_Surface* objets = IMG_Load("romfs:/images/statut/objets.png");
    
    for (int i = 0; i < 3; i++) {
        Joueur* gpJoueur = new Joueur(gpJeu,i+1);
        if (gpJoueur->getLoader()) {
            //vie
            if(gpJoueur->getVie()>gpJoueur->getVieMax()) gpJoueur->setVie(gpJoueur->getVieMax());
            for(int j=0;j<gpJoueur->getVieMax()/2;j++) {
                src.h = 7; src.w = 7; src.y=9;
                dst.x = 64-8+((j%10)*8)+8;dst.y = 57+8*((int)(j/10))+i*48;
                if (gpJoueur->getVie()-(j*2)>1)src.x=141;
                if (gpJoueur->getVie()-(j*2)==1)src.x=149;
                if (gpJoueur->getVie()-(j*2)<1)src.x=157;
                SDL_BlitSurface(imageStat, &src, image, &dst);
            }
            
            dst.x=176-4; dst.y=56+i*48;
            if (gpJoueur->nbCristaux()) {
                //cristaux
                src.x=16; src.y=17*4; src.w=16; src.h=17; dst.x-=(16-2);
                for (int j=0; j<7; j++) {
                    if (gpJoueur->hasCristal(j)) src.x=16; else src.x=32;
                    SDL_BlitSurface(inventaire, &src, image, &dst);
                    dst.x+=16;
                }
            } else if (gpJoueur->hasObjet(O_CARTE)) { //stèle lue
                //médaillons
                src.y=32; src.w=16; src.h=16;
                for (int i = 0; i < 3; i++) {
                    if (gpJoueur->hasMedaillon(i)) src.x=16*i;
                    else src.x=48;
                    SDL_BlitSurface(objets, &src, image, &dst);
                    dst.x+=16;
                }dst.x+=8;
                //clé du temps
                if (gpJoueur->hasObjet(O_CLE_TEMPS)) {
                    src.x=80;
                    SDL_BlitSurface(objets, &src, image, &dst);
                } dst.x+=16+8;
                //ocarina
                if (gpJoueur->hasObjet(O_OCARINA)) {
                    src.y=85; src.x=0;
                    SDL_BlitSurface(inventaire, &src, image, &dst);
                }
            }
            
            //cristaux
            /*dst.x=176+8-16-16-4; dst.y=56+i*48;
            src.x=16; src.y=17*4; src.w=16; src.h=17;
            for (int j=0; j<5; j++) {
                if (gpJoueur->hasCristal(j)) src.x=16; else src.x=32;
                SDL_BlitSurface(inventaire, &src, image, &dst);
                dst.x+=16+2;
            }
            
            //épée
            dst.x=280-48+8; dst.y=56+i*48;
            src.x=16*(gpJoueur->getEpee()-1); src.y=0; src.w=16; src.h=16;
            if (gpJoueur->getEpee()) SDL_BlitSurface(objets, &src, image, &dst);
            
            //masque
            dst.x=280-32+16-4; dst.y=56+i*48;
            src.x=16*(gpJoueur->hasObjet(O_MASQUE)-1); 
            src.y=102-17*(gpJoueur->hasObjet(O_MASQUE)-1); src.w=16; src.h=16;
            if (gpJoueur->hasObjet(O_MASQUE)) SDL_BlitSurface(inventaire, &src, image, &dst);*/
            
            //triforce
            dst.x=272+8; dst.y=56+i*48;
            src.x=128; src.y=0; src.w=17; src.h=16;
            if (gpJoueur->getEnnemi(50)) SDL_BlitSurface(objets, &src, image, &dst);
            
            gpJeu->getKeyboard()->setSave(i,1);
        }else gpJeu->getKeyboard()->setSave(i,0);
		delete gpJoueur;
    }
    
    SDL_FreeSurface(objets);
    SDL_FreeSurface(imageStat);
    SDL_FreeSurface(inventaire);
}

void Generique::initOption() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64,288,32);
    cadre(16,128,288,32);
    cadre(16,192,136,32);
    
    gpJeu->affiche(image, "OPTIONS", 40, 16);
    gpJeu->affiche(image, "MUSIC", 60, 72);
    gpJeu->affiche(image, "SOUNDS", 60, 136);
    gpJeu->affiche(image, "RETURN", 63, 200);
    
    src.x = 0; src.y = 96; dst.x = 128; dst.y = 72; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    for (int i = 144; i < 264; i+=16) {
        src.x = 16; src.y = 96; dst.x = i; dst.y = 72; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    src.x = 32; src.y = 96; dst.x = 264; dst.y = 72; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    src.x = 0; src.y = 96; dst.x = 128; dst.y = 136; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    for (int i = 144; i < 264; i+=16) {
        src.x = 16; src.y = 96; dst.x = i; dst.y = 136; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    src.x = 32; src.y = 96; dst.x = 264; dst.y = 136; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
}

void Generique::initRecord() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(128,8,176,32);
    cadre(16,48,144,32); cadre(176,48,32,32); cadre(224,48,32,32); cadre(272,48,32,32);
    cadre(16,96,144,32); cadre(176,96,32,32); cadre(224,96,32,32); cadre(272,96,32,32);
    cadre(16,144,144,32); cadre(176,144,32,32); cadre(224,144,32,32); cadre(272,144,32,32);
    cadre(16,192,136,32);
    cadre(168,192,136,32);
    
    ostringstream oss;
    int temps = gpJeu->getKeyboard()->getTemps();
    if (temps > 359999) temps = 359999;
    int h = temps/3600;
    int m = (temps - ((int)(temps/3600))*3600)/60;
    int s = temps%60;
    if (h < 10) oss<<"0"; oss << h << ":";
    if (m < 10) oss<<"0"; oss << m << ":";
    if (s < 10) oss<<"0"; oss << s;
    
    
    gpJeu->affiche(image, "RECORDS", 40, 16);
    gpJeu->affiche(image, "BEST TIME : " + oss.str(), 140, 16);
    gpJeu->affiche(image, "100% RANK", 44, 56);
    gpJeu->affiche(image, "ULTIMATE RANK", 44, 104);
    gpJeu->affiche(image, "SPEED RANK", 44, 152);
    gpJeu->affiche(image, "RETURN", 63, 200);
    gpJeu->affiche(image, "ERASE", 215, 200);
    
    SDL_Surface* objets = IMG_Load("romfs:/images/statut/objets.png");
    
    //triforce
    src.y=0; src.w=17; src.h=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=231-48; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i) ? src.x=128 : src.x=145; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    //graäl
    src.y=16; //src.w=17; src.h=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=280-48; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i+3) ? src.x=128 : src.x=145; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    //ocarina
    src.x=162; src.w=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=280; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i+6) ? src.y=0 : src.y=16; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    SDL_FreeSurface(objets);
}

void Generique::initEffacer() {
    cadre(104,84,112,72);
    gpJeu->affiche(image, "ERASE ?", 133, 93);
    gpJeu->affiche(image, "YES", 151, 113);
    gpJeu->affiche(image, "NO", 151, 133);
}

void Generique::initCharger() {
    cadre(104,84,112,72);
    gpJeu->affiche(image, "LOAD", 139, 93);
    gpJeu->affiche(image, "ERASE", 139, 113);
    gpJeu->affiche(image, "CANCEL", 139, 133);
}

void Generique::initIntro() {
    if (imageFond1==NULL) {
        imageFond1 = IMG_Load("romfs:/images/logos/fond1.png");
        SDL_SetColorKey(imageFond1,SDL_SRCCOLORKEY,SDL_MapRGB(imageFond1->format,0,0,255));}
    if (imageFond2==NULL) imageFond2 = IMG_Load("romfs:/images/logos/fond2.png");
    
    ostringstream oss;
    for (int i = 0; i < 5; i++) {
        if (imageIntro[i]==NULL) {
            oss.str(""); oss << (i+1);
            imageIntro[i] = IMG_Load(("romfs:/images/logos/intro" + oss.str() + ".png").c_str());
        }
    }
    
    lastAnimTime = SDL_GetTicks(); anim=0;
    gpJeu->ecrit(1361, false, true, 32, 158, 256, 64);
}

void Generique::initNuit() {
    SDL_Rect dst;
    SDL_Surface* fond = IMG_Load("romfs:/images/logos/nuit.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(fond, NULL, image, &dst);
    SDL_FreeSurface(fond);
    //SDL_FillRect(image, NULL, SDL_MapRGB(image->format, 0, 0, 0));
    gpJeu->ecrit(1366);
}

void Generique::initAide1() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    gpJeu->affiche(image, "Return to the game: A - Next: Right", 24, 208);
    
    int ligne = 64;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    gpJeu->affiche(image, "Read / Open / Speak : A", 24, ligne); ligne+=16;
    gpJeu->affiche(image, "Confirm / Pass text: A", 24, ligne); ligne+=16;
    gpJeu->affiche(image, "Move Link: Arrows", 24, ligne); ligne+=16;
    if (gpJoueur->hasObjet(O_BOTTES)) {
        gpJeu->affiche(image, "Run: R hold", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->getEpee()) {
        gpJeu->affiche(image, "Use sword: B", 24, ligne); ligne+=16;
        gpJeu->affiche(image, "Spin attack: hold B to charge", 24, ligne); 
        ligne+=16;}
    gpJeu->affiche(image, "Item selection: L and START", 24, ligne); ligne+=16;
    if (ligne < 176)
    gpJeu->affiche(image, "Use selected object: Y", 24, ligne); ligne+=16;
    if (gpJoueur->hasObjet(O_GANTS)) {
        if (ligne < 176) gpJeu->affiche(image, "Carry: X", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->hasObjet(O_CARTE)) {
        if (ligne < 176) 
            gpJeu->affiche(image, "Open the map: START (outside or dungeons)", 24, ligne);
    } else 
        if (ligne < 176) 
            gpJeu->affiche(image, "Open the map: START (in dungeons)", 24, ligne);
    ligne+=16;
    if (gpJoueur->hasObjet(O_ENCYCL)) {
        if (ligne < 176) gpJeu->affiche(image, "View defeated monsters: L and B", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->hasObjet(O_POISSONS)) {
        if (ligne < 176) gpJeu->affiche(image, "VIew fishes : L and B", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->hasObjet(O_SAC_TROC)) {
        if (ligne < 176) gpJeu->affiche(image, "View barter items : L and B", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->hasObjet(O_MASQUE)) {
        if (ligne < 176) gpJeu->affiche(image, "Oni Link transformation : L and X", 24, ligne); 
        ligne+=16;}
    if (ligne < 176)
    gpJeu->affiche(image, "Look around: L and direction", 24, ligne); ligne+=16;
    if (ligne < 176)
    gpJeu->affiche(image, "Enlarge / Shrink: L and A", 24, ligne); ligne+=16;
    if (ligne < 176)
    gpJeu->affiche(image, "Save / Quit: SELECT", 24, ligne); ligne+=16;
    
    if (ligne >= 288) gpJeu->affiche(image, "HELP 1/3", 40, 16);
    else gpJeu->affiche(image, "HELP 1/2", 40, 16);
}

void Generique::initAide2() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    int ligne = 64-112;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ligne+=64;
    if (gpJoueur->hasObjet(O_BOTTES)) ligne+=16;
    if (gpJoueur->getEpee()) ligne+=32;
    if (ligne >= 64) 
    gpJeu->affiche(image, "Use selected object: Y", 24, ligne); ligne+=16;
    if (gpJoueur->hasObjet(O_GANTS)) {
        if (ligne >= 64) gpJeu->affiche(image, "Carry : X", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->hasObjet(O_CARTE)) {
        if (ligne >= 64) 
            gpJeu->affiche(image, "See the map: L and START (outside or dungeons)", 24, ligne);
    } else 
        if (ligne >= 64) 
            gpJeu->affiche(image, "See the map: L and START (in dungeons)", 24, ligne);
    ligne+=16;
    if (gpJoueur->hasObjet(O_ENCYCL)) {
        if (ligne >= 64) gpJeu->affiche(image, "View defeated monsters: L and B", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->hasObjet(O_POISSONS)) {
        if (ligne >= 64) gpJeu->affiche(image, "View fishes : L and B", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->hasObjet(O_SAC_TROC)) {
        if (ligne >= 64) gpJeu->affiche(image, "View barter items : L and B", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->hasObjet(O_MASQUE)) {
        if (ligne >= 64) gpJeu->affiche(image, "Oni Link transformation : L and X", 24, ligne); 
        ligne+=16;}
    if (ligne >= 176) {
        gpJeu->affiche(image, "HELP 2/3", 40, 16); 
        gpJeu->affiche(image, "Return to the game: A - Next: Right", 24, 208);
        return;}
    if (ligne >= 64) 
    gpJeu->affiche(image, "Look around: L and direction", 24, ligne); ligne+=16;
    if (ligne >= 176) {
        gpJeu->affiche(image, "HELP 2/3", 40, 16); 
        gpJeu->affiche(image, "Return to the game: A - Next: Right", 24, 208);
        return;}
    if (ligne >= 64) 
    gpJeu->affiche(image, "Enlarge / Shrink: L and A", 24, ligne); ligne+=16;
    if (ligne >= 176) {
        gpJeu->affiche(image, "HELP 2/3", 40, 16); 
        gpJeu->affiche(image, "Return to the game: A - Next: Right", 24, 208);
        return;}
    if (ligne >= 64) 
    gpJeu->affiche(image, "Save / Quit: SELECT", 24, ligne); ligne+=16;
    
    gpJeu->affiche(image, "HELP 2/2", 40, 16);
    gpJeu->affiche(image, "Return to the game: A - Previous: Left", 24, 208);
}

bool Generique::initAide3() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    gpJeu->affiche(image, "HELP 3/3", 40, 16);
    
    gpJeu->affiche(image, "Return to the game: Enter - Previous: Left", 24, 208);
    
    int ligne = 64-112*2;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ligne+=64;
    if (gpJoueur->hasObjet(O_BOTTES)) ligne+=16;
    if (gpJoueur->getEpee()) ligne+=32;
    ligne+=16;
    if (gpJoueur->hasObjet(O_GANTS)) ligne+=16;
    ligne+=16;
    if (gpJoueur->hasObjet(O_ENCYCL)) ligne+=16;
    if (gpJoueur->hasObjet(O_POISSONS)) ligne+=16;
    if (gpJoueur->hasObjet(O_SAC_TROC)) ligne+=16;
    if (gpJoueur->hasObjet(O_MASQUE)) ligne+=16;
    if (ligne >= 64) 
    gpJeu->affiche(image, "Look around: Ctrl and direction", 24, ligne); ligne+=16;
    if (ligne >= 64) 
    gpJeu->affiche(image, "Enlarge / Shrink: Ctrl and Enter", 24, ligne); ligne+=16;
    if (ligne >= 64) 
        gpJeu->affiche(image, "Save / Quit: Esc", 24, ligne);
    else {
        initAide2();
        return false;
    }
    return true;
}


void Generique::initTroc() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    SDL_Surface* imageCadreTroc = IMG_Load("romfs:/images/menu/cadrestroc.png");
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
        }
            
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    
    for (int i = 0; i < 5; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 112; dst.y = 0; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 112; dst.y = 16; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 112; dst.y = 32; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    
    
    SDL_Surface* tmp = imageCadre;
    imageCadre = imageCadreTroc;
    
    cadre(16,48,288,176);
    
    imageCadre = tmp;
    
    SDL_FreeSurface(imageCadreTroc);
    
    gpJeu->affiche(image, "BARTER ITEMS", 38-3, 16);
    
    int ligne = 58;
    int colonne = 44;
    ostringstream oss;
    Joueur* gpJoueur = gpJeu->getJoueur();
    src.w=16; src.h=16;
    
    for (int i = 0; i < 16; i++) {
        
        if (gpJoueur->getTroc(i)>-1) {
            
            src.x=i*16; src.y=153;
            dst.x=colonne-20; dst.y=ligne;
            
            SDL_BlitSurface(gpJeu->getImageObjets(), &src, image, &dst);
            
            oss.str(""); oss<<gpJoueur->getTroc(i);
        
            switch (i) {
                case 0 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" BAGS OF RICE", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" BAG OF RICE", colonne, ligne); break;
                case 1 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" JARS OF SPICES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" JAR OF SPICES", colonne, ligne); break;
                case 2 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" BAGS OF OLIVES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" BAG OF OLIVES", colonne, ligne); break;
                case 3 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" PEARLS", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" PEARL", colonne, ligne); break;
                case 4 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" FEATHERS", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" FEATHER", colonne, ligne); break;
                case 5 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" CHIKENS", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" CHICKEN", colonne, ligne); break;
                case 6 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" TAPESTRIES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" TAPESTRY", colonne, ligne); break;
                case 7 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" AMULETS", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" AMULET", colonne, ligne); break;
                case 8 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" PERFUMES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" PERFUME", colonne, ligne); break;
                case 9 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" MAGMA ROCKS", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" MAGMA ROCK", colonne, ligne); break;
                case 10 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" FROSTY ROCKS", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" FROSTY ROCK", colonne, ligne); break;
                case 11 : gpJeu->affiche(image, oss.str()+" PEPPER", colonne, ligne); break;
                case 12 : gpJeu->affiche(image, oss.str()+" COGWHEEL", colonne, ligne); break;
                case 13 : gpJeu->affiche(image, oss.str()+" GAUGE", colonne, ligne); break;
                case 14 : gpJeu->affiche(image, oss.str()+" WHEEL", colonne, ligne); break;
                case 15 : gpJeu->affiche(image, oss.str()+" ENERGY CORE", colonne, ligne); break;
        }
        
        }
        ligne+=20;
        if (ligne > 198) {ligne=58; colonne+=136;}
    }
}



void Generique::initRang(int i) {
    
    switch (i) {
        case 0 :
            cadre(64+8,96,192-16,48);
            if (gpJeu->getKeyboard()->getRang(i) 
            && gpJeu->getKeyboard()->getRang(i+3) 
            && gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANK : Legendary Hero", 72+8, 104);
            else if ((gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3))
            || (gpJeu->getKeyboard()->getRang(i+3) && gpJeu->getKeyboard()->getRang(i+6))) 
                gpJeu->affiche(image, "RANK : Hero of Two Worlds", 72+8, 104);
            else if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->affiche(image, "RANK : Heros of Hyrule", 72+8, 104);
            else if (gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANK : Hero of Termina", 72+8, 104);
            else if (gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANK : Hero of Time", 72+8, 104);
            else gpJeu->affiche(image, "RANK : UNKNOWN", 72+8, 104);
            gpJeu->affiche(image, "100% complete the game.", 72+8, 120);
            break;
        case 1 :
            cadre(64,80,192+16,80);
            int l; l=88;
            if (gpJeu->getKeyboard()->getRang(i) 
            && gpJeu->getKeyboard()->getRang(i+3)
            && gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANG : Legendary Sword Master", 72, l);
            else if ((gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3)) 
            || (gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+6))
            || (gpJeu->getKeyboard()->getRang(i+3) && gpJeu->getKeyboard()->getRang(i+6)))
                gpJeu->affiche(image, "RANK : Sword Master", 72, l);
            else if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->affiche(image, "RANK : Swanky", 72, l);
            else if (gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANK : Bigheaded", 72, l);
            else if (gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANK : Proud", 72, l);
            else gpJeu->affiche(image, "RANK : UNKNOWN", 72, l);
            l+=16;
            gpJeu->affiche(image, "Complete the game not dead,", 72, l);l+=16;
            gpJeu->affiche(image, "with 12 hearts at the very most,", 72, l);l+=16;
            gpJeu->affiche(image, "and without buying a bottle.", 72, l);l+=16;
            break;
        case 2 :
            cadre(48,88,224,64);
            if (gpJeu->getKeyboard()->getRang(i) 
            && gpJeu->getKeyboard()->getRang(i+3)
            && gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANK : Legendary Marathon Runner", 56, 96);
            else if ((gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3))
            || (gpJeu->getKeyboard()->getRang(i+3) && gpJeu->getKeyboard()->getRang(i+6))) 
                gpJeu->affiche(image, "RANK : Two Worlds Marathon Runner", 56, 96);
            else if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->affiche(image, "RANK : Hyrule Marathon Runner", 56, 96);
            else if (gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANK : Termina Marathon Runner", 56, 96);
            else if (gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANK : Marathon Runner of Time", 56, 96);
            else gpJeu->affiche(image, "RANK : UNKNOWN", 56, 96);
            gpJeu->affiche(image, "Complete the game in less than", 56, 112);
            gpJeu->affiche(image, "seven hours.", 56, 128);
            break;
    }
}

void Generique::cadre(int x, int y, int w, int h) {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    for (int j = y+16; j < y+h-16; j+=16)
        for (int i = x+16; i < x+w-16; i+=16) {
            src.x = 16; src.y = 64; dst.x = i; dst.y = j; 
            SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
    
    //haut et bas
    for (int i = x+16; i < x+w-16; i+=16) {
        src.x = 16; src.y = 48; dst.x = i; dst.y = y; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 80; dst.x = i; dst.y = y+h-16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    //gauche et droite
    for (int j = y+16; j < y+h-16; j+=16) {
        src.x = 0; src.y = 64; dst.x = x; dst.y = j; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 32; src.y = 64; dst.x = x+w-16; dst.y = j;
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    //haut gauche
    src.x = 0; src.y = 48; dst.x = x; dst.y = y; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //haut droite
    src.x = 32; src.y = 48; dst.x = x+w-16; dst.y = y; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //bas gauche
    src.x = 0; src.y = 80; dst.x = x; dst.y = y+h-16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //bas droite
    src.x = 32; src.y = 80; dst.x = x+w-16; dst.y = y+h-16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
}

void Generique::initScore() {
    SDL_FreeSurface(imageArbre);
    imageArbre = IMG_Load("romfs:/images/logos/arbre.png");
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    
    SDL_Rect dst; 
    
    for (int i = 0; i < 320; i+=48) {
        dst.x = i;
        for (int j = 0; j < 240; j+=96) {
            dst.y = j;
            SDL_BlitSurface(imageArbre, NULL, image, &dst);
        }
    }
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ostringstream oss;
    int pctg = 0;
    gpJeu->affiche(image, "RESULTS :", 136, 10);
    
    int temps = gpJoueur->getTemps(0)+gpJoueur->getTemps(1)*60+gpJoueur->getTemps(2)*3600;
    if (temps < gpJeu->getKeyboard()->getTemps() || gpJeu->getKeyboard()->getTemps()==0) {
        gpJeu->getKeyboard()->setTemps(temps); gpJeu->getKeyboard()->saveP();}
        
    oss.str(""); 
    if (gpJoueur->getTemps(2)<10)oss<<"0";oss << gpJoueur->getTemps(2) << ":";
    if (gpJoueur->getTemps(1)<10)oss<<"0";oss << gpJoueur->getTemps(1) << ":";
    if (gpJoueur->getTemps(0)<10)oss<<"0";oss << gpJoueur->getTemps(0);
    gpJeu->affiche(image, ("Game time: " + oss.str()).c_str(), 10, 30);
    
    int tmp=gpJoueur->getMort();
    oss.str(""); oss << tmp;
    gpJeu->affiche(image, ("Dead " + oss.str() + " times").c_str(), 160, 30);
    
    tmp=gpJoueur->nbQuarts();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Pieces of heart: " + oss.str() + " / 16").c_str(), 10, 50);

    tmp=gpJoueur->getNbGemmes();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Power Gems: " + oss.str() + " / 200").c_str(), 160, 50);

    tmp=0;
    for (int i = 0; i < 16; i++) if (gpJoueur->hasObjet(i)) tmp++;
    for (int i = 21; i < 35; i++) if (gpJoueur->hasObjet(i)) tmp++;
    if (gpJoueur->hasObjet(O_ARC) == 5) tmp++;
    if (gpJoueur->hasObjet(O_GANTS) == 2) tmp++;
    if (gpJoueur->hasObjet(O_BONUS_FORCE) == 2) tmp++;
    if (gpJoueur->hasObjet(O_BONUS_DEFENSE) == 2) tmp++;
    tmp+=gpJoueur->getBouclier();
    for (int i = 0; i < 4; i++) if (gpJoueur->hasBouteille(i)) tmp++;
    tmp+=gpJoueur->getEpee();
    if (gpJoueur->getEpee() == 5) tmp--; // car que 4 épées
    tmp+=gpJoueur->getTunique();
    if (gpJoueur->getMagieMax() > 32) tmp++;
    tmp+=(gpJoueur->getFlecheMax()-30)/5;
    tmp+=(gpJoueur->getBombeMax()-10)/2;
    if (gpJoueur->getRubisMax()>0) tmp++;
    if (gpJoueur->getRubisMax()>99) tmp++;
    if (gpJoueur->getRubisMax()>200) tmp++;
    if (gpJoueur->getRubisMax()>500) tmp++;
    if (gpJoueur->getGanonMax()>0) tmp++;
    if (gpJoueur->getGanonMax()>99) tmp++;
    if (gpJoueur->getGanonMax()>200) tmp++;
    if (gpJoueur->getGanonMax()>500) tmp++;
    if (gpJoueur->getPieceMax()>0) tmp++;
    if (gpJoueur->getPieceMax()>99) tmp++;
    if (gpJoueur->getPieceMax()>200) tmp++;
    if (gpJoueur->getPieceMax()>500) tmp++;
    for (int i = 0; i < 3; i++) if (gpJoueur->hasMelodie(i)) tmp++;
    for (int i = 0; i < 3; i++) if (gpJoueur->hasMedaillon(i)) tmp++;
    for (int i = 0; i < 7; i++) if (gpJoueur->hasCristal(i)) tmp++;
    for (int j = 0; j < 15; j++) for (int i = 0; i < 3; i++) if (gpJoueur->getCle(j,i)) tmp++;
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Objects: " + oss.str() + " / 139").c_str(), 10, 70);
    
    tmp=0;
    for (int i = 0; i < 16; i++) if (gpJoueur->getTroc(i) > -1) tmp++;
    if (gpJoueur->hasObjet(O_TROC1) < 10) tmp+=gpJoueur->hasObjet(O_TROC1);
    else tmp+=7;
    if (gpJoueur->hasObjet(O_TROC2) < 10) tmp+=gpJoueur->hasObjet(O_TROC2);
    else tmp+=7;
    if (gpJoueur->hasObjet(O_TROC3) < 10) tmp+=gpJoueur->hasObjet(O_TROC3);
    else tmp+=8;
    if (gpJoueur->hasObjet(O_TROC4) < 10) tmp+=gpJoueur->hasObjet(O_TROC4);
    else tmp+=7;
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Barter items: " + oss.str() + " / 45").c_str(), 160, 70);
    
    tmp=gpJoueur->nbPoissons();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Fishes: " + oss.str() + " / 30").c_str(), 10, 90);
    
    
    tmp=gpJoueur->nbEnnemis();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Enemies: " + oss.str() + " / 100").c_str(), 160, 90);
    
    pctg=(int)((pctg*100)/530);
    oss.str(""); oss << pctg;
    gpJeu->affiche(image, ("You complete the game with " + oss.str() + "%, congratulations!").c_str(), 
        10, 130);
    
    string result;
    int ligne = 170;
    gpJeu->affiche(image, "RANK : ", 10, ligne);
    
    if (gpJoueur->getMort()==0 && gpJoueur->hasBouteille(0)==0
        && gpJoueur->hasBouteille(1)==0 && gpJoueur->hasBouteille(2)==0
        && gpJoueur->hasBouteille(3)==0 && gpJoueur->getVieMax()==24) {
            if (gpJeu->getKeyboard()->getRang(1) && gpJeu->getKeyboard()->getRang(4)) 
                result="Legendary Sword Master"; 
            else if (gpJeu->getKeyboard()->getRang(1))
                result="Sword Master"; 
            else if (gpJeu->getKeyboard()->getRang(4))
                result="Sword Master"; 
            else result="Proud"; 
            gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;
            gpJeu->getKeyboard()->setRang(7); gpJeu->getKeyboard()->saveP();}
    else {
        if (pctg==100) {
            if (gpJeu->getKeyboard()->getRang(0) && gpJeu->getKeyboard()->getRang(3)) 
                result="Legendary Hero"; 
            else if (gpJeu->getKeyboard()->getRang(0))
                result="Hero of Hyrule"; 
            else if (gpJeu->getKeyboard()->getRang(3))
                result="Hero of Two Worlds"; 
            else result="Hero of Time"; 
            gpJeu->getKeyboard()->setRang(6); gpJeu->getKeyboard()->saveP();}
        if (pctg<100) result="Perfectionist";
        if (pctg<95) result="Zelda Fan";
        if (pctg<90) result="Keyboard professional";
        if (pctg<85) result="Experienced";
        if (pctg<80) result="Novice";
        gpJeu->affiche(image, " - "+result, 52, ligne);
        ligne+=20;
    }
    
    if (gpJoueur->getMort()>=100) {
        result="Living dead"; gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
    else if (gpJoueur->getMort()>=50) {
        result="Kamikaze"; gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
        
    if (temps<=25200) {
        if (gpJeu->getKeyboard()->getRang(2) && gpJeu->getKeyboard()->getRang(5)) 
            result="Legendary Marathon Runner";
        else if (gpJeu->getKeyboard()->getRang(2)) 
            result="Hyrule Marathon Runner";
        else if (gpJeu->getKeyboard()->getRang(5)) 
            result="Two Worlds Marathon Runner";
        else result="Marathon Runner of Time"; 
        gpJeu->getKeyboard()->setRang(8); gpJeu->getKeyboard()->saveP();
        gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
}

void Generique::draw(SDL_Surface* gpScreen) {
    SDL_Rect dst; dst.x = 0; dst.y = 0;
	int mode = gpJeu->getKeyboard()->getMode();
	
	if(mode>3 && mode !=28) {
		dst.y += BOTTOMOFF;
	} else {
		dst.y += BOTTOMOFF;
		dst.w = 320;
		dst.h = 240;
        SDL_FillRect(gpScreen, &dst, SDL_MapRGB(gpScreen->format, 0, 0, 0));
		dst.y = 0;
	}
	
    SDL_BlitSurface(image, NULL, gpScreen, &dst);
}

void Generique::drawSelection(SDL_Surface* gpScreen, int ligne, int colonne) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26+152*colonne; dst.y = BOTTOMOFF+53+48*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
}

void Generique::drawOption(SDL_Surface* gpScreen, int ligne, int opt1, int opt2) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26; dst.y = BOTTOMOFF+69+64*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
    
    src.h = 16; src.w = 8;src.x = 0;src.y=0;
    dst.x = 136+16*opt1; dst.y = BOTTOMOFF+56+16;
    SDL_BlitSurface(imageNiveau, &src, gpScreen, &dst);
                
    src.h = 16; src.w = 8;src.x = 0;src.y=0;
    dst.x = 136+16*opt2; dst.y = BOTTOMOFF+56+16+64;
    SDL_BlitSurface(imageNiveau, &src, gpScreen, &dst);
}

void Generique::drawRecord(SDL_Surface* gpScreen, int ligne, int colonne) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26+152*colonne; dst.y = BOTTOMOFF+53+48*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
}

void Generique::drawEffacer(SDL_Surface* gpScreen, int ligne) {
    drawRecord(gpScreen, 3, 1);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = BOTTOMOFF+113+20*ligne;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawCharger(SDL_Surface* gpScreen, int ligne, int ligne2) {
    drawSelection(gpScreen, ligne, 0);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = BOTTOMOFF+93+20*ligne2;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawEffacerSave(SDL_Surface* gpScreen, int ligne, int ligne2) {
    drawSelection(gpScreen, ligne, 0);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = BOTTOMOFF+113+20*ligne2;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawIntro(SDL_Surface* gpScreen, int etape) {
    SDL_Rect src;
    SDL_Rect dst;
    
    if(SDL_GetTicks() > lastAnimTime + 40) {
        lastAnimTime = SDL_GetTicks();
        anim++;
        if (anim > 31) anim = 0;
    }
                
    src.h = 16; src.w = 16;
    for (int j=0; j<240; j+=16) 
        for (int i=0; i<320; i+=16) {
            src.x = 16-anim%16;src.y=anim%16; dst.x = i; dst.y = j;
            if (i>16 && i<288 && j>144 && j<224) src.x+=32;
            SDL_BlitSurface(imageFond2, &src, gpScreen, &dst);
        }
                
    src.h = 32; src.w = 32;
    for (int j=0; j<240; j+=32) 
        for (int i=0; i<320; i+=32) {
            src.x = anim;src.y=anim; dst.x = i; dst.y = j;
            if (i>16 && i<288 && j>144 && j<224) src.x+=64;
            SDL_BlitSurface(imageFond1, &src, gpScreen, &dst);
        }
                
    src.h = 111; src.w = 320;
    src.x = 0; src.y=0; dst.x = 0; dst.y = 17;
    SDL_BlitSurface(imageIntro[etape], &src, gpScreen, &dst);
                
    gpJeu->getTexte()->draw(gpScreen);
	
	dst.x = 0; dst.y = 240; dst.h = 240; dst.w = 320;
	SDL_FillRect(gpScreen, &dst, SDL_MapRGB(gpScreen->format, 0, 0, 0));

}

void Generique::drawDebut(SDL_Surface* gpScreen) {
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(image, NULL, gpScreen, &dst);
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::drawBackground(SDL_Surface* gpScreen) {
    SDL_Rect dst;
	dst.x = 0;
	dst.y = 240;
    SDL_BlitSurface(imageBackground, NULL, gpScreen, &dst);
}
