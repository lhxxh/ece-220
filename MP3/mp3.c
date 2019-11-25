/* This code is to implement a C program to print 
a row in Pascal’s triangle. First the user inputs the row number.
Then the screen will show each element in this row. This can 
be achieved by using for several for loops under different 
conditions*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);                      /*get the rwo number*/

  int n = row;
  if ( (0<=n) && (n<=40) && (n%2==0)) {      /*in the case that the row is odd*/
  n = n/2;                                  
  int k;
  for(k=0; k<=n; k++) {                     /*set the column counter*/
  
    if(k==0) {                                /*in the case that k==0*/
  printf("1 ");
  continue;}
 
  else     {
  long unsigned int a=1;                     /*in the case that k>0*/
  long unsigned int b=1;                    
  long unsigned int c;
  int i;
  
  for(i=1; i<=k; i++) {                     /*set the column counter*/
  a=a*(2*n+1-i);
  b=b*i;               }
  c=a/b;
  printf("%lu ",c);    
           }
 		       }
 
  for(k=n-1; k>=0; k--) {                  /*in the case that column >n/2*/
       
    if(k==0) {                                /*in the case that k==0*/
  printf("1 ");
  continue;}

    else     {                              /*in the case that k>0*/
  long unsigned int a=1;
  long unsigned int b=1;
  long unsigned int c;
  int i;
 
  for(i=1; i<=k; i++) {                     /*print each element*/
  a=a*(2*n+1-i);
  b=b*i;              }
  c=a/b;
  printf("%lu ",c);    
           }            
			}
 				      }				
    
  if ( (0<=n) && (n<=40) && (n%2==1)) {      /*in the case row number is even*/   
  n = n/2;
  int k;
  for(k=0; k<=n; k++) {                     /*set the colomn couter*/
  
  if(k==0) {                               /*in the case k==0*/
  printf("1 ");
  continue;}
 
  else     {                               /*in the case k>=0*/
  long unsigned int a=1;
  long unsigned int b=1;       
  long unsigned int c;
  int i;
  
  for(i=1; i<=k; i++) {                    /*print each element in the row*/
  a=a*(2*n+2-i);
  b=b*i;               }
  c=a/b;
  printf("%lu ",c);    
           }
 		       }
 
  for(k=n; k>=0; k--) {                  /*set the colomn counter*/

    if(k==0) {                            /*in the case k==0*/
  printf("1 ");
  continue;}

  else     {                            /*in the case k>0*/
  long unsigned int a=1; 
  long unsigned int b=1;
  long unsigned int c;
  int i;
 
  for(i=1; i<=k; i++) {                 /*print each element in row*/
  a=a*(2*n+2-i);
  b=b*i;              }
  c=a/b;
  printf("%lu ",c);    
           }            
			}
 				      }	

  printf("\n");                           /*add a new line*/
return 0;

}

