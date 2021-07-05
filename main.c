#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct matrix
{
  size_t nrow;
  size_t ncol;
  double **values;
};

typedef struct matrix matrix;

matrix new_matrix (size_t rows, size_t cols, double array[rows][cols])
{
  matrix m;
  m.nrow = rows;
  m.ncol = cols;

  m.values = (double**) calloc (sizeof(double*), m.nrow);

  for (int i = 0; i<m.nrow; i++)
    for (int j=0; j<m.ncol; j++)
      m.values[i][j] = array[i][j];

  return m;
}

matrix empty_matrix (size_t rows, size_t cols)
{
  matrix m;
  m.nrow = rows;
  m.ncol = cols;

  m.values = (double**) calloc (sizeof(double*), m.nrow);
  
  for (int i = 0; i < m.nrow; i++)
    m.values[i] = (double*) calloc (sizeof(double), m.ncol);
  return m;
}

matrix random_unif_matrix (size_t rows, size_t cols)
{
  srand(time(NULL));
  matrix m;
  m.nrow = rows;
  m.ncol = cols;

  m.values = (double**) calloc (sizeof(double*), m.nrow);

  for (int i = 0; i<m.nrow; i++)
    for (int j=0; j<m.ncol; j++)
    {
      double losowa = (double) rand() / RAND_MAX;
      m.values[i][j] = losowa;
    }
  return m;
}

matrix add_to_matrix (matrix a, double b)
{
  for (int i = 0; i<a.nrow; i++)
    for (int j=0; j<a.ncol; j++)
    {
      a.values[i][j] += b;
    }
  return a;
}

matrix multiply_matrix (matrix a, double b)
{
  for (int i = 0; i<a.nrow; i++)
    for (int j=0; j<a.ncol; j++)
    {
      a.values[i][j] *= b;
    }
  return a;
}

matrix print_matrix (matrix a, FILE *stream, char sep)
{
  for (int i; i<a.nrow; i++)
  {
    for (int j=0; j<a.ncol; j++)
      fprintf (stream, "%lf%c", a.values[i][j], sep);
    fprintf(stream, "\n");
  }
}


void delete_matrix (matrix *m)
{
  for (int i = 0; i < m->nrow; i++)
  free (m->values[i]);
  free (m->values);
}


int main(void)
{
  matrix a, b;
  
  //funkcje new_matrix i print matrix
  double t[3][2] = {{4.2, 5.93}, {3, 1.1}, {0, 6.004}};
  a = new_matrix(3, 2, t);
  print_matrix(a, stdout, '\t');

  fprintf(stdout, "\n");

  //funkcje empty_matrix i print_matrix)
  b = empty_matrix(4, 6);
  print_matrix(b, stdout, ',');

  fprintf(stdout, "\n");

  delete_matrix(&a);
  delete_matrix(&b);

  //pd 9.2
  matrix c, d;

  c = random_unif_matrix(5, 5);
  print_matrix(c, stdout, '\t');
  fprintf(stdout, "\n");
  c= multiply_matrix(c, 2);
  c= add_to_matrix(c, -1);
  print_matrix(c, stdout, '\t');
  fprintf(stdout, "\n");

  double p[3][3] = {{-9, -8, -7}, {-6, -5, -4}, {-3, -2, -1}};
  d = new_matrix(3, 3, p);
  print_matrix(d, stdout, '\t');
  fprintf(stdout, "\n");
  d = add_to_matrix(d, 10);
  d = multiply_matrix(d, 11);
  print_matrix(d, stdout, '\t');
  fprintf(stdout, "\n");

  delete_matrix(&c);
  delete_matrix(&d);

  return 0;
}