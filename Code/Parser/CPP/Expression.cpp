#include "../HPP/Expression.hpp"
using namespace yt::Parser;

yt::Parser::Expression::Expression(Environment * env) :environment(env)
{
	std::vector<Lexer::Token* >operatorStack;
	while (1)
	{
		switch (this_token()->get_tag())
		{
		case Lexer::True:
		case Lexer::False:
		case Lexer::Tag::TLiteralDouble:
		case Lexer::Tag::TLiteralString:
		case Lexer::Tag::TLiteralInt:
		case Lexer::Tag::TLiteralLong:
		case Lexer::Tag::TLiteralChar:
			//  字面值总是先压入输入中.
			count_stack.push_back(this_token());
			break;
		case Lexer::Tag::Lk:
			// '(' 总是被压入栈中
			operatorStack.push_back(this_token());
			break;

		case Lexer::Tag::Ne:
		case Lexer::Tag::Ge:
		case Lexer::Tag::Eq:
		case Lexer::Tag::Gt:
		case Lexer::Tag::Le:
		case Lexer::Tag::Lt:
		case Lexer::Tag::Or:
		case Lexer::Tag::Add:
		case Lexer::Tag::Sub:
		case Lexer::Tag::Mul:
		case Lexer::Tag::Div:
		case Lexer::Tag::Assign:
			//顶部遇到了比自己厉害的, 然后就pass-pass, 直到比自己差点的. 
			//当然一样厉害的还是pass 不敢打啊.'('除外啦. 毕竟它走他也不走 它只认')'
			while (!operatorStack.empty() && operatorStack.back()->get_tag() != Lexer::Tag::Lk&&get_priority(this_token()->get_tag()) <= get_priority(operatorStack.back()->get_tag()))
			{
				count_stack.push_back(operatorStack.back());
				operatorStack.pop_back();
			}
			operatorStack.push_back(this_token());
			break;
		case Lexer::Tag::Rk:
			while (operatorStack.back()->get_tag() != Lexer::Tag::Lk)
			{
				count_stack.push_back(operatorStack.back());
				operatorStack.pop_back();
			}
			operatorStack.pop_back();
			break;
		case Lexer::Tag::MM:
		case Lexer::Tag::PP:
		case Lexer::Tag::Id:
			skip();
			break;
		default:
			while (!operatorStack.empty())
			{
				count_stack.push_back(operatorStack.back());
				operatorStack.pop_back();
			}
			return;
		}
		environment->current_pos++;
	}

}

void yt::Parser::Expression::skip()
{
	bool is_func;
redo:	switch (this_token()->get_tag())
{
case Lexer::Tag::PP:
case Lexer::Tag::MM:
	count_stack.push_back(next_token());
	goto redo;
case Lexer::Tag::Id:
	// 如果是个函数的话
	if (this_token()->get_tag() == Lexer::Tag::Lk)
	{
		throw std::runtime_error("void yt::Parser::Expression::skip() not compleleted ");
		// args_parse;
		// 等我把函数模块写完后回头来完善这个地方.
	}
	else if (this_token()->get_tag() == Lexer::Tag::PP || this_token()->get_tag() == Lexer::Tag::PP)
	{
		count_stack.push_back(this_token());
	}
	else
	{
		count_stack.push_back(this_token());
	}
	break;
default:
	return;
	throw std::runtime_error("\nError:" + this_token()->to_string() + "runtime_error12");
}
}

yt::Runtime::ObjectBase * yt::Parser::Expression::GetResult()
{
	using namespace yt::Lexer;
	std::deque<Runtime::ObjectBase*> tmpStack;
	for (size_t i = 0; i < count_stack.size(); i++)
	{
		switch (count_stack[i]->get_tag())
		{
		case TLiteralChar:
			tmpStack.push_front(new Runtime::ObjectBase(*(char*)count_stack[i]->get_value()));
			break;
		case TLiteralDouble:
			tmpStack.push_front(new Runtime::ObjectBase(*(double*)count_stack[i]->get_value()));
			break;
		case TLiteralInt:
			tmpStack.push_front(new Runtime::ObjectBase(*(int32_t*)count_stack[i]->get_value()));
			break;
		case TLiteralString:
			tmpStack.push_front(new Runtime::ObjectBase(*(std::string*)count_stack[i]->get_value()));
			break;
		case TLiteralLong:
			tmpStack.push_front(new Runtime::ObjectBase(*(int64_t*)count_stack[i]->get_value()));
			break;
		case True:
			tmpStack.push_front(new Runtime::ObjectBase(true));
			break;
		case False:
			tmpStack.push_front(new Runtime::ObjectBase(false));
			break;
		case Ne:
		case Ge:
		case Eq:
		case Gt:
		case Le:
		case And:
		case Or:
		case Lt:
		{
			Runtime::ObjectBase *newObj = (tmpStack[1])->Compare(tmpStack[0], count_stack[i]->get_tag());
			delete tmpStack[0];
			tmpStack.pop_front();
			delete tmpStack[0];
			tmpStack.pop_front();
			tmpStack.push_front(newObj);
			break;
		}
		case Add:
		{
			(tmpStack[1])->SelfAdd(tmpStack[0]);
			delete tmpStack[0];
			tmpStack.pop_front();
			break;
		}
		case Sub:
		{
			(tmpStack[1])->SelfSub(tmpStack[0]);
			delete tmpStack[0];
			tmpStack.pop_front();
			break;
		}
		case Mul:
		{
			(tmpStack[1])->SelfMul(tmpStack[0]);
			delete tmpStack[0];
			tmpStack.pop_front();
			break;
		}
		case Div:
		{
			(tmpStack[1])->SelfDiv(tmpStack[0]);
			delete tmpStack[0];
			tmpStack.pop_front();
			break;
		}
		case Assign:
		{
			auto a=*environment->stack_block.find_variable(count_stack[i - 2]) = *tmpStack[0];
			delete tmpStack[0];
			tmpStack.pop_front();
			delete tmpStack[0];
			tmpStack.pop_front();
			tmpStack.push_front(new Runtime::ObjectBase(a));
		}
			break;
		case MM:
		case PP:
		case Id:
			tmpStack.push_front(GetObjectValue(i));
			break;
		default:
			break;
		}
		//tmpStack.push_back(count_stack[i]);
	}
	if (tmpStack.empty())
		return nullptr;
	return tmpStack.front();
}
void yt::Parser::Expression::debug()
{
	for (auto & a : count_stack)
	{
		std::cout << a->to_string();
	}
}

yt::Runtime::ObjectBase * yt::Parser::Expression::GetObjectValue(size_t &i)
{
	switch (count_stack[i]->get_tag())
	{
	case Lexer::Tag::PP:
		i++;
		if (count_stack[i]->get_tag() == Lexer::Tag::Id)
			return new Runtime::ObjectBase(environment->stack_block.find_variable(count_stack[i])->operator++());
		throw std::runtime_error("damn it");
	case Lexer::Tag::MM:
		i++;
		if (count_stack[i]->get_tag() == Lexer::Tag::Id)
			return new Runtime::ObjectBase(environment->stack_block.find_variable(count_stack[i])->operator--());
	case Lexer::Tag::Id:
		return new Runtime::ObjectBase(*environment->stack_block.find_variable(count_stack[i]));
	default:
		break;
	}
}
