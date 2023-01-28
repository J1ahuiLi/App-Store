
#include "hash.h"
#include<iostream>
#include<string>
void HashInit(hash_table_entry*& HashTab, int length) {
	int i;
	HashTab = new hash_table_entry[length];
	for (i = 0; i < length; i++)
	{
		HashTab[i].app_node;
		HashTab[i].next = NULL;
	}
}

int HashNum(int length, const char* str) {
	int sum = 0;
	while (*str)
	{
		sum += *str;
		str++;
	}
	return sum % length;
}

void HashInsert(hash_table_entry* HashTab, int length, bst* node) {
	hash_table_entry* item;
	int index = HashNum(length, node->record.app_name);
	item = new hash_table_entry();
	item->app_node = node;
	strcpy(item->app_name, node->record.app_name);
	item->next = HashTab[index].next;
	HashTab[index].next = item;
}

bst* HashFind(hash_table_entry* HashTab, int length, const char* name) {
	hash_table_entry* node;
	int index = HashNum(length, name);
	node = (HashTab + index)->next;
	while (node)
	{
		if (strcmp(name, node->app_node->record.app_name) == 0)
		{
			return node->app_node;
		}
		node = node->next;
	}
	return NULL;
}

void HashDel(hash_table_entry* HashTab, int length, const char* name, const char* catname)
{
	hash_table_entry* node, * t;
	int index = HashNum(length, name);
	node = HashTab + index;
	while (node->next)
	{
		if (strcmp(name, node->next->app_name) == 0)
		{
				t = node->next;
				node->next = t->next;
				delete t;
			return;
		}
		node = node->next;
	}
	return;
}

int HashCountLineWithHead(hash_table_entry* HashTab)
{
	hash_table_entry* node;
	int count = 0;
	node = HashTab->next;
	while (node)
	{
		count++;
		node = node->next;
	}
	return count;
}

