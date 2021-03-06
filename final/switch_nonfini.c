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
* @version 0.0.1 / 09-02-2016
* @toto NA
* @bug NA 
*/

/**
* @file projet_final.c
* @brief
*
*  Back Track avec switch
**/ 


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>                         //pour malloc

#define K 2                                      //Taille du tétraedre
#define rouge 0
#define bleu 1
#define vert 2

#define MINROUGE 1                          //Definition des choix du switch
#define MAXBLEU 2
#define MAXVERT 3
#define MINMAXVERT 4
#define MINMAXBLEU 5



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
int compt = 0;                              //Compteur
int ligne[K];                               //Ligne de back track
liste liste_tetra = NULL;
liste liste_tetra_vert = NULL;
liste liste_tetra_bleu = NULL;
liste liste_tetra_rouge = NULL;       



 
 




/*--------------------------- AJOUT_LISTE------------------------------------*/
/* @brief: Enregistre les tatraedres dans une liste avec le nombre de boules de
*  couleurs.
*/
liste ajout_liste (int tetra[][K][K], liste liste_tetra,int nb_rouge, 
int nb_bleu, int nb_vert){
   
        int k1, l,c;
        maillon_tetra* ptr;
        
        ptr = (maillon_tetra*)malloc(sizeof(maillon_tetra));    
           
        for (k1=0; k1<K; k1++){                     //Enregistre le tetraedre
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
 
 
 


 
 
/*--------------------------TRIE ROUGE----------------------------------------*/ 
/* @Brief: Copie les éléments de la liste qui ont un minimum de rouge 
*  et enlève les symétries
*/
liste trie_rouge (liste liste_tetra, int* min_rouge){

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



/*--------------------------TRIE BLEU----------------------------------------*/ 
/* @Brief: Copie les éléments de la liste qui ont un maximum de bleu 
*  et enlève les symétries
*/
liste trie_bleu (liste liste_tetra, int* max_bleu){

    liste   copie;
    copie = NULL;
    if(liste_tetra == NULL){
        return(liste_tetra);
    }else{
    while( liste_tetra != NULL){
        if ((*max_bleu <= liste_tetra->nb_bleu)){
    copie = ajout_liste (liste_tetra->tetra, copie, 
            liste_tetra->nb_rouge, liste_tetra->nb_bleu, liste_tetra->nb_vert);
   
        }
     liste_tetra = liste_tetra->suivant;
    }
    return(copie);
    }
}




/*--------------------------TRIE VERT----------------------------------------*/ 
/* @Brief: Copie les éléments de la liste qui ont un maximum de vert 
*  et enlève les symétries
*/
liste trie_vert (liste liste_tetra, int* max_vert){

    liste   copie;
    copie = NULL;
    if(liste_tetra == NULL){
        return(liste_tetra);
    }else{
    while( liste_tetra != NULL){
        if ((*max_vert <= liste_tetra->nb_vert)){
    copie = ajout_liste (liste_tetra->tetra, copie, 
            liste_tetra->nb_rouge, liste_tetra->nb_bleu, liste_tetra->nb_vert);
   
        }
     liste_tetra = liste_tetra->suivant;
    }
    return(copie);
    }
}


/*---------------- BACK TRACK MIN ROUGE -------------------------------*/
/*@brief:
*/
void back_track_rouge (int i, int fin_boucle, int *min_rouge){

    int l, c, tetra[K][K][K], valeur, k1, nb_rouge, nb_vert, nb_bleu;
    nb_rouge=0;
    nb_bleu=0;
    nb_vert=0;
    

    if (i == fin_boucle){  	
    	
    	//Passage ligne en triangle
    	valeur = 0;
    	for(l=0; l<K; l++){     //Ligne 
    	    for(c=0; c<K-l; c++){
    	        tetra[l][c][K-1] = ligne[valeur];
    	        valeur = valeur+1;
    	    }
    	}
    	
    	
    	//compte les differentes couleurs des boules de la base
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
            for (l=k1; l>=0; l--)                    //lignes
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
           liste_tetra = trie_rouge (liste_tetra, min_rouge); 
        }
            
        
        
    }else{                                      //Back track
                ligne[i] = 0;       
				back_track_rouge (i+1, fin_boucle, min_rouge);
                ligne[i] = 1;        
				back_track_rouge (i+1, fin_boucle, min_rouge);
                ligne[i] = 2;                     
				back_track_rouge (i+1, fin_boucle, min_rouge);
    }
} 
 






/*---------------- BACK TRACK MAX BLEU -------------------------------*/
/*@brief:
*/
void back_track_bleu (int i, int fin_boucle, int *max_bleu){

    int l, c, tetra[K][K][K], valeur, k1, nb_rouge, nb_vert, nb_bleu;
    nb_rouge=0;
    nb_bleu=0;
    nb_vert=0;
    

    if (i == fin_boucle){  	
    	
    	//Passage ligne en triangle
    	valeur = 0;
    	for(l=0; l<K; l++){     //Ligne 
    	    for(c=0; c<K-l; c++){
    	        tetra[l][c][K-1] = ligne[valeur];
    	        valeur = valeur+1;
    	    }
    	}
    	
    	
    	//compte les differentes couleurs des boules de la base
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
            for (l=k1; l>=0; l--)                    //lignes
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
        if (nb_bleu >= *max_bleu ){
            *max_bleu = nb_bleu;
            
           liste_tetra = ajout_liste (tetra,liste_tetra,nb_rouge,nb_bleu,nb_vert);
           liste_tetra = trie_bleu (liste_tetra, max_bleu); 
        }
            
        
        
    }else{                                      //Back track
                ligne[i] = 0;       
				back_track_bleu (i+1, fin_boucle, max_bleu);
                ligne[i] = 1;        
				back_track_bleu (i+1, fin_boucle, max_bleu);
                ligne[i] = 2;                     
				back_track_bleu (i+1, fin_boucle, max_bleu);
    }
} 
 







/*---------------- BACK TRACK MAX VERT -------------------------------*/
/*@brief:
*/
void back_track_vert (int i, int fin_boucle, int *max_vert){

    int l, c, tetra[K][K][K], valeur, k1, nb_rouge, nb_vert, nb_bleu;
    nb_rouge=0;
    nb_bleu=0;
    nb_vert=0;
    

    if (i == fin_boucle){  	
    	
    	//Passage ligne en triangle
    	valeur = 0;
    	for(l=0; l<K; l++){     //Ligne 
    	    for(c=0; c<K-l; c++){
    	        tetra[l][c][K-1] = ligne[valeur];
    	        valeur = valeur+1;
    	    }
    	}
    	
    	
    	//compte les differentes couleurs des boules de la base
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
            for (l=k1; l>=0; l--)                    //lignes
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
        if (nb_vert >= *max_vert ){
            *max_vert = nb_vert;
            
           liste_tetra = ajout_liste (tetra,liste_tetra,nb_rouge,nb_bleu,nb_vert);
           liste_tetra = trie_vert (liste_tetra, max_vert); 
        }
            
        
        
    }else{                                      //Back track
                ligne[i] = 0;       
				back_track_vert (i+1, fin_boucle, max_vert);
                ligne[i] = 1;        
				back_track_vert (i+1, fin_boucle, max_vert);
                ligne[i] = 2;                     
				back_track_vert (i+1, fin_boucle, max_vert);
    }
} 
 








/*---------------- BACK TRACK MAX VERT MIN ROUGE -----------------------------*/
/*@brief:
*/
void back_track_vert_rouge (int i, int fin_boucle, int *max_vert, int *min_rouge){

    int l, c, tetra[K][K][K], valeur, k1, nb_rouge, nb_vert, nb_bleu;
    nb_rouge=0;
    nb_bleu=0;
    nb_vert=0;
    

    if (i == fin_boucle){  	
    	
    	//Passage ligne en triangle
    	valeur = 0;
    	for(l=0; l<K; l++){     //Ligne 
    	    for(c=0; c<K-l; c++){
    	        tetra[l][c][K-1] = ligne[valeur];
    	        valeur = valeur+1;
    	    }
    	}
    	
    	
    	//compte les differentes couleurs des boules de la base
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
            for (l=k1; l>=0; l--)                    //lignes
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
        
        
        // Calcule du maximum de vert:
        if (nb_rouge <= *min_rouge ){
             *min_rouge = nb_rouge;
             liste_tetra_rouge = ajout_liste (tetra,liste_tetra,nb_rouge,nb_bleu,nb_vert);
             liste_tetra_rouge = trie_rouge(liste_tetra, min_rouge);
              
        if (nb_vert >= *max_vert ){
              *max_vert = nb_vert;
              liste_tetra_vert = ajout_liste (tetra,liste_tetra,nb_rouge,nb_bleu,nb_vert);
              liste_tetra_vert = trie_vert(liste_tetra, max_vert);
            }  

        } 

             
    }else{                                      //Back track
                ligne[i] = 0;       
				back_track_vert_rouge (i+1, fin_boucle, max_vert, min_rouge);
                ligne[i] = 1;        
				back_track_vert_rouge (i+1, fin_boucle, max_vert, min_rouge);
                ligne[i] = 2;                     
				back_track_vert_rouge (i+1, fin_boucle, max_vert, min_rouge);
    }
} 







/*---------------- BACK TRACK MAX BLEU MIN ROUGE -----------------------------*/
/*@brief:
*/
void back_track_bleu_rouge (int i, int fin_boucle, int *max_bleu, int *min_rouge){

    int l, c, tetra[K][K][K], valeur, k1, nb_rouge, nb_vert, nb_bleu;
    nb_rouge=0;
    nb_bleu=0;
    nb_vert=0;
    

    if (i == fin_boucle){  	
    	
    	//Passage ligne en triangle
    	valeur = 0;
    	for(l=0; l<K; l++){     //Ligne 
    	    for(c=0; c<K-l; c++){
    	        tetra[l][c][K-1] = ligne[valeur];
    	        valeur = valeur+1;
    	    }
    	}
    	
    	
    	//compte les differentes couleurs des boules de la base
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
            for (l=k1; l>=0; l--)                    //lignes
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
        
        
        // Calcule du maximum de vert:
        if (nb_rouge <= *min_rouge ){
             *min_rouge = nb_rouge;
           liste_tetra_rouge = ajout_liste(tetra,liste_tetra_rouge,nb_rouge,nb_bleu,nb_vert);
             liste_tetra_rouge = trie_rouge(liste_tetra_rouge, min_rouge);
              
        if (nb_bleu >= *max_bleu ){
              *max_bleu = nb_bleu;
              liste_tetra_bleu = ajout_liste (tetra,liste_tetra_bleu,nb_rouge,nb_bleu,nb_vert);
              liste_tetra_bleu = trie_bleu(liste_tetra_bleu, max_bleu);
            }  

        } 

             
    }else{                                      //Back track
                ligne[i] = 0;       
				back_track_bleu_rouge (i+1, fin_boucle, max_bleu, min_rouge);
                ligne[i] = 1;        
				back_track_bleu_rouge (i+1, fin_boucle, max_bleu, min_rouge);
                ligne[i] = 2;                     
				back_track_bleu_rouge (i+1, fin_boucle, max_bleu, min_rouge);
    }
} 







/*-------------------- TRIE MIN MAX VERT ----------------------------*/
liste trie_minmax_vert (liste liste_tetra_vert,liste liste_tetra_rouge, int *max_vert, int *min_rouge){
    liste copie = NULL;
 
    return(copie);
}




/*---------------- Trie min max BLEU--------------------------*/
liste trie_minmax_bleu (liste liste_tetra_bleu,liste liste_tetra_rouge, int *max_bleu, int *min_rouge){

    liste copie = NULL;
    while (liste_tetra_rouge != NULL){
            if(liste_tetra_rouge->nb_bleu == *max_bleu){
                 copie = ajout_liste (liste_tetra_rouge->tetra, copie, 
                    liste_tetra_rouge->nb_rouge, liste_tetra_rouge->nb_bleu,
                    liste_tetra_rouge->nb_vert);
            }
             liste_tetra_rouge = liste_tetra_rouge->suivant; 
    }    
    
     while (liste_tetra_bleu != NULL){
            if(liste_tetra_bleu->nb_rouge == *min_rouge){
                    copie = ajout_liste (liste_tetra_bleu->tetra, copie, 
                    liste_tetra_bleu->nb_rouge, liste_tetra_bleu->nb_bleu,
                    liste_tetra_bleu->nb_vert);
                 
            }
            
            
             liste_tetra_bleu = liste_tetra_bleu->suivant; 
    }            

    return(copie);
}



/*------------------ FONCTION POUR LE SWITCH ---------------------------*/

int choisir ( void ){
    int reponse ;
     do {(void)printf("Choix : \n%d Minimum de rouges \n%d Maximum de bleus \n" ,
                       MINROUGE , MAXBLEU ) ;
         (void)printf("%d Maximum de verts \n%d Minimum rouges et maximum verts" ,
                       MAXVERT , MINMAXVERT ) ;
         (void)printf( "\n%d Minimum de rouges et maximum de bleus \n" ,
                      MINMAXBLEU) ;
         (void)scanf( "%d" , &reponse ) ;
        }
     while ( reponse < MINROUGE || reponse > MINMAXBLEU ) ;
     return( reponse ) ;
}









/*---------------------------MAIN-----------------------------------*/                 
int main (void){    
    int choix, fin_boucle, h, c, l, k1, compt, ini;   
    int *min_rouge, *max_bleu, *max_vert;
    compt = 0;                                      //compteur
    fin_boucle = 0;
    ini = 0;
    
    
    //Calcul du nombre de boules dans la base
	 for (h=1;h<=K;h++)
	    {  
		    fin_boucle = fin_boucle+h;
	    }	
	    
    min_rouge = &fin_boucle;
    max_bleu = &ini;
    max_vert = &ini;
          
                  
                  
    
    //Switch:
    choix = choisir() ;
          switch ( choix )
                 {case MINROUGE :                 
                     back_track_rouge(0,fin_boucle, min_rouge); 
                     while(liste_tetra != NULL){
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions\n",compt);
                     break ;
                    
                  case MAXBLEU :  
                    back_track_bleu(0,fin_boucle, max_bleu); 
                     while(liste_tetra != NULL){
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions\n",compt);
                    break ;
                  
                  case MAXVERT :  
                        back_track_vert(0,fin_boucle, max_vert); 
                     while(liste_tetra != NULL){
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions\n",compt);
                    break ;

                  case MINMAXVERT : 
                  back_track_vert_rouge(0,fin_boucle, max_vert, min_rouge);
                  liste_tetra = trie_minmax_vert (liste_tetra_vert, liste_tetra_rouge, max_vert, min_rouge); 
                     while(liste_tetra != NULL){
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions\n",compt);
                   
                  break ;
                  case MINMAXBLEU :  
                  back_track_bleu_rouge(0,fin_boucle, max_bleu, min_rouge);
                  liste_tetra = trie_minmax_bleu (liste_tetra_bleu, liste_tetra_rouge, max_bleu, min_rouge); 
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
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions\n",compt);
                   
                  break ;
                  
                 }
    

    return(0);

}    
