#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

// هدف نهایی
vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// ساختار حالت پازل
struct Puzzle {
    vector<vector<int>> state;
    int x, y;        // مختصات خانه خالی
    int moves;       // تعداد حرکت‌ها
    Puzzle *parent;  // اشاره‌گر به والد برای بازسازی مسیر

    Puzzle(vector<vector<int>> s, int x, int y, int m, Puzzle *p)
        : state(s), x(x), y(y), moves(m), parent(p) {}
};

// تبدیل حالت پازل به رشته (برای ذخیره در مجموعه)
string toString(const vector<vector<int>> &state) {
    string result;
    for (const auto &row : state) {
        for (int num : row) {
            result += to_string(num);
        }
    }
    return result;
}

// بررسی حل‌شدنی بودن پازل
bool isSolvable(const vector<vector<int>> &state) {
    vector<int> flattened;
    for (const auto &row : state) {
        for (int num : row) {
            if (num != 0) flattened.push_back(num);
        }
    }

    int inversions = 0;
    for (size_t i = 0; i < flattened.size(); ++i) {
        for (size_t j = i + 1; j < flattened.size(); ++j) {
            if (flattened[i] > flattened[j]) ++inversions;
        }
    }
    return inversions % 2 == 0;
}

// چاپ مسیر
void printPath(Puzzle *p) {
    if (p == nullptr) return;
    printPath(p->parent);
    for (const auto &row : p->state) {
        for (int num : row) {
            cout << (num == 0 ? "_" : to_string(num)) << " ";
        }
        cout << endl;
    }
    cout << "-------" << endl;
}

// حرکات مجاز: راست، پایین، چپ، بالا
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

// الگوریتم BFS
void solvePuzzle(vector<vector<int>> start) {
    if (!isSolvable(start)) {
        cout << "این پازل حل نشدنی است!" << endl;
        return;
    }

    queue<Puzzle *> q;
    unordered_set<string> visited;
    int exploredStates = 0; // شمارنده حالات جستجو شده

    // پیدا کردن خانه خالی
    int x, y;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (start[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    Puzzle *initial = new Puzzle(start, x, y, 0, nullptr);
    q.push(initial);
    visited.insert(toString(start));

    while (!q.empty()) {
        Puzzle *current = q.front();
        q.pop();

        // افزایش شمارنده حالات جستجو شده
        exploredStates++;

        // بررسی رسیدن به هدف
        if (current->state == goal) {
            cout << "پازل در " << current->moves << " حرکت حل شد!" << endl;
            cout << "تعداد حالات جستجو شده: " << exploredStates << endl;
            printPath(current);
            return;
        }

        // تولید حالات جدید
        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> newState = current->state;
                swap(newState[current->x][current->y], newState[nx][ny]);

                string newStateStr = toString(newState);
                if (visited.find(newStateStr) == visited.end()) {
                    visited.insert(newStateStr);
                    Puzzle *next = new Puzzle(newState, nx, ny, current->moves + 1, current);
                    q.push(next);
                }
            }
        }
    }

    cout << "پاسخی یافت نشد!" << endl;
    cout << "تعداد حالات جستجو شده: " << exploredStates << endl;
}

int main() {
    // حالت شروع
    vector<vector<int>> start = {
        {8, 6, 7},
        {2, 5, 4},
        {3, 0, 1}
    };

    solvePuzzle(start);

    return 0;
}