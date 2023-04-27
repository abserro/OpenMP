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

int composition(const vector<int>& vec_1, const vector<int>& vec_2, int start, int end) {
    long long int total = 1;
    for (int i = start; i < end; i++) {
        if (vec_1[i] + vec_2[i] != 0) {
            total *= vec_1[i] + vec_2[i];
        }
    }
    return total;
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

    cout << "\n\n* С распал. (without sections)" << endl;
    auto start = chrono::high_resolution_clock::now();

#pragma omp parallel
#pragma for private(i) reduction(*:total) nowait
    {
        for (i = 0; i < N; i++)
        {
            if (A[i] + B[i] != 0) {
                total *= A[i] + B[i];
            }
#pragma omp barrier
        }
    }
    
    /* Завершение параллельного фрагмента */
    time = chrono::high_resolution_clock::now() - start;

    cout << "Произведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns";


    total = 1;
    cout << "\n\n* С распал. (sections 2)" << endl;
    start = chrono::high_resolution_clock::now();

#pragma omp parallel sections private(i) reduction(*:total)
    {
#pragma omp section 
            {
                cout << "sec 1: \n" << omp_get_thread_num() << endl;
                total *= composition(A, B, 0, N/2);
            }
#pragma omp section
            {
                cout << "sec 2: \n" << omp_get_thread_num() << endl;
                total *= composition(A, B, N/2, N);
            }
    }
    /* Завершение параллельного фрагмента */
    time = chrono::high_resolution_clock::now() - start;

    cout << "Произведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns";


    total = 1;
    cout << "\n\n* С распал. (sections 4)" << endl;
    start = chrono::high_resolution_clock::now();

#pragma omp parallel sections private(i) reduction(*:total)
    {
#pragma omp section 
        {
            cout << "sec 1: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 0, N / 4);
        }
#pragma omp section
        {
            cout << "sec 2: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 4, N / 2);
        }
#pragma omp section
        {
            cout << "sec 3: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 2, 3 * N / 4);
        }
#pragma omp section
        {
            cout << "sec 4: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 3 * N / 4, N);
        }
    }
    /* Завершение параллельного фрагмента */
    time = chrono::high_resolution_clock::now() - start;

    cout << "Произведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns";


    total = 1;
    cout << "\n\n* С распал. (sections 8)" << endl;
    start = chrono::high_resolution_clock::now();

#pragma omp parallel sections private(i) reduction(*:total)
    {
#pragma omp section 
        {
            cout << "sec 1: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 0, N / 8);
        }
#pragma omp section
        {
            cout << "sec 2: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 8, N / 4);
        }
#pragma omp section
        {
            cout << "sec 3: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 4, 3 * N / 8);
        }
#pragma omp section
        {
            cout << "sec 4: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 3 * N / 8, N / 2);
        }
#pragma omp section 
        {
            cout << "sec 5: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 2, 5*N / 8);
        }
#pragma omp section
        {
            cout << "sec 6: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 5*N / 8, 3*N / 4);
        }
#pragma omp section
        {
            cout << "sec 7: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 3*N/4, 7 * N / 8);
        }
#pragma omp section
        {
            cout << "sec 8: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 7 * N / 8, N);
        }
    }
    /* Завершение параллельного фрагмента */
    time = chrono::high_resolution_clock::now() - start;

    cout << "Произведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns";


    total = 1;
    cout << "\n\n* С распал. (sections 16)" << endl;
    start = chrono::high_resolution_clock::now();

#pragma omp parallel sections private(i) reduction(*:total)
    {
#pragma omp section 
        {
            cout << "sec 1: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 0, N / 16);
        }
#pragma omp section
        {
            cout << "sec 2: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 16, N / 8);
        }
#pragma omp section
        {
            cout << "sec 3: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 8, 3 * N / 16);
        }
#pragma omp section
        {
            cout << "sec 4: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 3 * N / 16, N / 4);
        }
#pragma omp section 
        {
            cout << "sec 5: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 4, 5 * N / 16);
        }
#pragma omp section
        {
            cout << "sec 6: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 5 * N / 16, 3 * N / 8);
        }
#pragma omp section
        {
            cout << "sec 7: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 3 * N / 8, 7 * N / 16);
        }
#pragma omp section
        {
            cout << "sec 8: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 7 * N / 16, N / 2);
        }
#pragma omp section 
        {
            cout << "sec 9: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, N / 2, 9 * N / 16);
        }
#pragma omp section
        {
            cout << "sec 10: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 9 * N / 16, 5 * N / 8);
        }
#pragma omp section
        {
            cout << "sec 11: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 5 * N / 8, 11 * N / 16);
        }
#pragma omp section
        {
            cout << "sec 12: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 11 * N / 16, 3 * N / 4);
        }
#pragma omp section 
        {
            cout << "sec 13: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 3 * N / 4, 13 * N / 16);
        }
#pragma omp section
        {
            cout << "sec 14: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 13 * N / 16, 7 * N / 8);
        }
#pragma omp section
        {
            cout << "sec 15: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 7 * N / 8, 15 * N / 16);
        }
#pragma omp section
        {
            cout << "sec 16: \n" << omp_get_thread_num() << endl;
            total *= composition(A, B, 15 * N / 16, N);
        }
    }
    /* Завершение параллельного фрагмента */
    time = chrono::high_resolution_clock::now() - start;

    cout << "Произведение Аi + Вi: " << total;
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

    cout << "Произведение Аi + Вi: " << total;
    cout << "\nВремя выполнения: " << time.count() << " ns" << endl;
}