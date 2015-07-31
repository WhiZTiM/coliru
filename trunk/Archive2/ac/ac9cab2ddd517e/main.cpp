#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

struct node { int value; node* left; node* right; };

    void remove(int value, node*& node)
	{
		if(node == NULL)
		{
			throw std::logic_error("Not found"); 
			
		}
		if(node ->value == value)
		{

			node* temp = node; 
			if(node ->left == NULL && node ->right == NULL)
			{
				delete node; 
				node = NULL; 
			}
			else if(node ->left == NULL || node ->right == NULL)
			{
				if(node ->left ==  NULL)
				{
					node = node ->right; 
					delete node; 
				}
				else 
				{
					node = node ->left; 
					delete node; 
				}
			}
			else 
			{
			    // Save left and right subtrees of current node
			    // that we have to delete.
				node* leftnode = node ->left; 
				node* rightnode = node ->right; 
				
				// Delete current node.
				delete node; 
				
				// Replace current node with the maximum
				// on the left subtree
				node* temp_parent = node; 
				temp = leftnode; 
				while(temp ->right != NULL)
				{
				    temp_parent = temp; 
					temp = temp ->right; 
					
				}
				node = temp; 
				
				// Change old connections with temp
				// so that temp is skipped.
				if(temp == temp_parent->right)
				{
			        temp_parent->right = temp->left; 
				}
				else
				{
				    temp_parent->left = temp->left;
				}
				
				// Link old left and right nodes too.
				node-> left = leftnode; 
				node-> right = rightnode;

			}
		}
		else if(node ->value < value)
		{
			remove(value, node ->right); 			
		}
		else // node ->value > value
		{
			remove(value, node ->left); 
		}
	}
    
void print_ptree(node* root, int indent = 0) {
    if (root != nullptr) {
        std::cout << std::string(' ', indent * 4) << root->value;
        print_tree(root->left, indent + 1);
        print_tree(root->right, indent + 1);
    }
}

int main()
{
    node* root =
        new node{47,
            new node{32, nullptr, nullptr},
            new node{62,
                new node{57,
                    new node{49, nullptr, nullptr},
                    new node{62,
                        new node{59, nullptr, nullptr},
                        nullptr
                    }
                },
                new node{102, nullptr, nullptr}
            }
        };
    print_tree(root);
                
}
