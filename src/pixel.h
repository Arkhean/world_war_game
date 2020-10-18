/*
 * auteur : Julien Miens
 * création : 06/2015
 * revue : 09/2019
 * objectif : dessiner la carte
 */

#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "init.h"


Uint32 obtenirPixel (SDL_Surface * surface, int x, int y);
void definirPixel (SDL_Surface * surface, int x, int y, Uint32 pixel);

void colorier_map(SDL_Surface *carte_region, SDL_Surface **carte_affiche,
        SDL_Texture **texture, int joueur, region reg[], empire emp[],
        SDL_Renderer *renderer);

void encadrer (region reg[], int selection, SDL_Renderer *renderer,
                        SDL_Texture *frame);
void recolorier_region (empire emp[], region reg[], SDL_Renderer *renderer,
    SDL_Surface *carte_region, SDL_Surface **carte_affiche, SDL_Texture **texture,
    int region);

#endif // PIXEL_H_INCLUDED
