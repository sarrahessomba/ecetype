#include "ennemis.h"
#include <stdlib.h>
#include <allegro/datafile.h>
#include <allegro/gfx.h>

void init_ennemi_nv1(ennemi* mon_ennemi) {
    mon_ennemi->x = SCREEN_W+10;
    mon_ennemi->y = rand() % (480 - 150 + 1) + 150;
    mon_ennemi->dx = -1;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 50;
    mon_ennemi->taille_y = 50;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->pv = 1;
    mon_ennemi->dmg = 1;
    mon_ennemi->chargeur = 5;
    mon_ennemi->reload = 4;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->image_ennemi_nv1 = load_bitmap("ennemi_nv1.bmp", NULL);
}

void init_ennemi_nv2(ennemi* mon_ennemi) {
    mon_ennemi->x = rand() % (SCREEN_W / 2 + 1) + SCREEN_W / 2;
    mon_ennemi->y = choisir_y();
    mon_ennemi->dx = -1;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 50;
    mon_ennemi->taille_y = 50;
    mon_ennemi->pv = 2;
    mon_ennemi->dmg = 2;
    mon_ennemi->chargeur = 7;
    mon_ennemi->reload = 3;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->image_ennemi_nv1 = load_bitmap("ennemi_nv2.bmp", NULL);
}

void init_ennemi_nv3(ennemi* mon_ennemi) {
    mon_ennemi->x = SCREEN_W + 15;
    mon_ennemi->y = 0;
    mon_ennemi->dx = 0;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 25;
    mon_ennemi->taille_y = 25;
    mon_ennemi->pv = 3;
    mon_ennemi->dmg = 3;
    mon_ennemi->chargeur = 10;
    mon_ennemi->reload = 2;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->image_ennemi_nv1 = load_bitmap("boss.bmp", NULL);
}

void afficher_et_deplacer_ennemi_nv1(BITMAP* buffer, BITMAP* fond_nv1, ennemi* mon_ennemi, int temps_max) {
    stretch_sprite(buffer, mon_ennemi->image_ennemi_nv1, mon_ennemi->x, mon_ennemi->y, mon_ennemi->taille_x, mon_ennemi->taille_y);
    mon_ennemi->compteur_temps++;
    if (mon_ennemi->compteur_temps >= temps_max) {
        mon_ennemi->compteur_temps = 0;
        mon_ennemi->x += mon_ennemi->dx;
    }
}
void afficher_et_deplacer_ennemi_nv2(BITMAP* buffer, BITMAP* fond_nv2, ennemi* mon_ennemi, int temps_max) {
    stretch_sprite(buffer, mon_ennemi->image_ennemi_nv1, mon_ennemi->x, mon_ennemi->y, mon_ennemi->taille_x, mon_ennemi->taille_y);
    mon_ennemi->compteur_temps++;
    if (mon_ennemi->compteur_temps >= temps_max) {
        mon_ennemi->compteur_temps = 0;
        mon_ennemi->x += mon_ennemi->dx;
    }
}

int choisir_y() {
    int r = rand() % 2;
    if (r==0) {
        return(50);
    }
    else {
        return(SCREEN_H-150);
    }
}