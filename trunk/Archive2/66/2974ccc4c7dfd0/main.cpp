#ifndef LAB_ONE_TREE_NODE_HPP_
#define LAB_ONE_TREE_NODE_HPP_

#include <vector>

namespace lab_one
{
    class TreeNode
	{
	public:
	    TreeNode(char name_, int node_no_, int dist_);
	    bool operator<(const TreeNode &rhs) const; //So that priority queue works
	    std::vector<TreeNode> Expand();

	    char name;
	    int node_no;
	    int dist;
	};
}

#endif