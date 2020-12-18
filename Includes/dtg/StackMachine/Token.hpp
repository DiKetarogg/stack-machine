#pragma once
#ifndef DTG_STACKMACHINE_TOKEN_HPP
#define DTG_STACKMACHINE_TOKEN_HPP

#include <cstring>
#include <cstddef>
#include "dtg/Utilities.hpp"

namespace dtg {
namespace Stackmachine {

inline constexpr const char *g_Tokens[] = {
	"",
	"#",
	":",
	"add",
	"call",
	"callext",
	"div",
	"dup",
	"function",
	"goto",
	"ifeq",
	"ifgr",
	"main",
	"mul",
	"peek",
	"pop",
	"push",
	"return",
	"sub",
	"{",
	"}"
};


struct Token {

	enum Type {
		error,
		comment,
		colon,
		add,
		call,
		callext,
		div,
		dup,
		function,
		goto_,
		ifeq,
		ifgr,
		main,
		mul,
		peek,
		pop,
		push,
		return_,
		sub,
		openbrace,
		closebrace
	};

	Token() = delete;

	Token(enum Type token): m_Token(token) {}

	Token(const Token& other): m_Token(other.m_Token){}

	Token& operator =(enum Type token) {
		m_Token = token;
		return *this;
	}

	Token& operator =(const Token& other) {
		m_Token = other.m_Token;
		return *this;
	}

	const char* GetString() const {
		return g_Tokens[m_Token];
	}

	enum Type GetIndex() const {
		return m_Token;
	}

	operator const char*() const {
			return g_Tokens[m_Token];
	}

/*	C++20
	bool operator <=>(char* string) const {
		return strcmp(g_Tokens[m_Token], string) <=> 0;
	}

	bool operator <=>(const Token& other) const {
		return m_Token <=> other.m_Token;
	}

	bool operator <=>(enum Type token) const {
		return m_Token <=> token;
	}
*/
	DTG_SPACESHIP_OPERATOR((strcmp(g_Tokens[m_Token], string)), 0, const char* string);

	DTG_SPACESHIP_OPERATOR(m_Token, other.m_Token, const Token& other);

	DTG_SPACESHIP_OPERATOR(m_Token, token, enum Type token);

	private:
		Type m_Token;
};

}
}

#endif
