#pragma once
#include "../../Lexer/HPP/Token.hpp"
#include <string>
namespace Simcc
{
	namespace ExprTree
	{
		struct TreeNode;
		void insert_root(TreeNode *node, TreeNode *p);
		void insert_left(TreeNode *node, TreeNode *p);
		void insert_right(TreeNode *node, TreeNode *p);
		TreeNode *create_tree();
		void destroy_node(TreeNode *node);
		size_t heigth(TreeNode *node);
		//================debug===================
		// to draw a tree
		TreeNode* create_complete_tree(size_t length);
		void create_tree_graph_frame(TreeNode *node);
		void create_tree_graph_node(TreeNode *node, size_t length);
		void print_tree();
		extern std::vector<std::string> tree_graph;
		struct TreeNode
		{
			TreeNode()
			{
				root = nullptr;
				left = nullptr;
				right = nullptr;
				value = nullptr;
			}
			TreeNode(Lexer::Token *tok)
			{
				root = nullptr;
				left = nullptr;
				right = nullptr;
				value = tok;
			}
			 
			size_t count()
			{
				if (this == nullptr)
					return 0;
				else
					return left->count() + right->count() + 1;
			}
			void insert_left(TreeNode *node)
			{
				ExprTree::insert_left(this, node);
			}
			void insert_right(TreeNode*node)
			{
				ExprTree::insert_right(this, node);
			}
			void insert_root(TreeNode *node)
			{
				ExprTree::insert_root(this, node);
			}
			bool check()
			{
				if (this == nullptr)
					return true;
				if (root->left == this || root->right == this)
					left->check() && right->check();
				else
					return false;
			}
			TreeNode* to_orgin_root()
			{
				TreeNode* tmp = root;
				int count=0;
				if (root == nullptr)
					return this;
				while (tmp->root!=nullptr)
				{
					tmp = tmp->root;
				}
				return tmp;
			}
			void print(std::string indent,bool is_right)
			{
				// https://stackoverflow.com/questions/1649027/how-do-i-print-out-a-tree-structure
				if (this==nullptr||value == nullptr)
					return;
				std::cout << indent;
				if (is_right)
				{
					std::cout<<"L-";
					indent += "  ";
				}
				else
				{
					std::cout<<("R-");
					indent += "| ";
				}
				std::cout << value->to_string()<<std::endl;
				left->print(indent, false);
				right->print(indent, true);

			}
			bool is_root() { return root == nullptr; }
			bool is_leaf() { return left == nullptr&&right == nullptr; }

			TreeNode *root;
			TreeNode *left;
			TreeNode *right;
			Simcc::Lexer::Token *value;
		};



	}
}