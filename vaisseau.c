//
// Created by sarra on 4/28/2025.
//

#include "vaisseau.h"
//sous programmes concernat le vaisseau
#include <stdio.h>


void deplacement_vaisseau(t_vaisseau *vaisseau, int *tir_validee, int *cptimg, int *img_courante, int tmpimg) {
    if(key[KEY_RIGHT]) {
        vaisseau->x += vaisseau->dx;
        if(vaisseau->x > SCREEN_W) {
            vaisseau->x = SCREEN_W;
        }
    }
    else if(key[KEY_LEFT]) {
        vaisseau->x -= vaisseau->dx;
        if(vaisseau->x < 0) {
            vaisseau->x = 0;
        }
    }
    else if(key[KEY_DOWN]) {
        // Animation quand il descend
        (*cptimg)++;
        if (*cptimg >= tmpimg) {
            *cptimg = 0;
            (*img_courante)++;
            if (*img_courante >= (NB_SPRITES_VAISSEAU - 1)) {
                *img_courante = 6;
            }
        }
        vaisseau->y += vaisseau->dy;
        if(vaisseau->y > SCREEN_H) {
            vaisseau->y = SCREEN_H;
        }
    }
    else if(key[KEY_UP]) {
        // Animation du vaisseau qui monte
        (*cptimg)++;
        if (*cptimg >= tmpimg) {
            *cptimg = 0;
            (*img_courante)++;
            if ((*img_courante - 1) == (NB_SPRITES_VAISSEAU - 1)) {
                *img_courante = 0;
            }
            if (*img_courante >= (NB_SPRITES_VAISSEAU - 1) / 2) {
                *img_courante = 3;
            }
        }
        vaisseau->y -= vaisseau->dy;
        if(vaisseau->y < 0) {
            vaisseau->y = 0;
        }
    }

    // Gestion du tir
    if(key[KEY_SPACE]) {
        *tir_validee = 1;
    }
}
void initialisation_vaisseau_tir(t_vaisseau* vaisseau,t_tir* tir) {

    // Chargement des sprites bitmap DU VAISSEAU
    char nomfichier[100];
    for (int i=0;i<NB_SPRITES_VAISSEAU;i++){
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier, "vaisseau_sprites/vaisseau_%d.bmp",i);
        vaisseau->vaisseau_bmp[i] = load_bitmap(nomfichier,NULL);
        if (!vaisseau->vaisseau_bmp[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }

    tir->tir_bmp= load_bitmap("tir.bmp", NULL);
    if (!tir->tir_bmp) {
        allegro_message("Erreur lors du chargement de tir.bmp");
    }

    // Initialisation des coordonnees et de l'etat
    vaisseau->x = 100;
    vaisseau->y = SCREEN_H/2+100;
    vaisseau->dx = vaisseau->dy = 2;
    vaisseau->etat = 0;
    vaisseau->tx=50;
    vaisseau->ty = 50;


    //tir init
    tir->dx=tir->dy=7;
    tir->x=vaisseau->x + 16 + vaisseau->tx;
    tir->y=vaisseau->y + vaisseau->ty/2 -5;
    tir->tx=15;
    tir->ty=15;
};
