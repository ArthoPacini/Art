/* Function class is an interpreter class 
It constructs a stack machine from some mathematical expression

It may be construct like art::Function xSquaredFunction("x*x");
and be used like xSquaredFunction.getResult(2);

It may also receive multiple variables like art::Function functionExampleVar("x*y*z");
and be used like functionExampleVar.getResult({2,4,6});

Written by Artho Pacini
*/

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace art 
{
    class Function
    {
        private:
        std::string originalExpression;
        std::vector<std::string> reversePolishNotationFunction;
        std::vector<std::string> variableNames;
        std::vector<double> variableValues;
        std::vector<std::pair<std::string, double>> variableNamesAndValues;
        uint16_t variableCount;

        public:

        //Constructs the function with a given mathematical expression
        Function(std::string infixExpression)
        {
            //std::cout << "[Function]: Building function..." << std::endl;
            originalExpression = infixExpression;

            std::vector<std::string> expressionParts = getExpressionParts(infixExpression);
            for(const auto & e : expressionParts)
            {
                if(isVariable(e))
                    variableNames.push_back(e);
            }

            //Convert to reverse polish notation

            std::vector<std::string> reversePolishNotation = getReversePolishNotation(expressionParts);

            reversePolishNotationFunction = reversePolishNotation;
            variableCount = variableNames.size();

            //std::cout << "[Function]: Function built..." << std::endl;
        }

        uint16_t getVariableCount()
        {
            return variableCount;
        }

        //Returns the priority of the operator
        std::size_t getOperatorPriority(char c)
        {
            switch(c)
            {
                case ')': return 0;
                case '(': return 0;
                
                case '+': return 1;
                case '-': return 1;

                case '*': return 2;
                case '/': return 2;

                case '^': return 3;

                default: return 0;
            }
        }

        //Check if given char is a number or not.
        bool isNumber(char c)
        {
            const std::string numbers = "0123456789.,";
            for(const auto & n : numbers)
                if(c == n) 
                    return true;

            return false;
        }

        //Check if given char is a operator or not
        bool isOperator(char c)
        {
            const std::string operators = "+-*/^()";
            for(const auto & op : operators)
                if(c == op)
                    return true;
            
            return false;
        }

        //Check if given char is a variable of not
        bool isVariable(char c)
        {
            const std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            for(const auto & a : alpha)
                if(c == a)
                    return true;
            
            return false;
        }

        //Return a vector containing all identified parts of a given expression. i.e "x+3.14*y" would return {"x", "+", "3.14", "*", "y"}
        std::vector<std::string> getExpressionParts(std::string & infixExpression)
        {
            //std::cout << "[Function]: Building expression 1/2..." << std::endl;

            std::vector<std::string> expression;
            for(unsigned i = 0; i < infixExpression.length(); i++)
            {
                char c = infixExpression[i];
                if(c == ' ')
                    continue;
                if(isNumber(c))
                {
                    unsigned j = 0;
                    std::string number = "";
                    while(isNumber(infixExpression[i+j]) && i+j < infixExpression.length())
                    {
                        if(infixExpression[i+j] == ',')
                            infixExpression[i+j] = '.';
                        number.push_back(infixExpression[i+j]);
                        j++;
                    }

                    expression.push_back(number);
                    i+=j-1;
                }
                else
                if(isOperator(c))
                {
                    std::string op;
                    op.push_back(c);
                    expression.push_back(op);
                }
                else
                if(isVariable(c))
                {
                    std::string variable;
                    variable.push_back(c);
                    expression.push_back(variable);
                }
                
            }
            return expression;
        }

        //Check if given std::string is a number
        bool isNumber(const std::string & s)
        {
            for(auto const & c : s)
                if(!isNumber(c))
                    return false;

            return true;
        }

        //Check if given std::string is a variable
        bool isVariable(const std::string & s)
        {
            for(auto const & c : s)
                if(!isVariable(c))
                    return false;

            return true;
        }

        //Check if given std::string is a operator
        bool isOperator(const std::string & s)
        {
            for(auto const & c : s)
                if(!isOperator(c))
                    return false;

            return true;
        }

        //Return a vector containing all parts of the expression, in the reverse polish notation
        std::vector<std::string> getReversePolishNotation(std::vector<std::string> & expressionParts)
        {
            //std::cout << "[Function]: Building expression 2/2..." << std::endl;

            std::vector<std::string> reversePolishNotation;
            std::vector<std::string> operatorStack;

            for(const auto & e : expressionParts)
            {
                if(isNumber(e) || isVariable(e))
                {
                    reversePolishNotation.push_back(e);
                }
                else
                if(isOperator(e))
                {
                    if(operatorStack.size() == 0 || e.back() == '(')
                        operatorStack.push_back(e);
                    else
                    {
                        if(e.back() == ')')
                        {
                            while(operatorStack.back().back() != '(' && operatorStack.size() > 0)
                            {
                                reversePolishNotation.push_back(operatorStack.back());
                                operatorStack.pop_back();
                            }
                            operatorStack.pop_back();
                            continue;
                        }

                        while(getOperatorPriority(operatorStack.back().back()) >= getOperatorPriority(e.back()))
                        {
                            reversePolishNotation.push_back(operatorStack.back());
                            operatorStack.pop_back();
                            if(operatorStack.size() == 0)
                                break;
                        }

                        operatorStack.push_back(e);
                    }
                }
                
            }

            if(operatorStack.size() > 0)
                while(operatorStack.size() > 0)
                {
                    reversePolishNotation.push_back(operatorStack.back());
                    operatorStack.pop_back();
                }
            return reversePolishNotation;
        }

        

        //Get the result of the function, passing one variable
        double getResult(double v)
        {
            std::vector<double> _v = {v};
            return getResult(_v);
        }

        //Get the result of the function, passing multiple variables
        double getResult(std::vector<double> _variableValues = {0})
        {
            variableNamesAndValues.clear();
            variableNamesAndValues.reserve(_variableValues.size());

            variableValues = _variableValues;

            for(unsigned i = 0; i < variableNames.size(); i++)
                if(i > _variableValues.size())
                    break;
                else
                {
                    bool doesVariableAlreadyExists = false;
                    for(const auto & v : variableNamesAndValues)
                        if(variableNames[i] == v.first)
                        {
                            doesVariableAlreadyExists = true;
                            break;
                        }
                    
                    if(!doesVariableAlreadyExists)
                        variableNamesAndValues.push_back(std::make_pair(variableNames[i], _variableValues[i]));

                }


            std::stack<double> calculusStack;

            for(auto const & r : reversePolishNotationFunction)
            {
                if(isNumber(r))
                    calculusStack.push(std::stod(r));
                else
                if(isVariable(r))
                {
                    bool doesVariableExist = false;
                    for(const auto & v : variableNamesAndValues)
                        if(r == v.first)
                        {
                            calculusStack.push(v.second);
                            doesVariableExist = true;
                        }
                    if(!doesVariableExist)
                        throw std::runtime_error("Variable" + r + " not declared or found");

                }
                else
                if(isOperator(r))
                {
                    double operand_02 = calculusStack.top();
                    calculusStack.pop();
                    double operand_01 = calculusStack.top();
                    calculusStack.pop();

                    switch (r.back())
                    {
                    case '+':
                        calculusStack.push(operand_01 + operand_02);
                        break;
                    case '-':
                        calculusStack.push(operand_01 - operand_02);
                        break;
                    case '*':
                        calculusStack.push(operand_01 * operand_02);
                        break;
                    case '/':
                        calculusStack.push(operand_01 / operand_02);
                        break;
                    case '^':
                        calculusStack.push(std::pow(operand_01,operand_02));
                    default:
                        break;
                    }
                }
            }

            return calculusStack.top();
        }

        //Return the original expression
        std::string getOriginalExpression()
        {
            return originalExpression;
        }

        //Return all variable values
        std::vector<double> getVariablesValues()
        {
            return variableValues;
        }

        //Return all variable names
        std::vector<std::string> getVariablesNames()
        {
            return variableNames;
        }

        //Return an string containing all variables names and it value
        std::string getVariableNamesAndValues()
        {


            std::string v;

            for(unsigned i = 0; i < variableNamesAndValues.size(); i++)
            {
                v += variableNamesAndValues[i].first;
                v += ": ";
                v += std::to_string(variableNamesAndValues[i].second);
                if(!(i+1 >= variableNamesAndValues.size()))
                    v += ", ";
            }

            return v;
        }

        
    };
}

#endif