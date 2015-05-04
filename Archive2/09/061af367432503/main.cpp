#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void print(char ** ast, size_t nstr){
    size_t i = 0;
	for (; i < nstr; i++){
		printf("%s\n", ast[i]);
	}
}
void sol_1(int n) {
	size_t i = 0, j = 0, size = n;
	char **ast = NULL;
	ast = malloc(sizeof(*ast)* size);
	if (ast == NULL){ //wasn't required in the quiz
		exit(EXIT_FAILURE);
	}
	for (; i < size; i++){
		ast[i] = malloc((i + 2)* sizeof(**ast));
		if (ast[i] == NULL){ //wasn't required in the quiz
			exit(EXIT_FAILURE);
		}
		for (j = 0; j < i+1; j++){
			ast[i][j] = '*';
		}
		ast[i][j] = '\0';
	}
	print(ast, size); //wasn't required in the quiz

	for (i = 0; i < size; i++){
		free(ast[i]);
	}
	free(ast);
}

void sol_2(int n) {
	size_t i = 0, j = 0, size = n;
	char **ast = NULL;
	ast = malloc(sizeof(char*)* size);
	if (ast == NULL){ //wasn't required in the quiz
		exit(EXIT_FAILURE);
	}
	for (; i < size; i++){
		ast[i] = malloc((i + 2)* sizeof(char));
		if (ast[i] == NULL){ //wasn't required in the quiz
			exit(EXIT_FAILURE);
		}
		ast[i][0] = '\0';
		for (j = 0; j < i + 1; j++){
			strcat(ast[i], "*");
		}
	}
	print(ast, size); //wasn't required in the quiz

	for (i = 0; i < size; i++){
		free(ast[i]);
	}
	free(ast);
}

void sol_3(int n) {
	size_t i = 0, j = 0, size = n;
	char **ast = NULL;
	ast = malloc(sizeof(char*)* size);
	if (ast == NULL){ //wasn't required in the quiz
		exit(EXIT_FAILURE);
	}
	for (; i < size; i++){
		ast[i] = calloc((i + 2), sizeof(char));
		if (ast[i] == NULL){ //wasn't required in the quiz
			exit(EXIT_FAILURE);
		}
		for (j = 0; j < i + 1; j++){
			strcat(ast[i], "*");
		}
	}
	print(ast, size); //wasn't required in the quiz

	for (i = 0; i < size; i++){
		free(ast[i]);
	}
	free(ast);
}

int main(void) {
    sol_1(1);
    printf("--------\n");
    sol_2(2);
    printf("--------\n");
	sol_3(6);
	return 0;
}