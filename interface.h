//
// Created by sarra on 4/28/2025.
//

#ifndef INTERFACE_H
#define INTERFACE_H

#endif //INTERFACE_H
#include <stdio.h>
#include <allegro.h>

#define SCREEN_W 800
#define SCREEN_H 600

BITMAP *decor;
BITMAP *buffer;
int scroll_x = 0;

void AFdecor() {
    // Calcule la position de départ
    int x1 = -scroll_x;
    int x2 = x1 + decor->w;

    // Affiche les deux décors à la suite
    blit(decor, buffer, 0, 0, x1, 0, decor->w, SCREEN_H);
    blit(decor, buffer, 0, 0, x2, 0, decor->w, SCREEN_H);

    // Mise à jour du défilement
    scroll_x++;
    if (scroll_x >= decor->w) {
        scroll_x = 0; // On revient au début
    }
}

int main(void) {
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (!buffer) {
        allegro_message("Erreur de création du buffer");
        return 1;
    }

    decor = load_bitmap("decor.bmp", NULL);
    if (!decor) {
        allegro_message("Erreur de chargement du décor");
        return 1;
    }

    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);

        AFdecor();

        textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "Scroll infini fluide - ESC pour quitter");
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        rest(16);
    }
    destroy_bitmap(decor);
    destroy_bitmap(buffer);
    return 0;
}
END_OF_MAIN();