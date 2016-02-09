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
#include <stdlib.h>             //pour malloc

#define K 5                     //K taille du tetradre
#define rouge 0
#define bleu 1
#define vert 2



/*Declaration de la structure de listes*/
typedef struct maillon_tetra{   
    int nb_bleu;
    int nb_rouge;
    int nb_vert;   
    int tetra[K][K][K];                    
    struct maillon_tetra *suivant;         //Creation pointeur sur prochain maillon
}maillon_tetra;

typedef maillon_tetra *liste;
 
 
/* Declaration des variables globales*/
int compt = 0;              //Compteur
int ligne[K];              //Ligne de back track
liste liste_tetra = NULL;




/*---------------------------------------------------------------------------*/
/* Enregistrement des tetraedre dans la liste*/
liste ajout_liste (int tetra[][K][K], liste liste_tetra,int nb_rouge, int nb_bleu, int nb_vert){
   
        int k1, l,c, i, j,k ;

        maillon_tetra* ptr;
        ptr = (maillon_tetra*)malloc(sizeof(maillon_tetra));       //Cree pointeur sur 1 maillon
        for (k1=0; k1<K; k1++){
            for (l=0; l<=k1; l++) {                      
               for(c=0; c<=k1-l; c++) {
                    ptr->tetra[l][c][k1] = tetra[l][c][k1];
                }
            }
        }  
        ptr->nb_rouge = nb_rouge;  
        ptr->nb_bleu = nb_bleu;  
        ptr->nb_vert = nb_vert;                           
        ptr->suivant = liste_tetra;        
        
        return ptr; 
}
 
 
 
 /*------------------------------------------------------------------*/


 
 
/*------------------------------------------------------------------*/ 
/* Fonction de trie*/
/*liste trie (liste liste_tetra, int nb_rouge, int nb_bleu, int nb_vert, int min_rouge){
int l, c, k1;
    liste  pre, tmp, copie;
    //tmp = liste_tetra;
    copie = NULL;
    // Choix rouge et vert
    
    
    while( liste_tetra != NULL){
        if ((nb_rouge >= liste_tetra->nb_rouge)){
    copie = ajout_liste (liste_tetra->tetra, copie, 
            liste_tetra->nb_rouge, liste_tetra->nb_bleu, liste_tetra->nb_vert);
            
    /*while (tmp != NULL){
    
        if ((min_rouge == tmp->nb_rouge)){
             pre = tmp;
             tmp = tmp->suivant;
             
        }else{
            if(tmp == liste_tetra){
                liste_tetra = tmp->suivant;
                free (tmp);
                tmp = liste_tetra;
            }else{
            pre->suivant = tmp->suivant;
            free(tmp);
            tmp = pre->suivant;
            }  
        }*/
    
    //}
    /* liste_tetra = liste_tetra->suivant;
     
    }
    }
    
    
    return(copie);
    }*/

liste trie (liste liste_tetra, int nb_rouge, int nb_bleu, int nb_vert, int* min_rouge){

    liste   copie;
    copie = NULL;
    if(liste_tetra == NULL){
        return(liste_tetra);
    }else{
    while( liste_tetra != NULL){
        if ((*min_rouge >= liste_tetra->nb_rouge)){
    copie = ajout_liste (liste_tetra->tetra, copie, 
            liste_tetra->nb_rouge, liste_tetra->nb_bleu, liste_tetra->nb_vert);
   
        }
     liste_tetra = liste_tetra->suivant;
    }
    return(copie);
    }
}

/*liste trie (liste liste_tetra, int nb_rouge, int nb_bleu, int nb_vert, int* min_rouge){

liste  pre, tmp, copie;
    tmp = liste_tetra;

    while (tmp != NULL){
    
        if ((*min_rouge >= tmp->nb_rouge)){
            printf("ON est bon: nb_rouge:%i, min:%i\n",tmp->nb_rouge, *min_rouge);  
             pre = tmp;
             tmp = tmp->suivant;
             
        }else{
            if(tmp == liste_tetra){
                liste_tetra = tmp->suivant;
                free (tmp);
                tmp = liste_tetra;
            }else{
            pre->suivant = tmp->suivant;
            free(tmp);
            tmp = pre->suivant;
            }  
            
            }
     }
            
    return(tmp);

}*/


 
 /*-------------------------------------------------------------------*/
/*Fonction back_track de base */
void back_track_base (int i, int fin_boucle, int *min_rouge){
    int j, l, m, c, tetra[K][K][K], valeur, k1;
  
    int nb_rouge, nb_vert, nb_bleu;
    int /*min_rouge,*/ max_bleu, max_vert;
    nb_rouge=0;
    nb_bleu=0;
    nb_vert=0;
    
    //min_rouge = fin_boucle;
    max_bleu = 0;
    max_vert = 0;

       
	 
    if (i == fin_boucle)
    	{  	
    	
    	//Fonction passage ligne en triangle
    	valeur = 0;
    	for(l=0; l<K; l++){     //Ligne 
    	    for(c=0; c<K-l; c++){
    	        tetra[l][c][K-1] = ligne[valeur];
    	        valeur = valeur+1;
    	    }
    	}
    	
    	
    	
    	//comptage des boules de la base
    	for (l=0; l<=K-1; l++) 
    	{                         
   			for(c=0; c<=K-1-l; c++) 
   			{
				if(tetra[l][c][K-1]==0)
				{
					nb_rouge++;
				}else if(tetra[l][c][K-1]==1)
				{
					nb_bleu++;
				}else
				{
					nb_vert++;
				}
       	 	}
   		 }
    	
    	
    	
    	
    	//Calcul des niveaux inferieurs:
    	 for(k1=K-2; k1>=0; k1--)                   //niveaux
        {
            for (l=k1; l>=0; l--)                  //lignes
            {                  
                for(c=0; c<=k1-l; c++)                //colonnes  
                {
                    //Si les 3 boules identiques-->rouge
                    if((tetra[l][c][k1+1] == tetra[l][c+1][k1+1]) 
                    && (tetra[l][c+1][k1+1] ==  tetra[l+1][c][k1+1]))
                    {
                        tetra[l][c][k1] = rouge;
                        nb_rouge++;
                    
                    //Si les 3 boules differentes -->vert    
                    }else if((tetra[l][c][k1+1] != tetra[l][c+1][k1+1]) 
                    && (tetra[l][c+1][k1+1] !=  tetra[l+1][c][k1+1])
                    && (tetra[l][c][k1+1] != tetra[l+1][c][k1+1]))
                    {
                        tetra[l][c][k1] = vert;
                        nb_vert++;
                    
                    //Si 2 boules identiques-->bleu    
                    }else{
                        tetra[l][c][k1] = bleu;
                        nb_bleu++;
                    }
                }
            }
        }
        
        // Calcule du minimum de rouge:
        if (nb_rouge <= *min_rouge ){
            *min_rouge = nb_rouge;
            
            
           liste_tetra = ajout_liste (tetra,liste_tetra,nb_rouge,nb_bleu,nb_vert);
           liste_tetra = trie (liste_tetra,nb_rouge,nb_bleu,nb_vert, min_rouge);
            
          
      }
        
        
 

    	
    	
    	//Afficher les solutions
    	/*printf("\nTetra %i",compt);
    	for(k1=K-1; k1>=0; k1--){
        	for (l=0; l<=k1; l++) {              
        	printf("\n");            
               for(c=0; c<=k1-l; c++) {
                    printf("%i ",liste_tetra->tetra[l][c][k1]);
                }
            }
            printf("\n");
        }
        printf("nb_rouge:%i, nb_vert:%i\n",liste_tetra->nb_rouge,liste_tetra->nb_vert); */
       
        compt ++;
        
        
    }else{
                ligne[i] = 0;       
				back_track_base (i+1, fin_boucle, min_rouge);
                ligne[i] = 1;        
				back_track_base (i+1, fin_boucle, min_rouge);
                ligne[i] = 2;                     
				back_track_base (i+1, fin_boucle, min_rouge);
    }
} 
 












 
 
 
 /*Main*/
 int main (void){
    int fin_boucle, h, c, l, k1, com;
    int *min_rouge;
    com = 0;
    

    
    
    //Calcul de la fin de la boucle
	    for (h=1;h<=K;h++)
	    {
		    fin_boucle = fin_boucle+h;
	    }	

    min_rouge = &fin_boucle;
    printf("MIN ROUGE %i \n", *min_rouge);
    printf("ADRESSE: MIN ROUGE%i \n", min_rouge);
    
   back_track_base(0,fin_boucle, min_rouge);     //appel de la fonction backtrack
   
   while(liste_tetra != NULL){
 
     for(k1=K-1; k1>=0; k1--){
        	for (l=0; l<=k1; l++) {              
        	printf("\n");            
               for(c=0; c<=k1-l; c++) {
                    printf("%i ",liste_tetra->tetra[l][c][k1]);
                }
            }
            printf("\n");
        }
        printf("nb_rouge:%i\n",liste_tetra->nb_rouge);
        com = com +1;
        
        
        liste_tetra = liste_tetra->suivant;
        
    }
  printf("SOLUTIONS:%i\n",com);
    
    
    printf("Il ya %i solutions \n",compt);
    
    return(0);
    
} 
 
