#include <ctime>
#include <iostream>
#include <fstream>

/*Порядок: по убыванию элементов. Методы: пузырька, пузырька с фиксацией факта
обмена, пузырька с фиксацией места обмена, шейкера. N1=5000, N2=15000, N3=30000, N4=50000.
Критерий – количество сравнений. */

/*В первой программе провести сравнение указанных алгоритмов сортировки массивов,
содержащих N1, N2, N3 и N4 элементов. Каждую функцию сортировки вызывать трижды: для
сортировки неупорядоченного массива, упорядоченного массива и массива, упорядоченного в
обратном порядке. При работе каждого алгоритма сортировки выполнить подсчет основных
(производимых над элементами массива) и вспомогательных (всех остальных) операций,
указанных в вариативной части задания (сравнений или присваиваний), а также зафиксировать
время работы алгоритма. Сортируемая последовательность для всех методов должна быть
одинаковой (считывать необходимое количество элементов из прилагаемого файла
test_numbers.txt). Оценить время работы и эффективность алгоритмов сортировки по заданному
критерию и объему требуемой дополнительно памяти.*/

int* besporyadok_massiv(int n);
int* neporyadok_massiv(int n);
int* poryadok_massiv(int n);
using namespace std;

void BubbleSort(int* a, int n); //пузырек
void BubbleSort1(int* a, int n); //пузырек с фиксацией факта обмена
void BubbleSort2(int* a, int n); //пузырек с фиксацией места обмена
void ShakerSort(int* a, int n); //шейкерная сортировка


int main()
{
    setlocale(0, "Russian");
    int kol[4], i, n1 = 5000, n2 = 15000, n3 = 30000, n4 = 50000,*a;
    kol[0] = n1; kol[1] = n2; kol[2] = n3; kol[3] = n4;
    for (i = 0; i < 4; i++)
    {
        cout << "Массив без порядка:" << endl;
        BubbleSort(besporyadok_massiv(kol[i]), kol[i]);
        BubbleSort1(besporyadok_massiv(kol[i]), kol[i]);
        BubbleSort2(besporyadok_massiv(kol[i]), kol[i]);
        ShakerSort(besporyadok_massiv(kol[i]), kol[i]);
        cout << "Массив упорядочен:" << endl;
        BubbleSort(poryadok_massiv(kol[i]), kol[i]);
        BubbleSort1(poryadok_massiv(kol[i]), kol[i]);
        BubbleSort2(poryadok_massiv(kol[i]), kol[i]);
        ShakerSort(poryadok_massiv(kol[i]), kol[i]);
        cout << "Массив упорядочен обратно:" << endl;
        BubbleSort(neporyadok_massiv(kol[i]), kol[i]);
        BubbleSort1(neporyadok_massiv(kol[i]), kol[i]);
        BubbleSort2(neporyadok_massiv(kol[i]), kol[i]);
        ShakerSort(neporyadok_massiv(kol[i]), kol[i]);
    }
    return 0;
}

int* besporyadok_massiv(int n)
{
    int* a, x;
    a = new int[n];
    ifstream f("test_numbers.txt");
    for (int i = 0; i < n; i++)
    {
        f >> x;
        a[i] = x;
    }
    return a;
}

int* neporyadok_massiv(int n)
{
    int* a, x;
    a = new int[n];
    for (int i = 0; i < n;i++)
    {
        a[i] = i;
    }
    return a;
}

int* poryadok_massiv(int n)
{
    int* a, x;
    a = new int[n];
    for (int i = 0, j=n-1; i < n; i++,j--)
    {
        a[i] = j;
    }
    return a;
}

void BubbleSort(int* a, int n) //пузырек
{
    int i, j, x, time=clock();
    unsigned long long kolo = 0, kolm = 0;
    for (i = 1; ++kolo && i < n; i++)
    {
        for (j = n - 1; ++kolo && j >= i; j--)
        {
            kolm += 1;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
    }
    cout << "Метод пузырька для " << n << " элементов " << "runtime = " << (clock()-time)/ 1000.
        << "\nКол-во операций: М = " << kolm << " Вспомогательных = " << kolo << endl;
    delete[]a;
    
}

void BubbleSort1(int* a, int n) //пузырек с фиксацией факта обмена
{
    int i, j, x, flag = 1, time = clock();
    unsigned long long kolo = 0, kolm = 0;
    for (i = 1; ++kolo && flag; i++)
    {
        flag = 0; /*признак упорядоченной последовательности*/
        for (j = n - 1; ++kolo && j >= i; j--)
        {
            kolm += 1;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                flag = 1; /*была перестановка, значит, еще не все*/
            }
        }
    }
    cout << "Метод пузырька с фиксацией факта обмена для " << n << " элементов " << "runtime = " << (clock() - time) / 1000.
        << "\nКол-во операций: М = " << kolm << " Вспомогательных = " << kolo << endl;
    delete[]a;
}

void BubbleSort2(int* a, int n) //пузырек с фиксацией места обмена
{
    int i = 1, j, x, k, time = clock(); /*i=1 - левая граница сравниваемых элементов*/
    unsigned long long kolo = 0, kolm = 0;
    do
    {
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; ++kolo && j >= i; j--)
        {
            kolm += 1;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        }
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (++kolo && k);
    cout << "Метод пузырька с фиксацией места обмена для " << n << " элементов " << "runtime = " << (clock() - time) / 1000.
        << "\nКол-во операций: М = " << kolm << " Вспомогательных = " << kolo << endl;
    delete[]a;
}

void ShakerSort(int* a, int n) //шейкерная сортировка
{

    int j, k = n - 1, left = 1, right = n - 1, x, time = clock();
    unsigned long long kolo = 0, kolm = 0;
    do
    {
        for (j = right; ++kolo && j >= left; j--) /*сначала просматриваем справа налево*/
        {
            kolm += 1;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j;
            }
        }
        left = k + 1;
        for (j = left; ++kolo && j <= right; j++) /*а теперь просматриваем слева направо*/
        {
            kolm += 1;
            if (a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j;
            }
        }
        right = k - 1;
    } while (++kolo && left < right); /*и так до тех пор, пока есть что просматривать*/
    cout << "Шейкерная сортировка для " << n << " элементов " << "runtime = " << (clock() - time) / 1000.
        << "\nКол-во операций: М = " << kolm << " Вспомогательных = " << kolo << endl;
    delete[]a;
}