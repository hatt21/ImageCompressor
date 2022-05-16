#include "include/projet.h"

int main(void){

	MLV_create_window("Approximation","Approximation", NB_PIX_X+300, NB_PIX_Y); // creation de la fenetre
	
	//affiche image
	FILE *fichier; //creation d'une variable fichier
	char *nom_fichier="images/img4.png"; // creation d'une variable nom fichier qui contiendra le chemin vers le fichier affiché initialement
	char tmp[15]; //creation d'une variable tampon
	int i=0;
	for (i;i<12;i++){
		tmp[i]=nom_fichier[i]; //on donne les 12 premieres valeurs de nom_fichier à tmp pour ensuite avoir juste a lui donner l'extension du fichier
	}
	char *banque_image[4]; // creation d'une variable contenant toutes les images du projet
	banque_image[0]="img1.png";
	banque_image[1]="img2.png";
	banque_image[2]="img3.png";
	banque_image[3]="img4.png";
	int x1,y1; // creation de 2 variable qui contiendront les coordonnées en x et y du clic
	int boucle=0; 
	Arbre pixels; // creation d'une variable qui contiendra l'arbre correspondanr a l'image
	
	while (boucle==0){
	
		MLV_Image* image=MLV_load_image(nom_fichier); // charge l'image 
		AfficheMenu(); //affiche le menu
		AfficheImage(image); //affiche l'image
		MLV_actualise_window();
		
		MLV_wait_mouse(&x1,&y1); //attend un clic 
		
		if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>461 && y1<501)){// si l'on clique dans "subdivision cercle"
			pixels=cercle(image); // on appel la fonction cercle
			MLV_wait_mouse(&x1,&y1); //on attend un clic après
			
			if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>71 && y1<111)){ // si l'on clique sur "sauvegarde NB"
				tmp[12]='q'; // on donne a tmp l'extension "qtn"
				tmp[13]='t';
				tmp[14]='n';
				fichier=fopen(tmp,"w"); // on ouvre le fichier du nom de tmp
				sauvegardeNB(pixels,fichier); // on lance la sauvegarde
				fclose(fichier); // on ferme le fichier
			}
			if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>136 && y1<176)){ // si l'on clique sur "sauvegarder RGBA"
				tmp[12]='q'; // on donne a tmp l'extension "qtc"
				tmp[13]='t';
				tmp[14]='c';
				fichier=fopen(tmp,"w"); // on ouvre le fichier du nom de tmp
				sauvegardeRGBA(pixels,fichier); // on lance la sauvegarde
				fclose(fichier); // on ferme le fichier
			}
			
			if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>201 && y1<241)){ // si l'on clique dans "minimisation"
				Arbre parcours=pixels; //on cree un arbre parcours auquel on donnera l'arbre pixels
				minimisation(&parcours,pixels); //on lance la minimisation
				MLV_wait_mouse(&x1,&y1); //on attend un clic
				
				if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>266 && y1<306)){ // si l'on clique sur "sauvegarde Min NB"
					tmp[12]='g'; // on donne a tmp l'extension "gmn"
					tmp[13]='m';
					tmp[14]='n';
					fichier=fopen(tmp,"w"); // on ouvre le fichier du nom de tmp
					sauvegardeMinNB(pixels,fichier); // on lance la sauvegarde
					fclose(fichier); // on ferme le fichier
				}
				
				if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>331 && y1<371)){ // si l'on clique sur "sauvegarde Min RGBA"
					tmp[12]='g'; // on donne a tmp l'extension "gmc"
					tmp[13]='m';
					tmp[14]='c';
					fichier=fopen(tmp,"w"); // on ouvre le fichier du nom de tmp
					sauvegardeMinRGBA(pixels,fichier); // on lance la sauvegarde
					fclose(fichier); // on ferme le fichier
				}
			}
		}
		if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>6 && y1<46)){ // si l'on clique dans "subdivision"
			pixels=subdivision(image); //on lance la subdivisioj
			MLV_wait_mouse(&x1,&y1); // on attend un clic
			
			if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>71 && y1<111)){ // si l'on clique sur "sauvegarde NB"
				tmp[12]='q'; // on donne a tmp l'extension "qtn"
				tmp[13]='t';
				tmp[14]='n';
				fichier=fopen(tmp,"w"); // on ouvre le fichier du nom de tmp
				sauvegardeNB(pixels,fichier); // on lance la sauvegarde
				fclose(fichier); // on ferme le fichier
			}
			if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>136 && y1<176)){ // si l'on clique sur "sauvegarder RGBA"
				tmp[12]='q'; // on donne a tmp l'extension "qtc"
				tmp[13]='t';
				tmp[14]='c';
				fichier=fopen(tmp,"w"); // on ouvre le fichier du nom de tmp
				sauvegardeRGBA(pixels,fichier); // on lance la sauvegarde
				fclose(fichier); // on ferme le fichier
			}
			
			if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>201 && y1<241)){ // si l'on clique dans "minimisation"
				Arbre parcours=pixels; //on cree un arbre parcours auquel on donnera l'arbre pixels
				minimisation(&parcours,pixels); //on lance la minimisation
				MLV_wait_mouse(&x1,&y1); //on attend un clic
				
				if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>266 && y1<306)){
					tmp[12]='g'; // on donne a tmp l'extension "gmn"
					tmp[13]='m';
					tmp[14]='n';
					fichier=fopen(tmp,"w"); // on ouvre le fichier du nom de tmp
					sauvegardeMinNB(pixels,fichier); // on lance la sauvegarde
					fclose(fichier); // on ferme le fichier
				}
				
				if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>331 && y1<371)){
					tmp[12]='g'; // on donne a tmp l'extension "gmc"
					tmp[13]='m';
					tmp[14]='c';
					fichier=fopen(tmp,"w"); // on ouvre le fichier du nom de tmp
					sauvegardeMinRGBA(pixels,fichier); // on lance la sauvegarde
					fclose(fichier);// on ferme le fichier
				}
			}
		}
		if ((x1>=NB_PIX_X+50 && x1<NB_PIX_X+250) && (y1>396 && y1<436)){ // si on clique dans "ouvrir image"
			//une boite de message s'affiche et invite a saisir le nom de l'image, ex:"img4.png"
			char *tmp2;	MLV_wait_input_box(100,150,400,160,MLV_COLOR_RED,MLV_COLOR_RED,MLV_COLOR_BLACK,"   SAISISSEZ UN NOM DE FICHIER:     ",&tmp2);
			int i=0;
			for (i;i<4;i++){
				if (strcmp(banque_image[i],tmp2)==0){ //on parcourt la banque d'image pour trouver celle correspondante
					tmp[7]=tmp2[0]; // et on donne a tmp le nom de l'image
					tmp[8]=tmp2[1];
					tmp[9]=tmp2[2];
					tmp[10]=tmp2[3];
					tmp[12]=tmp2[5];
					tmp[13]=tmp2[6];
					tmp[14]=tmp2[7];
					nom_fichier=tmp;
				}
			}
			continue;
		}
	}
}
