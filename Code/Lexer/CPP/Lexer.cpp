#include "../HPP/Lexer.hpp"
using namespace yt::Lexer;
bool _is_operator(char ch)
{
	switch (ch)
	{
	case '+':case '-':case '*':case '/':case '&':case '|':case ':':case'=':case'<':case'>':case'[':case']':case'(':case')':
	case'{':case'}':case';':case ',':case '.':case'!':case'#':
		return true;
	default:
		return false;
	}
}
void Lexer::read_string() {
	std::string value;
	if (content[index] == '\"')
		index++;
	else
		throw std::runtime_error("a string-literal must start with\"");
	for (; content[index] != '\"'; index++)
	{
		if (index >= content.size())
		{
			throw std::runtime_error("string-literal isn't matched");
		}
		if (content[index] == '\\')
		{
			if (index >= content.size() - 1)
			{
				throw std::runtime_error("string-literal isn't matched");
			}
			index++;
			switch (content[index]) {
			case 'n':
				value += '\n';
				break;
			case 't':
				value += '\t';
				break;
			case '\"':
				value += '\"';
				break;
			case '\'':
				value += '\'';
				break;
			case '\\':
				value += '\\';
				break;
			}
		}
		else
			value += content[index];
	}
	index++;
	token_stream.push_back(new yt::Lexer::VString(value));
}
void yt::Lexer::Lexer::read_char()
{
	char ch = 0;
	if (content[index++] != '\'')
	{
		throw std::runtime_error("a char-literal must start with\'");
	}
	if (content[index] == '\\')
	{
		index++;
		switch (content[index])
		{
		case 'n':
			ch = '\n';
			break;
		case 't':
			ch = '\t';
			break;
		case '\\':
			ch = '\\';
			break;
		case '\'':
			ch = '\'';
			break;
		case '\"':
			ch = '\"';
			break;
		default:
			throw std::runtime_error("unexcepted escape char!");
			break;
		}
		index++;
		token_stream.push_back(new VChar(ch));
		if (content[index] == '\'')
		{
			index++;
			return;
		}
		else
		{
			throw std::runtime_error("char-literal must be a single char.");
		}
	}
	else
	{
		ch = content[index++];
		token_stream.push_back(new VChar(ch));
		if (content[index] == '\'')
		{
			index++;
			return;
		}
		else
		{
			throw std::runtime_error("char-literal must be a single char.");
		}
	}
}
void yt::Lexer::Lexer::read_number()
{
	int64_t intPart = 0;
	// 负号被当作一种运算;
	while (isdigit(content[index]))
	{
		intPart = intPart * 10 + (content[index++] - 48);
	}
	if (content[index] != '.')
	{
		token_stream.push_back(new VInt(intPart));
		return;
	}
	else if (content[index] == 'L')
	{
		index++;
		token_stream.push_back(new VLong(intPart));
		return;
	}
	index++;
	double v = (double)intPart;
	double v2 = 0.1;
	while (isdigit(content[index]))
	{
		v += v2*(content[index++] - 48);
		v2 /= 10;
	}
	token_stream.push_back(new VDouble(v));
}
void yt::Lexer::Lexer::read_word()
{
	std::string word;
	while ((isalnum(content[index]) || content[index] == '_') && index < content.size())
	{
		word += content[index++];
	}
	auto result = keyword_map().find(word);
	if (result == keyword_map().end())
	{
		token_stream.push_back(new TId(word));
		return;
	}
	token_stream.push_back(new Token(result->second));

}
void yt::Lexer::Lexer::read_symbol()
{
	std::string tmp(1, content[index]);
	if (index < content.size() - 1 && _is_operator(content[index + 1]))
	{
		tmp += content[index + 1];
	}
	auto result = symbol_map().find(tmp);
	if (result == symbol_map().end())
	{
		token_stream.push_back(new Token(symbol_map().find(std::string(1, content[index++]))->second));
		return;
	}
	index += tmp.size();
	token_stream.push_back(new Token(result->second));
}
void Lexer::debug()
{
	for (const auto & a : token_stream)
	{
		std::cout << a->to_string();
	}
}

void yt::Lexer::Lexer::init_token_stream()
{
	while (index < content.size())
	{
		switch (content[index])
		{
		case '\'':
			read_char();
			continue;
		case '\n':
			token_stream.push_back(new EndLine());
			index++;
			continue;
		case '\"':
			read_string();
			continue;
		case '/':
			index++;
			if (content[index] != '/')
			{
				index--;
				break;
			}
			else
			{
				while (index!=content.size()&&content[index++] != '\n')
					index++;
				continue;
			}
			break;
		case '\t':
		case ' ':
			index++;
			continue;
		default:
			break;
		}
		if (isdigit(content[index]))
			read_number();
		else if (_is_operator(content[index]))
			read_symbol();
		else if (isalpha(content[index]) || content[index] == '_')
			read_word();
		else
		{
			throw std::runtime_error(std::string(1, content[index]) + " unkonwn char");
		}
	}
	token_stream.push_back(new EndLine());
}
