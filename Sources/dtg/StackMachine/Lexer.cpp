#include "dtg/StackMachine/Lexer.hpp"
#include <stdexcept>
#include <cstring>

namespace dtg {
namespace Stackmachine {

void Lexer::Parse() {
	m_Mode = global;
	m_Iterator = const_cast<char*>(m_Contents);
	m_Tokens.clear();
	m_Tokens.reserve(256);
	while(*m_Iterator) {
		while (isspace(*m_Iterator))
			++m_Iterator;
		ExtractToken();
	}
}

void Lexer::ExtractToken() {
	unsigned char i;
	char word[9];

	if (islower(*m_Iterator)) {
		i = 0;
		do {
			word[i] = *m_Iterator;
			++m_Iterator;
			++i;
		} while (*m_Iterator && !isspace(*m_Iterator) && i != 8);
		word[i] = 0;
		unsigned char left	= Token::Type::add;
		unsigned char middle	= Token::Type::ifgr;
		unsigned char right	= Token::Type::sub;
		int cmp;
		while (right - left != 1) {
			cmp = strcmp(word, g_Tokens[middle]);
			if (cmp < 0) {
				right = middle;
				middle -= (right - left) / 2;
			}
			else if (cmp > 0) {
				left = middle;
				middle += (right - left) / 2;
			}
			else {
				m_Tokens.push_back(static_cast<enum
						Token::Type>(middle));
				return;
			}
		}
	}
	else {
		switch(*m_Iterator) {
			case *g_Tokens[Token::Type::comment]:
				m_Tokens.push_back(Token::Type::comment);
				break;
			case *g_Tokens[Token::Type::colon]:
				m_Tokens.push_back(Token::Type::colon);
				break;
			case *g_Tokens[Token::Type::openbrace]:
				m_Tokens.push_back(Token::Type::openbrace);
				break;
			case *g_Tokens[Token::Type::closebrace]:
				m_Tokens.push_back(Token::Type::closebrace);
				break;
			default:
				m_Tokens.push_back(Token::Type::error);
		}
		++m_Iterator;
		return;
	}
	m_Tokens.push_back(Token::Type::error);
}

}
}

