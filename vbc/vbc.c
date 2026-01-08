#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "vbc.h"

const char *g_input;
int g_pos;

void error(char c)
{
    if (c == '\0')
        write(2, "Unexpected end of input\n", 24);
    else
    {
        write(2, "Unexpected token '", 18);
        write(2, &c, 1);
        write(2, "'\n", 2);
    }
    exit(1);
}

int expression(void);

int factor(void)
{
    int result;

    if (g_input[g_pos] >= '0' && g_input[g_pos] <= '9')
    {
        result = g_input[g_pos] - '0';
        g_pos++;
        return result;
    }
    else if (g_input[g_pos] == '(')
    {
        g_pos++; // skip '('
        result = expression();
        if (g_input[g_pos] != ')')
            error(g_input[g_pos]);
        g_pos++; // skip ')'
        return result;
    }
    else
        error(g_input[g_pos]);
    return 0;
}

int term(void)
{
    int result = factor();

    while (g_input[g_pos] == '*')
    {
        g_pos++; // skip '*'
        result = result * factor();
    }
    return result;
}

int expression(void)
{
    int result = term();

    while (g_input[g_pos] == '+')
    {
        g_pos++; // skip '+'
        result = result + term();
    }
    return result;
}

int main(int argc, char **argv)
{
    int result;

    if (argc != 2)
    {
        write(2, "Usage: ./vbc <expression>\n", 26);
        return 1;
    }

    g_input = argv[1];
    g_pos = 0;

    result = expression();

    if (g_input[g_pos] != '\0')
        error(g_input[g_pos]);

    printf("%d\n", result);
    return 0;
}
