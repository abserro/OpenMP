#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <vector>
#include <ctime>

using namespace std;

const int M = 15;
const int N = 15;

int count_units(unsigned int number) {
    int count = 0;
    while (number > 0) {
        if (number % 2 == 1) {
            count++;
        }
        number /= 2;
    }
    return count;
};

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    int i, j, k;
    vector <vector <unsigned int>> matrix(M, vector <unsigned int>(N));
    //vector <int> sum_1(N);
    //vector <int> sum_2(N);

    cout << "Исходная матрица: " << endl;
    cout << "\n\nРазмер матрицы: " << M << " * " << N << endl;

    for (i=0; i < M; i++) {
        for (j=0; j < N; j++) {
            matrix[i][j] = 1 + rand() % (10 - 1 + 1);
            //cout << matrix[i][j] << "   ";
        }
        //cout << endl;
    }
    
    cout << "\nБез распараллеливания: " << endl;

    int start = clock();
    int sum_units = 0;
    for (i = 0; i < M; i++) {
        sum_units = 0;
        for (j = 0; j < N; j++) {
            for (k = j+1; k < N; k++) {
                sum_units += count_units(matrix[i][j] * matrix[i][k]);
            }
        }
        cout << sum_units << "   ";
        //sum_1.push_back(sum_units);
    }
    int end = clock();
    cout << "\nВремя: " << end - start  << " ms" << endl;
    
    cout << "\nС распараллеливанием: " << endl;
    
    start = clock();
    sum_units = 0;
#pragma omp parallel shared(matrix) private(i)
    {
#pragma omp for private(j, k, sum_units)
        
    for ( i = 0; i < M; i++) {
        sum_units = 0;
        for (j = 0; j < N; j++) {
            for (k = j + 1; k < N; k++) {
                sum_units += count_units(matrix[i][j] * matrix[i][k]);
            }
        }
        cout << sum_units << "   ";
        }
    }
    end = clock();
    cout << "\nВремя: " << end - start << " ms" << endl;
    
}