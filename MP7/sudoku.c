#include "sudoku.h"
/*This code is used to solve sudoku and it can be realized by several imporatnat functions
called solve_sudoku,is_val_valid,is_val_in_col,is_val_in_row and is_val_in_3x3_zone. Each of them has its own duty.
is_val_in_row is to make sure there is no repeted number in the desired row. is_val_in_col is to make sure
there is no repeted number in the desired column.is_val_in_3x3_zone is to make sure there is no repeted number
in the 3*3 zone. is_val_valid is to combine the three functions above to make sure no instances described in the three
above functions occuring. And the solve_sudoku is the main funtion to solve sudoku */
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int j, flag;
  flag=0;                       /*set the flag to zero and assume there is no repeted number in the desired row.*/
  for(j=0;j<9;j++){
    if(sudoku[i][j]==val)
    flag=1;                /*check each element in the desired row, if the repeted number exists, then set the flag to 1.*/
  }

  if(flag==0)
  return 0;        /*if there is no repeted number, return 0.*/
  else
  return 1;      /*if the repeted number exists, return 1*/
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int i, flag;
  flag=0;             /*set the flag to zero and assume there is no repeted number in the desired column.*/
  for(i=0;i<9;i++){
    if(sudoku[i][j]==val)
    flag=1;        /*check each element in the desired column, if the repeted number exists, then set the flag to 1.*/
  }

  if(flag==0)
  return 0;          /*if there is no repeted number, return 0.*/
  else
  return 1;        /*if the repeted number exists, return 1*/

  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int i_new, j_new, a, b,flag;
  i_new=(i/3)*3;
  j_new=(j/3)*3;            /*get the left top coordinate i and j, which is used to check each elements in desired 3*3 zone*/
  flag=0;                   /*set the flag to zero and assume there is no repeted number in the desired 3*3 zone.*/
  for(a=0;a<3;a++){
    for(b=0;b<3;b++){
      if(sudoku[i_new+a][j_new+b]==val)
      flag=1;        /*check each element in the desired 3*3zone, if the repeted number exists, then set the flag to 1.*/
    }
  }

  if(flag==0)
  return 0;          /*if there is no repeted number, return 0.*/
  else
  return 1;          /*if the repeted number exists, return 1*/
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if((is_val_in_col(val,j,sudoku)==1)||(is_val_in_row(val,i,sudoku)==1)||(is_val_in_3x3_zone(val,i,j,sudoku)==1))
  return 0;            /* in the case that any row, column or 3*3 zone has repeted number, return 0*/
  else
  return 1;         /*in any other circumstances, return 1*/
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
int i,j,flag,a,b;
flag=1;                        /*set the flag to 1 and assume every space has been filled with number 1-9*/
 for(i=0;i<9;i++){
   for(j=0;j<9;j++){
     if((sudoku[i][j]<1)||(sudoku[i][j]>9)){
       flag=0;              /*if any space is not filled with number 1-9, then set the flag to 0*/
       break;             /*break the for loop in the case of space is not filled with number 1-9*/
     }
   }
   if(flag==0)
   break;          /*if any space is not filled with number 1-9, break the for loop*/
 }

if(flag==1)         /*if the flag is 1, every space has been filled, then return true.*/
return true;

else{
  for(a=1;a<10;a++){
    b=is_val_valid(a,i,j,sudoku);   /*in the other case, check the desired space can be filled.*/
    if(b==1){
    sudoku[i][j]=a;             /*in the case it can be filled with a, fill it first.*/
    if(solve_sudoku(sudoku))   /*use recursion to check.*/
    return true;              /*if recursion is true, then return true.*/
    sudoku[i][j]=0;          /*if recursion is not true, set the desired space with 0.*/
    }
  }
return false;          /*return false if the for loop has been terminated.*/
}
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
