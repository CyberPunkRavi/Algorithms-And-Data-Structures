/*********************
M Ravi Kumar 
CS18MTECH11028
CSE IITH 
ADSA Assignment 3
*********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

// Maximum stack size 
#define MAX_SIZE 100 
#define ONE 1
static int id = 0;              /* Genarate Id for Each Employee*/
double  max_sum = 0;       
typedef struct Node_ {
    struct Node_ *left_child;   /* left child */
    struct Node_ *right_sib;    /* right Sibling */
    struct Node_ *parent;       /* parent */
    char name[50];              //Name 
    double rating;              //conviviality rating
    int emp_id;                 //emp id
} Node;
Node *root = NULL;
/*#####################################
#	Stack Implimentation for           #
#	Tree Traversal		                 #		
######################################*/
struct Stack 
{ 
    int size; 
    int top; 
    Node* *array; 
}; 
// A utility function to create a stack of given size 
struct Stack* createStack(int size) 
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
    stack->size = size; 
    stack->top = -1; 
    stack->array = (Node**) malloc(stack->size * sizeof(Node*)); 
    return stack; 
}
// BASIC OPERATIONS OF STACK 
int isFull(struct Stack* stack) 
{  return stack->top - 1 == stack->size; } 
  
int isEmpty(struct Stack* stack) 
{  return stack->top == -1; } 
  
void push(struct Stack* stack, Node* node) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = node; 
} 
  
Node* pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return NULL; 
    return stack->array[stack->top--]; 
} 
  
Node* peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return NULL; 
    return stack->array[stack->top]; 
}
/*#####################################
#	END           #
#	              #		
######################################*/  

/* New Node Creation */
Node *newNode(char  cur_name[],double rating){
  //printf("Statement newNode in fun\n");
  Node *x;
  if ((x = malloc (sizeof(*x))) == 0) {
        printf ("insufficient memory (insertNode)\n");
        exit(1);
    }
  strcpy(x->name, cur_name);
  x->rating = rating;
  x->left_child = NULL;
  x->right_sib = NULL;
  x->parent = NULL;
  x->emp_id = id;
  id++;
  //printf("Sucsses in newNode in fun\n");
  return x; 
}
/*   End of Node Creation     */


/* Finding parent node for insertion of New Node in Tree*/
Node *find_parent(char  name[],Node *root){
  //printf("Statement find_parent in fun %s\n",root->name);
  /*****Recursive
  if (root != NULL) {
  	//char pr[50];
  	//strcpy(pr,root->name);
	//printf("Parent Name of child %s \n",pr);
  	if(strcmp(name, root->name)==0){
  	    	printf(" inIf Statement \n");
		return root;
	  }
	else {    
    printf(" in else Statement \n");
    Node* ele = find_parent(name,root->left_child);
    if(ele == NULL) 
      return find_parent(name,root->right_sib);
    else return ele;
    }
  }
  return NULL;
  ********************/ 
    struct Stack* stack = createStack(MAX_SIZE); 
    do
    { 
        // Move to leftmost node 
        while (root) 
        { 
            // Push root's right child and then root to stack. 
            if (root->right_sib) 
                push(stack, root->right_sib); 
            push(stack, root); 
  
            // Set root as root's left child   
            root = root->left_child; 
        } 
  
        // Pop an item from stack and set it as root     
        root = pop(stack); 
        // If the popped item has a right child and the right child is not 
        // processed yet, then make sure right child is processed before root 
        if (root->right_sib && peek(stack) == root->right_sib) 
        { 
            pop(stack);  // remove right child from stack 
            push(stack, root);  // push root back to stack 
            root = root->right_sib; // change root so that the right  
                                // child is processed next 
        } 
        else  // Else print root's data and set root as NULL 
        { 
          //printf("%d ", root->name);
          if(strcmp(name, root->name)==0)
            return root;
          root = NULL; 
        } 
    } while (!isEmpty(stack));
}
/*** End of Function ****/


/* Adding New child to Tree */
void add_child(char parent_nm[],char cur_name[],double rating){
  //printf("Statement add_child in fun\n");
  if(root == NULL)
    root = newNode(cur_name,rating);
  else{
    Node* parent = find_parent(parent_nm,root); 
    if (parent== NULL)
    	printf("Returning NUll Parent\n");	
    char pr[50];
    strcpy(pr,parent->name);
    //printf("Parent Name of child %s \n",pr);
    Node* child  = newNode(cur_name,rating);
    child->parent = parent;
    parent->left_child = child; 
    //printf("Sucsses add_child in fun\n");
  }
}


/* Adding New sibling to Tree */
void add_sibling(char parent_nm[],char cur_name[],double rating){
    //printf("Statement add_sibling in fun\n");
    Node* parent = find_parent(parent_nm,root);
    char pr[50];
    strcpy(pr,parent->name);
    //printf("Parent Name of child %s \n",pr);
    Node* sibl  = newNode(cur_name,rating);
    sibl->parent = parent->parent;
    parent->right_sib = sibl;
    //printf("Sucsses add_sibling in fun\n"); 
}

/*** Display the Tree ***/
void display(Node *root)
{
	if(root != NULL)
	{
	  printf("\nValues at each node: ");
	  char pr[50];
	  strcpy(pr,root->name);
		printf("Each Node Name %s\n",root->name);
    printf("Each Node Id %d\n",root->emp_id);
		if(root->left_child != NULL)
		printf("Left Child %s\n",root->left_child->name);
		if(root->right_sib != NULL)
		printf("Right Sibling %s\n",root->right_sib->name);
		if(root->parent != NULL)
		printf("Parent %s\n",root->parent->name);
		display(root->left_child);
		display(root->right_sib);
		
	}
	return;
}

int visited[100] = {0};                     //Used for Finding max rating  
double mx_rating[100] = {0};                //Used for Finding max rating  


/** Finding score at each node **/
double score(Node* root){

  //printf("Statement score in fun\n");
  //printf("Current Node Values   %s %d\n",root->name,root->emp_id);
  	
  if(visited[root->emp_id] == ONE)
		return mx_rating[root->emp_id];

  visited[root->emp_id] = ONE;
  //printf("Visited root %d %d\n",root->emp_id,visited[root->emp_id]);
	
  /* Base Case : Node has no child*/ 
  if(root->left_child == NULL){
    mx_rating[root->emp_id] = root->rating;
    return root->rating;
  }

  /**************************
   if current node included 
   **************************/
  double sum1 = root->rating;
  struct Stack* stack = createStack(MAX_SIZE);
  Node* im_child = root->left_child;
  if(im_child->left_child != NULL)
    push(stack,im_child);
  while(im_child->right_sib != NULL &&
           im_child->right_sib->left_child != NULL){
      push(stack, im_child->right_sib);
      //printf("pushing into stak %s\n",im_child->right_sib->name);
      im_child = im_child->right_sib;
  }
  /* Traversing throug Grand child */
  while (!isEmpty(stack)){
    Node * cur = pop(stack);
    //printf("popping stak %s\n",cur->name);
    cur = cur->left_child;
    while(cur != NULL){
      if(visited[cur->emp_id] == ONE)
        sum1 = sum1+mx_rating[cur->emp_id];
      else
        sum1 = sum1 + score(cur);      //Recursive Call
      cur = cur->right_sib;
    }
  }

  /*************************
   If current Node not included
   ***************************/
  double sum2 = 0;
  Node* child = root->left_child;
  /*Traversing through child*/
  while(child != NULL ){
    if(visited[child->emp_id] == ONE)
      sum2 = sum2+mx_rating[child->emp_id];
      else
        sum2 = sum2 + score(child);    //Recursive Call
    child = child->right_sib;
  }

  if(sum1>sum2)
    mx_rating[root->emp_id] = sum1;
  else
    mx_rating[root->emp_id] = sum2;
  return sum1>sum2?sum1:sum2;  	
}

int guests[100] = {0};

/*****************************
Genarating guest list
******************************/
void guest_list(Node* root){
  //printf("Statement guest in fun\n");
  //printf("Node guest in fun %s\n",root->name);
  struct Stack* stack = createStack(MAX_SIZE);
  double sum1 = root->rating;
  Node* im_child = root->left_child;
  if(im_child != NULL){
    if(im_child->left_child != NULL)
      push(stack,im_child);
    while(im_child->right_sib !=NULL &&
            im_child->right_sib->left_child != NULL){
        push(stack, im_child->right_sib);
        im_child = im_child->right_sib;
    }
    while (!isEmpty(stack)){
      Node * cur = pop(stack);
      cur = cur->left_child;
      while(cur != NULL){
        sum1 = sum1+mx_rating[cur->emp_id];
        cur = cur->right_sib;
      }
    }
  }
  //printf("Sum 1 %lf\n",sum1);

  double sum2 = 0;
  Node* child = root->left_child;
  while(child != NULL ){
      sum2 = sum2+mx_rating[child->emp_id];
    child = child->right_sib;
  }

  //printf("Sum 2 %lf\n",sum2);

  if(mx_rating[root->emp_id]== sum1){
    //printf("Guest s are %s\n",root->name);
    guests[root->emp_id]=ONE;
    Node* im_child1 = root->left_child;
    if(im_child1 == NULL)
      return;
    if(im_child1->left_child != NULL)
      push(stack,im_child1);
    while(im_child1->right_sib != NULL &&
            im_child1->right_sib->left_child != NULL){
        push(stack, im_child1->right_sib);
        im_child1 = im_child1->right_sib;
    }
    while (!isEmpty(stack)){
      Node * cur1 = pop(stack);
      cur1 = cur1->left_child;
      while(cur1 != NULL){
        guest_list(cur1);
        cur1 = cur1->right_sib;
      }
    }
  }
  else if(mx_rating[root->emp_id] == sum2){
    Node* child1 = root->left_child;
    while(child1 != NULL ){
      guest_list(child1);
      child1 = child1->right_sib;
    }
  }
}

void print_guest_list(Node * root){
  //printf("Statement Printing guest list in fun\n");
  if(root == NULL)
    return;
  if( guests[root->emp_id] ==1 )
    printf("%s\t",root->name);
  print_guest_list(root->left_child);
	print_guest_list(root->right_sib);
  
}

int main(void) {
  int employee_count;
  printf("Enter total no of employees \n");
  scanf("%d",&employee_count);
  int i;
  for(i=0;i<employee_count;i++){
    printf("Enter 0 for Adding child 1 for Adding sibling \n");
    int choise;
    scanf("%d",&choise);
    if(choise == 1){
      printf("Enter Left sibling Name,Name,rating \n");
      char lft_sib[50];
      char cur_name[50];
      double rating;
      scanf("%s",lft_sib);
      scanf("%s",cur_name);
      scanf("%lf",&rating);
      add_sibling(lft_sib,cur_name,rating);
    }
    else {
      printf("Enter parent Name,Name,rating \n");
      char parent[50];
      char cur_name[50];
      double rating;
      scanf("%s",parent);
      scanf("%s",cur_name);
      scanf("%lf",&rating);
      add_child(parent,cur_name,rating);

    }
 }
 display(root);
 max_sum = score(root);
 printf("Max rating from tree %lf\n",max_sum);
 guest_list(root);
 printf("Guest List \n");
 print_guest_list(root);
 printf("\n");
 
 /****
 for(i=0;i<100;i++){
   //if(guests[i]  == 1)
    printf("%lf ",mx_rating[i]);
 }
 *****/
 return 0;
}