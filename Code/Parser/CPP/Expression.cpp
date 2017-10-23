#include "../HPP/Expression.hpp"
using namespace yt::Parser;

void yt::Parser::Expression::CreateExpressionStack()
{
	Lexer::Token *currentTok = environment->token_stream->operator[](environment->current_pos);
	while (currentTok->get_tag() != Lexer::Endl)
	{
		Lexer::Token *currentTok = environment->token_stream->operator[](environment->current_pos);
		switch (currentTok->get_tag())
		{
		case Lexer::Id:
			tmpStack.push_back(GetObjectValue());
			environment->current_pos++;
			continue;
		case Lexer::Add:
			tmpStack.push_back(_Eunit(_Eunit::Operator::Add));
			environment->current_pos++;
			continue;
		case Lexer::Sub:
			tmpStack.push_back(_Eunit::Sub);
			environment->current_pos++;
			continue;
		case Lexer::Div:
			tmpStack.push_back(_Eunit::Div);
			environment->current_pos++;
			continue;
		case Lexer::Mul:
			tmpStack.push_back(_Eunit::Mul);
			environment->current_pos++;
			continue;
		case Lexer::Tag::TLiteralInt:
			tmpStack.push_back(new Runtime::ObjectBase(*(int32_t*)currentTok->get_value()));
			environment->current_pos++;
			continue;
		case Lexer::Tag::TLiteralDouble:
			tmpStack.push_back(new Runtime::ObjectBase(*(double*)currentTok->get_value()));
			environment->current_pos++;
			continue;
		case Lexer::Tag::TLiteralChar:
			tmpStack.push_back(new Runtime::ObjectBase(*(char*)currentTok->get_value()));
			environment->current_pos++;
			continue;
		case Lexer::Tag::TLiteralString:
			tmpStack.push_back(new Runtime::ObjectBase(*(std::string*)currentTok->get_value()));
			environment->current_pos++;
			continue;
		case Lexer::Tag::TLiteralLong:
			tmpStack.push_back(new Runtime::ObjectBase(*(std::int64_t*)currentTok->get_value()));
			environment->current_pos++;
			continue;
		case Lexer::Tag::Lk:
			tmpStack.push_back(_Eunit::Lk);
			environment->current_pos++;
			continue;
		case Lexer::Tag::Rk:
			tmpStack.push_back(_Eunit::Rk);
			environment->current_pos++;
			continue;
		default:
			return;
		}
	}
}

yt::Runtime::ObjectBase * yt::Parser::Expression::GetObjectValue()
{
	return environment->stack_block.find_variable(environment->token_stream->operator[](environment->current_pos));
}
yt::Runtime::ObjectBase * yt::Parser::Expression::GetResult()
{
	for (size_t i = 0; i < outPut.size(); i++)
	{
		switch (outPut[i].op)
		{
		case _Eunit::Add:
		{
			int tmp_index = i - 2;
			_Eunit need_to_push = outPut[tmp_index].obj->Add(outPut[i - 1].obj);
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut.insert(outPut.begin() + (tmp_index), need_to_push);
			i -= 2;
			break;
		}
		case _Eunit::Sub:
		{
			int tmp_index = i - 2;
			_Eunit need_to_push = outPut[tmp_index].obj->Sub(outPut[i - 1].obj);
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut.insert(outPut.begin() + (tmp_index), need_to_push);
			i -= 2;
			break;
		}
		case _Eunit::Mul:
		{
			int tmp_index = i - 2;
			_Eunit need_to_push = outPut[tmp_index].obj->Mul(outPut[i - 1].obj);
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut.insert(outPut.begin() + (tmp_index), need_to_push);
			i -= 2;
			break;
		}
		case _Eunit::Div:
		{
			int tmp_index = i - 2;
			_Eunit need_to_push = outPut[tmp_index].obj->Div(outPut[i - 1].obj);
			std::cout << "that's";
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut[tmp_index].destroData();
			outPut.erase(outPut.begin() + (tmp_index));
			outPut.insert(outPut.begin() + (tmp_index), need_to_push);
			i -= 2;
			break;
		}
		case _Eunit::Value:
			continue;
		default:
			throw std::runtime_error("runtime error6");
		}
	}
	return outPut.front().obj;
}

void yt::Parser::Expression::Translate()
{
	for (auto & a : tmpStack)
	{
		switch (a.op)
		{
		case _Eunit::Value:
			//  变量总是先压入输入中.
			outPut.push_back(a);
			break;
		case _Eunit::Lk:
			// '(' 总是被压入栈中
			operatorStack.push_back(a);
			break;
		case _Eunit::Add:
		case _Eunit::Sub:
		case _Eunit::Mul:
		case _Eunit::Div:
			//顶部遇到了比自己厉害的, 然后就pass-pass, 直到比自己差点的. 
			//当然一样厉害的还是pass 不敢打啊.'('除外啦. 毕竟它走他也不走 它只认')'
			while (!operatorStack.empty() && operatorStack.back().op != _Eunit::Lk&&get_priority(a) <= get_priority(operatorStack.back()))
				pop_top();
			operatorStack.push_back(a);
			break;
		case _Eunit::Rk:
			while (operatorStack.back().op != _Eunit::Lk)
			{
				pop_top();
			}
			operatorStack.pop_back();
			break;
		default:
			throw std::runtime_error("runtime error5");
		}
	}
	while (!operatorStack.empty())
	{
		pop_top();
	}
}

void yt::Parser::Expression::debug()
{
	return;
	for (auto & a : outPut)
	{
		std::cout << a.to_string();
	}
}