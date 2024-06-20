#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
/*
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#                   -- [ CCalc ] --                         #  
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#

Software Name: CCalc
Version: 1.0.0
Authors: Aeternusdio.
Ecosystem: The ASP Software Development Software Suite. or (DSS)
[ Edited with Vim. ]
Date Written: Wednesday, june 19 2024

Description:
A CLI tool for calculating various mathematical (and others) operations.

License: ASP License V2 & MIT (Dual Licensed)
Website: No Wesbite.
Contact: No Contact.

Dependencies:
- NONE
------------------------------

The MIT License (MIT)

Copyright (c) 2024 Apache Software Production. (ASP)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

SLOWFETCH IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

double evaluate_expression(const char *expression);
double apply_operator(double a, double b, char op);
int precedence(char op);
int is_operator(char c);
int is_numeric(char c);

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        fprintf(stderr, "Usage: ccalc <option> <mathematical expression> (See README.md, section 4 on Usage.)\n");
        return 1;
    }
    
    if (strcmp(argv[1], "-calc") == 0) {
        
        char *expression = argv[2];
        double result = evaluate_expression(expression);
        printf("Result: %.2lf\n", result);
        
    } else if (strcmp(argv[1], "-sqrt") == 0) {
        
        char *number_str = argv[2];
        if (strchr(number_str, ' ') != NULL) {
            fprintf(stderr, "Error: Invalid input. Spaces are not allowed in the expression.\n");
            return 1;
        }
        for (int i = 0; number_str[i] != '\0'; i++) {
            if (!isdigit(number_str[i]) && number_str[i] != '.') {
                fprintf(stderr, "Error: Invalid input. The number must be numeric.\n");
                return 1;
            }
        }
        double number = atof(number_str);
        double result = sqrt(number);
        printf("Square root of %.2lf is: %.2lf\n", number, result); 
        
    } else {
        
        fprintf(stderr, "Invalid argument: %s\n", argv[1]);
        return 1;
        
    }
    return 0;
}

double evaluate_expression(const char *expression) {
    double operands[50];
    char operators[50];
    int operand_top = -1;
    int operator_top = -1;
    int i = 0;
    while (expression[i] != '\0') {
        if (expression[i] == ' ') {
            i++;
            continue;
        }
        if (is_numeric(expression[i])) {
            double num = 0;
            while (is_numeric(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            if (expression[i] == '.') {
                i++;
                double decimalPlace = 10.0;
                while (is_numeric(expression[i])) {
                    num = num + (expression[i] - '0') / decimalPlace;
                    decimalPlace *= 10;
                    i++;
                }
            }
            operand_top++;
            operands[operand_top] = num;
        } else if (expression[i] == '%') {
            if (operand_top < 0) {
                fprintf(stderr, "Error: Invalid expression. '%%' cannot be the first character.\n");
                exit(EXIT_FAILURE);
            }
            operands[operand_top] *= 0.01; 
            i++;
        } else if (is_operator(expression[i])) {
            while (operator_top >= 0 && precedence(operators[operator_top]) >= precedence(expression[i])) {
                double b = operands[operand_top--];
                double a = operands[operand_top--];
                char op = operators[operator_top--];
                operands[++operand_top] = apply_operator(a, b, op);
            }
            operators[++operator_top] = expression[i];
            i++;
        } else if (expression[i] == '(') {
            operators[++operator_top] = expression[i];
            i++;
        } else if (expression[i] == ')') {
            while (operator_top >= 0 && operators[operator_top] != '(') {
                double b = operands[operand_top--];
                double a = operands[operand_top--];
                char op = operators[operator_top--];
                operands[++operand_top] = apply_operator(a, b, op);
            }
            operator_top--;
            i++;
        } else {
            printf("Invalid character found: %c\n", expression[i]);
            exit(EXIT_FAILURE);
        }
        if (i >= strlen(expression)) {
            break;
        }
    }
    while (operator_top >= 0) {
        double b = operands[operand_top--];
        double a = operands[operand_top--];
        char op = operators[operator_top--];
        operands[++operand_top] = apply_operator(a, b, op);
    }
    return operands[0];
}
double apply_operator(double a, double b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            printf("Invalid operator: %c\n", op);
            exit(EXIT_FAILURE);
    }
}
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}
int is_numeric(char c) {
    return isdigit(c) || c == '.';
}