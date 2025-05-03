#include <stdio.h>
#include <allegro.h>
#include "vaisseau.h"
#include "interface.h"
//Prototypes des SP

void initialisation_allegro();
int main(void) {
    initialisation_allegro();

    //Pour le scroller le fond
    int scroll_x=0;
    int active_scroll=1;
    //VAR de tir
    int tir_enclenche = 0;
    t_tir  tirs[NB_TIR];
    t_tir tirs_speciaux[NB_TIR];
    for (int i = 0; i < NB_TIR; i++) {
        tirs[i].tir_actif=0;//tir desactivé au début
    }
    for (int i = 0; i < NB_TIR; i++) {
        tirs_speciaux[i].tir_actif=0;//tir desactivé au début
    }
    //


    t_vaisseau vaisseau;
    t_tir tir;
    BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION];
    //init du vaisseau et tir
    initialisation_vaisseau_tir(&vaisseau,&tir,explosion_sprites);

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* fond_jeu_collision =load_bitmap("fond jeu.bmp", NULL);

    if (!fond_jeu_collision) {//fond pour collision
        allegro_message("Erreur lors du chargement de fond_jeu.bmp");
        return 1;
    }
    BITMAP* fond_jeu_normal=load_bitmap("fond jeu normal.bmp",NULL);
    if (!fond_jeu_normal) {
        allegro_message("Erreur de fond jeu normal.bmp");
        return 1;
    }

    int cptimg=0, tmpimg=4;
    int img_courante=0;



    // varibles concernatn l'animation de l'explosion
    int cptimg_ex=0, tmpimg_ex=7;
    int img_courante_ex=0;



    int son_active=0;

    while (!key[KEY_ESC]) {//jeu
        if(active_scroll==1) {
            scroll_x+=VITESSE_DE_SCROLL;
        }

        int decalge_x=scroll_x%(fond_jeu_normal->w+1);
        stretch_blit(fond_jeu_normal,buffer,decalge_x,0,fond_jeu_normal->w,fond_jeu_normal->h,0,0,SCREEN_W,SCREEN_H);

        stretch_sprite(buffer,vaisseau.vaisseau_bmp[img_courante],vaisseau.x,vaisseau.y,vaisseau.tx,vaisseau.ty);
        //
        deplacement_vaisseau(&vaisseau,&cptimg,&img_courante,tmpimg);
        //
        gestion_score_point_vie_vaisseau(&vaisseau, collision_vaisseau_decor(&active_scroll,decalge_x,&vaisseau,fond_jeu_collision,&cptimg_ex,tmpimg_ex,&img_courante_ex,explosion_sprites,buffer,&img_courante));
        //tir)

        //tir
        tir_fonction(&son_active,tirs,tir,vaisseau,buffer,&tir_enclenche);

        stretch_blit(buffer,screen,0,0,buffer->w,buffer->h,0,0,SCREEN_W,560);
        tir_enclenche = key[KEY_SPACE];
        rest(16);
    }

    // Libération de la mémoire
    destroy_sample(tir.son_tir);
    remove_sound();//ferme le syst audio
    destroy_bitmap(buffer); // Libère la mémoire du buffer
    destroy_bitmap(vaisseau.vaisseau_bmp[0]);

    allegro_exit();

    return 0;
}
END_OF_MAIN();




//Sous programmes de bases allegro

void initialisation_allegro(){
    allegro_init(); // appel obligatoire (var.globales, recup. infos système ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    if (install_sound(DIGI_AUTODETECT,MIDI_NONE,NULL)!=0) {//initialise l utilisation du son
        printf("N a pas pu initialise le son\n");
    };
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    //ici: identique à celle du bureau
    set_color_depth(desktop_color_depth());
    //sélection du mode graphique
    // avec choix d'un driver+mode+résolution de l'écran
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0){
        // message et sortie de prog. si échec
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}
