#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc , char * argv[])
{
  int my_rank;		/* rank of process	*/
  int p;			/* number of process	*/
  int i;
  int* arr;
  float globalSum = 0;
  float localSum = 0;
  float localSumOfSquaredDifferences =0;
  float globalSumOfSquaredDifferences =0;
  float globalmean;
  float sDeviation=0;
  int n;

  
  
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
        printf("Enter an integer: ");
        scanf("%d", &n);
        
    }

    MPI_Bcast(&n , 1 , MPI_INT, 0,MPI_COMM_WORLD);
    

  

    if( my_rank != 0)
  {
    int i=0;
    int x;
    arr =  malloc (n * sizeof (int));
    for( i = 0; i<n; i++){
        x=rand()%20;
        arr[i]=x;
        localSum+=x;
        
    }
    
        printf("rank %d: ",my_rank);

    for( i=0;i<n;i++){
             printf("%d ,",arr[i]);
   
    }

    printf("\n");

  
  }
  
   MPI_Allreduce(&localSum,&globalSum,1,MPI_FLOAT,MPI_SUM,MPI_COMM_WORLD);
  
   
   
   if(my_rank!=0){
       float num;
       globalmean = globalSum /(n * (p-1));
       
    for( i = 0; i<n; i++){
       num = pow((arr[i]-globalmean),2);
       localSumOfSquaredDifferences+=num;
    }
    localSumOfSquaredDifferences= localSumOfSquaredDifferences/n;
    }
    
    MPI_Bcast(&globalmean , 1 , MPI_FLOAT, 1,MPI_COMM_WORLD);
    MPI_Reduce(&localSumOfSquaredDifferences,&globalSumOfSquaredDifferences,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

       
  
 if (my_rank == 0 ){
        sDeviation =sqrt(globalSumOfSquaredDifferences/(p-1));
        printf("\nglobalSum= %f ,globalmean= %f ,globalSumOfSquaredDifferences= %f\n",globalSum,globalmean,globalSumOfSquaredDifferences);
        
        printf("\nStandard Deviation= %f \n",sDeviation);
  }
	/* shutdown MPI */
	MPI_Finalize();
    return 0;
}
