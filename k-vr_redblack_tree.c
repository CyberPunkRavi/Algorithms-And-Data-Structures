#include <stdio.h>
#include <stdlib.h>
typedef struct rbtree_node {
    char color;
    int data;
    struct rbtree_node *left,
                     *right,
                     *parent;
}rbtree_node;
rbtree_node *root=NULL;


rbtree_node* BSTInsert(rbtree_node* root, rbtree_node *New)
{
    
    if (root == NULL)
       return New;
    
    if (New->data < root->data)
    {
        root->left  = BSTInsert(root->left, New);
        root->left->parent = root;
    }
    else if (New->data > root->data)
    {
        root->right = BSTInsert(root->right, New);
        root->right->parent = root;
    }
    
    return root;
}

 rbtree_node* redBlackInsert(rbtree_node *root, int z) {  
    rbtree_node *New = (rbtree_node *)malloc(sizeof(rbtree_node));
/*    
    New->data = z;
    New->left = NULL;
    New->right = NULL;
    New->color = 'R';
    
	rbtree_node *Yp = NULL;
      rbtree_node *Xp = root;
 
    while (Xp != NULL) {
        Yp = Xp;
        if (New->data < Xp->data)
            Xp = Xp->left;
        Xp = Xp->right;
    }
    New->parent = Yp;
    if (Yp == NULL) 
        root = New;
    else if (New->data < Yp->data)
            Yp->left = New;
    else
            Yp->right = New;
    New->left = NULL;
    New->right = NULL;
    New->color = 'R';
    
    printf("%d\n",root->data);
    
    return root;
 */   
    root = BSTInsert(root, New);
    return root;
     
    //redBlackInsertFixup(Root, New);
}
display(rbtree_node *root)
{

				printf("\n***in disple ***\n");
	if(root==NULL)
	{
	   printf("\n***root is null ***\n");
		return;
	}
	else
	{
		printf("%d\n",root->data);
		display(root->left);
		display(root->right);
		
		return;
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
			if (root == NULL)
			root = redBlackInsert(root,key);
			else redBlackInsert(root,key);
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
	
    return 0;
}
