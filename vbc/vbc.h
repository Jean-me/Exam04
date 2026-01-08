#ifndef VBC_H
#define VBC_H

extern const char *g_input;
extern int g_pos;

void error(char c);
int expression(void);
int term(void);
int factor(void);

#endif
