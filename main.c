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
    BITMAP* fond_nv2 = load_bitmap("fond_nv2.bmp", NULL);
    BITMAP* fond_nv3 = load_bitmap("fond_nv3.bmp", NULL);

    /* Création et initialisation des ennemis */
    ennemi tab_ennemi[10];
    for (int i = 0; i < 10; i++) {
        init_ennemi_nv3(&tab_ennemi[i]);
    }

    int temps_max = 2;
    while (!key[KEY_ESC]) {
        // Dessine le fond UNE FOIS par frame
        stretch_sprite(buffer, fond_nv3, 0, 0, SCREEN_W, SCREEN_H);
        afficher_ennemi_nv3(buffer, &tab_ennemi[0], temps_max);
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
