#include <stdio.h>
#include <math.h>


int main(){
    int n,r;
    
    
    printf("Enter the no. of bits in data (n): ");
    scanf("%d",&n);
    
    char data[n];
    
    printf("Enter the data: ");
    scanf("%s",data);
    
    r = 1;
    while(pow(2,r)<n+r+1){
        r++;
    }
     
    printf("Number of redundant bits: %d\n",r);
    
    
    int pos[r];
    
    for(int i=0;i<r;i++){
        pos[i] = (int)pow(2,i);
    }
    
    for(int i=0;i<r;i++){
        printf("|%d",pos[i]);
    }
    printf("\ndata\n");
    for(int i=0;i<n;i++){
        printf("|%c",data[i]);
    }
    int c=0;
    printf("\n");
    for(int i=0;i<n+r;i++){
        printf("|%d",n+r-i);
        
    }
    printf("\n");
    int cD=0,cP=r-1;
    for(int i=0;i<n+r;i++){
        int p = n+r-i;
        //printf("|%d",p);
        
        if(p==pos[cP]){
            
            printf("|r%d",cP+1); //n+r-i
            cP--;
        }
        else{
            printf("|%c",data[cD++]);
        }
        
    }
    
    int R[r];
    for(int i=0;i<r;i++){
        
    }
    
    printf("\n");
    
    
}
