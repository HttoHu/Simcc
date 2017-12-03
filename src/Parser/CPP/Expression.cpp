#include "../HPP/Expression.hpp"

using namespace Simcc;

//***********************************
bool is_literal(Simcc::Lexer::Tag t)
{
	if (t == Lexer::TLiteralChar || t == Lexer::TLiteralDouble || t == Lexer::TLiteralInt
		|| t == Lexer::TLiteralLong || t == Lexer::TLiteralString)
		return true;
	return false;
}

//***********************************
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

TokenStream Simcc::Expression::cut_brackets(const TokenStream & ts, size_t start_pos)
{
	TokenStream ret;
	int deepth = 0;
	if (ts[start_pos]->get_tag() == Lexer::Lk)
	{
		deepth = 1;
		size_t index = ++start_pos;
		while (1)
		{
			if (ts[start_pos]->get_tag() == Lexer::Lk)
				deepth++;
			else if (ts[start_pos]->get_tag() == Lexer::Rk)
				deepth--;
			if (deepth == 0)
				return ret;
			ret.push_back(ts[start_pos++]);
		}
	}
	else
	{
		throw std::runtime_error("cut_brackets: ts[start_pos] must be a left braket");
	}
}

ExprTree::TreeNode * Simcc::Expression::set_expr_tree(const TokenStream & ts)
{
	ExprTree::TreeNode *sign = nullptr;
	ExprTree::TreeNode *value = nullptr;
	bool is_first = true;
	//ExprTree::TreeNode *
	ExprTree::TreeNode *expr_tree = nullptr;
	ExprTree::TreeNode  *current = nullptr;
	size_t pos = 0;
	if (ts.front()->get_tag() == Lexer::Endl)
		pos++;
	switch (ts[pos]->get_tag())
	{
	case Lexer::Lk:
	{
		TokenStream ts2 = cut_brackets(ts, pos);
		pos++;
		value = set_expr_tree(ts2);
		pos += ts2.size();
		Lexer::Operator *op = static_cast<Lexer::Operator*>(ts[pos]);
		if (Lexer::is_single_variable_countsign(op->count_sign))
		{
			sign = new ExprTree::TreeNode(ts[pos]);
			sign->insert_left(value);
			pos++;
			break;
		}
		else
		{
			return value;
		}
		break;
	}
	case Lexer::TOperator:
	{
		Lexer::Operator *op = static_cast<Lexer::Operator*>(ts[pos]);
		if (op->count_sign == Lexer::MM || Lexer::Sub || Lexer::PP)
		{
			value = new ExprTree::TreeNode(op);
			pos++;
			value->insert_left(new ExprTree::TreeNode(ts[pos]));
			pos++;
			if (Lexer::is_single_variable_countsign(op->count_sign))
			{
				sign = new ExprTree::TreeNode(ts[pos]);
				sign->insert_left(value);
				pos++;
				break;
			}
			else
			{
				std::cout << "RIGHT" << std::endl;
				return value;
			}
		}
		else
			throw std::runtime_error("bad expr");
	}
	default:
		value = new ExprTree::TreeNode(ts[pos]);
		pos++;
		sign = new ExprTree::TreeNode(ts[pos]);
		pos++;
		sign->insert_left(value);
		break;
	}

	expr_tree = current = sign;
	for (int i = pos; i < ts.size(); i++)
	{
		if (ts[i]->get_tag() == Lexer::Endl)
		{
			i++;
			continue;
		}
		Lexer::Token *tok = ts[i];
		Lexer::Tag t = ts[i]->get_tag();

		if (t == Lexer::Id || is_literal(t))
		{
			value = new ExprTree::TreeNode(tok);
			sign->insert_right(value);
		}
		else if (t == Lexer::Lk)
		{
			TokenStream ts2 = cut_brackets(ts, i);
			ExprTree::TreeNode *children = set_expr_tree(ts2);
			current->insert_right(children);
			i += ts2.size();
		}
		else if (t == Lexer::TOperator)
		{
			sign = new ExprTree::TreeNode(tok);
			ExprTree::TreeNode *tmp = nullptr;
			try
			{
				tmp = find_place(sign, current);
				if (tmp != nullptr)
				{
					sign->insert_left(tmp);
				}
			}
			catch (ExprTree::TreeNode *tr)
			{
				current = current->to_orgin_root();
				sign->insert_left(current);
			}
			current = sign;
		}

	}
	return current->to_orgin_root();
}

ExprTree::TreeNode* Simcc::Expression::find_place(ExprTree::TreeNode * n, ExprTree::TreeNode * m)
{
	/*
	* the Expr Tree has a property that the leaves are all numbers/id/right_value
	* and we need to compare the priority between n and m (n is something need to be inserted, m is n's competitor)
	* if n's priority is greater than m's, n should replace m's right node. and then return right node.
	* in other cases : m will be its root, and then continue comparing with n until n's PRI > m's PRI.
	*/
	while (Lexer::operator_priority(static_cast<Lexer::Operator*>(n->value)->count_sign) <=
		Lexer::operator_priority(static_cast<Lexer::Operator*>(m->value)->count_sign))
	{
		//std::cout << n->value->to_string() << " cw " << m->value->to_string() << std::endl;
		if (m->root == nullptr)
		{
			throw n;
		}
		m = m->root;
	}
	ExprTree::TreeNode *ret;
	ret = m->right;
	m->insert_right(n);
	return ret;
}
