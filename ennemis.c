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
    mon_ennemi->image_ennemi = load_bitmap("ennemi_nv1.bmp", NULL);
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
    mon_ennemi->image_ennemi = load_bitmap("ennemi_nv2.bmp", NULL);
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

void init_ennemi_nv3(ennemi* mon_ennemi) {
    mon_ennemi->x = SCREEN_W ; // Arrivée: SCREEN_W-285
    mon_ennemi->y = SCREEN_H-650;
    mon_ennemi->dx = -1;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 270;
    mon_ennemi->taille_y = 500;
    mon_ennemi->pv = 3;
    mon_ennemi->dmg = 3;
    mon_ennemi->chargeur = 10;
    mon_ennemi->reload = 2;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->image_ennemi = load_bitmap("boss.bmp", NULL);
}

void afficher_et_deplacer_ennemi_nv1(BITMAP* buffer, BITMAP* fond_nv1, ennemi* mon_ennemi, int temps_max) {
    stretch_sprite(buffer, mon_ennemi->image_ennemi, mon_ennemi->x, mon_ennemi->y, mon_ennemi->taille_x, mon_ennemi->taille_y);
    mon_ennemi->compteur_temps++;
    if (mon_ennemi->compteur_temps >= temps_max) {
        mon_ennemi->compteur_temps = 0;
        mon_ennemi->x += mon_ennemi->dx;
    }
}
void afficher_et_deplacer_ennemi_nv2(BITMAP* buffer, BITMAP* fond_nv2, ennemi* mon_ennemi, int temps_max) {
    stretch_sprite(buffer, mon_ennemi->image_ennemi, mon_ennemi->x, mon_ennemi->y, mon_ennemi->taille_x, mon_ennemi->taille_y);
    mon_ennemi->compteur_temps++;
    if (mon_ennemi->compteur_temps >= temps_max) {
        mon_ennemi->compteur_temps = 0;
        mon_ennemi->x += mon_ennemi->dx;
    }
}

void afficher_ennemi_nv3(BITMAP* buffer, ennemi* boss, int temps_max) {
    stretch_sprite(buffer, boss->image_ennemi, boss->x, boss->y, boss->taille_x, boss->taille_y);
    if (boss->x > SCREEN_W - 285) {
        boss->compteur_temps++;
        if (boss->compteur_temps >= temps_max) {
            boss->compteur_temps = 0;
            boss->x += boss->dx;
        }
    }
}