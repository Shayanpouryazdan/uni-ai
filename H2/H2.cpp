#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <string>

using namespace std;

// ساختار برای نگه‌داشتن اطلاعات پازل
struct Puzzle {
    vector<vector<int>> state;
    int x, y;        // مختصات خانه خالی
    int g, h;        // g: هزینه حرکت‌ها، h: مقدار هیوریستیک
    Puzzle *parent;  // اشاره‌گر به والد برای بازسازی مسیر

    Puzzle(vector<vector<int>> s, int x, int y, int g, int h, Puzzle *p)
        : state(s), x(x), y(y), g(g), h(h), parent(p) {}
};

// حرکات مجاز: راست، پایین، چپ، بالا
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

// هدف نهایی
vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
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

// محاسبه مقدار هیوریستیک (چند خانه در مکان درست نیستند)
int calculateHeuristic(const vector<vector<int>> &state) {
    int h = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] != 0 && state[i][j] != goal[i][j]) {
                h++;
            }
        }
    }
    return h;
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

// مقایسه اولویت در صف اولویت‌دار
struct Compare {
    bool operator()(const Puzzle *a, const Puzzle *b) {
        return (a->g + a->h) > (b->g + b->h); // f = g + h
    }
};

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

// الگوریتم A* برای حل پازل
void solvePuzzle(vector<vector<int>> start) {
    if (!isSolvable(start)) {
        cout << "این پازل حل نشدنی است!" << endl;
        return;
    }

    priority_queue<Puzzle *, vector<Puzzle *>, Compare> pq;
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

    int h = calculateHeuristic(start);
    Puzzle *initial = new Puzzle(start, x, y, 0, h, nullptr);
    pq.push(initial);
    visited.insert(toString(start));

    while (!pq.empty()) {
        Puzzle *current = pq.top();
        pq.pop();

        // افزایش شمارنده حالات جستجو شده
        exploredStates++;

        // بررسی رسیدن به هدف
        if (current->state == goal) {
            cout << "پازل در " << current->g << " حرکت حل شد!" << endl;
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
                    int newH = calculateHeuristic(newState);
                    Puzzle *next = new Puzzle(newState, nx, ny, current->g + 1, newH, current);
                    pq.push(next);
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