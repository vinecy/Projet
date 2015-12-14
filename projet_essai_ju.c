// Essai BACK TRACK pour la base

// Couleurs boules:
// Rouge: 1
// Bleu: 2
// Vert: 3

// Ligne: i
// colonne: j
// Niveau: k
// niveau[i][j][k]
// La base est le niveau k et le dernier niveau (1 boule) est le niveau 0


//Condditions couleurs:
//Rouge que sur 3 rouges
//Bleu que sur 2 couleurs  differentes
//Vert que sur 3 couleurs differentes




/*-------------------------------------------------------------------------------------------------------------------*/
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
* @version 0.0.1 / 14-12-2015
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

int main (void){
// Donnees
    int i, j, k, k1;
    int niveau[k][k][k];            //Initialisation tableau
    int rouge, bleu ,vert;          
    rouge = 1;
    bleu = 2;
    vert = 3;
    k = 4;
    
    
//Code:
    //Initialisation des tableaux a 0:
    for(k1=0; k1<k; k1++){
       for (i=0; i<k; i++) {
           for(j=0; j<k; j++){
            niveau[i][j][k1] = 0;
            }
        }
    }
    
    
    
    //Affichage des niveaux:
    for(k1=0; k1<k; k1++){
        printf("\n Niveaux %i:\n",k1);
       for (i=0; i<k; i++) {
        printf("\n");
           for(j=0; j<k; j++) {
            printf("%i ",niveau[i][j][k1]);
            }
        }
        printf("\n");
    }
    
    //Creation de la base:
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
