#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "sort.hpp"
using namespace std;

int main() {
    random_device rd;
    minstd_rand rng(rd());
    vector<int> test1, test2, test3, test4, test5, test6, test7;
    for (int i = 0; i < 25;++i) {
        auto a = rng();
        test1.push_back(a);
        test2.push_back(a);
        test3.push_back(a);
        test4.push_back(a);
        test5.push_back(a);
        test6.push_back(a);
        test7.push_back(a);
    }
    auto t0 = chrono::steady_clock::now();
    auto t1 = chrono::steady_clock::now();
    bubble_sort(test1);
    auto t2 = chrono::steady_clock::now();
    insertion_sort(test2);
    auto t3 = chrono::steady_clock::now();
    selection_sort(test3);
    auto t4 = chrono::steady_clock::now();
    merge_sort(test4);
    auto t5 = chrono::steady_clock::now();
    quick_sort_extra(test5);
    auto t6 = chrono::steady_clock::now();
    quick_sort_inplace(test6);
    auto t7 = chrono::steady_clock::now();
    sort(test7.begin(), test7.end());
    auto t8 = chrono::steady_clock::now();
    double bubble = chrono::duration<double, milli>(t2 - t1).count();
    double insertion = chrono::duration<double, milli>(t3 - t2).count();
    double selection = chrono::duration<double, milli>(t4 - t3).count();
    double merge = chrono::duration<double, milli>(t5 - t4).count();
    double quick_e = chrono::duration<double, milli>(t6 - t5).count();
    double quick_i = chrono::duration<double, milli>(t7 - t6).count();
    double sortstd = chrono::duration<double, milli>(t8 - t7).count();
    cout << bubble << " " << insertion << " " << selection << " " << merge << " " << quick_e << " " << quick_i << " " << sortstd << endl;
    return 0;
}