//хедер, который вычисляет площадь. В нем хранятся функции:
//1) Max_min - вычисляет максимум и минимум, но "возвращает" одномерные массивы
//длинной N. Дело в том, что нам необходимы максимумы и минимы по каждой перем.
//2) Area_result многомерный объем поглощающей области


void Max_min(double **matrix_system, double *max_mass, double *min_mass,
int N, int it, int start)
{
  int i, j;
  double max, min;
  double var_matr = 0.0;
  for (j = 0; j < N; j++)
  {
    max = -100.0; min = 100.0;
    for (i = start; i < it; i++)
    {
      var_matr = matrix_system[j][i];
      if (var_matr > max)
        max = var_matr;
      else if (var_matr < min)
        min = var_matr;
    }
    max_mass[j] = max;
    min_mass[j] = min;
  }
}

double Area_result(double *max_mass,
  double *min_mass, int N, int it, int start)
{

  double z = 0.0;
  for (int i = 0; i < N;  i++)
  {
    if (i == 0)
      z = max_mass[i] - min_mass[i];
    else
      z *= max_mass[i] - min_mass[i];
  }
  return z;
}
