#include <stdio.h>
#include <allegro.h>
#include "vaisseau.h"

void initialisation_allegro();




int main(void)
{
    initialisation_allegro();

    stretch_sprite(screen,load_bitmap("Niveau 1.bmp",NULL),0,0,SCREEN_W,SCREEN_H);
    stretch_sprite(screen,load_bitmap("enemi.bmp",NULL),50,50,90,90);
    readkey();
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
}
