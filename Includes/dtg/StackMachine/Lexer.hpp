#ifndef DTG_STACKMACHINE_LEXER_HPP
#define DTG_STACKMACHINE_LEXER_HPP

#include "Token.hpp"
#include <vector>

namespace dtg {
namespace Stackmachine {


class Lexer {
	protected:
		enum Mode {
			global,
			main,
			function
		};
	public:
		Lexer(): m_Contents(0) {}

		Lexer(const char* contents): m_Contents(contents){}

		Lexer(const Lexer&) = delete;

		Lexer(Lexer&&) = delete;

		void Parse();

		void SetContents(const char* string) {
			m_Contents = string;
		}

		std::vector<Token>& GetTokens() {
			return m_Tokens;
		}
	protected:

		void ExtractToken();

	private:
		const char*		m_Contents;
		char*			m_Iterator;
		std::vector<Token>	m_Tokens;
		Mode			m_Mode;
		long long		m_Number;
};

}
}
#endif
