/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Listable.h"

Listable::Listable() : suivant(0), id(0) {
}

Listable::~Listable() {
	if(suivant) delete suivant;
	suivant = 0;
}

int Listable::size() {
    if (suivant == 0) return 0;
    return (suivant->size() + 1);
}
        
void Listable::ajout(Listable* l) {
    if (suivant == 0) {
        suivant = l;
        suivant->id = id + 1;
// nop90: releasing an element here is wrong because deleting an object as lista ble instance, doesn't call the top level desctructor, 
// this way some resources could not be released.
// anyway it seems to never happen in other parts of the code that a list is added instead of a sinfle element, so I commented it ou. 
//        delete suivant->suivant; // au cas où on a donné une liste au lieu d'un élément
    }
    else suivant->ajout(l);
}

//void Listable::enleve(Listable* l) {
Listable* Listable::enleve(Listable* l) {
//    if (suivant == 0) return;
    if (suivant == 0) return 0;
    if (l == suivant) {
        Listable* tmp = suivant->suivant;
        suivant->suivant = 0; //pour éviter suppressions récursives
// nop90: this is wrong too for the same reason above, and this happens in Jeu.cpp, Object.cpp, Projectile,cpp, Listable.cpp
//        delete suivant;

// the quick fix I found is toreturn the ojbect to be deleted to the caller, that will have to release it after a cast to the righr top level class

        Listable* ret = suivant;
		
        suivant = tmp;
		
		return ret;
    }
    else suivant->enleve(l);
}

void Listable::setSuivant(Listable* l) {
    if (suivant) delete suivant;
	suivant = l;
}

bool Listable::operator==(const Listable* l) {
    return (id == l->id);
}

int Listable::getListId() {return id;}
