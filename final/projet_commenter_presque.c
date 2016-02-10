 /** 
* Polytech Marseille
* Case 925 -163, avenue de Luminy
* 13288 Marseille CEDEX 9
*
* Ce fichier est l'oeuvre d'eleves de Polytech Marseille. Il ne peut être 
* reproduit, utilise ou modifie sans l'avis express de ses auteurs.
*/

/**
* @author 
*  BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
*  DENIS Justine <justine.denis@etu.univ-amu.fr>
*
* @version 0.0.1 / 09-02-2016
* @toto NA
* @bug NA 
*/

/**
* @file projet_final.c
* @brief
*
*  Creation de tous les tétraedres possibles pour une base donnée K. 
*  K est la longueur/largeur de la base du tétraedre.
*  Dans ce programme, nous cherchons les tetraedre:
*  - minimisant le nombre de rouge (code par 0)
*  - maximisant le nombre de bleu  (code par 1)
*  - maximisant le nombre de vert  (code par 2)
*  - minimisant le nombre de rouge et maximisant le nombre de bleu
*  - minimisant le nombre de rouge et maximisant le nombre de vert 
**/ 


#include <stdio.h>                    
#include <stdlib.h>                              //pour malloc



#define K 2                                      //Taille du tétraedre
#define ROUGE 0                                  //Definit les codes couleurs   
#define BLEU 1
#define VERT 2

#define MINROUGE 1                              //Definition des choix du switch
#define MAXBLEU 2
#define MAXVERT 3
#define MINMAXVERT 4
#define MINMAXBLEU 5

//Pour la fonction printf avec couleur:
#define couleur(param) printf("\033[%sm",param)
    


/*Declaration de la structure de listes*/
typedef struct maillon_tetra{   
    int nb_bleu;
    int nb_rouge;
    int nb_vert;   
    int tetra[K][K][K];                    //Enregistre le tetraedre                
    struct maillon_tetra *suivant;         //Pointeur sur prochain maillon
}maillon_tetra;

typedef maillon_tetra *liste;


/* Declaration des variables globales*/
int compt = 0;                              //Compteur
int ligne[K];                               //Ligne de back track
liste liste_tetra = NULL;                   //Liste des tetraedres
liste liste_tetra_rouge = NULL;             //Liste tetraedre avec minimum rouges    



 
 



//////////////////////// FONCTIONS ////////////////////////////////////////////

/*--------------------------- AJOUT_LISTE------------------------------------*/
/* @brief: Enregistre les tatraedres dans une liste avec le nombre de boules de
*  couleurs.
*  Parametres: Tableau du tetraedre en cour, liste des tetredres, nombre de 
*  rouges, de bleu et de vert dans le tetraedre en cour. Retourne un maillon.
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
        
    return ptr;                                 //Retourne le maillon
}



/*--------------- SYMETRIE-------------------------------------------------*/
/*  @brief: Compare le tetraedre avec des symetries axial, horaire et 
*   anti-horaire. Si le tetraedre est une symetrie d'un maillon de la liste,
*   alors on retourne 0 sinon 1. 
*   Parametres: liste contenant les tetraedres. 
*/

int symetrie(liste liste_tetra)
{
	if(liste_tetra->suivant==NULL)
	{
		return(1);                              //Si il n'y a qu'un tetraedre... 
		                                        //...renvoit pas de symetrie
	}
	
	int result;                                 //bouleen retourne
	int result1=0;                              //bouleen symetrie axiale
	int result2=0;                              //bouleen symetrie anti-horaire
	int result3=0;                              //bouleen symetrie horaire
	int result4=0;                              //symetrie antihoraire et axiale
	int result5=0;                              //symetrie horaire et axiale
	int i,j,l,c;
	int tetra[K][K],copie[K][K];
	

    for (l=0; l<=K; l++)                        //Recupere la base du denier... 
    {                                           //...tetraedre de la liste
        for(c=0; c<=K-l; c++) 
        {
       		tetra[l][c] = liste_tetra->tetra[l][c][K-1];
       	}
   	}	
   	
    liste_tetra = liste_tetra->suivant; 
    
	while (liste_tetra != NULL)                 //Verifie les symetries
	{
	result1=0;
	result2=0;
	result3=0;
	result4=0;
	result5=0;

        for (l=0; l<=K-1; l++)                      //Recupere une base a comparer
        {                      
            for(c=0; c<=K-1-l; c++) 
            {
            	   copie[l][c] = liste_tetra->tetra[l][c][K-1];
           	}
        }
        
            
	    for(i=0;i<K;i++)                        //boucles de reperage des symetries
	    {
		    for(j=0;j<K-i;j++)
		    {
			    if(copie[i][K-1-i-j]!=tetra[i][j])
			    {
				    result1=1;                    //0 Symetrie axiale sinon 1 	 
			    }
		    }
	    }
	
	    for(i=0;i<K;i++)                        
	    {
		    for(j=0;j<K-i;j++)
		    {
			    if(copie[K-1-i-j][i]!=tetra[i][j])
			    {
				    result2=1;                  //0 symetrie rotation antihoraire 
			    }
		    }
	    }
	
	    for(i=0;i<K;i++)
	    {
		    for(j=0;j<K-i;j++)
		    {
			    if(copie[j][K-1-i-j]!=tetra[i][j])
			    {
				    result3=1;                  //0 symetrie rotation horaire sinon 1
			    }
		    }
	    }
	
	    for(i=0;i<K;i++)
	    {
		    for(j=0;j<K-i;j++)
		    {
			    if(copie[K-1-i-j][j]!=tetra[i][j])
			    {
				    result4=1;                  //0 symetrie anti-horaire et axiale
			    }
		    }
	    }
	
	    for(i=0;i<K;i++)
	    {
		    for(j=0;j<K-i;j++)
		    {
			    if(copie[j][i]!=tetra[i][j])
			    {
				    result5=1;                  //0 symetrie horaire et axiale 
			    }
		    }
	    }
	
        liste_tetra = liste_tetra->suivant;
		
	    // Attribution de la valeur de result
	    if((result1==0)||(result2==0)||(result3==0)||(result4==0)||(result5==0))
	    {

		    result=0;                           // si 0: symetrie detectee...
		    return(result);
	    }
    }	
	result=1;                                   //... Sinon 1 pas de symetrie
	
	return(result);                             // Retourne bouleen    
} 




/*------------------------ AFFICHAGE -------------------------------------*/
/* @brief: Affiche les tetraedres en couleurs
*  Parametre: liste contenant les tetraedres
*/

void affichage(liste liste_tetra)
{
 	int c, l, k1,compteur;
 	compteur=0;
 	printf("\nAffichage des solutions\n");
	while(liste_tetra != NULL)
	{
		compteur++;
		printf("Solution n°%i",compteur); 	
    	for(k1=K-1; k1>=0; k1--)
    	{
    		for (l=0; l<=k1; l++) 
    		{              
        		printf("\n");            
            	for(c=0; c<=k1-l; c++) 
            	{
               		if (liste_tetra->tetra[l][c][k1]==0)
               		{
               			couleur("31");//couleur rouge
               			printf("r ");
               			couleur("0");//retourne a la couleur blanche
               		}
               		else if(liste_tetra->tetra[l][c][k1]==1)
               		{
               			couleur("36");//couleur cyan car bleu est trop sombre
               			printf("b ");
               			couleur("0");
               		}
               		else
               		{
               			couleur("32");//couleur verte
               			printf("v ");
               			couleur("0");
               		}
                }
            }
            printf("\n");
        }
        printf("\n");
        liste_tetra = liste_tetra->suivant;
    }
} 
/////////////////////////////////////////// CASE MIN ROUGE///////////////////// 
/*--------------------------TRIE ROUGE----------------------------------------*/ 
/* @Brief: Copie les éléments de la liste qui ont un minimum de rouge 
*  et enlève les symétries
*  Parametre: liste contenant les tetraedre et un entier contenant le minimum de rouge
*  Retourne une liste
*/
liste trie_rouge (liste liste_tetra, int* min_rouge){
    liste  copie;								//Copie: nouvelle liste vide			
    copie = NULL;
    if(liste_tetra == NULL)
    {
        return(liste_tetra);
    }else{
	    while( liste_tetra != NULL)
	    {										//Si nombre rouge minimum et tetra non symetrique
	        if ((*min_rouge >= liste_tetra->nb_rouge) && symetrie(liste_tetra))
	        {									//Copie le maillon dans la liste
	    		copie = ajout_liste (liste_tetra->tetra, copie, 
	            liste_tetra->nb_rouge, liste_tetra->nb_bleu, liste_tetra->nb_vert);
	        }
	     liste_tetra = liste_tetra->suivant;
	    }
    return(copie);								//Retourne copie
    }
}



/*--------------------------TRIE BLEU----------------------------------------*/ 
/* @Brief: Copie les éléments de la liste qui ont un maximum de bleu 
*  et enlève les symétries
*  Parametre: liste contenant les tetraedre et un entier contenant le maximum de bleu
*  Retourne une liste
*/
liste trie_bleu (liste liste_tetra, int* max_bleu){

    liste   copie;
    copie = NULL;
    if(liste_tetra == NULL){
        return(liste_tetra);
    }else{
    while( liste_tetra != NULL){
        if ((*max_bleu <= liste_tetra->nb_bleu) && symetrie(liste_tetra)){
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
        if ((*max_vert <= liste_tetra->nb_vert) && symetrie(liste_tetra)){
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
                        tetra[l][c][k1] = ROUGE;
                        nb_rouge++;
                    
                    //Si les 3 boules differentes -->vert    
                    }else if((tetra[l][c][k1+1] != tetra[l][c+1][k1+1]) 
                    && (tetra[l][c+1][k1+1] !=  tetra[l+1][c][k1+1])
                    && (tetra[l][c][k1+1] != tetra[l+1][c][k1+1]))
                    {
                        tetra[l][c][k1] = VERT;
                        nb_vert++;
                    
                    //Si 2 boules identiques-->bleu    
                    }else{
                        tetra[l][c][k1] = BLEU;
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
                        tetra[l][c][k1] = ROUGE;
                        nb_rouge++;
                    
                    //Si les 3 boules differentes -->vert    
                    }else if((tetra[l][c][k1+1] != tetra[l][c+1][k1+1]) 
                    && (tetra[l][c+1][k1+1] !=  tetra[l+1][c][k1+1])
                    && (tetra[l][c][k1+1] != tetra[l+1][c][k1+1]))
                    {
                        tetra[l][c][k1] = VERT;
                        nb_vert++;
                    
                    //Si 2 boules identiques-->bleu    
                    }else{
                        tetra[l][c][k1] = BLEU;
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
                        tetra[l][c][k1] = ROUGE;
                        nb_rouge++;
                    
                    //Si les 3 boules differentes -->vert    
                    }else if((tetra[l][c][k1+1] != tetra[l][c+1][k1+1]) 
                    && (tetra[l][c+1][k1+1] !=  tetra[l+1][c][k1+1])
                    && (tetra[l][c][k1+1] != tetra[l+1][c][k1+1]))
                    {
                        tetra[l][c][k1] = VERT;
                        nb_vert++;
                    
                    //Si 2 boules identiques-->bleu    
                    }else{
                        tetra[l][c][k1] = BLEU;
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
                        tetra[l][c][k1] = ROUGE;
                        nb_rouge++;
                    
                    //Si les 3 boules differentes -->vert    
                    }else if((tetra[l][c][k1+1] != tetra[l][c+1][k1+1]) 
                    && (tetra[l][c+1][k1+1] !=  tetra[l+1][c][k1+1])
                    && (tetra[l][c][k1+1] != tetra[l+1][c][k1+1]))
                    {
                        tetra[l][c][k1] = VERT;
                        nb_vert++;
                    
                    //Si 2 boules identiques-->bleu    
                    }else{
                        tetra[l][c][k1] = BLEU;
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
                        tetra[l][c][k1] = ROUGE;
                        nb_rouge++;
                    
                    //Si les 3 boules differentes -->vert    
                    }else if((tetra[l][c][k1+1] != tetra[l][c+1][k1+1]) 
                    && (tetra[l][c+1][k1+1] !=  tetra[l+1][c][k1+1])
                    && (tetra[l][c][k1+1] != tetra[l+1][c][k1+1]))
                    {
                        tetra[l][c][k1] = VERT;
                        nb_vert++;
                    
                    //Si 2 boules identiques-->bleu    
                    }else{
                        tetra[l][c][k1] = BLEU;
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
liste trie_minmax_vert (liste liste_tetra_rouge, int *max_vert, int *min_rouge){
    liste copie = NULL;
    while (liste_tetra_rouge != NULL){
            if((liste_tetra_rouge->nb_vert == *max_vert) && symetrie(liste_tetra_rouge)){
                 copie = ajout_liste (liste_tetra_rouge->tetra, copie, 
                    liste_tetra_rouge->nb_rouge, liste_tetra_rouge->nb_bleu,
                    liste_tetra_rouge->nb_vert);
            }
            liste_tetra_rouge = liste_tetra_rouge->suivant; 
    }    
    return(copie);
}




/*---------------- Trie min max BLEU--------------------------*/
liste trie_minmax_bleu (liste liste_tetra_rouge, int *max_bleu, int *min_rouge){

    liste copie = NULL;
    while (liste_tetra_rouge != NULL){
            if((liste_tetra_rouge->nb_bleu == *max_bleu) && symetrie(liste_tetra_rouge)){
                 copie = ajout_liste (liste_tetra_rouge->tetra, copie, 
                    liste_tetra_rouge->nb_rouge, liste_tetra_rouge->nb_bleu,
                    liste_tetra_rouge->nb_vert);
            }
            liste_tetra_rouge = liste_tetra_rouge->suivant; 
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
         (void)printf( "\n%d Minimum rouges et maximum bleus \n" ,
                      MINMAXBLEU) ;
         (void)scanf( "%d" , &reponse ) ;
        }
     while ( reponse < MINROUGE || reponse > MINMAXBLEU ) ;
     return( reponse ) ;
}









/*---------------------------MAIN-----------------------------------*/                 
int main (void){    
    int choix, fin_boucle, h, compt, ini, encore;   
    int *min_rouge, *max_bleu, *max_vert;
    compt = 0;                                      //compteur
    fin_boucle = 0;
    ini = 0;                                        //initialisation des maximum
                                     
    
    
    //Calcul du nombre de boules dans la base
	 for (h=1;h<=K;h++)
	    {  
		    fin_boucle = fin_boucle+h;
	    }	
	    
    min_rouge = &fin_boucle;
    max_bleu = &ini;
    max_vert = &ini;
          
                  
                  
    
    //Switch:
    do{
        choix = choisir() ;
        switch ( choix ){
                 case MINROUGE : 
                    compt = 0;                  
                     back_track_rouge(0,fin_boucle, min_rouge); 
                     affichage (liste_tetra);
                     while(liste_tetra != NULL){
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions",compt);
                     printf(" pour %i rouges\n",*min_rouge);
                     break ;
                    
                  case MAXBLEU :
                    compt = 0;    
                    back_track_bleu(0,fin_boucle, max_bleu); 
                    affichage (liste_tetra);
                     while(liste_tetra != NULL){
                        
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions",compt);
                     printf(" pour %i bleu\n",*max_bleu);
                    break ;
                  
                  case MAXVERT : 
                    compt = 0;   
                        back_track_vert(0,fin_boucle, max_vert); 
                        affichage (liste_tetra);
                     while(liste_tetra != NULL){
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions",compt);
                      printf(" pour %i verts\n",*max_vert);
                    break ;

                  case MINMAXVERT : 
                  compt = 0;  
                  back_track_vert_rouge(0,fin_boucle, max_vert, min_rouge);
                  liste_tetra = trie_minmax_vert (liste_tetra_rouge, max_vert, min_rouge); 
                  affichage (liste_tetra);
                     while(liste_tetra != NULL){
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions",compt);
                      printf(" pour %i rouges et %i verts\n",*min_rouge,*max_vert);
                   
                  break ;
                  case MINMAXBLEU :  
                  compt = 0;  
                  back_track_bleu_rouge(0,fin_boucle, max_bleu, min_rouge);
                  liste_tetra = trie_minmax_bleu (liste_tetra_rouge, max_bleu, min_rouge); 
                  affichage (liste_tetra);
                     while(liste_tetra != NULL){
                       
                        compt = compt+1; 
                        liste_tetra = liste_tetra->suivant;
                     }
                     printf("Il y a %i solutions",compt);
                     printf(" pour %i rouges et %i bleu\n",*min_rouge,*max_bleu);
                   
                  break ;
                  
          }
          (void)printf( "\n Souhaitez vous continuer?\n 1: Oui   0: Non\n " ) ;
          (void)scanf( "%d" , &encore ) ;
     }while ( encore ) ;
      (void)printf( "Fin du programme\nAurevoir\n" ) ;    
    

    return(0);

}                 
