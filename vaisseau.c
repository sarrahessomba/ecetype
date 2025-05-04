//
// Created by sarra on 4/28/2025.
//

#include "vaisseau.h"
//sous programmes concernat le vaisseau
#include <stdio.h>

//PERMET DE GERER LE DEPLACEMENT DU VAISSEAU AINSI QUE LES SPRITES CONCERNES
void deplacement_vaisseau(t_vaisseau *vaisseau, int *cptimg, int *img_courante, int tmpimg) {
    if(key[KEY_RIGHT]) {

      if(*img_courante!=0) {
          if(*img_courante<=(NB_SPRITES_VAISSEAU-1)/2) {
              (*img_courante)--;
              if(*img_courante<=0) {
                  *img_courante=0;
              }
          }else {
              (*img_courante)--;
              if(*img_courante<=NB_SPRITES_VAISSEAU-(NB_SPRITES_VAISSEAU-1)/2) {
                  *img_courante=0;
              }
          }
      }
        vaisseau->x += vaisseau->dx;
        if(vaisseau->x + vaisseau->tx > SCREEN_W) {
            vaisseau->x = SCREEN_W -vaisseau->tx;
        }
    }
    else if(key[KEY_LEFT]) {
        if(*img_courante!=0) {
            if(*img_courante<=(NB_SPRITES_VAISSEAU-1)/2) {
                (*img_courante)--;
                if(*img_courante<=0) {
                    *img_courante=0;
                }
            }else {
                (*img_courante)--;
                if(*img_courante<=NB_SPRITES_VAISSEAU-(NB_SPRITES_VAISSEAU-1)/2) {
                    *img_courante=0;
                }
            }
        }
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
            if(*img_courante==0) {
                (*img_courante)=4;
            }
            (*img_courante)++;

            if (*img_courante >= (NB_SPRITES_VAISSEAU - 1)) {
                *img_courante = (NB_SPRITES_VAISSEAU - 1);
            }
        }
        vaisseau->y += vaisseau->dy;
        if(vaisseau->y + vaisseau->ty> SCREEN_H) {
            vaisseau->y = SCREEN_H-vaisseau->ty;
        }
    }
    else if(key[KEY_UP]) {
        // Animation du vaisseau qui monte
        (*cptimg)++;
        if (*cptimg >= tmpimg) {
            *cptimg = 0;
            (*img_courante)++;
            if ((*img_courante -1) == (NB_SPRITES_VAISSEAU - 1)) {
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


}

//INITIALISE LES DONNES DU VAISSEAU , DES TIRS , ET CHARGE TOUTE LES SPRITES
void initialisation_vaisseau_tir(t_vaisseau* vaisseau,t_tir* tir, BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION] ) {
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


    // Chargement des sprites d explosion
    char nomfichier2[100];
    for (int i=0;i<NB_SPRITES_EXPLOSION;i++) {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier2,"explosion_sprites/explosion_%d.bmp",i);
        explosion_sprites[i] = load_bitmap(nomfichier2,NULL);
        if(!explosion_sprites[i]) {
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }
    /*
//chargement du tir simple

    tir->tir_bmp= load_bitmap("tir.bmp", NULL);
    if (!tir->tir_bmp) {
        allegro_message("Erreur lors du chargement de tir.bmp");
    }*/
    //Chargement des sprites du tir special
    char nomfichier3[100];
    for(int i=0; i<NB_SPRITES_TIR;i++) {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier3,"tir_special/tir_special_%d.bmp",i);
        tir->tir_special_bmp[i] = load_bitmap(nomfichier3,NULL);
        if(!tir->tir_special_bmp[i]) {
            allegro_message("pas pu trouver %s",nomfichier3);
        }
    }

    for(int i=0;i<NB_TIR;i++) {
        tir->tir_bmp=load_bitmap("tir.bmp", NULL);
    }
    //Chargement du son du tir
    tir->son_tir=load_sample("son_tir.wav");
    if (!tir->son_tir) {
        allegro_message("erreur  chargement de son_tir.wav");
    }
        // Initialisation des donnes du vaisseau
        vaisseau->x = 100;
        vaisseau->y = SCREEN_H/2 +70 ;
        vaisseau->dx = vaisseau->dy = 2;
        vaisseau->etat = 0;//pas encore gagné
        vaisseau->tx=50;
        vaisseau->ty = 50;
        vaisseau->nb_vies=3;
        vaisseau->score=0;

        //tir init
        tir->dx=tir->dy=7;
        tir->x=vaisseau->x + 16 + vaisseau->tx;
        tir->y=vaisseau->y + vaisseau->ty/2 -5;
        tir->tx=15;
        tir->ty=15;
        // init des variables pour animation
        tir->cptimg=0;
        tir->img_courante=0;


};
int calcul_coordonees_x(int scroll_x,int x,BITMAP* bmp) {//recoit le x du screen et le convertit au x du decor
    int nouveau_x=  (scroll_x+ (x*bmp->w)/(SCREEN_W)) % bmp->w;
    return nouveau_x;
};
int  calcul_coordonees_y(int y,BITMAP* bmp) {//recoit le x du screen et le convertit au x du decor
    int nouveau_y=(y*bmp->h)/(SCREEN_H);
    return nouveau_y;
};
// lANCE L'ANIMATION DE L'EXPLOSION
int explosion_animation(t_vaisseau vaisseau, int* cptimg, int* imgcourante,int tmpimg,BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION],BITMAP* buffer) { // lance l'animation de l'explosion
int fini=0;
    (*cptimg)++;
    if (*cptimg>=tmpimg){
        *cptimg=0;
        (*imgcourante)++;
        if (*imgcourante>=NB_SPRITES_EXPLOSION-1){ // quand l'indice de l'image courante arrive à NIMAGE
            *imgcourante=NB_SPRITES_EXPLOSION-1; // on recommence la séquence à partir de 0
            fini=1;
            }
    }

    stretch_sprite(buffer,explosion_sprites[*imgcourante],vaisseau.x-10,vaisseau.y,2*explosion_sprites[*imgcourante]->w,2*explosion_sprites[*imgcourante]->h);
return fini;
}

//DETECTE LA COLLISION ENTRE VAISSEAU ET DECOR
int collision_vaisseau_decor(int * active_scroll,int scroll_x,t_vaisseau* vaisseau,BITMAP* fond_jeu_collision,  int* cptimg_ex, int tmpimg_ex,int* img_courante_ex,BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION],BITMAP* buffer,int* imgcourante) {

    int collision_eu=0;

    if(getpixel(fond_jeu_collision,calcul_coordonees_x(scroll_x,vaisseau->x,fond_jeu_collision),calcul_coordonees_y(vaisseau->y,fond_jeu_collision))==makecol(255,255,255) || getpixel(fond_jeu_collision,calcul_coordonees_x(scroll_x,(vaisseau->x+ vaisseau->tx),fond_jeu_collision),calcul_coordonees_y(vaisseau->y + vaisseau->ty,fond_jeu_collision))==makecol(255,255,255) || getpixel(fond_jeu_collision,calcul_coordonees_x(scroll_x,vaisseau->x  + vaisseau->tx,fond_jeu_collision),calcul_coordonees_y(vaisseau->y,fond_jeu_collision))==makecol(255,255,255) || getpixel(fond_jeu_collision,calcul_coordonees_x(scroll_x,vaisseau->x ,fond_jeu_collision),calcul_coordonees_y(vaisseau->y + vaisseau->ty,fond_jeu_collision))==makecol(255,255,255)){

        *active_scroll=0;
        int fini= explosion_animation(*vaisseau,cptimg_ex,img_courante_ex,tmpimg_ex,explosion_sprites,buffer);
        printf("touched\n");
        // Initialisation des donnes du vaisseau
        if(fini) {
//reinitialise
            vaisseau->x = 100;
            vaisseau->y = SCREEN_H/2 + 70;

            *imgcourante=0;
            *img_courante_ex=0;
            *active_scroll=1;
            rest(20);
            collision_eu=1;
        }

    }
    return collision_eu;
}
void tir_fonction(int *son_active,t_tir tirs[NB_TIR],t_tir tir,t_vaisseau vaisseau,BITMAP* buffer,int* tir_enclenche) {
    if(*son_active) {
        play_sample(tir.son_tir,255,128,1000,0); //255 est le volume, 128 panoramique, 1000 vitesse de lec du son, 0 pour jouer le son une fois ou en boucle (1)
        *son_active=0;
    }
    if(key[KEY_SPACE] && !(*tir_enclenche)) {
        *son_active=1;

        for (int i = 0; i < NB_TIR; i++) {

            if (!tirs[i].tir_actif) {
                tirs[i].x = vaisseau.x + 16 + vaisseau.tx;
                tirs[i].y = vaisseau.y + vaisseau.ty/2 -5;
                tirs[i].tir_actif = 1;
                break;
            }
        }

    }

    for (int i = 0; i < NB_TIR; i++) {
        if (tirs[i].tir_actif) {
            tirs[i].x += tir.dx;
            if (tirs[i].x > SCREEN_W) {
                tirs[i].tir_actif = 0;
            }
        }
    }
    for (int i = 0; i < NB_TIR; i++) {
        if (tirs[i].tir_actif) {
            stretch_sprite(buffer, tir.tir_bmp, tirs[i].x, tirs[i].y,tir.tx,tir.ty);
        }
    }
}
void gestion_score_point_vie_vaisseau(t_vaisseau* vaisseau,int collision_eu) {
    if(collision_eu) {
        vaisseau->nb_vies--;
    }
    printf("%d\n",vaisseau->nb_vies);
}//collison_tir_ennemi a ajoute et collison ennemei
