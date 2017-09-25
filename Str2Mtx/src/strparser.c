#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "strparser.h"

static unsigned int COLUMN_VALUE_STR_SIZE 	= 16;
static unsigned int VECTOR_LENGTH 			= 32;
static unsigned int ROWS_LENGTH 			= 32;

static char COLUMNS_SEPARATOR 				= ' ';
static char ROWS_SEPARATOR					= ';';

double* parse_vector(const char* input, size_t* size)
{
	unsigned int input_index 		= 0;
	unsigned int str_value_index 	= 0;
	unsigned int values_index 		= 0;
	size_t input_length;
	char str_value[COLUMN_VALUE_STR_SIZE];
	double _values[VECTOR_LENGTH];
	input_length = strlen(input);

	for( ; input_index < input_length; input_index++)
	{
		char current_char = *(input+input_index);
		if(isdigit(current_char) || current_char == '.')
		{
			*(str_value+str_value_index++)=current_char;
		}
		else if(current_char==COLUMNS_SEPARATOR)
		{
			double value = atof(str_value);
			*(_values+values_index++)=value;
			int i;
			for(i=0; i<str_value_index; i++)
				*(str_value+i)='\0';
			str_value_index=0;
		}
	}
	double value = atof(str_value);
	*(_values+values_index++)=value;
	double* vector = calloc(values_index, sizeof(double));
	int j;
	for(j=0; j<values_index; j++)
		*(vector+j) = *(_values+j);
	*size = values_index;
	return vector;
}

double** parse_matrix(const char* input, size_t* cols, size_t* rows) {
	size_t _rows = 0;
	size_t _cols = 0;

	unsigned int input_index = 0;
	unsigned int str_column_index = 0;

	size_t input_length = strlen(input);
	char str_column[VECTOR_LENGTH];
	double* temp_matrix[ROWS_LENGTH];

	for( ; input_index < input_length; input_index++) {
        char current_char = *(input+input_index);
        if(current_char == ROWS_SEPARATOR) {
			str_column[str_column_index] = '\0';
			if(str_column[str_column_index-1] == COLUMNS_SEPARATOR) str_column[str_column_index-1] = '\0';
			size_t row_size;
			double* row = parse_vector(str_column, &row_size);
			if(_rows == 0) _cols = row_size;
			if(_cols != row_size) return NULL;
			temp_matrix[_rows++] = row;
			for(int i=0; i<str_column_index; i++) *(str_column+i)='\0';
			str_column_index = 0;
        }
        else
			str_column[str_column_index++] = current_char;
	}
	*cols = _cols;
	*rows = _rows;

	double** matrix = calloc(_rows, sizeof(double*));
	if(matrix == NULL) return NULL;

	for(int i = 0; i < _rows; i++) *(matrix+i) = temp_matrix[i];

	return matrix;
}
