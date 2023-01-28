struct app_info {
	string category; // Name of category
	string app_name; // Name of the application
	string version; // Version number
	float size; // Size of the application
	string units; // GB or MB
	float price; // Price in $ of the application
};
#define CAT_NAME_LEN 25
struct categories {
	char category[CAT_NAME_LEN]; // Name of category
	struct bst* root; // Pointer to root of BST for this category
};
// Dynamically allocate an array of size n of type struct categories (here using malloc)
//