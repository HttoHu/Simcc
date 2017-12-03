#include "..\HPP\Tree.hpp"
using namespace Simcc::ExprTree;
//=====================variables============================
std::vector<std::string> Simcc::ExprTree::tree_graph;
//=====================methods/functions=======================
TreeNode * Simcc::ExprTree::create_tree()
{
	return new TreeNode();
}

void Simcc::ExprTree::destroy_node(TreeNode * node)
{
	if (node == nullptr)
		return;
	destroy_node(node->left);
	destroy_node(node->right);
}

size_t Simcc::ExprTree::heigth(TreeNode * node)
{
	if (node == nullptr)
		return 0;
	size_t left_deepth = 1 + heigth(node->left);
	size_t right_deepth = 1 + heigth(node->right);
	return left_deepth > right_deepth ? left_deepth : right_deepth;
}

TreeNode * Simcc::ExprTree::create_complete_tree(size_t length)
{
	if (length == 0)
		return nullptr;
	length--;
	TreeNode *root = new TreeNode();
	root->left = create_complete_tree(length);
	root->right = create_complete_tree(length);
	return root;
}

void Simcc::ExprTree::create_tree_graph_frame(TreeNode * node)
{
	int length = heigth(node);
	tree_graph.resize(length * 3);
	for (auto &a : tree_graph)
	{
		a.resize(pow(2, length) * 4);
	}
	// we build a tree from bottom to top
	for (int i = length - 1; i >= 0; i--)
	{
		/* first we need to count how many lines and sticks we need .
		* then we need to know the length of each unit.
		*/
		int count = pow(2, i + 1);
		int dis = 4 * pow(2, length - i) / count;
		for (int j = 1; j <= count; j++)
		{
			tree_graph[i * 3 + 1][dis*j] = '|';
			//tree_graph[i * 3 + 2][dis*j] = '_';
		}
	}
}
void Simcc::ExprTree::create_tree_graph_node(TreeNode * node, size_t length)
{

}
void Simcc::ExprTree::print_tree()
{
	for (const auto & a : tree_graph)
	{
		std::cout << a << std::endl;
	}
}
/*
*/
void Simcc::ExprTree::insert_root(TreeNode * node, TreeNode * p)
{
	if (node == nullptr)
		node = p;
	node->root = p;
}

void Simcc::ExprTree::insert_left(TreeNode * node, TreeNode *p)
{
	if (node == nullptr)
		node = p;
	node->left = p;
	p->root = node;
}

void Simcc::ExprTree::insert_right(TreeNode * node, TreeNode * p)
{
	if (node == nullptr)
		node = p;
	node->right = p;
	p->root = node;
}
