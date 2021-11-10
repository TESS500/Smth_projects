#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const char* brainfuck_to_c (const char* src) {
	char *clean_str = malloc(sizeof(char)*1), *tmp_s, *tmp_str;
	int i = 0, len = 0, sign, brace = 0;
	clean_str[0] = '\0';
	while (*src) {
		while (*src != '+' && *src != '-' && *src == '<' && *src == '>'
			&& *src != '.' && *src != ',' && *src == '[' && *src == ']' && src) *src++;
		for (sign = 0; *src == '+' || *src == '-'; *src++) {
			if (*src == '+') sign++;
			else sign--;
		}
		if (sign != 0) {
			tmp_s = malloc(sizeof(char) * 10);
			itoa(abs(sign), tmp_s, 10);
			i = len;
			len += strlen("*p += ;\n") + strlen(tmp_s) + brace * 2;
			tmp_str = malloc(sizeof(char) * (len + 1));
			sprintf(tmp_str, "%s", clean_str);
			for (int spaces = 0; spaces < brace; spaces++) {
				tmp_str[i++] = ' '; tmp_str[i++] = ' ';
			}
			tmp_str[i] = '\0';
			if (sign > 0)	sprintf(tmp_str, "%s*p += %s;\n", tmp_str, tmp_s);
			else 			sprintf(tmp_str, "%s*p -= %s;\n", tmp_str, tmp_s);
			free(clean_str);
			free(tmp_s);
			clean_str = tmp_str;
		}
		for (sign = 0; *src == '<' || *src == '>'; *src++) {
			if (*src == '>') sign++;
			else sign--;
		}
		if (sign != 0) {
			tmp_s = malloc(sizeof(char) * 10);
			itoa(abs(sign), tmp_s, 10);
			i = len;
			len += strlen("p += ;\n") + strlen(tmp_s) + brace * 2;
			tmp_str = malloc(sizeof(char) * (len + 1));
			sprintf(tmp_str, "%s", clean_str);
			for (int spaces = 0; spaces < brace; spaces++) {
				tmp_str[i++] = ' '; tmp_str[i++] = ' ';
			}
			tmp_str[i] = '\0';
			if (sign > 0)	sprintf(tmp_str, "%sp += %s;\n", tmp_str, tmp_s);
			else 			sprintf(tmp_str, "%sp -= %s;\n", tmp_str, tmp_s);
			free(clean_str);
			free(tmp_s);
			clean_str = tmp_str;
		}
		else if (*src == '.') {
			i = len;
			len += strlen("putchar(*p);\n") + brace * 2;
			tmp_str = malloc(sizeof(char) * (len + 1));
			sprintf(tmp_str, "%s", clean_str);
			for (int spaces = 0; spaces < brace; spaces++) {
				tmp_str[i++] = ' '; tmp_str[i++] = ' ';
			}
			tmp_str[i] = '\0';
			sprintf(tmp_str, "%sputchar(*p);\n", tmp_str);
			free(clean_str);
			clean_str = tmp_str;
			*src++;
		}
		else if (*src == ',') {
			i = len;
			len += strlen("*p = getchar();\n") + brace * 2;
			tmp_str = malloc(sizeof(char) * (len + 1));
			sprintf(tmp_str, "%s", clean_str);
			for (int spaces = 0; spaces < brace; spaces++) {
				tmp_str[i++] = ' '; tmp_str[i++] = ' ';
			}
			tmp_str[i] = '\0';
			sprintf(tmp_str, "%s*p = getchar();\n", tmp_str);
			free(clean_str);
			clean_str = tmp_str;
			*src++;
		}
		else if (*src == '[') {
			i = len;
			len += strlen("if (*p) do {\n") + brace * 2;
			tmp_str = malloc(sizeof(char) * (len + 1));
			sprintf(tmp_str, "%s", clean_str);
			for (int spaces = 0; spaces < brace; spaces++) {
				tmp_str[i++] = ' '; tmp_str[i++] = ' ';
			}
			tmp_str[i] = '\0';
			sprintf(tmp_str, "%sif (*p) do {\n", tmp_str);
			free(clean_str);
			clean_str = tmp_str;
			brace++;
			*src++;
		}
		else if (*src == ']') {
			if (brace == 0) {
				free(clean_str);
				clean_str = malloc(sizeof(char) * 7);
				sprintf(clean_str, "Error!");
				return (clean_str); }
			brace--;
			i = len;
			len += strlen("} while (*p);\n") + brace * 2;
			tmp_str = malloc(sizeof(char) * (len + 1));
			sprintf(tmp_str, "%s", clean_str);
			for (int spaces = 0; spaces < brace; spaces++) {
				tmp_str[i++] = ' '; tmp_str[i++] = ' ';
			}
			tmp_str[i] = '\0';
			sprintf(tmp_str, "%s} while (*p);\n", tmp_str);
			free(clean_str);
			clean_str = tmp_str;
			*src++;
		}
	}
	// printf("%s", clean_str);
	return (clean_str);
}

int main()
{
	const char *r = brainfuck_to_c("[]][");
}