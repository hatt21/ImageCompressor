#include "include/projet.h"

int nb_noeud(Arbre pixels){  

	/* fonction qui prend en argument un arbre et qui renvoie son nombre de noeuds + son nombre de feuille*/

	int nb; //variable qui servira de stockage pour le nombre
	if (pixels->no==NULL){ //on rencontre une feuille et on ajoute 1
		return 1;
	}
	nb=nb_noeud(pixels->no)+nb_noeud(pixels->ne)+nb_noeud(pixels->se)+nb_noeud(pixels->so);
	return nb+1; // on remonte dans un noeud, on ajoute 1
}
double distance(int *pixel1, int *pixel2){

	/* fonction qui prend en argument 2 pixels et qui va calculer la distance avec une formule mathématique
	en utilisant les (r,g,b,a) et qui retourne la distance entre ces 2 pixels*/

	double x=(pow(pixel1[0]-pixel2[0],2)+pow(pixel1[1]-pixel2[1],2)+pow(pixel1[2]-pixel2[2],2)+pow(pixel1[3]-pixel2[3],2));
	double y=sqrt(x); 
	return y;
}

void moyenne(int d, int x1, int y1, int x2, int y2, MLV_Image* image, int *pixel){

	/* fonction qui prend en argument un nombre de pixels d, 4 coordonnées, une image et un pointeur vers 
	un pixels moyen*/

	int R=0; //initialisation de toutes les variables R,G,B,A a 0 qui contiendront les sommes de tous les R,G,B,A de tous les pixels
	int G=0;
	int B=0;
	int A=0;
	int i,j; 
	int r,g,b,a; //variables qui contiendront les valeurs récupérées avec MLV_get_pixel_on_image
	for (i=x1; i<x2; i++){
		for (j=y1; j<y2; j++){
			MLV_get_pixel_on_image(image,i,j,&r,&g,&b,&a);
			R+=r; // on ajoute a chaque variable la valeur récupérée dans MLV_get_pixel_on_image
			G+=g;
			B+=b;
			A+=a;
		}
	}
	pixel[0]=R/d; // on attribue a chaque case du tableau la moyenne des pixels qu'on obtiendra en divisant la somme des valeurs des pixels par le nombre de pixels
	pixel[1]=G/d;
	pixel[2]=B/d;
	pixel[3]=A/d;
}

double erreur(int x1, int y1, int x2, int y2, int *moyenne, MLV_Image* image){

	/* fonction qui prend en argument 4 coordonnées, un tableau moyenne qui contien une moyenne de pixels 
	et une image et qui renvoie l'erreur de la zone*/

	int i,j,r,g,b,a;;
	double erreur=0; //initialisation de l'erreur a 0
	int pixel_reel[4]; //initialisation d'un tableau de taille 4 contenant les (r,g,b,a) de la zone
	for (i=x1; i<x2; i++){ 
		for (j=y1; j<y2; j++){
			MLV_get_pixel_on_image(image,i,j,&r,&g,&b,&a); 
			pixel_reel[0]=r; //on donne au tableau les valeurs recuperees dans MLV_get_pixel_on_image
			pixel_reel[1]=g;
			pixel_reel[2]=b;
			pixel_reel[3]=a;
			erreur+=distance(pixel_reel,moyenne); //on calcule la distance entre pixel_reel et moyenne et on ajoute a erreur
		}
	}
	return erreur;
}

Arbre alloueNoeud(int x1, int y1, int x2, int y2,int hauteur,MLV_Image* image){

	/*fonction basique qui prend en argument des coordonnées,une hauteur et une image etqui alloue des valeurs par 
	défaut a un noeud et le renvoie*/

	Arbre tmp=(Noeud *) malloc(sizeof(Noeud));
	if (tmp==NULL){
		return NULL;
	}
	tmp->hauteur=hauteur;
	
	tmp->no=NULL;
	tmp->ne=NULL;
	tmp->se=NULL;
	tmp->so=NULL;
	
	tmp->x1=x1;
	tmp->x2=x2;
	tmp->y1=y1;
	tmp->y2=y2;
	int d=(x2-x1)*(x2-x1); //calcul du nombre de pixels dans la zone correspondant aux coordonnées
	moyenne(d,x1,y1,x2,y2,image,tmp->pixel);
	tmp->erreur=erreur(x1,y1,x2,y2,tmp->pixel,image);
	return tmp;
}

Arbre ExtraitMax(Arbre pixels,Arbre *max){

	/*fonction qui recoit en argument 2 arbres, un qui servira de parcours, et l'autre qui est un pointeur
	vers la variable qui va contenir le maximum (calculé avec l'erreur) de l'arbre à parcourir*/

	if (pixels->no==NULL){ //on rencontre une feuille
		if(pixels->erreur>(*max)->erreur){ //si cette feuille a une erreur supérieure a celle de max, on la remplace
			(*max)=pixels;
		}
		return NULL;
	}
	ExtraitMax(pixels->no,&(*max));
	ExtraitMax(pixels->ne,&(*max));
	ExtraitMax(pixels->se,&(*max));
	ExtraitMax(pixels->so,&(*max));
	return *max;
}

int comparedouble(double i,double j){

	/*fonction qui prend 2 double en argument et qui renvoie 1 s'ils sont égaux avec un taux de diff de
	0.000001, et qui renvoie 0 sinon*/

	double diff=i-j;
	if ((diff<epsilon) && (-diff<epsilon)){
		return 1;
	}
	else{
		return 0;
	}
}

Arbre AjouteMax(Arbre *pixels,Arbre max,MLV_Image *image, int *i){

	/*fonction qui prend en argument2 arbres, un que l'on va parcourir et modifier, un qui contient le maximum
	recuperee dans extraitmax, une image et une variable i qui vaut 0 ou 1*/

	if ((*pixels)->no==NULL){ // on rencontre une feuille
		if(comparedouble((*pixels)->erreur,max->erreur)==1 && *i==0){ //si le pixel est égal au max on rentre
			*pixels=max; //on remplaceles variables et on alloue ses 4 fils
			(*pixels)->no=alloueNoeud((*pixels)->x1,(*pixels)->y1,((*pixels)->x1+((*pixels)->x2-(*pixels)->x1)/2),((*pixels)->y1+((*pixels)->y2-(*pixels)->y1)/2),(*pixels)->hauteur+1,image);
			(*pixels)->ne=alloueNoeud(((*pixels)->x1+((*pixels)->x2-(*pixels)->x1)/2),(*pixels)->y1,(*pixels)->x2,((*pixels)->y1+((*pixels)->y2-(*pixels)->y1)/2),(*pixels)->hauteur+1,image);
			(*pixels)->se=alloueNoeud(((*pixels)->x1+((*pixels)->x2-(*pixels)->x1)/2),((*pixels)->y1+((*pixels)->y2-(*pixels)->y1)/2),(*pixels)->x2,(*pixels)->y2,(*pixels)->hauteur+1,image);
			(*pixels)->so=alloueNoeud((*pixels)->x1,((*pixels)->y1+((*pixels)->y2-(*pixels)->y1)/2),((*pixels)->x1+((*pixels)->x2-(*pixels)->x1)/2),(*pixels)->y2,(*pixels)->hauteur+1,image);
			AffichePixels((*pixels)->no); //on affiche les 4 fils graphiquement
			AffichePixels((*pixels)->ne);
			AffichePixels((*pixels)->se);
			AffichePixels((*pixels)->so);
			(*pixels)->erreur=-100.0000; //on donne -100.0000 a la variable erreur pour pas que ExtraitMax qui prend en compte les erreurs reprenne cette feuille
			*i=1; // on met i==1 pour pas que l'on ajoute deux fois max
		}
		return NULL;
	}
	AjouteMax(&(*pixels)->no,max,image,i);
	AjouteMax(&(*pixels)->ne,max,image,i);
	AjouteMax(&(*pixels)->se,max,image,i);
	AjouteMax(&(*pixels)->so,max,image,i);
	return *pixels;
}

Arbre AjouteMaxCercle(Arbre *pixels,Arbre max,MLV_Image *image, int *i){

	/*fonction identique a ajoutemax mais qui dessinera avec MLV_draw_filled_rectangle un rectagle noir 
	pour effacer le cercle précédent*/

	if ((*pixels)->no==NULL){
		if(comparedouble((*pixels)->erreur,max->erreur)==1 && *i==0){
			*pixels=max;
			(*pixels)->no=alloueNoeud((*pixels)->x1,(*pixels)->y1,((*pixels)->x1+((*pixels)->x2-(*pixels)->x1)/2),((*pixels)->y1+((*pixels)->y2-(*pixels)->y1)/2),(*pixels)->hauteur+1,image);
			(*pixels)->ne=alloueNoeud(((*pixels)->x1+((*pixels)->x2-(*pixels)->x1)/2),(*pixels)->y1,(*pixels)->x2,((*pixels)->y1+((*pixels)->y2-(*pixels)->y1)/2),(*pixels)->hauteur+1,image);
			(*pixels)->se=alloueNoeud(((*pixels)->x1+((*pixels)->x2-(*pixels)->x1)/2),((*pixels)->y1+((*pixels)->y2-(*pixels)->y1)/2),(*pixels)->x2,(*pixels)->y2,(*pixels)->hauteur+1,image);
			(*pixels)->so=alloueNoeud((*pixels)->x1,((*pixels)->y1+((*pixels)->y2-(*pixels)->y1)/2),((*pixels)->x1+((*pixels)->x2-(*pixels)->x1)/2),(*pixels)->y2,(*pixels)->hauteur+1,image);
			MLV_draw_filled_rectangle((*pixels)->x1,(*pixels)->y1,(*pixels)->x2-(*pixels)->x1,(*pixels)->y2-(*pixels)->y1,MLV_COLOR_BLACK);
			AfficheCerclePixels((*pixels)->no);
			AfficheCerclePixels((*pixels)->ne);
			AfficheCerclePixels((*pixels)->se);
			AfficheCerclePixels((*pixels)->so);
			(*pixels)->erreur=-100.0000;
			*i=1;
		}
		return NULL;
	}
	AjouteMaxCercle(&(*pixels)->no,max,image,i);
	AjouteMaxCercle(&(*pixels)->ne,max,image,i);
	AjouteMaxCercle(&(*pixels)->se,max,image,i);
	AjouteMaxCercle(&(*pixels)->so,max,image,i);
	return *pixels;
}

Arbre cercle(MLV_Image* image){

	/*fonction qui assure l'approximation et qui renvoie l'arbre complet correspondant à l'image*/

	//affiche moyenne pixels de l'image entiere
	Arbre pixels=alloueNoeud(0,0,NB_PIX_X,NB_PIX_Y,0,image); //on alloue le premier noeud de l'arbre
	MLV_draw_filled_rectangle(pixels->x1,pixels->y1,pixels->x2-pixels->x1,pixels->y2-pixels->y1,MLV_COLOR_BLACK); //dessine un carré noir
	AfficheCerclePixels(pixels); //appel a la fonction afficheCerckepixels pour afficher le premier noeud de l'arbre
	MLV_actualise_window();
	MLV_wait_seconds(1);
	pixels->erreur=-100.00000000; // on met son erreur a -100 pour pas que extraitmax prenne cette valeur en max tout le temps
	
	// affiche les 4 premieres feuilles de l'arbre et leur pixel moyen
	pixels->no=alloueNoeud(0,0,256,256,1,image); //on alloue les 4 fils du premier noeud
	pixels->ne=alloueNoeud(256,0,512,256,1,image);
	pixels->se=alloueNoeud(256,256,512,512,1,image);
	pixels->so=alloueNoeud(0,256,256,512,1,image);
	MLV_draw_filled_rectangle(pixels->x1,pixels->y1,pixels->x2-pixels->x1,pixels->y2-pixels->y1,MLV_COLOR_BLACK);
	AfficheCerclePixels(pixels->no); //on affiche les 4 fils
	AfficheCerclePixels(pixels->ne);
	AfficheCerclePixels(pixels->se);
	AfficheCerclePixels(pixels->so);	
	MLV_actualise_window();
	MLV_wait_seconds(1);
	AfficheMenu();
	
	int i=4; // initialisation du nombre de feuille a 4
	int j; 
	Arbre Max=pixels; //initilisation de Max avec la valeur du pixels actuel
	double erreur=Max->erreur; //initialisation de erreur avec l'erreur de max
	int temps=1000; // intialisation de temps a 1000 millisecondes pour représenter 1 seconde
	
	while (i<NB_MAX_FEUILLE){ //tant que le nombre de feuille est inferieur au nombre max de feuille 
		j=0; // initialisation de j à 0
		Arbre Max=pixels; //initilisation de Max avec la valeur du pixels actuel
		ExtraitMax(pixels,&Max); //appel a extraitmax qui va modifier Max
		if (comparedouble(Max->erreur,0.000000)==1){ // si l'erreur max vaut 0, on arrete la boucle
			break;
		}
		AjouteMaxCercle(&pixels,Max,image,&j); 
		i+=3; //on ajoute 3 au nombre de feuilles i
		MLV_actualise_window();
		MLV_wait_milliseconds(temps);
		temps=temps/1.2; // on divise le temps pour avoir une accélration d'acutalisation de la fenêtre
	}
	return pixels;
}

Arbre subdivision(MLV_Image* image){

	/*fonction identique a cerlce() avec quelques exceptions signalées en commentaires*/

	MLV_draw_text_box(NB_PIX_X+5,6,40,244,"+",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
MLV_draw_text_box(NB_PIX_X+5,262,40,244,"-",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	Arbre pixels=alloueNoeud(0,0,NB_PIX_X,NB_PIX_Y,0,image);
	AffichePixels(pixels);
	MLV_actualise_window();
	MLV_wait_seconds(1);
	pixels->erreur=-100.00000000;
	
	pixels->no=alloueNoeud(0,0,256,256,1,image);
	pixels->ne=alloueNoeud(256,0,512,256,1,image);
	pixels->se=alloueNoeud(256,256,512,512,1,image);
	pixels->so=alloueNoeud(0,256,256,512,1,image);
	AffichePixels(pixels->no);
	AffichePixels(pixels->ne);
	AffichePixels(pixels->se);
	AffichePixels(pixels->so);	
	MLV_actualise_window();
	MLV_wait_seconds(1);
	
	int i=4;
	int j,k,stop,x,y;
	Arbre Max=pixels;
	double erreur=Max->erreur;
	int taux=1; //initialisation du taux de rafraichissement à 1
	
	while (i<NB_MAX_FEUILLE){
		//initialisation de x,y,k et stop à 0
		x=0; //coord en x du clic
		y=0; // coord en y du clic
		k=0; //variable pour la boucle while
		stop=0; // variable pour arreter sortir des boucles while
		while(k<taux){
			j=0;
			Arbre Max=pixels;
			ExtraitMax(pixels,&Max);
			if (comparedouble(Max->erreur,0.000000)==1){
				stop=1; //on met stop a 1 pour sortir de la deuxieme boucle while
				break;
			}
			AjouteMax(&pixels,Max,image,&j);
			i+=3;
			k++;
		}
		MLV_actualise_window();
		MLV_wait_mouse_or_seconds(&x,&y,1); // on attend un clic ou une seconde
		if ((x>=NB_PIX_X+5 && x<NB_PIX_X+45) && (y>6 && y<250)){ // si l'utilisateur clique sur la case +
			taux++; //on augmente le taux de rafraichissement de 1
		}
		else if ((x>=NB_PIX_X+5 && x<NB_PIX_X+45) && (y>262 && y<506) && taux>1){ // si l'utilisateur clique sur -
			taux--; // on diminue le taux de rafraichissement de 1
		}
		if (stop==1){
			break;
		}
	}
	return pixels;
}



