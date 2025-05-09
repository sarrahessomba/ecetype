#include <stdio.h>
#include <allegro.h>
#include "ennemis.h"

void initialisation_allegro();

int main(void)
{
    srand(time(NULL));
    initialisation_allegro();
    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* fond_nv1 = load_bitmap("fond_nv1.bmp", NULL);

    /* Création et initialisation des ennemis */
    ennemi tab_ennemi[10];
    for (int i = 0; i < 10; i++) {
        init_ennemi_nv1(&tab_ennemi[i]);
    }

    int temps_max = 2;
    int ennemi_courant = 0;

    while (!key[KEY_ESC]) {
        // Dessine le fond UNE FOIS par frame
        stretch_sprite(buffer, fond_nv1, 0, 0, SCREEN_W, SCREEN_H);

        // Affiche les ennemis déjà activés
        for (int i = 0; i <= ennemi_courant; i++) {
            afficher_et_deplacer_ennemi(buffer, fond_nv1, &tab_ennemi[i], temps_max);
        }

        // Active le suivant quand le précédent atteint le milieu
        if (ennemi_courant < 9 && tab_ennemi[ennemi_courant].x == SCREEN_W / 2) {
            ennemi_courant++;
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    allegro_exit();
    return 0;
}
END_OF_MAIN();

void initialisation_allegro() {
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 900, 700, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}
