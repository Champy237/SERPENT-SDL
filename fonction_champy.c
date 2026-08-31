#include "fonction_champy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialiserSDLChampy(SDL_Window** fenetreChampy, SDL_Renderer** renduChampy) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation SDL: %s\n", SDL_GetError());
        exit(1);
    }

    *fenetreChampy = SDL_CreateWindow("Jeu du Serpent Champy",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      LARGEUR_GRILLE_CHAMPY * TAILLE_CASE_CHAMPY,
                                      HAUTEUR_GRILLE_CHAMPY * TAILLE_CASE_CHAMPY,
                                      SDL_WINDOW_SHOWN);
    if (*fenetreChampy == NULL) {
        printf("Erreur lors de la creation de la fenetre: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    *renduChampy = SDL_CreateRenderer(*fenetreChampy, -1, SDL_RENDERER_ACCELERATED);
    if (*renduChampy == NULL) {
        printf("Erreur lors de la creation du rendu: %s\n", SDL_GetError());
        SDL_DestroyWindow(*fenetreChampy);
        SDL_Quit();
        exit(1);
    }
}

void fermerSDLChampy(SDL_Window* fenetreChampy, SDL_Renderer* renduChampy) {
    SDL_DestroyRenderer(renduChampy);
    SDL_DestroyWindow(fenetreChampy);
    SDL_Quit();
}

void dessinerSerpentChampy(SDL_Renderer* renduChampy, SerpentPartieChampy* serpentChampy, int tailleSerpentChampy) {
    SDL_SetRenderDrawColor(renduChampy, 0, 255, 0, 255);
    for (int iChampy = 0; iChampy < tailleSerpentChampy; iChampy++) {
        SDL_Rect rectChampy = {
            serpentChampy[iChampy].xChampy * TAILLE_CASE_CHAMPY,
            serpentChampy[iChampy].yChampy * TAILLE_CASE_CHAMPY,
            TAILLE_CASE_CHAMPY,
            TAILLE_CASE_CHAMPY
        };
        SDL_RenderFillRect(renduChampy, &rectChampy);
    }
}

void dessinerPommeChampy(SDL_Renderer* renduChampy, PommeChampy* pommeChampy) {
    SDL_Rect rectChampy = {
        pommeChampy->xChampy * TAILLE_CASE_CHAMPY,
        pommeChampy->yChampy * TAILLE_CASE_CHAMPY,
        TAILLE_CASE_CHAMPY,
        TAILLE_CASE_CHAMPY
    };
    if (pommeChampy->estBonusChampy) {
        SDL_SetRenderDrawColor(renduChampy, 255, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renduChampy, 255, 255, 0, 255);
    }
    SDL_RenderFillRect(renduChampy, &rectChampy);
}

void deplacerSerpentChampy(SerpentPartieChampy* serpentChampy, int* tailleSerpentChampy, int directionXChampy, int directionYChampy, JeuChampy* jeuChampy) {
    for (int iChampy = *tailleSerpentChampy - 1; iChampy > 0; iChampy--) {
        serpentChampy[iChampy] = serpentChampy[iChampy - 1];
    }
    serpentChampy[0].xChampy += directionXChampy;
    serpentChampy[0].yChampy += directionYChampy;

    if (jeuChampy->invincibleChampy) {
        if (serpentChampy[0].xChampy < 0) {
            serpentChampy[0].xChampy = LARGEUR_GRILLE_CHAMPY - 1;
        } else if (serpentChampy[0].xChampy >= LARGEUR_GRILLE_CHAMPY) {
            serpentChampy[0].xChampy = 0;
        }

        if (serpentChampy[0].yChampy < 0) {
            serpentChampy[0].yChampy = HAUTEUR_GRILLE_CHAMPY - 1;
        } else if (serpentChampy[0].yChampy >= HAUTEUR_GRILLE_CHAMPY) {
            serpentChampy[0].yChampy = 0;
        }
    }
}

void verifierCollisionsChampy(SerpentPartieChampy* serpentChampy, int* tailleSerpentChampy, PommeChampy* pommeChampy, JeuChampy* jeuChampy) {
    if (serpentChampy[0].xChampy == pommeChampy->xChampy && serpentChampy[0].yChampy == pommeChampy->yChampy) {
        jeuChampy->scoreChampy++;
        if (*tailleSerpentChampy < TAILLE_MAX_SERPENT_CHAMPY) {
            (*tailleSerpentChampy)++;
        }

        if (pommeChampy->estBonusChampy) {
            jeuChampy->invincibleChampy = 1;
            jeuChampy->tempsInvincibiliteChampy = SDL_GetTicks();
        }

        pommeChampy->estBonusChampy = (jeuChampy->scoreChampy % 2 == 0);
        pommeChampy->xChampy = rand() % LARGEUR_GRILLE_CHAMPY;
        pommeChampy->yChampy = rand() % HAUTEUR_GRILLE_CHAMPY;
    }

    for (int iChampy = 1; iChampy < *tailleSerpentChampy; iChampy++) {
        if (serpentChampy[0].xChampy == serpentChampy[iChampy].xChampy && serpentChampy[0].yChampy == serpentChampy[iChampy].yChampy) {
            jeuChampy->invincibleChampy = 0;
        }
    }

    if (!jeuChampy->invincibleChampy) {
        if (serpentChampy[0].xChampy < 0 || serpentChampy[0].xChampy >= LARGEUR_GRILLE_CHAMPY ||
            serpentChampy[0].yChampy < 0 || serpentChampy[0].yChampy >= HAUTEUR_GRILLE_CHAMPY) {
            jeuChampy->scoreChampy = 0;
            *tailleSerpentChampy = 1;
            serpentChampy[0].xChampy = LARGEUR_GRILLE_CHAMPY / 2;
            serpentChampy[0].yChampy = HAUTEUR_GRILLE_CHAMPY / 2;
        }
    }
}
