#include "AI.h"

void intelligence_artificielle (SDL_Texture *frame, SDL_Texture *fond,int joueur,
     region reg[], empire emp[], SDL_Renderer *renderer, SDL_Texture **Carte,
     SDL_Surface *carte_region, SDL_Surface **carte_affiche, TTF_Font *petit,
                                int *jouer, int *boucle, SDL_Rect position_echap[],
                                SDL_Texture *menu, Mix_Chunk *clic,
                                SDL_Texture *tex_menu_save, SDL_Rect rect_menu_save[])
{
    SDL_Delay(50);
    printf("entrer\n");
    int i,e;
    int menace[NB_REG] = {0};
    int attaque[NB_REG] = {0};
    int aller = 0;

    SDL_Rect faction = {66,696,207,111};
    SDL_Rect position = {0,0,1600,900};

    menace_et_attaque(menace, attaque, reg, joueur);
    ia_renfort(menace, attaque, reg, joueur);
    deplacement(reg, joueur, menace);

    printf("ok\n");
    const Uint8 *state;
    SDL_Event event;
    if (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_KEYDOWN :
                state = SDL_GetKeyboardState(NULL);
                    if (state[SDL_SCANCODE_ESCAPE]){
                        int sert_a_rien;
                        menu_echap(renderer,frame,fond,jouer,position_echap,menu,boucle,&sert_a_rien,clic,reg,petit,rect_menu_save,tex_menu_save,emp,joueur);
                        SDL_RenderCopy(renderer,*Carte,NULL,&position);
                        SDL_SetRenderDrawColor(renderer,emp[joueur].rouge,emp[joueur].vert,emp[joueur].bleu,255);
                        SDL_RenderFillRect(renderer,&faction);
                        milita_sur_carte(renderer,reg,petit);
                        SDL_RenderPresent(renderer);
                    }
                break;
            case SDL_QUIT :
                *boucle = 0;
                *jouer = 0;
                break;
        }
    }

    // redefinir attaque avant
    attaquer(attaque, joueur, reg);
    srand(time(NULL));
    for (i=0;i<NB_REG;i++){
        if (reg[i].appartenance == joueur && attaque[i] > 0){
            for (e=0;e<NB_REG;e++){
                if (reg[e].appartenance != joueur && reg[i].acces[e] == 1){
                    if ( (reg[i].milita > reg[e].milita) || (reg[i].milita >= reg[e].milita && reg[i].milita > 10) ){
                        aller = (rand() % (2 - 1 + 1));//???
                        if (aller == 1){
                            printf("au combat !\n");
                            combat(nbre_a_envoyer(reg, i, e, joueur, menace), reg, i, e, joueur, renderer, carte_region, carte_affiche, Carte, petit, emp);
                        }
                    }
                }
            }
        }
    }
    printf("ok fin\n");
}

void menace_et_attaque (int menace[], int attaque[], region reg[], int joueur){
    // parcourir les regions pour definir menace et la ou on peut attaquer
    for (int i=0;i<NB_REG;i++){
        // si c'est a la faction qui joue
        if (reg[i].appartenance == joueur){
            // parcours les acces
            for (int e=0;e<NB_REG;e++){
                // si acces
                if (reg[i].acces[e] == 1){
                    if (reg[e].appartenance != joueur && reg[e].milita > reg[i].milita){
                        // definir un degre de menace
                        menace[i] = reg[e].milita - reg[i].milita;
                    }
                    else if (reg[e].appartenance != joueur && reg[e].milita < reg[i].milita){
                        attaque[i] = reg[i].milita - reg[e].milita;
                    }
                }
            }
        }
    }
}
int menacee (int menace, int joueur, region pro, region reg[]){
    int nbre = 0;
    for (int i=0;i<NB_REG;i++){
        if (pro.acces[i] == 1){
            if (reg[i].appartenance != joueur && reg[i].milita > pro.milita){
                menace = reg[i].milita - pro.milita;
                nbre = 1;
            }
        }
    }
    return nbre;
}

void ia_renfort(int menace[], int attaque[], region reg[], int joueur){
    int renforts = 0;
    int nbre_regions = 0;
    for (int i=0;i<NB_REG;i++)///nbre de renforts
    {
        if (reg[i].appartenance == joueur){
            nbre_regions++;
        }
    }
    if (nbre_regions >= 3){
        renforts = nbre_regions / 3;
    }
    else{
        renforts = 1;
    }

    ///repartir les renforts selon le degre de menace et la ou on peut attaquer
    for (int q=5;q>=0;q--){
        for (int i=0;i<NB_REG;i++){
            if (renforts != 0 && reg[i].milita < 15){
                if (menace[i] > q || attaque [i] > q){
                    renforts--;
                    reg[i].milita++;
                    //printf("je met un renfort\n");
                }
            }
        }
    }
    //printf("restants %d renforts\n",renforts);
    if (renforts != 0){
        for (int q=0;q<15;q++){
            for (int i=0;i<NB_REG;i++){
                if (reg[i].appartenance == joueur && reg[i].milita == q && renforts != 0){
                    reg[i].milita++;
                    renforts--;
                    //printf("j'en met un la %d\n",i);
                }
            }
        }
    }
    //printf("renforts restants %d\n",renforts);
}

void deplacement (region reg[], int joueur, int menace[]){
    printf("dans deplacement\n");
    ///bouger pour retablir defense sans s'exposer
    for (int i=0;i<NB_REG;i++){
        if (reg[i].appartenance == joueur && menace[i] > 0){
            for (int e=0;e<NB_REG;e++){
                if (reg[i].acces[e] == 1 && menace[e] == 0 && reg[e].appartenance == joueur){
                    do{
                        if (reg[e].milita > 1 && reg[i].milita < 15){
                            reg[e].milita--;
                            //printf("-1 a %s\n",reg[e].nom);
                            reg[i].milita++;
                            //printf("+1 a %s\n",reg[i].nom);
                        }
                        //printf("menace !\n");
                        //printf("%d %d\n",menacee(menace[e], joueur, reg[e], reg),reg[e].milita);
                    }while(menacee(menace[e], joueur, reg[e], reg) == 0 && reg[e].milita > 1 && reg[i].milita < 15);
                }
            }
        }
    }
}

void attaquer (int attaque[], int joueur, region reg[]){
    for (int i=0;i<NB_REG;i++){
        if (reg[i].appartenance == joueur){
            for (int e=0;e<NB_REG;e++){
                if (reg[i].acces[e] == 1){
                    if (reg[e].appartenance != joueur && reg[e].milita < reg[i].milita){
                        attaque[i] = reg[i].milita - reg[e].milita;
                    }
                    if (reg[e].milita == reg[i].milita && reg[e].appartenance != joueur){
                        attaque[i] = 1;
                    }
                }
            }
        }
    }
}
int nbre_a_envoyer (region reg[], int origine, int aller, int joueur, int menace[])
{
    int envoie = 0;
    int foncer = (rand() % (1 - 0 + 1) + 0);

    if (foncer == 1 && reg[origine].milita != reg[aller].milita){
        //printf("je fonce ! ");
        envoie = (rand() % ((reg[origine].milita-1) - reg[aller].milita + 1) + reg[aller].milita);
        reg[origine].milita = reg[origine].milita - envoie;
    }
    else{
        //printf("je suis prudent ");
        for (int i=0;i<NB_REG;i++){
            if (reg[origine].acces[i] == 1 && reg[i].appartenance == joueur && menace[i] == 0){
                do{
                        if (reg[i].milita > 1 && reg[origine].milita < 15){
                            reg[i].milita--;
                            //printf("-1 a %s\n",reg[i].nom);
                            reg[origine].milita++;
                            //printf("+1 a %s\n",reg[origine].nom);
                        }
                        //printf("%d %d\n",menacee(menace[i], joueur, reg[origine], reg),reg[i].milita);
                    }while(menacee(menace[i], joueur, reg[origine], reg) == 0 && reg[i].milita > 1 && reg[origine].milita < 15);
            }
        }
        envoie = reg[origine].milita / 2;
        if (envoie <= 0){
            printf ("erreur : %d %d",reg[origine].milita, reg[aller].milita);
        }
        reg[origine].milita = reg[origine].milita - envoie;
    }
    //printf("envoie : %d\n",envoie);
    return envoie;
}
void combat (int envoie, region reg[], int origine, int aller, int joueur,
    SDL_Renderer *renderer, SDL_Surface *carte_region, SDL_Surface **carte_affiche,
    SDL_Texture **Carte, TTF_Font *petit, empire emp[])
{
    SDL_Rect position = {0, 0, 1600, 900};

    srand(time(NULL));
    int score_attaquant[3];
    int score_defenseur[3];
    definirScore(envoie,score_attaquant);
    definirScore(reg[aller].milita,score_defenseur);

    //printf("\nenvoie %d de %s(%d) vers %s(%d)\n",envoie, reg[origine].nom,reg[origine].milita,reg[aller].nom,reg[aller].milita);
    //printf("%s attaque %s\n",emp[reg[origine].appartenance].nom,emp[reg[aller].appartenance].nom);
    for (int i=0;i<3;i++){
        if (score_defenseur[i] != 0 && score_attaquant[i] != 0){
            if (score_attaquant[i] > score_defenseur[i]){
                reg[aller].milita--;
            }
            else{
                envoie--;
            }
        }
    }
    //printf ("il reste %d (envoie)\n",envoie);
    if(reg[aller].milita <= 0){
        //printf("victoire !\n");
        reg[aller].appartenance = joueur;
        reg[aller].milita = envoie;
        reg[aller].pts_move = 0;
        recolorier_region(emp,reg,renderer,carte_region,carte_affiche,Carte,aller);
    }
    else{
        //printf("defaite ");
        reg[origine].milita = reg[origine].milita + envoie;
        //printf("attaquant = %d\n",reg[origine].milita);
    }
    SDL_Rect faction = {66,696,207,111};
    SDL_RenderCopy(renderer,*Carte,NULL,&position);
    SDL_SetRenderDrawColor(renderer,emp[joueur].rouge,emp[joueur].vert,emp[joueur].bleu,255);
    SDL_RenderFillRect(renderer,&faction);
    milita_sur_carte(renderer,reg,petit);
    SDL_RenderPresent(renderer);
}

void alive (empire emp[], region reg[]){
    int points[NB_EMP] = {0};

    for (int e=0;e<NB_EMP;e++){
        for (int i=0;i<NB_REG;i++){
            if (reg[i].appartenance == e){
                points[e]++;
            }
        }
        if (points[e] > 0){
            emp[e].live = 1;
        }
        else{
            emp[e].live = 0;
            //printf("%s est mort !\n",emp[e].nom);
        }
    }
}

int somme_faction (empire emp[]){
    int somme = 0;
    for (int i=0;i<NB_EMP;i++){
        if (emp[i].live == 1){
            somme++;
        }
    }
    return somme;
}
