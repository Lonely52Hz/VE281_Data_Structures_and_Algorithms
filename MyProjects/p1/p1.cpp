#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> p0;

vector<vector<int>> graham(vector<vector<int>> &set);
int ccw(const vector<int> &p1, const vector<int> &p2, const vector<int> &p3);
bool comp(const vector<int> &p1, const vector<int> &p2);
void modify(vector<vector<int>> &set);
int small(vector<vector<int>> &set);

int main() {
    int n;
    int x, y = 0;
    vector<int> point;
    vector<vector<int>> set;
    vector<vector<int>> s;
    cin >> n;
    if (n <= 0) {
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        point.push_back(x);
        point.push_back(y);
        set.push_back(point);
        point.clear();
    }
    s = graham(set);
    for (int i = 0; i < (int)s.size(); ++i) {
        cout << s[i][0] << ' ' << s[i][1] << endl;
    }
    return 0;
}

vector<vector<int>> graham(vector<vector<int>> &set) {
    vector<vector<int>> s;
    int p0_idx = small(set);
    vector<int> temp = set[0];
    set[0] = set[p0_idx];
    set[p0_idx] = temp;
    sort(set.begin() + 1, set.end(), comp); // sort
    modify(set); // modify the sorted set
    for (int i = 0; i < (int)set.size(); ++i) {
        while ((int)s.size() > 1 && ccw(s[(int)s.size() - 2], s[(int)s.size() - 1], set[i]) <= 0) {
            s.pop_back();
        }
        s.push_back(set[i]);
    }
    return s;
}

int ccw(const vector<int> &p1, const vector<int> &p2, const vector<int> &p3) {
    return (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0]);
}

bool comp(const vector<int> &p1, const vector<int> &p2) {
    if (ccw(p0, p1, p2) >= 0) {
        return true;
    }
    else {
        return false;
    }
}

void modify(vector<vector<int>> &set) {
    for (auto i = set.begin() + 1; i < set.end(); ++i) { // delete those the same as p0
        if (*i == set[0]) {
            set.erase(i);
            i--;
        }
    }
    for (auto i = set.begin() + 1; i < set.end() - 1; ++i) { // choose the farthest one
        if (ccw(p0, *i, *(i + 1)) == 0) {
            if (((*i)[0] - p0[0]) * ((*i)[0] - p0[0]) > ((*(i + 1))[0] - p0[0]) * ((*(i + 1))[0] - p0[0])) {
                set.erase(i + 1);
                i--;
            }
            else if (((*i)[0] - p0[0]) * ((*i)[0] - p0[0]) < ((*(i + 1))[0] - p0[0]) * ((*(i + 1))[0] - p0[0])) {
                set.erase(i);
                i--;
            }
            else { // delete dupilicated one
                set.erase(i + 1);
                i--;
            }
        }
    }
}

int small(vector<vector<int>> &set) {
    p0 = set[0];
    int p0_idx = 0;
    for (int i = 1; i < (int)set.size(); ++i) {
        if (set[i][1] < p0[1] || (set[i][1] == p0[1] && set[i][0] < p0[0])) {
            p0 = set[i];
            p0_idx = i;
        }
    }
    return p0_idx;
}