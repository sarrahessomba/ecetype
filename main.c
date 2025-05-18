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
    /*************************************************************************   VARIABLES   *******************************************************************************/
    //VAR de tir
    int tir_enclenche = 0;
    t_tir  tirs[NB_TIR];
    t_tir tir;


    //varaibles pour le vaisseau
    t_vaisseau vaisseau;
    BITMAP* explosion_sprites[NB_SPRITES_EXPLOSION];
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
    char pseudo[20] = "";//variable pour entrer le nom
    BITMAP* pause_img=load_bitmap("interface/pause.bmp",NULL);
    if (!pause_img) {
        allegro_message("Erreur de chargement de interface/pause.bmp");
        return -1;
    }
    BITMAP* perdu_img=load_bitmap("interface/perdu.bmp",NULL);
    if (!perdu_img) {
        allegro_message("Erreur de chargement de interface/perdu.bmp");
    }
    BITMAP* gagne_img=load_bitmap("interface/gagne.bmp",NULL);
    if (!gagne_img) {
        allegro_message("Erreur de chargement de interface/gagne.bmp");
    }
    BITMAP *buffer_menu = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* buffer_P=create_bitmap(SCREEN_W,SCREEN_H);
    //initialisation des position des boutons

    Bouton btn_nouvelle  = {200, 250, 300, 60};
    Bouton btn_reprendre = {200, 310, 300, 60};

    //Ennemies
    ennemi ennemi_niveau1[10];
        //

    ennemi ennemi_niveau2[2];
    tir_ennemi tirs_ennemi1[NB_TIR_ENNEMI] ;
    tir_ennemi tirs_ennemi2 [NB_TIR_ENNEMI];
    tir_ennemi tirs_ennemi3 [NB_TIR_ENNEMI];
    BITMAP* image_tir_ennemi=load_bitmap("tir_ennemi.bmp", NULL);

   ennemi boss;

    int temps_max = 1;

    int nb_ennemi_2 = 1;
    int nb_ennemi_3=1;

    int scroll_x=0;
    //variables pour niveau
    int fin_nv1=1730;
    int fin_nv2=3467;
    int fin_nv3=5202 ;
    int rejouer=0;
    //chargement partie
    int partie_charge=0;//partie pas charge
    int scroll_x_partie_charge=0;



/*************************************************************************   VARIABLES   *********************************************************************/

    // MENU PRINCIPAL
    while (!key[KEY_ESC]) {
        afficher_menu(fond_menu, buffer_menu);

        if (mouse_b & 1) {
            int mx = mouse_x;
            int my = mouse_y;

            if (souris_sur_bouton(btn_nouvelle, mx, my)) {
                BITMAP* buffer2=create_bitmap(SCREEN_W,SCREEN_H);

                saisir_pseudo(pseudo, sizeof(pseudo),buffer2,zone_nom);
                allegro_message("Bienvenue %s !", pseudo);
                break;
            }
            if (souris_sur_bouton(btn_reprendre, mx, my)) {
                charger_partie(&scroll_x_partie_charge,&vaisseau,pseudo);
                partie_charge=1;
                allegro_message("Reprendre la partie !");
                break;
            }
        }

        rest(10);
    }

do{
    rejouer=0;
    //INITIALISTION
    //BOSS
    init_ennemi_nv3(&boss);
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        init_tir(&tirs_ennemi3[i],boss,image_tir_ennemi);
    }
    //ENNEMIS 2
    init_ennemi_nv2(ennemi_niveau2);
    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
        init_tir(&tirs_ennemi1[i],ennemi_niveau2[0],image_tir_ennemi);
        init_tir(&tirs_ennemi2[i],ennemi_niveau2[1],image_tir_ennemi);
    }
    //ENNEMIS 1
    for (int i = 0; i < 10; i++) {
        init_ennemi_nv1(&ennemi_niveau1[i]);
    }
    int ennemi_courant = 0;
    int compteur_ennemi_apparition = 0;
    int ennemi_courant2 = 0;
    int compteur_ennemi_apparition2 = 0;
//VAISSEAU ET TIRS
    initialisation_vaisseau_tir(&vaisseau,&tir,explosion_sprites);
    for (int i = 0; i < NB_TIR; i++) {
        tirs[i].tir_actif=0;//tir desactivé au début du jeuu

    }
//
if(partie_charge==0) {
    scroll_x=0;
}else if(partie_charge==1) {
    scroll_x=scroll_x_partie_charge;
    if(scroll_x>=0 && scroll_x<=fin_nv1) {
        scroll_x=0;
    }else if(scroll_x>fin_nv1 && scroll_x<=fin_nv2) {
        scroll_x=fin_nv1+1;
    }else if(scroll_x>fin_nv2 && scroll_x<=fin_nv3) {
        scroll_x=fin_nv2+1;
    }else if(scroll_x>fin_nv3) {
        scroll_x=fin_nv3+1;
    }
    partie_charge=0;
}
    int active_scroll=1;
    fin=0;
    while (!key[KEY_ESC]) {
        if(key[KEY_P]) {
            pause(pause_img,buffer_P,pseudo,scroll_x,vaisseau);
        }

        if (vaisseau.nb_vies == 0) {
            blit(perdu_img, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            while (!key[KEY_ENTER] && !key[KEY_ESC]) {
                rest(10);
            }

            if (key[KEY_ENTER]) {
                rejouer = 1;
                break; // sortir du while et aller dans do while pour relancer le jeu
            }
            if (key[KEY_ESC]) {
                return 0;
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

            // recolle le début du fond à droite
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
                collision_tir_ennemi(tirs,ennemi_niveau1,10,&vaisseau);
                // COLLISION AVEC ENNNEMI

                // Active le suivant quand le précédent atteint le milieu
                if (ennemi_courant < 9 && compteur_ennemi_apparition%80==0) {
                    ennemi_courant++;
                    //pour pas que ca arrete d afficher d'autres ennemis
                }

                compteur_ennemi_apparition++;
                //niveau2
            }else if(scroll_x>fin_nv1 && scroll_x<=fin_nv2) {
                //reinit de ennemi_niveau 1
                for (int i = 0; i < 10; i++) {
                    ennemi_niveau1[i].x = SCREEN_W+10;
                    ennemi_niveau1[i].y = rand() % (408-50 - 115 + 1) + 115;
                }

                //ENNEMIS 2 SPAWN

                afficher_et_deplacer_ennemi_nv2(buffer,ennemi_niveau2,temps_max);
                if(ennemi_niveau2[0].ennemi_actif) {
                    tir_ennemi_niveau2(tirs_ennemi1,&ennemi_niveau2[0],&vaisseau,buffer);
                }
                if(ennemi_niveau2[1].ennemi_actif) {
                    tir_ennemi_niveau2(tirs_ennemi2,&ennemi_niveau2[1],&vaisseau,buffer);
                }
                collision_tir_ennemi(tirs,ennemi_niveau2,2,&vaisseau);

                //TIR VAISSEAU SUR ENNEMI

                // COLLISION AVEC TIR ENNEMI ET VAISSEAU
                printf("%d\n",vaisseau.point);
                // Active le suivant quand le précédent atteint le milieu



                //niveau3
            }else if(scroll_x>fin_nv2 && scroll_x<=fin_nv3) {

                for(int i=0;i<= ennemi_courant2;i++) {
                    if(ennemi_niveau1[i].ennemi_actif) {
                        afficher_et_deplacer_ennemi_nv1(buffer,&ennemi_niveau1[i],temps_max);
                    }

                }
                //TIR VAISSEAU SUR ENNEMI
                collision_tir_ennemi(tirs,ennemi_niveau1,10,&vaisseau);


                // Active le suivant quand le précédent atteint le milieu
                if (ennemi_courant2 < 9 && compteur_ennemi_apparition2%80==0) {
                    ennemi_courant2++;
                    //pour pas que ca arrete d afficher d'autres ennemis
                }

                compteur_ennemi_apparition2++;

                // Active le suivant quand le précédent atteint le milieu
            }else if(scroll_x>fin_nv3) {
                active_scroll=0;
                if(boss.ennemi_actif) {
                    afficher_ennemi_nv3(buffer,&boss,temps_max);
                    tir_ennemi_boss(tirs_ennemi3,&boss,&vaisseau,buffer);
                    collision_tir_ennemi(tirs,&boss,nb_ennemi_3,&vaisseau);

                }
                if(!boss.ennemi_actif) {
                    active_scroll=1;
                    scroll_x=0;
                    //INITIALISTION
                    //ENNEMIS 1
                    for (int i = 0; i < 10; i++) {
                        init_ennemi_nv1(&ennemi_niveau1[i]);
                    }
                     ennemi_courant = 0;
                    compteur_ennemi_apparition = 0;
                    ennemi_courant2 = 0;
                     compteur_ennemi_apparition2 = 0;
                    //BOSS
                    init_ennemi_nv3(&boss);
                    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
                        init_tir(&tirs_ennemi3[i],boss,image_tir_ennemi);
                    }
                    //ENNEMIS 2
                    init_ennemi_nv2(ennemi_niveau2);
                    for (int i = 0; i < NB_TIR_ENNEMI; i++) {
                        init_tir(&tirs_ennemi1[i],ennemi_niveau2[0],image_tir_ennemi);
                        init_tir(&tirs_ennemi2[i],ennemi_niveau2[1],image_tir_ennemi);
                    }
                }


            }

            stretch_sprite(buffer,vaisseau.vaisseau_bmp[img_courante],vaisseau.x,vaisseau.y,vaisseau.tx,vaisseau.ty);
            deplacement_vaisseau(&vaisseau,&cptimg,&img_courante,tmpimg);
            gestion_score_point_vie_vaisseau(&vaisseau,collision_vaisseau_decor(&active_scroll,scroll_x,&vaisseau,fond_collision,&cptimg_ex,tmpimg_ex,&img_courante_ex,explosion_sprites,buffer,&img_courante),collision_vaisseau_ennemis(&vaisseau,ennemi_niveau1,&ennemi_courant),collision_vaisseau_ennemis(&vaisseau,ennemi_niveau2,&nb_ennemi_2));
            //tir
            tir_fonction(&son_active,tirs,tir,vaisseau,buffer,&tir_enclenche);
            textprintf_ex(buffer,font,50,515,makecol(255,255,255),-1,"SCORE: %d",vaisseau.score);
            textprintf_ex(buffer,font, 350,515,makecol(255,255,255),-1,"POINTS_VIE: %d",vaisseau.point);
            textprintf_ex(buffer,font, 650,515,makecol(255,255,255),-1,"VIES: %d",vaisseau.nb_vies);

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            tir_enclenche = key[KEY_SPACE];
            rest(20);
        }
    }
}while (rejouer);

        allegro_message("sortie");
        // Libération de la mémoire
        destroy_sample(tir.son_tir);
        remove_sound();//ferme le syst audio
        destroy_bitmap(fond_menu);
        destroy_bitmap(pause_img);
    destroy_bitmap(gagne_img);
    destroy_bitmap(perdu_img);
        destroy_bitmap(fond_jeu);
        destroy_bitmap(fond_collision);
        destroy_bitmap(buffer); // Libère la mémoire du buffer
        destroy_bitmap(buffer_menu);
        destroy_bitmap(buffer_P);
        for (int i = 0; i < 10; i++) {
            destroy_bitmap(ennemi_niveau1[i].image_ennemi);
        }
    for(int i=0;i<2;i++) {
        destroy_bitmap(ennemi_niveau2[i].image_ennemi);
    }
    destroy_bitmap(boss.image_ennemi);
    for(int i=0; i<NB_TIR_ENNEMI; i++) {
        destroy_bitmap(tirs_ennemi1[i].image_tir);
        destroy_bitmap(tirs_ennemi2[i].image_tir);
        destroy_bitmap(tirs_ennemi3[i].image_tir);
    }


        for (int i = 0; i < NB_SPRITES_VAISSEAU; i++) {
            destroy_bitmap(vaisseau.vaisseau_bmp[i]);
        }

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
