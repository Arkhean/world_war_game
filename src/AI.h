/*
 * auteur : Julien Miens
 * création : 06/2015
 * revue : 09/2019
 * objectif : simuler les joueurs ordinateurs
 * stratégie basique : reforcer les points faibles, attaquer les points faibles
 * de l'ennemi, un peu de probabilité pour un peu d'imprévisibilité
 */

#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "init.h"
#include "pixel.h"
#include "time.h"
#include "jeu.h"
#include "menu.h"

void intelligence_artificielle (SDL_Texture *frame, SDL_Texture *fond, int joueur,
     region reg[], empire emp[], SDL_Renderer *renderer, SDL_Texture **Carte,
     SDL_Surface *carte_region, SDL_Surface **carte_affiche, TTF_Font *petit,
     int *jouer, int *boucle, SDL_Rect position_echap[], SDL_Texture *menu,
     Mix_Chunk *clic,SDL_Texture *tex_menu_save, SDL_Rect rect_menu_save[]);

void menace_et_attaque (int menace[], int attaque[], region reg[], int joueur);
void ia_renfort(int menace[], int attaque[], region reg[], int joueur);
int menacee (int menace, int joueur, region pro,region reg[]);
void deplacement (region reg[], int joueur, int menace[]);
void attaquer (int attaque[], int joueur, region reg[]);
int nbre_a_envoyer (region reg[], int origine, int aller, int joueur, int menace[]);

void combat (int envoie, region reg[], int origine, int aller, int joueur,
    SDL_Renderer *renderer, SDL_Surface *carte_region, SDL_Surface **carte_affiche,
             SDL_Texture **Carte, TTF_Font *petit, empire emp[]);

void alive (empire emp[], region reg[]);
int somme_faction (empire emp[]);


#endif // AI_H_INCLUDED
