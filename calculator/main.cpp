#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_space(char *s) {
  char *p = s;
  while (*s) {
    if (*s == ' ') s++;
    else *p++ = *s++;
  }
  *p = '\0';
}

/*
expr is the expression
s is the start character's address, *s is the start character
E -> T +- T | T
T -> F * / F | F
F -> (E) | num
-----------------------
or
E -> T +- E | T
T -> F * / T | F
F -> (E) | num
LWL
wenlianglaw@gmail.com
NYC
2015-09-09

2023 updated removed some unnecessary code, such as handling "(" in E and F.
*/

#define recursive
#ifndef recursive
double E(char *expr, char **s) {
  double T(char *expr, char **s);
  double ret = 0.0F;
  if (!**s) return ret;
  ret = T(expr, s);
  while (**s == '+' || **s == '-') {
    (*s)++;
    ret += *(*s - 1) == '+' ? T(expr, s) : -T(expr, s);
  }
  return ret;
}

double T(char *expr, char **s) {
  double F(char *expr, char **s);
  double ret;
  ret = F(expr, s);
  while (**s == '*' || **s == '/') {
    (*s)++;
    ret *= *(*s - 1) == '*' ? F(expr, s) : 1 / F(expr, s);
  }
  return ret;
}

double F(char *expr, char **s) {
  if (!**s) return 1.0F;
  double ret = 1.0F;
  if (**s == '(') {
    (*s)++;
    ret = E(expr, s);
  }
  if (**s == ')')
    (*s)++;  // do nothing
  else if (**s >= '0' && **s <= '9' || **s == '+' || **s == '-') {
    ret = strtod(*s, s);
  }
  return ret;
}

#else  // ifdef recursive
double E(char *expr, char** s) {
	double T(char *expr, char** s);
	double ret = 0.0F;
	if (!**s) return ret;
	ret = T(expr, s);
	while (**s) {
		if (**s == '+' || **s == '-') {
			(*s)++;
			ret += *(*s - 1) == '+' ? T(expr, s) : -T(expr, s);
		}
		else break;
	}
	return ret;
}

double T(char *expr, char** s) {
	double F(char *expr, char** s);
	double ret;
	ret = F(expr, s);
	while (**s) {
		if (**s == '*' || **s == '/') {
			(*s)++;
			ret *= *(*s - 1) == '*' ? F(expr, s) : 1 / F(expr, s);
		}
		else break;
	}
	return ret;
}

double F(char *expr, char** s) {
	if (!**s) return 1.0F;
	double ret = 1.0F;
	if (**s == '(') {
		(*s)++;
		ret = E(expr, s);
	}
	if (**s == ')') (*s)++;// do nothing
	else if (**s >= '0' && **s <= '9' || **s == '+' || **s == '-') {
		ret = strtod(*s, s);
	}
	return ret;
}
#endif

int main() {
  // char *str = "3*(4+5)*6";
  char str[] = "(3*2) + 1.5 + 1.5 + 4 * (3+2) - (3*2) - (2+((2))) / (2)";
  char *pstr = str;
  trim_space(str);
  double d = E(str, &pstr);
  printf("%lf\n", d);

  return 0;
}
