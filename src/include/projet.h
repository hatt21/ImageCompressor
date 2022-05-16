#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NB_PIX_X 512
#define NB_PIX_Y 512
#define NB_MAX_FEUILLE 262144
#define epsilon 0.000001 

typedef struct noeud{
	int pixel[4]; // contiendra la pixel moyen du noeud 
	int hauteur; // contiendra la hauteur du noeud
	struct noeud *no; //les 4 fils du noeud
	struct noeud *ne;
	struct noeud *se;
	struct noeud *so;
	int x1,y1,x2,y2; // contient les coordonnées du noeud
	double erreur; // contiendra l'erreur du noeud
}Noeud, *Arbre;

//Approximation

int nb_noeud(Arbre pixels);

double distance(int *pixel1, int *pixel2);

void moyenne(int d, int x1, int y1, int x2, int y2, MLV_Image* image, int *pixel);

double erreur(int x1, int y1, int x2, int y2, int *moyenne, MLV_Image* image);

Arbre alloueNoeud(int x1, int y1, int x2, int y2,int hauteur,MLV_Image* image);

Arbre ExtraitMax(Arbre pixels,Arbre *max);

int comparedouble(double i,double j);

Arbre AjouteMax(Arbre *pixels,Arbre max,MLV_Image *image,int *i);

Arbre AjouteMaxCercle(Arbre *pixels,Arbre max,MLV_Image *image, int *i);

Arbre cercle(MLV_Image* image);

Arbre subdivision(MLV_Image* image);

//Minimisation

Arbre TrouveFeuille(Arbre tmp,Arbre *feuille,int *j);

Arbre TrouveNoeud(Arbre tmp,Arbre *noeud,int *j);

Arbre minimisation(Arbre *parcours,Arbre tmp);

// Affichage

void AfficheImage();

void AffichePixels(Arbre pixels);

void AfficheCerclePixels(Arbre pixels);

void AfficheMenu();

//Sauvegarde

int indice(Arbre tab[], Arbre a,int max);

void sauvegardeMinNB(Arbre pixels,FILE *fichier);

void sauvegardeMinRGBA(Arbre pixels,FILE *fichier);

int sauvegardeRGBA(Arbre pixels,FILE *fichier);

int sauvegardeNB(Arbre pixels,FILE *fichier);
