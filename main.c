#include <stdio.h>
#include <allegro.h>
#include "vaisseau.h"

//Prototypes des SP

void initialisation_allegro();

int main(void) {
    initialisation_allegro();


    int tir_validee=0;
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
    int cptimg_ex=0, tmpimg_ex=4;
    int img_courante_ex=0;

    //
    int tir_special_actif=0;
    int cpt=0;
int fini_spe=0;
    int fini=0;

    while (!key[KEY_ESC]) {//jeu

        stretch_blit(fond_jeu_normal,buffer,0,0,fond_jeu_normal->w,fond_jeu_normal->h,0,0,SCREEN_W,SCREEN_H);
        stretch_sprite(buffer,vaisseau.vaisseau_bmp[img_courante],vaisseau.x,vaisseau.y,vaisseau.tx,vaisseau.ty);
        //
        deplacement_vaisseau(&vaisseau,&tir_validee,&cptimg,&img_courante,tmpimg);
        //
        collision_vaisseau_decor(&vaisseau,fond_jeu_collision,&cptimg_ex,tmpimg_ex,&img_courante_ex,explosion_sprites,buffer,&img_courante);


        if (tir_validee) {
            if (tir_special_actif) {
                tir.cptimg++;
                if(tir.cptimg>=tmpimg) {
                    cptimg=0;
                    tir.img_courante++;
                    if (tir.img_courante>=NB_SPRITES_TIR-1) {
                        tir.img_courante=NB_SPRITES_TIR-1;
                    }
                }
                stretch_sprite(buffer,tir.tir_special_bmp[tir.img_courante],tir.x,tir.y,tir.tir_special_bmp[tir.img_courante]->w,tir.tir_special_bmp[tir.img_courante]->h);
                tir.x+=tir.dx;

                if(tir.x > SCREEN_W ) {
                    tir_validee=0;
                    tir.x = vaisseau.x + vaisseau.tx;
                    if(tir.img_courante==NB_SPRITES_TIR-1) {
                        fini_spe=1;
                    }

                }

            }else {

                stretch_sprite(buffer,tir.tir_bmp,tir.x,tir.y,tir.tx,tir.ty);
                tir.x+=tir.dx;

                if(tir.x > SCREEN_W ) {
                    tir_validee=0;
                    tir.x = vaisseau.x + vaisseau.tx;
                    cpt++;
                    if(cpt>=3) {
                        cpt=3;
                    }
                }
            }




        }
        if(cpt==3) {
            tir_special_actif=1;
        }
        if(fini_spe) {
            cpt=0;
            tir.img_courante=0;
            tir_special_actif=0;
            fini_spe=0;
        }
        // Si la touche espace est pressée et que le tir n'est pas validé
        if (key[KEY_SPACE] && !tir_validee) {
            tir_validee = 1;  // Valider le tir
            tir.x = vaisseau.x + vaisseau.tx;  // Positionner le tir juste à droite du vaisseau
            tir.y = vaisseau.y + vaisseau.ty / 2 - 5;  // Centrer verticalement le tir
        }

        stretch_blit(buffer,screen,0,0,buffer->w,buffer->h,0,0,SCREEN_W,560);
        rest(16);
    }

    // Libération de la mémoire
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

