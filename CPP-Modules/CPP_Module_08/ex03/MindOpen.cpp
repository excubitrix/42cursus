#include "MindOpen.hpp"

MindOpen::MindOpen(const char* file) : _i(0), _array(std::vector<char>(30000, 0)), _cur(0) {
	try
	{
		std::ifstream in;
		in.open(file);
		std::stringstream ss;
		ss << in.rdbuf();
		this->_code = ss.str();
		in.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	this->_getInstructions();
}

MindOpen::MindOpen(MindOpen const& src) : _array(std::vector<char>(30000, 0)) {
	*this = src;
}

MindOpen::~MindOpen(void) {
	this->_array.clear();
	std::deque<IInstruction*>::iterator it;
	for (it = this->_instructions.begin(); it != this->_instructions.end(); it++)
		delete *it;
	this->_instructions.clear();
}

MindOpen&	MindOpen::operator=(MindOpen const& src) {
	if (this != &src)
	{
		std::copy(src._code.begin(), src._code.end(), this->_code.begin());
		this->_i = src._i;
		std::copy(src._array.begin(), src._array.end(), this->_array.begin());
		this->_cur = src._cur;
		std::deque<IInstruction*>::iterator it;
		for (it = this->_instructions.begin(); it != this->_instructions.end(); it++)
			delete *it;
		this->_instructions.clear();
		std::copy(src._instructions.begin(), src._instructions.end(), this->_instructions.begin());
	}
	return *this;
}

const char*	MindOpen::SyntaxException::what() const throw() {
	return "Syntax error";
}

const char*	MindOpen::KillException::what() const throw() {
	return "EOF received";
}

char	MindOpen::getData(void) {
	return this->_array[this->_i];
}

void	MindOpen::moveRight(void) {
	this->_i++;
}

void	MindOpen::moveLeft(void) {
	this->_i--;
}

void	MindOpen::increment(void) {
	this->_array[this->_i]++;
}

void	MindOpen::decrement(void) {
	this->_array[this->_i]--;
}

void	MindOpen::readData(void) {
	char c;
	std::cin.get(c);
	if (std::cin.eof())
		throw KillException();
	this->_array[this->_i] = c;
}

void	MindOpen::writeData(void) {
	std::cout << getData();
	std::cout.flush();
}

void	MindOpen::next(void) {
	int sub = 1;

	do {
		this->_cur++;
		if (dynamic_cast<LoopStart*>(this->_instructions[this->_cur]))
			sub++;
		else if (dynamic_cast<LoopEnd*>(this->_instructions[this->_cur]))
			sub--;
	} while (sub != 0);
}

void	MindOpen::repeat(void) {
	int sub = 0;

	do {
		if (dynamic_cast<LoopStart*>(this->_instructions[this->_cur]))
			sub++;
		else if (dynamic_cast<LoopEnd*>(this->_instructions[this->_cur]))
			sub--;
		this->_cur--;
	} while (sub != 0);
}

void	MindOpen::execute(void) {
	std::fill(this->_array.begin(), this->_array.end(), 0);
	for (this->_cur = 0; this->_cur < this->_instructions.size(); this->_cur++)
		this->_instructions[this->_cur]->execute(*this);
}

void	MindOpen::_getInstructions(void) {
	int	count = 0;
	size_t length = this->_code.length();
	for (size_t i = 0; i < length; i++)
	{
		switch (this->_code[i])
		{
			case '/' :
				this->_instructions.push_back(new MoveRight());
				break ;
			case '\\' :
				this->_instructions.push_back(new MoveLeft());
				break ;
			case '!' :
				this->_instructions.push_back(new Increment());
				break ;
			case '?' :
				this->_instructions.push_back(new Decrement());
				break ;
			case '*' :
				this->_instructions.push_back(new Write());
				break ;
			case '~' :
				this->_instructions.push_back(new Read());
				break ;
			case '(' :
				this->_instructions.push_back(new LoopStart());
				count++;
				break ;
			case ')' :
				this->_instructions.push_back(new LoopEnd());
				count--;
				break ;
		}
	}
	if (count != 0)
		throw SyntaxException();
}

MindOpen::MindOpen(void) {
}
