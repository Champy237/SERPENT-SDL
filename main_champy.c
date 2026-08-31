#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction_champy.h"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    SDL_Window* fenetreChampy;
    SDL_Renderer* renduChampy;
    SDL_Event eChampy;
    int continuerChampy = 1;
    int directionXChampy = 1, directionYChampy = 0;
    SerpentPartieChampy serpentChampy[TAILLE_MAX_SERPENT_CHAMPY];
    int tailleSerpentChampy = 1;
    PommeChampy pommeChampy = {5, 5, 0};
    JeuChampy jeuChampy = {0, 0, 0};

    srand(time(NULL));

    initialiserSDLChampy(&fenetreChampy, &renduChampy);

    serpentChampy[0].xChampy = 10;
    serpentChampy[0].yChampy = 10;

    while (continuerChampy) {
        while (SDL_PollEvent(&eChampy)) {
            if (eChampy.type == SDL_QUIT) {
                continuerChampy = 0;
            } else if (eChampy.type == SDL_KEYDOWN) {
                if (eChampy.key.keysym.sym == SDLK_UP && directionYChampy != 1) {
                    directionXChampy = 0;
                    directionYChampy = -1;
                } else if (eChampy.key.keysym.sym == SDLK_DOWN && directionYChampy != -1) {
                    directionXChampy = 0;
                    directionYChampy = 1;
                } else if (eChampy.key.keysym.sym == SDLK_LEFT && directionXChampy != 1) {
                    directionXChampy = -1;
                    directionYChampy = 0;
                } else if (eChampy.key.keysym.sym == SDLK_RIGHT && directionXChampy != -1) {
                    directionXChampy = 1;
                    directionYChampy = 0;
                }
            }
        }

        deplacerSerpentChampy(serpentChampy, &tailleSerpentChampy, directionXChampy, directionYChampy, &jeuChampy);
        verifierCollisionsChampy(serpentChampy, &tailleSerpentChampy, &pommeChampy, &jeuChampy);

        if (jeuChampy.invincibleChampy && SDL_GetTicks() - jeuChampy.tempsInvincibiliteChampy > 20000) {
            jeuChampy.invincibleChampy = 0;
        }

        SDL_SetRenderDrawColor(renduChampy, 0, 0, 0, 255);
        SDL_RenderClear(renduChampy);

        dessinerSerpentChampy(renduChampy, serpentChampy, tailleSerpentChampy);
        dessinerPommeChampy(renduChampy, &pommeChampy);

        SDL_RenderPresent(renduChampy);

        SDL_Delay(100);
    }

    fermerSDLChampy(fenetreChampy, renduChampy);
    return 0;
}
