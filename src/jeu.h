/*
 * auteur : Julien Miens
 * création : 06/2015
 * revue : 09/2019
 * objectif : fonction gérant les étapes d'un tour de jeu
 * renfort > attaque > déplacement > fin
 */

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "init.h"
#include "pixel.h"
#include <time.h>
#include "menu.h"

void renforts (SDL_Texture *frame, SDL_Texture *fond, region reg[], int joueur,
                SDL_Surface *carte,  SDL_Renderer *renderer, SDL_Texture *Carte,
                int *jouer, int *boucle, SDL_Rect position_echap[], SDL_Texture *menu,
                SDL_Texture *message[], Mix_Chunk *clic, Mix_Chunk *mover,
                int *partie,TTF_Font *petit,SDL_Rect rect_menu_save[],
                SDL_Texture *tex_menu_save, empire emp[]);


void mouvement (SDL_Texture *frame, SDL_Texture *fond, SDL_Rect position_echap[],
                SDL_Texture *menu, Mix_Chunk *clic, Mix_Chunk *mover, region reg[],
                int joueur, SDL_Surface *carte_region, SDL_Texture **Carte,
                int *jouer, int *boucle, SDL_Renderer *renderer, empire emp[],
                SDL_Texture *menu_move, SDL_Rect position_move[], TTF_Font *police,
                SDL_Texture *menu_battle, SDL_Surface **carte_affiche, SDL_Rect rect_menu_save[],
                SDL_Texture *tex_menu_save, SDL_Texture *Fin, Mix_Chunk *combat);


void sous_fonction_mouvement (SDL_Texture *frame, SDL_Texture *fond,
                    SDL_Renderer *renderer, SDL_Texture * texture, SDL_Rect position[],
                     int *mouvement, int x, int y, TTF_Font *police, region reg[],
                     int region, int aller, Mix_Chunk *clic);

void reinit_texture (region reg[], int region, int aller, TTF_Font *police,
                    int envoie, SDL_Renderer *renderer, SDL_Texture *texture);

void sous_fonction_attaque (SDL_Texture *frame, SDL_Texture *fond,
                SDL_Renderer *renderer, SDL_Texture * texture, SDL_Rect endroits[],
                int *mouvement, int x, int y, TTF_Font *police, region reg[],
                int region, int aller, int joueur, int *victoire, Mix_Chunk *clic,
                Mix_Chunk *combat);

void sous_sous_fonction_attaque (int x, int y, int envoie, region reg[], int aller,
            SDL_Renderer *renderer, TTF_Font *police, int joueur, int origine,
            int *victoire, Mix_Chunk *combat);

void definirScore (int nbre, int points[]);

#endif // JEU_H_INCLUDED
