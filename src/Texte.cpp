/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"
#include "Keyboard.h"

Texte::Texte(Jeu* jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("") {
    lastAnimTime = SDL_GetTicks();
    imageFont = IMG_Load("romfs:/images/texte/font.png");
    SDL_SetColorKey(imageFont,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
    imageCoeur = IMG_Load("romfs:/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
}

Texte::~Texte() {
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::chercheText() {
    ostringstream os;
    ostringstream os2;
    int tmp;
    switch (id) {
        case 1 : texte = "Trade item*Talk with the good person to trade it."; break;
        case 2 : texte = "You cannot fish here, try to find a pontoon."; break;
        case 3 : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "You have found a piece of heart!!!";
            if (tmp<4) buffer = "Collect "+os.str()+" more to have a new heart!!!";
            else buffer = "You've gained a new heart !!!";
            break;
        case 4 : texte = "You really enjoy talking to trees, don't you?"; break;
        case 5 : texte = "Link's house**Do not come any closer."; break;
        case 6 : texte = "N: To the Kakariko Village"; break;
        case 7 : texte = "E : To Hyrule City"; break;
        case 8 : texte = "Nothing caught..."; break;
        case 9 : texte = "You caught a crawfish!"; break;
        case 10 : texte = "You caught a smelt!"; break;
        case 11 : texte = "You caught a zebrafish!"; break;
        case 12 : texte = "You caught a goby!"; break;
        case 13 : texte = "You caught a crab!"; break;
        case 14 : texte = "You caught an eel larvae!"; break;
        case 15 : texte = "You caught a minnow!"; break;
        case 16 : texte = "You caught a goldfish!"; break;
        case 17 : texte = "You caught a bleak!"; break;
        case 18 : texte = "You caught a gudgeon!"; break;
        case 19 : texte = "You caught a loach!"; break;
        case 20 : texte = "You caught a stickleback!"; break;
        case 21 : texte = "You caught a ruffe!"; break;
        case 22 : texte = "You caught a blenny!"; break;
        case 23 : texte = "You caught a magikarp!"; buffer="It had no effect..."; break;
        case 24 : texte = "You caught a trout!*It's a big fish!"; break;
        case 25 : texte = "You caught an ayu!*It's a big fish!"; break;
        case 26 : texte = "You caught a black perch!*It's a big fish!"; break;
        case 27 : texte = "You caught an eel!*It's a big fish!"; break;
        case 28 : texte = "You caught a catfish!*It's a big fish!"; break;
        case 29 : texte = "You caught a largemouth bass!*It's a big fish!"; break;
        case 30 : texte = "You caught a huchen!*It's a big fish!"; break;
        case 31 : texte = "You caught a barbell!*It's a big fish!"; break;
        case 32 : texte = "You caught a lamprey!*It's a big fish!"; break;
        case 33 : texte = "You caught a nase!*It's a big fish!"; break;
        case 34 : texte = "You caught a salmon!*This fish is huge!"; break;
        case 35 : texte = "You caught a sturgeon!*This fish is huge!"; break;
        case 36 : texte = "You caught an arctic charr!*This fish is huge!"; break;
        case 37 : texte = "You caught a carp!*This fish is huge!"; break;
        case 38 : texte = "You caught a brown bullhead!*This fish is huge!"; break;
        case 39 : texte = "You have found a power gem!**Barter it in the city for prices."; break;
        case 40 : 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_DEVANT_CHEZ_LINK) {id=44; chercheText();break;}
            texte = "Good morning sir Link!*You look dreadful, were you asleep?"; idsuiv=41; break;
        case 41 : texte = "The princess wants to see you urgently at the castle!"; idsuiv=42; break;
        case 42 : texte = "..."; idsuiv=43; break;
        case 43 : texte = "..."; idsuiv=44; break;
        case 44 : texte = "The castle. To the east, don't tell me you've forgotten?"; break;
        case 45 : texte = "Hem Hem..."; idsuiv=46; break;
        case 46 : texte = "TUTORIAL : Press A near someone to talk with him, or near a sign to read it."; break;
        case 47 : texte = "You didn't learn any song.";
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=48; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=57; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=59; chercheText();break;}
            break;
        case 48 : texte = "- SONG OF SOARING*- Do not play";
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=50; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=61; chercheText();break;}
            break;
        case 49 : texte = "- Song of Soaring*- DO NOT PLAY"; break;
        case 50 : texte = "- SONG OF SOARING*- Inverted Song of Time*- Do not play";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=53; chercheText();break;}
            break;
        case 51 : texte = "- Song of Soaring*- INVERTED SONG OF TIME*- Do not play"; break;
        case 52 : texte = "- Song of Soaring*- Inverted Song of Time*- DO NOT PLAY"; break;
        case 53 : texte = "- SONG OF SOARING*- Inverted Song of Time*- Song of Double Time*- Do not play"; break;
        case 54 : texte = "- Song of Soaring*- INVERTED SONG OF TIME*- Song of Double Time*- Do not play"; break;
        case 55 : texte = "- Song of Soaring*- Inverted Song of Time*- SONG OF DOUBLE TIME*- Do not play"; break;
        case 56 : texte = "- Song of Soaring*- Inverted Song of Time*- Song of Double Time*- DO NOT PLAY"; break;
        case 57 : texte = "- INVERTED SONG OF TIME*- Do not play";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=64; chercheText();break;}
            break;
        case 58 : texte = "- Inverted Song of Time*- DO NOT PLAY"; break;
        case 59 : texte = "- SONG OF DOUBLE TIME*- Do not play"; break;
        case 60 : texte = "- Song of Double Time*- DO NOT PLAY"; break;
        case 61 : texte = "- SONG OF SOARING*- Song of Double Time*- Do not play"; break;
        case 62 : texte = "- Song of Soaring*- SONG OF DOUBLE TIME*- Do not play"; break;
        case 63 : texte = "- Song of Soaring*- Song of Double Time*- DO NOT PLAY"; break;
        case 64 : texte = "- INVERTED SONG OF TIME*- Song of Double Time*- Do not play"; break;
        case 65 : texte = "- Inverted Song of Time*- SONG OF DOUBLE TIME*- Do not play"; break;
        case 66 : texte = "- Inverted Song of Time*- Song of Double Time*- DO NOT PLAY"; break;
        case 67 : texte = "No effect..."; break;
        case 68 : texte = "Link's estate*Private property"; break;
        case 69 : texte = "Hyrule City"; break;
        case 70 : texte = "Looks like there are no fish here..."; break;
        case 71 : texte = "N: To Hyrule Castle"; break;
        case 72 : texte = "The castle is up north, hurry up!"; break;
        case 73 : texte = "The castle is on the other side of the bridge, rush up!"; break;
        case 74 : texte = "The princess is waiting for you at the castle, northerly from here."; break;
        
        case 75 : texte = "You don't have enough."; break;
        case 76 : texte = "Come back if you change your mind."; break;
        case 77 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)>-1) {id=80; chercheText();break;}
            texte = "A cogwheel for a chicken and 100 rupees?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100
            || gpJeu->getJoueur()->getTroc(M_POULET)<1) idsuiv=75;
            break;
        case 78 : texte = "A cogwheel for a chicken and 100 rupees?**              yes              NO ?"; idsuiv=76; break;
        case 79 : texte = "You got a cogwheel!*Go and give it to the man near of the waterfall!"; break;
        case 80 : 
            if ((gpJeu->getJoueur()->getCoeur(14) && gpJeu->getZone()==18)
            || (gpJeu->getJoueur()->getCoeur(15) && gpJeu->getZone()==3)) {
                id=82; chercheText();break;}
            texte = "A piece of heart for a magma rock and a frosty rock?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<1) idsuiv=75;
            break;
        case 81 : texte = "A piece of heart for a magma rock and a frosty rock?*              yes              NO ?"; idsuiv=76; break;
        case 82 : texte = "Sorry, I have nothing in stock anymore."; break;
        case 83 : 
            if (gpJeu->getJoueur()->getRubisMax()>=200) {id=86; chercheText();break;}
            texte = "A wallet able to hold up to 200 rupees for 1 feather and 10 rupees?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10
            || gpJeu->getJoueur()->getTroc(M_PLUME)<1) idsuiv=75;
            break;
        case 84 : texte = "A wallet able to hold up to 200 rupees for 1 feather and 10 rupees?*              yes              NO ?"; idsuiv=76; break;
        case 85 : texte = "You got a regular wallet!*It allows you to hold up to 200 rupees!"; break;
        case 86 : 
            if (gpJeu->getJoueur()->getRubisMax()>=500) {id=89; chercheText();break;}
            texte = "A wallet able to hold up to 500 rubis for a tapestry and 100 rupees?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100
            || gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1) idsuiv=75;
            break;
        case 87 : texte = "A wallet able to hold up to 500 rubis for a tapestry and 100 rupees?*              yes              NO ?"; idsuiv=76; break;
        case 88 : texte = "You got a big wallet!*It allows you to hold up to 500 rupees!!!"; break;
        case 89 : 
            if (gpJeu->getJoueur()->getRubisMax()==999) {id=82; chercheText();break;}
            texte = "A wallet able to hold up to 999 rupees for 1 amulet, 1 magma rock and 250 rupees?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1) idsuiv=75;
            break;
        case 90 : texte = "A wallet able to hold up to 999 rupees for 1 amulet, 1 magma rock and 250 rupees?*              yes              NO ?"; idsuiv=76; break;
        case 91 : texte = "You got a huge wallet!!!*It allows you to hold up to 999 rupees!!!"; break;
        case 92 : 
            texte = "A chicken for 2 bags of rice and 3 bags of olives?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_RIZ)<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<3) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_POULET)>=99) idsuiv=95;
            break;
        case 93 : texte = "A chicken for 2 bags of rice and 3 bags of olives?**              yes              NO ?"; idsuiv=76; break;
        case 94 : texte = "You got a chicken!"; break;
        case 95 : texte = "You can't carry more..."; break;
        case 96 : 
            texte = "A feather for 2 jars of spices and 2 bags of olives ?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PLUME)>=99) idsuiv=95;
            break;
        case 97 : texte = "A feather for 2 jars of spices and 2 bags of olives?*              yes              NO ?"; idsuiv=76; break;
        case 98 : texte = "You got a feather!"; break;
        case 99 : 
            texte = "A bag of rice for 15 rupees?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_RIZ)>=99) idsuiv=95;
            break;
        case 100 : texte = "A bag of rice for 15 rupees?**              yes              NO ?"; idsuiv=76; break;
        case 101 : texte = "You got a bag of rice!"; break;
        case 102 : 
            texte = "A bag of olives for 10 rupees?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_OLIVES)>=99) idsuiv=95;
            break;
        case 103 : texte = "A bag of olives for 10 rupees?**              yes              NO ?"; idsuiv=76; break;
        case 104 : texte = "You got a bag of olives!"; break;
        case 105 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>2) {id=112; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==2 
            && gpJeu->getJoueur()->getObjet()==15) {id=106; chercheText();break;}
            texte = "I feel like I spent my entire life sweeping...*One of these days, I would like to go on a journey..."; break;
        case 106 : texte = "Is this a chart you have?*Do you mind giving it to me? I dream of going in a travel to see wonderful things!"; idsuiv=107; break;
        case 107 : texte = "I will give you my broom in return, is it okay with you?*              YES ?            no  "; idsuiv=109; break;
        case 108 : texte = "I will give you my broom in return, is it okay with you?*              yes              NO ?"; idsuiv=110; break;
        case 109 : texte = "Thank you! Take my broom as a reward. It's a first-class broom, it is in my family since centuries, you're making a good deal!"; break;
        case 110 : texte = "Oh. If that's so I guess I just have to keep sweeping..."; break;
        case 111 : texte = "You traded the chart for a broom!"; break;
        case 112 : texte = "So, where am I going?"; break;
        case 113 : texte = "Sometimes, in my dream, I eat them spit roasted..."; break;
        case 114 : texte = "This town is full of shops of all kinds, too bad I'm interested in none of them..."; break;
        case 115 : texte = "Since the return of the peace, princess Zelda made a lot for Hyrule. There wouldn't be such prosperous town without her."; break;
        case 116 : texte = "To barter is the only way to get some rare objects, or some ingredients to cook."; break;
        case 117 : texte = "My Mom always tells me not to get close the hens... Why?"; break;
        case 118 : texte = "The princess insists that we keep watching on the city... But every one know that Ganon is dead..."; break;
        case 119 : texte = "I would rather sleep in the castle instead of mounting guard here..."; break;
        case 120 : texte = "Life is good in Hyrule since Ganon is not a threat anymore, thanks again Link!"; break;
        case 121 : texte = "Since the theft in the castle, the princess doubled the guard... and here I am, again..."; break;
        case 122 : texte = "Join up, they said... It's a man's life, they said..."; break;
        case 123 : texte = "I heard that a very precious object has been stolen in the castle, and since then the princess would have become an absolute paranoiac...";
            buffer="I guess it was something she was fond of... A mirror of her collection, probably..."; break;
        case 124 : texte = "Zzzzz... Zzzzz..."; break;
        case 125 : texte = "N : To Ganon Castle"; break;
        case 126 : 
            if (gpJeu->getJoueur()->hasObjet(O_PERLE)) {id=82; chercheText();break;}
            texte = "The Moon Pearl for a wheel, a gauge, an energy core and 100 Gold Ganon?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100
            || gpJeu->getJoueur()->getTroc(M_ROUE)<1
            || gpJeu->getJoueur()->getTroc(M_JAUGE)<1
            || gpJeu->getJoueur()->getTroc(M_SOURCE_ENERGIE)<1) idsuiv=75;
            break;
        case 127 : texte = "The Moon Pearl for a wheel, a gauge, an energy core and 100 Gold Ganon?*              yes              NO ?"; idsuiv=76; break;
        case 128 : texte = "You got the Moon Pearl!*You regain your normal aspect and the use of your weapons!"; break;
        case 129 : 
            if (gpJeu->getJoueur()->getGanonMax()>=200) {id=132; chercheText();break;}
            texte = "A wallet able to hold up to 200 Gold Ganon for a pearl and 10 Gold Ganon?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10
            || gpJeu->getJoueur()->getTroc(M_PERLES)<1) idsuiv=75;
            break;
        case 130 : texte = "A wallet able to hold up to 200 Gold Ganon for a pearl and 10 Gold Ganon?*              yes              NO ?"; idsuiv=76; break;
        case 131 : texte = "You got a regular wallet!*It allows you to hold up to 200 Gold Ganon!"; break;
        case 132 : 
            if (gpJeu->getJoueur()->getGanonMax()>=500) {id=135; chercheText();break;}
            texte = "A wallet able to hold up to 500 Gold Ganon for an amulet and 100 Gold Ganon?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1) idsuiv=75;
            break;
        case 133 : texte = "A wallet able to hold up to 500 Gold Ganon for an amulet and 100 Gold Ganon?*              yes              NO ?"; idsuiv=76; break;
        case 134 : texte = "You got a big wallet!*It allows you to hold up to 500 Gold Ganon!!!"; break;
        case 135 : 
            if (gpJeu->getJoueur()->getGanonMax()==999) {id=82; chercheText();break;}
            texte = "A wallet able to hold up to 999 Gold Ganon for a perfume, a frosty rock and 250 Gold Ganon?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<250
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<1) idsuiv=75;
            break;
        case 136 : texte = "A wallet able to hold up to 999 Gold Ganon for a perfume, a frosty rock and 250 Gold Ganon?*              yes              NO ?"; idsuiv=76; break;
        case 137 : texte = "You got a huge wallet!!!*It allows you to hold up to 999 Gold Ganon!!!"; break;
        case 138 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUE)>-1) {id=141; chercheText();break;}
            texte = "A wheel for 3 jars of spices?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<3) idsuiv=75;
            break;
        case 139 : texte = "A wheel for 3 jars of spices?**              yes              NO ?"; idsuiv=76; break;
        case 140 : texte = "You got a wheel!*...*Awesome..."; break;
        case 141 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=82; chercheText();break;}
            texte = "A bomb bag for 1 pepper et 3 jars of spices?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)<1
            || gpJeu->getJoueur()->getTroc(M_EPICES)<3) idsuiv=75;
            break;
        case 142 : texte = "A bomb bag for 1 pepper et 3 jars of spices?**              yes              NO ?"; idsuiv=76; break;
        case 143 : texte = "You got a bomb bag!*You will be able to blow out new ways!"; break;
        case 144 : 
            texte = "A magma rock for a tapestry, an amulet and a perfume?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)>=99) idsuiv=95;
            break;
        case 145 : texte = "A magma rock for a tapestry, an amulet and a perfume?*              yes              NO ?"; idsuiv=76; break;
        case 146 : texte = "You got a magma rock!"; break;
        case 147 : 
            texte = "A pearl for 5 jars of spices and 5 Gold Ganon? *              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5
            || gpJeu->getJoueur()->getTroc(M_EPICES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 148 : texte = "A pearl for 5 jars of spices and 5 Gold Ganon? *              yes              NO ?"; idsuiv=76; break;
        case 149 : texte = "You got a pearl!"; break;
        case 150 : 
            texte = "A jar of spices for 10 Gold Ganon?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_EPICES)>=99) idsuiv=95;
            break;
        case 151 : texte = "A jar of spices for 10 Gold Ganon?**              yes              NO ?"; idsuiv=76; break;
        case 152 : texte = "You got a jar of spice!"; break;
        case 153 : texte = "He! Heeeee! Heeeeeeee!"; break;
        case 154 : texte = "Last night, the barman didn't have beer left... Ganon turned red with rage and started to destroy everything..."; buffer="In the end, no one has anything left to drink..."; break;
        case 155 : texte = "The destroyed houses were Ganon's opponents' ones..."; 
            buffer="The bar is destroyed too, but... ...for other reasons..."; break;
        case 156 : texte = "The market place is main attraction of the city, now that the bar is ruined..."; break;
        case 157 : 
            if (gpJeu->getJoueur()->hasObjet(O_PERLE)) texte = "You've got the Moon Pearl?*Well, in view of the result, maybe it wasn't that much of a good deal...";
            else texte = "The Moon Pearl helps you regain a human aspect. A stallholder has one, but it's far too expensive..."; break;
        case 158 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "N : Holy Lands - Camping prohibited"; break;
        case 159 : 
            if (gpJeu->getJoueur()->getPieceMax()>=200) {id=162; chercheText();break;}
            texte = "A wallet able to hold up to 200 Gold coins for a chicken and 10 Gold coins?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10
            || gpJeu->getJoueur()->getTroc(M_POULET)<1) idsuiv=75;
            break;
        case 160 : texte = "A wallet able to hold up to 200 Gold coins for a chicken and 10 Gold coins?*              yes              NO ?"; idsuiv=76; break;
        case 161 : texte = "You got a regular wallet!*It allows you to hold up to 200 Gold coins!"; break;
        case 162 : 
            if (gpJeu->getJoueur()->getPieceMax()>=500) {id=165; chercheText();break;}
            texte = "A wallet able to hold up to 500 Gold coins for a perfume and 100 Gold coins?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<100
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            break;
        case 163 : texte = "A wallet able to hold up to 500 Gold coins or a perfume and 100 Gold coins?*              yes              NO ?"; idsuiv=76; break;
        case 164 : texte = "You got a big wallet!*It allows you to hold up to 500 Gold coins!!!"; break;
        case 165 : 
            if (gpJeu->getJoueur()->getPieceMax()==999) {id=82; chercheText();break;}
            texte = "A wallet able to hold up to 999 Gold coins for a tapestry, a magma rock and 250 Gold coins?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<250
            || gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1) idsuiv=75;
            break;
        case 166 : texte = "A wallet able to hold up to 999 Gold coins for a tapestry, a magma rock and 250 Gold coins?*              yes              NO ?"; idsuiv=76; break;
        case 167 : texte = "You got a huge wallet!!!*It allows you to hold up to 999 Gold coins!!!"; break;
        case 168 : 
            texte = "An amulet for 1 chicken and 2 bags of olives?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<1
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_AMULETTE)>=99) idsuiv=95;
            break;
        case 169 : texte = "An amulet for 1 chicken and 2 bags of olives?*              yes              NO ?"; idsuiv=76; break;
        case 170 : texte = "You got an amulet!"; break;
        case 171 : 
            texte = "A feather for a jar of spices and a bag of olives?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<1
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PLUME)>=99) idsuiv=95;
            break;
        case 172 : texte = "A feather for a jar of spices and a bag of olives?*              yes              NO ?"; idsuiv=76; break;
        case 173 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "With all these wolves, it's very dangerous to leave the village..."; break;
        case 174 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Your weapon looks like this of the Knights... *Did you ever fight wolves with it?"; break;
        case 175 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "I hate hens, but if the wolves manage to get in the village, maybe they won't dare coming close..."; break;
        case 176 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "The torchs at the entry of the village keep the wolves away, but they come closer and closer every day..."; break;
        case 177 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "The chief of the village had a bar built recently... They say that he would have done this to attract the Hylian Knights so that they would protect us..."; break;
        case 178 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (!gpJeu->getJoueur()->getPieceMax()) {id=771; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>3) {id=185; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==3 
            && gpJeu->getJoueur()->getObjet()==15) {id=179; chercheText();break;}
            texte = "When time is no good, I make marmelades to keep me busy... But in this season, I guess I will have to find another activity..."; break;
        case 179 : texte = "Is that a broom you have?*I feel a vocation springing up in me... Will you cede it to me for my last marmelade jar?"; idsuiv=180; break;
        case 180 : texte = "This broom for a marmelade pot?**              YES ?            no  "; idsuiv=182; break;
        case 181 : texte = "This broom for a marmelade pot?**              yes              NO ?"; idsuiv=183; break;
        case 182 : texte = "Great! This will keep my mind away of all the problems of this time, and maybe it will even keep the wolves away of me!"; break;
        case 183 : texte = "Sooner or later, I'm sure you will give it to me..."; break;
        case 184 : texte = "You traded the broom for a marmelade pot!"; break;
        case 185 : texte = "Giving is giving!"; break;
        case 186 : texte = "Hyrule Castle"; break;
        case 187 : texte = "N : To the graveyard"; break;
        case 188 : texte = "Welcome in the castle, Sir Link!"; break;
        case 189 : texte = "We were ordered to let you pass."; break;
        case 190 : texte = "Ganon Castle"; break;
        case 191 : 
            texte = "5 Gold Ganon and we let ya come'n go in the castle?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5) idsuiv=75;
            break;
        case 192 : texte = "5 Gold Ganon and we let ya come'n go in the castle?*              yes              NO ?"; idsuiv=76; break;
        case 193 : texte = "You can go."; break;
        case 194 : texte = "MAY THE WAY TO THE TRIFORCE BE OPENED FOR YOU...*SEE APPEAR THE TEMPLE OF THE TRIFORCE!"; break;
        case 195 : texte = "W : To Hyrule Castle"; break;
        case 196 : texte = "N : To the waterfalls"; break;
        case 197 : texte = "E : Entry of the Lost Woods"; break;
        case 198 : 
            tmp = 6-(gpJeu->getJoueur()->nbCristaux());
            os << tmp;
            texte = "You've found a magic crystal!!!";
            if (tmp>0) buffer = "Again "+os.str()+" left to find!";
            else buffer = "Finally you've got them all!!!";
            break;
        case 199 : texte = "Do you want to save your game?**                    ? YES ?*                      no   "; break;
        case 200 : texte = "Do you want to save your game?**                      yes  *                    ? NO  ?"; break;
        case 201 : texte = "Game saved."; break;
        
        case 202 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>6) {id=209; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==6 
            && gpJeu->getJoueur()->getObjet()==11) {id=203; chercheText();break;}
            texte = "I'm building an opera here, I don't have time to talk during the break!"; 
            buffer="What's more, I've lost my precious star accessory..."; break;
        case 203 : texte = "You've found my fetish skull???*I had forgotten it in jail...*Give it back! I will be eternally grateful!"; idsuiv=204; break;
        case 204 : texte = "This skull for my gratefulness, ok?**              YES ?            no  "; idsuiv=206; break;
        case 205 : texte = "This skull for my gratefulness, ok?**              yes              NO ?"; idsuiv=207; break;
        case 206 : texte = "Thank you! I regain all motivation! I will finish this opera!"; buffer="After a break..."; break;
        case 207 : texte = "Thief..."; break;
        case 208 : texte = "You traded the skull for an IOU!"; break;
        case 209 : texte = "To be or not to be? that is the question..."; buffer="do I say it well ?"; break;
        case 210 : texte = "Temple of Courage**Courage, flee!"; break;
        case 211 : texte = "Welcome at Tingle's place!"; break;
        case 212 : texte = "Temple of Air**Chance of cold!"; break;
        case 213 : texte = "S : To Mabe Village"; break;
        case 214 : texte = "Mabe Village"; break;
        case 215 : 
            texte = "A tapestry for 2 pearls and 5 jars of spices? **              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_PERLES)<2
            || gpJeu->getJoueur()->getTroc(M_EPICES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)>=99) idsuiv=95;
            break;
        case 216 : texte = "A tapestry for 2 pearls and 5 jars of spices? **              yes              NO ?"; idsuiv=76; break;
        case 217 : texte = "You got a tapestry!"; break;
        case 218 : 
            texte = "An amulet for 5 chickens and 5 bags of olives? *              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<5
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_AMULETTE)>=99) idsuiv=95;
            break;
        case 219 : texte = "An amulet for 5 chickens and 5 bags of olives? *              yes              NO ?"; idsuiv=76; break;
        case 220 : 
            texte = "A pearl for 2 jars of spices and 2 bags of rice?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<2
            || gpJeu->getJoueur()->getTroc(M_RIZ)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 221 : texte = "A pearl for 2 jars of spices and 2 bags of rice?*              yes              NO ?"; idsuiv=76; break;
        case 222 : 
            texte = "A bag of rice for a bag of olives and 2 rupees? *              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_RIZ)>=99) idsuiv=95;
            break;
        case 223 : texte = "A bag of rice for a bag of olives and 2 rupees? *              yes              NO ?"; idsuiv=76; break;
        case 224 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)==0) 
                texte = "The men of the village are all obsessed by the fishing contest...*I wonder who will be the winner..."; 
            else if (gpJeu->getJoueur()->hasObjet(O_POISSONS)==0)
                {texte = "You're participating in the fishing contest too?*...*..."; buffer="In the end you're just like the others...";} 
            else {texte = "You won the fishing contest?*...*..."; buffer="I am your biggest fan!!!";}
            break;
        case 225 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)==0) 
                texte = "A fishing stand has just opened at the west of the village...*The owner organizes a great fishing contest to mark the start of his shop."; 
            else if (gpJeu->getJoueur()->hasObjet(O_POISSONS)==0)
                {texte = "You are in the contest too? *It's hopeless, I can't find more than three types of fish...";} 
            else {texte = "Since the fishing contest is over, everyone returned to his own business.";}
            break;
        case 226 : texte = "Ma e Vi l ge"; break;
        case 227 : 
            texte = "Hang-out of the Fearless Knights";
            if (gpJeu->getJoueur()->getAvancement()<GANON_CAPTURE)
            texte += "**NB : If we are not here, try the tavern."; break;
        case 228 :
            if (gpJeu->getJoueur()->getGemme(91)) {id=230; chercheText();break;}
            texte = "A power gem for 2 pearls?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_PERLES)<2) idsuiv=75;
            break;
        case 229 : texte = "A power gem for 2 pearls?**              yes              NO ?"; idsuiv=76; break;
        case 230 : 
            if (gpJeu->getJoueur()->getGemme(92)) {id=232; chercheText();break;}
            texte = "A power gem for 2 feathers?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_PLUME)<2) idsuiv=75;
            break;
        case 231 : texte = "A power gem for 2 feathers?**              yes              NO ?"; idsuiv=76; break;
        case 232 : 
            if (gpJeu->getJoueur()->getGemme(93)) {id=82; chercheText();break;}
            texte = "A power gem for 2 chickens?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<2) idsuiv=75;
            break;
        case 233 : texte = "A power gem for 2 chickens?**              yes              NO ?"; idsuiv=76; break;
        case 234 : 
            texte = "A chicken for 1 bag of rice and 2 bags of olives? *              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_OLIVES)<2
            || gpJeu->getJoueur()->getTroc(M_RIZ)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_POULET)>=99) idsuiv=95;
            break;
        case 235 : texte = "A chicken for 1 bag of rice and 2 bags of olives? *              yes              NO ?"; idsuiv=76; break;
        case 236 : texte = "Beyond Hyrule's South border, a gigantic ocean is said to stand..."; buffer="At the mating season the seagulls get over the cliff separating us from the seashore and come in the village."; break;
        case 237 : texte = "This village is under the protection of the Hylian Knights, you are safe here."; 
            if (gpJeu->getJoueur()->getAvancement()<GANON_CAPTURE) 
            buffer="Yet, since a tavern opened in the neighbouring town, we don't see our protectors around anymore..."; break;
        case 238 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>2) {id=245; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==2 
            && gpJeu->getJoueur()->getObjet()==7) {id=239; chercheText();break;}
            texte = "Not here either? But where did I lose it?"; break;
        case 239 : texte = "You have found my mother-in-law's vase??? *She makes me look for it everywhere for centuries! *Give it back right away!"; idsuiv=240; break;
        case 240 : texte = "This vase for a stuff I just found, ok?**              YES ?            no  "; idsuiv=242; break;
        case 241 : texte = "This vase for a stuff I just found, ok?**              yes              NO ?"; idsuiv=243; break;
        case 242 : texte = "Wise resolution kid."; break;
        case 243 : texte = "Kill him..."; break;
        case 244 : texte = "You traded the boot for a hammer!"; break;
        case 245 : texte = "You wanna enter my gang?**              YES ?            no  "; idsuiv=247; break;
        case 246 : texte = "You wanna enter my gang?**              yes              NO ?"; idsuiv=243; break;
        case 247 : texte = "Ha! Ha! Ha! *I was kidding! *Pathetic little fool! *Do you realize who you are dealing with?!"; break;
        case 248 : texte = "Temple of Wisdom**Only the wise ones will stay away from it."; break;
        case 249 : texte = "Boat rental shop"; break;
        case 250 : texte = "The boat shop is closed for today, I am about to win the fishing contest, I already have three differents!"; break;
        case 251 : 
            if (gpJeu->getJoueur()->hasObjet(O_PALMES)) {texte="Some monsters sinked my boat... *I'm sorry, but you will have to swim now....";break;}
            if (gpJeu->getJoueur()->hasObjet(O_BARQUE)) {id=253; chercheText();break;}
            texte = "Would you like to rent a boat for 15 rupees?**              YES ?            no  "; idsuiv=253;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            break;
        case 252 : texte = "Would you like to rent a boat for 15 rupees?**              yes              NO ?"; idsuiv=76; break;
        case 253 : texte = "You can use the boat at the pontoon, have fun, but don't go too far."; break;
        case 254 : texte = "(far away voice:) *I told you... DON'T GO TOO FAR!!!!"; break;
        case 255 : texte = "Abyss Cave**Thank you to don't come look for the descendant of the wisemen who is not hidding here."; break;
        case 256 : texte = "Blacksmith"; break;
        case 257 : texte = "Great Pyramid"; break;
        case 258 : texte = "HINT 1: The stone the most at the right is the second one. *HINT 2: The stones must all be removed by weight order."; break;
        case 259 : texte = "HINT 3: The tail's stones must be removed before the fin's one. *HINT 4: The eye's stone must be the fifth you remove."; break;
        case 260 : texte = "HINT 5: The water stones must be removed before the last one of the tail. *HINT 6: The eye's stone must be removed after the fin's one."; break;
        case 261 : texte = "HINT 7: The last stone is not the eye. *HINT 8: The 2 stones of the tail must not be removed one after the other."; break;
        case 262 : texte = "HINT 9: One of the nine hints is a fake."; break;
        case 263 : texte = "N : Rocky Mountains"; break;
        case 264 : texte = "Kakariko Village"; break;
        case 265 : 
            if (gpJeu->getJoueur()->hasObjet(O_BOTTES)) {id=82; chercheText();break;}
            texte = "The Pegasus boots for a tapestry and a perfume? *              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            break;
        case 266 : texte = "The Pegasus boots for a tapestry and a perfume? *              yes              NO ?"; idsuiv=76; break;
        case 267 : texte = "You got the Pegasus boots! *Hold R to run!"; break;
        case 268 : 
            texte = "A perfume for 3 feathers and 4 bags of rice? **              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_PLUME)<3
            || gpJeu->getJoueur()->getTroc(M_RIZ)<4) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PARFUM)>=99) idsuiv=95;
            break;
        case 269 : texte = "A perfume for 3 feathers and 4 bags of rice? **              yes              NO ?"; idsuiv=76; break;
        case 270 : texte = "You got a perfume!"; break;
        case 271 : 
            texte = "A bag of olives for 15 rupees?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_OLIVES)>=99) idsuiv=95;
            break;
        case 272 : texte = "A bag of olives for 15 rupees?**              yes              NO ?"; idsuiv=76; break;
        case 273 : 
            texte = "A jar of spices for 20 rupees?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_EPICES)>=99) idsuiv=95;
            break;
        case 274 : texte = "A jar of spices for 20 rupees?**              yes              NO ?"; idsuiv=76; break;
        case 275 : texte = "The Kakariko Village is a prerequisite for all adventurers willing to climb up the mountain. The less brave ones just reach the saloon..."; break;
        case 276 : texte = "Welcome in our village, Link! *Have fun, but don't go too close of the cactus..."; break;
        case 277 : texte = "The Pegasus boots make you going much much faster. It's a real advantage in a fight."; 
            if (gpJeu->getJoueur()->hasObjet(O_BOTTES)) buffer="You have these boots? *Then you must be pretty strong now..."; break;
        case 278 : 
            texte = "A frosty rock for a tapestry, an amulet and a perfume? *              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>=99) idsuiv=95;
            break;
        case 279 : texte = "A frosty rock for a tapestry, an amulet and a perfume? *              yes              NO ?"; idsuiv=76; break;
        case 280 : texte = "You got a frosty rock!"; break;
        case 281 : 
            texte = "A pearl for a jar of spices and a bag of rice? *              YES ?            no  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<1
            || gpJeu->getJoueur()->getTroc(M_RIZ)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 282 : texte = "A pearl for a jar of spices and a bag of rice? *              yes              NO ?"; idsuiv=76; break;
        case 283 : texte = "This village is under the protection of the 7 Wise Men. Because of their magic, you have to go pretty far before seeing a wolf..."; break;
        case 284 : texte = "You are here in the safer village you could find. Nothing to see withthe hamlet in the center doomed to disappear, or with the west village protected by alcoholics..."; break;
        case 285 : texte = "Temple of Time"; break;
        case 286 : texte = "Mine Entry"; break;
        case 287 : texte = "Temple of Power**Only for sturdy."; break;
        case 288 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>2) {id=295; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==2 
            && gpJeu->getJoueur()->getObjet()==11) {id=289; chercheText();break;}
            texte = "I isolated myself from the world to meditate on the meaning of life..."; buffer="...but I must admitt I miss some particular things..."; break;
        case 289 : texte = "Is this a bottle of wine you have??? *Give it to me! I will give you gold for it!!!"; idsuiv=290; break;
        case 290 : texte = "This bottle for gold, ok ?**              YES ?            no  "; idsuiv=292; break;
        case 291 : texte = "This bottle for gold, ok ?**              yes              NO ?"; idsuiv=293; break;
        case 292 : texte = "I feel I'm getting close of the truth!"; break;
        case 293 : texte = "...*I will have to meditate on the meaning of your refusal..."; break;
        case 294 : texte = "You traded the bottle for Gold Dust!"; break;
        case 295 : texte = "I finally found the meaning of life... -hiccup- !"; break;
        case 296 : texte = "Tower of Ice**The way will open when all the power gems are found."; break;
        case 297 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>1) {id=304; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==1 
            && gpJeu->getJoueur()->getObjet()==3) {id=298; chercheText();break;}
            texte = "From here I can admire the lake of lava... *In fact, I love all the red and shiny things."; break;
        case 298 : texte = "Mmm... it's an amazing gemstone you have here... *Would you give it to me for... a surprise?"; idsuiv=299; break;
        case 299 : texte = "This red gemstone for a surprise, ok?**              YES ?            no  "; idsuiv=301; break;
        case 300 : texte = "This red gemstone for a surprise, ok?**              yes              NO ?"; idsuiv=302; break;
        case 301 : texte = "Thank you! Here is your surprise! I tried to get ride of it for a looong time..."; break;
        case 302 : texte = "Too bad for you, no gemstone no surprise."; break;
        case 303 : texte = "You traded the red gemstone for an anvil! You can't run nor swim while you have it!"; break;
        case 304 : texte = "I feel like I have a great weight off me, and I'm wealthier too, so happy!"; break;
        case 305 : texte = "Temple of Fire"; break;
        case 306 : texte = "We are talking reindeers."; break;
        case 307 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>4) {id=314; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==4 
            && gpJeu->getJoueur()->getObjet()==7) {id=308; chercheText();break;}
            texte = "We ran aground here after crashing into a seagull... *It wouldn't have happened if I had have a horn..."; 
            buffer = "Oh, I almost forgot: *Ho! Ho! Ho!"; break;
        case 308 : texte = "Is this a bell here? It's giving me an idea... Would you give it to me? I don't have pony anymore, but I guess I can find something to thank you..."; idsuiv=309; break;
        case 309 : texte = "This little bell for a gift, ok?**              YES ?            no  "; idsuiv=311; break;
        case 310 : texte = "This little bell for a gift, ok?**              yes              NO ?"; idsuiv=312; break;
        case 311 : texte = "Thank you! Here is your gift: the axe I had to deliver to the local executioner. Happy ?"; break;
        case 312 : texte = "... *What is your name, naughty boy?*I strike you off my list."; break;
        case 313 : texte = "You traded the little bell for an axe!"; break;
        case 314 : texte = "Ho! Ho! Ho!"; buffer="That's all very well, but how do I go home?"; break;
        case 315 : texte = "TUTORIAL :*A hit on one of these colored sphere switch the stumbling blocks."; break;
        case 316 : texte = "You have found a sword!!!*Use it with the key B, or keep B holded to charge a spin attack!"; break;
        case 317 : texte = "TUTORIAL :*Falling in a hole will bring you at the floor below. However, if there is no floor below like here, a fall will make you lose life and will bring at the entry of the area, so be careful!"; break;
        case 318 : texte = "TUTORIAL :*During the game, you might see some spots apparently inaccessible, like the platform underneath. You will then have"; buffer="to come back later with more equipment to reach it."; break;
        case 319 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 320 : texte = "The guards saw you heading toward the forest, I thought you may have a lead so I ran up..."; break;
        case 321 : texte = "Mmm... This stele is written in ancient hylian... I will translate it:"; idsuiv=322; break;
        case 322 : texte = "At the dawn of cataclysm, shall the heroe find this stele. The Pendents of Courage, Wisdom and Power in his possession, his only chance to save the world will arise."; break;
        case 323 : texte = "..."; buffer="I'm afraid we'll have to forget about the ocarina for a moment...*If this stele says the truth, you have to gather the 3 pendents as soon as possible..."; idsuiv=324; break;
        case 324 : texte = "They are hidden in 3 temples, the nearest is a tower by the waterfalls, north of here... Take this map, it will help you find your way!"; break;
        case 325 : texte = "You got the map of Hyrule!**Press START outdoors to see it."; break;
        case 326 : 
            if (!gpJeu->getJoueur()->hasMedaillon(0)) {texte = "The first pendent is in a tower North of this forest. Leave the forest by the West and head North to arrive in the waterfalls area."; break;}
            if (!gpJeu->getJoueur()->hasMedaillon(1)) {texte = "The second pendent is in the temple in the middle of the Lake. You should rent a boat at the Mabe village..."; break;}
            if (!gpJeu->getJoueur()->hasMedaillon(2)) {texte = "The last pendent is in a temple surrounded by the mountains, North of the Kakariko Village."; break;}
            if (gpJeu->getJoueur()->getEpee()<2) {id=327; chercheText();break;}
            id=329; chercheText();break;
        case 327 : texte = "You've found all the pendents ?*Very well, we don't know what is going to happen, so take this sword with you."; break;
        case 328 : texte = "You got the Master Sword!!!*You will probably need its power!"; break;
        case 329 : 
            if (gpJeu->getJoueur()->getAvancement() == PORTAIL_F_OUVERT) {texte = "it looks like a teleportation portal, but... ...we have no information about where it goes..."; break;}
            texte = "Try to touch the stele, something will surely happen now that you've got the pendents..."; break;
        case 330 : texte = "One last thing:*Monsters are starting to appear everywhere in Hyrule... It's a very bad omen... Be careful."; break;
        case 331 : 
            texte = "Hello Link, I don't have many visitors these times...";
            if (gpJeu->getJoueur()->getBouclier()!=1) {idsuiv=333; break;}
            buffer="Let me improve your shield..."; break;
        case 332 : texte = "You got a better shield!!!*Your defense raises by one point!"; break;
        case 333 : texte = "Come back to see me if you are hurt, I would take care of your wounds."; break;
        case 334 : texte = "You got 10 bags of rice!"; break;
        case 335 : texte = "You got 10 jars of spices!"; break;
        case 336 : texte = "You got 10 bags of olives!"; break;
        case 337 : texte = "To reach the Pyramid, find and write down the 9 hints hidden on the desert's signs, the lift the whale's stones in the right order, and the way will open..."; break;
        case 338 :
            if (gpJeu->getJoueur()->getAvancement() < GARS_MINE_AIDE) {
                texte = "Cart express: I'm out for the moment, in case of emergency, I am at the saloon.** - The mine employee -"; break;}
            texte = "Cart express : service is provided again!"; break;
        case 339 : texte = "Jump on the cart and let me take care of the lever. *Don't worry, it's my job!"; break;
        case 340 : texte = "You have found some wooden planks!*You could use them to build a bridge..."; break;
        case 341 : texte = "Looks like a good place to build a bridge."; break;
        case 342 : texte = "                      Link*                 Heroe of Hyrule*               - Killed by Ganon -"; break;
        case 343 : texte = "We are all back together, we can open the portal..."; break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "Be sure to be ready, the ocarina's thief is probably a powerfull creature..."; break;}
            texte = "You took the ocarina back? Congratulations!"; break;
        case 345 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "This portal is very special, it leads to an exact place in the past... But we are not able to keep it opened forever, hurry up!"; break;}
            texte = "You got the ocarina? Then we completed the mission our ancestors entrusted us with..."; break;
        case 346 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "The portal is finally opened... Hurry Link, you've got to take the ocarina back!"; break;}
            texte = "The Ocarina of Time..."; buffer="Go to the Temple of Time, fulfil your destiny!"; break;
        case 347 : texte = "When we are all together with the key of Time, we'll open the portal..."; break;
        case 348 : texte = "You succeeded... We close the portal now..."; break;
        case 349 : texte = "You got a gauge!*...*Awesome..."; break;
        case 350 :
            if (gpJeu->getJoueur()->getBombeMax()<30 || gpJeu->getJoueur()->getFlecheMax()<70)
                {id=351; chercheText();break;}
            if (!gpJeu->getJoueur()->hasObjet(O_RECUP_FLECHE) 
            || !gpJeu->getJoueur()->hasObjet(O_RECUP_BOMBE))
                {id=356; chercheText();break;}
            texte = "Okay I have enough gold, go away."; break;
            break;
        case 351 : 
            texte = "Gimme 100 Gold Ganon right away if you want a reward, ok ?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100) idsuiv=75;
            break;
        case 352 : texte = "Gimme 100 Gold Ganon right away if you want a reward, ok ?*              yes              NO ?"; idsuiv=353; break;
        case 353 : texte = "You're making me lose my time, sheesh!"; break;
        case 354 : texte = "I will increase the number of arrows you can carry with you.*Say thank you !"; break;
        case 355 : texte = "I will increase the number of bombs you can carry with you.*I'm too kind with children..."; break;
        case 356 : 
            texte = "Give me 999 Gold Ganon if you want a four-star reward, ok?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<999) idsuiv=75;
            break;
        case 357 : texte = "Give me 999 Gold Ganon if you want a four-star reward, ok?*              yes              NO ?"; idsuiv=353; break;
        case 358 : texte = "Your account of arrows will now fill up permanently, don't hesitate to shoot anymore."; break;
        case 359 : texte = "Your bomb stock restores permanently now, you can blow up freely!"; break;
        case 360 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) {id=333; chercheText();break;}
            texte = "Welcome heroe, I will increase your Magic Meter, you may need it."; break;
        case 361 : texte = "Your stock of magic power doubled!"; break;
        case 362 : 
            if (gpJeu->getEpoque()==T_PASSE && !gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Do you want something to drink?"; break;
        case 363 : texte = "According to the gossips, a fairy would hide behind the waterfall...*Absolute poppycock..."; break;
        case 364 : texte = "I'm er... mounting guard in the bar, that's it.*But I would prefer this to be between you and me, ok?"; break;
        case 365 : texte = "Heroe of Hyrule or whatever, don't think you can drink for free."; break;
        case 366 : texte = "It's too risky for you to go in there, you could be seen."; break;
        case 367 : 
            if (gpJeu->getEpoque()==T_PASSE && !gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getZone()==84 && gpJeu->getJoueur()->getNbGemmes() == 200 
            && gpJeu->getJoueur()->getGemme() == 0) {id=405; chercheText(); break;}
            texte = "Choose what you want.*"; break;
        case 368 : texte = "10 arrows for 20 rupees?**              YES ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=75; break;
        case 369 : texte = "10 arrows for 20 rupees?**              yes              NO ?"; break;
        case 370 : texte = "5 bombs for 30 rupees?**              YES ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=75; break;
        case 371 : texte = "5 bombs for 30 rupees?**              yes              NO ?"; break;
        case 372 : texte = "You need a bag of bomb to buy this."; break;
        case 373 : texte = "You need a bow to buy this."; break;
        case 374 : texte = "You don't need this."; break;
        case 375 : texte = "Thank you."; break;
        case 376 : texte = "A heart for 5 rupees?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getVie() == gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=75; break;
        case 377 : texte = "A heart for 5 rupees?**              yes              NO ?"; break;
        case 378 : texte = "A little magic jar for 15 rupees?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75; break;
        case 379 : texte = "A little magic jar for 15 rupees?**              yes              NO ?"; break;
        case 380 : texte = "A big magic jar for 25 rupees?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=75; break;
        case 381 : texte = "A big magic jar for 25 rupees?**              yes              NO ?"; break;
        case 382 :
            if (gpJeu->getJoueur()->getAvancement()<APPREND_POUR_ROC_GIVRE) {texte = "I've just arrived in the city, I'm not open yet, come back later."; break;}
            if (gpJeu->getJoueur()->getAvancement()==APPREND_POUR_ROC_GIVRE 
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)==-1) {
                texte = "If I have a frosty rock?*Yes, that's right."; idsuiv=383; break;
            }
            texte = "I thought no one had power gems, so I wasn't sure whether to open my shop or not, but you helped me decide.";
            buffer = "At your next visit I will be open, you will be able to buy extremly rare items for power gems.";
            break;
        case 383 : texte = "I let you have it for 30 power gems, ok?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getGemme()<30) idsuiv=385; break;
        case 384 : texte = "I let you have it for 30 power gems, ok?**              yes              NO ?"; idsuiv=76; break;
        case 385 : texte = "You don't have enough gems.*Look better, they can be found anywhere."; break;
        case 386 : texte = "This detector will help you know whether you have all the power gems in the area you are or not. An essential tool for someone looking for all the gems, it's yours for 20 power gems!"; idsuiv=387; break;
        case 387 : texte = "The detector for 20 power gems, ok?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 388 : texte = "The detector for 20 power gems, ok?**              yes              NO ?"; break;
        case 389 : texte = "You got the detector!*When you press L and START, the number of gems in you possession is written in green if you have all the gems of the area."; break;
        case 390 : 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=393; chercheText(); break;}
            texte = "An empty bottle for 10 power gems?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getGemme()<10) idsuiv=385; break;
        case 391 : texte = "An empty bottle for 10 power gems?**              yes              NO ?"; break;
        case 392 : texte = "You got a bottle!*You can fill it with potions!"; break;
        case 393 : texte = "An empty bottle for 20 power gems?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 394 : texte = "An empty bottle for 20 power gems?**              yes              NO ?"; break;
        case 395 : 
            if (gpJeu->getJoueur()->hasObjet(O_BONUS_FORCE)==1) {id=398; chercheText(); break;}
            texte = "An improvment of your strength for 20 power gems? *              YES ?            no  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 396 : texte = "An improvment of your strength for 20 power gems? *              yes              NO ?"; break;
        case 397 : texte = "Your strength increases by one point!"; break; 
        case 398 : 
            texte = "An improvment of your strength for 40 power gems? *              YES ?            no  ";
            if (gpJeu->getJoueur()->getGemme()<40) idsuiv=385; break;
        case 399 : texte = "An improvment of your strength for 40 power gems? *              yes              NO ?"; break;
        case 400 : 
            if (gpJeu->getJoueur()->hasObjet(O_BONUS_DEFENSE)==1) {id=403; chercheText(); break;}
            texte = "An improvment of your defense for 20 power gems? *              YES ?            no  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 401 : texte = "An improvment of your defense for 20 power gems? *              yes              NO ?"; break;
        case 402 : texte = "Your defense increases by one point!"; break; 
        case 403 : 
            texte = "An improvment of your defense for 40 power gems? *              YES ?            no  ";
            if (gpJeu->getJoueur()->getGemme()<40) idsuiv=385; break;
        case 404 : texte = "An improvment of your defense for 40 power gems? *              yes              NO ?"; break;
        case 405 : texte = "Mmm... my stock is empty..."; idsuiv=406; break;
        case 406 : texte = "I guess you've found all the power gems, it's incredible..."; idsuiv=407; break;
        case 407 : texte = "According to an old legend, when all the power gems are found, a temple hidding a fabulous treasure will open...*We just have to wait..."; break;
        case 408 : texte = "Come back when you have an empty bottle and I will sell you my potions."; break;
        case 409 :
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Red potions restore your energy and green potions restore your magic."; 
            idsuiv=410; break;
        case 410 : texte = "Which one would you like?*                ?  RED POTION  ?*                  green potion  *                     no one    "; idsuiv=413; break;
        case 411 : texte = "Which one would you like?*                   red potion   *                ? GREEN POTION ?*                     no one    "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=415; break;
        case 412 : texte = "Which one would you like?*                   red potion   *                  green potion  *                ?    NO ONE    ?"; break;
        case 413 : texte = "A red potion for 60 rupees?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=75; break;
        case 414 : texte = "A red potion for 60 rupees?**              yes              NO ?"; break;
        case 415 : texte = "A green potion for 40 rupees?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=75; break;
        case 416 : texte = "A green potion for 40 rupees?**              yes              NO ?"; break;
        case 417 : texte = "You got a red potion!!!**Drink it to restore all your energy!!!"; break;
        case 418 : texte = "You got a green potion!!!**Drink it to restore all your magic!!!"; break;
        case 419 : texte = "You got a blue potion!!!**Drink it to restore your energy and your magic!!!"; break;
        case 420 : texte = "You don't need to drink this potion now."; break;
        case 421 : texte = "                 Already tired?                  ?                 CONTINUE                 ?                   Save and quit                               Quit without saving            "; break;
        case 422 : texte = "                 Already tired?                                    Continue                     ?               SAVE AND QUIT              ?                Quit without saving            "; break;
        case 423 : texte = "                 Already tired?                                    Continue                                     Save and quit                  ?            QUIT WITHOUT SAVING           ?"; break;
        case 424 : 
            if (gpJeu->getJoueur()->getCoffre(15,14)) {id=431; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==3 
            && gpJeu->getJoueur()->getObjet()==3) {id=425; chercheText();break;}
            texte = "I am the unluckiest man of the country, nothing good ever happen to me..."; break;
        case 425 : texte = "Is this a lucky charm you have?*Give it to me!*Nobody in the world need it more than me!"; idsuiv=426; break;
        case 426 : texte = "This horseshoe for... nothing, ok?**              YES ?            no  "; idsuiv=428; break;
        case 427 : texte = "This horseshoe for... nothing, ok?**              yes              NO ?"; idsuiv=429; break;
        case 428 : texte = "Thank you so much! Maybe I will be lucky now!"; 
            buffer = "I'm sorry my friend, but I have nothing to give you in return, unlucky for you."; break;
        case 429 : texte = "... *How unlucky I am..."; break;
        case 430 : texte = "You traded the horseshoe for... his gratitude?"; break;
        case 431 : texte = "In the end I'm a lucky devil."; break;
        case 432 : texte = "I don't have price to put in game anymore, sorry."; break;
        case 433 : 
            tmp = 4-(gpJeu->getJoueur()->getCoeur(28) + gpJeu->getJoueur()->getGemme(160) 
            + gpJeu->getJoueur()->getGemme(161) + gpJeu->getJoueur()->getGemme(162));
            if (tmp==0) {id=432; chercheText();break;}
            os << tmp; os2 << ((4-tmp+1)*5);
            texte = "There are "+os.str()+" prices in these 9 chests, do you want to try your luck for "+os2.str()+" rupees ?*You can open only one chest, ok?*              YES ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<(4-tmp+1)*5) idsuiv=75; break;
        case 434 : 
            tmp = 4-(gpJeu->getJoueur()->getCoeur(28) + gpJeu->getJoueur()->getGemme(160) 
            + gpJeu->getJoueur()->getGemme(161) + gpJeu->getJoueur()->getGemme(162));
            os << tmp; os2 << ((4-tmp+1)*5);
            texte = "There are "+os.str()+" prices in these 9 chests, do you want to try your luck for "+os2.str()+" rupees ?*You can open only one chest, ok?*              yes              NO ?"; break;
        case 435 : texte = "Choose a chest."; break;
        case 436 : texte = "Hey! You gotta pay to open one of my chests!!!"; break;
        case 437 : texte = "You lose! This chest is empty."; break;
        case 438 :
            if (gpJeu->getJoueur()->hasObjet(O_SAC_TROC)) {id=444; chercheText();break;}
            texte = "Good morning Link, you want to cross the bridge to go to the temple?"; idsuiv=439;
            break;
        case 439 : texte = "Usually I would just have to turn this lever, but I played with it all last night and well... it brokes."; 
            buffer="I even tought about putting wooden planks to allow the path, but someone stole them during the night..."; idsuiv=440; break;
        case 440 : texte = "I could fix the lever, but I need a replacement part, and I can't leave my post..."; idsuiv=441; break;
        case 441 : texte = "I need a cogwheel, they can be found at the marketplace of Hyrule City."; idsuiv=442; break;
        case 442 : texte = "You know how it works, don't you? Each stallholder offers some products for others, you've got to gather what they want in order to get what you want."; idsuiv=443; break;
        case 443 : texte = "I will give you the merchandises I already have.*If you want to see what you have in you bag, press L and B (Press L and B again to change list)."; break;
        case 444 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)==0) {id=446; chercheText();break;}
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)>0) {id=445; chercheText();break;}
            texte = "I need a cogwheel to fix that lever.*Go find one at the marketplace of Hyrule city if you want to cross the bridge."; break;
        case 445 : texte = "You brought me a cogwheel?*Very well, now it should work."; break;
        case 446 : texte = "The lever is broken again...*At least now the bridge is out...*It will teach me to build exotic bridge"; break;
        case 447 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "A blue potion for 160 rupees?*You will like it...*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=75; break;
        case 448 : texte = "A blue potion for 160 rupees?*You will like it...*              yes              NO ?"; break;
        case 449 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>1) {id=456; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==1 
            && gpJeu->getJoueur()->getObjet()==15) {id=450; chercheText();break;}
            texte = "I'm fond of every thing green and shiny!"; 
            buffer = "Don't worry, I'm not going to steal your rupees... *I'm trying to quit."; break;
        case 450 : texte = "It's really beautiful what you have here... *Love it!*I trade it for a chart of an... INESTIMABLE value!"; idsuiv=451; break;
        case 451 : texte = "This green gemstone for a map, ok?**              YES ?            no  "; idsuiv=453; break;
        case 452 : texte = "This green gemstone for a map, ok?**              yes              NO ?"; idsuiv=454; break;
        case 453 : texte = "Thank youuuu!!! Here is your chart, now get lost!"; break;
        case 454 : texte = "Very well... *Watch out for your rupees then!"; break;
        case 455 : texte = "You traded the gemstone for a map!"; break;
        case 456 : texte = "You came to give me some rupees?*How nice of you!"; break;
        case 457 : texte = "The princess wants me to warn her if anything strange happen on the town..."; 
            buffer = "This morning I saw a seagull flying strangely... I'm not sure whether I've got to tell her or not..."; break;
        case 458 :
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)) {id=478; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() == PARLE_PECHE) {id=460; chercheText();break;}
            gpJeu->getJoueur()->setAvancement(PARLE_PECHE);
            texte = "Hello Link, welcome at the fishing stand!"; idsuiv = 459; break;
        case 459 : texte = "To unveil the opening of my stand, I'm organizing a great fishing contest!*You've probably heard about it, all the city participates!"; idsuiv=460; break;
        case 460 : texte = "To win the contest and the special price, you've got to be the first one to hook 5 different types of fish."; idsuiv=461; break;
        case 461 : texte = "Do you want to try? The registration fee is 10 Rupees, ok?*              YES ?            no  "; idsuiv=463;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=75; break;
        case 462 : texte = "Do you want to try? The registration fee is 10 Rupees, ok?*              yes              NO ?"; idsuiv=464; break;
        case 463 : texte = "Excellent, here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 464 : 
            texte = "Mmm... Do you want to participate for 5 Rupees? *              YES ?            no  "; idsuiv=466; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=75; break;
        case 465 : texte = "Mmm... Do you want to participate for 5 Rupees? *              yes              NO ?"; idsuiv=467; break;
        case 466 : texte = "Very well, here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 467 : texte = "And for 2 Rupees?**              YES ?            no  "; idsuiv=469;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<2) idsuiv=75; break;
        case 468 : texte = "And for 2 Rupees?**              yes              NO ?"; idsuiv=470; break;
        case 469 : texte = "Well, here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 470 : texte = "For 1 Rupees ?**              YES ?            no  "; idsuiv=472;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<1) idsuiv=75; break;
        case 471 : texte = "For 1 Rupees ?**              yes              NO ?"; idsuiv=473; break;
        case 472 : texte = "Ok, here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 473 : texte = "Don't tell me you want to participate for free???*               YEAH ?          no  "; idsuiv=475; break;
        case 474 : texte = "Don't tell me you want to participate for free???*               yeah            NO ?"; idsuiv=476; break;
        case 475 : texte = "...*Here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 476 : texte = "Go away, enemy of fishermen!"; break;
        case 477 : texte = "You got a fishing rod!*Use it on a pontoon, then bring the fish up pressing Y when the line is moving."; break;
        case 478 : 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) {id=487; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=5) {id=479; chercheText();break;}
            tmp = 5-gpJeu->getJoueur()->nbPoissons();
            os << tmp;
            if (tmp > 1) texte = "Still "+os.str()+" different fish to find, good luck!";
            else texte = "Just one more fish to find!"; break;
        case 479 : texte = "You have found 5 fish???*You must be super-fisherman!"; idsuiv=480; break;
        case 480 : texte = "This means the fishing contest is over, and you are the winner!"; idsuiv=481; break;
        case 481 : texte = "I guess you want your price now...*Well, as a reward for your victory in the fishing contest: *... ... ..."; idsuiv=482; break;
        case 482 : texte = "I hire you!"; idsuiv=483; break;
        case 483 : texte = "There are a lot of other types of fish in Hyrule, I want to list them all by area."; idsuiv=484; break;
        case 484 : texte = "I will reward you each time you bring me 5 new types of fish.*From now on you can consult the list pressing L and B (Press L and B again to change list)."; idsuiv=485; break;
        case 485 : texte = "With your current fishing rod, you will unfortunately be able to catch only little fish..."; break;
        case 486 : texte = "Be sure to go fishing every where!*Each fish caught give you some energy, did you notice?"; break;
        case 487 :
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>1) {id=490; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=10) {id=488; chercheText();break;}
            tmp = 10-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Bring me "+os.str()+" new types of fish for the next reward!";
            break;
        case 488 : texte = "Here is your reward for the 10 different types of fish you found:"; break;
        case 489 : texte = "You got a better fishing rod!!!*You'll be able to catch fish of regular size."; break;
        case 490 : 
            if (gpJeu->getJoueur()->hasBouteille(2)) {id=492; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=15) {id=491; chercheText();break;}
            tmp = 15-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Bring me "+os.str()+" new types of fish for the next reward!";
            break;
        case 491 : texte = "Here is your reward for the 15 different types of fish you found:"; break;
        case 492 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>2) {id=495; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=20) {id=493; chercheText();break;}
            tmp = 20-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Bring me "+os.str()+" new types of fish for the next reward!";
            break;
        case 493 : texte = "Here is your reward for the 20 different types of fish you found:"; break;
        case 494 : texte = "You got the better fishing rod!!!*You will be able to catch gigantic fish!"; break;
        case 495 : 
            if (gpJeu->getJoueur()->getCoeur(27)) {id=497; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=25) {id=496; chercheText();break;}
            tmp = 25-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Bring me "+os.str()+" new types of fish for the next reward!";
            break;
        case 496 : texte = "Here is your reward for the 25 different types of fish you found:"; break;
        case 497 : 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)>1) {id=500; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=30) {id=498; chercheText();break;}
            tmp = 30-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Bring me "+os.str()+" new types of fish for the next reward!";
            break;
        case 498 : texte = "Here is your reward for having found all the different types of fish in Hyrule:"; break;
        case 499 : texte = "YOU ARE FIRED!!!!"; break;
        case 500 : texte = "Finally, all the fish existing in Hyrule are listed, my fisherman guidebook is finished..."; break;
        case 501 : texte = "Good morning Link.*I am the mayor, welcome in the Mabe Village."; 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) idsuiv=503; else idsuiv=502; break;
        case 502 : texte = "At this time a fishing contest is organized on the town, everybody speaks about nothing but this... *Is that why you came?"; break;
        case 503 : texte = "The fishing contest being over, Mabe Village returns to its usual calmness."; break;
        case 504 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>1) {id=511; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==1 
            && gpJeu->getJoueur()->getObjet()==7) {id=505; chercheText();break;}
            texte = "I am the legendary fisherman!*I like the blue and shiny of the ocean..."; 
            buffer = "Why I didn't win the fishing contest?*Well... I'm not interested in that kind of thing.... That's why."; break;
        case 505 : texte = "A blue and shiny gemstone?*I need it!*I trade it for the last thing I hooked!"; idsuiv=506; break;
        case 506 : texte = "The blue gemstone for his fishing, ok ?**              YES ?            no  "; idsuiv=508; break;
        case 507 : texte = "The blue gemstone for his fishing, ok ?**              yes              NO ?"; idsuiv=509; break;
        case 508 : texte = "He-he! You drive a bargain kid."; buffer="This boot was full of wales when I found it, unusual isn't it?"; break;
        case 509 : texte = "You are too nice, but don't worry about me, don't be afraid of defrauding me."; break;
        case 510 : texte = "You traded the blue gemstone for an old boot!*Way to go..."; break;
        case 511 : texte = "If you ever find new blue gemstones, it will be a pleasure to do a deal with you!"; break;
        case 512 : 
            if (!gpJeu->getJoueur()->hasObjet(O_CANNE)) texte = "These days, young men never listen to their elder's advice...*I think this fishing contest will last...";
            else {texte = "Formerly I was a famous fisherman, do you want me to give you some hints?"; idsuiv=513;} break;
        case 513 : texte = "ABOUT THE TYPES OF FISH          ?*About the areas of fishing        *About the bonus                   *Nothing at all                    "; idsuiv=517; break;
        case 514 : texte = "About the types of fish           *ABOUT THE AREAS OF FISHING       ?*About the bonus                   *Nothing at all                    "; idsuiv=518; break;
        case 515 : texte = "About the types of fish           *About the areas of fishing        *ABOUT THE BOUNS                  ?*Nothing at all                    "; idsuiv=519; break;
        case 516 : texte = "About the types of fish           *About the areas of fishing        *About the bonus                   *NOTHING AT ALL                   ?"; idsuiv=520; break;
        case 517 : texte = "They say that waters in Hyrule provide a habitat for no less than 30 types of fish, but they all have their own area, you will not find them all at the same place."; break;
        case 518 : texte = "There are in Hyrule a lot of spot to fish, but only 6 distinct areas. To find new fish you will have to go fishing in other places."; 
            buffer="If you find a fish already hooked somewhere else, this means you are in the same fishing area."; break;
        case 519 : texte = "Fishing is not only for fun, a fish hooked will give you energy. The quantity of life earned depends of the fish."; break;
        case 520 : texte = "Tsss... youth these days..."; break;
        case 521 : 
            if (!gpJeu->getJoueur()->hasObjet(O_POISSONS)) texte = "I spent hours fishing in the lake and could only find 3 different types of fish..."; 
            else texte = "We had to go fishing at different places to find more than 3 fish?*If I had known..."; break;
        case 522 :
            if (gpJeu->getJoueur()->getAvancement()==PARLE_GARS_MINE_SALOON) {id=523; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_BARMAN_SALOON
            && gpJeu->getJoueur()->getAvancement()<DETTE_PAYEE) {id=528; chercheText();break;}
            texte = "Do you want something to drink?"; break;
        case 523 : texte = "You need help from the drunk guy there? *Unfortunately for you I can't let him go if he doesn't pay."; idsuiv=524; break;
        case 524 : texte = "You want to pay it off? It's 10 000 Rupees, ok? *              YES ?            no  "; idsuiv=75; break;
        case 525 : texte = "You want to pay it off? It's 10 000 Rupees, ok? *              yes              NO ?"; idsuiv=526; break;
        case 526 : texte = "Of course..."; buffer="Okay, I got another idea: usually I use a frosty rock to prepare my fresh drinks, but I just finished the last one I heritated from my ancestors..."; idsuiv=527; break;
        case 527 : texte = "If you bring me a new frosty rock, I will consider his debt payed."; break;
        case 528 : 
            if (gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>0) {id=529; chercheText();break;}
            texte = "So, you can't find a frosty rock?"; break;
        case 529 : texte = "You got a frosty rock? Impressive..."; idsuiv=530; break;
        case 530 : texte = "You give me this frosty rock and I'll forget his debt, ok?*              YES ?            no  "; idsuiv=533; break;
        case 531 : texte = "You give me this frosty rock and I'll forget his debt, ok?*              yes              NO ?"; idsuiv=532; break;
        case 532 : texte = "I understand, after all it's nothing of your business."; break;
        case 533 : texte = "Thank you!*As promised, the old man can go, he doesn't owe me anything more."; break;
        case 534 : 
            if (gpJeu->getJoueur()->getAvancement()==PANCARTE_MINE_LUE) {id=535; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==PARLE_GARS_MINE_SALOON) {id=537; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==PARLE_BARMAN_SALOON) {id=538; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>PARLE_BARMAN_SALOON
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<0) {id=540; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()<DETTE_PAYEE
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>0) {id=541; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==DETTE_PAYEE) {id=542; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==GARS_MINE_AIDE) {id=543; chercheText();break;}
            texte = "Let me drink alone! -hiccups- !"; break;
        case 535 : texte = "You went to the mine?*I used to work there...*But because monsters appeared in, the mine is temporarly closed..."; idsuiv=536; break;
        case 536 : texte = "I would like to help you cross the mine, but the barman doesn't want to let me go if I don't pay. Yet I don't have money anymore, so I can't leave, and I drink to spend the time."; idsuiv=537; break;
        case 537 : texte = "Someone should really pay off my debt for me... ...* -hiccup- !"; break;
        case 538 : texte = "You want to know where to find a frosty rock? *Mmm... I heard that a guy arrived in Hyrule City lately, and he is about to open a shop of a new kind..."; idsuiv=539; break;
        case 539 : texte = "Well, I think this guy has got a frosty rock."; break;
        case 540 : texte = "Go and see the guy in the strange shop at Hyrule City, he should have a frosty rock."; break;
        case 541 : texte = "You got a frosty rock???*Give it to the barman, I promise I will help you with the mine!"; break;
        case 542 : texte = "I'm free now... I tought I would have to do the dishes for the rest of the week!*Thank you Link!"; idsuiv=543; break;
        case 543 : texte = "You can go to the mine, I'll meet you there.** -hiccup- !"; break;
        case 544 : texte = "Welcome in the saloon, make yourself at home Link!"; break;
        case 545 : texte = "While the mine up north is closed, I don't have anything to do but spending my time here..."; break;
        case 546 : texte = "Almost all the men in the village work in the mine north of the village."; buffer="This morning monsters appeared inside so the mine had to close."; break;
        case 547 : texte = "Rice, spices and olives are the basis of the barter in Hyrule, you should always have some with you."; break;
        case 548 : texte = "I am the head of the mine, and the most powerful man in the village, so don't try to look down upon me, boy."; break;
        case 549 : texte = "I am the chief of the village... But actually the chief of the mine is much more influent than me, he hired almost all the village's men."; break;
        case 550 : texte = "The bank is under our surveillance. Nothing to report."; break;
        case 551 : 
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())==0) idsuiv=552;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>0) idsuiv=553;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())==0) idsuiv=559;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>0) idsuiv=564;
            texte = "Welcome in the Hyrule bank. I am specialized in currencies."; break;
        case 552 : texte = "You have nothing interesting, come back if you find gold, I'll give you a good price for it."; break;
        case 553 : texte = "You have some gold coins? With the face of a monster on it... Gold Ganon you say?"; idsuiv=554; break;
        case 554 : texte = "It's really ugly, but the gold is reusable, let's see..."; idsuiv=555; break;
        case 555 : 
            int g;
            int gmax;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()>gpJeu->getJoueur()->getRubisMax()-2) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Gold Ganon for "+os2.str()+" Rupees, ok?**              YES ?            no  "; idsuiv=558; break;
        case 556 : 
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Gold Ganon for "+os2.str()+" Rupees, ok?**              yes              NO ?"; idsuiv=76; break;
        case 557 : texte = "Your wallet is full, come back later, I'll buy all that off you."; break;
        case 558 : texte = "It's a deal!"; break;
        case 559 : texte = "You have Gold Coins? I tought this currency didn't exist anymore..."; idsuiv=560; break;
        case 560 : texte = "I'll give you a good price, let's see..."; idsuiv=561; break;
        case 561 : 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()>gpJeu->getJoueur()->getRubisMax()-4) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*4);
            texte = os.str()+" Gold Coins for "+os2.str()+" Rupees, ok?**              YES ?            no  "; idsuiv=563; break;
        case 562 : 
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*4);
            texte = os.str()+" Gold Coins for "+os2.str()+" Rupees, ok?**              yes              NO ?"; idsuiv=76; break;
        case 563 : texte = "It's a deal!"; break;
        case 564 : texte = "What do you want to sell me?*   - GOLD COINS ?*   - Gold Ganon  *   - Nothing  "; idsuiv=560; break;
        case 565 : texte = "What do you want to sell me?*   - Gold Coins  *   - GOLD GANON ?*   - Nothing  "; idsuiv=554; break;
        case 566 : texte = "What do you want to sell me?*   - Gold Coins  *   - Gold Ganon  *   - NOTHING ?"; idsuiv=76; break;
        case 567 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC2)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC3)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC4)==10) {id=574; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==7 
            && gpJeu->getJoueur()->getObjet()==3) {id=568; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==7 
            && gpJeu->getJoueur()->getObjet()==7) {id=575; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==8 
            && gpJeu->getJoueur()->getObjet()==11) {id=580; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==7 
            && gpJeu->getJoueur()->getObjet()==15) {id=585; chercheText();break;}
            texte = "I'm here to build a bridge northerly. I'm sure it would be useful some day."; 
            buffer = "The problem is... I don't have tools...*What should I do?"; break;
        case 568 : texte = "This hammer looks good...*It could really help me, will you give it to me for a legendary treasure I found when i was an explorer?"; idsuiv=569; break;
        case 569 : texte = "This hammer for a legendary treasure, ok?**              YES ?            no  "; idsuiv=571; break;
        case 570 : texte = "This hammer for a legendary treasure, ok?**              yes              NO ?"; idsuiv=572; break;
        case 571 : texte = "Thank you, you can have this:"; break;
        case 572 : texte = "I think I'll never finish this bridge..."; break;
        case 573 : texte = "You got the Fire Arrows!*These burning arrows use magic and release an incredible power!"; break;
        case 574 : texte = "Looks like I finally got all I need...*I get myself motivated, and I do it!"; break;
        case 575 : texte = "Is that a bridge plan?*I really need that, will you give it to me for a legendary treasure I found when I was an explorer?"; idsuiv=576; break;
        case 576 : texte = "This plan for a legendary treasure, ok?**              YES ?            no  "; idsuiv=578; break;
        case 577 : texte = "This plan for a legendary treasure, ok?**              yes              NO ?"; idsuiv=572; break;
        case 578 : texte = "Thank you, take this gift in return:"; break;
        case 579 : texte = "You got the Ice Arrows!*These freezing arrows use magic and release an incredible power!"; break;
        case 580 : texte = "You've got a saw?*I can't make a bridge without it, will you give it to me for a legendary treasure I found when I was an explorer?"; idsuiv=581; break;
        case 581 : texte = "This saw for a legendary treasure, ok?**              YES ?            no  "; idsuiv=583; break;
        case 582 : texte = "This saw for a legendary treasure, ok?**              yes              NO ?"; idsuiv=572; break;
        case 583 : texte = "Thank you, take this in exchange:"; break;
        case 584 : texte = "You got the Light Arrows!*These arrows use a lot of magic and release an ultimate power!"; break;
        case 585 : texte = "You've got a nail?*I guess it may help, will you give it to me for a bauble?"; idsuiv=586; break;
        case 586 : texte = "This nail for a bauble, ok?**              YES ?            no  "; idsuiv=588; break;
        case 587 : texte = "This nail for a bauble, ok?**              yes              NO ?"; idsuiv=572; break;
        case 588 : texte = "Thank you, I give you that in return:"; break;
        case 589 : 
            if (gpJeu->getJoueur()->hasObjet(O_ENCYCL)) {id=593; chercheText();break;}
            texte = "Hello Link, do you remember me?"; idsuiv=590; break;
        case 590 : texte = "Monsters appeared in Hyrule today, so once again I'll try to list them all, and once again I count on your help."; idsuiv=591; break;
        case 591 : texte = "Pressing L and B, you can see the monsters already listed (Press L and B again to change list). You just have to kill a monster to add it."; idsuiv=592; break;
        case 592 : 
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<"10 Gold Coins"; break;
                case T_PRESENT : os<<"40 Rupees"; break;
                case T_FUTUR : os<<"20 Gold Ganon"; break;
            }
            texte = "I'll owe you "+os.str()+" for each new monster. Come and see me when you have some time to get your money."; break;
        case 593 :
            g = gpJeu->getJoueur()->getSolde();
            if (g == 0) {id=595; chercheText();break;}
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(g/4)<<" Gold Coins"; break;
                case T_PRESENT : os<<g<<" Rupees"; break;
                case T_FUTUR : os<<(g/2)<<" Gold Ganon"; break;
            }
            texte = "I owe you "+os.str()+", do you want to be paid now?*              YES ?            no  "; break;
        case 594 : 
            g = gpJeu->getJoueur()->getSolde();
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(g/4)<<" Gold Coins"; break;
                case T_PRESENT : os<<g<<" Rupees"; break;
                case T_FUTUR : os<<(g/2)<<" Gold Ganon"; break;
            }
            texte = "I owe you "+os.str()+", do you want to be paid now?*              yes              NO ?"; break;
        case 595 : texte="Your account is at 0, I gave you everything."; break;
        case 596 : 
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<2) idsuiv=597;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>1) idsuiv=598;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<2) idsuiv=603;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>1) idsuiv=608;
            texte = "Welcome in the Hyrule Bank. I am specialized in currencies."; break;
        case 597 : texte = "You don't have anything interesting, come back if you find some gold or rupees, I'll give you a good price."; break;
        case 598 : texte = "You have some rupees? We haven't used them for ages, but they are still very valuable..."; idsuiv=599; break;
        case 599 : texte = "Let's see..."; idsuiv=600; break;
        case 600 : 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()==gpJeu->getJoueur()->getGanonMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Rupees for "+os2.str()+" Gold Ganon, ok?**              YES ?            no  "; idsuiv=602; break;
        case 601 : 
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Rupees for "+os2.str()+" Gold Ganon, ok?**              yes              NO ?"; idsuiv=76; break;
        case 602 : texte = "It's a deal!"; break;
        case 603 : texte = "You possess Gold Coins? It's unbelievable that you could find such an ancient money!"; idsuiv=604; break;
        case 604 : texte = "They contain a lot of gold... *Let's see..."; idsuiv=605; break;
        case 605 : 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()>gpJeu->getJoueur()->getGanonMax()-2) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Gold Coins for "+os2.str()+" Gold Ganon, ok?**              YES ?            no  "; idsuiv=607; break;
        case 606 : 
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Gold Coins for "+os2.str()+" Gold Ganon, ok?**              yes              NO ?"; idsuiv=76; break;
        case 607 : texte = "It's a deal!"; break;
        case 608 : texte = "What do you want to sell me?*   - GOLD COINS ?*   - Rupees  *   - Nothing  "; idsuiv=604; break;
        case 609 : texte = "What do you want to sell me?*   - Gold Coins  *   - RUPEES ?*   - Nothing  "; idsuiv=599; break;
        case 610 : texte = "What do you want to sell me?*   - Gold Coins  *   - Rupees  *   - NOTHING ?"; idsuiv=76; break;
        case 611 : texte = "It's been a long time since I had so much fun!"; break;
        case 612 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>6) {id=619; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==6 
            && gpJeu->getJoueur()->getObjet()==7) {id=613; chercheText();break;}
            texte = "One of my ancestors wanted to build a bridge, but in the end he just made the plan..."; 
            buffer = "I'm from a lineage of incapables, no wonder I suck in every thing I do... On top of that I'm sick, and no one loves me..."; break;
        case 613 : texte = "You have a rope?*Give it to me please, I will give you the heritage of my family, I don't have any descendants anyway..."; idsuiv=614; break;
        case 614 : texte = "This rope for his heritage, ok?**              YES ?            no  "; idsuiv=616; break;
        case 615 : texte = "This rope for his heritage, ok?**              yes              NO ?"; idsuiv=617; break;
        case 616 : texte = "Well...*...Thank you man...*..."; break;
        case 617 : texte = "I knew that, nobody have never given anything anyway..."; break;
        case 618 : texte = "You traded the rope for a bridge's plan."; break;
        case 619 : texte = "...*I would like to be alone just a moment..."; break;
        case 620 : 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {id=624; chercheText();break;}
            texte = "Good day, you must be Link, I was waiting for you."; idsuiv=621; break;
        case 621 : texte = "I'm a descendant of the 7 Wise Men. Chased by Ganon's minions, I had to run away and hide here."; idsuiv=622; break;
        case 622 : texte = "Seeing you here brings hope, I will go in the portal's cave.*Take this, I think it might help you."; break;
        case 623 : texte = "You got a pepper!"; break;
        case 624 : texte = "Good luck Link!"; break;
        case 625 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=635; chercheText();break;}
            texte = "Welcome Link, I was waiting for you..."; idsuiv=626; break;
        case 626 : texte = "I guess you have a lot of questions, allow me to answer you."; idsuiv=627; break;
        case 627 : texte = "We are in Hyrule, but in a time that is nothing for you but a sad future...*The portal you took allowed you to come here and now, to be the witness of these sad days..."; idsuiv=628; break;
        case 628 : texte = "You want to know what happened? Ganon attacked the castle, stronger than ever, and you were defeated."; idsuiv=629; break;
        case 629 : texte = "Before her execution, princess Zelda managed to send her plan to the wise men. She thought the theft of the Ocarina was the turning point of the war, so she ordered that the descendants of the 7 wise men give you the Ocarina back whenever you would arrive by the portal."; idsuiv=630; break;
        case 630 : texte = "Since you are here, in front of me, this means the day has finally arrived.*However... the ocarina was never found."; idsuiv=631; break;
        case 631 : texte = "So we drew up another plan. We are going to send you in the past, the night when the ocarina was stolen, and you will catch the thief red-handed."; idsuiv=632; break;
        case 632 : texte = "Now, we are only 3 descendants remaining, search and find the two others as well as the Key of Time, and we'll open the portal."; idsuiv=633; break;
        case 633 : texte = "Take this, it will help you in your researches:"; break;
        case 634 : texte = "You got the hookshot!*Use it to jump over ditches!"; break;
        case 635 : 
            if (gpJeu->getJoueur()->getCoffre(3,29)) {id=636; chercheText();break;}
            texte = "One of them is hidden in a temple, in the middle of the lake."; break;
        case 636 : 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {id=637; chercheText();break;}
            texte = "The last wise man is hidden nearby the waterfalls."; break;
        case 637 : 
            if (gpJeu->getJoueur()->hasObjet(O_CLE_TEMPS)) {id=638; chercheText();break;}
            texte = "The key of time was placed in the Grand Pyramid."; break;
        case 638 : 
            if (gpJeu->getJoueur()->getAvancement()>SAGES_GROTTE) {id=639; chercheText();break;}
            texte = "The wise men are in the cave, the key of time in your possession...*Very well, meet us at the portal's cave, time has come."; break;
        case 639 :
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=640; chercheText();break;}
            texte = "In the Temple of Time is hidden a song that, played with the ocarina, will bring you back at your time."; break;
        case 640 : texte = "Good luck Link, we are all counting on you."; break;
        case 641 : texte = "10 arrows for 10 Gold Ganon?**              YES ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) idsuiv=75; break;
        case 642 : texte = "10 arrows for 10 Gold Ganon?**              yes              NO ?"; break;
        case 643 : texte = "5 bombs for 15 Gold Ganon?**              YES ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<15) idsuiv=75; break;
        case 644 : texte = "5 bombs for 15 Gold Ganon?**              yes              NO ?"; break;
        case 645 : texte = "One heart for 4 Gold Ganon?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getVie() == gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<4) idsuiv=75; break;
        case 646 : texte = "One heart for 4 Gold Ganon?**              yes              NO ?"; break;
        case 647 : texte = "A little magic jar for 8 Gold Ganon?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<8) idsuiv=75; break;
        case 648 : texte = "A little magic jar for 8 Gold Ganon?**              yes              NO ?"; break;
        case 649 : texte = "A big magic jar for 16 Gold Ganon? *              YES ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<16) idsuiv=75; break;
        case 650 : texte = "A big magic jar for 16 Gold Ganon? *              yes              NO ?"; break;
        case 651 : 
            if (gpJeu->getJoueur()->getGanonMax()>0) {id=652; chercheText(); break;}
            texte = "One second is one drip of the coffee pot. Let's hurry it up."; break;
        case 652 :
            if (gpJeu->getJoueur()->getCafe()>-1) {id=653; chercheText(); break;}
            texte = "You want to work for me? The true measure of a man is in the amount of work he does. That's what I always say."; idsuiv=653; break;
        case 653 : 
            if (gpJeu->getJoueur()->getChargeCafe()==-1 
            && gpJeu->getMonde()->motifValue(6*16,8*16)==1005) {id=655; chercheText(); break;}
            if (gpJeu->getJoueur()->getCafe()>=17) {id=672; chercheText(); break;}
            texte = "Run on the moving walkway to charge the dynamo, then stand on the button. This will start up the drip coffee maker. Then come to me to receive your money."; idsuiv=654; break;
        case 654 : texte = "I don't ask you if you're ready, preparation is the last refuge of the weak.."; break;
        case 655 : 
            if (gpJeu->getJoueur()->getCafe()>1) {
                id=654+gpJeu->getJoueur()->getCafe(); chercheText(); break;}
            texte = "I never drink more than 17 cups of coffee during a day.*But the first one is always the best."; break;
        case 656 : texte = "Blacker than a moonless night, hotter and more bitter than Hell itself... *That is coffee."; break;
        case 657 : texte = "Obviously, we'll take another."; break;
        case 658 : texte = "By the way, I wouldn't put salt in my coffee. The two don't go well, after all."; break;
        case 659 : texte = "This coffee here... It's my own special blend. I call it Godot 107. I'm trying to decide wheter to cut down on the acidity or the bitterness..."; buffer="That's the only thing I've got on my mind right now..."; break;
        case 660 : texte = "Ha... !*My 6th cup of coffee is staring up at me coldly."; break;
        case 661 : texte = "Godot Blend 102...*... My personal favorite."; break;
        case 662 : texte = "Ha... ! This blend...*Godot Blend 107...*I've decided... It's a little too bitter after all!"; break;
        case 663 : texte = "...*Aaah, bitter!"; break;
        case 664 : texte = "The weak get washed away by the tides of fate, The strong drink it up.*Ha... !*It's bitter today, too... Just like my destiny."; break;
        case 665 : texte = "...My 11th cup.*I've promised to drink no more than 17 during a day. Which means I'm still good 'til the last drop."; break;
        case 666 : texte = "A single drop of milk is all it takes to destroy the pure black magic in the cup!"; break;
        case 667 : texte = "... What bitterness.*You will learn to appreciate the bitterness when you're older."; break;
        case 668 : texte = "You know what my golden rule is?*Chuck out a bad cup of coffee. *You can always get another."; break;
        case 669 : texte = "Ha... !*Then I'd say that gives me time... to enjoy another cup of pure black magic!"; break;
        case 670 : texte = "Two minutes isn't even enough time to brew a good cup o' Joe..."; break;
        case 671 : texte = "...Cup number 17. The last cup.*It seems like the time has come to put an end to this deal."; break;
        case 672 : 
            if (gpJeu->getJoueur()->getGemme(173)) {id=673; chercheText(); break;}
            texte = "I drank my 17 cups, this is a reward"; break;
        case 673 : texte = "You still need money? Here's..."; break;
        case 674 :
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Red potions restore your energy and green potions restore your magic."; 
            idsuiv=675; break;
        case 675 : texte = "Which one do you want?*                ? RED POTION ?*                  green potion  *                      no one      "; idsuiv=678; break;
        case 676 : texte = "Which one do you want?*                  red potion  *                ? GREEN POTION ?*                      no one      "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=680; break;
        case 677 : texte = "Which one do you want?*                  red potion  *                  green potion  *                ?     NOTHING     ?"; break;
        case 678 : texte = "A red potion for 40 Gold Ganon?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<40) idsuiv=75; break;
        case 679 : texte = "A red potion for 40 Gold Ganon?**              yes              NO ?"; break;
        case 680 : texte = "A green potion for 25 Gold Ganon?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<25) idsuiv=75; break;
        case 681 : texte = "A green potion for 25 Gold Ganon?**              yes              NO ?"; break;
        case 682 : 
            if (gpJeu->getJoueur()->getCoffre(15,14)) {id=683; chercheText();break;}
            texte = "My family only knew misfortune for centuries... Even if I would like to help, I have nothing for you."; break;
        case 683 :
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>=4) {id=685; chercheText();break;}
            texte = "I am the most lucky man in the country."; buffer = "You don't believe me?*Take this treasure I found this morning wandering around, I will probably find another one tomorrow!"; break;
        case 684 : texte = "You got a precious jewel!"; break;
        case 685 : texte = "How strange, giving you this jewel makes me feel like I've settled an old familial debt..."; break;
        case 686 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>4) {id=693; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==4 
            && gpJeu->getJoueur()->getObjet()==15) {id=687; chercheText();break;}
            texte = "I am the best pastry chef of the country."; buffer = "Unfortunately, I have nothing in stock, you can't find anything sweet around here..."; break;
        case 687 : texte = "You have marmelade???*I thought the last ones were out-of-date since centuries! Give it to me, for my special breakfast stock!"; idsuiv=688; break;
        case 688 : texte = "This marmelade for his stock, ok?**              YES ?            no  "; idsuiv=690; break;
        case 689 : texte = "This marmelade for his stock, ok?**              yes              NO ?"; idsuiv=691; break;
        case 690 : texte = "I will have my best breakfast since ages!*Here is what I had put aside:"; break;
        case 691 : texte = "In that case why did you display it? *Show off..."; break;
        case 692 : texte = "You traded the marmelade for a croissant."; break;
        case 693 : texte = "Sooner or later, I guess I will have to find a new job..."; break;
        case 694 :
            if (gpJeu->getJoueur()->getGanonMax() > 0) {id=696; chercheText();break;}
            texte = "You look even more broke than I am...*You should go to see the guy in the coffe house, he looks for an employee."; buffer = "Also, take this, you'll need it:"; break;
        case 695 : texte = "You got a wallet able to hold up to 99 Gold Ganon!"; break;
        case 696 : texte = "So, how goes your money?"; break;
        case 697 : 
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())<2 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<4) idsuiv=698;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())<2 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>3) idsuiv=699;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>1 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<4) idsuiv=704;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>1 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>3) idsuiv=709;
            texte = "Welcome in the Hyrule Bank. I am specialized in currencies."; break;
        case 698 : texte = "You don't have anything interesting, come back if you find precious currencies, I will give you a good price."; break;
        case 699 : texte = "These are rupees you say? Pretty curious."; idsuiv=700; break;
        case 700 : texte = "It seems to be precious, let's see..."; idsuiv=701; break;
        case 701 : 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()==gpJeu->getJoueur()->getPieceMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/4);
            texte = os.str()+" Rupees for "+os2.str()+" Gold Coins, ok?**              YES ?            no  "; idsuiv=703; break;
        case 702 : 
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/4);
            texte = os.str()+" Rupees for "+os2.str()+" Gold Coins, ok?**              yes              NO ?"; idsuiv=76; break;
        case 703 : texte = "It's a deal!"; break;
        case 704 : texte = "You have gold? With a monster head on it... You call that Gold Ganon?"; idsuiv=705; break;
        case 705 : texte = "It's really ugly, but the gold is reusable, let's see..."; idsuiv=706; break;
        case 706 : 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()==gpJeu->getJoueur()->getPieceMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Gold Ganon for "+os2.str()+" Gold Coins, ok?**              YES ?            no  "; idsuiv=708; break;
        case 707 : 
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Gold Ganon for "+os2.str()+" Gold Coins, ok?**              yes              NO ?"; idsuiv=76; break;
        case 708 : texte = "It's a deal!"; break;
        case 709 : texte = "What do you want to sell me?*   - RUPEES ?*   - Gold Ganon  *   - Nothing  "; idsuiv=700; break;
        case 710 : texte = "What do you want to sell me?*   - Rupees  *   - GOLD GANON ?*   - Nothing  "; idsuiv=705; break;
        case 711 : texte = "What do you want to sell me?*   - Rupees  *   - Gold Ganon  *   - NOTHING ?"; idsuiv=76; break;
        case 712 :
            if (gpJeu->getJoueur()->getCoffre(15,22)) {id=717; chercheText();break;}
            texte = "Hello Link, I was waiting for you."; idsuiv=713; break;
        case 713 : texte = "I am the leader of the 7 Wise Men, and also the most powerful of them. I saw you in my dreams, as well as a very sad future..."; idsuiv=714; break;
        case 714 : texte = "Your presence here seems to show that I was successful... At least partially..."; idsuiv=715; break;
        case 715 : texte = "I was the one who created the portal to the future, for you to be the witness of my visions."; idsuiv=716; break;
        case 716 : texte = "I also built the Temple of Time with the others wise men, so that you would travel as you wish across the times."; idsuiv=717; break;
        case 717 : texte = "From now on it's up to you. You have to find the 7 magic crystals that will open the way to the legendary Goddesses Temple, and be the first to find and take the Triforce!"; idsuiv=718; break;
        case 718 : texte = "Shall his path lead the true heroe to the Triforce."; break;
        case 719 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>2
            && gpJeu->getJoueur()->hasObjet(O_TROC2)>3
            && gpJeu->getJoueur()->hasObjet(O_TROC3)>3) {id=726; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==2 
            && gpJeu->getJoueur()->getObjet()==3) {id=720; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==3 
            && gpJeu->getJoueur()->getObjet()==7) {id=727; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==3 
            && gpJeu->getJoueur()->getObjet()==11) {id=733; chercheText();break;}
            texte = "Don't judge me on my size, I am a first-class blacksmith!"; 
            buffer = "But I got admit, I happen to have just arrived here, and I couldn't move all my forge here... So I don't have anything."; break;
        case 720 : texte = "You've carried an anvil with you???*What are you, stupid?"; buffer = "I can get you rid of it if you want, I need one. *I would even give you a little reward for your trouble."; idsuiv=721; break;
        case 721 : texte = "This anvil for a reward, ok?**              YES ?            no  "; idsuiv=723; break;
        case 722 : texte = "This anvil for a reward, ok?**              yes              NO ?"; idsuiv=724; break;
        case 723 : texte = "Thank you, there, it's a horseshoe I made some time ago:"; break;
        case 724 : texte = "I only said that to help you..."; break;
        case 725 : texte = " You got a horseshoe!"; break;
        case 726 : texte = "With all these things you brought to me, I can open my forge again!"; break;
        case 727 : texte = "It's a good hammer you have here...*It may be useful in my forge... Will you give it to me? I will reward you with one of my creations."; idsuiv=728; break;
        case 728 : texte = "This hammer for a reward, ok?**              YES ?            no  "; idsuiv=730; break;
        case 729 : texte = "This hammer for a reward, ok?**              yes              NO ?"; idsuiv=731; break;
        case 730 : texte = "Thank you, here is one of my most beautiful creations:"; break;
        case 731 : texte = "As if you knew what to do with this hammer..."; break;
        case 732 : texte = "You got a little bell!"; break;
        case 733 : texte = "You have some Gold Dust?*I will need it to forge new wonderful objects, will you give it to me for a wonderful reward?"; idsuiv=734; break;
        case 734 : texte = "The Gold Dust for a wonderful reward, ok?**              YES ?            no  "; idsuiv=736; break;
        case 735 : texte = "The Gold Dust for a wonderful reward, ok?**              yes              NO ?"; idsuiv=737; break;
        case 736 : texte = "Thank you, take this magic mirror in return! *It was bewitched by the wise men and got some mysterious powers..."; break;
        case 737 : texte = "It was areally good reward though..."; break;
        case 738 : texte = "You got the magic mirror!"; break;
        case 739 : 
            if (gpJeu->getJoueur()->getEpee()>2) {id=748; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==0) {id=745; chercheText();break;}
            texte = "You sword is really impressive... But I think I could improve it..."; idsuiv=740; break;
        case 740 : texte = "Do you want me to work on your sword?**              YES ?            no  "; idsuiv=742; break;
        case 741 : texte = "Do you want me to work on your sword?**              yes              NO ?"; idsuiv=743; break;
        case 742 : texte = "So give me your sword, it won't be long."; break;
        case 743 : texte = "What a pity, your sword really is fascinating..."; break;
        case 744 : texte = "You entrusted the Master Sword."; break;
        case 745 : texte = "It won't be long, don't worry."; break;
        case 746 :
            if (gpJeu->getJoueur()->getEpee()) {id=748; chercheText();break;}
            texte = "It's done, here is your sword:"; break;
        case 747 : texte = "The Master Sword was reforge! His power is improved!"; break;
        case 748 : texte = "One day, I will forge a sword as beautiful as yours, word of blacksmith!"; break;
        case 749 : texte = "You shouldn't go too far away from the village by this weather..."; break;
        case 750 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "10 arrows for 5 Gold Coins?**              YES ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<5) idsuiv=75; break;
        case 751 : texte = "10 arrows for 5 Gold Coins?**              yes              NO ?"; break;
        case 752 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "5 bombs for 10 Gold Coins?**              YES ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10) idsuiv=75; break;
        case 753 : texte = "5 bombs for 10 Gold Coins?**              yes              NO ?"; break;
        case 754 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "One heart for 1 Gold Coins?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getVie() == gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<1) idsuiv=75; break;
        case 755 : texte = "One heart for 1 Gold Coins?**              yes              NO ?"; break;
        case 756 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "A little magic jar for 3 Gold Coins? *              YES ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<3) idsuiv=75; break;
        case 757 : texte = "A little magic jar for 3 Gold Coins? *              yes              NO ?"; break;
        case 758 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "A big magic jar for Gold Coins? *              YES ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<6) idsuiv=75; break;
        case 759 : texte = "A big magic jar for 6 Gold Coins? *              yes              NO ?"; break;
        case 760 : texte = "You find the book of Mudora!*From now on you understand the ancient Hylian!"; break;
        case 761 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Hello, I am the chief of the village. *Don't listen to the gossips saying that this village is endangered, and enjoy your time with us."; break;
        case 762 : texte = "Looks like it stopped snowing..."; break;
        case 763 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Red potions restore your energy and green potions restore your magic."; 
            idsuiv=764; break;
        case 764 : texte = "Wich one do you want?*                ? RED POTION ?*                  green potion  *                      no one      "; idsuiv=767; break;
        case 765 : texte = "Wich one do you want?*                  red potion  *                ? GREEN POTION ?*                      no one      "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=769; break;
        case 766 : texte = "Wich one do you want?*                  red potion  *                  green potion  *                ?     NO ONE     ?"; break;
        case 767 : texte = "A red potion for 15 Gold Coins?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<15) idsuiv=75; break;
        case 768 : texte = "A red potion for 15 Gold Coins?**              yes              NO ?"; break;
        case 769 : texte = "A green potion for 10 Gold Coins?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10) idsuiv=75; break;
        case 770 : texte = "A green potion for 10 Gold Coins?**              yes              NO ?"; break;
        case 771 : texte = "You look pretty moneyless, you don't even have a wallet?*Here, take this one:"; break;
        case 772 : texte = "You've got a wallet able to hold up to 99 Gold Coins!"; break;
        case 773 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Hello, I am one of the 7 wise men, in passing through this town."; idsuiv=774; break; 
        case 774 :
            texte ="The book of Mudora was bewitched to enable anyone having it to speak our language.";
            buffer = "You must come from far away if you don't speak our language... Keep this book, it will help you."; break;
        case 775 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Hi man, the name is Ganondorf, if you hear anything about the magic crystals, you come and speak to me, got it?"; break;
        case 776 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "I am the head of the hylian knights. *If you don't want any trouble behave yourself, follow Ganondorf's example, he is a good guy."; break;
        case 777 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "This Ganondorf keep treating us to drink... *He really is a good fellow..."; break;
        case 778 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>5) {id=785; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==5 
            && gpJeu->getJoueur()->getObjet()==15) {id=779; chercheText();break;}
            texte = "To drink is very well... but when do we eat?"; break;
        case 779 : texte = "Don't tell me... This smell... It's a croissant!*Give it to me, for my endless friendship!"; idsuiv=780; break;
        case 780 : texte = "This croissant for his friendship, ok?**              YES ?            no  "; idsuiv=782; break;
        case 781 : texte = "This croissant for his friendship, ok?**              yes              NO ?"; idsuiv=783; break;
        case 782 : texte = "Thank you!!!*Take this present in return, it's the symbol of our friendship!"; break;
        case 783 : texte = "... You are declaring war to the Hylian Knight???*Are you out of your mind???"; break;
        case 784 : texte = "You traded the croissant for a beer."; break;
        case 785 : texte = "Hi pal!*Will you drink something with us?"; break;
        case 786 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "If you want a hylian knight to disclose a restricted information, you have to treat him a drink. It's our rule."; break;
        case 787 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->getCoffre(15,23)<3) {id=788; chercheText(); break;}
            texte = "You already know all my informations...*Hic!"; break;
        case 788 : 
            texte = "I have a lot of restricted informations known only by ourselves (and by Ganondorf). A glass of beer is 1 Gold Coin, do we have a deal?"; idsuiv=789; break;
        case 789 : 
            texte = "An information for 1 Gold Coin, ok?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<1) idsuiv=75; break;
        case 790 : texte = "An information for 1 Gold Coin, ok?**              yes              NO ?"; idsuiv=76; break;
        case 791 : 
            if (gpJeu->getJoueur()->getCoffre(15,23)>0) {id=792; chercheText(); break;}
            texte = "The Hylian Knights were founded in order to protect the temple of the Goddesses... This temple is supposed to hide a powerful relic called the Triforce..."; break;
        case 792 : 
            if (gpJeu->getJoueur()->getCoffre(15,23)>1) {id=793; chercheText(); break;}
            texte = "To open the way to the temple of the Godesses, you have to go in the Holy Land, North of here, and stand on the Triforce symbol with the 7 crystals in your possession."; break;
        case 793 : texte = "The 7 magic crystals are hidden every where in Hyrule... And, keep this as a secret, one of them is kept by the legendary hylian knights!"; break;
        case 794 : texte = "Our chief chased him downstairs..."; break;
        case 795 : texte = "What a strenght... he beat us so easily..."; break;
        case 796 : texte = "He is... downstairs...*Be careful... ... my friend."; break;
        case 797 : texte = "He is too strong... The chief won't hold out any longer...*Help him, I'm begging you..."; break;
        case 798 : texte = "Someone ... stop him..."; break;
        case 799 : texte = "Do you intend to be on my way too? So en garde!"; break;
        case 800 : texte = "I failed...*Forgive me master..."; break;
        case 801 : texte = "Thank you for your help Link, without you, Ganondorf would have take the crystal..."; idsuiv=802; break;
        case 802 : texte = "The order of the Hylian Knight was founded to protect the access to the Temple of the Goddesses, it was our mission to keep the crystal safe. Without this one, the 6 others are useless."; idsuiv=803; break;
        case 803 : texte = "Unfortunately, with time, the order became weak. And today, we failed."; idsuiv=804; break;
        case 804 : texte = "Keep the crystal, you seem much more trustworthy than we are..."; idsuiv=805; break;
        case 805 : texte = "As for Ganondorf... We couldn't have guessed he would betray us... He was almost one of us..."; idsuiv=806; break;
        case 806 : texte = "He was send to the Supermax prison, north of here... *He shouldn't be any trouble now..."; break;
        case 807 : 
            if (gpJeu->getJoueur()->getGemme(178)) {id=816; chercheText(); break;}
            texte = "I failed against Ganondorf, but don't underestimate me. I am the man who killed a hundred wolves."; idsuiv=808; break;
        case 808 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=1) {id=809; chercheText(); break;}
            texte = "You didn't kill any wolf???*You are a coward!"; break;
        case 809 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=2) {id=810; chercheText(); break;}
            texte = "You killed only one wolf???*You are weak!"; break;
        case 810 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=50) {id=811; chercheText(); break;}
            os << g;
            texte = "You killed only "+os.str()+" wolves?*It's not that great..."; break;
        case 811 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=80) {id=812; chercheText(); break;}
            os << g;
            texte = "You killed "+os.str()+" wolves?*Not bad..."; break;
        case 812 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=100) {id=813; chercheText(); break;}
            os << g;
            texte = "You killed "+os.str()+" wolves?*Pretty impressive..."; break;
        case 813 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>100) {id=814; chercheText(); break;}
            texte = "You killed 100 wolves?*As many as I did... it's hard to believe..."; break;
        case 814 : 
            texte = "You killed more than a hundred wolves???*Incredible..."; idsuiv=815; break;
        case 815 : texte = "You really deserve this reward:"; break;
        case 816 : texte = "It's time for me to go back in the training..."; break;
        case 817 : texte = "I will change my hairstyle."; break;
        case 818 : texte = "I will start a diet."; break;
        case 819 : texte = "I won't sell restricted informations anymore."; break;
        case 820 : texte = "I won't spend my days in the tavern."; break;
        case 821 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>5) {id=828; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==5 
            && gpJeu->getJoueur()->getObjet()==7) {id=822; chercheText();break;}
            texte = "I broke my last axe... So I play hangman to kill time, but it's not the same..."; break;
        case 822 : texte = "You have an axe for me???*Give it to me! I trade it for a rope just as effective!"; idsuiv=823; break;
        case 823 : texte = "This axe for a rope, ok?**              YES ?            no  "; idsuiv=825; break;
        case 824 : texte = "This axe for a rope, ok?**              yes              NO ?"; idsuiv=826; break;
        case 825 : texte = "I am so touched...*That's for you:"; break;
        case 826 : texte = "...*It should be punishable by death penalty..."; break;
        case 827 : texte = "You traded the axe for a rope."; break;
        case 828 : texte = "I can't wait to try this axe!"; break;
        case 829 : texte = "Hello, I am the head of this village."; idsuiv=830; break;
        case 830 : texte = "The Mabe village is like a paradise for tourists, but like a hell for robbers."; buffer = "Did you know that famous pirate was captured here when he passed by this town?"; break;
        case 831 : texte = "You find a hammer!"; break;
        case 832 : 
            if (gpJeu->getJoueur()->getCoffre(15,26)) {id=839; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==6 
            && gpJeu->getJoueur()->getObjet()==3) {id=833; chercheText();break;}
            texte = "My husband is guard at the prison.*It's a full-time job so I don't see him very often..."; break;
        case 833 : texte = "???*What do you have here???*Let me have a look at it!"; idsuiv=834; break;
        case 834 : texte = "Give her the wedding ring, ok?**              YES ?            no  "; idsuiv=836; break;
        case 835 : texte = "Give her the wedding ring, ok?**              yes              NO ?"; idsuiv=837; break;
        case 836 : texte = "It's my husband's wedding ring!*Don't tell me he went to see HER again!!!"; break;
        case 837 : texte = "...*It seems more and more shady...*Gimme that!"; idsuiv=834; break;
        case 838 : texte = "You traded the wedding ring for nothing."; break;
        case 839 : texte = "Out of my way!"; break;
        case 840 : texte = "Don't go in the storeroom, I didn't do the cleaning!"; break;
        case 841 : texte = "A famous pirate named Ganon D. Roger was captured in this town a long time ago...";
            buffer = "They say that a descendant of this pirate would live in Hyrule right now..."; break;
        case 842 : texte = "You are in the 7 wise men's residence.*This place is devoted to meditation and knowledge."; break;
        case 843 : texte = "Our chief, the most powerful of the 7 wise men, is barely seen here. He prefers to stay meditating in his house at the South of the Village."; break;
        case 844 : texte = "Some years ago, we were 8 wise men. One of us, Agahnim, thought that it was our duty to take the Triforce and to use it for the sake of everyone."; idsuiv=845; break;
        case 845 : texte = "Our chief squarely refused. He said that such a power should not fall into the hands of men, that the consequences could be desastrous..."; idsuiv=846; break;
        case 846 : texte = "After this quarrel, Agahnim left the order. But lately, he reappeared, endowed with strange powers..."; buffer="We unfortunately do not know what he may have in mind."; break;
        case 847 : texte = "A legendary pirate came in Hyrule long ago. He was captured after a long fighting against the hylian knights of the time."; idsuiv=848; break;
        case 848 : texte = "The day of his public execution, a man in the crowd asked him where he had hidden his treasure. The pirate explained that it was hidden in 4 temples in Hyrule."; idsuiv=849; break;
        case 849 : texte = "After this declaration, many men went in search of this treasure but no one ever came back..."; break;
        case 850 : texte = "Did you meet a man named Ganondorf? *When he was just a child he almost ended up in the stomach of a wolf, but he was saved by a former member of our order."; idsuiv=851; break; 
        case 851 : texte = "Since then he considers his saviour as his master."; break;
        case 852 : texte = "Our chief asked us to gather our powers in order to create a very special temple East of here. He says that this temple would save the world..."; break;
        case 853 : 
            if (gpJeu->getJoueur()->getGemme(182)) {id=854; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>0) {id=855; chercheText();break;}
            texte = "The moutain North of the village hid a temple. Far end of this temple is hidden an incredible treasure. But... it's far to dangerous to go in."; break;
        case 854 : texte = "I still can't believe you were able to find this treasure..."; break;
        case 855 : texte = "WHAT ??? YOU FOUND THE TREASURE OF THE TEMPLE!!!"; idsuiv=856; break;
        case 856 : texte = "Incredible... take this, I want to reward you for this feat!"; break;
        case 857 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>4) {id=864; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==4 
            && gpJeu->getJoueur()->getObjet()==3) {id=858; chercheText();break;}
            texte = "It's been along time since HE gave me anything..."; break;
        case 858 : texte = "You have a jewel?*It's from HIM, isn't it?*Yes, it can only be from HIM!"; idsuiv=859; break;
        case 859 : texte = "Give the jewel?**              YES ?            no  "; idsuiv=861; break;
        case 860 : texte = "Give the jewel?**              yes              NO ?"; idsuiv=862; break;
        case 861 : texte = "It's so nice of him...*Could you go to the prison and give him this letter please?"; break;
        case 862 : texte = "...*I'll tell HIM!"; break;
        case 863 : texte = "You traded the jewel for a letter."; break;
        case 864 : texte = "He! He! He!"; break;
        case 865 : texte = "I am the chief of the village and er... anyway the wise men are the one in control here..."; break;
        case 866 :
            if (gpJeu->getJoueur()->getCoffre(15,27)==12) {id=886; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(15,27)) {id=868; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==7 
            && gpJeu->getJoueur()->getObjet()==11) {id=867; chercheText();break;}
            texte = "We are closed to the public."; break;
        case 867 : texte = "We waited for you for a long time...*Take the time to visit my opera..."; break;
        case 868 : texte = "This opera has a long story, take your time to discover it..."; break;
        case 869 : texte = "Welcome visitor, allow me to tell you the story of this opera."; buffer="I am the founder of this opera, but formerly I was nothing but a mere thief."; break;
        case 870 : texte = "One day, a burglary went wrong and the hylian knights patrolling near the tavern fell on me. I was punished and sent in prison."; break;
        case 871 : texte = "In prison, I found an old skull under my berth. I used it as an accessory to recite monologues, much to the delight of my cellmate."; idsuiv=872; break;
        case 872 : texte = "Thus was born my passion for the theatre and then for the opera, in prison."; break;
        case 873 : texte = "Shortly before my release, I made the promise on the old skull to construct the most somptuous of the theatres before my cellmate's release."; break;
        case 874 : texte = "Once free, I went in search of a building land. Until the day when, chased by wolves, I had to take refuge in the Lost Woods."; idsuiv=875; break;
        case 875 : texte = "That's when I found this glade, at the far end of the forest, in a green setting, protected by the one-thousand-year-old trees..."; break;
        case 876 : texte = "I started to built my opera. The plans were quickly made, but without money to pay workers, it seemed an impossible task."; idsuiv=877; break;
        case 877 : texte = "When I was thinking of giving up, an odd fellow came and brought me back the skull, and reminded me my promise."; break;
        case 878 : texte = "After months of work, the opera was finished. It was the most beautiful opera ever seen in Hyrule."; break;
        case 879 : texte = "Quickly, prestigious artists coming from all countries came to perform here. I had fufilled my dream and kept my promise."; break;
        case 880 : texte = "During the war against Ganon, many smugglers used the chaos to prosper."; idsuiv=881; break;
        case 881 : texte = "One of them was none other than my old cellmate, newly released, who asked to use the opera as his hideout."; break;
        case 882 : texte = "With the return of the peace, the King of Hyrule wished to end the smuggling. He sent his best soldiers to chase the culprits."; idsuiv=883; break;
        case 883 : texte = "I was afraid of losing every thing because of my complicity, I asked my old friend to leave the opera, saying that I would hand him over the king if he refused."; break;
        case 884 : texte = "Obliged to leave the opera, the bandits locked me in their old hideout with the employees, and burned it down."; idsuiv=885; break;
        case 885 : texte = "This is how I died, along with my opera, that was destroyed forever..."; break;
        case 886 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>7) {id=893; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==7 
            && gpJeu->getJoueur()->getObjet()==11) {id=887; chercheText();break;}
            texte = "You know my story, don't you have anything to show me?"; break;
        case 887 : texte = "I have waited your coming for centuries to settle that old debt..."; idsuiv=888; break;
        case 888 : texte = "Make him settle his debt?**              YES ?            no  "; idsuiv=890; break;
        case 889 : texte = "Make him settle his debt?**              yes              NO ?"; idsuiv=891; break;
        case 890 : texte = "My life was short but exciting. Nothing of it would have been possible without your intervention."; buffer="I wanted to give you this: the saw I used to construct this opera!"; break;
        case 891 : texte = "...*You must be kidding?"; break;
        case 892 : texte = "You traded the IOU for a saw."; break;
        case 893 : texte = "Go now, it is time for us to rest in peace..."; break;
        case 894 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>1) {id=901; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==1 
            && gpJeu->getJoueur()->getObjet()==11) {id=895; chercheText();break;}
            texte = "As the barman, I know all the gossips...";
            buffer = "Here is one: my favorite color is said to be the yellow...*But I didn't tell you anything, ok?"; break;
        case 895 : texte = "It's a pretty yellow stone you have here... Will you trade it for my best bottle?"; idsuiv=896; break;
        case 896 : texte = "This yellow gemstone for a bottle, ok?**              YES ?            no  "; idsuiv=898; break;
        case 897 : texte = "This yellow gemstone for a bottle, ok?**              yes              NO ?"; idsuiv=899; break;
        case 898 : texte = "Yay! It's mine!"; break;
        case 899 : texte = "Tsss... no one will give you more for it you know..."; break;
        case 900 : texte = "You traded the yellow gemstone for a bottle of wine."; break;
        case 901 : texte = "You want something to drink? It will be free for you."; break;
        case 902 : texte = "A melody is engraved on the stele:"; break;
        case 903 : texte = "You learn the song of soaring!*Play it outside to teleport!"; break;
        case 904 : texte = "You learn the inverted song of time!*Play it outside to go back in time!"; break;
        case 905 : texte = "You learn the song of double time!*Play it outside to travel to the future!"; break;
        case 906 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>5) {id=913; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==5 
            && gpJeu->getJoueur()->getObjet()==3) {id=907; chercheText();break;}
            texte = "I am a part-time guard in this prison. *Outside of the visit hours I'm not allowed to let you pass."; break;
        case 907 : texte = "This letter is for me? It's probably from HER... Give it quickly!"; idsuiv=908; break;
        case 908 : texte = "Give the letter?**              YES ?            no  "; idsuiv=910; break;
        case 909 : texte = "Give the letter?**              yes              NO ?"; idsuiv=911; break;
        case 910 : texte = "...*...*..."; buffer="I have to leave my post... it's er... an emergency... You look like a good guy, take my place. Oh and keep that for me:"; break;
        case 911 : texte = "It's not for me?*Too bad..."; break;
        case 912 : texte = "You traded the letter for a wedding ring."; break;
        case 913 : texte = "I gotta go!"; break;
        case 914 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>5) {id=921; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==5 
            && gpJeu->getJoueur()->getObjet()==11) {id=915; chercheText();break;}
            texte = "I am but a mere innocent arrived here by mistake... You wouldn't have something to help me fly from here?"; break;
        case 915 : texte = "A... spoon huh?"; idsuiv=916; break;
        case 916 : texte = "Give the spoon?**              YES ?            no  "; idsuiv=918; break;
        case 917 : texte = "Give the spoon?**              yes              NO ?"; idsuiv=919; break;
        case 918 : texte = "Thank you... ... ...*There, take this gift as a thanks...*It belonged to my former cellmate..."; break;
        case 919 : texte = "Sounds like a wonderful spoon escape possibility just fled..."; break;
        case 920 : texte = "You traded the spoon for a skull."; break;
        case 921 : texte = "Well... some work has to be done now..."; break;
        case 922 : texte = "I didn't think my mission could fail... The hylian knights aren't very strong, even their chief is getting weaker..."; break;
        case 923 : texte = "The explosion came from the room at the right."; break;
        case 924 : texte = "So here is the man who was able to stop the powerful Ganondorf..."; idsuiv=925; break;
        case 925 : texte = "I am Agahnim, former wise man, and Ganondorf's mentor. As for you, you must be Link..."; idsuiv=926; break;
        case 926 : texte = "Like it or not, we are going to take the Triforce.*Farewell!"; break;
        case 927 : texte = "                    Level 1 :                                                                                Temple of Courage"; break;
        case 928 : texte = "                    Level 2 :                                                                                 Temple of Wisdom"; break;
        case 929 : texte = "                    Level 3 :                                                                                  Temple of Power"; break;
        case 930 : texte = "                    Level 4 :                                                                                   Abyss Ruins"; break;
        case 931 : texte = "                    Level 5 :                                                                                 Phantom Pyramid"; break;
        case 932 : texte = "                 Great Pyramid"; break;
        case 933 : texte = "                Temple of Earth"; break;
        case 934 : texte = "                 Temple of Air"; break;
        case 935 : texte = "                Temple of Water"; break;
        case 936 : texte = "                 Temple of Fire"; break;
		case 937 : texte = "               Temple of Goddesses"; break;
        case 938 : 
            if (gpJeu->getAudio()->isSpecial()) {
            texte = "                 Hyrule Castle"; break;}
            texte = "                   Final Level :                                                                               Hyrule Castle"; break;
        case 939 : texte = "            Second Quest - Level 1 :                                                                               Casino"; break;
        case 940 : texte = "            Second Quest - Level 2 :                                                                            Tower of Gem"; break;
        case 941 : texte = "          Second Quest - Final Level :                                                                        Final Destination"; break;
        
        case 942 : texte = "You found the map!!!**Press START to see the dungeon map."; break;
        case 943 : texte = "You found the compass!!!**The Boss and chests are now indicated on the map."; break;
        case 944 : texte = "You found the Boss Key!!!**Use it to open his haunt."; break;
        case 945 : texte = "You found a little key.**Use it to unlock a door."; break;
        case 946 : texte = "You found a new heart!!! **Your amount of life increases by one heart!!!"; break;
        case 947 : texte = "You found a bow!!!**Equip it selecting the bow from inventory then use it with Y to attack from a distance!"; break;
        case 948 : 
            if (gpJeu->getZone()==47) {id=949; chercheText();break;}
            if (gpJeu->getZone()==48) {id=950; chercheText();break;}
            texte = "You found the Pendant of Courage!!!"; break;
        case 949 : texte = "You found the Pendant of Wisdom!!!"; break;
        case 950 : texte = "You found the Pendant of Power!!!"; break;
        case 951 : texte = "You found the Power Gloves!!!**Now you can lift rocks!"; break;
        case 952 : 
            if (gpJeu->getJoueur()->hasObjet(O_GANTS)) {id=954; chercheText();break;}
            if (gpJeu->getJoueur()->getExplore(1,16,4)) {id=953; chercheText();break;}
            texte = "I give up, you win!*How could you defeat the Ultimate LOL technique???"; break;
        case 953 : texte = "You won't let me get out of it so easily, huh?*The code in the next room is 12086... Now get lost."; break;
        case 954 : texte = "I should have stayed in the family gang..."; break;
        case 955 : texte = "You found the lantern!!!**Now you can shot up flames!"; break;
        case 956 : texte = "You found the flippers!!!**Now you can cross the water!"; break;
        case 957 : 
            if (gpJeu->getJoueur()->getCoffre(3,29)) {id=960; chercheText();break;}
            texte = "???*How could you arrive in here? *My pet was supposed to mount guard!"; idsuiv=958; break;
        case 958 : texte = "...*You are Link, you say?*...*So the time has already come?"; idsuiv=959; break;
        case 959 : texte = "Ganon's minions discovered my existence and destroyed the village I lived in. That's why I came in this temple to hide."; idsuiv=960; break;
        case 960 : texte = "Continue your quest Link, I will see you again in the portal's cave!"; break;
        case 961 : texte = "You found a better tunic!!!**Your defense raises by one point!"; break;
        case 962 : texte = "You found the Key of Time!!!**Go quickly show it to the wise men!"; break;
        case 963 : texte = "You found the Magic Hammer!!!**Use it to pound the stakes blocking your way!"; break;
        case 964 : texte = "You found the Titan's Mitt!!!**Now you can lift the heaviest rocks!!!"; break;
        case 965 : texte = "You found a Yellow Gemstone!**It's an inestimable treasure!"; break;
        case 966 : texte = "You found the Fairy Bow!!!**Your arrows are now incredibly powerful!!!"; break;
        case 967 : texte = "You found a Green Gemstone!**It's an inestimable treasure!"; break;
        case 968 : texte = "You found the Ice Rod!!!**Now you can freeze your enemies from a distance!!!"; break;
        case 969 : texte = "You found a Blue Gemstone!**It's an inestimable treasure!"; break;
        case 970 : texte = "You found the Fire Rod!!!**You can now shoot up powerful fire balls!!!"; break;
        case 971 : texte = "You found a Red Gemstone!**It's an inestimable treasure!"; break;
	    case 972 : texte = "You found an incredibly tough shield!!!*Your defense raises with one point!"; break;
        case 973 : texte = "Here you are at last."; idsuiv=974; break;
        case 974 : texte = "Did you really think you could outrun a sorcerer able to teleport?"; idsuiv=975; break;
        case 975 : texte = "I guess i still have to thank you. *To find this temple is no easy. Ganondorf and I spent months without finding even one crystal."; idsuiv=976; break;
        case 976 : texte = "And the day when finally, we were about to reach one easily you turned up and brought down the powerful Ganondorf... *I have to admit I wasn't expecting that..."; idsuiv=977; break;
        case 977 : texte = "However, it seemed obvious that we were working towards the same end, and that you were in advance of us."; idsuiv=978; break;
        case 978 : texte = "So we decided you would find the temple for us."; idsuiv=979; break;
        case 979 : texte = "You had fun all this time, but now is our turn."; idsuiv=980; break;
        case 980 : texte = "It is time for you to disappear."; break;
        case 981 : texte = "What??? *You couldn't possibly defeat Aghanim???"; idsuiv=982; break;
        case 982 : texte = "... *Hope still remains, I can do something..."; break;
        case 983 : texte = "Welcome Link. *We are Din, Nayru et Farore, the founding Goddesses of Hyrule."; idsuiv=984; break;
        case 984 : texte = "Your efforts to save Hyrule finally lead you in front of us."; idsuiv=985; break;
        case 985 : texte = "As you may have undestood already, You cannot change the past. All of your acts had the only effect of preparing the present you come from."; idsuiv=986; break;
        case 986 : texte = "Ganondorf came to our temple to follow his master, and he finally brought him back to life."; idsuiv=987; break;
        case 987 : texte = "He wished to be able to travel between life and death, but only the most powerful demons can do that."; idsuiv=988; break;
        case 988 : texte = "Thanks to his new powers, Ganon was able to bring Aghanim back to life, but his new nature overflew his reason."; idsuiv=989; break;
        case 989 : texte = "He changed Agahnim into zombi in his pay, proclaimed himself King of Evil and came back to conquer Hyrule."; idsuiv=990; break;
        case 990 : texte = "The chief of the middle village organized the defense of Hyrule after proclaiming himself King. He had the Master Sword forged and made knights and wise men work together."; idsuiv=991; break;
        case 991 : texte = "The Hylian Knights were destroyed, but their chief, armed with the Master Sword, beat back Ganon long enough to give the wise men time to seal him forever."; idsuiv=992; break;
        case 992 : texte = "But you know what happened next. Using Agahnim, Ganon eliminated the wise men's descendents ans broke off the seal."; idsuiv=993; break;
        case 993 : texte = "With the Master Sword you beat him off several times, but the world of death can't keep him prisoner for long."; idsuiv=994; break;
        case 994 : texte = "Ganon found the Triforce, but this temple hides some other treasurs..."; idsuiv=995; break;
        case 995 : texte = "Against the Triforce, able to give an illimited power to the one touching it, we created an anti-Triforce."; idsuiv=996; break;
        case 996 : texte = "They are 3 weapons with an exceptional power. If two of them unite against the Triforce holder, they will call of his wish."; idsuiv=997; break;
        case 997 : texte = "The Sword of Courage is rightfully yours. We also entrust you with the Bow of Wisdom, give it to the only one able to handle it."; idsuiv=998; break;
        case 998 : texte = "As for the Trident of Power, we send it to the last chosen one."; break;
        case 999 : texte = "You got the Sword of Courage!!! *This legendary weapon gives off a tremendous power."; break;
        case 1000: texte = "You got the Bow of Wisdom!!! *A mysterious power prevents you from using it..."; break;
        case 1001: texte = "Time has come Link, we send you back to your era."; break;
        case 1002: texte = "Link! It's Zelda! I'm talking with you by telepathy, you couldn't be reach!"; idsuiv=1003; break;
        case 1003: texte = "Ganon is back! He's attacking the castle! *All of the guards have been changed into monsters under his control, be careful!"; break;
        case 1004: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_PALAIS) {id=1010; chercheText();break;}
            texte = "The throne room is further North."; break;
        case 1005: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_ZELDA_PALAIS) {id=1010; chercheText();break;}
            if (gpJeu->getJoueur()->getRubisMax()) {id=1013; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_PALAIS) {id=1007; chercheText();break;}
            texte = "The Princess is not ready to receive you yet."; idsuiv=1006; break; 
        case 1006: texte = "However, she instructed me to tell that some items have been stored for you in the storeroom."; break;
        case 1007: texte = "The Princess will be ready to see you in a few minutes."; break;
        case 1008:
            if (gpJeu->getJoueur()->getRubisMax()) {id=1010; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()<PARLE_GARDE_PALAIS) {id=1004; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_RESERVE) {id=1009; chercheText();break;}
            texte = "You got the authorization to go in the storeroom? *Very well, you can go on."; break;
        case 1009: texte = "The storeroom is further East"; break;
        case 1010: texte = "The castle is under control."; break;
        case 1011: texte = "You found a shield!*Your defense raises by one point!"; break;
        case 1012: texte = "You got a wallet able to hold up to 99 Rupees !"; break;
        case 1013: texte = "Princess Zelda is waiting for you."; break;
        case 1014: texte = "Hello Link."; break;
        case 1015: texte = "Er, Link! *I'm here!*Yoo-hoo!"; break;
        case 1016: 
            if (gpJeu->getJoueur()->getAvancement()>=PASSAGE_TROUVE) {id=1031; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=ZELDA_SOUS_SOL) {id=1025; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_ZELDA_PALAIS) {id=1019; chercheText();break;}
            texte = "Some thing terrible happenned last night, Link..."; idsuiv=1017; break;
        case 1017: texte = "The Ocarina of Time you brought back from Termina... *I kept it in a safety vault here in the castle, but it has been stolen!"; idsuiv=1018; break;
        case 1018: texte = "I send guards everywhere in Hyrule, so I don't think the thief could make his way any far..."; idsuiv=1019; break;
        case 1019: texte = "I would like you to find and bring back the Ocarina. Start your investigation in the safety vault in the basement, I'll meet you there."; break;
        case 1020: 
            if (gpJeu->getJoueur()->getAvancement()<PARLE_ZELDA_PALAIS) {id=1004; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_CH_FORTE) {id=1010; chercheText();break;}
            texte = "The safety vaults are this way."; break;
        case 1021: texte = "The access to the safety vault is stricly forbidden."; break;
        case 1022: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_SOUS_SOL) {id=1023; chercheText();break;}
            texte = "The Princess instructed you with investigating the Ocarina theft? *In that case you can go. There is nothing left to steal anyway..."; break;
        case 1023: texte = "I was guarding this door last night. I am absolutely sure no one came through it..."; break;
        case 1024: texte = "That's where the Ocarina was kept. The guard heard a big noise. But before he realized it was coming from inside the room, the safe had been cleared out."; idsuiv=1025; break;
        case 1025: texte = "If you see anything suspicious, go in front of it and press A to point it out to me."; break;
        case 1026: texte = "It's a torch... What were you expecting for? A ceiling chandelier?"; break;
        case 1027: texte = "This safe is the one in which the Ocarina was kept. Until last night..."; break;
        case 1028: 
            if (gpJeu->getJoueur()->getAvancement()>=RIDEAUX_REPERES) {id=1030; chercheText();break;}
            texte = "This room used to lead out into the sewer... *Before changing it into a safety vault I had the way sealed off. The curtains are here to hide that it wasn't good work..."; break;
        case 1029: texte = "It's er... a rubber duck. *Don't ask me what it's doing here..."; break;
        case 1030: texte = "These curtains intrigue you apparently... *Let's see what's behind..."; break;
        case 1031: texte = "So that's where the thief came from! *What are you waiting for? Go after him!"; break;
        case 1032: texte = "I feel forgotten... *Here I am, guarding a safety vault empty and wide open..."; break;
        case 1033: texte = "The thief is probably in this forest, you can't give up now!"; break;
        case 1034: texte = "TUTORIAL : Press X in front of a light object like a jar in order to lift it up. Press a second time to throw it."; break;
        case 1035: texte = "TUTORIAL : Press A in front of a chest to open it. You can open a chest only if you are down it."; break;
        case 1036: texte = "                 Hyrule Castle"; break;
        case 1037: texte = "This way leads to the prison cells, you have nothing to do there."; break;
        case 1038: texte = "This way leads to a very high safety zone. Even the Hero of Hyrule is not allowed to go in."; break;
        case 1039: texte = "Er... How did you arrive here?"; break;
        case 1040: texte = "These stairs lead to the safety vaults."; break;
        case 1041: texte = "The throne room is behind this door."; break;
        case 1042: texte = "The throne room is called the throne room because there is only one throne left..."; break;
        case 1043: texte = "The door left-hand leads to the dancehall and the VIP quarters, and the door up leads to the dinig room and the kitchen."; break;
        case 1044: texte = "In the old days I played the piano standing up, but in the course of time, I decided to sit."; break;
        case 1045: texte = "I'm here as a musician, but the dancing nights I prefer to forget the harp and dance."; break;
        case 1046: texte = "I heard that a musical instrument thief came in the castle last night."; idsuiv=1047; break;
        case 1047: texte = "Fortunately, he didn't see my violin."; break;
        case 1048: texte = "A little tonic ?**              YES ?            no  "; break;
        case 1049: texte = "A little tonic ?**              yes              NO ?"; break;
        case 1050: texte = "Chef in the castle, it's no sinecure..."; break;
        case 1051: texte = "They say the best cooks are able to read and cook at the same time. As for me, I can half-do it."; break;
        case 1052: texte = "I never know what to prepare, I have to find an idea quick!"; break;
        case 1053: texte = "Waitress in the castle, it's a pretty good job, quiet and well-paying."; break;
        case 1054: texte = "The West wing is only for VIPs. And er... I didn't receive any orders about you... an oversight probably."; break;
        case 1055: texte = "The East wing of the castle is only for the guards. Sorry, but you've got nothing to do there."; break;
        case 1056: texte = "This door leads to the storeroom."; break;
        case 1057: texte = "The library is a place... pretty quiet."; break;
        case 1058: texte = "You got a energy core!*...*It's not that bad..."; break;
        case 1059: 
            if (gpJeu->getJoueur()->getAvancement()>=MOT_DE_PASSE_DONNE) {id=1062; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==MOT_DE_PASSE_CONNU) {id=1061; chercheText();break;}
            texte = "The access to the throne room is only allowed to accredited people."; break;
        case 1060: 
            if (gpJeu->getJoueur()->getAvancement()>=MULTIPASSE_UTILISE) {id=1062; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=MULTIPASS) {id=1063; chercheText();break;}
            texte = "The access to this part of the castle is reserved to the renovation staff."; break;
        case 1061: texte = "You know the secret phrase?*I knew that under your look of cute little bunny a Ganon's elite soldier was hiding."; break;
        case 1062: texte = "You can go."; break;
        case 1063: texte = "You got the authorization to go everywhere in the castle??? *Well, go through if that's so..."; break;
        case 1064: 
            if (gpJeu->getJoueur()->getAvancement()>=MOT_DE_PASSE_CONNU) {id=1070; chercheText();break;}
            texte = "You came to free me? *I didn't need your help..."; idsuiv=1065; break;
        case 1065: texte = "I wanted to take this castle by force... So I came to challenge Ganon."; idsuiv=1066; break;
        case 1066: texte = "It was a long and terrible fight... *But the throne room guards finally arrested me..."; idsuiv=1067; break;
        case 1067: texte = "Such a rotten luck, I really wanted to meet Ganon..."; idsuiv=1068; break;
        case 1068: texte = "Since then I heard that there is a secret phrase to give to the guards to pass. You have to tell them this :"; idsuiv=1069; break;
        case 1069: texte = "Sorry, but our princess is in another castle!"; idsuiv=1070; break;
        case 1070: texte = "Next time, I'll do it."; break;
        case 1071: texte = "!!!*Hey, you are..."; idsuiv=1072; break;
        case 1072: 
            gpJeu->getAudio()->stopSpecial();
            texte = "A little pink bunny! *I love pink!"; idsuiv=1073; break;
        case 1073: texte = "Make yourself at home little bunny, I entitle you to wander in the castle as you wish."; break;
        case 1074: 
            if (gpJeu->getJoueur()->isLapin()) {id=1073; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>6) {id=1078; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==6 
            && gpJeu->getJoueur()->getObjet()==15) {id=1075; chercheText();break;}
            texte = "I feel like I met you somewhere... *Anyway, you don't know where I could find a good beer?"; break;
        case 1075: texte = "Is it a beer you have?*I take it, you're here for that anyway, aren't you?"; idsuiv=1076; break;
        case 1076: texte = "Here, you can have that, as a reward."; break;
        case 1077: texte = "You traded the beer for some nails..."; break;
        case 1078: texte = "I think I like you, you're a good boy. *You wouldn't have another beer for me?"; break;
        case 1079: texte = "A score is engraved. If you had an instrument you could try to play it."; break;
        case 1080: texte = "You have... er... stolen the ocarina ??? *Let's say it's for a good cause..."; break;
        case 1081: texte = "At the instant when he played the tune with the ocarina, Link was brought back to his area. He ran to the castle to tell his story to the Princess..."; break;
        case 1082: texte = "What an awful story... *Is the Hyrule Realm really doomed to fall into Ganon's hands?"; idsuiv=1083; break;
        case 1083: 
            if (gpJeu->getJoueur()->getEpee()==5 && gpJeu->getJoueur()->hasObjet(O_ARC_OR) < 2) {id=1092; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==4 
            && gpJeu->getJoueur()->getObjet()==11) {id=1085; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==5 && gpJeu->getJoueur()->getEnnemi(50)) {id=1112; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==5) {id=1095; chercheText();break;}
            texte = "What should we do now? *If only Ganon had never found the Triforce..."; break;
        case 1084: texte = "The Ocarina carried Link once again. The Hero of Hyrule arrived in a vast snow-covered field..."; break;
        case 1085: texte = "Is that mirror for me?**              YES ?            no  "; idsuiv=1087; break;
        case 1086: texte = "Is that mirror for me?**              yes              NO ?"; idsuiv=1088; break;
        case 1087: texte = "... You're giving me a mirror??? Do you think I'm the kind of girl who spends her whole day looking at herself???"; 
            buffer = "Oh well, you can have this, as a thanks."; break;
        case 1088: texte = "...*Go away quick if you don't want to end up in a cell."; break;
        case 1089: texte = "You traded the mirror for a spoon!"; break;
        case 1090: texte = "You are in a high safety zone, I will ask you to leave."; break;
        case 1091: texte = "You found an extremly tough tunic!!!*Your defense raises by one point!"; break;
        case 1092: texte = "Happy to see you at last Link!"; idsuiv=1093; break;
        case 1093: texte = "You're telling that this bow is for me and able to defeat Ganon?*Cool!"; break;
        case 1094: texte = "You gave the Bow of Wisdom to the Princess."; break;
        case 1095: texte = "Don't worry about me, I'll be able to make my own way now."; idsuiv=1096; break;
        case 1096: texte = "We have to breast Ganon, you go first, I'll meet you there.*I have to put my make-up on first."; break;
        case 1097: texte = "!!! *Ganon regained his human form! *He is not a demon anymore, he is not able to come back from the dead world, we won!"; break;
        case 1098: texte = "???"; break;
        case 1099: texte = "Here you are at last Link. *This time victory will be mine, I perfected my techniques especially to beat you."; break;
        case 1100: texte = "Once again we face each other Link. *I feel like I get out of a long nightmare..."; idsuiv=1101; break;
        case 1101: texte = "Agahnim was wrong, the Triforce should have never been found."; idsuiv=1102; break;
        case 1102: texte = "Listen to me carefully Link, a long long time ago now, Agahnim disappeared after he left the order of the wisemen."; idsuiv=1103; break;
        case 1103: texte = "The day he came back, he was gifted with very dark power. As a wiseman, he would never have been able to shoot fire ball, his speciality was rabbits..."; idsuiv=1104; break;
        case 1104: texte = "I owed too much to Agahnim to put up to him, but I made inquiry while we were looking for the crystals."; idsuiv=1105; break;
        case 1105: texte = "It seems like he got his powers from an entity far more dangerous and powerful than I never could be"; idsuiv=1106; break;
        case 1106: texte = "There are still in Hyrule places you didn't explored and enemies you didn't fight. Youre quest is not finished yet..."; idsuiv=1107; break;
        case 1107: texte = "You want to know why i'm telling you all of that? *I guess I ain't gonna get out of it that easily, after what I've done..."; idsuiv=1108; break;
        case 1108: texte = "If I fail today, someone will have to avenge Aghanim instead of me. *But..."; idsuiv=1109; break;
        case 1109: texte = "... will you be able to?"; break;
        case 1110: texte = "You have found the Triforce!!!"; break;
        case 1111: texte = "That's how Ganondorf was defeated forever. The Triforce was once again get back and kept safe in the castle. **However, concerned by Ganondorf's last words, Link spent the rest of his life watching over Hyrule. ***End of the First Quest."; break;
        case 1112: texte = "Ganon has recovered a human form... *is he still our enemy?"; break;
        case 1113: texte = "Ready for a last duel?"; break;
	case 1114: 
            if (gpJeu->getMonde()->motifValue(69*16,90*16) == 6380) {texte = "Welcome to the Casino !"; break;}
            texte = "Welcome dear guest, the entry fee is 10 Golden Ganon, are you okay with that?*              YES ?            no  "; idsuiv=1117; break;
        case 1115: texte = "Welcome dear guest, the entry fee is 10 Golden Ganon, are you okay with that?*              yes              NO ?"; idsuiv=1116; break;
        case 1116: texte = "Too bad."; break;
        case 1117: 
            if (gpJeu->getMonde()->motifValue(69*16,90*16) != 6380 &&
            gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) {id=1118; chercheText();break;}
            texte = "Welcome in the Casino!"; break;
        case 1118: texte = "Be back when you have money my friend."; break;
        case 1119: texte = "We are closed for now, come back later."; break;
        case 1120: texte = "Welcome in the family Casino, do you want me to explain you the game rules for 5 Golden Ganon?*              YES ?            no  "; idsuiv=1122; break;
        case 1121: texte = "Welcome in the family Casino, do you want me to explain you the game rules for 5 Golden Ganon?*              yes              NO ?"; idsuiv=1116; break;
        case 1122: 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5) {id=1118; chercheText();break;}
            texte = "In this casino, enemies won't take you energy but money. Each attack makes you lose a little more life than the last one."; idsuiv=1123; break;
        case 1123: texte = "You don't have a rupee left, you're expeled. We're not interested by broke clients."; idsuiv=1124; break;
        case 1124: texte = "However, if you win the various games in the casino, you will win marvelous prices."; break;
        case 1125: 
            if (gpJeu->getJoueur()->getCoffre(12,1)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Strike the enemies to stop them on a mark. Get the 4 different marks and you'll win the price."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1126: texte = "Do you want to try for 10 Golden Ganon?**              YES ?            no  "; break;
        case 1127: texte = "Do you want to try for 10 Golden Ganon?**              yes              NO ?"; idsuiv=1116; break;
        case 1128: texte = "You already won this game."; break;
        case 1129: texte = "Congratulation!*Here is your price:"; break;
        case 1130: texte = "You will probably be more lucky next time."; break;
        case 1131:
            if (gpJeu->getJoueur()->getCoffre(12,2)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1132; chercheText();break;}
            texte = "Strike the enmies to stop them on a figure. Get a 4, a 2 and a 1 and you'll get the price."; 
            buffer="Talk to me if you fail, you'll just start again with the right numbers you've already found."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1132: texte = "Do you want to complete for 5 Golden Ganon?**              YES ?            no  "; break;
        case 1133: texte = "Do you want to complete for 5 Golden Ganon?**              yes              NO ?"; idsuiv=1116; break;
        case 1134:
            if (gpJeu->getJoueur()->getCoffre(12,5)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->isTempsVisible()) {id=1135; chercheText();break;}
            texte = "This is the Casino Great Race's starting line, you've got 21 seconds to reach the finishing line."; 
            idsuiv=1126; break;
        case 1135: texte = "You're losing time there, you know?"; break;
        case 1136:
            if (gpJeu->getJoueur()->getCoffre(12,5)) {id=1128; chercheText();break;}
            texte = "This is the Casino Great Race's finishing line. Go to the starting line if you want to break the record."; break;
        case 1137:
            if (gpJeu->getJoueur()->getCle(12,0)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Strike the enemies to stop them on a figure and get more than I do with one die less."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1138:
            if (gpJeu->getJoueur()->getCoffre(12,4)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Chose a figure, eather 1, or 6. I will throw 4 dices, if your figure is in, you win, if not, you pay 10 time the difference with the closest dice."; 
            idsuiv=1139; break;
        case 1139: texte = "Do you want to try?**              YES ?            no  "; idsuiv=1141; break;
        case 1140: texte = "Do you want to try?**              yes              NO ?"; idsuiv=1116; break;
        case 1141: texte = "Which figure do you chose?**              ONE  ?            six  "; break;
        case 1142: texte = "Which figure do you chose?**              one               SIX ?"; break;
        case 1143:
            if (gpJeu->getJoueur()->getCle(12,1)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Strike the enemy to stop them on a figure that will be handed over to a block on the right. The push the blocks so that they arrive at 0 onto the flagstones."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1144:
            if (gpJeu->getJoueur()->getCoffre(12,3)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) > 1) {id=1145; chercheText();break;}
            texte = "I sell you a key for a price equal to the sum of your four dices times the amount of mine."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1145:
            tmp = gpJeu->getJoueur()->getCoffre(12,13)-2; os << tmp;
            texte = "I sell you a key for "+os.str()+" Golden Ganon, are you okay with that?*              YES ?            no  "; idsuiv=1129; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<tmp) {idsuiv=1118;break;}
            break;
        case 1146:
            tmp = gpJeu->getJoueur()->getCoffre(12,13)-2; os << tmp;
            texte = "I sell you a key for "+os.str()+" Golden Ganon, are you okay with that?*              yes              NO ?"; idsuiv=1116; break;
            break;
        case 1147:
            if (gpJeu->getJoueur()->getCle(12,2)) {id=1148; chercheText();break;}
            texte = "The Chest room is at the end of the corridor on the left. Only the best customers may hope to reach it.";
            break;
        case 1148: 
            if (gpJeu->getJoueur()->getCoeur(11)) {id=1149; chercheText();break;}
            texte = "Did you open the chest?*Then now you should try the Special Room."; break;
        case 1149: texte = "People like you have got nothing to do in a casino...*We are broke..."; break;
        case 1150: texte = "Welcome to the Casino Great Quiz!"; idsuiv=1151; break;
        case 1151: texte = "Here I'm the one asking questions, and bad answers are expensive."; idsuiv=1152; break;
        case 1152: 
            gpJeu->getJoueur()->setCoffre(12,14,0); // ->nb questions posées
            for (int i = 0; i < MAX_QUIZZ; i++) gpJeu->getJoueur()->setCoffre(12,15+i,0);
            tmp = rand()%MAX_QUIZZ; idsuiv = 1154 + tmp*4;
            gpJeu->getJoueur()->setCoffre(12,15+tmp,1);
            texte = "I don't ask you if you want to play, I'm a boss after all.*So let's get it started..."; 
            break;
        case 1153: 
            if ((MAX_QUIZZ-gpJeu->getJoueur()->getCoffre(12,14)) > 0) {
                tmp = rand()%(MAX_QUIZZ-gpJeu->getJoueur()->getCoffre(12,14));
                for (int i = 0; i <= tmp; i++) {
                    if (gpJeu->getJoueur()->getCoffre(12,15+i) > 0) {
                        tmp++;
                    }
                } 
                idsuiv=1154+tmp*4;
                gpJeu->getJoueur()->setCoffre(12,15+tmp,1);
            }
            texte = "Next question..."; break;
        case 1154: texte = "This casino houses a total of 6 different games without this quiz, right?*              RIGHT ?          wrong  "; idsuiv=1157; break;
        case 1155: texte = "This casino houses a total of 6 different games without this quiz, right?*              right            WRONG ?"; idsuiv=1156; break;
        case 1156: texte = "Correct! There are 7 games, 1 for the map, 1 for the compass and 5 for the keys."; break;
        case 1157: texte = "No! There are 7 games, 1 for the map, 1 for the compass and 5 for the keys."; break;
        
        case 1158: texte = "The guy in the cofee house never drinks more than 16 cofeecups a day, right?*             RIGHT ?          wrong  "; idsuiv=1161; break;
        case 1159: texte = "The guy in the cofee house never drinks more than 16 cofeecups a day, right?*             right            WRONG ?"; idsuiv=1160; break;
        case 1160: texte = "Correct! He can go up to 17 cups!"; break;
        case 1161: texte = "No! He can go up to 17 cups!"; break;
        
        case 1162: texte = "This game contains a total of 150 power gems, right?*             RIGHT ?          wrong  "; idsuiv=1165; break;
        case 1163: texte = "This game contains a total of 150 power gems, right?*             right            WRONG ?"; idsuiv=1164; break;
        case 1164: texte = "Correct! There are 200."; break;
        case 1165: texte = "No! There are 200."; break;
        
        case 1166: texte = "There are only 7 houses left in the middle village, is that so?*             RIGHT ?          wrong  "; idsuiv=1168; break;
        case 1167: texte = "There are only 7 houses left in the middle village, is that so?*             right            WRONG ?"; idsuiv=1169; break;
        case 1168: texte = "Correct! The 3 others are destroyed."; break;
        case 1169: texte = "No! There are 10 houses, 3 of them are destroyed, so only 7 are left."; break;

        case 1170: 
            tmp = gpJeu->getJoueur()->getMort() + 1; os << tmp;
            texte = "You died "+os.str()+" times, am I right?**             RIGHT ?          wrong  "; idsuiv=1173; break;
        case 1171: 
            tmp = gpJeu->getJoueur()->getMort() + 1; os << tmp;
            texte = "You died "+os.str()+" times, am I right?**             right            WRONG ?"; idsuiv=1172; break;
        case 1172: 
            tmp = gpJeu->getJoueur()->getMort(); os << tmp;
            texte = "Correct! You died "+os.str()+" times."; break;
        case 1173: 
            tmp = gpJeu->getJoueur()->getMort(); os << tmp;
            texte = "No! You died "+os.str()+" times."; break;
            
        case 1174: texte = "14 bad answers are enough to make lose any player, right?*             RIGHT ?          wrong  "; idsuiv=1176; break;
        case 1175: texte = "14 bad answers are enough to make lose any player, right?*             right            WRONG ?"; idsuiv=1177; break;
        case 1176: texte = "Correct! 14 bad answer make lose minimum 1050 Golden Ganon out of 999 transportable."; break;
        case 1177: texte = "No! 14 bad answer make lose minimum 1050 Golden Ganon out of 999 transportable."; break;
        
        case 1178: texte = "I'm the coolest boss in the game, right?**             RIGHT ?          wrong  "; idsuiv=1180; break;
        case 1179: texte = "I'm the coolest boss in the game, right?**             right            WRONG ?"; idsuiv=1181; break;
        case 1180: texte = "Ha! Ha! We agree."; break;
        case 1181: texte = "... *This one is wrong, on principle..."; break;
        
        case 1182: texte = "Only 3 dungeons in the past are necessary to finish the game, right? *             RIGHT ?          wrong  "; idsuiv=1184; break;
        case 1183: texte = "Only 3 dungeons in the past are necessary to finish the game, right? *             right            WRONG ?"; idsuiv=1185; break;
        case 1184: texte = "Correct! Temple of the air, temple of fire and the Goddesses Temple."; break;
        case 1185: texte = "No! There are 2 indeed, the temple of the air, temple of fire and the Goddesses Temple."; break;
        
        case 1186: texte = "More than 4000 Golden Ganon are necessary to get all of the fat fairy's prices, right?*            RIGHT ?          wrong  "; idsuiv=1189; break;
        case 1187: texte = "More than 4000 Golden Ganon are necessary to get all of the fat fairy's prices, right?*            right            WRONG ?"; idsuiv=1188; break;
        case 1188: texte = "Correct! 3798 are enough."; break;
        case 1189: texte = "No! 3798 are enough."; break;
        
        case 1190: texte = "In Zelda's time, the palace had 80 pillars, right?*             RIGHT ?          wrong  "; idsuiv=1192; break;
        case 1191: texte = "In Zelda's time, the palace had 80 pillars, right?*             right            WRONG ?"; idsuiv=1193; break;
        case 1192: texte = "Correct! There were 80 indeed."; break;
        case 1193: texte = "No! There were actually 80."; break;
        
        case 1194: 
            tmp = gpJeu->getJoueur()->getCoffre(12,14) + 1; os << tmp;
            texte = "You already answered "+os.str()+" of my questions, is that so?*             RIGHT ?          wrong  "; idsuiv=1197; break;
        case 1195: 
            tmp = gpJeu->getJoueur()->getCoffre(12,14) + 1; os << tmp;
            texte = "You already answered "+os.str()+" of my questions, is that so?*             right            WRONG ?"; idsuiv=1196; break;
        case 1196: texte = "Correct! But now you did."; break;
        case 1197: texte = "No! But now you did."; break;
        
        case 1198: texte = "You can find a maximum of 16 pieces of heart in this game, right?*             RIGHT ?          wrong  "; idsuiv=1200; break;
        case 1199: texte = "You can find a maximum of 16 pieces of heart in this game, right?*             right            WRONG?"; idsuiv=1201; break;
        case 1200: texte = "Correct! There are 16 in all."; break;
        case 1201: texte = "No! There are 16 in all."; break;
        
        case 1202: texte = "A blue potion costs the equivalent of 40 Rupees plus 40 Golden Ganon plus 10 Gold Coins, right?*             RIGHT ?          wrong  "; idsuiv=1204; break;
        case 1203: texte = "A blue potion costs the equivalent of 40 Rupees plus 40 Golden Ganon plus 10 Gold Coins, right?*             right            WRONG ?"; idsuiv=1205; break;
        case 1204: texte = "Correct! That is 160 Rupees."; break;
        case 1205: texte = "No! This equals 160 Rupees, so the price of a blue potion."; break;
        
        case 1206: texte = "In the mine, the trolley's track could change with 3 levers, right?*             RIGHT ?          wrong  "; idsuiv=1209; break;
        case 1207: texte = "In the mine, the trolley's track could change with 3 levers, right?*             right            WRONG ?"; idsuiv=1208; break;
        case 1208: texte = "Correct! There were 2 only."; break;
        case 1209: texte = "No! There were 2 only."; break;
        
        case 1210: texte = "You had to find 3 different kinds of fish to win the angling contest, right?*             RIGHT ?          wrong  "; idsuiv=1213; break;
        case 1211: texte = "You had to find 3 different kinds of fish to win the angling contest, right?*             right            WRONG ?"; idsuiv=1212; break;
        case 1212: texte = "Correct! You needed 5."; break;
        case 1213: texte = "No! You needed 5."; break;
        
        case 1214: texte = "Only the Master Sword is able to throw back the projectiles, right?*             RIGHT ?          wrong  "; idsuiv=1217; break;
        case 1215: texte = "Only the Master Sword is able to throw back the projectiles, right?*             right            WRONG ?"; idsuiv=1216; break;
        case 1216: texte = "Correct! Your current sword can do that too."; break;
        case 1217: texte = "No! Your current sword can do that too."; break;
        
        case 1218: texte = "Zelda is taller than you, true?**             RIGHT ?          wrong  "; idsuiv=1221; break;
        case 1219: texte = "Zelda is taller than you, true?**             right            WRONG ?"; idsuiv=1220; break;
        case 1220: texte = "Correct! You are a pixel more."; break;
        case 1221: texte = "No! You are a pixel more."; break;
        
        case 1222: texte = "The dungeon 3 has 3 floors, right?**             RIGHT ?          wrong  "; idsuiv=1224; break;
        case 1223: texte = "The dungeon 3 has 3 floors, right?**             right            WRONG ?"; idsuiv=1225; break;
        case 1224: texte = "Correct! And one only for the boss."; break;
        case 1225: texte = "No! 2 floors plus 1 for the boss, so 3."; break;
        
        case 1226: texte = "Link's demonic incarnation is a pink bunny, right?*             RIGHT ?          wrong  "; idsuiv=1229; break;
        case 1227: texte = "Link's demonic incarnation is a pink bunny, right?*             right            WRONG ?"; idsuiv=1228; break;
        case 1228: texte = "Correct! It's Oni Link."; break;
        case 1229: texte = "No! It's Oni Link."; break;
        
        case 1230: texte = "Tingle should never had existed, right?**             RIGHT ?          wrong  "; idsuiv=1232; break;
        case 1231: texte = "Tingle should never had existed, right?**             right            WRONG ?"; idsuiv=1233; break;
        case 1232: texte = "Er... we're wandering from the point there, but I'll say it's okay."; break;
        case 1233: texte = "... *To me, he shouldn't have."; break;
        
        case 1234: texte = "You want to give me Golden Ganon, right?**             RIGHT ?          wrong  "; idsuiv=1237; break;
        case 1235: texte = "You want to give me Golden Ganon, right?**             right            WRONG ?"; idsuiv=1236; break;
        case 1236: texte = "Correct! Alas..."; break;
        case 1237: texte = "Thanks!"; break;
        
        case 1238: texte = "Snakes' bites leave you half a heart no matter your life and defense, right?*             RIGHT ?          wrong  "; idsuiv=1241; break;
        case 1239: texte = "Snakes' bites leave you half a heart no matter your life and defense, right?*             right            WRONG ?"; idsuiv=1240; break;
        case 1240: texte = "Correct! If you had only half a heart left, the bite leaves you nothing."; break;
        case 1241: texte = "No! If you had only half a heart left, the bite leaves you nothing."; break;
        
        case 1242: texte = "Link's property has 77 grass tuft, right?**             RIGHT ?          wrong  "; idsuiv=1244; break;
        case 1243: texte = "Link's property has 77 grass tuft, right?**             right            WRONG ?"; idsuiv=1245; break;
        case 1244: texte = "Correct! Happy to see I'm not the only who have counted them!"; break;
        case 1245: texte = "Non! Do you realize I know your property better than you do???"; break;
        
        case 1246: texte = "2 to the power of 12 is smaller than the cube root of 7, is that so?*             RIGHT ?          wrong  "; idsuiv=1249; break;
        case 1247: texte = "2 to the power of 12 is smaller than the cube root of 7, is that so?*             right            WRONG ?"; idsuiv=1248; break;
        case 1248: texte = "Correct! Well, I think."; break;
        case 1249: texte = "No! I think it's the other way around."; break;
        
        case 1250: texte = "It is possible to finish the game moving only in moonwalk, right?*             RIGHT ?          wrong  "; idsuiv=1253; break;
        case 1251: texte = "It is possible to finish the game moving only in moonwalk, right?*             right            WRONG ?"; idsuiv=1252; break;
        case 1252: texte = "Correct! But you can try if you want."; break;
        case 1253: texte = "No! Well, you shall try..."; break;
        
        case 1254: texte = "It's in the past when you can win the most money by killing an enemy, right?*             RIGHT ?          wrong  "; idsuiv=1257; break;
        case 1255: texte = "It's in the past when you can win the most money by killing an enemy, right*             right            WRONG ?"; idsuiv=1256; break;
        case 1256: texte = "Correct! It's in the present, with red Rupees."; break;
        case 1257: texte = "No! It's in the present, with red Rupees."; break;
        
        case 1258: texte = "Your sword can defeat any opponent, exept a boss, in less that 6 blows, right?*             RIGHT ?          wrong  "; idsuiv=1261; break;
        case 1259: texte = "Your sword can defeat any opponent, exept a boss, in less that 6 blows, right?*             right            WRONG ?"; idsuiv=1260; break;
        case 1260: texte = "Correct! There are enemies that can't be killed with the sword."; break;
        case 1261: texte = "No! There are enemies that can't be killed with the sword."; break;
        
        case 1262: texte = "The puzzle in the desert had 6 stones, didn't it?*             RIGHT ?          wrong  "; idsuiv=1264; break;
        case 1263: texte = "The puzzle in the desert had 6 stones, didn't it?*             right           WRONG ?"; idsuiv=1265; break;
        case 1264: texte = "Correct! And I never could find the order..."; break;
        case 1265: texte = "No! You cheated to solve it, I'm sure..."; break;
        
        case 1266: 
            tmp = gpJeu->getJoueur()->getTemps(2); os << tmp;
            texte = "You played more than "+os.str()+" hours, right?**             RIGHT ?          wrong  "; idsuiv=1268; break;
        case 1267: 
            tmp = gpJeu->getJoueur()->getTemps(2); os << tmp;
            texte = "You played more than "+os.str()+" hours, right?**             right            WRONG ?"; idsuiv=1269; break;
        case 1268: texte = "Correct! It goes by fast, doesn't it?"; break;
        case 1269: texte = "No! It goes by fast, doesn't it?"; break;
        
        case 1270: texte = "The hens in the past are more patient than the ones in the present, right?*             RIGHT ?          wrong  "; idsuiv=1273; break;
        case 1271: texte = "The hens in the past are more patient than the ones in the present, right?*             right            WRONG ?"; idsuiv=1272; break;
        case 1272: texte = "Correct! You know your stuff..."; break;
        case 1273: texte = "No! You'll just have to check..."; break;
        
        case 1274: texte = "It was possible to catch 4 different fishes in the Lake Hylia, right?*             RIGHT ?          wrong  "; idsuiv=1276; break;
        case 1275: texte = "It was possible to catch 4 different fishes in the Lake Hylia, right?*             right            WRONG ?"; idsuiv=1277; break;
        case 1276: texte = "Correct! There were 6 different species."; break;
        case 1277: texte = "No! There were 6 different species, so it was possible to find 4."; break;
        
        case 1278: texte = "Santa Claus exists, is that true?**             RIGHT ?          wrong  "; idsuiv=1280; break;
        case 1279: texte = "Santa Claus exists, is that true?**             right            WRONG ?"; idsuiv=1281; break;
        case 1280: texte = "Correct! And you met him once."; break;
        case 1281: texte = "No! You met him once."; break;
        
        case 1282: texte = "In the past, the mountains had a total of 16 stones, right?*             RIGHT ?          wrong  "; idsuiv=1285; break;
        case 1283: texte = "In the past, the mountains had a total of 16 stones, right?*             right            WRONG ?"; idsuiv=1284; break;
        case 1284: texte = "Correct! There were 15 only, obviously."; break;
        case 1285: texte = "No! There were 15 only, obviously."; break;
        
        case 1286: texte = "There is a total of 42 carpets in this Casino, right? *             RIGHT ?          wrong  "; idsuiv=1289; break;
        case 1287: texte = "There is a total of 42 carpets in this Casino, right? *             right            WRONG ?"; idsuiv=1288; break;
        case 1288: texte = "Correct! There are 44."; break;
        case 1289: texte = "No! There are 44."; break;
        
        case 1290: texte = "Power gems can be swaped for 5 different type of items, right?*             RIGHT ?          wrong  "; idsuiv=1292; break;
        case 1291: texte = "Power gems can be swaped for 5 different type of items, right?*             right            WRONG ?"; idsuiv=1293; break;
        case 1292: texte = "Correct! I see you did not forget the frosty rock."; break;
        case 1293: texte = "No! You probably forgot the frosty rock."; break;
        
        case 1294: texte = "The green tunic gives you but one point of defense, right?*             RIGHT ?          wrong  "; idsuiv=1297; break;
        case 1295: texte = "The green tunic gives you but one point of defense, right?*             right            WRONG ?"; idsuiv=1296; break;
        case 1296: texte = "Correct! The green tunic is your first one and gives no point of defense."; break;
        case 1297: texte = "No! The green tunic is your first one and gives no point of defense."; break;
        
        case 1298: texte = "There were 5 mirrors in Zelda's bedroom, right?*             RIGHT ?          wrong  "; idsuiv=1300; break;
        case 1299: texte = "There were 5 mirrors in Zelda's bedroom, right?*             right            WRONG ?"; idsuiv=1301; break;
        case 1300: texte = "Correct! You gave her the fifth one actually."; break;
        case 1301: texte = "No! In fact you gave her the fifth one."; break;
        
        case 1302: texte = "The Pyramid in the past had 85 rooms, right?**             RIGHT ?          wrong  "; idsuiv=1305; break;
        case 1303: texte = "The Pyramid in the past had 85 rooms, right?**             right            WRONG ?"; idsuiv=1304; break;
        case 1304: texte = "Correct! 84 only."; break;
        case 1305: texte = "No! 84 only."; break;
        
        case 1306: texte = "The fire arrows are strongest than the ice ones, right?*             RIGHT ?          wrong  "; idsuiv=1308; break;
        case 1307: texte = "The fire arrows are strongest than the ice ones, right?*             right            WRONG ?"; idsuiv=1309; break;
        case 1308: texte = "Correct! The fire arrows have a strength of 10, the ice ones have 7."; break;
        case 1309: texte = "No! The fire arrows have a strength of 10, the ice ones have 7."; break;
        
        case 1310: texte = "Bombs cause as many damage as hammer blows, right?*             RIGHT ?          wrong  "; idsuiv=1313; break;
        case 1311: texte = "Bombs cause as many damage as hammer blows, right?*             right            WRONG ?"; idsuiv=1312; break;
        case 1312: texte = "Correct! Bombs have a strength of 5, the hammer of 3."; break;
        case 1313: texte = "No! Bombs have a strength of 5, the hammer of 3."; break;
        
        case 1314: texte = "What??? You defeated me???**             RIGHT ?          right  "; break;
        case 1315: texte = "What??? You defeated me???**             right            RIGHT ?"; break;
        
        case 1316: texte = "You have found the Shield of the Goddesses!!!*Now your life comes back constantly!!!"; break;
        case 1317: texte = "On this stone is written the story of Hyrule in ancient Hylian:"; idsuiv=1318; break;
        case 1318: texte = "After the Goddesses Din, Nayru and Farore created Hyrule, an evil entity with an unequaled power came to occupy this land."; idsuiv=1319; break;
        case 1319: texte = "Despite of their great powers, the Goddesses had to accept that they could never destroy this creature."; idsuiv=1320; break;
        case 1320: texte = "...*The continuation of the story is not written here. Maybe on another stone?"; break;
        
        case 1321: texte = "You have found the Tunic of the Goddesses!!!*Now your magic comes back constantly!!!"; break;
        case 1322: texte = "On this stone is written the story of Hyrule in ancient Hylian:"; idsuiv=1323; break;
        case 1323: texte = "Din, Nayru and Farore could not resolve to do nothing, and they challenged the evil entity."; idsuiv=1324; break;
        case 1324: texte = "After a long and hopeless fight, they had to find a compromise and they managed to scatter the entity's power."; idsuiv=1325; break;
        case 1325: texte = "However, in order to do so, they had to create devilish creatures holding fragments of the entity's power."; idsuiv=1326; break;
        case 1326: texte = "What was left of the evil entity is locked in a human form, and shall not be set free as long as all the devilish creatures are not defeated."; break;
		
		case 1327: texte = "Welcome among us, do you want me to explain you how does this play work?*              YES ?            no  "; idsuiv=1329; break;
        case 1328: texte = "Welcome among us, do you want me to explain you how does this play work?*              yes              NO ?"; idsuiv=1332; break;
        case 1329: texte = "Enemies in this dungeon are very particular, each of their attack will make you lose twice more than the previous blow."; idsuiv=1330; break; 
        case 1330: texte = "Be extremly carefull, 7 blows will be enough to kill you."; idsuiv=1331; break;
        case 1331: texte = "Plus, the number of enemy you kill, as for the number of type of enemy, are counted. A certain amount is needed to open some doors."; idsuiv=1332; break;
        case 1332: texte = "Good luck Link, whatever happens everything end here."; break;
        
        case 1333:
            if (gpJeu->getJoueur()->getCoffre(14,9)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 30 && gpJeu->getJoueur()->getCompteurType() >= 4) {id=1335; chercheText();break;}
            texte = "Eliminateat least 30 enemies of 4 various types and I will open the door."; break;
        case 1334: texte = "Good luck Link."; break;
        case 1335: texte = "You have defeated enough enemies, I shall open..."; break;
        case 1336:
            if (gpJeu->getJoueur()->getCoffre(14,10)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 60 && gpJeu->getJoueur()->getCompteurType() >= 10) {id=1335; chercheText();break;}
            texte = "Eliminate at least 60 enemies of 10 various types and I will open the door."; break;
        case 1337:
            if (gpJeu->getJoueur()->getCoffre(14,11)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 20 && gpJeu->getJoueur()->getCompteurType() >= 3) {id=1335; chercheText();break;}
            texte = "Eliminate at least 20 enemies de 3 various types and I will open the door."; break;
        case 1338:
            if (gpJeu->getJoueur()->getCoffre(14,12)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 99 && gpJeu->getJoueur()->getCompteurType() >= 12) {id=1335; chercheText();break;}
            texte = "Eliminate at least 99 enemies of 12 various types and I will open the door."; break;
        case 1339:
            if (gpJeu->getJoueur()->getCoffre(14,13)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 30 && gpJeu->getJoueur()->getCompteurType() >= 12) {id=1335; chercheText();break;}
            texte = "Eliminate at least 30 enemies of 12 various types and I will open the door."; break;
        case 1340:
            if (gpJeu->getJoueur()->getCoffre(14,14)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 40 && gpJeu->getJoueur()->getCompteurType() >= 6) {id=1335; chercheText();break;}
            texte = "Eliminate at least 40 enemies of various 6 types and I will open the door."; break;
        case 1341:
            if (gpJeu->getJoueur()->getCoffre(14,15)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 50 && gpJeu->getJoueur()->getCompteurType() >= 7) {id=1335; chercheText();break;}
            texte = "Eliminate at least 50 enemies of 7 various types and I will open the door."; break;
        case 1342: texte = "You have found the Mask of Oni Link !!! *Use 'O' to transform yourself and become incredibly powerful."; break;
        case 1343: texte = "Congratulations Link! You've defeated every single type of enemy... It's incredible..."; idsuiv=1344; break;
        case 1344: texte = "I owe you a lot, do you want to be paid now?"; idsuiv=1345; break;
        case 1345: texte = "I'm finally able to take back my original form, be ready to take a lot!*Farewell, Hero of Hyrule!"; break;
        case 1346: 
            if (gpJeu->nbEnnemis()==0) {id=1348; chercheText();break;}
            texte = "Hurry Link! Use the Sword of the Godesses to finish him off definitely!"; break;
        case 1347: 
            if (gpJeu->nbEnnemis()==0) {id=1349; chercheText();break;}
            if (gpJeu->getEnnemi()->getSuivant()->getSpecial(2)<13) {id=1350; chercheText();break;}
            texte = "Not on me, goofy..."; break;
        case 1348: texte = "Congratulations Link, let's go home now."; break;
        case 1349: texte = "Justice has been done. My Master is finally avenged."; break;
        case 1350: texte = "Out of my way!"; break;
        case 1351: texte = "What the hell are you doing?"; break;
        case 1352: texte = "Let me explain you the reason of our presence in the entity with no name's dungeon."; idsuiv=1353; break;
        case 1353: texte = "After your departure from the Castle that followed my victory upon Ganon, Ganondorf gave me back the Triforce and told me his story."; idsuiv=1354; break;
        case 1354: texte = "We quickly came to the conclusion that the man of the monster's encyclopedia was highly suspicious, so when we learned from a guard that you had gone to see him, we decided to come to your help."; idsuiv=1355; break;
        case 1355: texte = "As we thought, only the power of the 3 Weapons of the Goddesses unified and used by the 3 Chosen ones could destroyed this plague forever."; idsuiv=1356; break;
        case 1356: texte = "As for Ganondorf, he has nothing to see now with the monster we knew, there is no darkness in him anymore, and he is trustworthy."; idsuiv=1357; break;
        case 1357: texte = "From now on Hyrule is in peace, for good. Monsters will never reappear again, Evil is definitely defeated."; idsuiv=1358; break;
        case 1358: texte = "So tell me Link, what are you gonna do of your days off?"; break;
        case 1359: texte = "Hyrule was saved and every threat dispeled. After long adventures, the three heroes had accomplished their destiny. **The three Goddesses came back in Hyrule to congratulate them, and then left again, taking the Triforce with them. **The powerful Ganondorf became quickly the new chief of the guards and spent the rest of his days protecting the realm against enemies that never came."; idsuiv=1360; break;
        case 1360: texte = "Princess Zelda was celebrated accross the entire country and far more away as being the sovereign that had brought peace on the world. **Link prefered to fly away from celebrity, he disappeared, and no one ever saw him in Hyrule again."; break;
        case 1361: texte = "After the events that occured in Termina, Princess Zelda put an end to Link's exile, announcing to the people the victory of the hero on his evil alter-ego."; idsuiv=1362; break;
        case 1362: texte = "But the Hylian knight, unable to accept his status of hero, left to live as an ermit in a forest given to him by the princess."; idsuiv=1363; break;
        case 1363: texte = "The existence of Termina had to be kept secret, therefore the princess hid the events that took place there and let the people living in an illusory peace."; idsuiv=1364; break;
        case 1364: texte = "But both of them perfectly knew that, from the bottom of hell, Ganon the immortal drawed his power from his"; buffer="first wish to the Triforce, and rounded up his army with a view to invade Hyrule."; idsuiv=1365; break;
        case 1365: texte = "Until the day when, after months spent watching out for an attack, an event came up and put an end to this endless waiting..."; break;
        case 1366: texte = "HELLOOO !!! *MY LORD LINK !!!"; break;
        case 1367: texte = "HELP : Press L and Y to consult the help."; break;
        case 1368: texte = "Come back when you'll have a wallet and we'll talk business."; break;
        case 1369: texte = "We heard sounds of battle, and nothing more..."; break;
        case 1370: texte = "What, by all heavens, can have happened?"; break;
		case 1371:
            tmp = 0;
            for (int i = 0; i < 9; i++) if (gpJeu->getKeyboard()->getRang(i)) tmp++;
            if (tmp == 9 && gpJeu->getJoueur()->getEnnemi(141)) {id=1372; chercheText();break;}
            texte = "This door leads to a secret room. *Get the 9 ranks in the Records screen and come back after having get the second end to penetrate it.";
            break;
        case 1372: texte = "You may go in, Legendary Hero."; break;
        case 1373: texte = "Welcome in 3T's hidden room!"; idsuiv=1374; break;
        case 1374: texte = "I am Vincent, I thought and encoded the game."; break;
        case 1375: texte = "Hi, I am Lobalùz. *I helped invent the game, made some new graphics, tested the majority of the dungeons, and translated the texts."; break;
        case 1376: texte = "Hello, I am Raiden! *I took care of drawing the illustrations of the game(... and also the clouds on the maps, but who cares actually...)."; idsuiv=1377; break;
        case 1377: texte = "We may find other drawings from me on the following adress : http://alandar.deviantart.com"; break;
        case 1378: texte = "Monsters sank my boat... *I'm sorry, you will have to swim now...";break;
    }
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        afficheLettre(gpScreen, s.at(i),a,b);
        a+=6;
    }
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3 && texte == "You have found a piece of heart!!!") {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        afficheLettre(gpScreen, texte.at(i),a,b);
        a+=6;
        if (a > x+w-16) {a=x+8; b+=16;}
    }
    
    if(SDL_GetTicks() > lastAnimTime + vitesse && def && av < (int)texte.length()) {
        lastAnimTime = SDL_GetTicks();
        do av++;
        while (av < (int)texte.length() && texte.at(av-1) == ' ');
        if (texte.at(av-1) != ' ') gpJeu->getAudio()->playSound(0,1);
    }
}

bool Texte::isFinished() {return (av==(int)texte.length());}

int Texte::getId() {return id;}

void Texte::changeId(int i) {
    id=i; idsuiv=0; buffer="";
    chercheText();
    decoupeText();
    if (av>(int)texte.length()) av=(int)texte.length();
}

void Texte::drawCadre(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=8; src.h=8; src.x = 103; src.y = 100; dst.x = x; dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.y = 109; src.w=8;
    for (int j = 8; j < h-8; j+=16) {
        dst.y = y + j;
        src.x = 103; dst.x = x; src.h=16;
        while (dst.y + src.h > y+h && src.h>0) src.h--;
        if (src.h>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
        src.x = 129; dst.x = x+w-8;
        if (src.h>0)SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.h=8; src.x = 103; src.y = 126; dst.x = x; dst.y = y+h-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit) {
    if (idTxt == 0) return;
    id = idTxt; 
    idsuiv = 0;
    buffer = "";
    chercheText();
    
    x = vx; y = vy; w = vw; h = vh;
    decoupeText();
        
    def=defil;
    if (def) av = 0;
    else av = texte.length();
    
    cadre = cadr;
    
    vitesse = vit;
}

void Texte::decoupeText() {
    //compte le nombre de caractères possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte à afficher; à chaque début de mot, 
    //vérifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isolés en début de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du début du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une étoile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot dépasse
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot à la ligne
                else while((i%nbcol) != 0) {texte.insert(i," "); i++;}
            }
        }
        
    }
    
    // si le texte est trop grand, on le coupe en deux
    if ((int)texte.length() > tailleMax) {
        buffer = texte.substr(tailleMax);
        texte = texte.substr(0, tailleMax);
    }
}

int Texte::tailleMot(int deb) {
    int i = deb;
    int total = 0;
    while (texte.at(i)!=' ') {total++; i++; if (i >= (int)texte.length()) return total;}
    return total;
}

void Texte::afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy) {
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;
    
    // /
    if(val==47) {src.x=52;src.y=151;}
    
    // @ hylien
    if(val==64) {src.x=4;src.y=151;}
            
    // + hylien
    if(val==43) {src.x=20;src.y=151;}
            
    // = hylien
    if(val==61) {src.x=36;src.y=151;}
            
    //minuscules a-z
    if(val>=97 && val<=122) {src.x=4+16*((val-97)%10); src.y=52+16*((val-97)/10);}
            
    //majuscules A-Z
    if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}   
    // ç
    if(val==-25) {src.x=148;src.y=34;}
    // é
    if(val==-23) {src.x=100;src.y=84;}
    // ê
    if(val==-22) {src.x=116;src.y=84;}
    // è
    if(val==-24) {src.x=132;src.y=84;}
    // ë
    if(val==-21) {src.x=132;src.y=151;}
    // à
    if(val==-32) {src.x=148;src.y=84;}
    // â
    if(val==-30) {src.x=148;src.y=103;}
    // ä
    if(val==-28) {src.x=148;src.y=135;}
    // î
    if(val==-18) {src.x=84;src.y=119;}
    // ï
    if(val==-17) {src.x=116;src.y=151;}
    // û
    if(val==-5) {src.x=84;src.y=103;}
    // ù
    if(val==-7) {src.x=148;src.y=151;}
    // ü
    if(val==-4) {src.x=116;src.y=135;}
    // ö
    if(val==-10) {src.x=132;src.y=135;}
    // ô
    if(val==-12) {src.x=148;src.y=119;}
            
    //ponctuation
    // -
    if(val==45) {src.x=102;src.y=34;}
    // .
    if(val==46) {src.x=118;src.y=34;}
    // ,
    if(val==44) {src.x=134;src.y=34;}
    // !
    if(val==33) {src.x=3;src.y=135;}
    // ?
    if(val==63) {src.x=19;src.y=135;}
    // (
    if(val==40) {src.x=35;src.y=135;}
    // )
    if(val==41) {src.x=51;src.y=135;}            
    // ' ( avec @ )
    if(val==39) {src.x=67;src.y=135;}
    // :
    if(val==58) {src.x=83;src.y=135;}
    // ... ( avec % )
    if(val==37) {src.x=101;src.y=135;}
    // >
    if(val==62) {src.x=100;src.y=151;}
    // <
    if(val==60) {src.x=84;src.y=151;}
            
    //chiffres            
    if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
    
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

bool Texte::hasNext() {
    return (buffer != "" || idsuiv > 0);
}

bool Texte::suite() {
    if (av < (int)texte.length()) {
        av = texte.length();
        return true;
    }
    if (!hasNext()) {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (buffer != "") {
        texte = buffer;
        buffer = "";
    }
    else {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def) av = 0;
    else av = texte.length();
    gpJeu->getAudio()->playSound(17);
    return true;
}
