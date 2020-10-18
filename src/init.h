/*
 * auteur : Julien Miens
 * création : 06/2015
 * revue : 09/2019
 * objectif : initialiser les textures qui seront utilisés plus tard durant le
 * jeu
 */

#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>

#define NB_REG 42
#define NB_EMP 6

typedef struct region region;
struct region{
    char nom[15];
    int appartenance;
    int rouge;
    int vert;
    int bleu;
    Uint32 couleur;
    int acces[NB_REG];
    int milita;
    char pocesseur;
    int nbreacces;
    int x;
    int y;
    SDL_Texture *troupes;
    SDL_Rect rect;
    int pts_move;
};
typedef struct empire empire;
struct empire{
    int live;
    int ordi;
    char nom[15];
    int rouge;
    int vert;
    int bleu;
};

void initRect (SDL_Rect *rectangle,int x,int y,int w,int h);
void initempire(empire emp[]);
void initregion(region reg[]);

void milita_sur_carte (SDL_Renderer *renderer, region reg[], TTF_Font *police);

void initmenubase(SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[],
                                                            SDL_Texture *menu);
void initmenunew (SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[],
                                                            SDL_Texture *menu);
void init_menu_echap(SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[],
                                                        SDL_Texture *menu);
void init_menu_save (SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[],
                                                            SDL_Texture *menu);
void init_menu_charger (SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[],
                                                            SDL_Texture *menu);
void charger_partie (region reg[], int partie, empire emp[], int *joueur);


void init_texture_renforts(SDL_Texture *texture[], TTF_Font *police,
                                                    SDL_Renderer *renderer);
void init_texture_fin (SDL_Texture **texture, TTF_Font *police,
                                                SDL_Renderer *renderer);
void init_texture_ordi(SDL_Texture **Ai, SDL_Texture **Humain, TTF_Font *police,
                                                SDL_Renderer *renderer);
void init_menu_mouvement(SDL_Texture *menu, TTF_Font *police,
                        SDL_Renderer *renderer, SDL_Rect position[]);
void init_menu_attaque(SDL_Texture *menu, TTF_Font *police, SDL_Renderer *renderer,
                                                        SDL_Rect position[]);




#endif // INIT_H_INCLUDED
