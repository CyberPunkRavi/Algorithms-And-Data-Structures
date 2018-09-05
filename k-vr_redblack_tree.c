#include <stdio.h>
#include <stdlib.h>
struct rbtree_node {
    char colour;
    int key;
    struct rbtree_node *left,
                     *right,
                     *parent;
};
rbtree_node *root=NULL;

btree_node* BSTInsert(rbtree_node* root, rbtree_node *New)
{
    
    if (root == NULL)
       return New;
    
    if (New->key < root->rbtree_node)
    {
        root->left  = BSTInsert(root->left, New);
        root->left->parent = root;
    }
    else if (New->data > root->key)
    {
        root->right = BSTInsert(root->right, New);
        root->right->parent = root;
    }
    
    return root;
}

 void redBlackInsert(rbtree_node **root, int z) {  
    rbtree_node *New = (rbtree_node *)malloc(sizeof(rbtree_node));
    New->key = z;
    New->left = NULL;
    New->right = NULL;
    New->color = 'R';
    
    root = BSTInsert(root, New);
     
    //redBlackInsertFixup(Root, New);
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
			redBlackInsert(root,key);
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
