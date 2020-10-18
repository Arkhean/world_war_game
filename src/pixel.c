#include "pixel.h"

Uint32 obtenirPixel (SDL_Surface * surface, int x, int y)
{
    int nbopp = surface->format->BitsPerPixel/8;
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * nbopp;

    switch (nbopp)
    {
    case 1 :
        return *p;
    case 2 :
        return *(Uint16*)p;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0]<<16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4 :
        return *(Uint32*)p;
    default :
        return 0;
    }
}

void definirPixel (SDL_Surface * surface, int x, int y, Uint32 pixel)
{
    int nbopp = surface->format->BitsPerPixel/8;
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * nbopp;

    switch (nbopp)
    {
    case 1 :
        *p = pixel;
        break;
    case 2 :
        *(Uint16*)p = pixel;
        break;
    case 3 :
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
            else
            {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
            }
            break;
    case 4 :
        *(Uint32*)p = pixel;
        break;
    }
}

void colorier_map (SDL_Surface *carte_region, SDL_Surface **carte_affiche, SDL_Texture **texture, int joueur, region reg[], empire emp[], SDL_Renderer *renderer)
{
    Uint32 pixel;
    int x,y,i;

        for (x=0;x<1600;x++){
            for (y=0;y<900;y++){
                for (i=0;i<NB_REG;i++){
                    pixel = obtenirPixel(carte_region, x, y);
                    if (pixel == reg[i].couleur){
                        pixel = SDL_MapRGBA(carte_region->format,emp[reg[i].appartenance].rouge, emp[reg[i].appartenance].vert, emp[reg[i].appartenance].bleu,255);
                        definirPixel(*carte_affiche,x,y,pixel);
                    }
                }
            }
        }

    SDL_DestroyTexture(*texture);
    *texture = SDL_CreateTextureFromSurface(renderer,*carte_affiche);
}
void encadrer (region reg[], int selection, SDL_Renderer *renderer, SDL_Texture *frame)
{
    SDL_SetRenderTarget(renderer, frame);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &reg[selection].rect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    int i;
    for(i=0;i<NB_REG;i++){
        if (reg[selection].acces[i] == 1){
            SDL_RenderDrawRect(renderer, &reg[i].rect);
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
}

void recolorier_region (empire emp[5], region reg[], SDL_Renderer *renderer, SDL_Surface *carte_region, SDL_Surface **carte_affiche, SDL_Texture **texture, int region)
{
    Uint32 pixel;
    int x,y;

        for (x=0;x<1600;x++){
            for (y=0;y<900;y++){
                pixel = obtenirPixel(carte_region, x, y);
                if (pixel == reg[region].couleur){
                    pixel = SDL_MapRGBA(carte_region->format, emp[reg[region].appartenance].rouge, emp[reg[region].appartenance].vert, emp[reg[region].appartenance].bleu,255);
                    definirPixel(*carte_affiche, x, y, pixel);
                }
            }
        }

    SDL_DestroyTexture(*texture);
    *texture = SDL_CreateTextureFromSurface(renderer, *carte_affiche);
}
