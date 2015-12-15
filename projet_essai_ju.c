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
#define K 4


/*      Retourne la couleur à poser */
int quelle_couleur (T[i][j][k]){

}


//C'EST LE BACK TRACK SANS CONDITIONS
//PB: affiche des zeros alors qu'on a pas de zero!! (peut-etre mettre rouge = 0 ==> solutions?)
/* Fonction base back_track*/
int niveau [K][K][K];

/* Fonction base back_track*/
void back_track_base (int i){            //appel 1er back_track ligne = 0
    int j;
    if (i == K){                        //Si la ligne = nb lignes
       for (i=0; i<K; i++) {              //Afficher les solutions
        printf("\n");
           for(j=K-i; j>0; j--) {
            printf("%i ",niveau[i][j][K]);
            }
        }
        printf("\n");

    }else{                          //Sinon pour chaque colonnes
        for (j=K-i; j>0; j--){
            niveau[i][j][K] = 1;        //SI ROUGE = 0 ==> MARCHE
            back_track_base (i+1);
            niveau[i][j][K] = 2;        //DONC BLEU = 1
            back_track_base (i+1);
            niveau[i][j][K] = 3;        //ET VERT = 2

        }
        
    }
    
}






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
    
    
    
    //Affichage des niveaux (en forme de tableau n*n):
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
    
    
    //Affichage des niveaux en triangle en fonction des niveau:
    for(k1=0; k1<K; k1++){
        printf("\n Niveaux %i:\n",k1);
       for (i=k1; i<K; i++) {
        printf("\n");
           for(j=K-i; j>0; j--) {
            printf("%i ",niveau[i][j][k1]);
            }
        }
        printf("\n");
    }
    
        
    //Creation du tetraedre:
    for(k1=k; k1>0; k--){
        if(k1 == k){                //Si le niveau est la base
        //Faire un back track sans condition impossible
        
        }else{                      //le niveau est fait en fonction de la base
        
        }
    
    }
    
    
    //Appel back track pour la base:
    back_track_base(0);
    
    
    
    
    
    /* BONUS:
     BACK TRACK des DAMES qui marche SANS CONDITIONS: (la condition c'est l'appel de mla fonction possible)


#define N 4

int TAB[N][N];
int compt = 0;



void aff_sol (void){
int i, j;
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++){
            printf("%i ",TAB[i][j]);
        }
        printf("\n");
      } 
      printf("\n");
}


int possible (int l, int c){
    int d;   
    int ok = 1;
    for(d=1; d<=l && ok; d++){              //Tant que c'est ok
        ok = !TAB[l-d][c] 
        && ((c-d) < 0 || !TAB[l-d][c-d]) 
        && ((c+d) >= N || !TAB[l-d][c+d]);        
    }
     return ok;
}


void back_track (int l){            //l = lignes
    int  c;                //n = nb lignes (taille echiquier)                    
    if(l == N){  //imprimer solutions (toutes)                     
      aff_sol();
      compt++ ;
    }else{                    //c = colonnes
        for(c=0; c<N; c++){
            //if(possible(l,c)){      //POUR ENLEVER LES CONDITIONS--> enleve la fonction
                TAB[l][c] = 1;
                back_track(l+1);
                TAB[l][c] = 0;
            //}
        }
    }
    
}


*/
    
    
    
    
    
    
    
    
    
    
    
}
