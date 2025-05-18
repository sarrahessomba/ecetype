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


void init_ennemi_nv2(ennemi mon_ennemi[2]) {
    // En Haut
    mon_ennemi[0].x = SCREEN_W / 2 + 60;
    mon_ennemi[0].y = 0;
    mon_ennemi[0].dy = 2;

    // En Bas
    mon_ennemi[1].x = SCREEN_W / 2 + 60;
    mon_ennemi[1].y = 450;
    mon_ennemi[1].dy = -2;
    for(int i = 0; i < 2; i++) {
        mon_ennemi[i].taille_x = 50;
         mon_ennemi[i].taille_y = 50;
         mon_ennemi[i].pv = 2;
         mon_ennemi[i].dmg = 2;
        mon_ennemi[i].chargeur = 0;
        mon_ennemi[i].reload = 50;
         mon_ennemi[i].compteur_temps = 0;
        mon_ennemi[i].ennemi_actif=1;
         mon_ennemi[i].image_ennemi = load_bitmap("ennemi_nv2/ennemi_nv2_0.bmp", NULL);
    }
}

void init_ennemi_nv3(ennemi* mon_ennemi) {
    mon_ennemi->x = SCREEN_W *2 ;
    mon_ennemi->y = 0;
    mon_ennemi->dx = -1;
    mon_ennemi->dy = 0;
    mon_ennemi->taille_x = 270;
    mon_ennemi->taille_y = 500;
    mon_ennemi->pv = 10;
    mon_ennemi->dmg = 3;
    mon_ennemi->chargeur = 0;
    mon_ennemi->reload = 50;
    mon_ennemi->compteur_temps = 0;
    mon_ennemi->ennemi_actif=1;
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
void afficher_et_deplacer_ennemi_nv2(BITMAP* buffer, ennemi mon_ennemi[2], int temps_max) {
    for(int i = 0; i < 2; i++) {
        if(mon_ennemi[i].ennemi_actif) {
            stretch_sprite(buffer, mon_ennemi[i].image_ennemi, mon_ennemi[i].x, mon_ennemi[i].y, mon_ennemi[i].taille_x, mon_ennemi[i].taille_y);
        }
    }
    mon_ennemi[0].compteur_temps++;
    if (mon_ennemi[0].compteur_temps >= temps_max) {
        mon_ennemi[0].y += mon_ennemi[0].dy;
        mon_ennemi[1].y += mon_ennemi[1].dy;
        // Inversion en haut
        if (mon_ennemi[0].y <= 0) {
          mon_ennemi[0].y = 0;
           mon_ennemi[0].dy = -mon_ennemi[0].dy;
        }
        // Inversion en bas
        if (mon_ennemi[0].y >= 450) {
            mon_ennemi[0].y = 450;
            mon_ennemi[0].dy = -mon_ennemi[0].dy;
        }
        // Inversion en bas
        if (mon_ennemi[1].y >= 450) {
            mon_ennemi[1].y = 450;
            mon_ennemi[1].dy = -mon_ennemi[1].dy;
        }
        // Inversion en haut
        if (mon_ennemi[1].y <= 0) {
            mon_ennemi[1].y = 0;
            mon_ennemi[1].dy = -mon_ennemi[1].dy;
        }


        mon_ennemi[0].compteur_temps = 0;

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
int collision_vaisseau_ennemis(t_vaisseau *vaisseau, ennemi *ennemi_niveau1, int *ennemi_courant) {

    int collision_eu=0;
    for (int i = 0; i <= *ennemi_courant; i++) {
        if(ennemi_niveau1[i].ennemi_actif) {
            if (vaisseau->x <= ennemi_niveau1[i].x + ennemi_niveau1[i].taille_x &&
                ennemi_niveau1[i].x <= vaisseau->x + vaisseau->tx &&
                vaisseau->y <= ennemi_niveau1[i].y + ennemi_niveau1[i].taille_y &&
                ennemi_niveau1[i].y <= vaisseau->y + vaisseau->ty) {
                ennemi_niveau1[i].ennemi_actif = 0;
                vaisseau->x = 100;
                vaisseau->y = SCREEN_H/2 + 85;
                printf("touchee\n");
                rest(400);
                collision_eu = 1;
                }
        }
    }
    return collision_eu;
}



//void tir_ennemi_nv2
void init_tir(tir_ennemi* tir_ennemi,ennemi ennemi_niveau,BITMAP* image_tir_ennemi) {
    tir_ennemi->dx=tir_ennemi->dy=3;
    tir_ennemi->x=ennemi_niveau.x + ennemi_niveau.taille_x;
    tir_ennemi->y=ennemi_niveau.y + ennemi_niveau.taille_x/2 -5;
    tir_ennemi->tx=30;
    tir_ennemi->ty=30;
    tir_ennemi->tir_actif=0;
    tir_ennemi->image_tir=image_tir_ennemi;

}

void tir_ennemi_niveau2 (tir_ennemi tir_ennemi[NB_TIR_ENNEMI], ennemi* ennemi_niveau2, t_vaisseau* vaisseau, BITMAP* buffer) {
    // Incrémentation du chargeur pour cadence de tir
    (ennemi_niveau2->chargeur)++;
    if (ennemi_niveau2->chargeur >= ennemi_niveau2->reload) {
        // Création d'un nouveau tir si possible
        for (int i = 0; i < NB_TIR_ENNEMI; i++) {
            if (!tir_ennemi[i].tir_actif) {

                tir_ennemi[i].x = ennemi_niveau2->x + 10;
                tir_ennemi[i].y = ennemi_niveau2->y + ennemi_niveau2->taille_y / 2;
                tir_ennemi[i].tir_actif = 1;

                break;
            }
        }
        ennemi_niveau2->chargeur = 0;
    }

    // Déplacement des tirs + désactivation si sort de l'écran
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        if (tir_ennemi[i].tir_actif) {
            tir_ennemi[i].x -= tir_ennemi[i].dx;
            if (tir_ennemi[i].x < 0) {
                tir_ennemi[i].tir_actif = 0;
            }
        }
    }

    // Détection de collision avec le vaisseau
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        if(ennemi_niveau2->ennemi_actif){
            if (tir_ennemi[i].tir_actif) {
                if (tir_ennemi[i].x < vaisseau->x + vaisseau->tx &&
                    tir_ennemi[i].x + tir_ennemi[i].tx > vaisseau->x &&
                    tir_ennemi[i].y < vaisseau->y + vaisseau->ty &&
                    tir_ennemi[i].y + tir_ennemi[i].ty > vaisseau->y) {

                    // Collision détectée : on enlève un point et désactive le tir
                    vaisseau->point-=50;
                    tir_ennemi[i].tir_actif = 0;

                    // Sécurité pour ne pas descendre sous 0
                    if (vaisseau->point < 0) {
                        vaisseau->point = 0;
                    }
                    }
            }
        }
    }


    // Affichage des tirs actifs
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        if (tir_ennemi[i].tir_actif) {
            stretch_sprite(buffer, tir_ennemi[i].image_tir,
                           tir_ennemi[i].x, tir_ennemi[i].y,
                           tir_ennemi[i].tx, tir_ennemi[i].ty);
        }
    }
}

void tir_ennemi_boss(tir_ennemi tir_ennemi[NB_TIR_ENNEMI], ennemi* boss, t_vaisseau* vaisseau, BITMAP* buffer) {
    boss->chargeur++;
    if (boss->chargeur >= boss->reload) {
        int tirs_crees = 0;

        // Création de 3 tirs : haut milieu bas
        for (int i = 0; i < NB_TIR_ENNEMI && tirs_crees < 3; i++) {
            if (!tir_ennemi[i].tir_actif) {
                tir_ennemi[i].x = boss->x + 10;
                tir_ennemi[i].y = boss->y + boss->taille_y / 2;
                tir_ennemi[i].tir_actif = 1;
                tir_ennemi[i].dx = 5;

                // Directions différentes
                if (tirs_crees == 0) {
                    tir_ennemi[i].dy = -2; // vers le haut
                } else if (tirs_crees == 1) {
                    tir_ennemi[i].dy = 0;  // tout droit
                } else if (tirs_crees == 2) {
                    tir_ennemi[i].dy = 2;  // vers le bas
                }

                tirs_crees++;
            }
        }

        // Réinitialise le chargeur
        boss->chargeur = 0;
    }

    // Déplacement des tirs et désactivation s’ils sortent de l’écran
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        if (tir_ennemi[i].tir_actif) {
            tir_ennemi[i].x -= tir_ennemi[i].dx;
            tir_ennemi[i].y += tir_ennemi[i].dy;

            if (tir_ennemi[i].x < 0 || tir_ennemi[i].y < 0 || tir_ennemi[i].y > SCREEN_H) {
                tir_ennemi[i].tir_actif = 0;
            }
        }
    }

    // Détection de collision avec le vaisseau
    if (boss->ennemi_actif) {
        for (int i = 0; i < NB_TIR_ENNEMI; i++) {
            if (tir_ennemi[i].tir_actif) {
                if (tir_ennemi[i].x < vaisseau->x + vaisseau->tx &&
                    tir_ennemi[i].x + tir_ennemi[i].tx > vaisseau->x &&
                    tir_ennemi[i].y < vaisseau->y + vaisseau->ty &&
                    tir_ennemi[i].y + tir_ennemi[i].ty > vaisseau->y) {

                    // Collision détectée
                    vaisseau->point -= 50;
                    if (vaisseau->point < 0) {
                        vaisseau->point = 0;
                    }

                    tir_ennemi[i].tir_actif = 0;
                }
            }
        }
    }

    // Affichage des tirs actifs
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        if (tir_ennemi[i].tir_actif) {
            stretch_sprite(buffer, tir_ennemi[i].image_tir,
                           tir_ennemi[i].x, tir_ennemi[i].y,
                           tir_ennemi[i].tx, tir_ennemi[i].ty);
        }
    }
}


void collision_tir_ennemi(t_tir tirs[NB_TIR], ennemi ennemis[], int nb_ennemis,t_vaisseau* vaisseau) {
    for (int i = 0; i < NB_TIR; i++) {
        if (tirs[i].tir_actif) {
            for (int j = 0; j < nb_ennemis; j++) {
                if (ennemis[j].ennemi_actif) {

                    if (tirs[i].x < ennemis[j].x + ennemis[j].taille_x &&
                        tirs[i].x + tirs[i].tx > ennemis[j].x &&
                        tirs[i].y < ennemis[j].y + ennemis[j].taille_y &&
                        tirs[i].y + tirs[i].ty > ennemis[j].y) {
                        printf("toucheeeee\n");
                        // Collision détectée
                        tirs[i].tir_actif = 0;
                        ennemis[j].pv -= 1;

                        if (ennemis[j].pv <= 0) {
                            ennemis[j].ennemi_actif = 0;
                            vaisseau->score+=50;
                            // Optionnel : jouer une animation d'explosion, son, etc.
                        }

                        break; // On arrête de vérifier ce tir car il a déjà touché un ennemi
                        }
                }
            }
        }
    }
}
void collision_tir_vaisseau(t_tir tirs_ennemi[NB_TIR_ENNEMI],t_vaisseau* vaisseau,ennemi* ennemi) {
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        if(ennemi->ennemi_actif) {
            if (tirs_ennemi[i].tir_actif) {
                if (tirs_ennemi[i].x < vaisseau->x + vaisseau->tx &&
                    tirs_ennemi[i].x + tirs_ennemi[i].tx > vaisseau->x &&
                    tirs_ennemi[i].y <vaisseau->y +vaisseau->ty &&
                    tirs_ennemi[i].y + tirs_ennemi[i].ty > vaisseau->y) {
                    printf("toucheee\n");
                    // Collision détectée
                    tirs_ennemi[i].tir_actif = 0;
                    vaisseau->point -=  50;

                    if (vaisseau->point <= 0) {
                        vaisseau->nb_vies--;
                        vaisseau->point=250;
                        // Optionnel : jouer une animation d'explosion, son, etc.
                    }
                }
            }
        }
    }
}
