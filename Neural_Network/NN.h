#define Alpha 0.1
#define Lambda 0.01
#define PI 3.1415926
#define E 2.718281

typedef class Neural_Net
{
private:
  double **W1, **W2;
  double **b1, b2;
  double **R1, R2;
  double **a1, **a2, a3;
  double **Delta_W1, **Delta_W2;
  double **Delta_b1, Delta_b2;
  int m;
  int y;

public:
  Neural_Net();
  void Display();
  double GaussRan();
  void Active();
  void Backpro();
  double Function(double Z);
  void Gradient_Decrease();
  void Matrix_Mul(double **Ori1, double **Ori2, double **Dest ,int row, int k, int col);
  void GetResult();
  void DeleteArr(double **Arr, int r);
  ~Neural_Net();
}NN;
