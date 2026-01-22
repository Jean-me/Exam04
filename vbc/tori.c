
#include <stdio.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;


node    *mul(char **s);
node    *num(char **s);
node    *add(char **s);

node    *nt(int type, int val, node *l, node *r)
{
    node *ret = calloc(1, sizeof(node));
    if (!ret)
        return (NULL);
    ret->type = type;
    ret->val = val;
    ret->l = l;
    ret->r = r;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int accept(char **s, char c)
{
    if (**s == c)
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

node    *add(char **s)
{

    node *l;
    l = mul(s);
    if (!l) 
        return (NULL);
    while(accept(s, '+'))
    {
        node *r = mul(s);
        if (!r)
            return (destroy_tree(l), NULL); 
        l = nt(ADD, 0, l, r);
    }
    return (l);
}

node    *mul(char **s)
{
    node *l;
    l = num(s);
    if (!l) 
        return (NULL);
    while(accept(s, '*'))
    {
        node *r = num(s);
        if (!r)
            return (destroy_tree(l), NULL);
        l = nt(MULTI, 0, l, r);
    }
    return (l);
}

node    *num(char **s)
{
    if (accept(s,'('))
    {
        node *l = add(s);
           if (!l) 
            return (NULL); 
        if (!expect(s, ')'))
            return (destroy_tree(l), NULL);
        return l;
    }
    if (!isdigit(**s))
        return (unexpected(**s), NULL);
    int val = (**s) - 48;
    (*s)++;
    return(nt(VAL, val, NULL, NULL));
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    char *input = argv[1];
    node *tree = add(&input);
    if (!tree)
        return (1);
    if (!expect(&input,0))
        return (destroy_tree(tree),1);    
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
}
