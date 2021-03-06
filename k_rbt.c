/* red-black tree */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef int T;                  /* type of item to be stored */
#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)

static int k =2;
/* Red-Black tree description */
typedef enum { BLACK, RED } nodeColor;

typedef struct Node_ {
    struct Node_ *left;         /* left child */
    struct Node_ *right;        /* right child */
    struct Node_ *parent;       /* parent */
    nodeColor color;            /* node color (BLACK(0), RED(0)) */
    T data;                     /* data stored in node */
} Node;

#define NIL &sentinel           /* all leafs are sentinels */
Node sentinel = { NIL, NIL, 0, BLACK, 0};

Node *root = NIL;               /* root of Red-Black tree */
Node *k_root = NIL;
int is_left ;
void display(Node *root);
void rotateLeft(Node *x) {

   /**************************
    *  rotate node x to left *
    **************************/

    Node *y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    /* establish y->parent link */
    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        root = y;
    }

    /* link x and y */
    y->left = x;
    if (x != NIL) x->parent = y;
}

void rotateRight(Node *x) {

   /****************************
    *  rotate node x to right  *
    ****************************/

    Node *y = x->left;

    /* establish x->left link */
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;

    /* establish y->parent link */
    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        root = y;
    }

    /* link x and y */
    y->right = x;
    if (x != NIL) x->parent = y;
}

int is_k_red_conflict(Node *x) {
  int ct=k;
  Node* cur = x;
  while ( (cur->parent != NIL) && cur->parent->color != 0  ){
	    ct--;
	    printf("\nK value for a node %d ",ct);
	    if(ct == 0){
	        is_left = (cur == cur->parent->left)?1:0;
	    }
	    if(ct == 0){
	      k_root = cur->parent;
	      break;
	    }
	    cur=cur->parent;  	      
	}
	 	 	
	if(ct <=0){
	 printf("\n K red conflit");
	 printf("\n ----K root red conflit:%d",k_root->data);
       printf("\n ----K root left child :%d",is_left);
	 return 1;
	 
	
	}
	else{
	printf("\n No K red conflit");
	return 0;
	}
}

void insertFixup(Node *x) {

   /*************************************
    *  maintain Red-Black tree balance  *
    *  after inserting node x           *
    *************************************/

    /* check Red-Black properties */

    while (x != root && is_k_red_conflict(x)) {
        /* we have a violation */
        
        //k_root has single child then do rotations
         printf("\nInsertion fixing up");
        if(k_root->right==NIL || k_root->left==NIL ){
             
             if(k_root->left==NIL)
              rotateLeft(k_root);
             else 
              rotateRight(k_root);
               
        }
        //make coloring and rotations
        else {
		  if (k_root == k_root->parent->left ) {
		 
		      Node *y = k_root->parent->right;
		      if (y->color == RED) {

		          /* k_root sibling is RED */
		          k_root->color = BLACK;
		          y->color = BLACK;
		          k_root->parent->color = RED;
		          x = k_root->parent;
		      } else {

		          /* k_root sibling is BLACK */
		          if (!is_left) {  //x is right child of k_root
		              /* make x a left child */
		              x = k_root;
		              rotateLeft(x);
		          }

		          /* recolor and rotate */   //x is left child of k_root
		          k_root->color = BLACK;
		          k_root->parent->color = RED;
		          rotateRight(k_root->parent);
		      }
		  } else {

		      /* mirror image of above code */
		      printf("hello");
		      Node *y = k_root->parent->left;
		      if (y->color == RED) {

		          /* k_root sibbling is RED */
		          k_root->color = BLACK;
		          y->color = BLACK;
		          k_root->parent->color = RED;
		          x = k_root->parent;
		      } else {

		          /* k_root sibling is BLACK */
		          if (is_left) {
		              x = k_root;
		              rotateRight(x);
		          }
		          k_root->color = BLACK;
		          k_root->parent->color = RED;
		          rotateLeft(k_root->parent);
		      }
		 
		  }
		}
		
		display(root);
     
    }
    root->color = BLACK;
    
    display(root);//remove after debugging
     
}

Node *insertNode(T data) {
    Node *current, *parent, *x;

   /***********************************************
    *  allocate node for data and insert in tree  *
    ***********************************************/

    /* find where node belongs */
    current = root;
    parent = 0;
    while (current != NIL) {
        if (compEQ(data, current->data)) return (current);
        parent = current;
        current = compLT(data, current->data) ?
            current->left : current->right;
    }

    /* setup new node */
    if ((x = malloc (sizeof(*x))) == 0) {
        printf ("insufficient memory (insertNode)\n");
        exit(1);
    }
    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;

    /* insert node in tree */
    if(parent) {
        if(compLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else {
        root = x;
    }

    insertFixup(x);
    return(x);
}

void deleteFixup(Node *x) {

   /*************************************
    *  maintain Red-Black tree balance  *
    *  after deleting node x            *
    *************************************/

    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft (x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight (w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft (x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight (x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft (w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight (x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void deleteNode(Node *z) {
    Node *x, *y;

   /*****************************
    *  delete node z from tree  *
    *****************************/

    if (!z || z == NIL) return;


    if (z->left == NIL || z->right == NIL) {
        /* y has a NIL node as a child */
        y = z;
    } else {
        /* find tree successor with a NIL node as a child */
        y = z->right;
        while (y->left != NIL) y = y->left;
    }

    /* x is y's only child */
    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;

    if (y != z) z->data = y->data;


    if (y->color == BLACK)
        deleteFixup (x);

    free (y);
}

Node *findNode(T data) {

   /*******************************
    *  find node containing data  *
    *******************************/

    Node *current = root;
    while(current != NIL)
        if(compEQ(data, current->data))
            return (current);
        else
            current = compLT (data, current->data) ?
                current->left : current->right;
    return(0);
}
void display(Node *root)
{

	if(root!=NIL)
	{
	      printf("\nValues at each node");
		printf("data at node %d\n",root->data);
		printf("color %d\n",root->color);
		printf("left %d\n",root->left->data);
		printf("right %d\n",root->right->data);
		if(root->parent != 0)
		printf("parent %d\n",root->parent->data);
		display(root->left);
		display(root->right);
		
	}
}
void main(int argc, char **argv ) {
    int a, maxnum, ct;
    Node *t;

    /* command-line:
     *
     *   rbt maxnum
     *
     *   rbt 2000
     *       process 2000 records
     *
     */
    /*
    maxnum = atoi(argv[1]);
    //maxnum = 10;
    for (ct = maxnum; ct; ct--) {
        a = rand() % 9 + 2;
        printf("\n inserting a '%d'\n",a);
        insertNode(a);
        
        display(root);
        
             
        if ((t = findNode(a)) != NULL) {
            deleteNode(t);
        } else {
            insertNode(a);
        }
       
        
    }*/
    
    printf("\n***Select K-RB Tree Operations***\n");
	int oprtn;
	while (1){
	
		printf("\n***Enter 1 for K-RB Tree Insertion***\n");
		printf("\n***Enter 2 for K-RB Tree Deletion***\n");
		printf("\n***Enter 3 for K-RB Tree Find***\n");
		printf("\n***Enter -1 for Exit***\n");
		scanf("%d",&oprtn);
		
		if( oprtn == -1 ) {
			printf("\n***Exiting Code***\n");
			break;
            }   
		else if ( oprtn == 1 ) {
			int key;
			printf("\n***Enter Key for insert into K-RB Tree***\n");
			scanf("%d",&key);
			insertNode(key);
			
		}
		else if ( oprtn == 2 ) {
			int key;
			printf("\n***Enter Key for delete from K-RB Tree***\n");
			scanf("%d",&key);
			//delete(key);
		}
		else if ( oprtn == 3 ) {
			int key;
			printf("\n***Enter Key for find in K-RB Tree***\n");
			scanf("%d",&key);
			//find(key);
		}
		else{
			printf("\n***Select Correct Operation ***\n");
			display(root);
			printf("\n***after calling disple ***\n");
		
		}
	}
    
              

    
    printf("%d\n",root->data);
   display(root);
}
