#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
expr is the expression
s is the start character's address, *s is the start character
*/
double E(char *expr,char** s) {
	double T(char *expr, char** s);
	double ret = 0.0F;
	if (!**s ) return ret;
	while ( char op = **s != 0 ) {
		ret = T(expr,s);
		if (op == '+') ret = ret + T(expr, s);
		else if (op == '-') ret = ret - T(expr, s);
		(*s)++;
	}
	return ret;
}

double T(char *expr, char** s) {
	double F(char *expr, char** s);
	double ret;
	if (!**s) ret;
	while (char op = **s == '*' || op == '/') {
		ret = F(expr, s);
		if (op == '*') ret = ret * F(expr, s);
		else if (op == '/') ret = ret / F(expr, s);
		(*s)++;
	}

	return ret;
}

double F(char *expr, char** s) {
	if (!**s) return 1.0F;
	char ch = **s;
	double ret;
	if (**s >= '0' && **s <= '9') {
		ret = strtod(*s, s);
	}
	else if (**s == '(') {
		(*s)++;
		ret = E(expr, s);
	} 
	else if (**s == ')');// do nothing
	return ret;
}


int main() {
	char *str = "3*(4+5)*6";
	double d = E(str,&str);
	printf("%lf\n", d);
	getchar();

	return 0;
}
