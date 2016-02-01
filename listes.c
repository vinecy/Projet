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
* @version 0.0.1 / 04-11-2015
* @toto NA
* @bug NA 
*/

/**
* @file liste.c
* @brief
*
*  FONCTION POUR MANIPULER LES LISTES:
*  CREATION, LONGUEUR, COPIE, RECHERCHE D'ELEMENT, SUPPRESSSION, INSERTION,...
*
**/ 

#include <stdio.h>
#include <stdlib.h>                         //pour malloc    
#include <assert.h>                         //pour assert


//Definition de la structure:
/*  t_ptr_liste
*   Creation du pointeur sur maillon */
typedef struct maillon{
    int donnee;                       //Creation donnee du maillon
    struct maillon *suivant;         //Creation pointeur sur prochain maillon
}maillon;

typedef maillon *t_ptr_liste;


//Prototypes:
t_ptr_liste cree_vide (void);
int est_vide(t_ptr_liste liste);
t_ptr_liste ajout_liste (t_ptr_liste liste, int x);
int tete_liste(t_ptr_liste liste);
t_ptr_liste queue_liste(t_ptr_liste liste);
t_ptr_liste cree_liste(void);
t_ptr_liste cree_liste_fc(void);
int affic_liste (t_ptr_liste liste);
int longueur_liste(t_ptr_liste liste);
int longueur_liste_re(t_ptr_liste liste);
int longueur_liste_fc(t_ptr_liste liste);
t_ptr_liste copie_liste(t_ptr_liste liste);
t_ptr_liste copie_liste_fc(t_ptr_liste liste);
t_ptr_liste recherche_element (int X, t_ptr_liste);
t_ptr_liste recherche_element_fc (int X, t_ptr_liste);
t_ptr_liste suppr_1 (int X, t_ptr_liste liste);
t_ptr_liste suppr_maillons(int X, t_ptr_liste liste);
t_ptr_liste insertion(int X, t_ptr_liste liste);
t_ptr_liste copie_inverse (t_ptr_liste liste);
t_ptr_liste copie_inverse_fc (t_ptr_liste liste);
int palindrome(t_ptr_liste liste);
t_ptr_liste fibo(int n);
t_ptr_liste fusion1(t_ptr_liste liste1, t_ptr_liste liste2);
t_ptr_liste fusion2(t_ptr_liste liste1, t_ptr_liste liste2);
t_ptr_liste somme_prefixe(t_ptr_liste liste);
t_ptr_liste tri_buble (t_ptr_liste liste);
t_ptr_liste suppr_tete (t_ptr_liste liste);
int main (void);







int main (void){ 
    
    int n;  
    t_ptr_liste adresse;  
    
    t_ptr_liste liste1, copie, liste2, tmp;
    
    liste1 = cree_liste();                       //cree une liste
    affic_liste(liste1);                         //lit la liste
    
    liste1 = suppr_tete(liste1);
    affic_liste(liste1); 
    
    /*liste2 = cree_liste();
    affic_liste(liste2);
    
    printf("La liste contient %i elements\n",longueur_liste(liste1));
    
    printf("\nVoici la copie de la liste ");
    copie = copie_liste(liste1);
    affic_liste(copie);
    
    printf("\nRecherche element X (entrer element >0) ");
    scanf("%i",&n); 
    adresse = recherche_element(n, liste1);   
    printf("\nL'adresse de %i est %i\n",n,adresse);
    
    printf("\nSupression d'un element(entrer element >0) ");
    scanf("%i",&n);   
    printf("\nNouvelle liste\n");
    affic_liste(suppr_1(n, liste1));

    printf("\nSupression des elements =X (entrer X>0) ");
    scanf("%i",&n);   
    printf("\nNouvelle liste\n");
    affic_liste(suppr_maillons(n, liste1));
    
    printf("\nAjout elements X (entrer X>0) ");
    scanf("%i",&n);   
    printf("\nNouvelle liste\n");
    affic_liste(insertion(n, liste1));
    
    printf("\nCopie inverse d'une liste ");
    affic_liste(copie_inverse_fc(liste1));
    
    printf("La liste est un palindrome? (1=oui, 0=non): %i\n",palindrome(liste1));
    
    n = 5;
    printf("Liste de fibonnaci pour n=5 \n");
    affic_liste(fibo(n));
    
    printf("\nLA fusion des deux listes est:\n");
    affic_liste(fusion1(liste1,liste2));
    
    printf("\nLA fusion des deux listes est:\n");
    affic_liste(fusion2(liste1,liste2));
    
    printf("\n La somme des prefixes est: \n");
    affic_liste(somme_prefixe(liste1));*/
    
    //printf("\n tri bublle\n");
    //affic_liste(tri_buble(liste1));
    
   


} 


t_ptr_liste suppr_tete (t_ptr_liste l)
{
   t_ptr_liste p;

   if (l==NULL){
      return (l);
  }else{
   p= l->suivant ;
  free(l);
   return(p); 
   }
}




 



/*--------------------------------------------------------------------------*/
/*----------------------FONCTION ADT ----------------------------------------*/

/* 1)
* FONCTION ADT (ABSTRACT DATA TYPE)*/

/* cree_vide
*  Creation d'une liste vide */
t_ptr_liste cree_vide (void){
    return NULL;
}

/* est_vide
*  Pour savoir si une liste est vide*/
int est_vide(t_ptr_liste liste){
    return(liste == cree_vide());    //Pas oublier comparaison fonction!
}

/* ajout_liste
*  Ajout d'un element dans une liste*/
t_ptr_liste ajout_liste (t_ptr_liste liste, int x){
    maillon* ptr;
    ptr = (maillon*)malloc(sizeof(maillon));       //Cree pointeur sur 1 maillon
    ptr->donnee = x;                               //Stock info ds maillon 
    ptr->suivant = liste;                          //pointeur sur la suite liste
    return ptr; 
}

/* tete_liste
*  Recupere les donnee d'un maillon*/
int tete_liste(t_ptr_liste liste){
    assert(!est_vide(liste));                       //si vide=> arrete prog
    return liste -> donnee;
}

/* queue_liste
*  Fonction qui renvoit au champ suivant*/
t_ptr_liste queue_liste(t_ptr_liste liste){
    assert(!est_vide(liste));                       //si vide=> arrete prog
    return liste -> suivant;
}



/*------------------------------------------------------------------------*/
/*  2)   Creation d'une liste
*   Stock une suite de chiffre dans une liste (stop qd negatif)*/
// avec FONCTION
t_ptr_liste cree_liste_fc(void){
    int n;
    t_ptr_liste liste;
    liste = cree_vide();
    
    printf("Entrez une valeur positive.\n Pour terminer la liste, ecrire un "
        "nombre negatif\n");
    scanf("%d",&n);
    
    while(n >= 0){
        liste = ajout_liste(liste,n);              //Creation element dans liste
        printf("Entrez une valeur positive.\n Pour terminer la liste, ecrire un "
        "nombre negatif\n");
        scanf("%d",&n);
    }
    return liste;
}

//avec POINTEUR
t_ptr_liste cree_liste(void){
    t_ptr_liste liste, tmp;
    int n;
    liste = NULL;
    
    printf("Entrez une valeur positive.\n Pour terminer la liste, ecrire un "
        "nombre negatif\n");
    scanf("%d",&n);
    
    while (n >=0){
        tmp = (maillon*)malloc(sizeof(maillon));       //alloue la memoire
        tmp->donnee = n;                               //place la valeur
        tmp->suivant = liste;                  //pointeur sur le champs suivant
        liste = tmp;  
        printf("Entrez une valeur positive.\n Pour terminer la liste, ecrire un "
        "nombre negatif\n");
        scanf("%d",&n);
    }
    return liste;
}



/*------------------------------------------------------------------------*/
/*  3) Affichage d'une liste
*   Affiche a l'ecran une liste*/
int affic_liste (t_ptr_liste liste){
    assert(!est_vide(liste));
    while (!est_vide(liste)){
        printf("%i ",tete_liste(liste));
        liste = queue_liste(liste);
    }
    printf("\n");
    return;
}


/*----------------------------------------------------------------------*/
/*4) Longeur de liste 
*   determine la longeur d'une liste*/
//Avec FONCTION
int longueur_liste_fc(t_ptr_liste liste) {
    int longueur;                               //compteur
    t_ptr_liste tmp;
    longueur = 0;
    while (!est_vide(liste)){                   //Tant que liste non vide
        longueur ++;                        
        liste = queue_liste(liste);
    }
    return longueur;
}

//recursive:
int longueur_liste_re(t_ptr_liste liste){
    if(est_vide(liste)) return (0);
    else return (longueur_liste(queue_liste(liste))+1);
}

//Avec pointeur
int longueur_liste(t_ptr_liste liste){
    int longueur;
    longueur = 0;
    while(liste!=NULL){                          //Tant que liste non vide
        longueur ++;
        liste = liste->suivant;
    }
    return longueur;
}


/*------------------------------------------------------------------------*/
/*  5) Copie de liste 
* Copie a l'identique une liste*/
//Avec fonction: 
t_ptr_liste copie_liste_fc(t_ptr_liste liste){
    t_ptr_liste copie;
    copie = cree_vide();
    if(!est_vide(liste)){
      return(ajout_liste(copie_liste_fc(queue_liste(liste)),tete_liste(liste)));
    } else return (cree_vide());
}

//Avec pointeur:
t_ptr_liste copie_liste(t_ptr_liste liste){
    t_ptr_liste copie;
    copie = NULL;
    if (liste != NULL){
        copie = malloc(sizeof(maillon));        //alloue la memoire
        copie->donnee = liste->donnee;
        copie->suivant = liste->suivant;
    }
    return copie;
}


/*------------------------------------------------------------------------*/
/*  6)Recherche d'un element:
*   Renvoit l'adresse de l'element dans la liste
*/
//Fonction
t_ptr_liste recherche_element_fc (int X, t_ptr_liste liste){
    while( (!est_vide(liste)) && (tete_liste(liste)!=X)){
        liste = queue_liste(liste);
    }return (liste); 
}

//Avec pointeur
t_ptr_liste recherche_element (int X, t_ptr_liste liste){
    while( (liste!=NULL) && (liste->donnee!=X)){
        liste = liste->suivant;
    }return (liste); 
}



/*------------------------------------------------------------------------*/
/* 7)   Suppression d'un element d'une liste
*       Supprime le premier X trouver
*/
t_ptr_liste suppr_1 (int X, t_ptr_liste liste){
    t_ptr_liste previous;
    t_ptr_liste ptr;
    ptr = liste;
    while ((ptr!=NULL) && (ptr->donnee!=X)){
        previous = ptr;
        ptr = ptr->suivant;
    }
    if(ptr != NULL){
        if(ptr == liste) {liste = liste->suivant;}
        else {
            previous->suivant = ptr->suivant;
            free(ptr);
            }
    }return liste;
} 


/*------------------------------------------------------------------------*/
/* 7-BIS) Suppresion de toutes les occurances*/
t_ptr_liste suppr_maillons(int X, t_ptr_liste liste){
    t_ptr_liste previous;
    t_ptr_liste ptr;
    ptr = liste;
    while(ptr){                                     //Tant que ptr!=0
        if (ptr->donnee != X){
            previous = ptr;
            ptr = ptr->suivant;
        }else{
            if(ptr == liste){
                liste = ptr->suivant;
                free(ptr);                          //supprime ptr
                ptr = liste;
            }else{
                previous->suivant = ptr->suivant;
                free(ptr);
                ptr = previous->suivant;
            }
        }
    } return (liste);
} 


/*------------------------------------------------------------------------*/
/*  8) Insertion dans une liste ordonnée*/
t_ptr_liste insertion(int X, t_ptr_liste liste){
    t_ptr_liste newMaillon;    
    t_ptr_liste ptr;
    ptr = liste;
    if (est_vide(liste)){ return(ajout_liste(liste, X));}
    while ((!est_vide(queue_liste(ptr))) && (tete_liste(queue_liste(ptr))<X) ){
        ptr = queue_liste(ptr);
    }
    if (ptr == liste)                     //Si X n'est pas dans le tableau trie
    { return ajout_liste(liste, X); }
    else{
        newMaillon = malloc(sizeof(maillon));
        newMaillon->donnee = X;
        newMaillon->suivant = ptr->suivant;
        ptr->suivant = newMaillon;
    } return liste;
}


/*------------------------------------------------------------------------*/
/*  9) Inverse d'une liste avec recopie 
* @bug: Affiche que un element*/
//Pointeurs:
/*t_ptr_liste copie_inverse (t_ptr_liste liste){
    t_ptr_liste copie;
    t_ptr_liste ptr;
    copie = NULL;
       while(ptr != NULL){
       //copie = (maillon*)malloc(sizeof(maillon)); //alloue la memoire
        liste = ptr-> suivant;     
        ptr->suivant = copie;
        copie = ptr;  
        ptr = liste->suivant;
        }return copie;
    }*/
      
//Fonction:
t_ptr_liste copie_inverse_fc(t_ptr_liste liste){
    t_ptr_liste copie;
    copie = cree_vide();
    while(!est_vide(liste)){
        copie = ajout_liste(copie,tete_liste(liste));
        liste = queue_liste(liste);
    }return copie;
}









/*------------------------------------------------------------------------------
----------------------------- SUITE LISTE ------------------------------------*/


/* LISTE PALINDROME:
* Regarde si la liste est la meme qu'on la regarde du debut à la fin*/
int palindrome(t_ptr_liste liste){
    int rep;                            //Booleen (vrai faux)
    t_ptr_liste inverse;
    inverse = copie_inverse_fc(liste);
    rep = 1;                             //1=vrai
    while((!est_vide(liste) && (rep==1))){
        if((tete_liste(inverse)==tete_liste(liste))){
        liste = queue_liste(liste);
        inverse = queue_liste(inverse);
        rep = 1;
        }
        else rep = 0;
    }

    return rep;
}


/*  3/ FUSION DE DEUX LISTES
*   avec des chiffres se repetant*/
t_ptr_liste fusion1(t_ptr_liste liste1, t_ptr_liste liste2){
    t_ptr_liste temp , fusion;
    fusion = NULL;
    
    //Fusion:
    while ((liste1 != NULL) && (liste2 != NULL)){    //Tant que liste pleine
        if (liste1->donnee <= liste2->donnee){           
            temp = (maillon*)malloc(sizeof(maillon)); 
            temp->donnee = liste1->donnee;
            temp->suivant = fusion;
            fusion = temp;    
            liste1 = liste1->suivant;  
               
        }else{ 
            temp = (maillon*)malloc(sizeof(maillon)); 
            temp->donnee = liste2->donnee;
            temp->suivant = fusion;
            fusion = temp;      
            liste2 = liste2->suivant;
            
        }
    }  
     //Si une des liste n'est pas fini
    if(liste1 != NULL){
        while(liste1 != NULL){
            temp = (maillon*)malloc(sizeof(maillon)); 
            temp->donnee = liste1->donnee;
            temp->suivant = fusion;
            fusion = temp;     
            liste1 = liste1->suivant;
        }    
    }else {
        while(liste2 != NULL){
            temp = (maillon*)malloc(sizeof(maillon)); 
            temp->donnee = liste2->donnee;
            temp->suivant = fusion;
            fusion = temp;     
            liste2 = liste2->suivant;
        }
    }

    return temp;
}    






/*  4/ FUSION DE DEUX LISTES SANS REPETITION
*   Le resultat est une  liste sans aucune repetion*/
t_ptr_liste fusion2(t_ptr_liste liste1, t_ptr_liste liste2){
    t_ptr_liste temp , fusion;
    fusion = NULL;
    
    //Fusion:
    while ((liste1 != NULL) && (liste2 != NULL)){    //Tant que liste pleine
        if (liste1->donnee < liste2->donnee){           
            temp = (maillon*)malloc(sizeof(maillon)); 
            temp->donnee = liste1->donnee;
            temp->suivant = fusion;
            fusion = temp;    
            liste1 = liste1->suivant;  
               
        }else if (liste1->donnee > liste2->donnee){
            temp = (maillon*)malloc(sizeof(maillon)); 
            temp->donnee = liste2->donnee;
            temp->suivant = fusion;
            fusion = temp;      
            liste2 = liste2->suivant;
            
        }else{ //Liste1 = liste2
            temp = (maillon*)malloc(sizeof(maillon)); 
            temp->donnee = liste1->donnee;
            temp->suivant = fusion;
            fusion = temp;    
            liste1 = liste1->suivant;
            liste2 = liste2->suivant;    
        }
    } 
     //Si une des liste n'est pas fini
    if(liste1 != NULL){
        while(liste1 != NULL){
            if(liste1->donnee == fusion->donnee){   //Va a la valeur suivante
                liste1 = liste1->suivant;
            }else{
                temp = (maillon*)malloc(sizeof(maillon)); //Ajoute la donnée
                temp->donnee = liste1->donnee;
                temp->suivant = fusion;
                fusion = temp;     
                liste1 = liste1->suivant;
            }
        }    
    }else {
        while(liste2 != NULL){
            if(liste2->donnee == fusion->donnee){   //Va a la valeur suivante
                liste2 = liste2->suivant;
            }else{                                  //Ajoute la donnée
                temp = (maillon*)malloc(sizeof(maillon)); 
                temp->donnee = liste2->donnee;
                temp->suivant = fusion;
                fusion = temp;     
                liste2 = liste2->suivant;
             }
        }
    }
    
    
    return temp;
}    
    
    
    
    
    

/* 5/   Somme des prefixes
*   Calcul de la somme des éléments précédent. 
*   i = Somme de 0 à i
*/
t_ptr_liste somme_prefixe(t_ptr_liste liste){
    t_ptr_liste Lsomme, tmp;
    int tmpSom;                            
    Lsomme = NULL;
    tmpSom = 0;                         //Initialisation compteur de la somme
    
    
    while (liste != NULL){              //Tant que la liste est pleine
        tmp = (maillon*)malloc(sizeof(maillon)); 
        tmp->donnee = liste->donnee+tmpSom;
        tmp->suivant = Lsomme;  
        Lsomme = tmp;
        
        tmpSom = tmpSom+liste->donnee;      //Ajout de la valeur de liste
        liste = liste->suivant;             //Maillon suivant    
    }
    return Lsomme;
}    




/* trie a bulle de liste*/
t_ptr_liste tri_buble (t_ptr_liste la){
    /*int bulle;
    t_ptr_liste tmp, trier;
    trier = NULL;
    do {
        bulle = 0;
        while (liste!=NULL){
            if(liste >= liste->suivant){
            tmp = (maillon*)malloc(sizeof(maillon));
            tmp->donnee = liste->suivant->donnee;
            tmp->suivant = liste->suivant;
            liste->donnee = liste->suivant->donnee;
            liste->suivant = liste->suivant->suivant;
            liste->suivant->donnee = tmp->donnee;
            liste->suivant->suivant = tmp->suivant;
            bulle = 1;
            }
       
            liste = liste->suivant;
        }
    } while (bulle!=1);
    
    return liste;
}  */


//void trier(liste la)
//{// ici on va ranger les elements dans l'ordre croisssant avant de les afficher.
   t_ptr_liste temp, temp1, temp3;
   int min;
   for(temp=la ; temp!=NULL ; temp=temp->suivant)
   {
     temp3=temp;
     min=temp->donnee;
     for(temp1=temp->suivant ; temp1!=NULL ; temp1=temp1->suivant)
     {
        if(min > temp1->donnee)
        {
           temp3=temp1; // le 3è temporaire est l'adresse de l'élement où se trouve le minimum
           min=temp3->donnee;
        }
     }
     temp3->donnee=temp->donnee; //echange des 2 elements...
     temp->donnee=min;
   }
   return la;
}
