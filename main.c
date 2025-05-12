#include <stdio.h>
#include <allegro.h>
#include "vaisseau.h"
#include "interface.h"
//Prototypes des SP

void initialisation_allegro();

void transition_crossfade(BITMAP* from, BITMAP* to, int speed_ms) {
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* img1 = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* img2 = create_bitmap(SCREEN_W, SCREEN_H);

    stretch_blit(from, img1, 0, 0, from->w, from->h, 0, 0, SCREEN_W, SCREEN_H);
    stretch_blit(to, img2, 0, 0, to->w, to->h, 0, 0, SCREEN_W, SCREEN_H);

    for (int alpha = 0; alpha <= 255; alpha += 5) {
        clear_to_color(buffer, makecol(0, 0, 0));

        // Affiche image1 avec opacité dégressive
        set_trans_blender(0, 0, 0, 255 - alpha);
        draw_trans_sprite(buffer, img1, 0, 0);

        // Affiche image2 avec opacité croissante
        set_trans_blender(0, 0, 0, alpha);
        draw_trans_sprite(buffer, img2, 0, 0);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(speed_ms);
    }

    destroy_bitmap(buffer);
    destroy_bitmap(img1);
    destroy_bitmap(img2);
}
int main(void) {
    initialisation_allegro();// initialisation des paramètres allegro
    //Pour le scroller le fond
    /*************************************************************************   VARIABLES   *********************************************************************/
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
    //varaibles pour le vaisseau
    t_vaisseau vaisseau;
    t_tir tir;
    BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION];
    //init du vaisseau et tir
    initialisation_vaisseau_tir(&vaisseau,&tir,explosion_sprites);
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* fond_jeu=load_bitmap("fond_jeu.bmp",NULL);
    if(!fond_jeu) {
        printf("Fond jeu erreur\n");
        return -1;
    }
    BITMAP* fond_collision=load_bitmap("fond_collision.bmp",NULL);
    if(!fond_collision) {
        printf("Fond collision erreur\n");
        return -1;
    }
    BITMAP* fond_transition=load_bitmap("fond_transition.bmp",NULL);
    if (!fond_transition) {
        allegro_message("Erreur de fond_transition.bmp");
        return -1;
    }

    int cptimg=0, tmpimg=4;
    int img_courante=0;



    // varibles concernatn l'animation de l'explosion
    int cptimg_ex=0, tmpimg_ex=7;
    int img_courante_ex=0;


//variables pour le son
    int son_active=0;
    int fin=0;
// interface du menu, zone de nom et pause et fin
    BITMAP *fond_menu = load_bitmap("interface/menu.bmp", NULL);
    if (!fond_menu) {
        allegro_message("Erreur de chargement de interface/menu.bmp");
        return -1;
    }
    BITMAP* zone_nom=load_bitmap("interface/nom.bmp",NULL);
    if (!zone_nom) {
        allegro_message("Erreur de chargement de interface/nom.bmp");
        return -1;
    }
    BITMAP* pause_img=load_bitmap("interface/pause.bmp",NULL);
    if (!pause_img) {
        allegro_message("Erreur de chargement de interface/pause.bmp");
        return -1;
    }

    BITMAP *buffer_menu = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* buffer_P=create_bitmap(SCREEN_W,SCREEN_H);
    //initialisation des position des boutons
    Bouton btn_nouvelle  = {200, 250, 300, 60};
    Bouton btn_reprendre = {200, 310, 300, 60};

/*************************************************************************   VARIABLES   *********************************************************************/

    // MENU PRINCIPAL
    while (!key[KEY_ESC]) {
        afficher_menu(fond_menu, buffer_menu);

        if (mouse_b & 1) {
            int mx = mouse_x;
            int my = mouse_y;

            if (souris_sur_bouton(btn_nouvelle, mx, my)) {
                BITMAP* buffer2=create_bitmap(SCREEN_W,SCREEN_H);
                char pseudo[20] = "";
                saisir_pseudo(pseudo, sizeof(pseudo),buffer2,zone_nom);
                allegro_message("Bienvenue %s !", pseudo);
                break;
            }
            if (souris_sur_bouton(btn_reprendre, mx, my)) {
                allegro_message("Reprendre la partie !");
                break;
            }
        }

        rest(10);
    }
int pause_active=0;

    while (!key[KEY_ESC]) {
        if(key[KEY_P]) {
            pause_active=1;
            while(key[KEY_P]) {
                rest(10);
            }

        }
        while(pause_active) {

            clear_bitmap(buffer_P);
            stretch_blit(pause_img,buffer_P,0,0,pause_img->w,pause_img->h,0,0,SCREEN_W,SCREEN_H);
            blit(buffer_P,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            if(key[KEY_P ] ) {
                pause_active=0;
                while(key[KEY_P]) {//attendre que KEY_P soit relaché
                    rest(10);
                }
            }
            if(key[KEY_ESC]) {
                break;
            }

        }
        if(!fin) {
            if(active_scroll==1) {
                scroll_x += VITESSE_DE_SCROLL;
                if(scroll_x>=fond_jeu->w) {
                    scroll_x=0;
                    fin=1;
                }
            }
            int offset = scroll_x % fond_jeu->w;

            // Affiche la partie droite du fond
            blit(fond_jeu, buffer, offset, 0, 0, 0, SCREEN_W, SCREEN_H);

            // Si besoin, recolle le début du fond à droite
            if (offset + SCREEN_W > fond_jeu->w) {
                int reste = fond_jeu->w - offset;
                blit(fond_jeu, buffer, 0, 0, reste, 0, SCREEN_W - reste, SCREEN_H);
            }

            stretch_sprite(buffer,vaisseau.vaisseau_bmp[img_courante],vaisseau.x,vaisseau.y,vaisseau.tx,vaisseau.ty);
            deplacement_vaisseau(&vaisseau,&cptimg,&img_courante,tmpimg);
            gestion_score_point_vie_vaisseau(&vaisseau,collision_vaisseau_decor(&active_scroll,scroll_x,&vaisseau,fond_collision,&cptimg_ex,tmpimg_ex,&img_courante_ex,explosion_sprites,buffer,&img_courante));

            //tir
            tir_fonction(&son_active,tirs,tir,vaisseau,buffer,&tir_enclenche);

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            tir_enclenche = key[KEY_SPACE];
            rest(20);
        }
    }

        allegro_message("sortie");
        // Libération de la mémoire
        destroy_sample(tir.son_tir);
        remove_sound();//ferme le syst audio
        destroy_bitmap(buffer); // Libère la mémoire du buffer
        destroy_bitmap(vaisseau.vaisseau_bmp[0]);
    destroy_bitmap(fond_menu);
        destroy_bitmap(fond_jeu);
        destroy_bitmap(fond_collision);

        for (int i = 0; i < NB_SPRITES_VAISSEAU; i++) {
            destroy_bitmap(vaisseau.vaisseau_bmp[i]);
        }
    blit(fond_jeu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    readkey();

    transition_crossfade(fond_jeu, fond_transition, 10);

    readkey();
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
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,530,0,0)!=0){
        // message et sortie de prog. si échec
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}
