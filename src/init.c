#include "init.h"

///initialiser les textures
void initmenubase(SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[],
                                                            SDL_Texture *menu)
{
    int i;
    SDL_Surface * surfaces[5];
    SDL_Texture * texture[5];
    SDL_Color white = {255,255,255,255};

    surfaces[0] = TTF_RenderText_Blended(police,"Risk",white);
    surfaces[1] = TTF_RenderText_Blended(police,"Nouveau",white);
    surfaces[2] = TTF_RenderText_Blended(police,"Charger",white);
    surfaces[3] = TTF_RenderText_Blended(police,"Options",white);
    surfaces[4] = TTF_RenderText_Blended(police,"Quitter",white);

    initRect(&position[0], (500-surfaces[0]->w)/2, 0, surfaces[0]->w, surfaces[0]->h);
    initRect(&position[1], (500-surfaces[1]->w)/2, 200, surfaces[1]->w, surfaces[1]->h);
    initRect(&position[2], (500-surfaces[2]->w)/2, 300, surfaces[2]->w, surfaces[2]->h);
    initRect(&position[3], (500-surfaces[3]->w)/2, 400, surfaces[3]->w, surfaces[3]->h);
    initRect(&position[4], (500-surfaces[4]->w)/2, 600, surfaces[4]->w, surfaces[4]->h);

    SDL_SetRenderTarget(renderer,menu);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rectangle = {0,0,500,700};
    SDL_RenderFillRect(renderer,&rectangle);
    for (i=0;i<5;i++){
        texture[i] = SDL_CreateTextureFromSurface(renderer,surfaces[i]);
        SDL_RenderCopy(renderer,texture[i],NULL,&position[i]);
    }
    SDL_SetRenderTarget(renderer,NULL);
    initRect(&position[0], (1600-surfaces[0]->w)/2, 100, surfaces[0]->w, surfaces[0]->h);
    initRect(&position[1], (1600-surfaces[1]->w)/2, 300, surfaces[1]->w, surfaces[1]->h);
    initRect(&position[2], (1600-surfaces[2]->w)/2, 400, surfaces[2]->w, surfaces[2]->h);
    initRect(&position[3], (1600-surfaces[3]->w)/2, 500, surfaces[3]->w, surfaces[3]->h);
    initRect(&position[4], (1600-surfaces[4]->w)/2, 700, surfaces[4]->w, surfaces[4]->h);

    for(i=0;i<5;i++){
        SDL_FreeSurface(surfaces[i]);
        SDL_DestroyTexture(texture[i]);
    }
}

void initmenunew (SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[],
                                                            SDL_Texture *menu)
{
    int i;
    SDL_Color white = {255,255,255,255};
    SDL_Surface * surface[9];
    SDL_Texture * texture[9];
    surface[0] = TTF_RenderText_Blended(police,"Choisir une faction",white);
    surface[1] = TTF_RenderText_Blended(police,"Europe",white);
    surface[2] = TTF_RenderText_Blended(police,"Amerique",white);
    surface[3] = TTF_RenderText_Blended(police,"Bresil",white);
    surface[4] = TTF_RenderText_Blended(police,"Afrique",white);
    surface[5] = TTF_RenderText_Blended(police,"Oceanie",white);
    surface[6] = TTF_RenderText_Blended(police,"Asie",white);
    surface[7] = TTF_RenderText_Blended(police,"retour",white);
    surface[8] = TTF_RenderText_Blended(police,"jouer",white);
    initRect(&position[0], (500-surface[0]->w)/2, 0, surface[0]->w, surface[0]->h);
    initRect(&position[1], (300-surface[1]->w)/2, 150, surface[1]->w, surface[1]->h);
    initRect(&position[2], (300-surface[2]->w)/2, 230, surface[2]->w, surface[2]->h);
    initRect(&position[3], (300-surface[3]->w)/2, 310, surface[3]->w, surface[3]->h);
    initRect(&position[4], (300-surface[4]->w)/2, 390, surface[4]->w, surface[4]->h);
    initRect(&position[5], (300-surface[5]->w)/2, 470, surface[5]->w, surface[5]->h);
    initRect(&position[6], (300-surface[6]->w)/2, 550, surface[6]->w, surface[6]->h);
    initRect(&position[7], (300-surface[7]->w)/2, 600, surface[7]->w, surface[7]->h);
    initRect(&position[8], (700-surface[8]->w)/2, 600, surface[8]->w, surface[8]->h);

    SDL_SetRenderTarget(renderer,menu);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rectangle = {00,0,500,700};
    SDL_RenderFillRect(renderer,&rectangle);
    for (i=0;i<9;i++){
        texture[i] = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_RenderCopy(renderer,texture[i],NULL,&position[i]);
    }
    SDL_SetRenderTarget(renderer,NULL);
    initRect(&position[0], (1600-surface[0]->w)/2, 100, surface[0]->w, surface[0]->h);
    initRect(&position[1], (1400-surface[1]->w)/2, 250, surface[1]->w, surface[1]->h);
    initRect(&position[2], (1400-surface[2]->w)/2, 330, surface[2]->w, surface[2]->h);
    initRect(&position[3], (1400-surface[3]->w)/2, 410, surface[3]->w, surface[3]->h);
    initRect(&position[4], (1400-surface[4]->w)/2, 490, surface[4]->w, surface[4]->h);
    initRect(&position[5], (1400-surface[5]->w)/2, 570, surface[5]->w, surface[5]->h);
    initRect(&position[6], (1400-surface[6]->w)/2, 650, surface[6]->w, surface[6]->h);
    initRect(&position[7], (1400-surface[7]->w)/2, 700, surface[7]->w, surface[7]->h);
    initRect(&position[8], (1800-surface[8]->w)/2, 700, surface[8]->w, surface[8]->h);
    for(i=0;i<9;i++){
        SDL_FreeSurface(surface[i]);
        SDL_DestroyTexture(texture[i]);
    }
}

void init_menu_echap(SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[],
                                    SDL_Texture *menu)
{
    int i;
    SDL_Color white = {255,255,255,255};
    SDL_Surface * surface[6];
    SDL_Texture * texture[6];
    surface[0] = TTF_RenderText_Blended(police,"Risk",white);
    surface[1] = TTF_RenderText_Blended(police,"Menu principal",white);
    surface[2] = TTF_RenderText_Blended(police,"Sauvegarder",white);
    surface[3] = TTF_RenderText_Blended(police,"Options",white);
    surface[4] = TTF_RenderText_Blended(police,"Reprendre la partie",white);
    surface[5] = TTF_RenderText_Blended(police,"Quitter",white);
    initRect(&position[0], (500-surface[0]->w)/2, 0, surface[0]->w, surface[0]->h);
    initRect(&position[1], (500-surface[1]->w)/2, 150, surface[1]->w, surface[1]->h);
    initRect(&position[2], (500-surface[2]->w)/2, 250, surface[2]->w, surface[2]->h);
    initRect(&position[3], (500-surface[3]->w)/2, 350, surface[3]->w, surface[3]->h);
    initRect(&position[4], (500-surface[4]->w)/2, 450, surface[4]->w, surface[4]->h);
    initRect(&position[5], (500-surface[5]->w)/2, 600, surface[5]->w, surface[5]->h);

    SDL_SetRenderTarget(renderer,menu);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rectangle = {0,0,500,700};
    SDL_RenderFillRect(renderer,&rectangle);
    for (i=0;i<6;i++){
        texture[i] = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_RenderCopy(renderer,texture[i],NULL,&position[i]);
    }
    SDL_SetRenderTarget(renderer,NULL);
    initRect(&position[0], (1600-surface[0]->w)/2, 100, surface[0]->w, surface[0]->h);
    initRect(&position[1], (1600-surface[1]->w)/2, 250, surface[1]->w, surface[1]->h);
    initRect(&position[2], (1600-surface[2]->w)/2, 350, surface[2]->w, surface[2]->h);
    initRect(&position[3], (1600-surface[3]->w)/2, 450, surface[3]->w, surface[3]->h);
    initRect(&position[4], (1600-surface[4]->w)/2, 550, surface[4]->w, surface[4]->h);
    initRect(&position[5], (1600-surface[5]->w)/2, 700, surface[5]->w, surface[5]->h);
    for(i=0;i<6;i++){
        SDL_FreeSurface(surface[i]);
        SDL_DestroyTexture(texture[i]);
    }
}

void init_menu_save (SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[7],
                                                            SDL_Texture *menu)
{
    int i;
    SDL_Color white = {255,255,255,255};
    SDL_Surface * surface[7];
    SDL_Texture * texture[7];
    surface[0] = TTF_RenderText_Blended(police,"Sauvegarder",white);
    surface[1] = TTF_RenderText_Blended(police,"sauvegarde 1",white);
    surface[2] = TTF_RenderText_Blended(police,"sauvegarde 2",white);
    surface[3] = TTF_RenderText_Blended(police,"sauvegarde 3",white);
    surface[4] = TTF_RenderText_Blended(police,"sauvegarde 4",white);
    surface[5] = TTF_RenderText_Blended(police,"sauvegarde 5",white);
    surface[6] = TTF_RenderText_Blended(police,"retour",white);
    initRect(&position[0], (500-surface[0]->w)/2, 0, surface[0]->w, surface[0]->h);
    initRect(&position[1], (500-surface[1]->w)/2, 150, surface[1]->w, surface[1]->h);
    initRect(&position[2], (500-surface[2]->w)/2, 230, surface[2]->w, surface[2]->h);
    initRect(&position[3], (500-surface[3]->w)/2, 310, surface[3]->w, surface[3]->h);
    initRect(&position[4], (500-surface[4]->w)/2, 390, surface[4]->w, surface[4]->h);
    initRect(&position[5], (500-surface[5]->w)/2, 470, surface[5]->w, surface[5]->h);
    initRect(&position[6], (500-surface[6]->w)/2, 600, surface[6]->w, surface[6]->h);

    SDL_SetRenderTarget(renderer,menu);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rectangle = {00,0,500,700};
    SDL_RenderFillRect(renderer,&rectangle);
    for (i=0;i<7;i++){
        texture[i] = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_RenderCopy(renderer,texture[i],NULL,&position[i]);
    }
    SDL_SetRenderTarget(renderer,NULL);
    initRect(&position[0], (1600-surface[0]->w)/2, 100, surface[0]->w, surface[0]->h);
    initRect(&position[1], (1600-surface[1]->w)/2, 250, surface[1]->w, surface[1]->h);
    initRect(&position[2], (1600-surface[2]->w)/2, 330, surface[2]->w, surface[2]->h);
    initRect(&position[3], (1600-surface[3]->w)/2, 410, surface[3]->w, surface[3]->h);
    initRect(&position[4], (1600-surface[4]->w)/2, 490, surface[4]->w, surface[4]->h);
    initRect(&position[5], (1600-surface[5]->w)/2, 570, surface[5]->w, surface[5]->h);
    initRect(&position[6], (1600-surface[6]->w)/2, 700, surface[6]->w, surface[6]->h);
    for(i=0;i<7;i++){
        SDL_FreeSurface(surface[i]);
        SDL_DestroyTexture(texture[i]);
    }
}

void init_menu_charger (SDL_Renderer *renderer, TTF_Font *police, SDL_Rect position[7],
                                                            SDL_Texture *menu)
{
    int i;
    SDL_Color white = {255,255,255,255};
    SDL_Surface * surface[7];
    SDL_Texture * texture[7];
    surface[0] = TTF_RenderText_Blended(police,"Charger",white);
    surface[1] = TTF_RenderText_Blended(police,"sauvegarde 1",white);
    surface[2] = TTF_RenderText_Blended(police,"sauvegarde 2",white);
    surface[3] = TTF_RenderText_Blended(police,"sauvegarde 3",white);
    surface[4] = TTF_RenderText_Blended(police,"sauvegarde 4",white);
    surface[5] = TTF_RenderText_Blended(police,"sauvegarde 5",white);
    surface[6] = TTF_RenderText_Blended(police,"retour",white);
    initRect(&position[0], (500-surface[0]->w)/2, 0, surface[0]->w, surface[0]->h);
    initRect(&position[1], (500-surface[1]->w)/2, 150, surface[1]->w, surface[1]->h);
    initRect(&position[2], (500-surface[2]->w)/2, 230, surface[2]->w, surface[2]->h);
    initRect(&position[3], (500-surface[3]->w)/2, 310, surface[3]->w, surface[3]->h);
    initRect(&position[4], (500-surface[4]->w)/2, 390, surface[4]->w, surface[4]->h);
    initRect(&position[5], (500-surface[5]->w)/2, 470, surface[5]->w, surface[5]->h);
    initRect(&position[6], (500-surface[6]->w)/2, 600, surface[6]->w, surface[6]->h);

    SDL_SetRenderTarget(renderer,menu);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rectangle = {00,0,500,700};
    SDL_RenderFillRect(renderer,&rectangle);
    for (i=0;i<7;i++){
        texture[i] = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_RenderCopy(renderer,texture[i],NULL,&position[i]);
    }
    SDL_SetRenderTarget(renderer,NULL);
    initRect(&position[0], (1600-surface[0]->w)/2, 100, surface[0]->w, surface[0]->h);
    initRect(&position[1], (1600-surface[1]->w)/2, 250, surface[1]->w, surface[1]->h);
    initRect(&position[2], (1600-surface[2]->w)/2, 330, surface[2]->w, surface[2]->h);
    initRect(&position[3], (1600-surface[3]->w)/2, 410, surface[3]->w, surface[3]->h);
    initRect(&position[4], (1600-surface[4]->w)/2, 490, surface[4]->w, surface[4]->h);
    initRect(&position[5], (1600-surface[5]->w)/2, 570, surface[5]->w, surface[5]->h);
    initRect(&position[6], (1600-surface[6]->w)/2, 700, surface[6]->w, surface[6]->h);
    for(i=0;i<7;i++){
        SDL_FreeSurface(surface[i]);
        SDL_DestroyTexture(texture[i]);
    }
}

void initregion(region reg[])
{
    FILE *fichier = fopen("doc/regions.txt","r");
    FILE *acces = fopen("doc/acces.txt","r");
    int accez;
    srand(time(NULL));
    SDL_Surface *carte = IMG_Load("doc/map.tga");

    for (int i=0;i<NB_REG;i++){
            fscanf(fichier,"%c %s %d %d %d c: %d %d\n",&reg[i].pocesseur,
            reg[i].nom, &reg[i].rouge, &reg[i].vert, &reg[i].bleu, &reg[i].x,
                            &reg[i].y);
            reg[i].couleur = SDL_MapRGBA(carte->format, reg[i].rouge, reg[i].vert,
                                                reg[i].bleu,255);
            reg[i].milita = (rand() % (5 - 1 + 1)) + 1;
            reg[i].pts_move = reg[i].milita;
            switch (reg[i].pocesseur)
            {
            case 'e' :
                reg[i].appartenance = 0;
                break;
            case 'a' :
                reg[i].appartenance = 1;
                break;
            case 'b' :
                reg[i].appartenance = 2;
                break;
            case 'f' :
                reg[i].appartenance = 3;
                break;
            case 'o' :
                reg[i].appartenance = 4;
                break;
            case 'c' :
                reg[i].appartenance = 5;
                break;
            }
            for (int e=0;e<NB_REG;e++){
                reg[i].acces[e] = 0;
            }
            fscanf(acces,"%d ",&reg[i].nbreacces);
            //printf ("%d ",reg[i].nbreacces);

    }
    fscanf(acces,"\n");
    for (int i=0;i<NB_REG;i++){
        for (int e=0;e<reg[i].nbreacces;e++){
            fscanf(acces,"%d ",&accez);
            reg[i].acces[accez-1] = 1;
        }
    }
    SDL_FreeSurface(carte);
    fclose(fichier);
    fclose(acces);
}

void initempire(empire emp[])
{
    FILE *fichier = fopen("doc/empires.txt","r");
    if (fichier == NULL){
        printf ("erreur de doc !\n");
    }
    for (int i=0;i<NB_EMP;i++){
        fscanf(fichier,"%s %d %d %d\n",emp[i].nom,&emp[i].rouge,&emp[i].vert,&emp[i].bleu);
        emp[i].live = 1;
    }
}

void initRect (SDL_Rect *rectangle,int x,int y,int w,int h)
{
    rectangle->x = x;
    rectangle->y = y;
    rectangle->w = w;
    rectangle->h = h;
}

void init_texture_renforts(SDL_Texture *texture[23], TTF_Font *police,
                                                    SDL_Renderer *renderer)
{
    SDL_Surface *surface[23];
    SDL_Color color = {255,255,255,255};
    char chaine[22];

    for (int i=0;i<23;i++){
        sprintf(chaine,"%d renforts restants",i);
        surface[i] = TTF_RenderText_Blended(police, chaine, color);
        texture[i] = SDL_CreateTextureFromSurface(renderer, surface[i]);
        SDL_FreeSurface(surface[i]);
    }
}

void init_texture_fin (SDL_Texture **texture, TTF_Font *police, SDL_Renderer *renderer)
{
    SDL_Color color = {255,255,255,255};
    SDL_Surface *surface = NULL;
    surface = TTF_RenderText_Blended(police,"Fin de tour",color);
    *texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
}

void init_texture_ordi(SDL_Texture **Ai,SDL_Texture **Humain, TTF_Font *police,
                            SDL_Renderer *renderer)
{
    SDL_Color color = {255,255,255,255};
    SDL_Surface *ai = TTF_RenderText_Blended(police,"ordi",color);
    SDL_Surface *humain = TTF_RenderText_Blended(police,"humain",color);

    *Ai = SDL_CreateTextureFromSurface(renderer,ai);
    *Humain = SDL_CreateTextureFromSurface(renderer,humain);

    SDL_FreeSurface(ai);
    SDL_FreeSurface(humain);
}

void init_menu_mouvement(SDL_Texture *menu,TTF_Font *police,SDL_Renderer *renderer,
                    SDL_Rect position[])
{
    SDL_Color color = {255,255,255,255};
    SDL_Surface *surface[5];
    SDL_Texture *truc;
    surface[0] = TTF_RenderText_Blended(police,"DEPLACEMENT",color);
    surface[1] = TTF_RenderText_Blended(police," + ",color);
    surface[2] = TTF_RenderText_Blended(police,"-",color);
    surface[3] = TTF_RenderText_Blended(police,"envoyer",color);
    surface[4] = TTF_RenderText_Blended(police,"annuler",color);
    initRect(&position[0], (500-surface[0]->w)/2, 0, surface[0]->w, surface[0]->h);
    initRect(&position[1], 100, 200, surface[1]->w, surface[1]->h);
    initRect(&position[2], 350, 200, surface[2]->w, surface[2]->h);
    initRect(&position[3], 75, 250, surface[3]->w, surface[3]->h);
    initRect(&position[4], 325, 250, surface[4]->w, surface[4]->h);

    for (int i=0;i<5;i++){
        truc = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_FreeSurface(surface[i]);
        SDL_SetRenderTarget(renderer,menu);
        SDL_RenderCopy(renderer,truc,NULL,&position[i]);
        SDL_DestroyTexture(truc);
        SDL_SetRenderTarget(renderer,NULL);
    }
}

void init_menu_attaque(SDL_Texture *menu,TTF_Font *police,SDL_Renderer *renderer,SDL_Rect position[])
{
    SDL_Color color = {255,255,255,255};
    SDL_Surface *surface[5];
    SDL_Texture *truc;
    surface[0] = TTF_RenderText_Blended(police,"ATTAQUE",color);
    surface[1] = TTF_RenderText_Blended(police," + ",color);
    surface[2] = TTF_RenderText_Blended(police,"-",color);
    surface[3] = TTF_RenderText_Blended(police,"envoyer",color);
    surface[4] = TTF_RenderText_Blended(police,"annuler",color);
    initRect(&position[0], (500-surface[0]->w)/2, 0, surface[0]->w, surface[0]->h);
    initRect(&position[1], 100, 200, surface[1]->w, surface[1]->h);
    initRect(&position[2], 350, 200, surface[2]->w, surface[2]->h);
    initRect(&position[3], 75, 250, surface[3]->w, surface[3]->h);
    initRect(&position[4], 325, 250, surface[4]->w, surface[4]->h);

    for (int i=0;i<5;i++){
        truc = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_FreeSurface(surface[i]);
        SDL_SetRenderTarget(renderer,menu);
        SDL_RenderCopy(renderer,truc,NULL,&position[i]);
        SDL_DestroyTexture(truc);
        SDL_SetRenderTarget(renderer,NULL);
    }
}

void milita_sur_carte (SDL_Renderer *renderer, region reg[],TTF_Font *police){
    int w,h;
    SDL_Surface *surface[15];
    SDL_Texture *texture[15];
    SDL_Color color = {255,255,255,255};
    char milita[3];

    ///init les 15
    for (int i=0;i<15;i++){
        sprintf(milita,"%d",i+1);
        surface[i] = TTF_RenderText_Blended(police, milita, color);
        texture[i] = SDL_CreateTextureFromSurface(renderer,surface[i]);
        SDL_FreeSurface(surface[i]);
    }

        ///donne une des 15 selon milita
        for (int i=0;i<NB_REG;i++){
            if (reg[i].milita < 1){
                printf("erreur milita inferieur !\n");
            }
            reg[i].troupes = texture[reg[i].milita-1];
            SDL_QueryTexture(texture[reg[i].milita-1], NULL, NULL, &w, &h);
            initRect(&reg[i].rect,reg[i].x-10,reg[i].y-10,w,h);
        }

    ///affiche tout
    for (int i=0;i<NB_REG;i++){
        SDL_RenderCopy(renderer,reg[i].troupes,NULL,&reg[i].rect);
    }
    ///menage
    for (int i=0;i<15;i++){
        SDL_DestroyTexture(texture[i]);
    }
}

void charger_partie (region reg[], int partie, empire emp[], int *joueur)
{
    char texte[20];
    sprintf(texte,"doc/partie%d.sav",partie);
    //printf("open partie %d\n",partie);
    FILE *fichier = fopen (texte,"r");
    for (int i=0;i<NB_REG;i++){
        fscanf(fichier,"nom : %s appartenance : %d milita : %d mouvement : %d\n",reg[i].nom,&reg[i].appartenance,&reg[i].milita,&reg[i].pts_move);
    }
    for (int i=0;i<NB_EMP;i++){
        fscanf(fichier, "%s : %d\n",emp[i].nom,&emp[i].ordi);
    }
    fscanf(fichier,"joueur actuel : %d\n",joueur);
    fclose(fichier);
}
