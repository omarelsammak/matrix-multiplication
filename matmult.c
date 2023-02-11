#include<stdlib.h>

#include<pthread.h>



#define Item(X, I, J, NCOL)      X[((J) + (I) * (NCOL))]

//omar ahmed elsammak id 6867

/*

 * matrix multiplication

 *     C = A*B

 *     A has l rows and m cols

 *     B has m rows and n cols

 *     C has l rows and n cols

 */

typedef struct  

{   int *A,*B,*C,l,m,n,i,j;

    /* data */

}arguments; // struct for arguments to be given in pthread create





arguments* argument_plug(int*A,int*B,int*C,int l,int m,int n,int i,int j){ // intializint struct contents to send them as an argument

arguments* a = (arguments*)malloc(sizeof(arguments));

    a->A=A;

    a->B=B;

    a->C=C;

    a->l=l;

    a->m=m;

    a->n=n;

    a->i=i;//row

    a->j=j;//col

    return a;

}



void matmult(int* A, int* B, int* C, int l, int m, int n)

{

    for(int i=0; i<l; i++)

        for(int j=0; j<n; j++)

        {

            int sum = 0;

            for(int k=0; k<m; k++)

                sum += Item(A, i, k, m) * Item(B, k, j, n);

            Item(C, i, j, n) = sum;

        }

}





/*

 * matrix multiplication

 *     C = A*B

 *     A has l rows and m cols

 *     B has m rows and n cols

 *     C has l rows and n cols

 */

void* version1(void *a){

    

    arguments* a1=(arguments*) a;//casting a to type argument as struct 

            int sum = 0;

            for(int k=0; k<a1->m; k++)

                sum += Item(a1->A, a1->i, k, a1->m) * Item(a1->B, k, a1->j, a1->n);

            Item(a1->C, a1->i, a1->j, a1->n) = sum;

    pthread_exit(0);//return

    

}



void matmult_v1(int* A, int* B, int* C, int l, int m, int n)

{   pthread_t thread1[l*n];//array of threads containig count of output matrix 

    arguments* a;

    for(int i=0; i<l; i++)

        for(int j=0; j<n; j++)

        {   a=argument_plug(A,B,C,l,m,n,i,j); // initializing a with all arguments

            pthread_create( &thread1[j+(i*n)], NULL,version1, (void*) a);//thread create

            

        }

    for(int i=0; i<l; i++)

        for(int j=0; j<n; j++){

            pthread_join( thread1[j+(i*n)], NULL);//wait for all threads to finish excution 

        }

    

}





void* version2(void* a){



 arguments* a1=(arguments*) a;//casting a to type argument as struct 

            

        for(int j=0; j<a1->n; j++)

        {   int sum = 0;

            for(int k=0; k<a1->m; k++){

                sum += Item(a1->A, a1->i, k, a1->m) * Item(a1->B, k, j, a1->n);

            }

             Item(a1->C, a1->i, j, a1->n) = sum;

            }

           

    pthread_exit(0);//return

    

     

}

/*

 * matrix multiplication

 *     C = A*B

 *     A has l rows and m cols

 *     B has m rows and n cols

 *     C has l rows and n cols

 */

void matmult_v2(int* A, int* B, int* C, int l, int m, int n)

{ 

    pthread_t thread1[l];//array of threads containig count of rows in matrix 

    arguments* a;

    for(int i=0; i<l; i++){

        a=argument_plug(A,B,C,l,m,n,i,0);

        pthread_create( &thread1[i], NULL,version2, (void*) a); //thread create

            }

        

    for(int i=0; i<l; i++)

        pthread_join( thread1[i], NULL);//wait for all threads to finish excution 



       

}





