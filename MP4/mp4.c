/*This code is to print out all semiprimes within a range given
by the user. We use the main funtion to call the print_semiprimes
functions, which includes the is_print function to judge the specif
number is a prime number, to reach the goal.*/

#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);             /*ask the user to decide the range*/
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }            /*in the case user put negative numbers, print out error message*/

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }          /*in the case user does not put number in ascending order,
              print out error message*/

   print_semiprimes(a,b) ;                       /*call funtion print_semiprimes*/
   return 0;
          }


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{ int i, flag_two=0;
  for(i=2;i<number;i++){      /*set the loop to check whether it is a prime number*/
  if(number%i==0){
  flag_two=1;           /* in the case it is not a prime number, set the flag to 1*/
  break;    }
                       }
  if (flag_two==1)
  return 0;            /* if it is not a prime number,return 0 */
  else
  return 1;          /* if it is a prime number return 1*/

}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{int n, flag_one=0;
 for(n=a;n<=b;n++){          /*set the loop of range, which decides where to start and end*/
 int k;
 for(k=2;k<n;k++){          /*set the loop of checking to check the given number is a semiprime*/
 is_prime(k);
 if((is_prime(k)==1)&&(n%k==0)){
         /*if the first element is a prime number and check whether the second is also a prime*/
 int r;
 r=n/k;
 if(r<k)
 break;
 is_prime(r);
 if(is_prime(r)==1){
 printf("%d ",n);
 flag_one=1;       }
    /* in the case two numbers are all prime numbers, print out n and set the flag to */
                             }
                 }
                  }
printf("\n");            /*add a new line*/
if(flag_one==1)
return 1;        /*if there is semiprime in the given range, return 1*/
else
return 0;       /*if there is no semiprime in the given range, return 2*/
}
