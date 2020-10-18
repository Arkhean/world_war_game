/*
 * auteur : Julien Miens
 * création : 06/2015
 * revue : 09/2019
 * objectif : fournir les menu du jeu
 * menu principal / menu pause
 * les sous-menus et les fonctions de gestion des boutons
 */


#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "init.h"
#include "pixel.h"



int menu (SDL_Renderer * renderer, SDL_Texture *frame, SDL_Texture *fond,
    int *joueur, int *jouer, SDL_Rect position[5], SDL_Texture *menu,
    SDL_Rect rectnew[], SDL_Texture *menunew, int *jeu, Mix_Chunk *clic,
    SDL_Rect rect_menu_charger[], SDL_Texture *tex_menu_charger, SDL_Texture *ai,
    SDL_Texture *humain, empire emp[]);

int menu_new(SDL_Renderer * renderer, SDL_Texture *frame, SDL_Texture *fond,
    int *joueur, SDL_Rect position[8], SDL_Texture *menu, Mix_Chunk *clic,
    SDL_Texture *ai, SDL_Texture *humain, empire emp[]);

void menu_echap (SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
    int *jouer, SDL_Rect position[6], SDL_Texture *menu, int *boucle, int *suivre,
    Mix_Chunk *clic, region reg[], TTF_Font *police, SDL_Rect rect_menu_save[],
    SDL_Texture *tex_menu_save, empire emp[5], int joueur);

void menu_save(SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
    region reg[], TTF_Font *police, SDL_Rect position[7], SDL_Texture *menu,
    Mix_Chunk *clic,empire emp[], int joueur);

int zone (SDL_Rect position, int x, int y);
void survoler (SDL_Renderer *renderer, SDL_Rect *position, SDL_Event event, int nbre);
void survoler_2 (SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
    SDL_Rect *position, SDL_Event event, int nbre);
int click (SDL_Renderer *renderer, SDL_Rect *position, SDL_Event event, int nbre,
    Mix_Chunk *clic);

void save (region reg[], SDL_Renderer *renderer, TTF_Font *police,int nbre,
                                    empire emp[], int joueur);
int menu_charger(SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
                SDL_Rect position[], SDL_Texture *menu, Mix_Chunk *clic);


#endif // MENU_H_INCLUDED
