#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int	ft_nbrlen(unsigned int nbr){
	unsigned int	i;
	for (i = 0; nbr >= 10; nbr /= 10) i++;
	return (i + 1);
}

char	*ft_itoa(int n) {
	char	*str;
	int	len, i;

	len = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * len + 1);
  i = len - 1;
	while (n >= 10) { str[i--] = n % 10 + 48; n /= 10; }
	str[i] = n % 10 + 48;
	str[len] = '\0';
	return (str);
}

int			good_char(char c) {
	if (c != '+' && c != '-' && c != '<' && c != '>'
           && c != '.' && c != ',' && c != '[' && c != ']')
		   return (0);
	return (1);
}
const char* brainfuck_to_c (const char* src) {
	char *clean_str = malloc(sizeof(char)*1), *tmp_s, *tmp_str;
	int i = 0, k = 0, len = 0, sign, brace = 0;
	clean_str[0] = '\0';
	while (src[k]) {
		while (!good_char(src[k]) && src[k]) k++;
		for (sign = 0; (src[k] == '+' || src[k] == '-' || !good_char(src[k])) && src[k]; k++) {
			if (src[k] == '+') sign++;
			else if (src[k] == '-') sign--;
		}
		if (sign != 0) {
      		tmp_s = ft_itoa(abs(sign));
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
		for (sign = 0; (src[k] == '<' || src[k] == '>' || !good_char(src[k])) && src[k]; k++) {
			if (src[k] == '>') sign++;
			else if (src[k] == '<') sign--;
		}
		if (sign != 0) {
			tmp_s = ft_itoa(abs(sign));
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
		else if (src[k] == '.') {
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
			k++;
		}
		else if (src[k] == ',') {
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
			k++;
		}
		else if (src[k] == '[') {
			while (!good_char(src[k]) && src[k]) k++;
      		if (src[k + 1] == ']') k += 2;
			else {
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
				k++;
			}
		}
		else if (src[k] == ']') {
			if (brace == 0) {
				free(clean_str);
				clean_str = malloc(sizeof(char) * 7);
				sprintf(clean_str, "Error!");
				return (clean_str);
      		}
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
	const char *r = brainfuck_to_c("++ ++");
}