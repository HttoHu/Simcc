#include "../HPP/Expression.hpp"
#include "../../Parser/HPP/BasicStmt.hpp"
using namespace Simcc;

//***********************************
bool is_literal(Simcc::Lexer::Tag t)
{
	if (t == Lexer::TLiteralChar || t == Lexer::TLiteralDouble || t == Lexer::TLiteralInt
		|| t == Lexer::TLiteralLong || t == Lexer::TLiteralString)
		return true;
	return false;
}
std::list<Stmt::Stmt*>  Simcc::Expression::trans_stmt;
void Simcc::Expression::_clear_trans_stmt()
{
	for (auto & a : trans_stmt)
		delete a;
	trans_stmt.clear();
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

Lexer::TId* Simcc::Expression::trans_expr_tree(ExprTree::TreeNode * expr_tree)
{
	if (expr_tree == nullptr)
		return nullptr;
	using namespace Lexer;
	if (expr_tree->is_leaf())
	{
		if (expr_tree->value->get_tag() == Lexer::Id)
			return static_cast<Lexer::TId*>(expr_tree->value);
		else if (is_literal(expr_tree->value->get_tag()))
		{

			Context::Type *lit_type;
			switch (expr_tree->value->get_tag())
			{
			case Lexer::TLiteralInt:
				lit_type = Context::Type::find_type("int");
				break;
			case Lexer::TLiteralDouble:
				lit_type = Context::Type::find_type("double");
				break;
			case Lexer::TLiteralLong:
				lit_type = Context::Type::find_type("long");
				break;
			case Lexer::TLiteralString:
				lit_type = Context::Type::find_type("string");
				break;
			case Lexer::TLiteralChar:
				lit_type = Context::Type::find_type("char");
				break;
			case Lexer::True:
				lit_type = Context::Type::find_type("bool");
				break;
			case Lexer::False:
				lit_type = Context::Type::find_type("bool");
				break;
			default:
				throw std::runtime_error("unknow type");
				break;
			}
			Lexer::TId* tmp = Lexer::TId::create_tmp_id();
			trans_stmt.push_front(new Stmt::CreateVariable(lit_type, tmp, expr_tree->value));
			return tmp;
		}
		throw std::runtime_error("bad expr");
	}
	if (expr_tree->value->get_tag() != Lexer::TOperator)
		throw std::runtime_error("bad expr");
	Lexer::CountSign cs = *(Lexer::CountSign*)expr_tree->value->get_value();
	switch (cs)
	{
	case PP:
	case MM:
	{
		auto a = expr_tree->left->value;
		if (a->get_tag() != Id)
			throw std::runtime_error("bad expr3");
		trans_stmt.push_back(new Stmt::SingleOS(static_cast<TId*>(a), static_cast<Operator*>(expr_tree->value)));
		return static_cast<TId*>(a);
	}
	case Sub:
		if (expr_tree->right == nullptr)
		{

		}
	case Add:
	case Mul:
	case Div:
	{
		TId *left_op = trans_expr_tree(expr_tree->left);
		TId *right_op = trans_expr_tree(expr_tree->right);
		if (left_op == nullptr || right_op == nullptr)
			throw std::runtime_error("bad expr");
		TId *tmp = TId::create_tmp_id();

		/* 17 12-5
		* -remember to add the stmt which creates the tmp variable. In present I am lack of tmp's type info, since I can not get
		* left_op right_op 's type info. ## and I haven't build a Symbol table yet. <-_-!>
		* Htto */

		trans_stmt.push_back(new Stmt::TOS(static_cast<TId*>(tmp), static_cast<TId*>(left_op), static_cast<TId*>(right_op),
			static_cast<Operator*>(expr_tree->value)));
		return tmp;
	}
	case SAdd:
	case SSub:
	case SMul:
	case SDiv:
	case Assign:
	{
		Token *tok = expr_tree->right->value;
		if (tok->get_tag() == TOperator)
		{
			CountSign cs = *(CountSign*)tok->get_value();
			switch (cs)
			{
			case MM:
			case PP:
			case Sub:
				if (expr_tree->have_single_son())
				{
					// a = -b
					/*
					a is left 
					= is op
					- is action op
					b is right->left->value 
					*/
					//AssignWithAction(Lexer::TId *vid, Lexer::Operator *op, Lexer::Operator * act, Lexer::TId *rid) :action_type(act),
					trans_stmt.push_back(
						new Stmt::AssignWithAction(static_cast<TId*>(expr_tree->left->value),
							static_cast<Operator*>(expr_tree->value),
							static_cast<Operator*>(expr_tree->right->value),
							static_cast<TId*>(expr_tree->right->left->value))  );
					break;
				}
				goto oc;
			default:
			{
			oc:TId  *v = trans_expr_tree(expr_tree->right);
				trans_stmt.push_back(new Stmt::Assign(static_cast<TId*>(expr_tree->left->value), static_cast<TId*>(tok),
					static_cast<Operator*>(expr_tree->value)));
				break;
			}
			}
		}
		else if (tok->get_tag() == Id)
		{

		}
	}
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
