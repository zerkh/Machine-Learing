#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cmath>
#include "NN.h"
using namespace std;

NN::Neural_Net()
{
  //初始化矩阵

  W1 = new double*[3];
  for(int i = 0; i < 3; i++)
    {
      W1[i] = new double[3];
    }

  W2 = new double*[1];
  for(int i = 0; i < 1; i++)
    {
      W2[i] = new double[3];
    }

  b1 = new double*[3];
  for(int i = 0; i < 3; i++)
    {
      b1[i] = new double[1];
    }

  R1 = new double*[3];
  for(int i = 0; i < 3; i++)
    {
      R1[i] = new double[1];
    }

  a1 = new double*[3];
  for(int i = 0; i < 3; i++)
    {
      a1[i] = new double[1];
    }

  a2 = new double*[3];
  for(int i = 0; i < 3; i++)
    {
      a2[i] = new double[1];
    }

  Delta_W1 = new double*[3];
  for(int i = 0; i < 3; i++)
    {
      Delta_W1[i] = new double[3];
    }

  Delta_W2 = new double*[1];
  for(int i = 0; i < 1; i++)
    {
      Delta_W2[i] = new double[3];
    }

  Delta_b1 = new double*[3];
  for(int i = 0; i < 3; i++)
    {
      Delta_b1[i] = new double[1];
    }

  m = 1;
  //矩阵导数初始化为零
  for(int r = 0; r < 3; r++)
    for(int c = 0; c < 3; c++)
      {
	Delta_W1[r][c] = 0;
      }
  
  for(int r = 0; r < 3; r++)
      {
	Delta_W2[0][r] = 0;
	Delta_b1[r][0] = 0;
	Delta_b2 = 0;
	b1[r][0] = 0;
	b2 = 0;
      }
  //阀值初始化为极小的数
  for(int r = 0; r < 3; r++)
    for(int c = 0; c < 3; c++)
      {
	W1[r][c] = GaussRan();
      }
  
  for(int r = 0; r < 3; r++)
    {
      W2[0][r] = GaussRan();
      b1[r][0] = GaussRan();
      b2 = GaussRan();
    }
}

//产生高斯分布随机数
double NN::GaussRan()
{
  double u1 = (double)(rand() % 1000) / 1000;
  double u2 = (double)(rand() % 1000) / 1000;
  double r;

  r = 5 * sqrt(-2.0 * (log(u1) / log(E))) * cos(2 * PI * u2);

  return r/10; 
}

//激活各变量
void NN::Active()
{
  double **Z2 = new double*[3];
  for(int i = 0; i < 3; i++)
    {
      Z2[i] = new double[1];
    }
  double Z3;
  //求隐藏单元的值
  Matrix_Mul(W1, a1, Z2, 3, 3, 1);
  for(int r = 0; r < 3; r++)
    {
      Z2[r][0] += b1[r][0];
    }
  for(int r = 0; r < 3; r++)
    {
      a2[r][0] = Function(Z2[r][0]);
    }
  //求输出单元的值
  double **Tmp = new double*[0];
  Tmp[0] = new double[0];
  Matrix_Mul(W2, a2, Tmp, 1, 3, 1);
  a3 = Function(Tmp[0][0] + b2);

  //DeleteArr(Z2, 3);
  //DeleteArr(Tmp, 3);
}

NN::~Neural_Net()
{
  DeleteArr(W1, 3);
  DeleteArr(W2, 1);
  DeleteArr(b1, 3);
  DeleteArr(R1, 3);
  DeleteArr(a1, 3);
  DeleteArr(a2, 3);
  DeleteArr(Delta_W1, 3);
  DeleteArr(Delta_W2, 1);
  DeleteArr(Delta_b1, 3);
}

void NN::DeleteArr(double **Arr, int r)
{
  for(int i = 0; i < r; i++)
    {
      delete []Arr[i];
    }

  delete []Arr;
}

//反向传播
void NN::Backpro()
{
  //求残差

  R2 = -(y - a3) * (a3 * (1 - a3));
  
  for(int rc = 0; rc < 3; rc++)
    {
      R1[rc][0] = (W2[0][rc]*R2) * (a2[rc][0]*(1-a2[rc][0]));
    }
  
  //求阀值的导数
  for(int r = 0; r < 3; r++)
    for(int c = 0; c < 3; c++)
      {
	Delta_W1[r][c] += R1[r][0] * a1[c][0];
      }
  
  for(int r = 0; r < 3; r++)
    {
      Delta_W2[0][r] += a2[r][0] * R2;
      Delta_b1[r][0] += R1[r][0];
      Delta_b2 += R2;
    }
}

double NN::Function(double Z)
{
  double Result;
  
  Result = 1 / (1+exp(-Z));

  return Result;
}

//矩阵乘法
void NN::Matrix_Mul(double **Ori1, double **Ori2, double **Dest ,int row, int k, int col)
{
  for(int r = 0; r < row; r++)
    for(int c = 0; c < col; c++)
      {
	int Result = 0;

	for(int i = 0; i < k; i++)
	  {
	    Result += Ori1[r][i] * Ori2[i][c];
	  }

	Dest[r][c] = Result;
      }
}

//预测结果
void NN::GetResult()
{
  ifstream fin("data.in");
  ofstream fout("data.out");

  streambuf *in, *out;
  in = cin.rdbuf(fin.rdbuf());
  out = cout.rdbuf(fout.rdbuf());

  cout << "Input the three parameters:\n";
  
  while(!cin.eof())
    {
      int y;
      a1[0][0] = 1;
      cin >> a1[1][0] >> a1[2][0] >> y;
      
      Active();

      
      cout << "Result: " << a1[1][0] << " " << a1[2][0] << " " << a3 << ' '
	   << y << endl; 
    }
  cin.rdbuf(in);
  cout.rdbuf(out);

  fin.close();
  fout.close();
}

void NN::Gradient_Decrease()
{
  ifstream in;
  in.open("data.in", ios::in);
  //进行一次迭代
  while(!in.eof())
    {
      a1[0][0] = 1;
      in  >> a1[1][0] >> a1[2][0] >> y;
      cout << "The " << m << "th training" << endl;

      Display();

      Active();
      Backpro();

      m++;
    }
  //梯度下降
  for(int r = 0; r < 3; r++)
    for(int c = 0; c < 3; c++)
      {
	//带惩罚项
	//W1[r][c] -= Alpha*((Delta_W1[r][c]/m) + Lambda*W1[r][c]);
	W1[r][c] -= Alpha*(Delta_W1[r][c]/m);
      }
  
  for(int r = 0; r < 3; r++)
    {
      //带惩罚项
      //W2[0][r] -= Alpha * ((Delta_W2[0][r]/m) + Lambda*W2[0][r]);
      W2[0][r] -= Alpha * (Delta_W2[0][r]/m);
      b1[r][0] -= Alpha * (Delta_b1[r][0]/m);
    }
  
  b2 -= Alpha * (Delta_b2/m);
  //再次初始化
  m = 1;

  for(int r = 0; r < 3; r++)
    for(int c = 0; c < 3; c++)
      {
	Delta_W1[r][c] = 0;
      }
  
  for(int r = 0; r < 3; r++)
    {
      Delta_W2[0][r] = 0;
      Delta_b1[r][0] = 0;
      Delta_b2 = 0;
      b1[r][0] = 0;
      b2 = 0;
    }
  
  in.close();
}

void NN::Display()
{
  cout << "W1:" << endl;
  for(int r = 0; r < 3; r++)
    {
      for(int c = 0; c < 3; c++)
	{
	  cout << W1[r][c] << " ";
	}

      cout << endl;
    }

  cout << "W2:" << endl;
  for(int i = 0; i < 3; i++)
    {
      cout << W2[0][i] << " ";
    }
  cout << endl;

  cout << "b1:" << endl;
  for(int i = 0; i < 3; i++)
    {
      cout << b1[i][0] << " ";
    }
  cout << endl;

  cout << "b2:" << endl;
  for(int i = 0; i < 1; i++)
    {
      cout << b2 << " ";
    }
  cout << endl;

  cout << "a2:" << endl;
  for(int i = 0; i < 3; i++)
    {
      cout << a2[i][0] << " ";
    }
  cout << endl;

  cout << endl;
}

int main()
{
  NN NetWork;

  for(int i = 0; i < 100000; i++)
    NetWork.Gradient_Decrease();
  
  NetWork.Display();

  NetWork.GetResult();
  
  return 0;
}



