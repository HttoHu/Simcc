#include "../HPP/Expression.hpp"

using namespace Simcc;

TokenStream Simcc::Expression::sub_token_stream(const TokenStream & ts, size_t start_pos, size_t length)
{
	if (start_pos + length >= ts.size())
	{
		throw std::out_of_range("sub_token_stream: out of range");
	}
	TokenStream ret(length);
	for (size_t i = 0; i < length; i++)
	{
		ret[i] = ts[start_pos + i];
	}
	return ret;
}

ExprTree::TreeNode * Simcc::Expression::set_expr_tree(const TokenStream & ts)
{
	Lexer::Token *oper;
	Lexer::Token *left;
	Lexer::Token *right;
	bool is_left = false;
	ExprTree::TreeNode *expr_tree=ExprTree::create_tree();
	ExprTree::TreeNode  *current=expr_tree;
	if (ts.front()->get_tag() == Lexer::Tag::TOperator)
	{
		if (((Lexer::Operator*)ts.front())->count_sign == Lexer::CountSign::Sub)
		{
			expr_tree->value = ts.front();
			current = expr_tree->left;
		}
	}
	for (const auto & a : ts)
	{
		// -> Here 23:03    11 - 30   if(a->get_tag()==Lexer::Id||a->get_tag()==Lexer::Tag::)
	}
}
