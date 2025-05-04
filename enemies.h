#ifndef ENEMIES_H
#define ENEMIES_H

typedef struct ennemi {
    int x; // Abscisse
    int y; // Ordonnée
    int dx; // Déplacement horizontal
    int dy; // Déplacement vertical
    int taille_x; // Taille en x
    int taille_y; // Taille en y
    int pv; // Points de vie
    int dmg; // Points de dégâts par tir
    int chargeur; // Nombre de balles dans un chargeur
    int reload; // Temps pour recharger un chargeur
} ennemi;

#endif //ENEMIES_H
