# Minitalk

## Présentation du projet
Minitalk est un projet de communication entre processus qui met en œuvre un système client-serveur en utilisant des signaux UNIX pour transmettre des messages.
Le serveur écoute et reçoit des messages envoyés par le client, puis les affiche rapidement.
Ce projet est une opportunité d'explorer la gestion des signaux, la communication interprocessus, et les subtilités des processus sous UNIX.

## Objectifs pédagogiques
Le projet Minitalk a pour objectifs de :

Maîtriser la gestion des signaux sous UNIX (SIGUSR1 et SIGUSR2).
Comprendre et implémenter la communication interprocessus via un modèle client-serveur.
Renforcer les compétences en programmation C, notamment la gestion des processus et la synchronisation.
Assurer une transmission rapide et efficace des données entre le client et le serveur.

## Fonctionnement du programme
### Serveur
Le serveur doit être lancé en premier. Il affiche alors son PID (Process ID), ce qui permet aux clients de le contacter.
Le serveur est capable de recevoir et d'afficher des messages de plusieurs clients successifs sans avoir besoin d'être relancé.
### Client
Le client prend deux paramètres : le PID du serveur et une chaîne de caractères à transmettre.
Le client envoie la chaîne de caractères au serveur en utilisant uniquement les signaux SIGUSR1 et SIGUSR2.

## Utilisation

![minitalkDemo](https://github.com/user-attachments/assets/6e8aaa9a-f9f4-4e3e-9a3a-18cf6e219d81)

