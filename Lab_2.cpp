// Lab_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    int i, j;
    int NMAX = 10;
    int LIMIT = 10;
    int sum;
    vector <vector <int>> a(NMAX, vector <int>(NMAX));
    chrono::duration<int64_t, nano> time_1;
    chrono::duration<int64_t, nano> time_2;

    //Заполнение вектора
    for (i = 0; i < NMAX; i++)
        for (j = 0; j < NMAX; j++)
            a[i][j] = rand() % 100;

    //Поиск оптимального предельного значения
    int count = 0;
    while (count < 10){
        //Без распал.
        cout << "* Размер массива: " << NMAX << endl;
        cout << "Без распал. " << endl;
        auto start = chrono::high_resolution_clock::now();
        for (i = 0; i < NMAX; i++)
        {
            sum = 0;
            for (j = 0; j < NMAX; j++)
                sum += a[i][j];
            //printf("Сумма элементов строки %d равна %f\n", i, sum);
        }
        time_1 = chrono::high_resolution_clock::now() - start;
        cout << "   Время: " << time_1.count() << endl;

        //С распал.
        cout << "С распал. " << endl;
        start = chrono::high_resolution_clock::now();
#pragma omp parallel shared(a)
        {
#pragma omp for private(i,j,sum) 
            for (i = 0; i < NMAX; i++)
            {
                sum = 0;
                for (j = 0; j < NMAX; j++)
                    sum += a[i][j];
                //printf("Сумма элементов строки %d равна %f\n", i, sum);
            }
        } /* Завершение параллельного фрагмента */
        time_2 = chrono::high_resolution_clock::now() - start;
        cout << "   Время: " << time_2.count() << endl;

        if (time_2 >= time_1) {
            count++;
        }

        NMAX++;
        a.assign(NMAX, vector<int>(NMAX, rand() % 100));
    }

    LIMIT = NMAX;
    cout << "LIMIT = " << LIMIT << endl;

    /*
    int start = clock();
#pragma omp parallel shared(a) if (NMAX>LIMIT)
    {
#pragma omp for private(i,j,sum) 
        for (i = 0; i < NMAX; i++) 
        {
            sum = 0;
            for (j = 0; j < NMAX; j++)
                sum += a[i][j];
            //printf("Сумма элементов строки %d равна %f\n", i, sum);
        }
    } /* Завершение параллельного фрагмента 
    int end = clock();
    cout << "Время выполнения: " << end - start << " ms" << endl;
    */
}
