#ifndef ENEMIES_H
#define ENEMIES_H

#include <allegro.h>

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
    BITMAP* image_ennemi_nv1; //Image de l'ennemi du premier niveau
} ennemi;

void init_ennemi_nv1(ennemi* mon_ennemi);
void init_ennemi_nv2(ennemi* mon_ennemi);
void init_ennemi_nv3(ennemi* mon_ennemi);
void afficher_et_deplacer_ennemi(BITMAP* buffer, BITMAP* fond_nv1, ennemi* tab_ennemis, int temps_max);

#endif //ENEMIES_H