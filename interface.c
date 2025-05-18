//
// Created by sarra on 4/28/2025.
//

#include "interface.h"
#include <stdio.h>
#include <string.h>
#include "vaisseau.h"
#define MAX_PSEUD0 20
//tout ce qui est menu et fond du jeu

// Fonction pour tester si la souris est sur un bouton
int souris_sur_bouton(Bouton b, int mx, int my) {
    return (mx >= b.x && mx <= b.x + b.w &&
            my >= b.y && my <= b.y + b.h);
}

// Affiche le menu sans texte (image seulement)
void afficher_menu(BITMAP *fond, BITMAP *buffer) {
    blit(fond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

// Fonction pour saisir un pseudo
void saisir_pseudo(char *pseudo, int max, BITMAP* buffer,BITMAP* zone_nom) {
    int len = 0;
    clear_keybuf();

    while (1) {
        clear_bitmap(buffer);
        blit(zone_nom, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        textprintf_ex(buffer, font, 364, 355, makecol(255, 255, 255), -1,
                      "%s", pseudo);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (keypressed()) {
            int keycode = readkey();
            char c = keycode & 0xff;

            if ((keycode >> 8) == KEY_ENTER) {
                pseudo[len] = '\0';
                break;
            }
             if ((keycode >> 8) == KEY_BACKSPACE && len > 0) {
                len--;
                pseudo[len] = '\0';
            }
            else if (c >= 32 && c <= 126 && len < max - 1) {
                pseudo[len++] = c;
                pseudo[len] = '\0';
            }
        }

        rest(10);
    }
}
void pause(BITMAP *pause_img, BITMAP *buffer_P,char* pseudo,int scroll_x,t_vaisseau vaisseau) {
    int pause_active = 1;

    // Attendre le relâchement de la touche P pour éviter double-déclenchement
    while (key[KEY_P]) {
        rest(10);
    }

    while (pause_active) {
        clear_bitmap(buffer_P);
        stretch_blit(pause_img, buffer_P, 0, 0, pause_img->w, pause_img->h, 0, 0, SCREEN_W, SCREEN_H);
        blit(buffer_P, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(10);

        // on retourne au jeu
        if (key[KEY_P]) {
            pause_active = 0;
            while (key[KEY_P]) {
                rest(10);
            }
        }

        // Sortir en appuyant sur ECHAP
        if (key[KEY_ESC]) {
            break;
        }
        if(key[KEY_S]) {
            sauvegarder_partie(pseudo,scroll_x,vaisseau);
        }
    }
}
void sauvegarder_partie(const char *pseudo, int scroll_x, t_vaisseau vaisseau) {
    char nom_fichier[40];
    sprintf(nom_fichier, "saves.txt");

    // Sauvegarde des données de jeu
    FILE *f = fopen(nom_fichier, "w");
    if (!f) {
        allegro_message("Erreur ouverture fichier de sauvegarde");
        return;
    }
    fprintf(f, "PSEUDO:%s\n", pseudo);
    fprintf(f, "SCROLL_X:%d\n", scroll_x);
    fprintf(f, "SCORE:%d\n", vaisseau.score);
    fprintf(f, "NB_VIES:%d\n", vaisseau.nb_vies);
    fprintf(f,"POINTS:%d\n",vaisseau.point);

    fclose(f);
    allegro_message("Partie sauvegardée pour %s", pseudo);
}

int charger_partie( int* scroll_x,t_vaisseau* vaisseau,char pseudo[20]) {
    char nom_fichier[40];
    sprintf(nom_fichier, "saves.txt");
    FILE *f = fopen(nom_fichier, "r");
    if (!f) {
        printf("Erreur d ouverture de saves.txt\n");
        return 0;
    }
    fscanf(f,"PSEUDO: %s\n",pseudo);
    fscanf(f, "SCROLL_X:%d\n", scroll_x);
    fscanf(f, "SCORE:%d\n", &vaisseau->score);
    fscanf(f, "NB_VIES:%d\n", &vaisseau->nb_vies);
    fscanf(f,"POINTS:%d\n",&vaisseau->point);

    fclose(f);
    allegro_message("partie chargee");
    return 1;
}

