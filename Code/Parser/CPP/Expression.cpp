#include "../HPP/Expression.hpp"
using namespace yt::Parser;

yt::Parser::Expression::Expression(Environment * env):environment(env)
{
	std::vector<Lexer::Token* >operatorStack;
	while (1)
	{
		switch (this_token()->get_tag())
		{
		case Lexer::Tag::TLiteralDouble:
		case Lexer::Tag::TLiteralString:
		case Lexer::Tag::TLiteralInt:
		case Lexer::Tag::TLiteralLong:
		case Lexer::Tag::TLiteralChar:
			//  ����ֵ������ѹ��������.
			count_stack.push_back(this_token());
			break;
		case Lexer::Tag::Lk:
			// '(' ���Ǳ�ѹ��ջ��
			operatorStack.push_back(this_token());
			break;
		case Lexer::Tag::Add:
		case Lexer::Tag::Sub:
		case Lexer::Tag::Mul:
		case Lexer::Tag::Div:
		case Lexer::Tag::Assign:
			//���������˱��Լ�������, Ȼ���pass-pass, ֱ�����Լ�����. 
			//��Ȼһ�������Ļ���pass ���Ҵ�.'('������. �Ͼ�������Ҳ���� ��ֻ��')'
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
			environment->current_pos++;
			return ;
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
		// ����Ǹ������Ļ�
		if (this_token()->get_tag() == Lexer::Tag::Lk)
		{
			throw std::runtime_error("void yt::Parser::Expression::skip() not compleleted ");
			// args_parse;
			// ���ҰѺ���ģ��д����ͷ����������ط�.
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
		throw std::runtime_error("\nError:"+this_token()->to_string()+"runtime_error12");
	}
}

yt::Runtime::ObjectBase * yt::Parser::Expression::GetResult()
{
	/*
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
	*/
}
void yt::Parser::Expression::debug()
{
	for (auto & a :count_stack)
	{
		std::cout << a->to_string();
	}
}