#ifndef RPN_HPP
# define RPN_HPP

#include <algorithm>
#include <stack>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>

class RPN
{
private:
	std::stack<int> _numbers;
	RPN();
	RPN(std::string arg);
	RPN(const RPN& copy);
	RPN& operator=(const RPN& src);
	~RPN();

public:
	static void parse_arg(const std::string& arg);
	static void calculate(const std::string& arg);
};

#endif