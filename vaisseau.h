//
// Created by sarra on 4/28/2025.
//

#ifndef VAISSEAU_H
#define VAISSEAU_H
#include <allegro.h>
#define  NB_SPRITES_VAISSEAU 7

typedef struct t_vaisseau {

    int etat;//a gagné ou pas
    int point;//point de vies
    //Position du vaisseau
    int x;
    int y;
    //deplacement ,vitesse
    int dx;
    int dy;
    int tx;
    int ty;
    //vaisseau
    BITMAP* vaisseau_bmp[NB_SPRITES_VAISSEAU];
}t_vaisseau;
typedef struct tir {
    int x;
    int y;
    int dx;
    int dy;
    int tx;
    int ty;
    BITMAP* tir_bmp;
}t_tir;
//sous programmes
void deplacement_vaisseau(t_vaisseau *vaisseau, int *tir_validee, int *cptimg, int *img_courante, int tmpimg);

void initialisation_vaisseau_tir(t_vaisseau* vaisseau,t_tir* tir);
#endif //VAISSEAU_H
