#include <stack>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <limits>

/*
** Positive overflow
** If both numbers are postive, you want to check
** if a is greater than INT_MAX divided by b. If
** this is true, then multiplying a by b will be
** larger than INT_MAX.
** Negative overflow
** If one number is negative, the logic is similar
** but uses INT_MIN.
** If both of the numbers are negative this
** doesn't work. However, this can't happen in this
** assignment?
*/
bool will_multiply_overflow(int a, int b)
{
    if (a == 0 || b == 0)
        return false;
    if (a > std::numeric_limits<int>::max() / b || a < std::numeric_limits<int>::min() / b)
        return true;

    return false;
}

bool will_add_overflow(int a, int b)
{
    if (a > 0 && b > 0) /* Check for overflow when adding two positive integers  */
        return a > std::numeric_limits<int>::max() - b;
    else if (a < 0 && b < 0) /* Check for overflow when adding two negative integers */
        return a < std::numeric_limits<int>::min() - b;
    return false; /* Overflow is not possible when adding two integers with different signs */
}

bool will_subtract_overflow(int a, int b)
{
    if (a > 0 && b < 0) /* Check for overflow when subtracting a negative integer from a positive integer */
        return a > std::numeric_limits<int>::max() + b;
    else if (a < 0 && b > 0) /* Check for overflow when subtracting a positive integer from a negative integer */
        return a < std::numeric_limits<int>::min() + b;
    return false; /* Overflow is not possible when subtracting integers with the same sign */
}

inline int isoperator(int c)
{
    switch (c)
    {
    case '+':
        return true;
    case '-':
        return true;
    case '/':
        return true;
    case '*':
        return true;
    default:
        return false;
    }
}

int main(int argc, char *argv[2])
{
    if (argc != 2)
    {
        std::cerr << "Error: number of arguments is not equal to 1\n";

        return 1;
    }

    char *expression = argv[1];
    std::size_t len = std::strlen(expression);
    if (len == 0)
    {
        std::cerr << "Error: empty input\n";

        return 1;
    }

    for (int i = 0; expression[i]; i++)
    {
        if (expression[i] == ' ')
            continue;
        if (!std::isdigit(expression[i]) && !isoperator(expression[i]))
        {
            std::cerr << "Error: input contains something else besides digit(s) or operator(s)\n";

            return 2;
        }
    }

    std::stack<int> a{};
    try
    {
        for (int i = 0; expression[i]; i++)
        {
            if (expression[i] == ' ')
                continue;

            if (std::isdigit(expression[i]))
                a.push(expression[i] - '0');
            else if (isoperator(expression[i]))
            {
                if (a.size() < 2)
                    throw std::runtime_error("Error: not enough operands for operator");
                int operand2 = a.top();
                a.pop();
                int operand1 = a.top();
                a.pop();

                switch (expression[i])
                {
                case '+':
                    if (will_add_overflow(operand1, operand2))
                        throw std::runtime_error("Error: int overflow during addition");
                    else
                        a.push(operand1 + operand2);
                    break;
                case '-':
                    if (will_subtract_overflow(operand1, operand2))
                        throw std::runtime_error("Error: int overflow during subtraction");
                    else
                        a.push(operand1 - operand2);
                    break;
                case '/':
                    if (operand2 == 0)
                        throw std::runtime_error("Error: division by zero");
                    else
                        a.push(operand1 / operand2);
                    break;
                case '*':
                    if (will_multiply_overflow(operand1, operand2))
                        throw std::runtime_error("Error: int overflow during multiplication");
                    else
                        a.push(operand1 * operand2);
                    break;
                }
            }
        }

        if (a.size() != 1)
            throw std::runtime_error("Error: invalid input");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';

        return 3;
    }
    std::cout << a.top() << '\n';

    return 0;
}

/*
 * ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 + "
 * ./RPN "2147483647 2 +"
 * ./RPN "7 7 * 7 -"
 * ./RPN "7,0 7 * 7 -"
 * ./RPN "7.0 7 * 7 -"
 * ./RPN "1 2 * 2 / 2 * 2 4 - +"
 * ./RPN "(1 + 1)"
 * ./RPN "8 8 8 8 8 8 8 8 8 8 8 8 * * * * * * * * *"
 * ./RPN "8 0 /"
 */