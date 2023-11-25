#include <iostream>
#include <vector>

using namespace std;

bool customComparator2(const pair<vector<int>, string> &a, const pair<vector<int>, string> &b) {
    // Sort based on vector<int>[0]
    if (a.first[0] != b.first[0]) {
        return a.first[0] < b.first[0];
    }

    // Sort based on vector<int>[1]
    if (a.first[1] != b.first[1]) {
        return a.first[1] < b.first[1];
    }

    // Sort based on string in increasing alphabetical order
    return a.second < b.second;
}

void merge2(vector<pair<vector<int>, string>> &arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<pair<vector<int>, string>> L(n1);
    vector<pair<vector<int>, string>> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (customComparator2(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort2(vector<pair<vector<int>, string>> &arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort2(arr, l, m);
        mergeSort2(arr, m + 1, r);

        merge2(arr, l, m, r);
    }
}

int main() {
    // Example usage
    vector<pair<vector<int>, string>> data = {
        {{3, 5}, "apple"},
        {{2, 9}, "banana"},
        {{3, 5}, "orange"},
        {{1, 3}, "grape"},
        {{2, 8}, "kiwi"}
    };

    // Sorting the vector using custom comparator
    mergeSort2(data, 0, data.size() - 1);

    // Printing the sorted vector
    for (const auto &item : data) {
        cout << "{" << item.first[0] << ", " << item.first[1] << ", " << item.second << "} ";
    }

    return 0;
}
