#pragma once
#include "Tree.hpp"
#include "../../Stmts/HPP/Stmts.hpp"
typedef std::vector<Simcc::Lexer::Token*> TokenStream;
namespace Simcc
{
	namespace Lexer
	{
		class TId;
	}
	namespace Expression
	{
		extern std::list<Stmt*> trans_stmt;
		void _clear_trans_stmt();

		Lexer::TId* expr();
		TokenStream sub_token_stream(const TokenStream &ts, size_t start_pos, size_t length);
		TokenStream cut_brackets(const TokenStream &ts, size_t start_pos);
		Action::ActionBase * trans_expr_tree(ExprTree::TreeNode* expr_tree);
		ExprTree::TreeNode *set_expr_tree(const TokenStream &ts);
		ExprTree::TreeNode* find_place(ExprTree::TreeNode *n, ExprTree::TreeNode *m);
		


		void trans_expr_tree_test();
	}
}