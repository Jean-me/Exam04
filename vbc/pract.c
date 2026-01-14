#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    enum
    {
        ADD,
        MULTI,
        VAL
    } type;
    int val;
    struct node *l;
    struct node *r;
} node;

node *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void destroy_tree(node *n)
{
    if (!n)
        return;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n"); //+++++++++++++++
}

int accept(char **s, char c)
{
    if (**s == c) //+++++++++++++++
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int check_balance(char *s);
node *parse_number_or_group(char **s);
node *parse_addition(char **s);
node *parse_multiplication(char **s);

node *parse_number_or_group(char **s)
{
    node *res;
    node tmp;

    res = NULL;
    if (**s == '(')
    {
        (*s)++;
        res = parse_addition(s);
        if (!res || **s != ')')
        {
            destroy_tree(res);
            unexpected(**s);
            return (NULL);
        }
        ()
    }
}