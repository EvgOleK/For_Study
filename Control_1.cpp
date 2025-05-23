#include <iostream>
#include <cstdio>
#include <cstring>
#include <limits>
#include <cstdlib>

void FreeData(char**, int32_t );

void ReadData(char** lines, int32_t* keys, int32_t N)
{
    const int32_t MAX_BUFFER_SIZE{ 100 };
    char buffer[MAX_BUFFER_SIZE]{};
    for (int32_t i{ 0 }; i < N; ++i)
    {
        std::cin.getline(buffer, MAX_BUFFER_SIZE);

        int32_t number{};
        char temp[100]{};
        if (sscanf_s(buffer, "%s %d", temp, (unsigned)sizeof(temp), &number) != 2)
        {
            std::cout << "Невозможно решить задачу: неверный формат строки " << i + 1 << ".\n";
            FreeData(lines, N);
        }
        keys[i] = number;

        int32_t len = std::strlen(buffer);
        lines[i] = new char[len + 1] {};
        strcpy_s(lines[i], len + 1, buffer);
    }
}

void SortData(int32_t* keys, char** lines, int32_t N)
{
    for (int32_t i{ 1 }; i < N; ++i)
    {
        int32_t currentKey = keys[i];
        char* currentLine = lines[i];
        int32_t j = i - 1;
        while (j >= 0 && keys[j] > currentKey)
        {
            keys[j + 1] = keys[j];
            lines[j + 1] = lines[j];
            --j;
        }
        keys[j + 1] = currentKey;
        lines[j + 1] = currentLine;
    }
}

void CalculateStats(const int32_t* keys, int32_t N, int32_t& sum, int32_t& min, int32_t& max)
{
    sum = 0;
    min = std::numeric_limits<int>::max();
    max = std::numeric_limits<int>::min();
    for (int32_t i{ 0 }; i < N; ++i)
    {
        sum += keys[i];
        if (keys[i] < min)
        {
            min = keys[i];
        }
        if (keys[i] > max)
        {
            max = keys[i];
        }
    }
}

void PrintData(char** lines, int32_t N)
{
    std::cout << "\nОтсортированные строки:\n";
    for (int i{ 0 }; i < N; ++i)
    {
        std::cout << lines[i] << "\n";
    }
}

void PrintStats(int32_t sum, int32_t min, int32_t max)
{
    std::cout << "\nСумма чисел: " << sum << "\n";
    std::cout << "Максимальное число: " << max << "\n";
    std::cout << "Минимальное число: " << min << "\n";
}

void FreeData(char** lines, int32_t N)
{
    for (int32_t i{ 0 }; i < N; ++i)
    {
        delete[] lines[i];
    }
    delete[] lines;
}

#include <windows.h>
int main() 
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int32_t N{};
    std::cout << "Введите количество строк: ";
    std::cin >> N;
    std::cin.ignore();

    if (N <= 0)
    {
        std::cout << "Невозможно решить задачу: количество строк должно быть больше 0.\n";
        return 1;
    }

    char** lines = new char* [N] {};
    int32_t* keys = new int32_t[N] {};

    ReadData(lines, keys, N);
    SortData(keys, lines, N);

    int32_t sum{}, minValue{}, maxValue{};
    CalculateStats(keys, N, sum, minValue, maxValue);

    PrintData(lines, N);
    PrintStats(sum, minValue, maxValue);

    FreeData(lines, N);
    delete[] keys;

    return 0;
}