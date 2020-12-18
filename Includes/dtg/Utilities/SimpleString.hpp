#ifndef DTG_SIMPLESTRING_HPP
#define DTG_SIMPLESTRING_HPP

#include <stdexcept>
#include "ArrayCopy.hpp"
#include "CountElems.hpp"

#ifndef DTG_NO_EXCEPT
#define DTG_STRING_OUT_OF_MEMORY throw std::runtime_error("dtg::SimpleString out of memory")
#else
#define DTG_STRING_OUT_OF_MEMORY
#endif

namespace dtg {

	template <class CharType>
	class BasicSimpleString {
		public:
			using value_type	= CharType;
			using pointer		= value_type*;
			using const_pointer	= const value_type*;
		public:
			BasicSimpleString():m_string(0){}

			BasicSimpleString(const BasicSimpleString& other):m_string(new value_type[countElems(other.m_string) + 1]) {
				if (m_string)
					dtg::TerminatedArrayCopy(m_string, other.m_string);
				else
					DTG_STRING_OUT_OF_MEMORY;
			}

			BasicSimpleString(BasicSimpleString&& other) noexcept :m_string(other.m_string) {
				other.m_string = 0;
			}

			BasicSimpleString(const_pointer string):m_string(new value_type[countElems(string) + 1]) {
				if (m_string)
					dtg::TerminatedArrayCopy(m_string, string);
				else
					DTG_STRING_OUT_OF_MEMORY;
			}

			BasicSimpleString& operator = (const BasicSimpleString& other) {
				m_string = new value_type[countElems(other.m_string) + 1];
				if (m_string)
					dtg::TerminatedArrayCopy(m_string, other.m_string);
				else
					DTG_STRING_OUT_OF_MEMORY;
				return *this;
			}

			BasicSimpleString& operator = (BasicSimpleString&& other) noexcept {
				if (this != &other) {
					delete[] m_string;

					m_string = other.m_string;
					other.m_string = 0;
				}
				return *this;
			}

			BasicSimpleString& operator = (const_pointer string) {
				delete[] m_string;
				m_string = new value_type[countElems(string) + 1];
				if (m_string)
					dtg::TerminatedArrayCopy(m_string, string);
				else
					DTG_STRING_OUT_OF_MEMORY;
				return *this;
			}
			~BasicSimpleString() {
				delete m_string;
			}

			operator const_pointer() const noexcept {
				return m_string;
			}

			operator pointer() noexcept {
				return m_string;
			}

		private:

		pointer m_string;
	};
	typedef BasicSimpleString<char>		SimpleString;
	typedef BasicSimpleString<wchar_t>	WSimpleString;
}

#undef DTG_DTG_STRING_OUT_OF_MEMORY

#endif
