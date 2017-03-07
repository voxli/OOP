#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const double Eps = 10E-10;

int main()
{
    ifstream f_in_Matrix("Matrix.txt");
    ifstream f_in_B("vector.txt");

    int matrix_size;

    f_in_Matrix >> matrix_size;

    double* B = new double[matrix_size];
    double** A = new double*[matrix_size];

    for(int i = 0; i < matrix_size; i++)
    {
        A[i] = new double[matrix_size];
    }

    double** E = new double*[matrix_size];

    for(int i = 0; i < matrix_size; i++)
    {
        E[i] = new double[matrix_size];
    }

    for(int i = 0; i < matrix_size; i++)
    {
        for(int j = 0; j < matrix_size; j++)
        {
            if(i == j)
            {
                E[i][j] = 1;
            }
            else
            {
                E[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < matrix_size; i++)
    {
        for(int j = 0; j < matrix_size; j++)
        {
            f_in_Matrix >> A[i][j];
        }
    }

    for(int i = 0; i < matrix_size; i++)
    {
        f_in_B >> B[i];
    }

    double* new_B = new double[matrix_size];

    for(int i = 0; i < matrix_size; i++)
    {
        new_B[i] = B[i];
    }

    f_in_B.close();
    f_in_Matrix.close();

    double temp;
    double temp_A;

    for(int i = 0; i < matrix_size; i++)
    {
        for(int j = i; j < matrix_size; j++)
        {
            if(abs(A[j][i]) < Eps)
            {
                A[j][i] = 0;
            }
            else
            {
                for(int k = i; k < matrix_size; k++)
                {
                    swap(A[i][k], A[j][k]);
                }
                swap(B[i], B[j]);

                for(int k = 0; k < matrix_size; k++)
                {
                    swap(E[i][k], E[j][k]);
                }

                temp = A[i][i];

                for(int k = i; k < matrix_size; k++)
                {
                    A[i][k] /= temp;
                }
                B[i] /= temp;

                for(int k = 0; k < matrix_size; k++)
                {
                    E[i][k] /= temp;
                }

                for(int k = i + 1; k < matrix_size; k++)
                {
                    temp_A = A[k][i];

                    B[k] = B[k] - temp_A * B[i];

                    for(int q = i; q < matrix_size; q++)
                    {
                        A[k][q] = A[k][q] - temp_A * A[i][q];
                    }

                    for(int q = 0; q < matrix_size; q++)
                     {
                        E[k][q] = E[k][q] - temp_A * E[i][q];
                     }
                  }

                break;
            }
        }
    }

    double temp_X;

    for(int i = matrix_size - 1; i > 0; i--)
    {
        for(int j = i; j > 0; j--)
        {
            B[j - 1] = B[j - 1] - A[j - 1][i] * B[i];

            temp_X = A[j - 1][i];

            for(int k = i; k < matrix_size; k++)
            {
                A[j - 1][k] = A[j - 1][k] - temp_X * A[i][k];
            }

            for(int k = 0; k < matrix_size; k++)
            {
                E[j - 1][k] = E[j - 1][k] - temp_X * E[i][k];
            }
        }
    }

    double Determinant = 1;

    for(int i = 0; i < matrix_size; i++)
    {
        Determinant *= A[i][i];
    }

    if(Determinant != 0)
    {
        ofstream f_out("Answer.txt");

        for (int i = 0; i < matrix_size; i++)
        {
            f_out << B[i] << endl;
        }

        f_out.close();

        ifstream f_in_Matrix_new("Matrix.txt");

        f_in_Matrix_new >> matrix_size;

        for(int i = 0; i < matrix_size; i++)
        {
            for(int j = 0; j < matrix_size; j++)
            {
                f_in_Matrix_new >> A[i][j];
            }
        }

        f_in_Matrix_new.close();

        cout << "======= A^(-1) =======" << "\n" << endl;

        for(int i = 0; i < matrix_size; i++)
        {
            for(int j = 0; j < matrix_size; j++)
            {
                cout << E[i][j] << "   ";
            }

            cout << endl;
        }
        cout << "\n" << "======== A*A^(-1) ========= " << "\n" << endl;

        double x;

        for(int i = 0; i < matrix_size; i++)
        {
            for(int j = 0; j < matrix_size; j++)
            {
                x = 0;

                for(int k = 0; k < matrix_size; k++)
                {
                    x += A[i][k] * E[k][j];
                }

                if(abs(x) < Eps)
                {
                    x = 0;
                }

                cout << x << "   ";
            }

            cout << endl;
        }

        cout << endl;

        double* check_B = new double[matrix_size];

        for (int i = 0; i < matrix_size; i++)
        {
            check_B[i] = 0;

            for(int j = 0; j < matrix_size; j++)
            {
                check_B[i] += A[i][j] * B[j];
            }
        }

        cout << "===== Test ===============================" << "\n" << endl;

        cout << "==== Vector B ====" << "\n" << endl;

        for(int i = 0; i < matrix_size; i++)
        {
            cout << check_B[i] << endl;
        }

        cout << endl;

        cout << "==== Vector X ====" << "\n" << endl;

        for(int i = 0; i < matrix_size; i++)
        {
            cout << B[i] << endl;
        }

        delete [] check_B;
        delete [] B;
    }
    else
    {
        cout << "Matrix has more then one solutions";
    }

    for (int i = 0; i < matrix_size; i++)
    {
        delete A[i];
        delete E[i];
    }

    delete[] A;
    delete[] E;

    return 0;
}
