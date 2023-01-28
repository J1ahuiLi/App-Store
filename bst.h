
#ifndef __BST__
#define __BST__
#include "defn.h"
#include<iostream>
#include<string>
using namespace std;
int bstcmp(struct app_info app1, struct app_info app2);
int bstcmp(struct app_info app1, const char* name);

bst* BstInsert(struct bst* &root, struct app_info app);

int BstSearch(struct bst* root, const char* key, struct app_info& re);
int BstSearchNode(struct bst* root, const char* key, struct bst*& re);
void preorder(struct bst* root);
void BstPreOrderFree(struct bst* root);


 
int BstDel(struct bst*& root,const char* key);
int BstCount(struct bst* root);
int BstDepth(struct bst* root);
void BstGetPriceArr(struct bst* root,float* &h);
void BstReport(struct bst* root);

int CanBstRangePrice(bst* root, float from, float to);
void BstRangePrice(struct bst* root, float from, float to);
int CanBstRangeApp(struct bst* root, const char* from, const char* to);
void BstRangeApp(struct bst* root, const char* from, const char* to);
#endif // !__BST__

