// 5/01/16


// Fonction pour créer le pointeur sur tableau

int ***createTable(int nbLin, int nbCol, int nbNiv){
int ***niveau;
int j, k1;
 
/* Allocation de la 1er dimension: lignes */
    niveau = (int ***)malloc ( sizeof(int **)  *  nbLin);
    
/* Allocation 2e dimension: colonnes */
    for ( j = 0 ; j < nbLin ; j++){
        niveau[j] = (int **)malloc (sizeof(int*) * nbCol);
    }
    
/*Allocation 3eme dimension : niveau*/  
    for ( j = 0 ; j < nbLin ; j++){  
        for ( k1 = 0 ; k1 < nbCol ; k1++){
            niveau[j][k1] = (int *)malloc (sizeof(int) * nbNiv);
        }
    }    
}
