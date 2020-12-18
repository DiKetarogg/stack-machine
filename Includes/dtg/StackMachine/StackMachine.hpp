#ifndef DTG_STACKMACHINE_STACKMACHINE_HPP
#define DTG_STACKMACHINE_STACKMACHINE_HPP
#include <fcntl.h>
#include <stdexcept>
#include "Lexer.hpp"
#include "Error.hpp"

namespace dtg{

template <class PrimitiveType, size_t MEMORY_SIZE, size_t STACK_SIZE>
class StackMachine {
	public:
		using value_type	= PrimitiveType;
		using function_type	= void(*)(void);
	public:

		StackMachine() = default;

		StackMachine(char* file): m_File(open(file, O_RDONLY)) {}

		StackMachine(int file): m_File(file) {}

		StackMachine(const StackMachine&) = delete;

		StackMachine(StackMachine&& other) = delete;
/*
		void Open(char* file) {
			if (m_File)
				close(m_File);
			m_File = open(file, O_RDONLY);
		}
*/
		

	private:
		int m_File;
		std::vector<Stackmachine::Error> m_Errors;
		RawArray<MEMORY_SIZE - sizeof(int) -
			sizeof(std::vector<Stackmachine::Error>),
			value_type> m_Container;
};


}




#endif
