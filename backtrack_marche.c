/** 
* Polytech Marseille
* Case 925 -163, avenue de Luminy
* 13288 Marseille CEDEX 9
*
* Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut être 
* reproduit, utilise ou modifie sans l'avis express de ses auteurs.
*/

/**
* @author DENIS Justine <justine.denis@etu.univ-amu.fr>
*
* @version 0.0.1 / 1-02-2016
* @toto NA
* @bug NA 
*/

/**
* @file essai_1.c
* @brief
*
*  Essai sur le back track pour la base
**/ 


#include <stdio.h>
#include <assert.h>

#define K 3                     //K taille du tetradre
#define rouge 0
#define bleu 1
#define vert 2
 
 
 
/* Declaration des variables globales*/
int compt = 0;              //Compteur
int niveau[K];              //Ligne de back track
 
 




/*Calcule le nombre d'elements pour remplir un triangle de longueur
 et largeur K*/
//int suite(int n)
//{
    int a=1;
	    int h,b,temp;
	    for (h=1;h<=K;h++)
	    {
		    temp=b;
		    b=b+h;
		    a=temp;
	    }	
	
	//return(b);
//}
 
 
 
/*Fonction back_track de base */
void back_track_base (int i){
    int j, l, m, c, triangle[K][K][K], valeur, nb;
    //nb = suite(K);
        
    if (i == b)
    	{  	
    	
    	printf("Solution 1ligne\n");
    	for (l=0; l<b; l++) 
        {
            printf("%i ",niveau[l]);
        }
        printf("\n");
    	
    	//Fonction passage ligne en triangle
    	valeur = 0;
    	for(l=0; l<K; l++){     //Ligne 
    	    for(c=0; c<K-l; c++){
    	        triangle[l][c][K-1] = niveau[valeur];
    	        valeur = valeur+1;
    	    }
    	}
    	
    	//Afficher les solutions
    	for (l=0; l<K; l++) {              
    	printf("\n");            
           for(c=0; c<K-l; c++) {
                printf("%i ",triangle[l][c][K-1]);
            }
        }
        printf("\n");

        compt ++;

    }else{
                niveau[i] = 0;       
				back_track_base (i+1);
                niveau[i] = 1;        
				back_track_base (i+1);
                niveau[i] = 2;                     
				back_track_base (i+1);
    }
} 
 












 
 
 
 /*Main*/
 int main (void){

    back_track_base(0);     //appel de la fonction backtrack
    printf("Il ya %i solutions \n",compt);
} 
 
