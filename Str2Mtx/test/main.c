#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "strparser.h"

#define DOUBLE_VAL "%.2lf\t"

/*
 * Tests methods.
 */
void should_parse_vector(void);
void should_parse_matrix(void);

/*
 * Helper methods.
 */
void print_vector(double* vector, size_t s);
void print_matrix(double** matrix, size_t cols, size_t rows);

int main()
{
	puts("\n\nParsed vector:");
	should_parse_vector();
	puts("\n\nParsed matrix:");
	should_parse_matrix();

    return 0;
}

void print_vector(double* vector, size_t s) {
	int c;
	for(c ; c < s; c++) {
        printf(DOUBLE_VAL, *(vector+c));
    }
}

void print_matrix(double** matrix, size_t c, size_t r) {
    for(int i = 0; i < r; i++) {
		double* r = *(matrix+i);
		for(int j = 0; j < c; j++) {
			printf(DOUBLE_VAL, *(r+j));
		}
		free(r);
		puts("");
    }
}

void should_parse_vector(void) {

	size_t s;
	double* vector = parse_vector("23 79 90 1 6 88.9 34.001 1.25 0.1", &s);

	size_t expected_s = 9;
	assert(s = expected_s);

	print_vector(vector, s);
	free(vector);
}

void should_parse_matrix(void) {

	size_t cols, rows;
    double** matrix = parse_matrix("1 2 3 4;5 6 7 8;9 10 11 12;13 14 15 16;", &cols, &rows);

	assert(matrix != NULL);
	assert(cols == 4);
	assert(rows == 4);

	print_matrix(matrix, cols, rows);
}
