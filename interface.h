//
// Created by sarra on 4/28/2025.
//

#ifndef INTERFACE_H
#define INTERFACE_H
#define VITESSE_DE_SCROLL 2//1 si plus lent
#include <allegro.h>
#include "vaisseau.h"

typedef struct {//structures pour les boutons reprendre, nouvelle partie et quitter
    int x, y, w, h;
} Bouton;

//sous programmes

int souris_sur_bouton(Bouton b, int mx, int my);// pour comparer la position des bouto par rapport au menu
void afficher_menu(BITMAP *fond, BITMAP *buffer);// pour afficher le menu
void saisir_pseudo(char *pseudo, int max, BITMAP* buffer, BITMAP* zone_nom) ;//pour saisir le pseudo
void pause(BITMAP *pause_img, BITMAP *buffer_P,char* pseudo,int scroll_x,t_vaisseau vaisseau) ;
void sauvegarder_partie(const char *pseudo, int scroll_x, t_vaisseau vaisseau) ;
int charger_partie( int *scroll_x,t_vaisseau* vaisseau,char pseudo[20]);

#endif //INTERFACE_H
