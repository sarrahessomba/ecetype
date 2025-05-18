//
// Created by sarra on 4/28/2025.
//

#ifndef ENEMIES_H
#define ENEMIES_H
#include <allegro.h>
#include "vaisseau.h"
#define NB_TIR_ENNEMI 100

typedef struct ennemi {
    int x; // Abscisse
    int y; // Ordonnée
    int dx; // Déplacement horizontal
    int dy; // Déplacement vertical
    int taille_x; // Taille en x
    int taille_y; // Taille en y
    int compteur_temps; // Variable de déplacement
    int pv; // Points de vie
    int dmg; // Points de dégâts par tir
    int chargeur; // Nombre de balles dans un chargeur
    int reload; // Temps pour recharger un chargeur
    BITMAP* image_ennemi; //Image de l'ennemi
    int ennemi_actif;//savoir s'il est mort ou pas
} ennemi;
typedef struct tir_ennemi {
    int x;
    int y;
    int dx;
    int dy;
    int tx;
    int ty;
    int tir_actif;
    BITMAP* image_tir;
}tir_ennemi;

void init_ennemi_nv1(ennemi* mon_ennemi);
void init_ennemi_nv2(ennemi mon_ennemi[2]);
void init_ennemi_nv3(ennemi* mon_ennemi);
void afficher_et_deplacer_ennemi_nv1(BITMAP* buffer,  ennemi* tab_ennemis, int temps_max);
void afficher_et_deplacer_ennemi_nv2(BITMAP* buffer, ennemi mon_ennemi[2], int temps_max);
int collision_vaisseau_ennemis(t_vaisseau *vaisseau, ennemi *ennemi_niveau1, int *ennemi_courant) ;
void collision_tir_ennemi(t_tir tirs[NB_TIR], ennemi ennemis[], int nb_ennemis,t_vaisseau* vaisseau);
void init_tir(tir_ennemi* tir_ennemi,ennemi ennemi_niveau,BITMAP* image_tir_ennemi) ;
void tir_ennemi_niveau2(tir_ennemi tir_ennemi[NB_TIR_ENNEMI], ennemi* ennemi_niveau2, t_vaisseau* vaisseau, BITMAP* buffer);
void afficher_ennemi_nv3(BITMAP* buffer, ennemi* boss, int temps_max);
void collision_tir_vaisseau(t_tir tirs_ennemi[NB_TIR_ENNEMI],t_vaisseau* vaisseau,ennemi* ennemi) ;
void tir_ennemi_boss(tir_ennemi tir_ennemi[NB_TIR_ENNEMI], ennemi* boss, t_vaisseau* vaisseau, BITMAP* buffer);

#endif //ENEMIES_H
