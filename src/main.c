/*
 * auteur : Julien Miens
 * création : 06/2015
 * revue : 09/2019
 * objectif : fichier principal du jeu
 */


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "init.h"
#include "menu.h"
#include "jeu.h"
#include "pixel.h"
#include "AI.h"

#define NB_REG 42
#define NB_EMP 6


int main(int argc, char *argv[]){
    // initialisation SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1){
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    ///window
    SDL_Window *screen = SDL_CreateWindow("Risk", SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
    ///renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1,
                        SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);

    SDL_Rect position = {0, 0, 1600, 900};
    SDL_Surface *loading = IMG_Load("doc/loading.tga");
    SDL_Texture *chargement = SDL_CreateTextureFromSurface(renderer,loading);
    SDL_RenderCopy(renderer,chargement,NULL,&position);
    SDL_RenderPresent(renderer);
    SDL_Rect rect = {406,591,20,56};


    // chargement
    // les polices
    printf("chargement police\n");
    TTF_Font *police = NULL;
    police = TTF_OpenFont("doc/heracles.TTF",50);
    if (police == NULL){
        printf("erreur police");
    }
    TTF_Font *petit = TTF_OpenFont("doc/heracles.TTF",30);

    // textures de fond et de menu
    printf("chargement texture\n");
    SDL_Texture *Carte = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, 1600, 900);
    SDL_Texture *Menu_Principal = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, 500, 700);
    SDL_Texture *Menu_Echap = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, 500, 700);
    SDL_Texture *Menu_Nouveau = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, 500, 700);
    SDL_Texture *Menu_Save = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, 500, 700);
    SDL_Texture *Menu_Charger = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, 500, 700);
    SDL_Texture *Renforts[23];
    SDL_Texture *menu_mouvement = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, 500, 300);
    SDL_Texture *menu_attaque = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, 500, 300);
    SDL_Texture *Background;
    SDL_Texture *Fin = NULL;
    SDL_Texture *ai;
    SDL_Texture *humain;
    SDL_Texture *fond = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, 1600, 900);
    SDL_Texture *frame = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, 1600, 900);

    ///positions
    SDL_Rect rect_Menu_Principal[5];
    SDL_Rect rect_Menu_Echap[6];
    SDL_Rect rect_Menu_Nouveau[9];
    SDL_Rect rect_menu_save[7];
    SDL_Rect rect_menu_charger[7];
    SDL_Rect rect_menu_mouvement[5];

    // initialisation des textures et des positions
    printf("initialisation surface et menu\n");
    SDL_Surface *carte_region = IMG_Load("doc/map.tga");
    SDL_Surface *carte_affiche = IMG_Load("doc/map.tga");
    Background = SDL_CreateTextureFromSurface(renderer,carte_region);

    initmenubase(renderer, police, rect_Menu_Principal, Menu_Principal);
    initmenunew(renderer, police, rect_Menu_Nouveau, Menu_Nouveau);
    init_menu_echap(renderer, police, rect_Menu_Echap, Menu_Echap);
    init_menu_save(renderer, police, rect_menu_save, Menu_Save);
    init_menu_charger(renderer, police, rect_menu_charger, Menu_Charger);
    init_texture_renforts(Renforts, petit, renderer);
    init_menu_mouvement(menu_mouvement, petit, renderer, rect_menu_mouvement);
    init_menu_attaque(menu_attaque, petit, renderer, rect_menu_mouvement);
    init_texture_fin(&Fin, petit, renderer);
    init_texture_ordi(&ai, &humain, police, renderer);

    TTF_CloseFont(police);

    ///initialisation des sons
    printf("initialisation sons\n");
    Mix_AllocateChannels(2);
    Mix_Chunk *clic = Mix_LoadWAV("sono/click.wav");
    Mix_Chunk *move = Mix_LoadWAV("sono/army_move.wav");
    Mix_Chunk *combat = Mix_LoadWAV("sono/combat.wav");

    int boucle = 1;
    int i;
    region reg[NB_REG];
    empire emp[NB_EMP];
    // fin chargement

    printf("boucle\n");
    while (boucle){
        SDL_RenderCopy(renderer, Background, NULL, &position);
        SDL_RenderPresent(renderer);
        int joueur = 0;
        int jouer = 1;
        int partie = 0;
        printf("menu lance\n");
        partie = menu(renderer, frame, fond, &joueur, &jouer,
            rect_Menu_Principal, Menu_Principal, rect_Menu_Nouveau, Menu_Nouveau,
             &boucle, clic, rect_menu_charger, Menu_Charger, ai, humain, emp);

        // lancement de la partie
        if (jouer == 1){
            // initialisation
            SDL_RenderCopy(renderer, chargement, NULL, &position);
            SDL_RenderPresent(renderer);
            initRect(&rect, 406, 591, 197, 56);

            initregion(reg);
            initempire(emp);

            int fait = 0;
            if (partie != 0){
                charger_partie(reg, partie, emp, &i);
                //printf("i = %d",i);
                rect.x = rect.x - 197;
                fait = 1;
            }
            // colorie des surfaces et les blit sur la texture Carte
            colorier_map(carte_region, &carte_affiche, &Carte, joueur, reg, emp, renderer);
            rect.w = rect.w + 197;
            SDL_Delay(500);

            //on écrit sur le fond et pas directement dans le renderer
            SDL_SetRenderTarget(renderer, fond);
            SDL_RenderCopy(renderer, Carte, NULL, &position);
            milita_sur_carte(renderer, reg, petit);
            SDL_SetRenderTarget(renderer, NULL);

            SDL_RenderCopy(renderer, fond, NULL, &position);
            SDL_RenderPresent(renderer);
            int partie = 1;

                while(jouer){
                    printf("\nje boucle !\n");
                    SDL_Delay(10);
                    if (fait == 1){
                        fait = 0;
                    }
                    else{
                        i = 0;
                    }
                    while(i < NB_EMP && jouer == 1){
                        printf ("\nfaction %d \n",i);
                        if (emp[i].live == 1){
                            SDL_Delay(10);
                            if (emp[i].ordi == 1){
                                //printf("c'est un humain\n");
                                renforts(frame,fond, reg, i, carte_region,
                                        renderer, Carte, &jouer, &boucle,
                                        rect_Menu_Echap, Menu_Echap, Renforts,
                                        clic, move, &partie, petit,
                                        rect_menu_save, Menu_Save, emp);
                                //si on n'a pas quitter via le menu echap
                                if (partie == 1){
                                    mouvement(frame, fond, rect_Menu_Echap,
                                        Menu_Echap, clic, move, reg, i,
                                        carte_region, &Carte, &jouer, &boucle,
                                        renderer, emp, menu_mouvement,
                                        rect_menu_mouvement, petit, menu_attaque,
                                        &carte_affiche, rect_menu_save, Menu_Save,
                                        Fin, combat);
                                }
                            }
                            else{
                                printf("c'est un ordi\n");
                                ///fonction AI
                                intelligence_artificielle(frame, fond, i, reg,
                                    emp, renderer, &Carte, carte_region,
                                    &carte_affiche, petit, &jouer, &boucle,
                                    rect_Menu_Echap, Menu_Echap, clic, Menu_Save,
                                    rect_menu_save);
                                printf("ok\n");
                            }
                        }
                        alive(emp, reg);
                        if (somme_faction(emp) == 1){
                            jouer = 0;
                            printf("\n\n%s a gagne !\n",emp[i].nom);
                            SDL_Delay(2000);
                        }
                        i++;
                    }
                }
            }
    }

    ///ménage
    for (i = 0; i < 23; i++){
        SDL_DestroyTexture(Renforts[i]);
    }
    SDL_FreeSurface(carte_region);
    SDL_FreeSurface(carte_affiche);
    SDL_FreeSurface(loading);

    SDL_DestroyTexture(Carte);
    SDL_DestroyTexture(Background);
    SDL_DestroyTexture(Menu_Echap);
    SDL_DestroyTexture(Menu_Principal);
    SDL_DestroyTexture(Menu_Nouveau);
    SDL_DestroyTexture(menu_mouvement);
    SDL_DestroyTexture(menu_attaque);
    SDL_DestroyTexture(Fin);
    SDL_DestroyTexture(chargement);
    SDL_DestroyTexture(ai);
    SDL_DestroyTexture(humain);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(frame);

    Mix_FreeChunk(clic);
    Mix_FreeChunk(combat);
    Mix_FreeChunk(move);

    TTF_CloseFont(petit);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
