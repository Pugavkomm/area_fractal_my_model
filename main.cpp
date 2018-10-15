//version beta 0.1
//author Pugavkomm
//numeric area fractl my system.
//https://github.com/Pugavkomm/area_fractal_my_model_c-.git

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <math.h>
#include </home/mech/area_fractal_my_model_c-/system_model.h>
#include </home/mech/area_fractal_my_model_c-/area_system.h>
#include <string>
using namespace std;
const double Pi = atan(1.0)*4;
const int quant_step = 200; // quant_step diff. initial
const int quant_step_d = 100;
const double step_d = .0001;
const int N = 10;
const int it = 100000;
const int start = 10000;
double alpha = 0.4;
void Initial(double **matr)
{
  int i;
  for (i = 0; i < 4; i++)
  {
    for (int j = 0; j < N; j++)
    {
      matr[j][i] = 0.0;
    }
  }
  for (i = 0; i < N; i++)
  {
    matr[i][0] = (double)(rand()%1400000 + 1)/1000000.0;
  }
  //matr[4][0] = .023;
}


void Compar(double *max_mass, double *max_mass_back, double *min_mass, double *min_mass_back)
{
  for (int i = 0; i < N; i++)
  {
    if (max_mass[i] > max_mass_back[i])
      max_mass_back[i] = max_mass[i];
    else if (min_mass[i] < min_mass_back[i])
      min_mass_back[i] = min_mass[i];
  }
}


int main(int argc, char const *argv[]) {
  srand(time(0));
  ofstream stels; // создаем метод для работы с файлами
  stels.open("save.txt"); // открыли или создали файл (отчистили старый)
  stels.close();


  double **matrix = new double *[N];
  for (int count = 0; count < N; count++) {
      matrix[count] = new double[it];
  }
  double max_mass[N], min_mass[N], max_mass_back[N] = {0.0}, min_mass_back[N] = {0.0};
  double area;
  double d;
  double d1 = (1.0 - alpha)/(1 + cos(Pi/(N + 1)));
  for (int j = 0; j < quant_step_d; j++)
  {
    d = d1 + step_d * (j - 1);
    for (int i = 0; i < quant_step; i++)
    {
      Initial(matrix);
      System_numeric(alpha, d, matrix, N, it); //замоделировали саму систему
      Max_min(matrix, max_mass, min_mass, N, it, start);
      Compar(max_mass, max_mass_back, min_mass, min_mass_back);
    }
    area = Area_result(max_mass_back, min_mass_back, N, it, start);
    ofstream itog; // создаем метод для работы с файлами
    itog.open("save.txt", ios::app); // открыли или создали файл,
  // с параметром дозаписи, чтобы дополнять строки.
    itog << d << " " << area << "\n";
    itog.close();
    cout << "d = " << to_string(d) << ", area = " << to_string(area) << endl;

  }

  return 0;
}
