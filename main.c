#include <stdio.h>
#include <allegro.h>
#include "vaisseau.h"

//Prototypes des SP

void initialisation_allegro();

int main(void)
{
    initialisation_allegro();
int tir_validee=0;
    t_vaisseau vaisseau;
    t_tir tir;
    //init du vaisseau et tir
    initialisation_vaisseau_tir(&vaisseau,&tir);
    //variables pour collision avec le decor
    int x_img=0;
    int y_img=0;
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
    int px; // position x enregistre lorsque le tir est confirme
    int py;// position yz enregistre lorsque le tir est confirme
    //
    int cpt=0;
    int tmp=6;
    //
    while (!key[KEY_ESC]) {

        stretch_blit(fond_jeu_normal,buffer,0,0,fond_jeu_normal->w,fond_jeu_normal->h,0,0,SCREEN_W,SCREEN_H);
        stretch_sprite(buffer,vaisseau.vaisseau_bmp[img_courante],vaisseau.x,vaisseau.y,vaisseau.tx,vaisseau.ty);




        deplacement_vaisseau(&vaisseau,&tir_validee,&cptimg,&img_courante,tmpimg);



        //
        x_img=(vaisseau.x*fond_jeu_collision->w)/(SCREEN_W); //coordonees x sur le decor
        y_img=((vaisseau.y )*(fond_jeu_collision->h +16))/(SCREEN_H);//coordonees y sur le decor
        putpixel(buffer,vaisseau.x +16,vaisseau.y+33,makecol(255,255,255));
        if(getpixel(fond_jeu_collision,x_img,y_img)==makecol(255,255,255) ){//|| getpixel(fond_jeu_collision,vaisseau.x + vaisseau.tx,vaisseau.y + vaisseau.ty)==makecol(255,255,255) || getpixel(fond_jeu_collision,vaisseau.x + vaisseau.tx,vaisseau.y )==makecol(255,255,255) || getpixel(fond_jeu_collision,vaisseau.x ,vaisseau.y + vaisseau.ty)==makecol(255,255,255)) {
            printf("touched\n");
        }

        if (tir_validee) {
            stretch_sprite(buffer,tir.tir_bmp,tir.x,tir.y,tir.tx,tir.ty);
            tir.x+=tir.dx;
            tir.y=vaisseau.y + vaisseau.ty/2 -5;
            if(tir.x > SCREEN_W ) {
               tir_validee=0;
                tir.x = vaisseau.x + vaisseau.tx;
            }
        }

        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(16); // Pour éviter d'utiliser 100% du CPU (~60 fps)
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

