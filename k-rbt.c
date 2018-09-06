#include <stdio.h>
#include <stdlib.h>
const int RED = 0;
const int BLACK = 1;
typedef struct RBTNode RBT;
typedef struct RBTNode *Position;
typedef struct RBTNode *SearchTree;

struct  RBTNode{
    int key;
    int color;
    Position parent, left, right;
}; 

static RBT sentinel = {0, 1, 0, 0, 0};
#define NIL &sentinel 

SearchTree tree = NIL;

Position RBTreeSearch(SearchTree tree, int k) {
    if (tree == NIL || k == tree->key) {
        return tree;
    }
    if (k < tree->key) {
        return RBTreeSearch(tree->left, k);
    } else {
        return RBTreeSearch(tree->right, k);
    }
} 
 
Position RBTreeMinimim(SearchTree tree) {
    while (tree->left != NIL) {
        tree = tree->left;
    }
    return tree;
}  

Position RBTreeMaximum(SearchTree tree) {
    while (tree->right != NIL) {
        tree = tree->right;
    }
    return tree;
} 
 
Position RBTreeSuccessor(Position x) {
    if (x->right != NIL) {
        return RBTreeMinimim(x->right);
    }
    Position y = x->parent;
    while (y != NIL && x == y-> right) {
        x = y;
        y = y->parent;
    }
    return y;
}  
 
void LeftRotate(SearchTree &tree, Position x) {
    Position y = x->right;

    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    } 
 
    y->parent = x->parent;
    if (x->parent == NIL) {
        tree = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
} 
 
void RightRotate(SearchTree &tree, Position x) {
    Position y = x->left;
    
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    } 
 
    
    y->parent = x->parent;
    if (x->parent == NIL) {
        tree = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}    
 

void RBTreeInsertFixUp(SearchTree &tree, Position z) {
    while (z->parent->color == RED) {
        if (z->parent = z->parent->parent->left) {
            Position y = z->parent->parent->right;
            if (y->color == RED) {//Case1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent ->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {//Case2
                    z = z->parent;
                    LeftRotate(tree, z); 
                }
                z->parent->color = BLACK;//Case3
                z->parent->parent->color = RED;
                RightRotate(tree, z->parent->parent);
            }
        } else {
            Position y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent ->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {//Case2
                    z = z->parent;
                    RightRotate(tree, z); //case2->case3
                }
                z->parent->color = BLACK;//Case3
                z->parent->parent->color = RED;
                LeftRotate(tree, z->parent->parent);
            }
        }//if-else
    }//while
    tree->color = BLACK;
}//RBInsertFixUp 
 

void RBTreeInsert(SearchTree &tree, int k) {
    Position y = NIL;
    Position x = tree;
    Position z = new RBT;
    z->key = k;
    z->parent = z->left = z->right = NIL;
 
  
    while (x != NIL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    if (y == NIL) {
        tree = z;
    } else {
        if (k < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }
    z->left = z->right = NIL;
    z->color = RED;
    RBTreeInsertFixUp(tree, z);
}    
 

void RBTreeDeleteFixUp(SearchTree &tree, Position x) {
    while (x != tree && x->color == BLACK) {
        if (x == x->parent->left) {
            Position w = x->parent->right;
            if (w->color == RED) {//Case1
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(tree, x->parent);
                w = x->parent->right;
            }
            //____________Case2__________________
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->right->color == BLACK) {//Case3->Case4
                w->left->color = BLACK;
                w->color = RED;
                RightRotate(tree, w);
                w = x->parent->right;
            } else {//Case4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(tree, x->parent);
                x = tree;
            }
        } else {
            Position w = x->parent->left;
            if (w->color == RED) {//Case1
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(tree, x->parent);
                w = x->parent->left;
            }
            //____________Case2__________________
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->left->color == BLACK) {//Case3->Case4
                w->left->color = BLACK;
                w->color = RED;
                LeftRotate(tree, w);
                w = x->parent->left;
            } else {//Case4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(tree, x->parent);
                x = tree;
            }
        }
    }
    x->color = BLACK;
} 
 

Position RBTreeDelete(SearchTree tree, Position z) {
    Position x, y;  
 
    if (z->left == NIL || z->right == NIL) {
        y = z;
    } else {
        y = RBTreeSuccessor(z);
    }  
 
    if (y->left != NIL) {
        x = y->left;
    } else {
        x = y->right;
    }  
 

    x->parent = y->parent;  
 
    if (y->parent == NIL) {
        tree = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }  
 
    if (y != z) {
        z->key = y->key;
    }  
 
    if (y->color == BLACK) {
        RBTreeDeleteFixUp(tree, x);
    }
    return y;
} 
 

void InOrderTraverse(SearchTree tree) {
    if (tree != NIL) {
        InOrderTraverse(tree->left);
        printf("\nkey = %2d ：color = ", tree->key);
        if (tree->color == 0) {
            printf("RED  " );
        } else {
            printf("BLACK" );
        } 
 
        printf("  parent = %2d ", tree->parent->key);
        if (tree->left != NIL) {
            printf(" left  = %2d ", tree->left->key);
        }
        if (tree->right != NIL) {
            printf(" right = %2d", tree->right->key);
        }
        InOrderTraverse(tree->right);
    }
}         

int main(int argc, char *argv[]) {

	int k;	
	printf("\n***Enter K Value***\n");
	scanf("%d",&k);
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
			RBTreeInsert(tree,key);
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
		
		}
	}
    return 0;
}
