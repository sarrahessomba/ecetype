//
// Created by sarra on 4/28/2025.
//

#ifndef VAISSEAU_H
#define VAISSEAU_H
#include <allegro.h>
#define  NB_SPRITES_VAISSEAU 7
#define NB_SPRITES_EXPLOSION 5
#define NB_SPRITES_TIR 5
typedef struct t_vaisseau {

    int etat;//a gagné ou pas
    int point;//point de vies
    int nb_vies;
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
    //animation tir special
    BITMAP* tir_special_bmp[NB_SPRITES_TIR];
    int cptimg;
    int img_courante;
    //son tir

}t_tir;
//sous programmes
void deplacement_vaisseau(t_vaisseau *vaisseau, int *tir_validee, int *cptimg, int *img_courante, int tmpimg);

void initialisation_vaisseau_tir(t_vaisseau* vaisseau,t_tir* tir,BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION]);

void collision_vaisseau_decor(t_vaisseau* vaisseau,BITMAP* fond_jeu_collision,  int* cptimg_ex, int tmpimg_ex,int* img_courante_ex,BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION],BITMAP* buffer,int* imgcourante);
//void collision_vaisseau_decor(t_vaisseau vaisseau,BITMAP* fond_jeu_collision);
#endif //VAISSEAU_H
