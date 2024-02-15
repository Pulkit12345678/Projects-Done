/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// #include <string>

int getheight(SymNode *root)
{
	return root->height;
}

int getbalance(SymNode *root)
{
	int firstheight = 0;
	int secondheight = 0;

	if (root->left != NULL)
	{
		firstheight = root->left->height;
	}

	if (root->right != NULL)
	{
		secondheight = root->right->height;
	}

	return abs(firstheight - secondheight);
}

void setheight(SymNode *root)
{
	int l = (root->left == nullptr) ? 0 : root->left->height;
	int r = (root->right == nullptr) ? 0 : root->right->height;
	root->height = max(l, r) + 1;
	// cout << "Kardi Height Bc" << endl;
}

SymNode *LLR(SymNode *root)
{
	SymNode *temp = root->left;
	root->left = temp->right;
	if (temp->right != NULL)
	{
		temp->right->par = root;
	}
	temp->right = root;
	temp->par = root->par;
	root->par = temp;
	if (temp->par != NULL && root->key < temp->par->key)
	{
		temp->par->left = temp;
	}
	else
	{
		if (temp->par != NULL)
		{
			temp->par->right = temp;
		}
	}
	root = temp;
	setheight(root->left);
	setheight(root->right);
	setheight(root);
	setheight(root->par);
	return root;
}

SymNode *RRR(SymNode *root)
{
	SymNode *temp = root->right;
	root->right = temp->left;
	if (temp->left != NULL)
	{
		temp->left->par = root;
	}
	temp->left = root;
	temp->par = root->par;
	root->par = temp;
	if (temp->par != NULL && root->key < temp->par->key)
	{
		temp->par->left = temp;
	}
	else
	{
		if (temp->par != NULL)
			temp->par->right = temp;
	}
	root = temp;
	setheight(root->left);
	setheight(root->right);
	setheight(root);
	setheight(root->par);
	return root;
}

SymNode *LRR(SymNode *root)
{
	root->left = RRR(root->left);
	return LLR(root);
}

SymNode *RLR(SymNode *root)
{
	root->right = LLR(root->right);
	return RRR(root);
}

SymNode *Insert(SymNode *root, SymNode *parent, string key)
{
	if (root == NULL)
	{
		root = new SymNode(key);
		root->par = parent;
	}
	else if (key < root->key)
	{
		root->left = Insert(root->left, root, key);
		root->left->par = root;

		int firstheight = -1;
		if (root->left != NULL)
		{
			firstheight = root->left->height;
		}

		int secondheight = -1;
		if (root->right != NULL)
		{
			secondheight = root->right->height;
		}

		if (abs(firstheight - secondheight) == 2)
		{
			if (key < root->left->key)
			{
				root = root->LeftLeftRotation();
			}
			else
			{
				root = root->LeftRightRotation();
			}
		}
	}
	else if (key > root->key)
	{
		root->right = Insert(root->right, root, key);
		root->right->par = root;

		int firstheight = -1;
		if (root->left != NULL)
		{
			firstheight = root->left->height;
		}

		int secondheight = -1;
		if (root->right != NULL)
		{
			secondheight = root->right->height;
		}

		if (abs(firstheight - secondheight) == 2)
		{
			if (key < root->right->key)
			{
				root = root->RightLeftRotation();
			}
			else
			{
				root = root->RightRightRotation();
			}
		}
	}

	int leftHeight;
	if (root->left != NULL)
	{
		leftHeight = root->left->height;
	}
	else
	{
		leftHeight = -1;
	}

	int rightHeight;
	if (root->right != NULL)
	{
		rightHeight = root->right->height;
	}
	else
	{
		rightHeight = -1;
	}

	root->height = 1 + max(leftHeight, rightHeight);

	if (root->par != NULL)
	{
		int parLeftHeight;
		if (root->par->left != NULL)
		{
			parLeftHeight = root->par->left->height;
		}
		else
		{
			parLeftHeight = -1;
		}

		int parRightHeight;
		if (root->par->right != NULL)
		{
			parRightHeight = root->par->right->height;
		}
		else
		{
			parRightHeight = -1;
		}

		root->par->height = 1 + max(parLeftHeight, parRightHeight);
	}

	return root;
}

SymbolTable::SymbolTable()
{
}

void SymbolTable::insert(string k)
{
	if (root == NULL)
	{
		root = new SymNode(k);
		size++;
	}
	else
	{
		root = Insert(root, NULL, k);
		size++;
	}
}

SymNode *searchrec(SymNode *&root, string key)
{
	if (root == NULL)
	{
		return NULL;
	}
	else if (root->key == key)
	{
		return root;
	}
	else if (root->key > key)
	{
		return searchrec(root->left, key);
	}
	else
	{
		return searchrec(root->right, key);
	}
}

SymNode *balancetree(SymNode *root)
{
	int balance = getbalance(root);
	if (abs(balance) == 2)
	{
		// cout << "Hummer" << endl;
		if (getheight(root->left) < getheight(root->right))
		{
			// cout << "Party" << endl;
			int rightheight1 = 0;
			int rightheight2 = 0;
			if (root->right->right != NULL)
			{
				// cout << "Coke" << endl;
				rightheight2 = root->right->right->height;
			}

			if (root->right->left != NULL)
			{
				// cout << "DJ" << endl;
				rightheight1 = root->right->left->height;
			}

			if (rightheight1 > rightheight2)
			{
				// cout << "Club" << endl;
				root = RLR(root);
			}
			else
			{
				// cout << "Dua" << endl;
				root = RRR(root);
			}
		}

		else
		{
			// cout << "Raat" << endl;
			int leftheight1 = 0;
			int leftheight2 = 0;
			if (root->left->right != NULL)
			{
				// cout << "Jashan" << endl;
				leftheight2 = root->left->right->height;
			}

			if (root->left->left != NULL)
			{
				// cout << "Aayi" << endl;
				leftheight1 = root->left->left->height;
			}

			if (leftheight1 > leftheight2)
			{
				// cout << "Dharti" << endl;
				root = LLR(root);
			}
			else
			{
				// cout << "Nache" << endl;
				root = LRR(root);
			}
		}
	}
	// cout << "Kar diya BC Balance" << endl;
	return root;
}

SymNode *deleterec(SymNode *&root, string key)
{
	if (root != NULL)
	{
		// cout << "NULL" << endl;
		if (root->key == key)
		{
			// cout << "YES" << endl;
			if (root->right == NULL && root->left != NULL)
			{
				SymNode *storage = new SymNode();
				SymNode *storage2 = new SymNode();
				// cout << "Fuck" << endl;
				if (root->par != NULL)
				{
					storage2 = root->left;
					// cout << "YO" << endl;
					if (root->par->key < root->key)
					{
						// cout << "Dhan" << endl;
						storage = root->par;
						root->par->right = root->left;
					}
					else
					{
						// cout << "Udd" << endl;
						storage = root->par;
						root->par->left = root->left;
					}
					setheight(storage);
				}
				storage2->par = storage;
				storage2 = balancetree(storage2);

				return storage2;
			}
			else if (root->left == NULL && root->right != NULL)
			{
				SymNode *storage = new SymNode();
				SymNode *storage2 = new SymNode();
				// cout << "Ter" << endl;
				if (root->par != NULL)
				{
					storage2 = root->right;
					// cout << "Ek" << endl;
					if (root->par->key < root->key)
					{
						// cout << "Chitta" << endl;
						storage = root->par;
						root->par->right = root->right;
					}
					else
					{
						// cout << "Puff" << endl;
						storage = root->par;
						root->par->left = root->right;
					}
					setheight(root->par);
				}

				storage2->par = storage;
				storage2 = balancetree(storage2);

				return storage2;
			}
			else if (root->left == NULL && root->right == NULL)
			{
				// cout << "Hup" << endl;
				SymNode *storage = new SymNode();
				if (root->par != NULL)
				{
					// cout << "Shoot" << endl;
					if (root->par->key < root->key)
					{
						// cout << "Setting parent's right to NULL" << endl;
						// cout << root->par->key << endl;
						// cout << root->key << endl;
						// cout << root->par->right->key << endl;
						storage = root->par;
						root->par->right = NULL;
						// cout << storage->key << endl;
					}
					else
					{
						// cout << "Setting parent's left to NULL" << endl;
						root->par->left = NULL;
					}

					setheight(storage);
				}
				// cout << "wtf" << endl;
				// cout << root->key << endl;
				// cout << storage->key;

				// cout << "Kardiya BC NULL" << endl;
				delete root; // Delete the node to free memory
				return NULL;
			}

			else
			{
				// cout << "Aali" << endl;
				SymNode *tmpnode = root;
				tmpnode = tmpnode->right;
				while (tmpnode->left != NULL)
				{
					// cout << "Punjab" << endl;
					tmpnode = tmpnode->left;
				}
				string val = tmpnode->key;
				root->right = deleterec(root->right, tmpnode->key);
				root->key = val;
				root = balancetree(root);
			}

			if (root->par != NULL)
			{
				// cout << "Ve" << endl;
				int parLeftHeight = (root->par->left != NULL) ? root->par->left->height : -1;
				int parRightHeight = (root->par->right != NULL) ? root->par->right->height : -1;
				root->par->height = 1 + max(parLeftHeight, parRightHeight);
			}

			return root;
		}
		else if (root->key < key)
		{
			// cout << "Kudi" << endl;
			root->right = deleterec(root->right, key);
			root = balancetree(root);
		}
		else if (root->key > key)
		{
			// cout << "Bailoando" << endl;
			root->left = deleterec(root->left, key);
			root = balancetree(root);
		}

		if (root != NULL)
		{
			// cout << "Rain" << endl;
			int leftHeight = (root->left != NULL) ? root->left->height : -1;
			int rightHeight = (root->right != NULL) ? root->right->height : -1;
			root->height = 1 + max(leftHeight, rightHeight);
		}

		if (root != NULL && root->par != NULL)
		{
			// cout << "Over" << endl;
			int parLeftHeight = (root->par->left != NULL) ? root->par->left->height : -1;
			int parRightHeight = (root->par->right != NULL) ? root->par->right->height : -1;
			root->par->height = 1 + max(parLeftHeight, parRightHeight);
		}
	}

	if (root == NULL)
	{
		// cout << "Me" << endl;
		return NULL;
	}
	// cout << "Mita Diya" << endl;
	return root;
}

void SymbolTable::remove(string k)
{
	SymNode *temp = searchrec(root, k);
	if (temp == NULL)
	{
		// cout << "Supriser MotherFucker" << endl;
		return;
	}
	else
	{
		// cout << "Honey" << endl;
		deleterec(root, k);
		size--;
	}
}

int SymbolTable::search(string k)
{
	SymNode *temp = searchrec(root, k);
	if (temp == NULL)
	{
		return -2;
	}
	else
	{
		return temp->address;
	}
}

void assign_address_rec(SymNode *&root, string key, int idx)
{
	if (root == NULL)
	{
		return;
	}
	else if (root->key == key)
	{
		root->address = idx;
	}
	else if (root->key > key)
	{
		assign_address_rec(root->left, key, idx);
	}
	else
	{
		assign_address_rec(root->right, key, idx);
	}
}

void SymbolTable::assign_address(string k, int idx)
{
	assign_address_rec(root, k, idx);
}

int SymbolTable::get_size()
{
	return size;
}

SymNode *SymbolTable::get_root()
{
	return root;
}

SymbolTable::~SymbolTable()
{
}
