/*This part of code consists of three main functions which are used to
implement a game program. These functions are set_seed, start_game and
make_guess. Set_seed is to provide a seed for srand function. start_game
is to generate four random number. And make_guess is to decide how many
perfect match and how many misplaced match.*/


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */

int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below
int seed, flag;
char post[2];
int result;
result= sscanf(seed_str, "%d%1s", &seed, post); /*decide whether the string is valid with only one interger*/
if(result == 1) {
  srand(seed);
  flag = 1;         /*in the case of valid, use srand to accept seed */
}
else {
  printf("set_seed: invalid seed\n");
  flag = 0;      /*in the case of invalid, print error message on the screen*/

}

if(flag == 1)
  return 1;  /* in the case of valid, return 1*/
else
  return 0;  /* in the case of invalid, return 0*/
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
*one= rand()%8;
*one += 1;
*two= rand()%8;
*two += 1;
*three= rand()%8;
*three += 1;
*four= rand()%8;
*four += 1;               /*generate four random numbers*/
guess_number= 1;    /* set the guess number to 1*/
solution1= *one;
solution2= *two;
solution3= *three;
solution4= *four;  /*copy the solution to static solution1,2,3,4*/
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two,
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
char post[2];
int w,x,y,z, flag;
int result;
int pair_one= 0, pair_two= 0, pair_three= 0, pair_four= 0;
int perfect_mat= 0, misplaced_mat=0;
int guess_one=0, guess_two=0, guess_three=0, guess_four=0;
int solu_one=0, solu_two=0, solu_three=0, solu_four=0;
result= sscanf(guess_str, "%d%d%d%d%1s", &w,&x,&y,&z,post);
*one= w;
*two= x;
*three = y;
*four = z;         /*store the guessed value as outputs*/

if((result == 4) && (w>0) && (9>w) && (x>0) && (9>x) && (y>0) && (9>y) && (z>0) && (9>z)){
if(w == solution1){
  perfect_mat += 1;
  pair_one = 1;
}                             /*check if the first number is perfectly matched*/
if(x == solution2){
  perfect_mat += 1;
  pair_two = 1;
}                        /*check if the second number is perfectly matched*/
if(y == solution3){
  perfect_mat += 1;
  pair_three = 1;
}                     /*check if the third number is perfectly mathced*/
if(z == solution4){
  perfect_mat += 1;
  pair_four = 1;
}                   /*check if the fourth number is perfectly matched*/
if(pair_one != 1){
  if((w == solution2) && (pair_two != 1)&& (guess_one != 1) && (solu_two != 1)){
  misplaced_mat += 1;
  guess_one = 1;
  solu_two =1;   }
  if((w == solution3) && (pair_three != 1)&& (guess_one != 1) && (solu_three != 1)){
  misplaced_mat += 1;
  guess_one = 1;
  solu_three = 1;}
  if((w == solution4) && (pair_four != 1)&& (guess_one != 1) && (solu_four != 1)){
  misplaced_mat += 1;
  guess_one = 1;
  solu_four = 1;}
}                 /*search for the misplaced match using the first number if it is not perfectly matched*/
if(pair_two != 1){
  if((x == solution1) && (pair_one != 1)&& (guess_two != 1)&& (solu_one != 1)){
  misplaced_mat += 1;
  guess_two = 1;
  solu_one = 1; }
  if((x == solution3) && (pair_three != 1)&& (guess_two != 1)&& (solu_three != 1)){
  misplaced_mat += 1;
  guess_two = 1;
  solu_three = 1;}
  if((x == solution4) && (pair_four != 1)&& (guess_two != 1)&& (solu_four != 1)){
  misplaced_mat += 1;
  guess_two = 1;
  solu_four = 1;}
}               /*search for the misplaced match using the second number if it is not perfectly matched*/
if(pair_three != 1){
  if((y == solution1) && (pair_one != 1)&& (guess_three != 1)&& (solu_one != 1)){
  misplaced_mat += 1;
  guess_three = 1;
  solu_one = 1;}
  if((y == solution2) && (pair_two != 1)&& (guess_three != 1)&& (solu_two != 1)){
  misplaced_mat += 1;
  guess_three = 1;
  solu_two = 1;}
  if((y == solution4) && (pair_four != 1)&& (guess_three != 1)&& (solu_four != 1)){
  misplaced_mat += 1;
  guess_three = 1;
  solu_four = 1;}
}              /*search for the misplaced match using the third number if it is not perfectly matched*/
if(pair_four != 1){
  if((z == solution2) && (pair_two != 1)&& (guess_four != 1)&& (solu_two != 1)){
  misplaced_mat += 1;
  guess_four = 1;
  solu_two = 1; }
  if((z == solution3) && (pair_three != 1)&& (guess_four != 1)&& (solu_three != 1)){
  misplaced_mat += 1;
  guess_four = 1;
  solu_three = 1;}
  if((z == solution1) && (pair_one != 1)&& (guess_four != 1)&& (solu_one != 1)){
  misplaced_mat += 1;
  guess_four = 1;
  solu_one = 1;}
}            /*search for the misplaced match using the fouth number if it is not perfectly matched*/
flag = 1;
}
else
flag = 0;

if(flag==1){
  printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number,perfect_mat,misplaced_mat);
  guess_number += 1;
  return 1;
}           /*in the case of valid, print the number of perfect matched number and misplace mathced number and increment guess number and finally return 0*/
else{
printf("make_guess: invalid guess\n");
  return 0;
}  /*in the case of invalid, print the error message and return 0 without incrementing guessed number*/
}
