#include "include/projet.h"

void AfficheImage(MLV_Image* image){ 

	/*fonction qui prend en argument une image et qui l'affiche à la coordonnée 0,0*/

	MLV_draw_image(image,0,0);
}

void AffichePixels(Arbre pixels){

	/*fonction qui prend en argument un arbre, essentiellement un noeud ou une feuille et qui affiche
	la moyenne des pixels du noeud ou de la feuille en fonction de sa taille calculée avec ses coordonnées
	x1,y1,xé,y2*/

	int i,j; //variable pour les boucles for
	unsigned int couleur=MLV_convert_rgba_to_color(pixels->pixel[0],pixels->pixel[1],pixels->pixel[2],pixels->pixel[3]); //convertit (r,g,b,a) en une MLV_Ccolor
	for (i=pixels->x1; i<pixels->x2; i++){ // parcours la longueur du noeud ou de la feuille
		for (j=pixels->y1; j<pixels->y2; j++){ // parcours la largeur du noeud ou de la feuille
			MLV_draw_pixel(i,j,couleur);
		}
	}

}

void AfficheCerclePixels(Arbre pixels){

	/* fonction identique à AffichePixels() mais qui affiche des cercles au lieu de pixels, de la taille 
	du noeud demandé*/

	unsigned int couleur=MLV_convert_rgba_to_color(pixels->pixel[0],pixels->pixel[1],pixels->pixel[2],pixels->pixel[3]); //convertit (r,g,b,a) en une MLV_Ccolor
	MLV_draw_filled_circle(pixels->x1+((pixels->x2-pixels->x1)/2),pixels->y1+((pixels->y2-pixels->y1)/2),(pixels->x2-pixels->x1)/2,couleur);
}

void AfficheMenu(){

	/* fonction qui affiche un menu dans la barre de gauche de la fenêtre avec des boutons*/

	MLV_draw_text_box(NB_PIX_X+50,6,200,40,"Subdivision",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(NB_PIX_X+50,71,200,40,"Sauvegarde N&B",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);	
	MLV_draw_text_box(NB_PIX_X+50,136,200,40,"Sauvegarde RGBA",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);	
	MLV_draw_text_box(NB_PIX_X+50,201,200,40,"Minimisation",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);	
	MLV_draw_text_box(NB_PIX_X+50,266,200,40,"Sauvegarde Min N&B",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);	
	MLV_draw_text_box(NB_PIX_X+50,331,200,40,"Sauvegarde Min RGBA",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);	
	MLV_draw_text_box(NB_PIX_X+50,396,200,40,"Ouvrir image",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(NB_PIX_X+50,461,200,40,"Subdivision Cercles",10,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
}
