#include <stdio.h>
#include <stdlib.h>

#define ERR_MALLOC "Error: malloc failed.\n"

typedef struct {
    char value;
	char* str;
} tab;

int my_strlen(char* str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return i;
}

char my_int_to_char(int i, int size)
{
	char c;

	while (i > 10)
		i = i % 10;
	c = i + 48;

	printf("char = %c\n", c);
	return c;
}

char* my_int_to_str(int i)
{
	int j = i;
	int k = 0;
	int size = 0;
	char* str = NULL;
	char* str2 = NULL;

	while (j > 10)
	{
		j = j / 10;
		size++;
	}
	size++;

	if ((str = (char*)malloc(sizeof(char) * size + 1)) == NULL)
	{
		fprintf(stderr, ERR_MALLOC);
		exit(EXIT_FAILURE);
	}
	else
	{
		while (k < size)
		{
			str[k] = 48 + (i % 10);
			k++;
			i = i / 10;
		}
		str[k] = '\0';
	}
	if ((str2 = (char*)malloc(sizeof(char) * size + 1)) == NULL)
	{
		fprintf(stderr, ERR_MALLOC);
		exit(EXIT_FAILURE);
	}
	else
	{
		k = 0;
		int l = 1;
		while (k < size)
		{
			str2[k] = str[size - l];
			k++;
			l++;
		}
		str2[k] = '\0';
	}

	free(str);
	return str2;
}

int my_getval(char c)
{
	if (c > 48 && c < 58)
		return c - 48;
	else if (c > 64 && c < 91)
		return c - 64;
	else if (c > 96 && c < 123)
		return c - 96;
	else
		return 0;
}

char* step1(char* str)
{
	int i = 0;
	int ret_int = 0;

	while (str[i] != '\0')
	{
		ret_int = ret_int + my_getval(str[i]);
		i++;
	}

	return my_int_to_str(ret_int);
}

char*	SumCharsAndDigits(const char* str)
{
	char* str2 = step1((char*)str);

	while (my_strlen(str2) > 1)
		str2 = step1(str2);
	return str2;
}

int	count_word(char* str)
{
	int i = 0;
	int nb = 0;

	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] != ' ' && str[i] != '\0')
			nb++;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
	}
	return nb;
}

int fill_field(tab* tableau, char* str, int i)
{
	int size = 0;
	int j = 0;

	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		j = i;
		while (str[i] != ' ' && str[i] != '\0')
		{
			size++;
			i++;
		}
		if ((tableau->str = (char*)malloc(sizeof(char) * size + 1)) == NULL)
		{
			fprintf(stderr, ERR_MALLOC);
			exit(EXIT_FAILURE);
		}
		i = j;
		j = 0;
		while (str[i] != ' ' && str[i] != '\0')
		{
			tableau->str[j++] = str[i];
			i++;
		}
		tableau->str[j] = '\0';
		tableau->value = SumCharsAndDigits(tableau->str)[0];
		return i;
	}
	return i;
}

void fill_tab(tab* tableau, char* str, int nb)
{
	int i = 0;
	int j = 0;

	while (i < nb)
	{
		j = fill_field(&tableau[i], str, j);
		i++;
	}

}

void	print_sorted_tab(tab* tableau, int tab_size)
{
	int i = 0;
	char min_val = '0';
	int printed = 0;

	while (printed < tab_size)
	{
		while (i < tab_size)
		{
			if (tableau[i].value == min_val)
			{
				printf("%c: %s\n", tableau[i].value, tableau[i].str);
				printed++;
			}
			i++;
		}
		min_val++;
		i = 0;
	}
}

void my_free_tab(tab* tableau, int size)
{
	int i = 0;

	while (i < size)
	{
		free(tableau[i].str);
		i++;
	}
	free(tableau);
}

void	PrintWordsSorted(const char* str)
{
	int nb_word = count_word((char*)str);

	tab* tableau = NULL;

	if ((tableau = (tab*)malloc(sizeof(tab) * nb_word)) == NULL)
	{
		fprintf(stderr, ERR_MALLOC);
		exit(EXIT_FAILURE);
	}
	fill_tab(tableau, (char*)str, nb_word);
	print_sorted_tab(tableau, nb_word);
	my_free_tab(tableau, nb_word);
}

int    main(int ac, char** av)
{
	printf("%s\n", SumCharsAndDigits("123"));
	printf("%s\n", SumCharsAndDigits("1d3"));
	printf("%s\n", SumCharsAndDigits("1D3"));
	printf("%s\n", SumCharsAndDigits("5#83"));

	PrintWordsSorted("   Mon code est    cool !    ");
	return 0;
}
