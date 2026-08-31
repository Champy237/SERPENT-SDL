#ifndef FONCTION_CHAMPY_H
#define FONCTION_CHAMPY_H

#include <SDL2/SDL.h>

#define TAILLE_CASE_CHAMPY 20
#define LARGEUR_GRILLE_CHAMPY 32
#define HAUTEUR_GRILLE_CHAMPY 24
#define TAILLE_MAX_SERPENT_CHAMPY 100

typedef struct {
    int xChampy, yChampy;
} SerpentPartieChampy;

typedef struct {
    int xChampy, yChampy;
    int estBonusChampy;
} PommeChampy;

typedef struct {
    int scoreChampy;
    int invincibleChampy;
    Uint32 tempsInvincibiliteChampy;
} JeuChampy;

void initialiserSDLChampy(SDL_Window** fenetreChampy, SDL_Renderer** renduChampy);
void fermerSDLChampy(SDL_Window* fenetreChampy, SDL_Renderer* renduChampy);
void dessinerSerpentChampy(SDL_Renderer* renduChampy, SerpentPartieChampy* serpentChampy, int tailleSerpentChampy);
void dessinerPommeChampy(SDL_Renderer* renduChampy, PommeChampy* pommeChampy);
void deplacerSerpentChampy(SerpentPartieChampy* serpentChampy, int* tailleSerpentChampy, int directionXChampy, int directionYChampy, JeuChampy* jeuChampy);
void verifierCollisionsChampy(SerpentPartieChampy* serpentChampy, int* tailleSerpentChampy, PommeChampy* pommeChampy, JeuChampy* jeuChampy);

#endif
