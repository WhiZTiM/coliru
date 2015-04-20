#include <string>
#include <iostream>
#include <vector>

struct Client
{
    std::string uniqueID;
};

struct Node
{
    Node() : client(nullptr), left(nullptr), right(nullptr) {}
    Client* client;
    Node*   left;
    Node*   right;
};

enum ICLResult { OK, ID_INVALID, CLIENT_INVALID, EXISTS, EXISTS_NOT, EMPTY_LIST };
ICLResult add(Client* client, Node* m_rootNode)
{
    if (!client)
    	return ICLResult::CLIENT_INVALID;
    
    if (client->uniqueID.length() == 0)
		return ICLResult::ID_INVALID;

	if (m_rootNode)
	{
		// check if client exists
		Node* currentNode = m_rootNode;
		int result;
		while (currentNode)
		{
			// check the node's client
			result = client->uniqueID.compare(currentNode->client->uniqueID);
			// if equal
			if (result == 0)
				return ICLResult::EXISTS;

			// less than
			else if (result < 0)
			{
				if (currentNode->left)
				{
					currentNode = currentNode->left;
					continue;
				}
				else
				{
					// Create node
					Node* tempNode = new Node;
					currentNode->left = tempNode;

					// Add client
					Client* tempClient = new Client;
                    tempClient->uniqueID = client->uniqueID;
					tempNode->client = tempClient;
				}
			}

			// greater than
			else
			{
				if (currentNode->right)
				{
					currentNode = currentNode->right;
					continue;
				}
				else
				{
					// Create node
					Node* tempNode = new Node;
					currentNode->right = tempNode;

					// Add client
					Client* tempClient = new Client;
                    tempClient->uniqueID = client->uniqueID;
					tempNode->client = tempClient;
				}
			}
		}
	}
	else
	{
		m_rootNode = new Node;
		Client* tempClient = new Client;
        tempClient->uniqueID = client->uniqueID;
		m_rootNode->client = tempClient;
	}

	return ICLResult::OK;
}

using namespace std;
int main()
{
    string s1 = "4xILASs5dmhcexwgWLIf6MJiKuA=";
    string s2 = "4XILASs5dmhcexwgWLIf6MJiKuA="; // second char to UPPER (differs from s1)
    Node* root = nullptr;
    
    Client c1;
    c1.uniqueID = s1;
    
    int result = add(&c1, root);
    if(result == ICLResult::OK)
        cout << "client added" << endl;
    else
        cout << "sth. went wrong" << endl;
    
    c1.uniqueID = "";
    result = add(&c1, root);
    if(result == ICLResult::ID_INVALID)
        cout << "id invalid" << endl;
    else
        cout << "sth. went wrong" << endl;
    
    c1.uniqueID = s1; // this id is already in list
    result = add(&c1, root);
    if(result == ICLResult::EXISTS)
        cout << "already exists" << endl;
    else
        cout << "sth. went wrong: code '" << result << "'" << endl;
    cout << "result: " << result << endl;
    
    cout << "content" << endl;
    cout << "c1 id: " << root->client->uniqueID << endl;    // ### segmentation fault ###
    cout << "c1 new id:" << c1.uniqueID << endl;
    
    Client c2;
    c2.uniqueID = s2;
    result = add(&c2, root);
    if(result == ICLResult::OK)
        cout << "another client added" << endl;
    else
        cout << "sth. went wrong" << endl;
}
