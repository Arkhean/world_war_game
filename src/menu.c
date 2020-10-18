#include "menu.h"

int menu (SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
    int *joueur, int *jouer, SDL_Rect position[], SDL_Texture *menu,
    SDL_Rect rectnew[], SDL_Texture *menunew, int *jeu, Mix_Chunk *clic,
    SDL_Rect rect_menu_charger[7], SDL_Texture *tex_menu_charger, SDL_Texture *ai,
     SDL_Texture *humain, empire emp[5])
{
    int boucle = 1;
    SDL_Rect rect = {550, 100, 500, 700};
    int partie = 0;

    SDL_Surface *carte_region = IMG_Load("doc/map.tga");
    SDL_Texture *Background = SDL_CreateTextureFromSurface(renderer, carte_region);

    while (boucle){
        printf("tour\n");
        SDL_Rect rect_tout = {0, 0, 1600, 900};

        SDL_SetRenderTarget(renderer, fond);
        SDL_RenderCopy(renderer, Background, NULL, &rect_tout);
        SDL_RenderCopy(renderer, menu, NULL, &rect);
        SDL_SetRenderTarget(renderer, NULL);

        SDL_RenderCopy(renderer, fond, NULL, &rect_tout);
        SDL_RenderPresent(renderer);
        SDL_Event event;
        int continuer = 1;

        while(continuer){
            while(SDL_PollEvent(&event)){

                switch (event.type)
                {
                case SDL_QUIT :
                    continuer = 0;
                    boucle = 0;
                    break;
                case SDL_MOUSEMOTION :
                    survoler_2(renderer, frame, fond, position, event, 5);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    switch(click(renderer,position,event,5,clic))
                    {
                    case 1 :
                        ///fonction nouvelle partie
                        boucle = menu_new(renderer, frame, fond, joueur, rectnew,
                             menunew, clic, ai, humain, emp);
                        continuer = 0;
                        break;
                    case 2 :
                        ///fonction charger partie
                        //SDL_Delay(100);
                        partie = menu_charger(renderer, frame, fond,
                            rect_menu_charger, tex_menu_charger, clic);
                        if (partie != 6){
                            continuer = 0;
                            boucle = 0;
                        }
                        else{
                            continuer = 0;
                        }
                        break;
                    case 3 :
                        ///fonction options
                        printf ("je vais le faire apres!\n");
                        break;
                    case 4 :
                        ///fonction quitter
                        continuer = 0;
                        boucle = 0;
                        *jouer = 0;
                        *jeu = 0;
                        break;
                    }
                break;
                }

            }
            SDL_Delay(50);
        }
    }
    SDL_FreeSurface(carte_region);
    SDL_DestroyTexture(Background);
    return partie;
}

int menu_new(SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
    int *joueur, SDL_Rect position[], SDL_Texture *menu, Mix_Chunk *clic,
    SDL_Texture *ai, SDL_Texture *humain, empire emp[])
{
    SDL_Rect rect_tout = {0, 0, 1600, 900};
    SDL_Rect rect = {550,100,500,700};
    int w,h;
    SDL_Rect rect_ai[NB_EMP];
    SDL_Rect rect_hu[NB_EMP];

    SDL_QueryTexture(ai,NULL,NULL,&w,&h);
        initRect(&rect_ai[0],950-w/2,250,w,h);
        initRect(&rect_ai[1],950-w/2,330,w,h);
        initRect(&rect_ai[2],950-w/2,410,w,h);
        initRect(&rect_ai[3],950-w/2,490,w,h);
        initRect(&rect_ai[4],950-w/2,570,w,h);
        initRect(&rect_ai[5],950-w/2,650,w,h);

    SDL_QueryTexture(humain,NULL,NULL,&w,&h);
        initRect(&rect_hu[0],950-w/2,250,w,h);
        initRect(&rect_hu[1],950-w/2,330,w,h);
        initRect(&rect_hu[2],950-w/2,410,w,h);
        initRect(&rect_hu[3],950-w/2,490,w,h);
        initRect(&rect_hu[4],950-w/2,570,w,h);
        initRect(&rect_hu[5],950-w/2,650,w,h);


    SDL_SetRenderTarget(renderer,fond);
    SDL_RenderCopy(renderer,menu,NULL,&rect);
    for (int i = 0; i < NB_EMP; i++){
        SDL_RenderCopy(renderer,ai,NULL,&rect_ai[i]);
        position[i+1] = rect_hu[i];
    }
    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer,fond,NULL,&rect_tout);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int continuer = 1;
    int nbre;

    while(continuer){
        while(SDL_PollEvent(&event)){

            switch (event.type)
            {
            case SDL_QUIT :
                continuer = 0;
                break;
            case SDL_MOUSEMOTION :
                survoler_2(renderer, frame, fond, position, event, 9);
                break;
            case SDL_MOUSEBUTTONUP :
                SDL_SetRenderTarget(renderer,fond);
                    switch(click(renderer, position, event, 9, clic))
                    {
                        case 1 :
                            emp[0].ordi = (emp[0].ordi + 1) % 2;
                            SDL_RenderCopy(renderer,menu,NULL,&rect);
                            for (int i = 0; i < NB_EMP; i++){
                                if (emp[i].ordi == 0){
                                    SDL_RenderCopy(renderer,ai,NULL,&rect_ai[i]);
                                }
                                else{
                                    SDL_RenderCopy(renderer,humain,NULL,&rect_hu[i]);
                                }
                            }
                            break;
                        case 2 :
                            emp[1].ordi = (emp[1].ordi + 1) % 2;
                            SDL_RenderCopy(renderer,menu,NULL,&rect);
                            for (int i = 0; i < NB_EMP; i++){
                                if (emp[i].ordi == 0){
                                    SDL_RenderCopy(renderer,ai,NULL,&rect_ai[i]);
                                }
                                else{
                                    SDL_RenderCopy(renderer,humain,NULL,&rect_hu[i]);
                                }
                            }
                            break;
                        case 3 :
                            emp[2].ordi = (emp[2].ordi + 1) % 2;
                            SDL_RenderCopy(renderer,menu,NULL,&rect);
                            for (int i = 0; i < NB_EMP; i++){
                                if (emp[i].ordi == 0){
                                    SDL_RenderCopy(renderer,ai,NULL,&rect_ai[i]);
                                }
                                else{
                                    SDL_RenderCopy(renderer,humain,NULL,&rect_hu[i]);
                                }
                            }
                            break;
                        case 4 :
                            emp[3].ordi = (emp[3].ordi + 1) % 2;
                            SDL_RenderCopy(renderer,menu,NULL,&rect);
                            for (int i = 0; i < NB_EMP; i++){
                                if (emp[i].ordi == 0){
                                    SDL_RenderCopy(renderer,ai,NULL,&rect_ai[i]);
                                }
                                else{
                                    SDL_RenderCopy(renderer,humain,NULL,&rect_hu[i]);
                                }
                            }
                            break;
                        case 5 :
                            emp[4].ordi = (emp[4].ordi + 1) % 2;
                            SDL_RenderCopy(renderer,menu,NULL,&rect);
                            for (int i = 0; i < NB_EMP; i++){
                                if (emp[i].ordi == 0){
                                    SDL_RenderCopy(renderer,ai,NULL,&rect_ai[i]);
                                }
                                else{
                                    SDL_RenderCopy(renderer,humain,NULL,&rect_hu[i]);
                                }
                            }
                            break;
                        case 6 :
                            emp[5].ordi = (emp[5].ordi + 1) % 2;
                            SDL_RenderCopy(renderer,menu,NULL,&rect);
                            for (int i = 0; i < NB_EMP; i++){
                                if (emp[i].ordi == 0){
                                    SDL_RenderCopy(renderer,ai,NULL,&rect_ai[i]);
                                }
                                else{
                                    SDL_RenderCopy(renderer,humain,NULL,&rect_hu[i]);
                                }
                            }
                            break;
                        case 7 :
                            continuer = 0;
                            nbre = 1;
                            break;
                        case 8 :
                            continuer = 0;
                            nbre = 0;
                            break;
                    }
            SDL_SetRenderTarget(renderer,NULL);
            SDL_RenderPresent(renderer);
            break;
            }
        }
        SDL_Delay(50);
    }
    return nbre;
}

void menu_echap (SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
    int *jouer, SDL_Rect position[6], SDL_Texture *menu, int *boucle, int *suivre,
     Mix_Chunk *clic, region reg[69],TTF_Font *police,SDL_Rect rect_menu_save[7],
      SDL_Texture *tex_menu_save,empire emp[5],int joueur)
{
    SDL_Rect rect = {550, 100, 500, 700};
    SDL_Rect rect_tout = {0, 0, 1600, 900};

    SDL_SetRenderTarget(renderer, fond);
    SDL_RenderCopy(renderer, menu, NULL, &rect);
    SDL_SetRenderTarget(renderer, frame);
    SDL_RenderCopy(renderer, fond, NULL, &rect_tout);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
    SDL_RenderPresent(renderer);

    const Uint8 *state;
    SDL_Event event;
    int continuer = 1;

    while(continuer)
    {
        while(SDL_PollEvent(&event)){

        switch (event.type)
        {
            case SDL_QUIT :
                continuer = 0;
                break;

            case SDL_MOUSEMOTION :
                survoler_2(renderer, frame, fond, position, event, 6);
                break;

            case SDL_MOUSEBUTTONDOWN :
                    switch (click(renderer, position, event, 6, clic))
                    {
                    case 1 :
                        ///fonction retour menu
                        continuer = 0;
                        *jouer = 0;
                        *boucle = 1;
                        *suivre = 0;
                        break;
                    case 2 :
                        ///fonction save
                        menu_save(renderer, frame, fond, reg, police,
                            rect_menu_save, tex_menu_save, clic, emp, joueur);
                        SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
                        SDL_RenderPresent(renderer);
                        break;
                    case 3 :
                        ///fonction options
                        printf ("je vais le faire apres!\n");
                        break;
                    case 4 :
                        ///fonction reprendre la partie
                        continuer = 0;
                        *jouer = 1;
                        *suivre = 1;
                        break;
                    case 5 :
                        ///fonction quitter
                        continuer = 0;
                        *jouer = 0;
                        *boucle = 0;
                        *suivre = 0;
                        break;
                    }
            break;
        case SDL_KEYDOWN :
            state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_ESCAPE]){
                continuer = 0;
            }
        }
        }
        SDL_Delay(50);

    }
}

void menu_save(SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
    region reg[69], TTF_Font *police, SDL_Rect position[7], SDL_Texture *menu,
    Mix_Chunk *clic, empire emp[5], int joueur)
{
    SDL_Rect rect = {550,100,500,700};
    SDL_Rect rect_tout = {0, 0, 1600, 900};
    SDL_SetRenderTarget(renderer, fond);
    SDL_RenderCopy(renderer, menu, NULL, &rect);
    SDL_SetRenderTarget(renderer, frame);
    SDL_RenderCopy(renderer, fond, NULL, &rect_tout);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
    SDL_RenderPresent(renderer);

    const Uint8 *state;
    SDL_Event event;
    int continuer = 1;
    while(continuer)
    {
        while(SDL_PollEvent(&event)){
        switch (event.type)
        {

        case SDL_QUIT :
            continuer = 0;
            break;

        case SDL_MOUSEMOTION :
            survoler_2(renderer, frame, fond, position, event, 7);
            break;

        case SDL_MOUSEBUTTONDOWN :
                    switch (click(renderer, position, event, 7, clic))
                    {
                    case 1 :
                        ///sauvegarder dans partie 1
                        save (reg,renderer,police,1,emp,joueur);
                        break;
                    case 2 :
                        ///sauvegarder dans partie 2
                        save (reg,renderer,police,2,emp,joueur);
                        break;
                    case 3 :
                        ///sauvegarder dans partie 3
                        save (reg,renderer,police,3,emp,joueur);
                        break;
                    case 4 :
                        ///sauvegarder dans partie 4
                        save (reg,renderer,police,4,emp,joueur);
                        break;
                    case 5 :
                        ///sauvegarder dans partie 5
                        save (reg,renderer,police,5,emp,joueur);
                        break;
                    case 6 :
                        ///retour !
                        continuer = 0;
                        break;
                    }
        case SDL_KEYDOWN :
            state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_ESCAPE]){
                continuer = 0;
            }
        }
        }
        SDL_Delay(50);
    }
}
int menu_charger(SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
    SDL_Rect position[7], SDL_Texture *menu, Mix_Chunk *clic)
{
    SDL_Rect rect = {550,100,500,700};
    SDL_Rect rect_tout = {0, 0, 1600, 900};
    SDL_SetRenderTarget(renderer, fond);
    SDL_RenderCopy(renderer, menu, NULL, &rect);
    SDL_SetRenderTarget(renderer, frame);
    SDL_RenderCopy(renderer, fond, NULL, &rect_tout);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
    SDL_RenderPresent(renderer);

    const Uint8 *state;
    SDL_Event event;
    int continuer = 1;
    while(continuer)
    {
        while(SDL_PollEvent(&event)){

        switch (event.type)
        {

        case SDL_QUIT :
            continuer = 0;
            break;

        case SDL_MOUSEMOTION :
            survoler_2(renderer, frame, fond, position, event, 7);
            break;

        case SDL_MOUSEBUTTONDOWN :
            return click(renderer,position,event,7,clic);
        case SDL_KEYDOWN :
            state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_ESCAPE])
            {
                continuer = 0;
            }
            break;
        }
        }
        SDL_Delay(50);
    }
    return 0;
}

int zone (SDL_Rect position, int x, int y)
{
    return (x > position.x && x < position.x+position.w
        && y > position.y && y < position.y+position.h);
}

void survoler_2 (SDL_Renderer *renderer, SDL_Texture *frame, SDL_Texture *fond,
     SDL_Rect *position, SDL_Event event, int nbre)
{
    SDL_Rect rect_tout = {0, 0, 1600, 900};
    SDL_SetRenderTarget(renderer, frame);
    SDL_RenderCopy(renderer, fond, NULL, &rect_tout);
    if (nbre == 1 && zone(position[0], event.button.x, event.button.y)){
        SDL_SetRenderDrawColor(renderer,255,255,0,255);
        SDL_RenderDrawRect(renderer,&position[0]);
    }
    for (int i=1;i<nbre;i++){//pour ignorer le titre qui n'est pas un bouton
            if (zone(position[i],event.button.x,event.button.y)){
                SDL_SetRenderDrawColor(renderer,255,255,0,255);
                SDL_RenderDrawRect(renderer,&position[i]);
            }
        }
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
    SDL_RenderPresent(renderer);
}

int click (SDL_Renderer *renderer,SDL_Rect *position,SDL_Event event,int nbre,
                                            Mix_Chunk *clic)
{
    for (int i=0;i<nbre;i++)
    {
        if (zone(position[i],event.button.x,event.button.y))
        {
            Mix_PlayChannel(1,clic,0);
            return i;
        }
    }
    return -1;
}
void save (region reg[], SDL_Renderer *renderer, TTF_Font *police,int nbre,
                                    empire emp[], int joueur)
{
        FILE *fichier = NULL;
        char texte[17];
        sprintf(texte,"doc/partie%d.sav",nbre);
        fichier = fopen(texte,"w+");
        for (int i=0;i<NB_REG;i++){
            fprintf(fichier,"nom : %s appartenance : %d milita : %d mouvement : %d\n",
                reg[i].nom, reg[i].appartenance, reg[i].milita, reg[i].pts_move);
        }
        for (int i=0;i<NB_EMP;i++){
            fprintf(fichier, "%s : %d\n",emp[i].nom,emp[i].ordi);
        }
        fprintf(fichier, "joueur actuel : %d\n",joueur);

        fclose(fichier);

        SDL_Color color = {255,255,255,255};
        SDL_Surface *surface = TTF_RenderText_Blended(police," Sauvegarde reussie !",color);
        SDL_Rect position = {(1600-surface->w)/2, 40, surface->w, surface->h};
        SDL_RenderFillRect(renderer,&position);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer,texture,NULL,&position);
        SDL_DestroyTexture(texture);
        SDL_RenderPresent(renderer);
}
