#ifndef STRTOOLS_H_INCLUDED
#define STRTOOLS_H_INCLUDED

/*
 * Parse string of values to array of double precision float values.
 */
double* parse_vector(const char* input, size_t* size);

/*
 * Parse string of values to multi-dimensional array of double precision float values.
 */
double** parse_matrix(const char* input, size_t* cols, size_t* rows);

#endif // STRTOOLS_H_INCLUDED
