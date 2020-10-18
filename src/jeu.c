#include "jeu.h"

void renforts(SDL_Texture *frame,SDL_Texture *fond, region reg[], int joueur,
    SDL_Surface *carte, SDL_Renderer *renderer, SDL_Texture *Carte, int *jouer,
    int *boucle, SDL_Rect position_echap[], SDL_Texture *menu,
    SDL_Texture *message[], Mix_Chunk *clic, Mix_Chunk *mover, int *partie,
    TTF_Font *petit, SDL_Rect rect_menu_save[], SDL_Texture *tex_menu_save,
    empire emp[])
{
    ///initialisation
    int i,renforts,nbre_regions,x,y,w,h;
    nbre_regions = 0;
    SDL_Rect faction = {66,696,207,111};
    for (i=0;i<NB_REG;i++){
        if (reg[i].appartenance == joueur){
            nbre_regions++;
        }
    }
    renforts = nbre_regions / 3;
    SDL_Event event;
    Uint32 pixel;
    SDL_Rect position = {0,0,1600,900};

    SDL_QueryTexture(message[renforts-1], NULL, NULL, &w, &h);
    SDL_Rect local = {60,820,w,h};

    SDL_SetRenderTarget(renderer,fond);
    SDL_RenderCopy(renderer, Carte, NULL, &position);
    SDL_SetRenderDrawColor(renderer, emp[joueur].rouge, emp[joueur].vert, emp[joueur].bleu, 255);
    SDL_RenderFillRect(renderer, &faction);
    milita_sur_carte(renderer, reg, petit);
    SDL_RenderCopy(renderer, message[renforts], NULL, &local);


    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, fond, NULL, &position);
    SDL_RenderPresent(renderer);

    const Uint8 *state;

    ///lancement fonction
    while(renforts != 0){
        SDL_Delay(10);
        SDL_PollEvent(&event);
        switch (event.type)
        {
                case SDL_MOUSEBUTTONDOWN :
                    x = event.button.x;
                    y = event.button.y;
                    pixel = obtenirPixel(carte,x,y);
                    for (i=0;i<NB_REG;i++){
                        if (pixel == reg[i].couleur && reg[i].appartenance == joueur && reg[i].milita < 15){
                            renforts--;
                            reg[i].milita++;
                            Mix_PlayChannel(1,mover,0);
                            SDL_Delay(250);
                        }
                    }
                        break;
                    case SDL_QUIT :
                        renforts = 0;
                        *boucle = 0;
                        *jouer = 0;
                        break;
                    case SDL_KEYDOWN :
                        state = SDL_GetKeyboardState(NULL);
                        if (state[SDL_SCANCODE_ESCAPE]){
                            menu_echap(renderer,frame,fond, jouer, position_echap, menu,boucle, &renforts, clic, reg, petit, rect_menu_save, tex_menu_save, emp,joueur);
                            if (*jouer == 0){
                                *partie = 0;
                            }
                        }
                        break;
        }
        SDL_SetRenderTarget(renderer, fond);
        SDL_RenderCopy(renderer,Carte,NULL,&position);
        SDL_SetRenderDrawColor(renderer,emp[joueur].rouge,emp[joueur].vert,emp[joueur].bleu,255);
        SDL_RenderFillRect(renderer,&faction);
        milita_sur_carte(renderer,reg,petit);
        SDL_RenderCopy(renderer, message[renforts], NULL, &local);
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, fond, NULL, &position);
        SDL_RenderPresent(renderer);
    }

}

void mouvement (SDL_Texture *frame, SDL_Texture *fond, SDL_Rect position_echap[], SDL_Texture *menu, Mix_Chunk *clic, Mix_Chunk *mover, region reg[], int joueur, SDL_Surface *carte_region,
                SDL_Texture **Carte, int *jouer, int *boucle, SDL_Renderer *renderer, empire emp[], SDL_Texture *menu_move, SDL_Rect position_move[],
                TTF_Font *police, SDL_Texture *menu_battle, SDL_Surface **carte_affiche,SDL_Rect rect_menu_save[], SDL_Texture *tex_menu_save, SDL_Texture *Fin,
                Mix_Chunk *combat)
{
    ///initialisation
    int continuer = 1;
    int mouvement = 1;
    SDL_Event event;
    Uint32 pixel;
    int i,x,y,e,c,w,h;
    SDL_Rect position = {0,  0, 1600, 900};
    SDL_QueryTexture(Fin, NULL, NULL, &w, &h);
    SDL_Rect rect_fin = {60, 820, w, h};
    SDL_Rect tab_rect_fin[1];
    tab_rect_fin[0] = rect_fin;
    SDL_Rect faction = {66, 696, 207, 111};

    const Uint8 *state;
    int victoire = 0;
    ///fabrication du fond
    SDL_SetRenderTarget(renderer, fond);
    SDL_RenderCopy(renderer, *Carte, NULL, &position);
    SDL_SetRenderDrawColor(renderer, emp[joueur].rouge, emp[joueur].vert, emp[joueur].bleu, 255);
    SDL_RenderFillRect(renderer, &faction);
    milita_sur_carte(renderer, reg, police);
    SDL_RenderCopy(renderer, Fin, NULL, &rect_fin);
    SDL_SetRenderTarget(renderer, frame);
    SDL_RenderCopy(renderer, fond, NULL, &position);
    SDL_SetRenderTarget(renderer, NULL);

    ///lancement fonction
    while (continuer){
        SDL_RenderCopy(renderer, frame, NULL, &position);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        while(SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_KEYDOWN :
                    state = SDL_GetKeyboardState(NULL);
                    if (state[SDL_SCANCODE_ESCAPE]){
                        menu_echap(renderer,frame,fond,jouer,position_echap,menu,boucle,&continuer,clic,reg,police,rect_menu_save,tex_menu_save,emp,joueur);
                    }
                    break;
                case SDL_QUIT :
                    continuer = 0;
                    *boucle = 0;
                    *jouer = 0;
                    break;
                case SDL_MOUSEMOTION :
                    survoler_2(renderer, frame, fond, tab_rect_fin, event, 1);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    x = event.button.x;
                    y = event.button.y;
                    pixel = obtenirPixel(carte_region,x,y);
                    mouvement = 1;
                    c = 0;
                    ///si clic sur fin de tour, quitter la boucle
                    if (zone(rect_fin, event.button.x, event.button.y)){
                        mouvement = 0;
                        continuer = 0;
                    }
                    else{
                    for (i=0;i<NB_REG;i++){
                        if (pixel == reg[i].couleur && reg[i].appartenance == joueur && c == 0){
                            ///encadrer
                            encadrer(reg, i, renderer, frame);
                            SDL_RenderCopy(renderer, frame, NULL, &position);
                            SDL_RenderPresent(renderer);

                            ///attendre un autre clic
                            while (mouvement){

                                SDL_Delay(10);
                                while(SDL_PollEvent(&event)){
                                    if (event.type == SDL_MOUSEBUTTONUP){
                                        printf("clic\n");
                                        x = event.button.x;
                                        y = event.button.y;
                                        pixel = obtenirPixel(carte_region,x,y);
                                        for (e=0;e<NB_REG;e++){
                                            ///si clic sur un ami ==> fenetre deplacement
                                            if (pixel == reg[e].couleur && reg[e].appartenance == joueur && e != i && reg[i].acces[e] == 1){
                                                ///fonction mouvement
                                                sous_fonction_mouvement(frame, fond, renderer, menu_move, position_move, &mouvement, x, y, police, reg, i, e, clic);
                                                mouvement = 0;
                                                SDL_SetRenderTarget(renderer, fond);
                                                SDL_RenderCopy(renderer, *Carte, NULL, &position);
                                                SDL_SetRenderDrawColor(renderer, emp[joueur].rouge, emp[joueur].vert, emp[joueur].bleu, 255);
                                                SDL_RenderFillRect(renderer, &faction);
                                                milita_sur_carte(renderer, reg, police);
                                                SDL_RenderCopy(renderer, Fin, NULL, &rect_fin);
                                                SDL_SetRenderTarget(renderer, frame);
                                                SDL_RenderCopy(renderer, fond, NULL, &position);
                                                SDL_SetRenderTarget(renderer, NULL);
                                                SDL_RenderCopy(renderer, frame, NULL, &position);
                                                SDL_RenderPresent(renderer);
                                            }
                                            ///si clic sur un ennemi ==> fenetre attaque
                                            else if (pixel == reg[e].couleur && reg[i].acces[e] == 1 && reg[e].appartenance != joueur){
                                                ///fonction attaque
                                                sous_fonction_attaque(frame, fond, renderer,menu_battle,position_move,&mouvement,x,y,police,reg,i,e,joueur,&victoire,clic, combat);
                                                if (victoire == 1){
                                                    recolorier_region(emp, reg, renderer, carte_region, carte_affiche, Carte, e);
                                                    victoire = 0;
                                                    c = 0;
                                                }
                                                mouvement = 0;
                                                SDL_SetRenderTarget(renderer, fond);
                                                SDL_RenderCopy(renderer, *Carte, NULL, &position);
                                                SDL_SetRenderDrawColor(renderer, emp[joueur].rouge, emp[joueur].vert, emp[joueur].bleu, 255);
                                                SDL_RenderFillRect(renderer, &faction);
                                                milita_sur_carte(renderer, reg, police);
                                                SDL_RenderCopy(renderer, Fin, NULL, &rect_fin);
                                                SDL_SetRenderTarget(renderer, frame);
                                                SDL_RenderCopy(renderer, fond, NULL, &position);
                                                SDL_SetRenderTarget(renderer, NULL);
                                                SDL_RenderCopy(renderer, frame, NULL, &position);
                                                SDL_RenderPresent(renderer);
                                            }
                                            ///sinon enlever coloriage, retour à la boucle principale
                                            else if (pixel == reg[e].couleur && reg[e].appartenance != joueur){
                                                mouvement = 0;
                                                c = 0;
                                            }
                                            else if (pixel != reg[e].couleur && c == 1){
                                                mouvement = 0;
                                                c = 0;
                                            }
                                        }
                                        c = 1;
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    for (i=0;i<NB_REG;i++){
        reg[i].pts_move = reg[i].milita;
    }
}

void sous_fonction_mouvement(SDL_Texture *frame, SDL_Texture *fond, SDL_Renderer *renderer, SDL_Texture * texture, SDL_Rect endroits[], int *mouvement, int x, int y, TTF_Font *police,
                             region reg[], int region, int aller, Mix_Chunk *clic)
{
    SDL_Rect affichage;
    int continuer = 1;
    SDL_Event event;
    int h,w,i;
    int envoie = 0;
    SDL_Rect rect_tout = {0, 0, 1600, 900};

    affichage.x = x;
    affichage.y = y;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
    affichage.w = w;
    affichage.h = h;
    if (x+w > 1600){
        affichage.x = affichage.x - w;
    }
    if (y+h > 900){
        affichage.y = affichage.y - h;
    }

    ///fonction info
    reinit_texture(reg, region, aller, police, envoie, renderer, texture); //texture est l'affichage de notre petit menu
    SDL_Texture *fond_tmp = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1600,900);
    SDL_SetRenderTarget(renderer, fond_tmp);
    SDL_RenderCopy(renderer, fond, NULL, &rect_tout);
    SDL_RenderCopy(renderer, texture, NULL, &affichage);
    SDL_SetRenderTarget(renderer, frame);
    SDL_RenderCopy(renderer, fond_tmp, NULL, &rect_tout);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
    SDL_RenderPresent(renderer);

    SDL_Rect position[5];
    for (i=0;i<5;i++){
        position[i].x = endroits[i].x + x;
        position[i].y = endroits[i].y + y;
        position[i].w = endroits[i].w;
        position[i].h = endroits[i].h;
        if (x+w > 1600){
            position[i].x = position[i].x - w;
        }
        if (y+h > 900){
            position[i].y = position[i].y - h;
        }
    }

    int max = 15 - reg[aller].milita;

    while(continuer){
        SDL_Delay(50);
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
                case SDL_QUIT :
                    continuer = 0;
                    *mouvement = 0;
                    break;
                case SDL_MOUSEMOTION :
                    survoler_2(renderer, frame, fond_tmp, position, event, 5);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    switch(click(renderer, position, event, 5, clic))
                    {
                    case 1 :
                        if (envoie++ > max-1){
                            envoie--;
                        }
                        if (envoie > reg[region].milita-1){
                            envoie--;
                        }
                        if (envoie > reg[region].pts_move-1){
                            envoie--;
                        }
                        break;
                    case 2 :
                        if (envoie-- < 1){
                            envoie++;
                        }

                        break;
                    case 3 :
                        ///deplacement des troupes
                        reg[region].milita = reg[region].milita - envoie;
                        reg[aller].milita = reg[aller].milita + envoie;
                        reg[region].pts_move = reg[region].pts_move - envoie;
                        continuer = 0;
                        *mouvement = 0;
                        break;
                    case 4 :
                        continuer = 0;
                        *mouvement = 0;
                        break;
                    }
                    printf("loop\n");
                    reinit_texture(reg, region, aller, police, envoie, renderer, texture); //texture est l'affichage de notre petit menu
                    SDL_SetRenderTarget(renderer, fond_tmp);
                    SDL_RenderCopy(renderer, texture, NULL, &affichage);
                    SDL_SetRenderTarget(renderer, frame);
                    SDL_RenderCopy(renderer, fond_tmp, NULL, &rect_tout);
                    SDL_SetRenderTarget(renderer, NULL);
                    SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
                    SDL_RenderPresent(renderer);
                break;
            }
        }
    }
    SDL_DestroyTexture(fond_tmp);
}

void reinit_texture(region reg[], int region, int aller, TTF_Font *police, int envoie, SDL_Renderer *renderer, SDL_Texture *texture)
{
    int i;
    SDL_Surface *surface[3];
    char textea[30];
    char texteb[30];
    char textec[3];
    sprintf(textea,"De %s (%d troupes)",reg[region].nom, reg[region].milita);
    sprintf(texteb,"Vers %s (%d troupes)",reg[aller].nom, reg[aller].milita);
    sprintf(textec,"%d",envoie);
    SDL_Color color = {255,255,255,255};
    surface[0] = TTF_RenderText_Blended(police,textea,color);
    surface[1] = TTF_RenderText_Blended(police,texteb,color);
    surface[2] = TTF_RenderText_Blended(police,textec,color);
    SDL_Rect local[3];
    initRect(&local[0],0,80,surface[0]->w, surface[0]->h);
    initRect(&local[1],0,120,surface[1]->w, surface[1]->h);
    initRect(&local[2],(500-surface[2]->w)/2,200,surface[2]->w, surface[2]->h);
    SDL_Rect rect[3];
    initRect(&rect[0],0,80,500, 50);
    initRect(&rect[1],0,120,500, 50);
    initRect(&rect[2],((500-surface[2]->w)/2-10), 200, 50, 50);
    SDL_Texture *texte;
    for (i=0;i<3;i++){
        texte = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_FreeSurface(surface[i]);
        SDL_SetRenderTarget(renderer,texture);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderFillRect(renderer,&rect[i]);
        SDL_RenderCopy(renderer,texte,NULL,&local[i]);
        SDL_DestroyTexture(texte);
        SDL_SetRenderTarget(renderer,NULL);
    }

}

void sous_fonction_attaque(SDL_Texture *frame, SDL_Texture *fond, SDL_Renderer *renderer, SDL_Texture * texture, SDL_Rect endroits[5], int *mouvement, int x, int y, TTF_Font *police, region reg[69],
                           int region, int aller, int joueur, int *victoire, Mix_Chunk *clic, Mix_Chunk *combat)
{
    SDL_Rect affichage;
    int continuer = 1;
    SDL_Event event;
    int h,w,i;
    int envoie = 0;
    SDL_Rect rect_tout = {0, 0, 1600, 900};

    affichage.x = x;
    affichage.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    affichage.w = w;
    affichage.h = h;
    if (x+w > 1600){
        affichage.x = affichage.x - w;
    }
    if (y+h > 900){
        affichage.y = affichage.y - h;
    }

    ///fonction info
    reinit_texture(reg, region, aller, police, envoie, renderer, texture); //texture est l'affichage de notre petit menu
    SDL_Texture *fond_tmp = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1600,900);
    SDL_SetRenderTarget(renderer, fond_tmp);
    SDL_RenderCopy(renderer, fond, NULL, &rect_tout);
    SDL_RenderCopy(renderer, texture, NULL, &affichage);
    SDL_SetRenderTarget(renderer, frame);
    SDL_RenderCopy(renderer, fond_tmp, NULL, &rect_tout);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
    SDL_RenderPresent(renderer);

    SDL_Rect position[5];
    for (i=0;i<5;i++){
        position[i].x = endroits[i].x + x;
        position[i].y = endroits[i].y + y;
        position[i].w = endroits[i].w;
        position[i].h = endroits[i].h;
        if (x+w > 1600){
            position[i].x = position[i].x - w;
        }
        if (y+h > 900){
            position[i].y = position[i].y - h;
        }
    }

    //int max = 15 - reg[aller].milita;///quoi ?

    while(continuer){
        SDL_Delay(50);
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
                case SDL_QUIT :
                    continuer = 0;
                    *mouvement = 0;
                    break;
                case SDL_MOUSEMOTION :
                    survoler_2(renderer, frame, fond_tmp, position, event, 5);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    switch (click(renderer,position,event,5,clic))
                    {
                    case 1 :
                        if (envoie++ > reg[region].milita-1){
                               envoie--;
                        }
                        break;
                    case 2 :
                        if (envoie-- < 1){
                            envoie++;
                        }
                        break;
                    case 3 :
                        ///deplacement des troupes pour l'attaque
                        if (envoie != 0){
                            sous_sous_fonction_attaque(affichage.x, affichage.y, envoie, reg, aller, renderer, police, joueur, region, victoire, combat);
                        }
                        continuer = 0;
                        break;
                    case 4 :
                        continuer = 0;
                        *mouvement = 0;
                        break;
                    }
                    printf("loop\n");
                    reinit_texture(reg, region, aller, police, envoie, renderer, texture); //texture est l'affichage de notre petit menu
                    SDL_SetRenderTarget(renderer, fond_tmp);
                    SDL_RenderCopy(renderer, texture, NULL, &affichage);
                    SDL_SetRenderTarget(renderer, frame);
                    SDL_RenderCopy(renderer, fond_tmp, NULL, &rect_tout);
                    SDL_SetRenderTarget(renderer, NULL);
                    SDL_RenderCopy(renderer, frame, NULL, &rect_tout);
                    SDL_RenderPresent(renderer);
                    break;
            }
        }
    }

}

void sous_sous_fonction_attaque(int x, int y, int envoie, region reg[], int aller, SDL_Renderer *renderer, TTF_Font *police, int joueur, int origine,
                                int *victoire, Mix_Chunk *combat)
{
    SDL_Texture *ecran = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 300);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetRenderTarget(renderer,ecran);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_Rect noir = {x,y,500,300};

    SDL_Color color = {255,255,255,255};
    srand(time(NULL));
    int score_attaquant[3];
    int score_defenseur[3];
    definirScore(envoie,score_attaquant);
    definirScore(reg[aller].milita,score_defenseur);
    int i;
    reg[origine].milita = reg[origine].milita - envoie;


    char textea[30];
    char texte[6][3];
    SDL_Surface *surface[11];
    sprintf(textea,"%d troupes contre %d troupes",envoie,reg[aller].milita);
    for (i=0;i<3;i++){
        sprintf(texte[i],"%d",score_attaquant[i]);

    }
    for (i=3;i<6;i++){
        sprintf(texte[i],"%d",score_defenseur[i-3]);
    }

    Mix_PlayChannel(1,combat,0);
    for (i=0;i<3;i++){
        if (score_defenseur[i] != 0 && score_attaquant[i] != 0){
            if (score_attaquant[i] > score_defenseur[i]){
                surface[i+8] = TTF_RenderText_Blended(police,"victoire",color);
                reg[aller].milita--;
            }
            else{
                surface[i+8] = TTF_RenderText_Blended(police,"defaite",color);
                envoie--;
            }
        }
        else{
            surface[i+8] = TTF_RenderText_Blended(police,"pas de combat",color);
        }

    }

    if(reg[aller].milita <= 0){
        reg[aller].appartenance = joueur;
        reg[aller].milita = envoie;
        *victoire = 1;
        reg[aller].pts_move = 0;
    }
    else{
        reg[origine].milita = reg[origine].milita + envoie;
    }


    surface[0] = TTF_RenderText_Blended(police,"COMBAT",color);
    surface[1] = TTF_RenderText_Blended(police,textea,color);
    for (i=2;i<8;i++){
        surface[i] = TTF_RenderText_Blended(police,texte[i-2],color);
    }
    SDL_Rect position[11];
    initRect(&position[0],250-surface[0]->w/2,0,surface[0]->w,surface[0]->h);
    initRect(&position[1],250-surface[1]->w/2,50,surface[1]->w,surface[1]->h);
    initRect(&position[2],100,100,surface[2]->w,surface[2]->h);
    initRect(&position[3],100,150,surface[3]->w,surface[3]->h);
    initRect(&position[4],100,200,surface[4]->w,surface[4]->h);
    initRect(&position[5],400,100,surface[5]->w,surface[5]->h);
    initRect(&position[6],400,150,surface[6]->w,surface[6]->h);
    initRect(&position[7],400,200,surface[7]->w,surface[7]->h);
    initRect(&position[8],250-surface[8]->w/2,100,surface[8]->w,surface[8]->h);
    initRect(&position[9],250-surface[9]->w/2,150,surface[9]->w,surface[9]->h);
    initRect(&position[10],250-surface[10]->w/2,200,surface[10]->w,surface[10]->h);

    SDL_Texture *texture;
    for (i=0;i<11;i++){
        texture = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_FreeSurface(surface[i]);
        SDL_SetRenderTarget(renderer,ecran);
        SDL_RenderCopy(renderer,texture,NULL,&position[i]);
        SDL_DestroyTexture(texture);
        SDL_SetRenderTarget(renderer,NULL);
    }
    SDL_RenderCopy(renderer,ecran,NULL,&noir);
    SDL_DestroyTexture(ecran);
    SDL_RenderPresent(renderer);
    SDL_Delay(4000);
}

void definirScore(int nbre, int points[3])
{
    int i;
    //printf("nbre = %d\n",nbre);

    for (i=0;i<3;i++){
        points[i] = 0;
    }

    if (nbre >= 3){
        int temp = 0;
        int *score = NULL;
        score = malloc(nbre *sizeof(int));

        for (i=0;i<nbre;i++){
            score[i] = (rand() % (6 - 1 + 1)) + 1;
        }

        i = 1;
        while (i < nbre){
            if (score[i] > score[i - 1]){
                temp = score[i];
                score[i] = score[i - 1];
                score[i - 1] = temp;
                i = 1;
            }
            else{
                i++;
            }
        }

        for (i=0;i<3;i++){
            if (score[i] > 6 || score[i] < 1){
                score[i] = 0;
            }
            points[i] = score[i];
        }
        free(score);
    }
    else if (nbre == 2){
        int temp = 0;
        int *score = NULL;
        score = malloc(nbre *sizeof(int));

        for (i=0;i<nbre;i++){
            score[i] = (rand() % (6 - 1 + 1)) + 1;
        }

        i = 1;
        while (i < nbre){
            if (score[i] > score[i - 1]){
                temp = score[i];
                score[i] = score[i - 1];
                score[i - 1] = temp;
                i = 1;
            }
            else{
                i++;
            }
        }

        for (i=0;i<2;i++){
            points[i] = score[i];
        }
        points[2] = 0;
        free(score);
    }
    else{
        points[0] = (rand() % (6 - 1 + 1)) + 1;
        points[1] = 0;
        points[2] = 0;
    }
}
