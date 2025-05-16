//
// Created by sarra on 4/28/2025.
//
//sous programmes concernant les enemies
#include "enemies.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include "vaisseau.h"


void init_ennemi_nv1(ennemi* mon_ennemi) {
    mon_ennemi->x = SCREEN_W+10;
    mon_ennemi->y = rand() % (408-50 - 115 + 1) + 115;
    mon_ennemi->dx = -5;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 50;
    mon_ennemi->taille_y = 50;
    mon_ennemi->ennemi_actif=1;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->pv = 1;
    mon_ennemi->dmg = 1;
    mon_ennemi->chargeur = 5;
    mon_ennemi->reload = 4;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->image_ennemi = load_bitmap("ennemi_nv1.bmp", NULL);
}


void init_ennemi_nv2(ennemi* mon_ennemi) {
    mon_ennemi->x = SCREEN_W/2;
    mon_ennemi->y = -10;
    mon_ennemi->dx = 0;
    mon_ennemi->dy = 2;
    mon_ennemi->taille_x = 50;
    mon_ennemi->taille_y = 50;
    mon_ennemi->pv = 2;
    mon_ennemi->dmg = 2;
    mon_ennemi->chargeur = 7;
    mon_ennemi->reload = 3;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->image_ennemi = load_bitmap("ennemi_nv2/ennemi_nv2_0.bmp", NULL);
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
    mon_ennemi->image_ennemi = load_bitmap("ennemi_nv3.bmp", NULL);
}

void afficher_et_deplacer_ennemi_nv1(BITMAP* buffer, ennemi* mon_ennemi, int temps_max) {

    stretch_sprite(buffer, mon_ennemi->image_ennemi, mon_ennemi->x, mon_ennemi->y, mon_ennemi->taille_x, mon_ennemi->taille_y);
    mon_ennemi->compteur_temps++;
    if (mon_ennemi->compteur_temps >= temps_max) {
        mon_ennemi->compteur_temps = 0;
        mon_ennemi->x += mon_ennemi->dx;
    }
}
void afficher_et_deplacer_ennemi_nv2(BITMAP* buffer, ennemi* mon_ennemi, int temps_max) {
    stretch_sprite(buffer, mon_ennemi->image_ennemi, mon_ennemi->x, mon_ennemi->y, mon_ennemi->taille_x, mon_ennemi->taille_y);
    mon_ennemi->compteur_temps++;
    if (mon_ennemi->compteur_temps >= temps_max) {
        mon_ennemi->compteur_temps = 0;
        if(mon_ennemi->y<=10) {
            mon_ennemi->y += mon_ennemi->dy;
        }
    }
}
int collision_vaisseau_ennemis(t_vaisseau *vaisseau, ennemi *ennemi_niveau1, int *ennemi_courant, int *scroll_x) {
    int collision_eu=0;
    for (int i = 0; i <= *ennemi_courant; i++) {
        if (vaisseau->x <= ennemi_niveau1[i].x + ennemi_niveau1[i].taille_x &&
            ennemi_niveau1[i].x <= vaisseau->x + vaisseau->tx &&
            vaisseau->y <= ennemi_niveau1[i].y + ennemi_niveau1[i].taille_y &&
            ennemi_niveau1[i].y <= vaisseau->y + vaisseau->ty) {

            printf("touchee\n");
            collision_eu = 1;
            rest(16);
            *scroll_x = 0;

            if (*ennemi_courant == 0) {
                init_ennemi_nv1(&ennemi_niveau1[*ennemi_courant]);
            } else if (*ennemi_courant > 0) {
                (*ennemi_courant)--;
                init_ennemi_nv1(&ennemi_niveau1[*ennemi_courant]);
            }
            collision_eu = 1;
            }
    }
    return collision_eu;
}

int collision_tir_ennemi (ennemi* ennemi,t_tir* tir) {
    if (tir->x <= ennemi->x + ennemi->taille_x  &&  ennemi->x <= tir->x + tir->tx  && tir->y <= ennemi->y + ennemi->taille_y  &&  ennemi->y <= tir->y + tir->ty ) {

        printf("touchee_tir\n");
        return 1;
    }
    return 0;
}


int choisir_y() {
    int r = rand() % 2;
    if (r==0) {
        return(-1);
    }
    return(1);
}