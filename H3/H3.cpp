#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <cmath>
#include <tuple>

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
    int x, y;          // مختصات خانه خالی
    int moves;         // تعداد حرکت‌ها
    int h;             // مقدار هیوریستیک
    Puzzle *parent;    // اشاره‌گر به والد برای بازسازی مسیر

    Puzzle(vector<vector<int>> s, int x, int y, int m, int h, Puzzle *p)
        : state(s), x(x), y(y), moves(m), h(h), parent(p) {}
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

// محاسبه هیوریستیک تعداد خانه‌های نادرست
int misplacedTiles(const vector<vector<int>> &state) {
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] != 0 && state[i][j] != goal[i][j]) {
                count++;
            }
        }
    }
    return count;
}

// محاسبه هیوریستیک فاصله منهتن
int manhattanDistance(const vector<vector<int>> &state) {
    int distance = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] != 0) {
                int value = state[i][j] - 1;
                int targetX = value / 3;
                int targetY = value % 3;
                distance += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return distance;
}

// هیوریستیک ترکیبی
int combinedHeuristic(const vector<vector<int>> &state) {
    int h1 = misplacedTiles(state);
    int h2 = manhattanDistance(state);
    return h1 + h2; // ترکیب خطی دو هیوریستیک
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

// مقایسه پازل‌ها بر اساس f = g + h
struct Compare {
    bool operator()(Puzzle *a, Puzzle *b) {
        return (a->moves + a->h) > (b->moves + b->h);
    }
};

// الگوریتم A* با هیوریستیک ترکیبی
void solvePuzzle(vector<vector<int>> start) {
    priority_queue<Puzzle *, vector<Puzzle *>, Compare> pq;
    unordered_set<string> visited;
    int exploredStates = 0; // شمارنده حالات بررسی‌شده

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

    int h = combinedHeuristic(start);
    Puzzle *initial = new Puzzle(start, x, y, 0, h, nullptr);
    pq.push(initial);
    visited.insert(toString(start));

    while (!pq.empty()) {
        Puzzle *current = pq.top();
        pq.pop();

        // افزایش شمارنده حالات بررسی‌شده
        exploredStates++;

        // بررسی رسیدن به هدف
        if (current->state == goal) {
            cout << "پازل در " << current->moves << " حرکت حل شد!" << endl;
            cout << "تعداد حالات بررسی‌شده: " << exploredStates << endl;
            printPath(current);
            return;
        }

        // تولید حالات جدید
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> newState = current->state;
                swap(newState[current->x][current->y], newState[nx][ny]);

                string newStateStr = toString(newState);
                if (visited.find(newStateStr) == visited.end()) {
                    visited.insert(newStateStr);
                    int newH = combinedHeuristic(newState);
                    Puzzle *next = new Puzzle(newState, nx, ny, current->moves + 1, newH, current);
                    pq.push(next);
                }
            }
        }
    }

    cout << "پاسخی یافت نشد!" << endl;
    cout << "تعداد حالات بررسی‌شده: " << exploredStates << endl;
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