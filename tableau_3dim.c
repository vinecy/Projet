int main (void){
    int c, l, m;
    int tria [2][2][2];
    
    tria[0][0][0] = 1;
    tria[0][1][0] = 2;
    tria[1][0][0] = 3;
    tria[1][1][0] = 4;
    
    tria[0][0][1] = 5;
    tria[0][1][1] = 6;
    tria[1][0][1] = 7;
    tria[1][1][1] = 8;
    
                  
                      

     //back_track_base(0);
     printf("Il ya %i solutions \n",compt);
    
        
                printf("ESsai1\n");          
     	for (l=0; l<K; l++) {              //Afficher les solutions
    	printf("\n");            
            for(c=0; c<K-l; c++) {
                printf("%i ",tria[l][c][0]);
            }
        }
        for (l=0; l<K; l++) {              //Afficher les solutions
    	printf("\n");            
            for(c=0; c<K-l; c++) {
                printf("%i ",tria[l][c][1]);
            }
        }
        printf("\n"); 
        printf("\n");   
        
        printf("ESsai2\n");        
        
        for (l=0; l<K; l++) {
        printf("\n");
           for(m=0; m<K; m++) {
            printf("%i ",tria[l][m][0]);
            }
        }
        for (l=0; l<K; l++) {
        printf("\n");
           for(m=0; m<K; m++) {
            printf("%i ",tria[l][m][1]);
            }
        }
        printf("\n");                 
}
