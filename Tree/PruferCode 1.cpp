#include<stdio.h>
int main()
{
    int i, j, canh, min, n;
    scanf("%d",&canh);                        
    int edge[canh][2], peak[canh+1] = {0};
   		for(i = 0; i < canh; i++) {
            scanf("%d",&edge[i][0]);
      		scanf("%d",&edge[i][1]);
      		peak[edge[i][0]]++;
      		peak[edge[i][1]]++;               
                                  }
    printf("Ma Prufer code cua cay la : ");
   		for(i = 0; i < canh-1; i++) {                               
      		min = 1000; 
      			for(j = 0; j < canh; j++) {                         
         			if(peak[edge[j][0]] == 1) {
            		    if(min > edge[j][0] && edge[j][0]!=0) {
              		        min = edge[j][0];
               		        n = j;
           							                          }
        								      }
                    if(peak[edge[j][1]] == 1) {
                        if(min > edge[j][1] && edge[j][1]!=0) {
                            min = edge[j][1];
                            n = j;
                                                             }
                                              }
                                          }
        peak[edge[n][0]]--; 
        peak[edge[n][1]]--; 
            if(min==edge[n][0])
                printf("%d ",edge[n][1]);
            else
                printf("%d ",edge[n][0]);
                                    }
    return 0;
}


