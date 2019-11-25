/*This code is to write three functions that are used to
play the game of life. These three functions have their
own duty to do their work. CountLiveNeighbor is to calculate
the number of neighbour of a given cell. UpdateBoard is to
update to a new version of grid. aliveStable is to check whether
the updated one is the same as the previous one*/






/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int i,j;
int check_row, check_col;
int count=0;
for(i=-1;i<2;i++){
 check_row=i+row;
 if((check_row<0)||(check_row>=boardRowSize))
 continue;                                  /*if the given neighbour's row is less than  or greater than boardRowSize, continue the loop*/
 for(j=-1;j<2;j++){
  check_col=j+col;
  if((check_col<0)||(check_col>=boardColSize))
  continue;                              /*if the given neighbour's row is less than or greater than boardColSize, continue the loop*/
	 if((i==0) && (j==0))
	  continue;                         /*if it is the value itself, continue the loop*/
		 count += board[check_row*boardColSize+check_col];
 }                                    /*increment the count if the given neighbour is alive*/
}
return count;                       /*return count number*/
                                      }
/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
int copy_board[boardRowSize*boardColSize];
int i,j,w;
for(i=0;i<boardRowSize;i++){
	for(j=0;j<boardColSize;j++){
	  copy_board[i*boardColSize+j]=board[i*boardColSize+j];    /*copy the board to copyboard*/
  }
	}
	for(i=0;i<boardRowSize;i++){
		for(j=0;j<boardColSize;j++){
      w = countLiveNeighbor(copy_board,boardRowSize,boardColSize,i,j);
			if(((w==2)||(w==3))&& (copy_board[i*boardColSize+j]==1))    /*if the given alive value has two or three neighours alive, it will still be alive*/
       board[i*boardColSize+j]=1;
       else if((w==3)&& (copy_board[i*boardColSize+j]==0))   /*if the given dead value has three neighours alive, it will be alive next time*/
       board[i*boardColSize+j]=1;
       else                                  /*in any other cases, the given value will be dead*/
       board[i*boardColSize+j]=0;
			}
			}

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){
int copy_board[boardRowSize*boardColSize];
int i,j,flag;
for(i=0;i<boardRowSize;i++){
	for(j=0;j<boardColSize;j++)
	  copy_board[i*boardColSize+j]=board[i*boardColSize+j];   /*copy the board to copy_board*/
	}
	updateBoard(copy_board,boardRowSize,boardColSize);    /*update the copy_board*/
	flag = 1;                               /*assume the updated copyboard is the same as unupdated board*/
	for(i=0;i<boardRowSize;i++){
		for(j=0;j<boardColSize;j++){
	    if(board[i*boardColSize+j] != copy_board[i*boardColSize+j]){
				flag=0;
				break;                   /*in any case if the number in the board is not the same as the number in the updated one, break the whole loop and set the flag to 0*/
			}
}
if(flag==0)
break;
}

if(flag==0)            /*if the flag is 0, return 0*/
return 0;
else          /*if the flag is 1, return 1*/
return 1;
}
