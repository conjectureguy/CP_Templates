template <typename T>
class Matrix {
 public:
  vector<vector<T> > A;
  int r, c;

  // Default Constructor
  Matrix() {
    this->r = 0;
    this->c = 0;
  }

  // Matrix with given dimensions and random values
  Matrix(int r, int c) {
    this->r = r;
    this->c = c;
    A.assign(r, vector<T>(c));
  }

  // Matrix with given value and dimensions
  Matrix(int r, int c, const T &val) {
    this->r = r;
    this->c = c;
    A.assign(r, vector<T>(c, val));
  }

  // Identity matrix with given dimension
  Matrix(int n) {
    this->r = this->c = n;
    A.assign(n, vector<T>(n));
    for (int i = 0; i < n; i++) A[i][i] = (T)1;
  }

  // Print the matrix
  void display() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) cout << A[i][j] << " ";

      cout << endl;
    }
  }

  // Input called to get input
  // Put custom code
  void input() {
    // for(int i=0;i<r;i++)
    //     for(int j=0;j<c;j++)
    //         define inout here
  }

  // Overloaded * operator to multiply 2 matrices
  // with conformable dimensions
  Matrix operator*(const Matrix<T> &B) {
    assert(c == B.r);
    int i, j, k;
    int x = r;
    int y = c;
    int z = B.c;

    Matrix<T> C(x, z, 0);

    for (i = 0; i < x; i++)
      for (j = 0; j < z; j++)
        for (k = 0; k < y; k++) {
          C[i][j] = (C[i][j] + ((long long)A[i][k] * (long long)B[k][j]));
          C[i][j] %= MOD;
        }

    return C;
  }

  // Overloaded *= operator to add 2 matrices
  // of conformable dimensions
  // and save result in first matrix
  void operator*=(const Matrix<T> &B) {
    assert(c == B.r);
    int i, j, k;
    int x = r;
    int y = c;
    int z = B.c;

    Matrix<T> C(x, z, 0);

    for (i = 0; i < x; i++)
      for (j = 0; j < z; j++)
        for (k = 0; k < y; k++) {
          C[i][j] = (C[i][j] + ((long long)A[i][k] * (long long)B[k][j]));
          C[i][j] %= MOD;
        }
    this->r = C.r;
    this->c = C.c;
    this->A = C.A;
  }

  // Overloaded + operator to add 2 matrices
  // with same dimensions
  Matrix operator+(const Matrix<T> &B) {
    assert(r == B.r);
    assert(c == B.c);

    Matrix<T> C(r, c, 0);
    int i, j;
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) {
        C[i][j] = A[i][j] + B[i][j];
        C[i][j] %= MOD;
      }

    return C;
  }

  // Overloaded += operator to add 2 matrices
  // of same dimensions
  // and save result in first matrix
  void operator+=(const Matrix<T> &B) {
    assert(r == B.r);
    assert(c == B.c);

    int i, j;
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) {
        A[i][j] = A[i][j] + B[i][j];
        A[i][j] %= MOD;
      }
  }

  // Overload unary - to get negative of a matrix
  Matrix operator-() {
    Matrix<T> C(r, c, 0);
    int i, j;
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) {
        C[i][j] = -A[i][j];
        C[i][j] %= MOD;
        if (C[i][j] < 0) C[i][j] += MOD;
      }

    return C;
  }

  // Overload binary - to subtract a matrix
  // from other with same dimensions
  Matrix operator-(const Matrix<T> &B) {
    assert(r == B.r);
    assert(c == B.c);

    Matrix<T> C(r, c, 0);
    int i, j;
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) {
        C[i][j] = A[i][j] - B[i][j];
        C[i][j] %= MOD;
        if (C[i][j] < 0) C[i][j] += MOD;
      }

    return C;
  }

  // Overload binary - to subtract a matrix
  // from other with same dimensions
  // and save result in first matrix
  void operator-=(const Matrix<T> &B) {
    assert(r == B.r);
    assert(c == B.c);

    int i, j;
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) {
        A[i][j] = A[i][j] - B[i][j];
        A[i][j] %= MOD;
        if (A[i][j] < 0) A[i][j] += MOD;
      }
  }

  // Overload ^ operator to raise a square matrix to a power
  // Using binary matrix exponentiation
  Matrix operator^(long long n) {
    assert(r == c);

    int i, j;
    Matrix<T> C(r);

    Matrix<T> X(r, c, 0);
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) X[i][j] = A[i][j];

    while (n) {
      if (n & 1) C *= X;

      X *= X;
      n /= 2;
    }
    return C;
  }

  // overloaded ^= operator to raise square matrix to power
  // Using binary exponentiation and store the result
  // in same matrix
  void operator^=(long long n) {
    assert(r == c);

    int i, j;
    Matrix<T> C(r);

    Matrix<T> X(r, c, 0);
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) X[i][j] = A[i][j];

    while (n) {
      if (n & 1) C *= (*this);

      (*this) *= (*this);
      n /= 2;
    }
    this->A = C.A;
  }

  // transpose operation
  Matrix transpose() {
    Matrix<T> C(c, r);

    int i, j;
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) C[j][i] = A[i][j];

    return C;
  }

  // transpose inplace
  void transposeInplace() {
    Matrix<T> C(c, r);

    int i, j;
    for (i = 0; i < r; i++)
      for (j = 0; j < c; j++) C[j][i] = A[i][j];

    this->r = C.r;
    this->c = C.c;
    this->A = C.A;
  }

  // Overload to access/set elements without using dot operator
  // Example :
  // Matrix m(5,3);
  // m.A[i][j] is valid to access
  // m[i][j] is valid as well
  vector<T> &operator[](int i) {
    assert(i < r);
    assert(i >= 0);
    return A[i];
  }

  // Overload to access/set elements without using dot operator
  // for accessing from cosnt objects
  const vector<T> &operator[](int i) const {
    assert(i < r);
    assert(i >= 0);
    return A[i];
  }

  // outstream has been overloaded to quickly print the matrix
  // help quicken the debugging process
  // eg) cout << M <<endl;
  friend ostream &operator<<(ostream &out, const Matrix<T> &M) {
    for (int i = 0; i < M.r; ++i) {
      for (int j = 0; j < M.c; ++j) {
        out << M[i][j] << " ";
      }
      out << '\n';
    }
    return out;
  }
};
