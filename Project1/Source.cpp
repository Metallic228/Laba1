#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <windows.h>
#include <psapi.h>  // ���������� ���������� ��� ��������� ���������� � ��������
#include <locale.h>

using namespace std;
using namespace chrono;

// ������� ��� ��������� ������������ ������ � ��
size_t getMemoryUsage() { //������� ���� size_t
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        return memInfo.WorkingSetSize / 1024; // ����������� ����� � ���������
    }
    return 0; // � ������ ������ ����� 0
}

void findMinimalOnesNumber(int N) {
    auto start = high_resolution_clock::now(); // �������� �����

    queue<long long> q;
    unordered_set<long long> visited; // ������ �������, ����� �� ��������� ���� � �� ��

    q.push(1);
    while (!q.empty()) {
        long long num = q.front();
        q.pop();

        if (num % N == 0) {
            cout << num << endl;

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << "����� ����������: " << duration.count() << " ��" << endl;
            cout << "������������ ������: " << getMemoryUsage() << " KB" << endl;
            return;
        }

        long long next1 = num * 10 + 1;

        if (visited.find(next1 % N) == visited.end()) {
            q.push(next1);
            visited.insert(next1 % N);
        }
    }

    cout << "NO" << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "����� ����������: " << duration.count() << " ��" << endl;
    cout << "������������ ������: " << getMemoryUsage() << " KB" << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int N;
    cout << "������� ����� N: ";
    cin >> N;

    findMinimalOnesNumber(N);

    return 0;
}
