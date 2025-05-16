#include <stdio.h>
#include <allegro.h>
#include "vaisseau.h"
#include "interface.h"
#include "enemies.h"
//Prototypes des SP

void initialisation_allegro();

int main(void) {

    initialisation_allegro();// initialisation des paramètres allegro
    //Pour le scroller le fond
    /*************************************************************************   VARIABLES   *********************************************************************/
    int scroll_x=0;
    int active_scroll=1;
    //VAR de tir
    int tir_enclenche = 0;
    t_tir  tirs[NB_TIR];
    for (int i = 0; i < NB_TIR; i++) {
        tirs[i].tir_actif=0;//tir desactivé au début
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

    //Ennemies
    ennemi ennemi_niveau1[10];
        //
    for (int i = 0; i < 10; i++) {
        init_ennemi_nv1(&ennemi_niveau1[i]);
    }
    ennemi ennemi_niveau2[10];
    tir_ennemi tirs_ennemi[NB_TIR_ENNEMI] ;
    BITMAP* image_tir_ennemi=load_bitmap("tir_ennemi.bmp", NULL);
    for (int i = 0; i < 10; i++) {
        init_ennemi_nv2(&ennemi_niveau2[i]);
        for (int j = 0; j < NB_TIR_ENNEMI; j++) {
            init_tir(&tirs_ennemi[j],ennemi_niveau2[i],image_tir_ennemi);
        }
    }



   ennemi boss;
    init_ennemi_nv3(&boss);
    int temps_max = 1;
    int ennemi_courant = 0;
    int ennemi_courant_2 = 0;
    int ennemi_courant_3 = 0;
    int ennemi_courant_4 = 0;
    //variables pour niveau
    int fin_nv1=1730;
    int fin_nv2=3467;
    int fin_nv3=5202 ;
    //tir



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


    while (!key[KEY_ESC]) {
       if(key[KEY_P]) {
           pause(pause_img,buffer_P);
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
            //niveau1
            if(scroll_x>=0 && scroll_x<=fin_nv1 ) {
                for(int i=0;i<= ennemi_courant;i++) {
                    if(ennemi_niveau1[i].ennemi_actif) {
                        afficher_et_deplacer_ennemi_nv1(buffer,&ennemi_niveau1[i],temps_max);
                    }

                }
                //TIR VAISSEAU SUR ENNEMI

                // COLLISION AVEC ENNNEMI

                    // Active le suivant quand le précédent atteint le milieu
                    if (ennemi_courant < 9 && ennemi_niveau1[ennemi_courant].x == SCREEN_W / 2) {
                        ennemi_courant++;
                    }
                //niveau2
            }else if(scroll_x>fin_nv1 && scroll_x<=fin_nv2) {
                for (int i = 0; i < 10; i++) {
                    ennemi_niveau1[i].x = SCREEN_W+10;
                    ennemi_niveau1[i].y = rand() % (408-50 - 115 + 1) + 115;
                }
                for(int i=0;i<= ennemi_courant_2;i++) {
                    if(ennemi_niveau2[i].ennemi_actif) {
                        afficher_et_deplacer_ennemi_nv2(buffer,&ennemi_niveau2[i],temps_max);
                        ennemi_niveau2[(i+1)%10].x=ennemi_niveau2[i].x +100;
                        tir_ennemi_niveau2(tirs_ennemi,&ennemi_niveau2[i],buffer);
                    }
                }
                //TIR VAISSEAU SUR ENNEMI

                // COLLISION AVEC ENNNEMI

                // Active le suivant quand le précédent atteint le milieu
                if (ennemi_courant_2 < 9 ) {
                    ennemi_courant_2++;
                }

                // Activer le suivant si le dernier actif a atteint le milieu de l'écran
                if (ennemi_courant_2 < 9) {
                    if (ennemi_niveau2[ennemi_courant_2].x < SCREEN_W / 2) {
                        ennemi_courant_2++;
                        ennemi_niveau2[ennemi_courant_2].ennemi_actif = 1;
                    }
                }


            //niveau3
            }else if(scroll_x>fin_nv2 && scroll_x<=fin_nv3) {

               /* for(int i=0;i<= ennemi_courant_3;i++) {
                    if(ennemi_niveau1[i].ennemi_actif) {
                        afficher_et_deplacer_ennemi_nv1(buffer,&ennemi_niveau1[i],temps_max);
                    }

                }
                //TIR VAISSEAU SUR ENNEMI

                // COLLISION AVEC ENNNEMI

                // Active le suivant quand le précédent atteint le milieu
                if (ennemi_courant_3 < 9 && ennemi_niveau1[ennemi_courant_3].x == SCREEN_W / 2) {
                    ennemi_courant_3++;
                }*/
                for(int i=0;i<= ennemi_courant_4;i++) {
                    if(ennemi_niveau2[i].ennemi_actif) {
                        afficher_et_deplacer_ennemi_nv2(buffer,&ennemi_niveau2[i],temps_max);
                        ennemi_niveau2[(i+1)%10].x=ennemi_niveau2[i].x +100;
                    }

                }
                //TIR VAISSEAU SUR ENNEMI

                // COLLISION AVEC ENNNEMI

                // Active le suivant quand le précédent atteint le milieu
                if (ennemi_courant_4 < 9 ) {
                    ennemi_courant_4++;
                }

            }else if(scroll_x>fin_nv3) {
                scroll_x=fin_nv3+1;
                active_scroll=0;
                afficher_ennemi_nv3(buffer,&boss,temps_max);

            }

            stretch_sprite(buffer,vaisseau.vaisseau_bmp[img_courante],vaisseau.x,vaisseau.y,vaisseau.tx,vaisseau.ty);
            deplacement_vaisseau(&vaisseau,&cptimg,&img_courante,tmpimg);
            gestion_score_point_vie_vaisseau(&vaisseau,collision_vaisseau_decor(&active_scroll,scroll_x,&vaisseau,fond_collision,&cptimg_ex,tmpimg_ex,&img_courante_ex,explosion_sprites,buffer,&img_courante),collision_vaisseau_ennemis(&vaisseau,ennemi_niveau1,&ennemi_courant,&active_scroll));
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
        destroy_bitmap(fond_menu);
        destroy_bitmap(pause_img);
        destroy_bitmap(fond_jeu);
        destroy_bitmap(fond_collision);
        destroy_bitmap(buffer); // Libère la mémoire du buffer
        destroy_bitmap(buffer_menu);
        destroy_bitmap(buffer_P);
        for (int i = 0; i < 10; i++) {
            destroy_bitmap(ennemi_niveau1[i].image_ennemi);
        }
    for(int i=0;i<10;i++) {
        destroy_bitmap(ennemi_niveau2[i].image_ennemi);
    }
    destroy_bitmap(boss.image_ennemi);
    for(int i=0; i<NB_TIR_ENNEMI; i++) {
        destroy_bitmap(tirs_ennemi[i].image_tir);
    }


        for (int i = 0; i < NB_SPRITES_VAISSEAU; i++) {
            destroy_bitmap(vaisseau.vaisseau_bmp[i]);
        }
    blit(fond_jeu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

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
