#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

const int N = 10;
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
    srand(time(NULL));
    chrono::duration<int64_t, nano> time;

    vector <int> A(N);
    vector <int> B(N);
    fill(A);
    fill(B);
    cout << "Vector A: " << endl;
    //show(A);
    cout << "\nVector B: " << endl;
    //show(B);

    int i = 0;
    unsigned long long int total = 1;


    cout << "\n\n* Critical section: " << endl;
    auto start = chrono::high_resolution_clock::now();

#pragma omp parallel for private(i)
    for (i = 0; i < N; i++)
    {
        if (A[i] + B[i] != 0) {
#pragma omp critical
            total *= A[i] + B[i];
        }
    }
    time = chrono::high_resolution_clock::now() - start;

    cout << "\nResult Ai + Bi: " << total;
    cout << "\nTime: " << time.count() << " ns";


    cout << "\n\n* Locks: " << endl;
    total = 1;
    omp_lock_t lock;
    omp_init_lock(&lock);
    start = chrono::high_resolution_clock::now();
#pragma omp parallel for private(i)
    for (i = 0; i < N; i++)
    {
        if (A[i] + B[i] != 0) {
            omp_set_lock(&lock);
            total *= A[i] + B[i];
            omp_unset_lock(&lock);
        }
    }
    time = chrono::high_resolution_clock::now() - start;
    omp_destroy_lock(&lock);
    cout << "\nResult Ai + Bi: " << total;
    cout << "\nTime: " << time.count() << " ns";


    
}