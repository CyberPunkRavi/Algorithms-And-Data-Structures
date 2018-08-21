#include<stdio.h>
#include<stdlib.h>
struct tree{
	int data;
	struct tree *left;
	struct tree *right;};
typedef struct tree bst;
bst *root=NULL;
int main()
{
	while(1)
	{
		printf("Enter elements to Insert -1 to exit");
		int v;
		scanf("%d",&v);
		if(v==-1)
			break;
		bst *cur=(bst *)malloc(sizeof(bst));
		bst *new=(bst *)malloc(sizeof(bst));
		new->data=v;
		if(root==NULL)
		{
			root=new;
			root->left=NULL;
			root->right=NULL;
		}
		else
		{
			cur=root;
			while(cur->left!=NULL || cur->right!=NULL)
			{
				if(cur->data<=v)
				{
					printf("%d\n",cur->data);
					if(cur->right==NULL)
						break;
					cur=cur->right;
				}
				else
					{printf("%d\n",cur->data);
						if(cur->left==NULL)
							break;
					cur=cur->left;}
			}
			if(cur->data<=v)
			{
				printf("right %d\n",cur->data);
				cur->right=new;
				cur->right->left=NULL;
				cur->right->right=NULL;
			}
			else
			{
				printf("left %d\n",cur->data);
				cur->left=new;
				cur->left->left=NULL;
				cur->left->right=NULL;
			}
		}
	}
	display(root);
	printf("Defth of tree %d\n",defth(root)-1);
}
display(bst *root)
{
	if(root==NULL)
	{
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
defth(bst* root)
{
	if(root==NULL)
		return 0;
	else
	return max(defth(root->left)+1,defth(root->right)+1);
}
max(a,b)
{
	if(a>=b)
		return a;
	else
		return b;
}
