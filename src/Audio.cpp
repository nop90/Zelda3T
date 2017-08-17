/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL/SDL.h>

#include "Audio.h"

Audio::Audio() : volume(0), musiqueId(0), specialId(0) {
	SDL_InitSubSystem(SDL_INIT_AUDIO);
    SOUND = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024)?0:1;
    music = NULL;
    
    if (SOUND) {
        previous_volume = 128;//-1;
        previous_volson = 128;//FSOUND_GetSFXMasterVolume();
        loadSounds();
    }
}

Audio::~Audio() {
    if (SOUND) {
        freeSounds();
        Mix_HaltMusic();
        Mix_VolumeMusic(previous_volume);
        Mix_FreeMusic(music);
        Mix_Volume(-1,previous_volson);
        Mix_CloseAudio();
    }
}

void Audio::setVolume(int vol) {volume=vol*4;
    if (previous_volume == -1) previous_volume = volume;//FMUSIC_GetMasterVolume(music);
     Mix_VolumeMusic( volume);}
void Audio::setVolson(int volson) {Mix_Volume(-1,volson*4);}

void Audio::loadSounds() {
    sons = new Mix_Chunk*[44];
    
    sons[0] = Mix_LoadWAV("romfs:/sound/text.ogg"); // lettres
    sons[1] = Mix_LoadWAV("romfs:/sound/menu1.ogg"); // menu 1
    sons[2] = Mix_LoadWAV("romfs:/sound/menu2.ogg"); // menu 2
    sons[3] = Mix_LoadWAV("romfs:/sound/menu3.ogg"); // menu 3
    sons[4] = Mix_LoadWAV("romfs:/sound/menu4.ogg"); // menu 4
    sons[5] = Mix_LoadWAV("romfs:/sound/timewarp.ogg"); // time retour
    sons[6] = Mix_LoadWAV("romfs:/sound/tombe.ogg"); // tombe (ennemi)
    sons[7] = Mix_LoadWAV("romfs:/sound/hitenemy.ogg"); //shot 1
    sons[8] = Mix_LoadWAV("romfs:/sound/killenemy.ogg"); // shot 2
    sons[9] = Mix_LoadWAV("romfs:/sound/surprise.ogg"); // surprise
    sons[10] = Mix_LoadWAV("romfs:/sound/monte.ogg"); // monte
    sons[11] = Mix_LoadWAV("romfs:/sound/descend.ogg"); // descend
    sons[12] = Mix_LoadWAV("romfs:/sound/chute.ogg"); // chute
    sons[13] = Mix_LoadWAV("romfs:/sound/item.ogg"); // item
    sons[14] = Mix_LoadWAV("romfs:/sound/rupee.ogg"); // rubis
    sons[15] = Mix_LoadWAV("romfs:/sound/heart.ogg"); // coeur
    sons[16] = Mix_LoadWAV("romfs:/sound/bomb.ogg"); // bombe
    sons[17] = Mix_LoadWAV("romfs:/sound/textnext.ogg"); // suite texte
    sons[18] = Mix_LoadWAV("romfs:/sound/textend.ogg"); // fin texte
    sons[19] = Mix_LoadWAV("romfs:/sound/happy.ogg"); // trouve objet
    sons[20] = Mix_LoadWAV("romfs:/sound/door.ogg"); // ouvre porte
    sons[21] = Mix_LoadWAV("romfs:/sound/pics.ogg"); // pics contre mur
    sons[22] = Mix_LoadWAV("romfs:/sound/sword.ogg"); // épée
    sons[23] = Mix_LoadWAV("romfs:/sound/SwordCharging.ogg"); // chargée
    sons[24] = Mix_LoadWAV("romfs:/sound/Sword360.ogg"); // spin
    sons[25] = Mix_LoadWAV("romfs:/sound/shoot.ogg"); // flèche
    sons[26] = Mix_LoadWAV("romfs:/sound/hookshot.ogg"); // grappin
    sons[27] = Mix_LoadWAV("romfs:/sound/stamp.ogg"); // pose bombe
    sons[28] = Mix_LoadWAV("romfs:/sound/magic.ogg"); // magie
    sons[29] = Mix_LoadWAV("romfs:/sound/burn.ogg"); // brûle
    sons[30] = Mix_LoadWAV("romfs:/sound/hammer.ogg"); // marteau
    sons[31] = Mix_LoadWAV("romfs:/sound/plouf.ogg"); // plouf
    sons[32] = Mix_LoadWAV("romfs:/sound/danger.ogg"); // danger
    sons[33] = Mix_LoadWAV("romfs:/sound/hurt.ogg"); // link se blesse
    sons[34] = Mix_LoadWAV("romfs:/sound/porte.ogg"); // porte objet
    sons[35] = Mix_LoadWAV("romfs:/sound/lance.ogg"); // lance objet
    sons[36] = Mix_LoadWAV("romfs:/sound/casse.ogg"); // casse objet
    sons[37] = Mix_LoadWAV("romfs:/sound/charge.ogg"); // charge magie
    sons[38] = Mix_LoadWAV("romfs:/sound/buisson.ogg"); // coupe buisson
    sons[39] = Mix_LoadWAV("romfs:/sound/pousse.ogg"); // pousse caisse
    sons[40] = Mix_LoadWAV("romfs:/sound/envol.ogg"); // chant envol
    sons[41] = Mix_LoadWAV("romfs:/sound/inverse.ogg"); // inversé
    sons[42] = Mix_LoadWAV("romfs:/sound/accelere.ogg"); // accéléré
    sons[43] = Mix_LoadWAV("romfs:/sound/splash.ogg"); // ...
    
}

void Audio::freeSounds() {
    if (SOUND) {
        for (int i = 0; i < 44; i++) Mix_FreeChunk(sons[i]);
        delete[] sons;
    }
}

void Audio::playSound(int id, int chl) {
    if (SOUND) //Mix_PlayChannel(chl,sons[id],0);
        Mix_PlayChannel(chl, sons[id],0);
}

void Audio::stopSound() {
    if (SOUND) {Mix_Pause(-1); musiqueId=0;}
}

void Audio::playMusic(int id) {
    if (SOUND) {
        if (id == 2 || id == 5 || id == 7 || id == 8 || id == 9 || id == 14) id = 1;
        if (id == 20 || id == 22 || id == 24) id = 17;
        if (id == 29) id = 19;
        if (id == 32 || id == 34 || id == 35 || id == 39 || id == 44) id = 31;
        if (id >= 61 && id <= 78) id = 61;
        if (id == 82 || id == 84 || id == 94 || id == 98 || id == 99
        || id == 101 || id == 107 || id == 108 || id == 109 || id == 112 
        || id == 117 || id == 118 || id == 122 || id == 128 || id == 129
        || id == 142 || id == 143 || id == 148 || id == 149) id = 81; //magasins
        if (id == 91 || id == 120 || id == 132) id = 85; //potions
        if (id == 102 || id == 136) id = 80; //bar
        if (id == 105 || id == 106 || id == 131 || id == 139 || id == 147) id = 95; //maire
        if (id == 152 || id == 153) id = 151; //temple temps
        if (musiqueId != id) {
            musiqueId = id;            
            if (specialId == 0) {
                Mix_HaltMusic();
                Mix_FreeMusic(music);
                music = choixMusique(id);
                if (previous_volume == -1) previous_volume = volume;
                Mix_VolumeMusic( volume);
                Mix_PlayMusic(music,-1);
                specialId = 0;
            }
        }
    }
}

bool Audio::isSpecial() {return (specialId>0);}

void Audio::stopMusic() {
    if (SOUND) Mix_HaltMusic();
}

void Audio::replayMusic() {
    if (SOUND) Mix_PlayMusic(music,-1);
}

Mix_Music* Audio::choixMusique(int id) {
    switch (id) {
        case 1 : case 2 : case 7 : return Mix_LoadMUS("romfs:/music/PlaineP.it");
        case 3 : return Mix_LoadMUS("romfs:/music/VilleCP.it");
        case 4 : return Mix_LoadMUS("romfs:/music/TerresS.it");
        case 6 : return Mix_LoadMUS("romfs:/music/BoisPerdus.it");
        case 8 : return Mix_LoadMUS("romfs:/music/CimetiereP.it");
        case 10 : return Mix_LoadMUS("romfs:/music/VillageMP.it");
        case 11 : return Mix_LoadMUS("romfs:/music/LacP.it");
        case 12 : return Mix_LoadMUS("romfs:/music/DesertP.it");
        case 13 : return Mix_LoadMUS("romfs:/music/Cocorico.it");
        case 15 : return Mix_LoadMUS("romfs:/music/MontP.it");
        case 16 : return Mix_LoadMUS("romfs:/music/Foret.it");
        case 17 : return Mix_LoadMUS("romfs:/music/Plaine.it");
        case 18 : return Mix_LoadMUS("romfs:/music/Cite.it");
        case 19 : return Mix_LoadMUS("romfs:/music/Chateau.it");
        case 21 : return Mix_LoadMUS("romfs:/music/Lanelle.it");
        case 23 : return Mix_LoadMUS("romfs:/music/Cimetiere.it");
        case 25 : return Mix_LoadMUS("romfs:/music/VillageM.it");
        case 26 : return Mix_LoadMUS("romfs:/music/Lac.it");
        case 27 : return Mix_LoadMUS("romfs:/music/Desert.it");
        case 28 : return Mix_LoadMUS("romfs:/music/VillageO.it");
        case 30 : return Mix_LoadMUS("romfs:/music/Mont.it");
        case 31 : case 32 : case 34 : case 35 :
            return Mix_LoadMUS("romfs:/music/Ombre.it");
        case 33 : return Mix_LoadMUS("romfs:/music/VilleF.it");
        case 36 : return Mix_LoadMUS("romfs:/music/BoisPerdusF.it");
        case 37 : return Mix_LoadMUS("romfs:/music/Cascades.it");
        case 38 : return Mix_LoadMUS("romfs:/music/CimetiereF.it");
        case 40 : return Mix_LoadMUS("romfs:/music/VillageMF.it");
        case 41 : return Mix_LoadMUS("romfs:/music/LacF.it");
        case 42 : return Mix_LoadMUS("romfs:/music/DesertF.it");
        case 43 : return Mix_LoadMUS("romfs:/music/VillageOF.it");
        case 45 : return Mix_LoadMUS("romfs:/music/MontF.it");
        case 46 : return Mix_LoadMUS("romfs:/music/Courage.it");
        case 47 : return Mix_LoadMUS("romfs:/music/Sagesse.it");
        case 48 : return Mix_LoadMUS("romfs:/music/Force.it");
        case 49 : return Mix_LoadMUS("romfs:/music/Abysses.it");
        case 50 : return Mix_LoadMUS("romfs:/music/PyramideF.it");
        case 51 : return Mix_LoadMUS("romfs:/music/PyramideP.it");
        case 52 : return Mix_LoadMUS("romfs:/music/Ordinn.it");
        case 53 : return Mix_LoadMUS("romfs:/music/Air.it");
        case 54 : return Mix_LoadMUS("romfs:/music/Glace.it");
        case 55 : return Mix_LoadMUS("romfs:/music/Feu.it");
        case 56 : return Mix_LoadMUS("romfs:/music/Titre.it");
        case 57 : return Mix_LoadMUS("romfs:/music/DFinal.it");
        case 58 : return Mix_LoadMUS("romfs:/music/Casino.it");
        case 59 : return Mix_LoadMUS("romfs:/music/Gemme.it");
        case 60 : return Mix_LoadMUS("romfs:/music/DestinationF.it");
        case 61 : return Mix_LoadMUS("romfs:/music/Cave.it");
        case 79 : return Mix_LoadMUS("romfs:/music/Home.it");
        case 80 : return Mix_LoadMUS("romfs:/music/Bar.it");
        case 81 : return Mix_LoadMUS("romfs:/music/Magasin.it");
        case 83 : return Mix_LoadMUS("romfs:/music/Maison.it");
        case 85 : return Mix_LoadMUS("romfs:/music/Potion.it");
        case 89 : return Mix_LoadMUS("romfs:/music/Jeu.it");
        case 95 : return Mix_LoadMUS("romfs:/music/Maire.it");
        case 119 : return Mix_LoadMUS("romfs:/music/Cafe.it");
        case 144 : return Mix_LoadMUS("romfs:/music/Sages.it");
        case 150 : return Mix_LoadMUS("romfs:/music/Opera.it");
        case 151 : return Mix_LoadMUS("romfs:/music/Epee.it");
        case 154 : return Mix_LoadMUS("romfs:/music/Prison.it");
        case 155 : return Mix_LoadMUS("romfs:/music/ChateauF.it");
        case 218 : return Mix_LoadMUS("romfs:/music/probleme.it");
        case 219 : return Mix_LoadMUS("romfs:/music/Epee.it");
        case 180 : return Mix_LoadMUS("romfs:/music/Titre.it");
        case 190 : return Mix_LoadMUS("romfs:/music/Selection.it");
        case 199 : return Mix_LoadMUS("romfs:/music/Nuit.it");
        case 200 : return Mix_LoadMUS("romfs:/music/Debut.it");
        default : return Mix_LoadMUS("romfs:/music/Maison.it");
    }
}

void Audio::playSpecial(int id) {
    if (SOUND) {
        if (specialId != id) {
                Mix_HaltMusic();
                Mix_FreeMusic(music);
            music = choixSpecial(id);
            if (previous_volume == -1) previous_volume = volume;
                Mix_VolumeMusic( volume);
                Mix_PlayMusic(music,-1);
            specialId=id;
        }    
    }
}

void Audio::stopSpecial() {
    if (!specialId) return;
    int tmp = musiqueId;
    musiqueId = 0;
    specialId = 0;
    playMusic(tmp);
}

Mix_Music* Audio::choixSpecial(int id) {
    switch (id) {
        case 1 : return Mix_LoadMUS("romfs:/music/Boss.it");
        case 2 : return Mix_LoadMUS("romfs:/music/Mort.it");
        case 3 : return Mix_LoadMUS("romfs:/music/Epee.it");
        case 4 : return Mix_LoadMUS("romfs:/music/BossF.it");
        case 5 : return Mix_LoadMUS("romfs:/music/Fin.it");
        case 6 : return Mix_LoadMUS("romfs:/music/BossM.it");
        case 7 : return Mix_LoadMUS("romfs:/music/Area81.it");
        case 8 : return Mix_LoadMUS("romfs:/music/OniLink.it");
        case 9 : return Mix_LoadMUS("romfs:/music/probleme.it");
        case 10 : return Mix_LoadMUS("romfs:/music/Harpie.it");
        case 11 : return Mix_LoadMUS("romfs:/music/Crabe.it");
        case 12 : return Mix_LoadMUS("romfs:/music/Imp.it");
        case 13 : return Mix_LoadMUS("romfs:/music/Masamune.it");
        case 14 : return Mix_LoadMUS("romfs:/music/ZoraS.it");
        case 15 : return Mix_LoadMUS("romfs:/music/Marlag.it");
        case 16 : return Mix_LoadMUS("romfs:/music/Fantomas.it");
        case 17 : return Mix_LoadMUS("romfs:/music/Vampire.it");
        case 18 : return Mix_LoadMUS("romfs:/music/Araignee.it");
        case 19 : return Mix_LoadMUS("romfs:/music/Plumes.it");
        case 20 : return Mix_LoadMUS("romfs:/music/Garuda.it");
        case 21 : return Mix_LoadMUS("romfs:/music/Heckran.it");
        case 22 : return Mix_LoadMUS("romfs:/music/Sun.it");
        case 23 : return Mix_LoadMUS("romfs:/music/Orcus.it");
        case 24 : return Mix_LoadMUS("romfs:/music/Agahnim.it");
        case 25 : return Mix_LoadMUS("romfs:/music/Zelda.it");
        case 26 : return Mix_LoadMUS("romfs:/music/AgahnimFinal.it");
        case 27 : return Mix_LoadMUS("romfs:/music/GanondorfFinal.it");
        case 28 : return Mix_LoadMUS("romfs:/music/Quizz.it");
        case 29 : return Mix_LoadMUS("romfs:/music/FinalBattle.it");
        default : return Mix_LoadMUS("romfs:/music/Boss.it");
    }
}
