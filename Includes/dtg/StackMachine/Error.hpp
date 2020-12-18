#ifndef DTG_STACKMACHINE_ERROR_HPP
#define DTG_STACKMACHINE_ERROR_HPP

#include "Token.hpp"


namespace dtg {
namespace Stackmachine {

	
class Error {
	public:
		Error(Token expected, size_t line, size_t character)
				:m_Token(expected),
				m_Line(line),
				m_Char(character) {}

		Error() = delete;

		Error(const Error&) = delete;

		Error(Error&&) = delete;

	private:
		Token m_Token;
		size_t m_Line;
		size_t m_Char;
};

}
}
#endif
