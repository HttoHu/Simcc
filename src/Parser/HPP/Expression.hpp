#pragma once
#include "Tree.hpp"
typedef std::vector<Simcc::Lexer::Token*> TokenStream;
namespace Simcc
{
	namespace Lexer
	{
		class TId;
	}
	namespace Stmt
	{
		class Stmt;
	}
	namespace Expression
	{
		extern std::list<Stmt::Stmt*> trans_stmt;
		TokenStream sub_token_stream(const TokenStream &ts, size_t start_pos, size_t length);
		TokenStream cut_brackets(const TokenStream &ts, size_t start_pos);
		Lexer::TId* trans_expr_tree(ExprTree::TreeNode* expr_tree);
		ExprTree::TreeNode *set_expr_tree(const TokenStream &ts);
		ExprTree::TreeNode* find_place(ExprTree::TreeNode *n, ExprTree::TreeNode *m);
	}
}