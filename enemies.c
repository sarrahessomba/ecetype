#include "enemies.h"
#include <stdlib.h>
#include <allegro/datafile.h>
#include <allegro/gfx.h>


void init_ennemi_nv1(ennemi* mon_ennemi) {
    mon_ennemi->x = 600;
    mon_ennemi->y = rand()%(480-150+1)+150;
    mon_ennemi->dx = -1;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 25;
    mon_ennemi->taille_y = 25;
    mon_ennemi->pv = 1;
    mon_ennemi->dmg = 1;
    mon_ennemi->chargeur = 5;
    mon_ennemi->reload = 4;
    mon_ennemi->image_ennemi_nv1 = load_bitmap("ennemi_nv1.bmp",NULL);
}

void init_ennemi_nv2(ennemi* mon_ennemi) {
    mon_ennemi->x =  rand()%(SCREEN_W/2+1)+SCREEN_W/2;
    mon_ennemi->y = SCREEN_H-10;
    mon_ennemi->dx = 0;
    mon_ennemi->dy = 1;
    mon_ennemi->taille_x = 25;
    mon_ennemi->taille_y = 25;
    mon_ennemi->pv = 2;
    mon_ennemi->dmg = 2;
    mon_ennemi->chargeur = 7;
    mon_ennemi->reload = 3;
    mon_ennemi->image_ennemi_nv1 = load_bitmap("ennemi_nv2.bmp",NULL);
}

void init_ennemi_nv3(ennemi* mon_ennemi) {
    mon_ennemi->x =  SCREEN_W+15;
    mon_ennemi->y = 0;
    mon_ennemi->dx = 0;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 25;
    mon_ennemi->taille_y = 25;
    mon_ennemi->pv = 3;
    mon_ennemi->dmg = 3;
    mon_ennemi->chargeur = 10;
    mon_ennemi->reload = 2;
    mon_ennemi->image_ennemi_nv1 = load_bitmap("boss.bmp",NULL);
}

void afficher_et_deplacer_ennemi(BITMAP* buffer, BITMAP* fond_nv1, ennemi* ennemi, int* compteur_temps, int temps_max) {
    stretch_sprite(buffer, fond_nv1, 0, 0, SCREEN_W, SCREEN_H);
    stretch_sprite(buffer, ennemi->image_ennemi_nv1, ennemi->x, ennemi->y, ennemi->taille_x, ennemi->taille_y);
    (*compteur_temps)++;
    if (*compteur_temps >= temps_max) {
        *compteur_temps = 0;
        ennemi->x += ennemi->dx;
    }
}


