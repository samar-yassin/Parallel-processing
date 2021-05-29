#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc , char * argv[])
{
    int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
    int upper = 25;
    int lower = 8;

	MPI_Status status;	/* return status for 	*/
				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if( my_rank == 0)
	{
        int globalSum=0;
        int i = 0;

        float r = (upper-lower)/(p-1);
        
        if(((upper-lower)%(p-1))!=0) r+=1;
        
        for (i = 1 ; i < p ; i++){
          MPI_Send (&r , 1 ,MPI_FLOAT, i , 0 , MPI_COMM_WORLD );
          MPI_Send (&lower , 1 ,MPI_INT, i , 0 , MPI_COMM_WORLD );
            
        }

        
        for (i = 1 ; i < p ; i++){
          int subSum;
          MPI_Recv(&subSum , 1 ,MPI_INT,i,0,MPI_COMM_WORLD, &status);
          globalSum += subSum;
        }
        printf("Total number of prime numbers is: %d\n",globalSum );
     
	}else
	{
        
   
    float r;
    int lower;
    int a;
    int b;
    int i = 0;
    int j = 0;
    int count=0;
    int localSum = 0;
    
    MPI_Recv(&r , 1 , MPI_FLOAT , 0 , 0 , MPI_COMM_WORLD, &status);
    MPI_Recv(&lower , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD, &status);
    
    a = (lower+(my_rank-1)*r);
    b = (lower+(my_rank-1)*r)+(r-1);
    if(b>upper) b=upper;
    
    for(j=a ; j<=b ; j++){
        if (j <= 1){
            continue;
        }
        int m = j/2;
        count+=1;
           
        
    for (i = 2; i <= m; ++i){
       
        if (j% i == 0){
            count-=1;

            break;
        }
     
    }
    }
    printf("Total number of prime numbers in P%d is: %d\n", my_rank,count );
    
    MPI_Send (&count , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
       
	}

	/* shutdown MPI */
	MPI_Finalize();
    return 0;
}
