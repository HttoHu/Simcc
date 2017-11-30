#pragma once
#include "../../Lexer/HPP/Token.hpp"
#include <string>
namespace Simcc
{
	namespace ExprTree
	{
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
			TreeNode(Lexer::Token *tok, TreeNode *r)
			{
				root = r;
				left = nullptr;
				right = nullptr;
				value = tok;
			}
			 
			bool is_root() { return root == nullptr; }
			bool is_leaf() { return left == nullptr&&right == nullptr; }

			TreeNode *root;
			TreeNode *left;
			TreeNode *right;
			Simcc::Lexer::Token *value;
		};
		TreeNode *create_tree();
		void destroy_node(TreeNode *node);
		void insert_left(TreeNode *node,TreeNode *p);
		void insert_right(TreeNode *node, TreeNode *p);
	}
}