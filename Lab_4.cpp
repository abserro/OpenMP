#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

const int N = 1000000;
const int R = 50;

void fill(vector<int>& vec) {
    for (int i = 0; i < N; i++) {
        vec[i] = rand() % R;
    }
}

void show(const vector<int>& vec) {
    for (int i = 0; i < N; i++) {
        cout << vec[i] << "  ";
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    chrono::duration<int64_t, nano> time;

    vector <int> A(N);
    vector <int> B(N);
    fill(A);
    fill(B);
    cout << "Вектор A: " << endl;
    //show(A);
    cout << "\nВектор B: " << endl;
    //show(B);

    int i = 0;
    long long int total = 1;


    cout << "\n\n* С распал. (critical)" << endl;
    auto start = chrono::high_resolution_clock::now();

#pragma omp parallel for private(i)
    for (i = 0; i < N; i++)
    {
        if (A[i] + B[i] != 0) {
#pragma omp critical
            total *= A[i] + B[i];
        }
    }
    /* Завершение параллельного фрагмента */
    time = chrono::high_resolution_clock::now() - start;

    cout << "\nПроизведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns";

    cout << "\n\n* С распал. (atomic)" << endl;
    start = chrono::high_resolution_clock::now();
    total = 1;
#pragma omp parallel for private(i)
    for (i = 0; i < N; i++)
    {
        if (A[i] + B[i] != 0) {
#pragma omp atomic
            total *= A[i] + B[i];
        }
    }
    /* Завершение параллельного фрагмента */
    time = chrono::high_resolution_clock::now() - start;

    cout << "\nПроизведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns";


    cout << "\n\n* С распал. (reduction)" << endl;
    start = chrono::high_resolution_clock::now();
    total = 1;
#pragma omp parallel for private(i) reduction(*:total)
    for (i = 0; i < N; i++)
    {
        if (A[i] + B[i] != 0) {
            total *= A[i] + B[i];
        }
    }
    /* Завершение параллельного фрагмента */
    time = chrono::high_resolution_clock::now() - start;

    cout << "\nПроизведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns";


    total = 1;
    cout << "\n\n* Бес распал." << endl;
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        if (A[i] + B[i] != 0) {
            total *= A[i] + B[i];
        }
    }
    time = chrono::high_resolution_clock::now() - start;

    cout << "\nПроизведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns" << endl;
}