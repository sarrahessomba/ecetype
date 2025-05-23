//
// Created by sarra on 4/28/2025.
//

#ifndef VAISSEAU_H
#define VAISSEAU_H
#include <allegro.h>
#define  NB_SPRITES_VAISSEAU 7
#define NB_SPRITES_EXPLOSION 5
#define NB_SPRITES_TIR 5
#define NB_TIR 100
typedef struct t_vaisseau {

    int etat;//a gagné ou pas
    int score;
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
    int tir_actif;
    BITMAP* tir_bmp;
    int cptimg;
    int img_courante;
    //son tir
    SAMPLE* son_tir;

}t_tir;
//sous programmes
void deplacement_vaisseau(t_vaisseau *vaisseau, int *cptimg, int *img_courante, int tmpimg);
void tir_fonction(int *son_active,t_tir tirs[NB_TIR],t_tir tir,t_vaisseau vaisseau,BITMAP* buffer,int* tir_enclenche) ;
void initialisation_vaisseau_tir(t_vaisseau* vaisseau,t_tir* tir,BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION]);

int collision_vaisseau_decor(int* active_scroll,int scroll_x,t_vaisseau* vaisseau,BITMAP* fond_jeu_collision,  int* cptimg_ex, int tmpimg_ex,int* img_courante_ex,BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION],BITMAP* buffer,int* imgcourante);
void gestion_score_point_vie_vaisseau(t_vaisseau* vaisseau,int collision_eu_decor, int collision_eu_ennemi1, int collision_eu_ennemi2);
int explosion_animation(t_vaisseau vaisseau, int* cptimg, int* imgcourante,int tmpimg,BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION],BITMAP* buffer) ; // lance l'animation de l'explosion
#endif //VAISSEAU_H
