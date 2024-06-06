#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Counting sort function to sort individual buckets
void heapify(float arr[], int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(float b[], int n)
{
    for(int i = n/2-1; i>=0; i--)
    {
        //create max heap
        heapify(b, n, i);
    }
    for(int i = n-1; i>=0; i--)
    {
        //swap 1st node with last node
        swap(b[0],b[i]);
        heapify(b, i, 0);
    }
} 

void bucketSort(float arr[], int n) {
    vector<float> b[n];

    for (int i = 0; i < n; i++) {
        int bi = (n - 1) * arr[i];
        b[bi].push_back(arr[i]);
    }

    for (int i = 0; i < n; i++) {
        heapSort(&b[i][0], b[i].size());
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b[i].size(); j++) {
            arr[index++] = b[i][j];
        }
    }
}

int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Initial array: " << endl; 
    cout << "-------------" << endl; 
    for (int i = 0; i < n; i++) { 
        cout << arr[i] << " ";
    } 
    bucketSort(arr, n);
    cout << "Sorted array is \n";
    cout << "-------------" << endl; 
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}