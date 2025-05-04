#include "enemies.h"
#include <stdlib.h>

const longueur_rect = 200;
const hauteur_rect = 300;

void init_ennemi_nv1(ennemi* mon_ennemi) {
    mon_ennemi->x = rand()%longueur_rect+1;
    mon_ennemi->y = rand()%hauteur_rect+1;
    mon_ennemi->pv = 1;
    mon_ennemi->dmg = 1;
    mon_ennemi->chargeur = 5;
    mon_ennemi->reload = 4;
}

void init_ennemi_nv2(ennemi* mon_ennemi) {
    mon_ennemi->x = rand()%longueur_rect+1;
    mon_ennemi->y = rand()%hauteur_rect+1;
    mon_ennemi->pv = 2;
    mon_ennemi->dmg = 2;
    mon_ennemi->chargeur = 7;
    mon_ennemi->reload = 3;
}

void init_ennemi_nv3(ennemi* mon_ennemi) {
    mon_ennemi->x = rand()%longueur_rect+1;
    mon_ennemi->y = rand()%hauteur_rect+1;
    mon_ennemi->pv = 3;
    mon_ennemi->dmg = 3;
    mon_ennemi->chargeur = 10;
    mon_ennemi->reload = 2;
}

void trouver_place(ennemi* mon_tab_ennemis) {

}