//
// Created by sarra on 4/28/2025.
//

#include "interface.h"
#include <allegro.h>
//tout ce qui est menu et fond du jeu

// Fonction pour tester si la souris est sur un bouton
int souris_sur_bouton(Bouton b, int mx, int my) {
    return (mx >= b.x && mx <= b.x + b.w &&
            my >= b.y && my <= b.y + b.h);
}

// Affiche le menu sans texte (image seulement)
void afficher_menu(BITMAP *fond, BITMAP *buffer) {
    blit(fond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

// Fonction pour saisir un pseudo
void saisir_pseudo(char *pseudo, int max, BITMAP* buffer,BITMAP* zone_nom) {
    int len = 0;
    clear_keybuf();

    while (1) {
        clear_bitmap(buffer);
        blit(zone_nom, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        textprintf_ex(buffer, font, 364, 355, makecol(255, 255, 255), -1,
                      "%s", pseudo);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (keypressed()) {
            int keycode = readkey();
            char c = keycode & 0xff;

            if ((keycode >> 8) == KEY_ENTER) {
                pseudo[len] = '\0';
                break;
            }
             if ((keycode >> 8) == KEY_BACKSPACE && len > 0) {
                len--;
                pseudo[len] = '\0';
            }
            else if (c >= 32 && c <= 126 && len < max - 1) {
                pseudo[len++] = c;
                pseudo[len] = '\0';
            }
        }

        rest(10);
    }
}
