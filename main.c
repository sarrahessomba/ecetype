#include <stdio.h>
#include <allegro.h>
#include "ennemis.h"


void initialisation_allegro();




int main(void)
{
    srand(time(NULL));
    initialisation_allegro();
    /* Ennemis niveau 1*/

    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W,SCREEN_H);

    int compteur_temps = 0;
    int temps_max = 20;

    ennemi tab_ennemi[10];
    BITMAP*  fond_nv1 = load_bitmap("fond_nv1.bmp",NULL);

    for (int i = 0; i < 10; i++) {
        init_ennemi_nv1(&tab_ennemi[i]);
    }

    while (!key[KEY_ESC]) {
        afficher_et_deplacer_ennemi(buffer, fond_nv1, &tab_ennemi[0], &compteur_temps, temps_max);


        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

    /* Fin Ennemis niveau 1*/
    allegro_exit();



    return 0;
}
END_OF_MAIN();




void initialisation_allegro(){
    allegro_init(); // Appel obligatoire (var. globales, recup. infos système ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    //ici : identique à celle du bureau
    set_color_depth(desktop_color_depth());
    //sélection du mode graphique
    // avec choix d'un driver+mode+résolution de l'écran
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,900,700,0,0)!=0){
        // Message et sortie de prog. Si échec
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}
