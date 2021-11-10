#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int	ft_nbrlen(unsigned int nbr){
	unsigned int	i;
	for (i = 0; nbr >= 10; nbr /= 10) i++;
	return (i + 1);
}

int			good_char(char c) {
	if (c != '+' && c != '-' && c != '<' && c != '>'
           && c != '.' && c != ',' && c != '[' && c != ']')
		   return (0);
	return (1);
}
const char* brainfuck_to_c (const char* src) {
	char *clean_str = malloc(sizeof(char) * 1400000);
	int i = 0, k = 0, len = 0, sign, brace = 0;
	clean_str[0] = '\0';
	while (src[k] && brace > -1) {
		while (!good_char(src[k]) && src[k]) k++;
		for (sign = 0; (src[k] == '+' || src[k] == '-' || !good_char(src[k])) && src[k]; k++) {
			if (src[k] == '+') sign++;
			else if (src[k] == '-') sign--;
		}
		if (sign != 0) {
			i = len;
			len += strlen("*p += ;\n") + ft_nbrlen(abs(sign)) + brace * 2;
			for (int spaces = 0; spaces < brace; spaces++) {
				clean_str[i++] = ' '; clean_str[i++] = ' ';
			}
			clean_str[i] = '\0';
			if (sign > 0)	sprintf(clean_str, "%s*p += %d;\n", clean_str, abs(sign));
			else 			sprintf(clean_str, "%s*p -= %d;\n", clean_str, abs(sign));
		}
		for (sign = 0; (src[k] == '<' || src[k] == '>' || !good_char(src[k])) && src[k]; k++) {
			if (src[k] == '>') sign++;
			else if (src[k] == '<') sign--;
		}
		if (sign != 0) {
			i = len;
			len += strlen("p += ;\n") + ft_nbrlen(abs(sign)) + brace * 2;
			for (int spaces = 0; spaces < brace; spaces++) {
				clean_str[i++] = ' '; clean_str[i++] = ' ';
			}
			clean_str[i] = '\0';
			if (sign > 0)	sprintf(clean_str, "%sp += %d;\n", clean_str, abs(sign));
			else 			sprintf(clean_str, "%sp -= %d;\n", clean_str, abs(sign));
		}
		else if (src[k] == '.') {
			i = len;
			len += strlen("putchar(*p);\n") + brace * 2;
			for (int spaces = 0; spaces < brace; spaces++) {
				clean_str[i++] = ' '; clean_str[i++] = ' ';
			}
			clean_str[i] = '\0';
			sprintf(clean_str, "%sputchar(*p);\n", clean_str);
			k++;
		}
		else if (src[k] == ',') {
			i = len;
			len += strlen("*p = getchar();\n") + brace * 2;
			for (int spaces = 0; spaces < brace; spaces++) {
				clean_str[i++] = ' '; clean_str[i++] = ' ';
			}
			clean_str[i] = '\0';
			sprintf(clean_str, "%s*p = getchar();\n", clean_str);
			k++;
		}
		else if (src[k] == '[') {
			while (!good_char(src[k]) && src[k]) k++;
      		if (src[k + 1] == ']') k += 2;
			else {
				i = len;
				len += strlen("if (*p) do {\n") + brace * 2;
				for (int spaces = 0; spaces < brace; spaces++) {
					clean_str[i++] = ' '; clean_str[i++] = ' ';
				}
				clean_str[i] = '\0';
				sprintf(clean_str, "%sif (*p) do {\n", clean_str);
				brace++;
				k++;
			}
		}
		else if (src[k] == ']') {
			brace--;
			i = len;
			len += strlen("} while (*p);\n") + brace * 2;
			for (int spaces = 0; spaces < brace; spaces++) {
				clean_str[i++] = ' '; clean_str[i++] = ' ';
			}
			clean_str[i] = '\0';
			sprintf(clean_str, "%s} while (*p);\n", clean_str);
			k++;
		}
	}
  	if (brace != 0) {
		free(clean_str);
		clean_str = malloc(sizeof(char) * 7);
		sprintf(clean_str, "Error!");
	}
	printf("%s", clean_str);
	return (clean_str);
}

int main()
{
	const char *r = brainfuck_to_c("+++++[>++++.<-]");
}