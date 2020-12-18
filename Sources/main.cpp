#include "dtg/StackMachine.hpp"
#include <iostream>

template <class Type>
void printEach(const Type& object) {
	unsigned i = 0;
	for (auto& e : object) {
		std::cout << '[' << e << ']';
		if (++i == 4) {
			i = 0;
			std::cout << '\n';
		}
		else
			std::cout << '\t';
	}
}

int main () {
	using namespace dtg;
	using namespace dtg::Stackmachine;
/*
	Token tokencall(Token::Type::call);
	Token tokenpeek(Token::Type::peek);
	std::cout << (tokencall == "call");
*/
	const char test[] = "function main { mul }";
	Lexer lexer;
	lexer.SetContents(test);
	lexer.Parse();
	auto& tokens = lexer.GetTokens();
	std::cout << '\n';
	printEach(tokens);

}
