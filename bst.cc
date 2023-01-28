#include "bst.h"
#include <iostream>
using namespace std;
int bstcmp(app_info app1, app_info app2)
{
	return strcmp(app1.app_name, app2.app_name);
}
int bstcmp(app_info app1,const char* name)
{
	return strcmp(app1.app_name,name);
}
int Max(int m, int n) { return m > n ? m : n; }
bst* BstInsert(bst*& root, app_info app)
{
	if (root == NULL)
	{
		root = new struct bst();
		root->left = root->right = NULL;
		root->record = app;
		return root;
	}
	else if (bstcmp(root->record, app) >= 0)
	{
		return	BstInsert(root->left, app);
	}
	else if (bstcmp(root->record, app) < 0)
	{
		return BstInsert(root->right, app);
	}
	return  NULL;
}

int BstSearch(bst* root, const char * key, app_info& re)
{
	int c;
	if (root == NULL)
	{
		return 0;
	}
	c =bstcmp(root->record,key);
	if (c == 0)
	{
		re = root->record;
		return 1;
	}
	if (c > 0)
	{
		return BstSearch(root->left, key, re);
	}
	else
	{
		return BstSearch(root->right, key, re);
	}
	return 0;
}
int BstSearchNode(bst* root, const char* key, bst*& re)
{
	int c;
	if (root == NULL)
	{
		return 0;
	}
	c = bstcmp(root->record, key);
	if (c == 0)
	{
		re = root;
		return 1;
	}
	if (c > 0)
	{
		return BstSearchNode(root->left,key, re);
	}
	else
	{
		return BstSearchNode(root->right, key, re);
	}
	return 0;
}
void preorder(bst* root) {
	if (root==NULL)
	{
		return;
	}
	preorder(root->left);
	cout <<"\t"<< root->record.app_name<<"\n";
	preorder(root->right);
}
void BstPreOrderFree(bst* root)
{
	if (root == NULL)
		return ;
	BstPreOrderFree(root->left);
	if (root->record.price==0)
		cout <<root->record.app_name<< "\n";
	BstPreOrderFree(root->right);
}


bst* treeDeleteMin(bst** p)
{
	bst* x;
	while ((*p)->left != NULL)
		p = &(*p)->left;
	x = *p;
	*p = x->right;

	return x;
}
int BstDel(bst* &root, const char* key)
{
		bst** p = &root, * x;
		int flag;
		while ((*p) != NULL) {
			flag = bstcmp((*p)->record, key);
			x = *p;
			if (flag == 0) {
				/* 没有孩子 */
				if ((x->left == NULL) && (x->right == NULL))
					*p = NULL;
				/* 有一个孩子 */
				else if (x->right == NULL)
					*p = x->left;
				else if (x->left == NULL)
					*p = x->right;
				/* 有两个孩子 */
				else {
					*p = treeDeleteMin(&x->right);
					(*p)->left = x->left;
					(*p)->right = x->right;
				}
				free(x);
				return 1;
			}
			else if (flag <0)
				p = &(*p)->right;
			else
				p = &(*p)->left;
		}
		return 0;
}

int BstCount(bst* root)
{
	if (root==NULL)
	{
		return 0;
	}
	return 1 + BstCount(root->left)+ BstCount(root->right);
}

int BstDepth(bst* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return 1 +Max(BstDepth(root->left), BstDepth(root->right));
}

void BstGetPriceArr(bst* root, float*& h)
{
	if (root==NULL)
	{
		return;
	}
	BstGetPriceArr(root->left,h);
	*h = root->record.price;
	h++;
	BstGetPriceArr(root->right, h);
}

void BstReport(bst* root)
{
	
		
	if (root!=NULL)
	{
		cout << "TreeNodeCount:" << BstCount(root) << "\t,TreeDepth:" << BstDepth(root);
		cout<< "\t,LeftDepth:";
		cout << BstDepth(root->left);
		cout << "\t,RightDepth:";
		cout << BstDepth(root->right);
		cout << "\n";
	}
	else
	{
		cout << "TreeNodeCount:" << BstCount(root) <<"" ;
	}
}

int CanBstRangePrice(bst* root, float from, float to) {
	int i;
	if (root == NULL)
		return 0;
	i=CanBstRangePrice(root->left, from, to);
	if (i > 0)
		return 1;
	if (root->record.price >= from && root->record.price <= to)
		return	 1;
	i = CanBstRangePrice(root->right, from, to);
	if (i > 0)
		return 1;
	return 0;
}
void BstRangePrice(bst* root, float from, float to)
{
	if (root==NULL)
	{
		return;
	}
	BstRangePrice(root->left,from,to);
	if (root->record.price>= from&& root->record.price<=to)
	{
		cout <<"\t"<< root->record.app_name << "\n";
	}
	BstRangePrice(root->right, from, to);
}

int CanBstRangeApp(bst* root, const char* from, const char* to)
{
	if (root == NULL)
		return 0;
	int f1 = bstcmp(root->record, from);
	int f2 = bstcmp(root->record, to);
	if (f1 < 0) 
		return  CanBstRangeApp(root->right, from, to);
	else if (f2 > 0) 
		return CanBstRangeApp(root->left, from, to);
	else
		return 1;

}
void BstRangeApp(bst* root, const char* from, const char* to)
{
	if (root == NULL)
		return;
	int f1 = bstcmp(root->record,from);
	int f2 = bstcmp(root->record, to);
	if (f1 < 0) 
		BstRangeApp(root->right, from, to);
	else if (f2 > 0) 
		BstRangeApp(root->left, from, to);
	else {
		BstRangeApp(root->left, from, to);
	cout << "\t" << root->record.app_name << "\n";	
	BstRangeApp(root->right, from, to);
	}
		
}