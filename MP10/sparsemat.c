#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
//This code is to implement several functions which are quite important to
//solve the matrix, which are loadfiles,gv_lils,set,and others. Each of them has
//own responsibility. load is to read the files, set is to setup the matrix, find is
//to find the specific value in the matrix and so on.
void add_rownode(sp_lils_row_node **list, int row);
void remove_rownode(sp_lils_row_node **head,int row);
void add_colnode(sp_lils_col_node **list, int col);
void remove_colnode(sp_lils_col_node **head,int col);
sp_lils_row_node *find_rownode(sp_lils_row_node *head, int row);
sp_lils_col_node *find_colnode(sp_lils_col_node *head, int col);

sp_lils * load_lils(char* input_file)
{
FILE *stream;
sp_lils *ptr=(sp_lils*)malloc(sizeof(sp_lils));
stream=fopen(input_file,"r");
int m,n;
fscanf(stream,"%d %d",&m,&n);
ptr->m=m;
ptr->n=n;
ptr->nz=0;
ptr->row_list_head=NULL;               //set up all necessary functions
int i,j;
double value;
while (feof(stream)!=0) {
  fscanf(stream,"%d %d %lf",&i,&j,&value);         //read the file and call set to set up
  set_lils(ptr,i,j,value);
}
fclose(stream);                            //when reach the end of file,close the file
    return ptr;
}


double gv_lils(sp_lils * mat_l,int row,int col)
{
sp_lils_row_node *rowhead=mat_l->row_list_head;
sp_lils_row_node* row_ptr=find_rownode(rowhead,row);
if(row_ptr==NULL)
return 0;                                          // find the row number
sp_lils_col_node *colhead=row_ptr->col_list_head;
sp_lils_col_node *col_ptr=find_colnode(colhead,col);
if(col_ptr==NULL)
return 0;                                //find column number

    return col_ptr->value;   //return the value if found
}



void set_lils(sp_lils * mat_l, int row, int col, double value)
{
sp_lils_row_node *row_head=mat_l->row_list_head;
add_rownode(&row_head,row);
mat_l->row_list_head=row_head;
sp_lils_row_node* row_ptr=find_rownode(row_head,row);
sp_lils_col_node* col_head=row_ptr->col_list_head;
add_colnode(&col_head,col);
row_ptr->col_list_head=col_head;
sp_lils_col_node* col_ptr=find_colnode(col_head,col);//give all the condition to set

if(value==0){
  remove_colnode(&col_head,col);
  row_ptr->col_list_head=col_head;
  if(col_head==NULL){
    remove_rownode(&row_head,row);  //in the case of 0, remove the node
    mat_l->row_list_head=row_head;
  }
}

else
  col_ptr->value=value;
  mat_l->nz+=1;                           //else set the condition
    return;
}

void save_lils(char * file_name,sp_lils * mat_l)
{
  FILE *stream;
  stream=fopen(file_name,"w");
  fprintf(stream,"%d %d\n",mat_l->m,mat_l->n);
  sp_lils_row_node* row_ptr=mat_l->row_list_head;
  while(row_ptr!=NULL){
    sp_lils_col_node*col_ptr=row_ptr->col_list_head;
  while(col_ptr!=NULL){
    fprintf(stream,"%d %d %f\n",row_ptr->idx_r,col_ptr->idx_c,col_ptr->value);
    col_ptr=col_ptr->next;
  }
    row_ptr=row_ptr->next;
  }
	return;                       //save the lils in to the file given by the name
}


sp_lils * add_lils(sp_lils * matA, sp_lils * matB){
sp_lils*matC=(sp_lils*)malloc(sizeof(sp_lils));
int A,B,C,D,row,col;
A=matA->m;
B=matA->n;
C=matB->m;
D=matB->n;
if((A!=C)||(B!=D))
return NULL;
else
matC->m=A;
matC->n=B;                              //set up the condition
matC->nz=0;
matC->row_list_head=NULL;

sp_lils_row_node* Arow_ptr=matA->row_list_head;
while(Arow_ptr!=NULL){
  row=Arow_ptr->idx_r;
  sp_lils_col_node*Acol_ptr=Arow_ptr->col_list_head;
while(Acol_ptr!=NULL){
  col=Acol_ptr->idx_c;
  set_lils(matC,row,col,Acol_ptr->value);
  Acol_ptr=Acol_ptr->next;
}
  Arow_ptr=Arow_ptr->next;
}                                          //matrix A conditon

sp_lils_row_node* Brow_ptr=matB->row_list_head;
while(Brow_ptr!=NULL){
  row=Brow_ptr->idx_r;
  sp_lils_col_node*Bcol_ptr=Brow_ptr->col_list_head;
while(Bcol_ptr!=NULL){
  col=Bcol_ptr->idx_c;
  double Cnumber,Bnumber;
  Bnumber=Bcol_ptr->value;
  Cnumber=gv_lils(matC,row,col);      //matrix B condition

  set_lils(matC,row,col,Cnumber+Bnumber);

  Bcol_ptr=Bcol_ptr->next;
}
  Brow_ptr=Brow_ptr->next;
}
	return matC;
}


void destroy_lils(sp_lils * mat_l){
  sp_lils_row_node* row_ptr=mat_l->row_list_head;
  sp_lils_row_node* row_pre_ptr;
  while(row_ptr!=NULL){
    row_pre_ptr=row_ptr;
    row_ptr=row_ptr->next;
    sp_lils_col_node* col_ptr=row_pre_ptr->col_list_head;
    sp_lils_col_node* col_pre_ptr;
  while(col_ptr!=NULL){
    col_pre_ptr=col_ptr;
    col_ptr=col_ptr->next;
    free(col_pre_ptr);
  }
    free(row_pre_ptr);            //free all the component
  }
    return;
}

void add_rownode(sp_lils_row_node **list, int row)
{
	sp_lils_row_node *current = *list;
	sp_lils_row_node *prev = *list;
	sp_lils_row_node *temp = (sp_lils_row_node *)malloc(sizeof(sp_lils_row_node)); //allocate memory for the new node
	temp->idx_r=row ; //initialize UIN for the new node
 int flag=0;
	//keep traversing the list until we reach the end
	while(current != NULL)
	{
		//the first instance when row is smaller than current idx_r
		//we want to insert new node in front of the current node
    flag=1;
    if(current->idx_r==row)
    return;

    if(row < current->idx_r)
		{
			temp->next = current;
			if(current == *list) //if the current node is the head, update head pointer
			  {	*list = temp;}
			else //for everything else, update previous node's next pointer
			  {prev->next = temp;}
			return; //exit function
		}

		//new node will have to be inserted at the tail
		if(current->next == NULL)
		{
			current->next = temp;
			temp->next = NULL;
		}

		prev = current;
		current = current ->next;
	}
  if(flag==0){
    temp->next=NULL;
    *list=temp;
  }
return;
}


void remove_rownode(sp_lils_row_node **head,int row)
{
	sp_lils_row_node *prev;
	sp_lils_row_node *current = *head;

	while(current != NULL) //find the record with matching UIN
	{
		if(current->idx_r == row)
			break;
		prev = current;
		current = current->next;
	}

	if(current == NULL) //if record is not found, return out
		return;

	if(current == *head) //if record is the first node, update head pointer
	{
		*head = current->next;
	}
	else if(current->next == NULL) //if record is the last note, set the previous node point to NULL
	{
		prev->next = NULL;
	}
	else //record found is in the middle of the list
	{
		prev->next = current->next;
	}

	free(current);
  return;
}

void add_colnode(sp_lils_col_node **list, int col)
{
	sp_lils_col_node *current = *list;
	sp_lils_col_node *prev = *list;
	sp_lils_col_node *temp = (sp_lils_col_node *)malloc(sizeof(sp_lils_col_node)); //allocate memory for the new node
	temp->idx_c=col ; //initialize UIN for the new node
  int flag=0;
	//keep traversing the list until we reach the end
	while(current != NULL)
	{
		//the first instance when row is smaller than current idx_r
		//we want to insert new node in front of the current node
    flag=1;
    if(current->idx_c==col)
    return;

		if(col < current->idx_c)
		{
			temp->next = current;
			if(current == *list) //if the current node is the head, update head pointer
			  {	*list = temp;}
			else //for everything else, update previous node's next pointer
			  {prev->next = temp;}
			return; //exit function
		}

		//new node will have to be inserted at the tail
		if(current->next == NULL)
		{
			current->next = temp;
			temp->next = NULL;
		}

		prev = current;
		current = current ->next;

	}
  if(flag==0){
    temp->next=NULL;
    *list=temp;
  }
return;
}

void remove_colnode(sp_lils_col_node **head,int col)
{
	sp_lils_col_node *prev;
	sp_lils_col_node *current = *head;

	while(current != NULL) //find the record with matching UIN
	{
		if(current->idx_c == col)
			break;
		prev = current;
		current = current->next;
	}

	if(current == NULL) //if record is not found, return out
		return;

	if(current == *head) //if record is the first node, update head pointer
	{
		*head = current->next;
	}
	else if(current->next == NULL) //if record is the last note, set the previous node point to NULL
	{
		prev->next = NULL;
	}
	else //record found is in the middle of the list
	{
		prev->next = current->next;
	}

	free(current);
  return;
}

sp_lils_row_node *find_rownode(sp_lils_row_node *head, int row)
{
	if(head->idx_r == row){
		return head;
	}
	else if((head == NULL) || (head->idx_r > row)){
		return NULL;
	}
	else
		return find_rownode(head->next, row);
}

sp_lils_col_node *find_colnode(sp_lils_col_node *head, int col)
{
	if(head->idx_c == col){
		return head;
	}
	else if((head == NULL) || (head->idx_c > col)){
		return NULL;
	}
	else
		return find_colnode(head->next, col);
}
