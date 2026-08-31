# Jeu du Serpent (Snake) en C avec SDL2

Jeu Snake développé en C avec la bibliothèque SDL2.
Contrôle du serpent au clavier, pommes classiques et pommes bonus.
Le bonus active une invincibilité temporaire qui permet de traverser les murs.
Gestion des collisions, de la croissance du serpent et du score.

## Aperçu du jeu

- Fenêtre de 640 x 480 pixels, grille de 32 x 24 cases (cases de 20 px)
- Le serpent est dessiné en vert
- Pomme normale : jaune
- Pomme bonus : rouge

## Règles

- Chaque pomme mangée augmente le score de 1 et allonge le serpent d'une case.
- Une pomme bonus (rouge) apparaît régulièrement : la manger active
  l'invincibilité pendant 20 secondes.
- Pendant l'invincibilité, le serpent traverse les bords de la fenêtre et
  réapparaît du côté opposé.
- Hors invincibilité, toucher un bord remet le score à 0 et le serpent à sa
  taille initiale.
- Se mordre la queue désactive l'invincibilité.

## Commandes

| Touche | Action |
| --- | --- |
| Flèche haut | Aller vers le haut |
| Flèche bas | Aller vers le bas |
| Flèche gauche | Aller vers la gauche |
| Flèche droite | Aller vers la droite |
| Fermer la fenêtre | Quitter le jeu |

Le demi-tour immédiat est interdit.

## Prérequis

- Un compilateur C (`gcc`)
- La bibliothèque SDL2 et ses fichiers de développement

Installation sur Debian / Ubuntu :

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev
```

## Compilation

```bash
make
```

## Lancement

```bash
./serpent
```

## Nettoyage

```bash
make clean
```

## Structure du projet

| Fichier | Rôle |
| --- | --- |
| `main_champy.c` | Boucle principale, gestion des événements et affichage |
| `fonction_champy.c` | Initialisation SDL, dessin, déplacement et collisions |
| `fonction_champy.h` | Structures (`SerpentPartieChampy`, `PommeChampy`, `JeuChampy`) et prototypes |
| `makefile` | Règles de compilation et de nettoyage |

## Auteur

NDJONG CEDRIC ALLAN — Université de Yaoundé 1
