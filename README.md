# 🌟 Raytracing 2D en SDL2

## 🧠 Description

Ce projet est une démonstration simple et interactive de **raytracing 2D** réalisée en C avec la bibliothèque **SDL2**. Le programme simule un cercle qui émet des rayons dans toutes les directions. Lorsqu’un rayon touche un autre objet circulaire, il s'arrête, simulant un effet d'ombre ou de détection de collision.

Le mouvement de l'émetteur de rayons est contrôlé par la souris, ce qui permet d'observer dynamiquement le comportement des rayons.

## 📸 Aperçu

Le programme ouvre une fenêtre dans laquelle :
- Un cercle jaune suit la souris.
- Un grand cercle brun reste fixe.
- Des centaines de rayons partent du petit cercle et sont bloqués lorsqu’ils touchent le grand cercle.
- Le fond est bleu.

## 🗂 Structure

.
├── main.c # Code principal du programme SDL
├── Makefile # Script pour compiler le projet
└── README.md # Documentation (vous y êtes)


## ⚙️ Compilation

Assurez-vous d’avoir la bibliothèque **SDL2** installée sur votre système.

### Sous Linux

Installer SDL2 :
```bash
sudo apt install libsdl2-dev

Compiler :

make

Sous macOS (via Homebrew)

brew install sdl2
make

▶️ Exécution

Lancez le programme :

./main

🖱️ Contrôles

    Déplacer la souris (clic maintenu) : le cercle jaune suit la souris, et les rayons sont mis à jour en temps réel.

    Fermer la fenêtre : quitte le programme proprement.

🎯 Objectifs pédagogiques

    Comprendre les bases du raytracing en 2D

    Utilisation de la SDL2 pour le rendu graphique

    Détection de collision basique entre rayons et cercles

    Animation interactive via la souris

📦 Dépendances

    SDL2

    Compilateur C (gcc ou clang)

    math.h pour la trigonométrie

🧽 Nettoyage

make clean
