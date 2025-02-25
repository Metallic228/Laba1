#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <windows.h>
#include <psapi.h>  // Подключаем библиотеку для получения информации о процессе
#include <locale.h>

using namespace std;
using namespace chrono;

// Функция для измерения используемой памяти в КБ
size_t getMemoryUsage() { //функция типа size_t
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        return memInfo.WorkingSetSize / 1024; // Преобразуем байты в килобайты
    }
    return 0; // В случае ошибки вернём 0
}

void findMinimalOnesNumber(int N) {
    auto start = high_resolution_clock::now(); // Засекаем время

    queue<long long> q;
    unordered_set<long long> visited; // Храним остатки, чтобы не проверять одно и то же

    q.push(1);
    while (!q.empty()) {
        long long num = q.front();
        q.pop();

        if (num % N == 0) {
            cout << num << endl;

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << "Время выполнения: " << duration.count() << " мс" << endl;
            cout << "Использовано памяти: " << getMemoryUsage() << " KB" << endl;
            return;
        }

        long long next1 = num * 10 + 1;

        if (visited.find(next1 % N) == visited.end()) {
            q.push(next1);
            visited.insert(next1 % N);
        }
    }

    cout << "NO" << endl;



}

int main() {
    setlocale(LC_ALL, "rus");
    int N;
    cout << "Введите число N: ";
    cin >> N;

    findMinimalOnesNumber(N);

    return 0;
}
