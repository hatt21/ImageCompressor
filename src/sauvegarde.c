#include "include/projet.h"

int indice(Arbre *tab, Arbre a,int max){
	
	/*fonction qui recoit un tableau, un arbre et une valeur max et qui renvoit l'indice de l'arbre dans le
	tableau si celui-ci le contien, -1 sinon*/

	int i=0;
	Arbre b;
	for (i;i<max+1;i++){
		b=tab[i]; // on initialise b avec l'arbre contenu dans tab[i], on rappelle que tab contient des arbres
		if (a->x1==b->x1 && a->x2==b->x2 && a->y1==b->y1 && a->y2==b->y2){ //on compare l'arbre a et b
		return i;
		}
	}
	return -1;
}

void sauvegardeMinNB(Arbre pixels,FILE *fichier){

	/*fonction qui assure la sauvegarde dans un fichier de l'arbre minimisé*/

	int i=0; //variable qui servira à parcourir le tableau de 1 à 1
	int j=0; //variable qui servira à ajouter des arbre dans le tableau
	int k;
	Arbre tab[nb_noeud(pixels)]; // initialisation du tableu de taille donnée par la fonction nb_noeud
	tab[0]=pixels; //initialisation de la premiere case du tableau avec le premier noeud de l'arbre
	Arbre a=tab[0]; // initialisation de a avec la premiere valeur du tableau,soit le premier noeud de l'arbre
	while (a!=NULL){ 
		if (a->no==NULL){ // si on rencontre une feuille
			if (a->pixel[0]==255 && a->pixel[1]==255 && a->pixel[2]==255 && a->pixel[3]==255){ //si cette feuille est blanche
				fprintf(fichier,"%d 0",i); 
			}
			else{ // si cette feuille est noire
				fprintf(fichier,"%d 1",i);
			}
			i++;

		}
		else{ // si l'on rencontre un noeud
			if (a->no!=NULL){
				fprintf(fichier,"%d " ,i); // on imprime d'abord le numéro du noeud
				k=indice(tab,a->no,j); //on récupère l'indice correspondant a a->no dans tab
				if (k==-1){ // si tab ne contient pas a->no
					j++; 
					tab[j]=a->no; //on ajoute a->no a l'arbre
					fprintf(fichier,"%d ",j); //on imprime le numéro de ligne correspondant a->no
				}
				else{ // si l'arbre contient a->no
					fprintf(fichier,"%d ",k); //on imprime l'indice de a->no
				}
			}
			if (a->ne!=NULL){ 
				k=indice(tab,a->ne,j); //on récupère l'indice correspondant a a->ne dans tab
				if (k==-1){ // si tab ne contient pas a->ne
					j++;
					tab[j]=a->ne; //on ajoute a->ne a l'arbre
					fprintf(fichier,"%d ",j); //on imprime le numéro de ligne correspondant a->ne
				}
				else{ // si l'arbre contient a->ne
					fprintf(fichier,"%d ",k); //on imprime l'indice de a->ne
				}
			}
			if (a->se!=NULL){
				k=indice(tab,a->se,j); //on récupère l'indice correspondant a a->se dans tab
				if (k==-1){// si tab ne contient pas a->se
					j++;
					tab[j]=a->se; //on ajoute a->se a l'arbre
					fprintf(fichier,"%d ",j); //on imprime le numéro de ligne correspondant a->nse
				}
				else{ // si l'arbre contient a->se
					fprintf(fichier,"%d ",k); //on imprime l'indice de a->se
				}
			}
			if (a->so!=NULL){
				k=indice(tab,a->so,j); //on récupère l'indice correspondant a a->so dans tab
				if (k==-1){// si tab ne contient pas a->so
					j++; 
					tab[j]=a->so; //on ajoute a->so a l'arbre
					fprintf(fichier,"%d ",j); //on imprime le numéro de ligne correspondant a->so
				}
				else{ // si l'arbre contient a->so
					fprintf(fichier,"%d ",k); //on imprime l'indice de a->so
				}
			
			}
			i++;
		}
		fprintf(fichier,"\n");
		a=tab[i]; // on donne à a l'abre suivant du tableau
	}
}

void sauvegardeMinRGBA(Arbre pixels,FILE *fichier){

	/*fonction identique a sauvegardeMinNB a quelques exceptions signalées en commentaire*/

	int i=0;
	int j=0;
	int k;
	Arbre tab[nb_noeud(pixels)];
	tab[j]=pixels;
	Arbre a=tab[j];
	while (a!=NULL){
		if (a->no==NULL){
			fprintf(fichier,"%df %d %d %d %d",i,a->pixel[0],a->pixel[1],a->pixel[2],a->pixel[3]); //on imprime les valeurs de RGBA après le numéro de la feuille
			i++;

		}
		else{
			if (a->no!=NULL){
				fprintf(fichier,"%d " ,i);
				k=indice(tab,a->no,j);
				if (k==-1){
					j++;
					tab[j]=a->no;
					fprintf(fichier,"%d ",j);
				}
				else{
					fprintf(fichier,"%d ",k);
				}
			}
			if (a->ne!=NULL){ 
				k=indice(tab,a->ne,j);
				if (k==-1){
					j++;
					tab[j]=a->ne;
					fprintf(fichier,"%d ",j);
				}
				else{
					fprintf(fichier,"%d ",k);
				}
			}
			if (a->se!=NULL){
				k=indice(tab,a->se,j);
				if (k==-1){
					j++;
					tab[j]=a->se;
					fprintf(fichier,"%d ",j);
				}
				else{
					fprintf(fichier,"%d ",k);
				}
			}
			if (a->so!=NULL){
				k=indice(tab,a->so,j);
				if (k==-1){
					j++;
					tab[j]=a->so;
					fprintf(fichier,"%d ",j);
				}
				else{
					fprintf(fichier,"%d ",k);
				}
			
			}
			i++;
		}
		fprintf(fichier,"\n");
		a=tab[i];
	}
}

int sauvegardeRGBA(Arbre pixels,FILE *fichier){

	/*fonction identique a sauvegardeNB à une exception signalée en commentaire*/

	if (pixels->no==NULL){
		fprintf(fichier,"1(%d,%d,%d,%d)",pixels->pixel[0],pixels->pixel[1],pixels->pixel[2],pixels->pixel[3]); //on imprime les valeurs RGBA de la feuille après le 1
		return 1;
	}
	else{
		fprintf(fichier,"0");
	}
	sauvegardeRGBA(pixels->no,fichier);
	sauvegardeRGBA(pixels->ne,fichier);
	sauvegardeRGBA(pixels->se,fichier);
	sauvegardeRGBA(pixels->so,fichier);
	return 1;
}

int sauvegardeNB(Arbre pixels,FILE *fichier){

	/*fonction qui assure la sauvegarde de l'arbre dans un fichier*/

	if (pixels->no==NULL){ // on rencontre une feuille
		if (pixels->pixel[0]==255 && pixels->pixel[1]==255 && pixels->pixel[2]==255 && pixels->pixel[3]==255){ // si la feuille est blanche
			fprintf(fichier,"10"); //on imprime 1 suivi d'un 0
		}
		else{ // si la feuille est noire
			fprintf(fichier,"11"); //on imprime 1 suivi de 1
		}
		return 1;
	}
	else if (pixels->no!=NULL){ //on rencontre un noeud
		fprintf(fichier,"0"); // on imprime 0
	}
	sauvegardeNB(pixels->no,fichier);
	sauvegardeNB(pixels->ne,fichier);
	sauvegardeNB(pixels->se,fichier);
	sauvegardeNB(pixels->so,fichier);
	return 1;
}
