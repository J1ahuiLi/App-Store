#ifndef __HASH__
#define __HASH__
#include"defn.h"

using namespace std;
void HashInit(hash_table_entry*& HashTab, int length);
int HashNum(int length, const char* str);
void HashInsert(hash_table_entry* HashTab, int length, bst* node);
bst* HashFind(hash_table_entry* HashTab, int length, const char* name);
void HashDel(hash_table_entry* HashTab, int length, const char* name, const char* catname);
int HashCountLineWithHead(hash_table_entry* HashTab);
#endif // !__HASH__

