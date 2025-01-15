/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:17:28 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/15 20:59:00 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// ortodox Canonica Desactivada
RPN::RPN(){}
RPN::RPN(std::string arg){(void)arg;}
RPN::RPN(const RPN& copy){_numbers = copy._numbers;}
RPN& RPN::operator=(const RPN& src){_numbers = src._numbers;
return *this;}
RPN::~RPN(){}

static int add(int a, int b) { return a + b; }
static int substract(int a, int b) { return a - b; }
static int multiply(int a, int b) { return a * b; }
static int divide(int a, int b) { 
    if (b == 0) {
        throw std::runtime_error("Error: Division by zero");
    }
    return a / b; 
}

bool static operatorFound(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}
void RPN::parse_arg(const std::string& arg){
	size_t numbers = 0;
	size_t operators = 0;
	if (arg.empty())
		throw std::logic_error("Error: Empty arguments");
	for(size_t i = 0; i < arg.size(); i++)
	{
		if (std::isdigit(arg.at(i)))
			numbers++;
		if (operatorFound(arg.at(i)))
			operators++;
		if (!operatorFound(arg.at(i)) && !std::isdigit(arg.at(i)) && arg.at(i) != ' ')
			throw std::logic_error("Error: Invalid element found");
		if (std::isdigit(arg.at(i)) && (i + 1) < arg.size() && arg.at(i + 1) != ' ')
			throw std::logic_error("Error: Invalid format, remember to use space after each number/operator");
		if (operatorFound(arg.at(i)) && i + 1 < arg.size() && arg.at(i + 1) != ' ')
			throw std::logic_error("Error: Invalid format, remember to use space after each number/operator");
	}
	if (numbers < 2)
		throw std::logic_error("Error: Not enough Numbers");
	if (operators < 1)
		throw std::logic_error("Error: Operator not found");
	if (operators != numbers - 1)
		throw std::logic_error("Error: Logic error");
	if (!operatorFound(*(arg.end() - 1)))
		throw std::logic_error("Error: Operator needed at the end");
}

typedef int (*Operation)(int, int);

void RPN::calculate(const std::string& arg)
{
	parse_arg(arg);
	static std::stack<int> _numbers;
	std::string operators[4] = {"+", "-", "*", "/"};
	Operation operations[4] = {add, substract, multiply, divide};
	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg.at(i) == ' ')
			continue;
		if (std::isdigit(arg.at(i)))
			_numbers.push(arg.at(i) - '0');
		else if (operatorFound(arg.at(i)))
		{
			if (_numbers.size() < 2)
				throw std::logic_error("Error: Logic error");
			int b =	_numbers.top();
			_numbers.pop();
			int a = _numbers.top();
			_numbers.pop();
			for (size_t j = 0; j < 4; j++)
			{
				if (arg.at(i) == operators[j][0])
				{
					int result = operations[j](a, b);
					_numbers.push(result);
				}
			}
		}
		else 	
			throw std::runtime_error("Peto!");
	}
	if (_numbers.size() != 1)
		throw std::runtime_error("Error: Pending elements on the stack");
	std::cout << "Result: " << _numbers.top() << std::endl;	
}