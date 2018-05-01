/***********************************************************************************/
//And here is the outline of the SortingClass.cpp :
#include "SortingClass.hpp"
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

SortingClass::SortingClass(int size, int smallest, int largest) : size(size), smallest(smallest), largest(largest) {
    //(5 pts) random numbers should be between the smallest and largest numbers,
    //in-order should start at smallest
    //reverse order should start at largest
    //all should be of size size
    
    initArrays();
}

SortingClass::SortingClass(int size) : size(size), smallest(10), largest(5000) {
    //(2 pts) largest should be 5000, smallest should be 10

    initArrays();
}

SortingClass::SortingClass() : size(50000), smallest (0), largest(100) {
    // (2 pts)Start with a smaller size to make sure your sorting algorithms are working
    // and build up to 50000
    
    initArrays();
}

void SortingClass::initArrays()
{
    randArr = new int[size];
    inOrderArr = new int[size];
    revOrderArr = new int[size];
    //int dn = (largest - smallest) / size;
    for (int i = 0; i < size; i++)
    { 
        randArr[i] = smallest + rand() % (largest - smallest + 1);
        
        inOrderArr[i] = smallest + i;
                //smallest + i * dn;
        revOrderArr[i] = largest - i;
                //largest - i * dn;
    }
    
}

    // takes the word "random", "inorder", or "reverse order" as input,
    // and returns the address of a newly made copy of that array
    // because we don't want to mess with the original arrays for the other sorts

    //(7 pts) based on s (which can be “rev”, “ord”, or “rand”, creates a new array,
    // copies over the old array, and returns the address of the new array

int *SortingClass::copyArr(string s) {

    int *newArray = new int[size];
    int *srcArray = nullptr;
    
    if (s == "rand") {
        srcArray = randArr;
    } else if (s == "ord") {
        srcArray = inOrderArr;
    } else if (s == "rev") {
        srcArray = revOrderArr;
    }
    if (srcArray != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            newArray[i] = srcArray[i];
        }
    }
    return newArray;
}


void SortingClass::selectionSort(int arr[]) {
    // (4 pts) Does what you’d think to the array passed into the method.
    for (int i = 0; i < size - 1; i++) {
        int min_pos = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_pos]) {
                min_pos = j;
            }
        }
        int tmp = arr[min_pos];
        arr[min_pos] = arr[i];
        arr[i] = tmp;
    }
}

void SortingClass::bubbleSort(int arr[])
{
    int numSwaps;
    do
    {
        numSwaps = 0;
        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                numSwaps++;
            }
        }
    }
    while (numSwaps > 0);
}

void SortingClass::insertionSort(int arr[]) {
    // (4 pts) Does what you think to the array passed into the method.
    for (int i = 1; i < size; i++) {
        int x = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > x) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = x;
    }
}

void SortingClass::quickSort(int first, int last, int arr[]) {
    // (4 pts) first and last are the indices indicating
    // the current part of the array you're sorting
    if (first < last)
    {
        int p = partition(first, last, arr);
        quickSort(first, p, arr);
        quickSort(p + 1, last, arr);
    }
    
}

int SortingClass::partition(int first, int last, int arr[]) {
    //(7 pts)again, because you're only partitioning part of the array

    int pivot = arr[first];
    int up = first + 1,down = last;
    do {
        while (arr[up] <= pivot && up != last)
        {
            up++;
        }
        while (arr[down] >= pivot && down != first)
        {
            down--;
        }
        
        if (up < down) {
            int tmp = arr[up];
            arr[up] = arr[down];
            arr[down] = tmp;
        }
    }
    while (up < down);
    
    int tmp = arr[first];
    arr[first] = arr[down];
    arr[down] = tmp;
    
    return down;
    
}

void SortingClass::merge(int arr[], int first, int mid, int last) {
    // (7 pts)f is first index, m is middle index (end of first sorted array portion)
    // and l is the last index of the second array portion
    
    // in this case, you're creating a newly
    //merged list from 2 portions of the array that are already sorted, and then copying the
    //sorted portion back into the list. Thus you'll need to know the index of 
    //the beginning of the first sorted list, the index of the beginning of the second sorted list
    //(m), and the index of the last value in the second sorted list
    
    int *output = new int[last - first + 1];
    
    int curr1 = first;
    int curr2 = mid + 1;
    
    int i = 0;
    
    while (curr1 <= mid && curr2 <= last)
    {
        if (arr[curr1] < arr[curr2])
        {
            output[i] = arr[curr1];
            curr1++;
        }
        else
        {
            output[i] = arr[curr2];
            curr2++;
        }
        i++;
    }
    
    while (curr1 <= mid)
    {
        output[i] = arr[curr1];
        curr1++;
        i++; 
    }
    
    while (curr2 <= last)
    {
        output[i] = arr[curr2];
        curr2++;
        i++;
    }
    
    for (i = first; i <= last; i++)
    {
        arr[i] = output[i - first];
    }
    
    delete[]     output;
}

void SortingClass::mergeSort(int arr[], int low, int hi) {
    
    // (4 pts)keeps dividing the portion of the array between the low index and the hi
    // index by dividing by 2
    
    if (low < hi)
    {
        int mid = (low + hi) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, hi);
        merge(arr, low, mid, hi);
    }
}

void SortingClass::compareSorts() {
    clock_t startTime = clock();
    double timePassed;
    //SELECTION SORT
    int *arr = copyArr("rand");
    startTime = clock();
    selectionSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Selection: rand " << timePassed << endl;
    arr = copyArr("rev");
    startTime = clock();
    selectionSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Selection: rev " << timePassed << endl;
    arr = copyArr("ord");
    startTime = clock();
    selectionSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Selection: ord " << timePassed << endl;
    
    //BUBBLE
    arr = copyArr("rand");
    startTime = clock();
    bubbleSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "bubble: rand " << timePassed << endl;
    arr = copyArr("rev");
    startTime = clock();
    bubbleSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "bubble: rev " << timePassed << endl;
    arr = copyArr("ord");
    startTime = clock();
    bubbleSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "bubble: ord " << timePassed << endl;
    
    //INSERTION
    arr = copyArr("rand");
    startTime = clock();
    insertionSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    
    cout << endl;
    delete [] arr;
    cout << "Insertion: rand " << timePassed << endl;
    arr = copyArr("rev");
    startTime = clock();
    insertionSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Insertion: rev " << timePassed << endl;
    arr = copyArr("ord");
    startTime = clock();
    insertionSort(arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Insertion: ord " << timePassed << endl;
    //QUICKSORT
    arr = copyArr("rand");
    startTime = clock();
    quickSort(0, size - 1, arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Quick: rand " << timePassed << endl;
    arr = copyArr("rev");
    startTime = clock();
    quickSort(0, size - 1, arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Quick: rev " << timePassed << endl;
    arr = copyArr("ord");
    startTime = clock();
    quickSort(0, size - 1, arr);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Quick: ord " << timePassed << endl;
    //MERGE
    arr = copyArr("rand");
    startTime = clock();
    mergeSort(arr, 0, size - 1);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Merge: rand " << timePassed << endl;
    arr = copyArr("rev");
    startTime = clock();
    mergeSort(arr, 0, size - 1);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Merge: rev " << timePassed << endl;
    arr = copyArr("ord");
    startTime = clock();
    mergeSort(arr, 0, size - 1);
    timePassed = clock() - startTime;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    delete [] arr;
    cout << "Merge: ord " << timePassed << endl;
}