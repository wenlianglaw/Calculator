#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
expr is the expression
s is the start character's address, *s is the start character
E -> T +- T | T
T -> F * / F | F
F -> (E) | num

LWL
wenlianglaw@gmail.com
NYC
2015-09-09
*/
double E(char *expr,char** s) {
	double T(char *expr, char** s);
	double ret = 0.0F;
	if (!**s) return ret;
	ret = T(expr, s);
	while (**s) {
		char op = *(*s)++;
		if (op == '+') ret += T(expr, s);
		else if (op == '-') ret -= T(expr, s);
		else if (op == ')') break;
		else (*s)--;
	}
	return ret;
}

double T(char *expr, char** s) {
	double F(char *expr, char** s);
	double ret;
	if (!**s) ret;
	ret = F(expr, s);
	while ( **s == '*' || **s == '/' ) {
		char op = *(*s)++;		
		if (op == '*') ret *= F(expr, s);
		else if (op == '/') ret /= F(expr, s);
		else (*s)--;
	}
	return ret;
}

double F(char *expr, char** s) {
	if (!**s) return 1.0F;
	char ch = **s;
	double ret = 1.0F;
	if (**s == '(') {
		(*s)++;
		ret = E(expr, s);
	} 
	else if (**s == ')');// do nothing
	else if (**s >= '0' && **s <= '9' || **s =='+' || **s == '-') {
		ret = strtod(*s, s);
	}
	return ret;
}

#if 0
double E(char *expr, char** s) {
	double T(char *expr, char** s);
	double ret = 0.0F;
	if (!**s) return ret;
	ret = T(expr, s);
	while (*s) {
		if (**s == '+' || **s == '-') {
			(*s)++;
			ret += *(*s - 1) == '+' ? T(expr, s) : -T(expr, s);
		}
		else if (**s == '(')
			ret = E(expr, s);
		else break;
	}
	return ret;
}

double T(char *expr, char** s) {
	double F(char *expr, char** s);
	double ret;
	ret = F(expr, s);
	if (**s == '*' || **s == '/') {
		(*s)++;
		ret *= *(*s - 1) == '*' ? F(expr, s) : 1 / F(expr, s);
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
	//char *str = "3*(4+5)*6";	
	char *str = "1+2*(4+3)";
	char *pstr = str;
	double d = E(str,&pstr);
	printf("%lf\n", d);

	getchar();
	return 0;
}
