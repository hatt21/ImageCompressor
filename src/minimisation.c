#include "include/projet.h"


Arbre TrouveNoeud(Arbre tmp,Arbre *noeud,int *j){

	/* fonction récursive qui prend en argument un arbre tmp qui est l'arbre a parcourir pour trouver le noeud, 
	un arbre noeud qui est un pointeur qui est le noeud a trouver et qui sera modifié dès que l'on trouvera
	une valeur correspondante dans tmp, un entier j qui est également un pointeur, initié à 0 qui prendra la 
	valeur de 1 dès que noeud aura été modifié, au cas ou l'abre contient + de 2 noeuds identiques*/

	if (tmp->no==NULL){ //si tmp->no==NULL, alors tous les autres fils de tmp sont nuls puisqu'on alloue tout le temps 4 fils a la fois
		return NULL; // on return NULL car on est arrivé au bout d'une branche de l'arbre, il faudra donc remonter dans l'arbre récursivement
	}
	else if (*j==0){ // si noeud n'a pas déjà été modifié on vérifie que tmp et noeud soit égaux en comparant leur coord et on modifie noeud et j
		if (tmp->pixel[0]==(*noeud)->pixel[0] && tmp->pixel[1]==(*noeud)->pixel[1] && tmp->pixel[2]==(*noeud)->pixel[2] && tmp->pixel[3]==(*noeud)->pixel[3] && tmp->hauteur==(*noeud)->hauteur){
			*noeud=tmp;
			*j=1;
		}
	}
	TrouveNoeud(tmp->no,&(*noeud),&(*j)); 
	TrouveNoeud(tmp->ne,&(*noeud),&(*j));
	TrouveNoeud(tmp->se,&(*noeud),&(*j));
	TrouveNoeud(tmp->so,&(*noeud),&(*j));
	return NULL;
}

Arbre TrouveFeuille(Arbre tmp,Arbre *feuille,int *j){

	/* identique a TrouveNoeud mais avec des feuille donc la condition pour verifier que tmp et feuille 
	sont égaux se fait quand tmp->no=NULL soit quand on rencontre une feuille*/
	
	if (tmp->no==NULL){
		if (*j==0){
			if (tmp->pixel[0]==(*feuille)->pixel[0] && tmp->pixel[1]==(*feuille)->pixel[1] && tmp->pixel[2]==(*feuille)->pixel[2] && tmp->pixel[3]==(*feuille)->pixel[3]){
				*feuille=tmp;
				*j=1;
			}
		}
		return NULL;
	}
	TrouveFeuille(tmp->no,&(*feuille),&(*j));
	TrouveFeuille(tmp->ne,&(*feuille),&(*j));
	TrouveFeuille(tmp->se,&(*feuille),&(*j));
	TrouveFeuille(tmp->so,&(*feuille),&(*j));
	return NULL;
}

Arbre minimisation(Arbre *parcours,Arbre tmp){

	/* fonction qui recoit 2 arbres en arguments,un qui servira a parcourir, un identique au premier
	qui servira de tampon pour les fonctions TrouveFeuille et TrouveNoeud*/

	if ((*parcours)->no==NULL){ //on rencontre une feuille
		int j=0; //variable qui servira a savoir si l'on a deja changer la variable feuille dans TrouveFeuille
		Arbre feuille=*parcours; //initialisation de la variable feuille avec la feuille actuelle parcours
		TrouveFeuille(tmp,&feuille,&j);
		*parcours=feuille; //remplacement de la feuille actuelle parcours par la feuille trouvee dans TrouveFeuille
		return NULL;
	}
	else{ //on rencontre un noeud
		int j=0; //variable qui servira a savoir si l'on a deja changer la variable noeud dans TrouveNoeud
		Arbre noeud=*parcours; //initialisation de la variable noeud avec le noeud actuel parcours
		TrouveNoeud(tmp,&noeud,&j);
		*parcours=noeud; //remplacement du noeud actuel parcours par le noeud trouvee dans TrouveNoeud
	}
	minimisation(&(*parcours)->no,tmp);
	minimisation(&(*parcours)->ne,tmp);
	minimisation(&(*parcours)->se,tmp);
	minimisation(&(*parcours)->so,tmp);
	return NULL;
}



