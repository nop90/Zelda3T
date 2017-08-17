/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include "Personnage.h"
#include "Bouclier.h"

class Jeu;

class Joueur : public Personnage {
    public :
        Joueur(Jeu* jeu, int nmsv);
        ~Joueur();
        void saveSemiEmpl();
        void restoreSemiEmpl();
        void restoreEmpl();
        void restoreOldEmpl();
        void draw(SDL_Surface* gpScreen);
        void moveX(int i, int nbdir);
        void moveY(int i, int nbdir);
        void moveX(int i);
        void moveY(int i);
        void setTypeAnim(int t);
        int getTypeAnim();
        void setBouclier(int b);
        void setMagie(int b);
        void setMagieMax(int b);
        void setEpee(int e);
        void setTunique(int t);
        void setRubis(int i);
        void setPiece(int i);
        void setGanon(int i);
        void setFleche(int i);
        void setBombe(int i);
        void setRubisMax(int i);
        void setPieceMax(int i);
        void setGanonMax(int i);
        void setFlecheMax(int i);
        void setBombeMax(int i);
        void calculDef();
        void chargeSpin();
        void dechargeSpin();
        int getCharge();
        int nbQuarts();
        int nbCristaux();
        bool hasCristal(int i);
        void setCristal(int i);
        bool hasMedaillon(int i);
        void trouveMedaillon(int i);
        bool hasMelodie(int i);
        void setMelodie(int i, int v=1);
        int hasObjet(int i);
        int hasBouteille(int i);
        void setBouteille(int i, int v);
        int getMagie();
        int getMagieMax();
        int getMiMagie();
        int getForce();
        int getEpee();
        int getTunique();
        int getDefense();
        int getBouclier();
        int getRubis();
        int getPiece();
        int getGanon();
        int getFleche();
        int getBombe();
        int getRubisMax();
        int getPieceMax();
        int getGanonMax();
        int getFlecheMax();
        int getBombeMax();
        int getObjet();
        int getCle();
        void setObjet(int i);
        bool getOni();
        void setOni(bool b);
        bool verifZone();
        bool isDauphin();
        void savePrec();
        void setVie(int i);
        void setVieMax(int i);
        void bigPlouf();
        void antiPlouf();
        void revie();
        int getBoostVie();
        void setBoostVie(int i);
        int getBoostMagie();
        void setBoostMagie(int i);
        int getBoostRubis();
        void setBoostRubis(int i);
        int getBoostPiece();
        void setBoostPiece(int i);
        int getBoostGanon();
        void setBoostGanon(int i);
        int getPousse();
        void setPousse(int i);
        void setTrouve(int i);
        int getCoeur(int i);
        void setCoeur(int i);
        int getCoffre(int i, int j);
        void setCoffre(int i, int j, int val=1);
        int getCle(int i, int j);
        void setCle(int i, int j, int val=1);
        int getAvancement();
        void setAvancement(int i);
        int getTemps(int i);
        void trouveObjet(int obj, int val=1);
        bool getExplore(int z, int i, int j);
        void setExplore(int z, int i, int j);
        void visible();
        void nonvisible();
        bool isLapin();
        void setLapin(bool b=true);
        void save();
        void load();
        void setImmo(bool b);
        bool getImmo();
        int nbEnnemis();
        void setEnnemi(int i);
        int getEnnemi(int i);
        int nbPoissons();
        void setPoisson(int i);
        int getPoisson(int i);
        bool getLoader();
        int getMort();
        int getTutoriel();
        void setTutoriel(int i);
        int getSolde();
        void paye();
        void testTapis();
        void geler();
        void degeler();
        int getGel();
        void mortel();
        int getGemme();
        int getGemme(int g);
        int getNbGemmes();
        void setGemme(int g);
        void trouveGemme(int g);
        void peche();
        void finPeche();
        void saveOldMap(); // sauvegarde la map à quitter pour restauration future
        int getTroc(int i);
        void setTroc(int i, int v);
        int getPosBarque();
        void setPosBarque(int i);
        int getPosBarqueOld();
        int getPosWagon();
        void setPosWagon(int i);
        int getPosWagonOld();
        int getPosRails();
        void setPosRails(int i);
        int getCafe();
        void boostCafe();
        int getChargeCafe();
        void boostChargeCafe();
        int getCafePaye();
        void egaliseCafePaye();
        void payeCafe();
        int nbLoups();
        bool isIvre();
        void setIvre();
        void setCompteurVisible(bool b);
        bool isCompteurVisible();
        bool isEnnVisible();
        void setCompteur(int i);
        int getCompteur();
        void setCompteurEnn(int i);
        int getCompteurEnn();
        void setCompteurType(int i);
        int getCompteurType();
        void razCompteurType();
        bool isTempsVisible();
        void setTempsVisible(bool b);
        Uint32 getTimeC();
        void initTimeC();
        void saveEmpl();
    private :
        void tireFleche();
        void tireGrappin();
        void tireMagie();
        void tireLanterne();
        void poseBombe();
        void lance(int v);
        void boit();
        void glisser();
        void drawChute(SDL_Surface* gpScreen);
        void drawImmoMarche(SDL_Surface* gpScreen);
        void drawCharge(SDL_Surface* gpScreen);
        void drawEpee(SDL_Surface* gpScreen);
        void drawSpin(SDL_Surface* gpScreen);
        void drawArc(SDL_Surface* gpScreen);
        void drawGrappin(SDL_Surface* gpScreen);
        void drawBaguette(SDL_Surface* gpScreen);
        void drawFlotte(SDL_Surface* gpScreen);
        void drawSouleve(SDL_Surface* gpScreen);
        void drawBoire(SDL_Surface* gpScreen);
        void drawPousse(SDL_Surface* gpScreen);
        void drawTrouve(SDL_Surface* gpScreen);
        void drawTouche(SDL_Surface* gpScreen);
        void drawMort(SDL_Surface* gpScreen);
        void drawPeche(SDL_Surface* gpScreen);
        void drawBarque(SDL_Surface* gpScreen);
        void drawWagon(SDL_Surface* gpScreen);
        int selectionPoisson();
        void collisionEpee();
        void collisionSpin();
        
        int numSave;
        int temps; //temps depuis la sauvegarde chargée
        int xdep2;
        int ydep2;
        Direction dirdep2;
        int magie;
        int magiemax;
        int typeanim;
        int minanim;
        int fleche;
        int bombe;
        int rubis;
        int pieceor;
        int ganonor;
        int objet;
        int gemme;
        int cafe;
        int cafep;
        int charge_cafe;
        int loups;
        Bouclier* boucl;
        int bouclier;
        int tunique;
        int epee;
        Jeu* gpJeu;
        int charge;
        int flechemax;
        int bombemax;
        int rubismax;
        int pieceormax;
        int ganonormax;
        bool lapin;
        bool oni;      //transformé
        int plouf;  //si entre dans l'eau
        int recup; //auto-recup quand suffisament grand;
        int mort; //nombre de mort
        int porte; //objet porté
        int boostVie;
        int boostMagie;
        int boostRubis;
        int boostPiece;
        int boostGanon;
        int pousse;
        int trouve;
        int posBarque;
        int posBarqueOld;
        int posWagon;
        int posWagonOld;
        int posRails;
        int avancement;
        int tutoriel;
        bool invisible;
        int dirglisse;          //direction pour glisser
        int dirglace;           //direction dans laquel link a commencer à glisser
        int glace;
        int glisse;      // si sur surface glissante et à quel point
        int vitesse;
        int oldxg; //x précédent
        int oldyg; //y précédent
        bool immo;
        bool loader; //si les données ont été chargées depuis une sauvegarde
        int verse;   //déjà versé
        int gel;
        int ivre;
        bool tempsVisible;   //pour course casino
        bool compteurVisible; //pour donjons cachés
        bool ennVisible; //pour destination finale
        int compteur;
        int compteurEnn;
        int cptType;
        int compteurType[12];
        int defense;
        int coeur[29]; //13 coeurs + 16 quarts de coeur
        int gemmes[200];
        int cristaux[7];
        int medaillon[3];
        int objets[35];
        int bouteille[4];
        int melodie[3];
        int ennemis[150]; //ennemis vaincus
        int poissons[30]; // poissons pêchés
        int troc[16]; //marchandises de troc
        int cle[15][4]; // clés dans donjon i, 0 : carte, 1 : boussole, 2 : clé boss, 3 : clés
        int coffre[16][64]; //15 donjons + coffres extérieurs
        bool explore[15][20][20]; //lieux explorés dans les donjons
        int oldx[8]; //x précédents
        int oldy[8]; //y précédents
        SDL_Surface* imageTmp; //image servant pour des animations quelconques
        SDL_Surface* imageEpee;
        SDL_Surface* imageSpin;
        SDL_Surface* imageObjets;
        Uint32 TimeB; //temps de la dernière sauvegarde chargée
        Uint32 TimeC; //temps de départ de la course
};

#endif  // Joueur.h
