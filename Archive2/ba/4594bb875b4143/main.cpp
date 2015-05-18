#include <iostream>
#include <string>
#include <vector>
// Write non-recursive version of tree traversal programs
#include <stack>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
};

void inorder_trav (TreeNode *root) {
    if (root==nullptr) { return; }
    TreeNode *p;
    stack<TreeNode *> st;
    
    p = root;
    while(!st.empty() || p!=nullptr) {
        if (p!=nullptr) {
            st.push(p);
            p=p->left;
        }else{
            p = st.top();
            st.pop();
            cout << "visit " << p->data << endl;
            p = p->right;
        }
    }
} 

void preorder_trav (TreeNode *root) {
    if (root == nullptr) { return; }
    TreeNode *p;
    stack<TreeNode *> st;
    st.push(p);
    while(!st.empty()) {
        p = st.top();
        st.pop();
        cout << "visit " << p->data << endl;
        
        if (p->right!=nullptr) { st.push(p->right); }
        if (p->left!=nullptr) { st.push(p->left); }
    }
}

int main()
{

}
