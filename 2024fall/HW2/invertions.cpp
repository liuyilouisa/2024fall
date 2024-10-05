#include <iostream>
#include <vector>

using namespace std;

unsigned long long int merge(vector<int> &arr, int l, int m, int r)
{
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    unsigned long long int inversions = 0;

    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
            inversions += left.size() - i;
        }
    }

    while (i < left.size())
    {
        arr[k++] = left[i++];
    }

    while (j < right.size())
    {
        arr[k++] = right[j++];
    }

    return inversions;
}

unsigned long long int mergeSort(vector<int> &arr, int l, int r)
{
    unsigned long long int inversions = 0;
    if (l < r)
    {
        int m = l + (r - l) / 2;
        inversions += mergeSort(arr, l, m);
        inversions += mergeSort(arr, m + 1, r);
        inversions += merge(arr, l, m, r);
    }
    return inversions;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    unsigned long long int inversions = mergeSort(arr, 0, arr.size() - 1);
    cout << inversions << endl;
    return 0;
}
