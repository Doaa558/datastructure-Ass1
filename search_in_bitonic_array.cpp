#include<iostream>
#include<algorithm>
using namespace std;
class SortingArray {
private:
    int size;
    static const int  Max_Size = 100;
    int data[Max_Size];
public:
    //constructor
    SortingArray(int arr[], int n) {
        size = n;
        for (int i = 0;i < size;i++) {
            data[i] = arr[i];
        }
    }
    // linear search
    void linearSearch(int target) {
        bool found = false;
        int nfound = 0;
        int middle = size / 2;
        for (int i = 0;i < size;i++) {
            if (data[i] == target) {
                if (nfound == 0) {
                    nfound += 1;
                    found = true;
                    if (i > middle) {
                        cout << target << " is found on Right half on position" << " " << i + 1 << endl;
                    }
                    else if (i < middle) {
                        cout << target << " is found on Left half on position" << " " << i + 1 << endl;
                    }
                    else if (i == middle) {
                        cout << target << " is The bitonic point on position" << " " << i + 1 << endl;
                    }
                }
                    else {
                        cout << target << " is duplicated, it also found on position" << " " << i + 1 << endl;
                    }
                

            }
        }
               if (!found) {
                    cout << target << " is not found" << endl;
                }
            
        
    }
    // bubblesort
    void BubbleSort(int L1, int R, int& compare1, int& swaps1) {
        for (int i = L1;i < R;i++) {
            for (int j = R - 1;j > i;--j) {
                compare1 += 1;
                if (data[j] < data[j - 1]) {
                    swap(data[j], data[j - 1]);
                    swaps1 += 1;
                }
            }
        }
    }
    //selectionsort
    void SelectionSort(int L2, int R, int& compare2, int& swaps2) {
        for (int i = L2, j, least;i < R - 1;i++) {
            least = i;
            for (j = i + 1;j < R;j++) {
                compare2 += 1;
                if (data[j] > data[least])
                    least = j;
            }
            if (least != i) {
                swap(data[i], data[least]);
                swaps2 += 1;
            }
        }
    }
    // the sortingalgorithm
    void sorting() {
        int mid = size / 2;
        int compare1 = 0, compare2 = 0;
        int swaps1 = 0, swaps2 = 0;
        BubbleSort(0, mid, compare1, swaps1);
        SelectionSort(mid, size, compare2, swaps2);
        cout << "Total comparisons = " << compare1 + compare2 << " where " << "Bubble_compare = " << compare1 << " and " << " Selection_compare = " << compare2 << endl;
        cout << "Total swaps = " << swaps1 + swaps2 << " where " << " Bubble_swaps = " << swaps1 << " and " << " Selection_swaps = " << swaps2 << endl;
    }
    //print
    void print() {
        cout << "----The sorted array------ ";
        for (int i = 0;i < size;i++)
            cout << data[i] << " ";
    }
    
    
};
int main() {
    cout << "------------------------ Search in bitonic array -----------------------------------" << endl;
     int n,t;
    cout << "Enter the size of the array: ";
        cin >> n;
        int* arr = new int[n];
        cout << "Enter the Array: ";
        // read data
        for (int i = 0;i < n;i++) {
            cin >> arr[i];
        }
    SortingArray a = SortingArray(arr, n);
    a.sorting();
    a.print();
    cout << endl;
       cout << " -----------Enter -999 to stop search to targets---------- "<<endl;
        cout << " Enter the Target Number: ";
        cin >> t;
        while (t != -999) {
            a.linearSearch(t);
            cout << "-----------Enter -999 to stop search to targets---------- "<<endl;
            cout << " Enter the Target Number: ";
            cin >> t;
        }
        if (t == -999) {
            cout << "         ---Thanks for using the app---      ";
        }
        delete[] arr;
    
}
