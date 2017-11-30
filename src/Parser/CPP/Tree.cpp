#include "..\HPP\Tree.hpp"
using namespace Simcc::ExprTree;
TreeNode * Simcc::ExprTree::create_tree()
{
	return new TreeNode();
}

void Simcc::ExprTree::destroy_node(TreeNode * node)
{
	if (node == nullptr)
		return;
	delete node->value;
	destroy_node(node->left);
	destroy_node(node->right);
}

void Simcc::ExprTree::insert_left(TreeNode * node,TreeNode *p)
{
	if (node->left == nullptr)
	{
		node->left == p;
	}
	TreeNode *tmp = node->left;
	node->left = p;
	p->left = tmp;
}

void Simcc::ExprTree::insert_right(TreeNode * node, TreeNode * p)
{
	if (node->right == nullptr)
	{
		node->right == p;
	}
	TreeNode *tmp = node->right;
	node->right = p;
	p->right = tmp;
}
