
#include<iostream>
#include<string>
#include"defn.h"
#include"bst.h"
#include"hash.h"
#include"prime.h"
#include"heap.h"
using namespace std;


struct hash_table_entry* HashTab;
struct categories* Categories;
int CategoriesNum;
int AppNum;
int HashLength;

void  GetRemoveQt(char * str) {
	char c='\0';
	while (c!='\"')
	{
		c=cin.get();
	}
	
	c = cin.get();
	while (c != '\"')
	{
		*str = c;
		str++;
		c = cin.get();
	}
	*str = '\0';
}


void InitCat() {
	int c; int i; string s;
	cin >> c;
	cin.ignore();
	Categories = new struct categories[c];
	CategoriesNum = c;
	for (i = 0; i < c; i++)
	{
		cin.getline(Categories[i].category, CAT_NAME_LEN);
		Categories[i].root = NULL;
	}
}
void InitApp() {
	int n, i, j; struct  app_info app; string s;
	bst* node;
	cin >> n;
	AppNum = n;
	for ( i = n * 2 + 1; ; i+=2)
	{
		if (TestForPrime(i))
		{
			break;
		}
	}
	HashLength = i;
	HashInit(HashTab,i);
	cin.ignore();
	for (i = 0; i < n; i++)
	{
		
		cin.getline(app.category, CAT_NAME_LEN);
		cin.getline(app.app_name, APP_NAME_LEN);
		cin.getline(app.version, VERSION_LEN);
		cin >> app.size;
		cin.ignore();
		cin.getline(app.units, UNIT_SIZE);
		cin >> app.price;
		cin.ignore();
		for (j = 0; j < CategoriesNum; j++)
		{
			if (strcmp(Categories[j].category, app.category) == 0)
			{
				node=BstInsert(Categories[j].root, app);
				HashInsert(HashTab, HashLength,node);
				break;
			}
		}
	}

}
int GetCatIndex(const char* catname) {
	int j;
	for (j = 0; j < CategoriesNum; j++)
	{
		if (strcmp(Categories[j].category, catname) == 0)
		{
			return j;
		}
	}
	return -1;
}
void FindMaxPriceApp(const char* catname) {
	int c; float* a,*h; float max;
	int index = GetCatIndex(catname);
	if (index < 0)
	{
		cout << "Category " << catname << " not found\n";
	}
	else if (Categories[index].root)
	{
		cout << "Max Price of Category " << catname << " :\n";
		 c = BstCount(Categories[index].root);
		 a = h = new float[c + 1]; 
		 BstGetPriceArr(Categories[index].root,h);
		 BuildHeap(a,c);
		 max = a[1];
		 BstRangePrice(Categories[index].root,max,max);
		 delete[] a;
	}
	else
	{
		cout << "Category " << catname << " no apps found";
	}
}
void RangeApp(const char* catname, const char* from, const char* to) {
	int index = GetCatIndex(catname);
	if (index < 0)
	{
		cout << "Category " << catname << " not found\n";
	}
	else if (CanBstRangeApp(Categories[index].root, from, to))
	{
		cout << "Applications in  Range( " << from << " , " << to
			<< ") in Category " << catname << ":\n";
		BstRangeApp(Categories[index].root, from, to);
	}
	else
	{
		cout << "No applications found in " << catname << " for the given range(" << from << " , " << to << ")\n";
	}
}

void RangePrice(const char* catname,float from,float to) {
	int index = GetCatIndex(catname);
	if (index<0)
	{
		cout << "Category " << catname<<" not found\n";
	}
	else if (CanBstRangePrice(Categories[index].root,from,to))
	{
		cout << "Applications in Price Range( " << from << " , " << to
			<< ") in Category " << catname << ":\n";
		BstRangePrice(Categories[index].root, from, to);
	}
	else
	{
		cout << "No applications found in "<<catname<<" for the given price range(" << from << " , " << to<< ")\n";
	}
}

void PrintApp(const char* appname) {
	bst* node=HashFind(HashTab,HashLength,appname);
	if (node)
	{
		cout << "Found Application " << appname<<":\n";
		cout << "\t" << node->record.app_name << "\n";
		cout << "\t" << node->record.category << "\n";
		cout << "\t" << node->record.version << "\n";
		cout << "\t" << node->record.size << "\n";
		cout << "\t" << node->record.units << "\n";
		cout << "\t" << node->record.price << "\n";
	}
	else
	{
		cout << "Application "<<appname <<" not found"<< "\n";
	}
	//todo
}

void PrintCat(const char* catname) {
	int index = GetCatIndex(catname);
	if (index < 0)
	{
		cout << "Category " << catname << " not found\n";
	}
	else if (Categories[index].root)
	{
		cout << "Category " << catname << " :\n";
		preorder(Categories[index].root);
	}
	else
	{
		cout << "Category " << catname << " no apps found\n";
	}
}

void PrintFree(const char* catname) {
	int index = GetCatIndex(catname);
	if (index < 0)
	{
		cout << "Category " << catname << " not found\n";
	}
	else if (CanBstRangePrice(Categories[index].root, 0,0))
	{
		cout<< "Free apps in category : "  << catname << " :\n";
		preorder(Categories[index].root);
	}
	else
	{
		cout << "Category " << catname << " no free apps found";
	}
}

void DeleteApp(const char* catname, const char* appname) {
	int index = GetCatIndex(catname);
	if (index < 0)
	{
		cout << "Category " << catname << " not found\n";
	}
	else if (BstDel(Categories[index].root,appname))
	{
		cout << "Category " << catname <<" app "<<appname<< " successfully deleted\n";
		HashDel(HashTab, HashLength, appname, catname);
	}
	else
	{
		cout <<"Application "<<appname<<" not found in category"<< catname << ",unable to delete\n";
	}
}

void Report() {
	int j;
	//bst tree
	for (j = 0; j < CategoriesNum; j++)
	{
		cout << Categories[j].category << " :\n";
		BstReport(Categories[j].root);
	}
	//hash tab
	for (j = 0; j < HashLength; j++)
	{
		cout << "Hash " << j << "\tLength " << HashCountLineWithHead(HashTab+j)<<"\t";
	}
	cout << "\n";
}
int main(void)
{
	int order; float f1, f2;
	string s; char carr[1024], carr2[1024], carr3[1024];
	InitCat();
	InitApp();
	cin >> order;
	for (int i = 0; i < order-1; i++)
	{
		cin >> s;
		if (s == "find")
		{
			cin >> s;
			if (s == "price") {
				cin >> s;
				if (s != "free")
					exit(0);
				GetRemoveQt(carr);
				PrintFree(carr);
			}
			else if (s == "app")
			{
				 GetRemoveQt(carr);
				PrintApp(carr);
			}
			else if (s=="max")
			{
				cin >> s;
				if (s != "price")
					exit(0);
				cin >> s;
				if (s != "apps")
					exit(0);
				GetRemoveQt(carr);
				FindMaxPriceApp(carr);
			}
			else
			{
				exit(0);
			}
		}
		else if (s == "print-apps")
		{
			cin >> s;
			if (s != "category")
			{
				exit(0);
			}
			  GetRemoveQt(carr);
			PrintCat(carr);
		}
		else if (s == "range")
		{
			GetRemoveQt(carr);
			cin >> s;
			if (s == "app")
			{
				  GetRemoveQt(carr2);
				  GetRemoveQt(carr3);
				RangeApp(carr, carr2, carr3);
			}
			else if (s=="price")
			{
				cin >> f1;
				cin >> f2;
				RangePrice(carr, f1, f2);
			}

		}
		else if (s == "delete")
		{
			  GetRemoveQt(carr);
			  GetRemoveQt(carr2);
			DeleteApp(carr,carr2);
			//todo
		}
		else if (s=="report")
		{
			Report();
		}
	}

	cin >> s;
	if (s=="no")
	{
		cin >> s;
		if (s == "report") {
			return 0;
		}
	}
	Report();
	return 0;
}