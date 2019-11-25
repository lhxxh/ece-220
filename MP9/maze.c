/*This program is to solve the maze with some functions called createMaze,destroyMaze,printMaze
solveMazeManhattanDFS.createMaze is to allocate memory for maze_t variable and to fill this structure
with appropriate information.destroyMaze is to free the unnessary information in the heap.printMaze is to
print the maze into a human readable maze picture. solveMazeManhattanDFS is to solve the maze.*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE *stream;
    char junk;
    int c,d,i,j;
    maze_t *ptr=(maze_t*)malloc(sizeof(maze_t));   //allocate the memory for maze_t in the heap
    stream=fopen(fileName,"r");                //open the file
    fscanf(stream,"%d %d",&c,&d);
    ptr->width=c;
    ptr->height=d;                             //put width and height information into maze_t structure
    fscanf(stream,"%c",&junk);                 // ignore newline character
    ptr->cells=(char**)malloc(d*sizeof(char*));
    for(i=0;i<d;i++){
    ptr->cells[i]=(char*)malloc(c*sizeof(char));
    }                                               // allocate memory space for cells in the heap
    for(i=0;i<d;i++){
      for(j=0;j<c;j++){
        char ch;
        fscanf(stream,"%c",&ch);
        ptr->cells[i][j] = ch;                   //fill the cell with the appropriate chracter
        if(ptr->cells[i][j]==START){
          ptr->startColumn=j;
          ptr->startRow=i;                      //load start information if found
        }
        if(ptr->cells[i][j]==END){
          ptr->endColumn=j;
          ptr->endRow=i;                       //load end information if found
        }
      }
      fscanf(stream,"%c",&junk);               //discard everyline's newline character
    }
    fclose(stream);                        //close the file
    return ptr;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freedchar **cells_ptr=ptr->cells;
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    if(maze!=NULL){
      if(maze->cells!=NULL){
    free(maze->cells);                 //free the cells
    free(maze);                       //free the structure of maze_t
    }
  }
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j;
    for(i=0;i<maze->height;i++){
      for(j=0;j<maze->width;j++){
        printf("%c",maze->cells[i][j]);       //print every cell
      }
      printf("\n");                       //at the end of each line, print newline character
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

    char **ptr=maze->cells;
    //base case
    if(ptr[row][col]==END)
    return 1;                    //if it is end return 1
    if((row<0)||(col<0)||(row>=maze->height)||(col>=maze->width))
    return 0;                    //if out of bound, return 0
    if((ptr[row][col]==WALL)||(ptr[row][col]==VISITED)||(ptr[row][col]==PATH))
    return 0;                    // if it is not space or start, return 0

    //recursive part
    if(ptr[row][col]!=START)
    ptr[row][col]=PATH;         //put path character into maze
    if(solveMazeManhattanDFS(maze,col+1,row)==1)
    return 1;
    if(solveMazeManhattanDFS(maze,col,row+1)==1)
    return 1;
    if(solveMazeManhattanDFS(maze,col-1,row)==1)
    return 1;
    if(solveMazeManhattanDFS(maze,col,row-1)==1)
    return 1;                  // recursive part

    if(ptr[row][col]!=START)
    ptr[row][col]=VISITED;    //if the recusive part all fails, mark it as visted and return 0
    return 0;
}
