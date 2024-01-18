#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <ctype.h>
#include <fstream>
#include <string>

using namespace std;

template <class T1, class T2>
class BST
{
private:
	struct Node
	{
		T1 c;
		T2 morse;
		Node* left;
		Node* right;
	};

	Node* root;

	void insert_node(Node*& node, Node*& new_node) //Inserts data into the tree (private)
	{
		if (node == nullptr) //Inserts the node
		{
			node = new_node;
		}
		else if (new_node->c < node->c) //Goes to the left branch
		{
			insert_node(node->left, new_node);
		}
		else //Goes to the right branch
		{
			insert_node(node->right, new_node);
		}
	}
	void delete_node(T1 chara, Node*& node) //Deletes/removes data from the tree (private)
	{
		if (chara < node->c)
		{
			delete_node(chara, node->left);
		}
		else if (chara > node->c)
		{
			delete_node(chara, node->right);
		}
		else
		{
			make_deletion(node);
		}
	}
	void make_deletion(Node*& node) //Deletes and reattaches a node to the nearest branch/subtree
	{
		Node* temp_node = nullptr;

		if (node == nullptr)
		{
			cout << "Node is empty.";
			return;
		}
		else if (node->right == nullptr)
		{
			temp_node = node;
			node = node->left; //Reattaching the left branch/subtree
			delete temp_node;
		}
		else if (node->left == nullptr)
		{
			temp_node = node;
			node = node->right; //Reattaching the right branch/subtree
			delete temp_node;
		}
		else
		{
			temp_node = node->right;

			while (temp_node->left != nullptr)
			{
				temp_node = temp_node->left;
			}

			temp_node->left = node->left;

			temp_node = node;
			node = node->right;

			delete temp_node;
		}
	}
	void destroy_subtree(Node* node) //Destroys the entire tree 
	{
		if (node != nullptr)
		{
			if (node->left != nullptr)
			{
				destroy_subtree(node->left);
			}
			if (node->right != nullptr)
			{
				destroy_subtree(node->right);
			}

			delete node;
		}
	}
	void disp_tree_in_order(Node* node) //Displays the contents of the tree in order (private)
	{
		if (node != nullptr)
		{
			disp_tree_in_order(node->left);
			cout << node->c << endl;
			cout << node->morse << endl << endl;
			disp_tree_in_order(node->right);
		}
	}
	void search_node(T1 chara, T2* mors_cod) //Searched for a specific character in the tree
	{
		Node* node = root;

		while (node != nullptr)
		{
			if (chara == ' ') //Checks for space
			{
				*mors_cod = ' ';
				return;
			}
			
			if (node->c == chara)
			{
				*mors_cod = node->morse;
				return;
			}
			else if (node->c < chara)
			{
				node = node->right;
			}
			else
			{
				node = node->left;
			}
		}

		return;
	}

public:

	BST() //Constructor
	{
		root = nullptr;
	}

	~BST() //Destructor
	{
		destroy_subtree(root);
	}

	void insert(T1 chara, T2 morse_code) //Inserts data into the tree (public)
	{
		Node* new_node = nullptr;
		new_node = new Node;
		new_node->right = new_node->left = nullptr;

		new_node->c = chara;
		new_node->morse = morse_code;

		insert_node(root, new_node);
	}
	void remove(T1 chara) //Deletes/removes data from the tree (public)
	{
		delete_node(chara, root);
	}
	void capital(char* symbol) // Checks if the character is a lowercase letter or a symbol
	{
		if (*symbol == '.' || *symbol == ',' || *symbol == '?' || *symbol == '1' || *symbol == '2' || *symbol == '3' || *symbol == '4' || *symbol == '5' || *symbol == '6' || *symbol == '7' || 
			*symbol == '8' || *symbol == '9' || *symbol == '0' || *symbol == ' ')
		{
			return;
		}
		else if (isupper((int)*symbol))
		{
			return;
		}
		else 
		{
			*symbol = toupper((int)*symbol);
			return;
		}
	}
	void convert(string sentence, string* coded_msg) //Converts the sentence into morse code.
	{
		int ind = 0;
		char temp = '\0';

		while (sentence[ind] != '\0')
		{
			temp = sentence[ind];
			capital(&temp);
			search_node(temp, coded_msg);
			cout << *coded_msg << " ";
			ind++;
		}
	}
	void disp_tree() //Displays the contents of the tree in order (public)
	{
		disp_tree_in_order(root);
	}
};

#endif