#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <vector>

template<typename T, typename Compare = std::less<T> >
void bubble_sort(std::vector<T> &vector, Compare comp = Compare()) {
    // TODO: implement
    int size = (int)vector.size();
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (comp(vector[j+1], vector[j])) {
                T temp = vector[j + 1];
                vector[j + 1] = vector[j];
                vector[j] = temp;
            }
        }
    }
}

template<typename T, typename Compare = std::less<T> >
void insertion_sort(std::vector<T> &vector, Compare comp = Compare()) {
    // TODO: implement
    int size = (int)vector.size();
    int j;
    T temp;
    for (int i = 1; i < size;++i) {
        j = i - 1;
        temp = vector[i];
        while (j >= 0 && comp(temp,vector[j])) {
            vector[j + 1] = vector[j];
            j--;
        }
        vector[j + 1] = temp;
    }
}

template<typename T, typename Compare = std::less<T> >
void selection_sort(std::vector<T> &vector, Compare comp = Compare()) {
    // TODO: implement
    int size = (int)vector.size();
    int min_idx;
    for (int i = 0; i < size - 1; ++i) {
        min_idx = i;
        for (int j = i + 1; j < size; ++j) {
            if (comp(vector[j], vector[min_idx])) {
                min_idx = j;
            }
        }
        T temp = vector[min_idx];
        vector[min_idx] = vector[i];
        vector[i] = temp;
    }
}

template<typename T, typename Compare = std::less<T> >
void merge(std::vector<T> &vector, int l, int m, int r, Compare comp = Compare()) {
    int i = l;
    int j = m + 1;
    int k = 0;
    std::vector<T> temp(r - l + 1);
    while (i <= m && j <= r) {
        if (comp(vector[j], vector[i])) {
            temp[k++] = vector[j++];
        }
        else {
            temp[k++] = vector[i++];
        }
    }
    while (i <= m) {
        temp[k++] = vector[i++];
    }
    while (j <= r) {
        temp[k++] = vector[j++];
    }
    for (int m = 0; m < k; ++m) {
        vector[l + m] = temp[m];
    }
}

template<typename T, typename Compare = std::less<T> >
void merge_sort_helper(std::vector<T> &vector, int l, int r, Compare comp = Compare()) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    merge_sort_helper(vector, l, m, comp);
    merge_sort_helper(vector, m + 1, r, comp);
    merge(vector, l, m, r, comp);
}

template<typename T, typename Compare = std::less<T> >
void merge_sort(std::vector<T> &vector, Compare comp = Compare()) {
    // TODO: implement
    merge_sort_helper(vector, 0, (int)vector.size() - 1, comp);
}

template<typename T, typename Compare = std::less<T> >
int partition_extra(std::vector<T> &vector, int l, int r, Compare comp = Compare()) {
    T pivot = vector[l];
    std::vector<T> ex(vector);
    int ll = l;
    int rr = r;
    for (int i = l + 1; i <= r; ++i) {
        if (comp(vector[i], pivot)) {
            ex[ll] = vector[i];
            ll++;
        }
        else {
            ex[rr] = vector[i];
            rr--;
        }
    }
    ex[ll] = pivot;
    vector = ex;
    return ll;
}

template<typename T, typename Compare = std::less<T> >
void quick_sort_extra_helper(std::vector<T> &vector, int l, int r, Compare comp = Compare()) {
    int pivot_idx;
    if (l >= r) {
        return;
    }
    pivot_idx = partition_extra(vector, l, r, comp);
    quick_sort_extra_helper(vector, l, pivot_idx - 1, comp);
    quick_sort_extra_helper(vector, pivot_idx + 1, r, comp);
}

template<typename T, typename Compare = std::less<T> >
void quick_sort_extra(std::vector<T> &vector, Compare comp = Compare()) {
    // TODO: implement
    quick_sort_extra_helper(vector, 0, (int)vector.size() - 1, comp);
}

template<typename T, typename Compare = std::less<T> >
int partition_inplace(std::vector<T> &vector,int l, int r, Compare comp = Compare()) {
    T pivot = vector[l];
    int ll = l + 1;
    int rr = r;
    while (true) {
        while (comp(vector[ll], pivot) && ll <= r) {
            ll++;
        }
        while (!comp(vector[rr], pivot) && rr > l) {
            rr--;
        }
        if (ll < rr) {
            T temp = vector[ll];
            vector[ll] = vector[rr];
            vector[rr] = temp;
        }
        else {
            vector[l] = vector[rr];
            vector[rr] = pivot;
            break;
        }
    }
    return rr;
}

template<typename T, typename Compare = std::less<T> >
void quick_sort_inplace_helper(std::vector<T> &vector, int l, int r, Compare comp = Compare()) {
    int pivot_idx;
    if (l >= r) {
        return;
    }
    pivot_idx = partition_inplace(vector, l, r, comp);
    quick_sort_inplace_helper(vector, l, pivot_idx - 1, comp);
    quick_sort_inplace_helper(vector, pivot_idx + 1, r, comp);
}

template<typename T, typename Compare = std::less<T> >
void quick_sort_inplace(std::vector<T> &vector, Compare comp = Compare()) {
    // TODO: implement
    quick_sort_inplace_helper(vector, 0, (int)vector.size() - 1, comp);
}

#endif //VE281P1_SORT_HPP
