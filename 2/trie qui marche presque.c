/* Fonction de trie*/
liste trie (liste liste_tetra, int nb_rouge, int nb_bleu, int nb_vert, int min_rouge){

    liste   copie;

    copie = NULL;

    
    
    while( liste_tetra != NULL){
        if ((nb_rouge >= liste_tetra->nb_rouge)){
    copie = ajout_liste (liste_tetra->tetra, copie, 
            liste_tetra->nb_rouge, liste_tetra->nb_bleu, liste_tetra->nb_vert);
   
    }
     liste_tetra = liste_tetra->suivant;
    }
    return(copie);
}
