//
// Created by sarra on 4/28/2025.
//

#ifndef ENEMIES_H
#define ENEMIES_H
#include <allegro.h>
#include "vaisseau.h"

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

void init_ennemi_nv1(ennemi* mon_ennemi);
void init_ennemi_nv2(ennemi* mon_ennemi);
void init_ennemi_nv3(ennemi* mon_ennemi);
void afficher_et_deplacer_ennemi_nv1(BITMAP* buffer,  ennemi* tab_ennemis, int temps_max);
void afficher_et_deplacer_ennemi_nv2(BITMAP* buffer,  ennemi* mon_ennemi, int temps_max);
int collision_vaisseau_ennemis(t_vaisseau *vaisseau, ennemi *ennemi_niveau1, int *ennemi_courant, int *scroll_x) ;
int choisir_y();
int collision_tir_ennemi (ennemi* ennemi,t_tir* tir);
#endif //ENEMIES_H
