//данный хедер содержит в себе все функции для вычисления системы
//на вход подается количество элементов: N, итераций: it, параметры:alpha, d


double Nonlinear_piese(double alpha, double x)
{
  //функция предназначена для вычисления нелинейности
  double z;
  if (x < 0.5)
    z =  - 2 * x * alpha;
  else if (x > 0.5)
  z =  - 2 * x * alpha + 2 * alpha;
  return z;
}


double Next_iter(double alpha, double d, double back_elem, double now_elem,
double follow_elem)
{
  double z = now_elem + d * (back_elem + follow_elem - 2 * now_elem) +
  Nonlinear_piese(alpha, now_elem);
  return z;
}


void System_numeric(double alpha, double d, double **matrix_system, int N, int it)
{
  double back = 0.0, now = 0.0, follow = 0.0;
  int i, j;
  for (i = 0; i < it - 1; i++)
  {
    for (j = 0; j < N; j++)
    {
      if (j == 0) {
          back = 0.;
          now = matrix_system[j][i];
          follow = matrix_system[j + 1][i];
      } else if (j == N - 1) {
          back = matrix_system[j - 1][i];
          now = matrix_system[j][i];
          follow = 0.;
      } else {
          back = matrix_system[j - 1][i];
          now = matrix_system[j][i];
          follow = matrix_system[j + 1][i];
      }
      matrix_system[j][i + 1] = Next_iter(alpha, d, back, now, follow);
    }
  }
}
