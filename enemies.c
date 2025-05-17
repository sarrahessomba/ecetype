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
    mon_ennemi->y = -20;
    mon_ennemi->dx = 0;
    mon_ennemi->dy = 2;
    mon_ennemi->taille_x = 50;
    mon_ennemi->taille_y = 50;
    mon_ennemi->pv = 2;
    mon_ennemi->dmg = 2;
    mon_ennemi->chargeur = 0;
    mon_ennemi->reload = 50;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->image_ennemi = load_bitmap("ennemi_nv2/ennemi_nv2_0.bmp", NULL);
}

void init_ennemi_nv3(ennemi* mon_ennemi) {
    mon_ennemi->x = SCREEN_W *2 ;
    mon_ennemi->y = 0;
    mon_ennemi->dx = -1;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 270;
    mon_ennemi->taille_y = 500;
    mon_ennemi->pv = 3;
    mon_ennemi->dmg = 3;
    mon_ennemi->chargeur = 0;
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

void afficher_ennemi_nv3(BITMAP* buffer, ennemi* boss, int temps_max) {
    stretch_sprite(buffer, boss->image_ennemi, boss->x, boss->y, boss->taille_x, boss->taille_y);
    if (boss->x > SCREEN_W - 285) {
        boss->compteur_temps++;
        if (boss->compteur_temps >= temps_max) {
            boss->compteur_temps = 0;
            boss->x += boss->dx;
            if(boss->x >= SCREEN_W- boss->taille_x +25) {
                boss->x =SCREEN_W-boss->taille_x +25;
            }
        }
    }
}
int collision_vaisseau_ennemis(t_vaisseau *vaisseau, ennemi *ennemi_niveau1, int *ennemi_courant, int *active_scroll) {
    int collision_eu=0;
    for (int i = 0; i <= *ennemi_courant; i++) {
        if (vaisseau->x <= ennemi_niveau1[i].x + ennemi_niveau1[i].taille_x &&
            ennemi_niveau1[i].x <= vaisseau->x + vaisseau->tx &&
            vaisseau->y <= ennemi_niveau1[i].y + ennemi_niveau1[i].taille_y &&
            ennemi_niveau1[i].y <= vaisseau->y + vaisseau->ty) {
            *active_scroll=0;
            vaisseau->x = 100;
            vaisseau->y = SCREEN_H/2 + 85;
            printf("touchee\n");
            rest(400);

            *active_scroll=1;


            if (*ennemi_courant == 0) {
                init_ennemi_nv1(&ennemi_niveau1[0]);
            } else if (*ennemi_courant > 0) {
                (*ennemi_courant)--;
                init_ennemi_nv1(&ennemi_niveau1[*ennemi_courant]);
            }
            collision_eu = 1;
        }
    }
    return collision_eu;
}



//void tir_ennemi_nv2
void init_tir(tir_ennemi* tir_ennemi,ennemi ennemi_niveau,BITMAP* image_tir_ennemi) {
    tir_ennemi->dx=tir_ennemi->dy=3;
    tir_ennemi->x=ennemi_niveau.x + ennemi_niveau.taille_x;
    tir_ennemi->y=ennemi_niveau.y + ennemi_niveau.taille_x/2 -5;
    tir_ennemi->tx=15;
    tir_ennemi->ty=15;
    tir_ennemi->tir_actif=0;
    tir_ennemi->image_tir=image_tir_ennemi;

}
void tir_ennemi_niveau2(tir_ennemi tir_ennemi[NB_TIR_ENNEMI],ennemi* ennemi_niveau2,BITMAP* buffer) {
        (ennemi_niveau2->chargeur)++;
        if(ennemi_niveau2->chargeur>= ennemi_niveau2->reload) {
           for(int i = 0; i< NB_TIR_ENNEMI; i++) {
               if (!tir_ennemi[i].tir_actif) {
                   tir_ennemi[i].x = ennemi_niveau2->x + 10;
                   tir_ennemi[i].y = ennemi_niveau2->y + ennemi_niveau2->taille_y/2 ;
                   tir_ennemi[i].tir_actif = 1;
                   break;
               }
           }
            ennemi_niveau2->chargeur=0;
        }
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        if (tir_ennemi[i].tir_actif) {
            tir_ennemi[i].y += tir_ennemi[i].dy;
            if (tir_ennemi[i].y > SCREEN_H) {
                tir_ennemi[i].tir_actif = 0;
            }

        }
    }
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        if (tir_ennemi[i].tir_actif) {
            stretch_sprite(buffer, tir_ennemi[i].image_tir, tir_ennemi[i].x, tir_ennemi[i].y,tir_ennemi[i].tx,tir_ennemi[i].ty);
        }
    }
}
void collision_tir_ennemi(t_tir tirs[NB_TIR], ennemi ennemis[], int nb_ennemis) {
    for (int i = 0; i < NB_TIR; i++) {
        if (tirs[i].tir_actif) {
            for (int j = 0; j < nb_ennemis; j++) {
                if (ennemis[j].ennemi_actif) {
                    // Détection collision AABB (rectangle vs rectangle)
                    if (tirs[i].x < ennemis[j].x + ennemis[j].taille_x &&
                        tirs[i].x + tirs[i].tx > ennemis[j].x &&
                        tirs[i].y < ennemis[j].y + ennemis[j].taille_y &&
                        tirs[i].y + tirs[i].ty > ennemis[j].y) {

                        // Collision détectée
                        tirs[i].tir_actif = 0;
                        ennemis[j].pv -= 1; // Ici on enlève 1 PV, adapte selon ta logique

                        if (ennemis[j].pv <= 0) {
                            ennemis[j].ennemi_actif = 0;
                            // Optionnel : jouer une animation d'explosion, son, etc.
                        }

                        break; // On arrête de vérifier ce tir car il a déjà touché un ennemi
                        }
                }
            }
        }
    }
}


int choisir_y() {
    int r = rand() % 2;
    if (r==0) {
        return(-1);
    }
    return(1);
}