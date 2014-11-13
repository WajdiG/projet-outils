/**
 * \file	fonction.c
 * \brief	projet de Black Jack
 * \author	 GUEDOUAR Wajdi
 * \author	 THIEULART Godefroy  
 * \author   OKROU PODA
 * \version	0.1
 * \date	22 Octobre 2014
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIBRE			0	/**< constante indiquant que la carte est libre */
#define BANQUE			1	/**< constante indiquant que la carte est dans la main de la banque */
#define JOUEUR			2	/**< constante indiquant que la carte est dans la main du joueur */
#define BANQUE_CACHEE	3	/**< constante indiquant que la carte est dans la main de la banque mais cachée*/

#define DEB_COEURS		0	/**< constante indiquant le début des cartes de type coeurs */
#define	FIN_COEURS		12	/**< constante indiquant la fin des cartes de type coeurs */
#define	DEB_CARREAUX	13	/**< constante indiquant le début des cartes de type carreaux */
#define FIN_CARREAUX	25	/**< constante indiquant le fin des cartes de type carreaux */
#define	DEB_PIQUES		26	/**< constante indiquant le début des cartes de type piques */
#define FIN_PIQUES		38	/**< constante indiquant le fin des cartes de type piques */
#define	DEB_TREFLES		39	/**< constante indiquant le début des cartes de type trefles */
#define	FIN_TREFLES		51	/**< constante indiquant le fin des cartes de type trefles */

short cartes[52];	/**< tableau contenant les 52 cartes du jeu */
short nb_as_joueur;	/**< variable globale contenant le nombre d'as du joueur */
short nb_as_banque;	/**< variable globale contenant le nombre d'as de la banque */


/**
*\fn short tirer_carte(short)
*\brief permet de tirer une carte parmis 52
*\param joueur celui qui tire la carte
*\return short renvoie à la carte tirée
*/
short tirer_carte(short joueur){
	srand(time(NULL));
	
	short carte = rand()%(52-1)+1;
	
	while(cartes[carte] != 0||(carte%13)==1){
		carte = rand()%(52-1)+1;
	}
	cartes[carte]=joueur;
	return carte;
}

/**
 *\fn void afficher_carte(short)
*\brief permet d'afficher la carte : son chiffre et sa couleur
*\param num parametre représetant la carte tirer dans la fonction tirer_carte
*/
void afficher_carte(short num){
	short chif=(num%13);
	
	if(num<=FIN_COEURS){
		switch(chif){
			case 0 : printf("as de coeur \n"); break;
			case 10 : printf("valet de coeur\n"); break;
			case 11 : printf("dame de coeur\n"); break;
			case 12 : printf("roi de coeur\n"); break;
			default : printf("%i de coeur \n",chif); 
		}
	}
	else if(num>=DEB_CARREAUX&&num<=FIN_CARREAUX){
		switch(chif){
			case 0 : printf("as de carreaux \n"); break;	
			case 10 : printf("valet de carreaux\n"); break;
			case 11 : printf("dame de carreaux\n"); break;
			case 12 : printf("roi de carreaux\n"); break;		
			default : printf("%i de carreaux \n",chif); 
		}
	}
	else if(num>=DEB_PIQUES&&num<=FIN_PIQUES){
		switch(chif){
		case 0 : printf("as de piques \n"); break;
		case 10 : printf("valet de piques\n"); break;
		case 11 : printf("dame de piques\n"); break;
		case 12 : printf("roi de piques\n"); break;
		default : printf("%i de piques \n",chif);
		}
	}
	else{
		switch(chif){
			case 0 : printf("as de trèffle \n"); break;
			case 10 : printf("valet de trèffle\n");	break;
			case 11 : printf("dame de trèffle\n"); break;
			case 12 : printf("roi de trèffle\n"); break;
			default : printf("%i de trèffle \n",chif);}
		}
	}

/**
*\fn void afficher_mains(short joueur)
*\brief fonction permettant d'afficher la main du joueur entrée en paramètre
*\param joueur parametre représentant le joueur concerné
*/
void afficher_mains(short joueur){
	int cpt=0;

	for(cpt=0 ; cpt<52 ; cpt++){
		if(cartes[cpt]==joueur){
				afficher_carte(cpt);
		}
	}
}

/**
*\fn void afficher_mains_cachee
*\brief fonction permettant d'affiché la main de la banque, carte cachée incluse
*/
void afficher_mains_cachee(){
	int cpt=0;

	for(cpt=0 ; cpt<52 ; cpt++){
		if(cartes[cpt]==BANQUE_CACHEE){
				afficher_carte(cpt);
		}
	}
}

/**
*\fn short donner_valeur_carte(short, short)
*\brief donne la valeur de la carte de 0 à 12
*\param joueur parametre représentant le joueur concerné
*\param carte parametre représentant la carte tirée par le joueur placé en paramètre
*\return  short indique la valeur de la carte attribuée au joueur 
*/
short donner_valeur_carte(short joueur, short carte){
	short chif=carte%13;
	
	if(chif>9){
		chif=10;
	}	
	
	if(chif==0){
		if(joueur==BANQUE || joueur==BANQUE_CACHEE){
			nb_as_banque++;
		}
		if(joueur==JOUEUR){
			nb_as_joueur++;
		}
		return 11;
	 }
	return chif;
}

/**
*\fn short evaluer_score(short, short, short*)
*\brief fonction permettant de mettre à jour le score du joueur placer en paramètre en fonction de la carte reçue
*\param joueur parametre représentant le joueur concerné
*\param carte parametre représentant la carte tirée par le joueur placé en paramètre
*\param score point du joueur
*\return short renvoie au point de la carte tirée par le joueur 
*/
short evaluer_score(short joueur, short carte_recue, short*score){	
	int carte = carte_recue%13;
	int score2=*score;
		
	if(joueur==JOUEUR){
		if(carte==0){
			if((*score+11)>21){score2+=1;}
			else{score2+=11;}
		}
		else if(carte>9){score2+=10;}
		else{score2+=carte;}
	}
	
	else if(joueur==BANQUE||joueur==BANQUE_CACHEE){
		if(carte==0){
			if((*score+11)>21){score2+=1;}
			else{score2+=11;}
		}
		else if(carte>9){score2+=10;}
		else{score2+=carte;}
	}	
	return score2;
}
