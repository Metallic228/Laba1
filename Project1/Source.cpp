#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;
using namespace chrono;

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        return memInfo.WorkingSetSize / 1024;
    }
    return 0;
}

struct Node {
    int remainder;
    int prevIndex;
};

void findMinimalOnesNumber(int N) {
    auto start = high_resolution_clock::now();

    if (N == 1) {
        cout << "Минимальное число: 1\n";
        cout << "Время выполнения: 0 мс\n";
        cout << "Использовано памяти: " << getMemoryUsage() << " KB\n";
        return;
    }

    vector<Node> nodes;
    vector<bool> visited(N, false);
    queue<int> q;

    nodes.push_back({ 1 % N, -1 });
    visited[1 % N] = true;
    q.push(0);

    int finalIndex = -1;

    while (!q.empty()) {
        int index = q.front();
        q.pop();

        int currentRemainder = nodes[index].remainder;

        if (currentRemainder == 0) {
            finalIndex = index;
            break;
        }

        int nextRemainder = (currentRemainder * 10 + 1) % N;

        if (!visited[nextRemainder]) {
            visited[nextRemainder] = true;
            nodes.push_back({ nextRemainder, index });
            q.push(nodes.size() - 1);
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    if (finalIndex != -1) {
        string result;
        int index = finalIndex;

        while (index != -1) {
            result = '1' + result;
            index = nodes[index].prevIndex;
        }

        cout << "Минимальное число: " << result << endl;
        cout << "Колличество единиц в числе: " << result.length() << endl;
        cout << "Время выполнения: " << duration.count() << " мс" << endl;
        cout << "Использовано памяти: " << getMemoryUsage() << " KB" << endl;
    } else {
        cout << "Решение не найдено." << endl;
        cout << "Время выполнения: " << duration.count() << " мс" << endl;
        cout << "Использовано памяти: " << getMemoryUsage() << " KB" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int N;
    cout << "Введите число N: ";
    cin >> N;

    if (N <= 0) {
        cout << "Число N должно быть положительным." << endl;
        return 1;
    }

    findMinimalOnesNumber(N);
    return 0;
}
