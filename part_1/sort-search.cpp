#include <iostream>
#include <array>

using namespace std;

//to print binary search
void printArray(int *arr, int low, int mid, int high) {
    printf("low: %i, mid: %i, high: %i\n", arr[low], arr[mid], arr[high]);
    for (int i = low; i <= high; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void InsertionSortAsc(int arr[], int size) {
    int i;
    int j;
    int pointer;

    for (i = 1; i < size; i++) { //To initialize outer loop

        pointer = arr[i]; // Pointer will point at index i 
        j = i -1; // To allow J to have the value of the first element in the array

        while(j >=0 && arr[j] > pointer) { // Move elements of arr[0..i-1] that are more than the pointer, to use one position ahead of their current position
            arr[j + 1] = arr[j];
            j = j -1;
        }
        arr[j+1] = pointer;

        cout << "Sorting:" << endl;
        for (int f = 0; f < size; f++) {
            cout << arr[f] << ",";
        }

        cout << endl;
    }
}

void InsertionSortDesc(int arr[], int size) {
    int i;
    int j;
    int pointer;

    for (i = 1; i < size; i++) { //To initialize outer loop
        pointer = arr[i];
        j = i -1;
        while(j >=0 && arr[j] < pointer) { // Move elements of arr[0..i-1] that are less than the pointer, to use one position ahead of their current position
            arr[j + 1] = arr[j];
            j = j -1;
        }
        arr[j+1] = pointer;

        cout << "Sorting:" << endl;
        for (int d = 0; d < size; d++) {
            cout << arr[d] << ",";
        }

        cout << endl;
    }
}

int linear(int array[], int size, int searchValue) {
    int i; // pointer to compare value in array with search value
    for(i = 0; i < size; i++) {
        if(array[i] == searchValue) {
            return i;
        }
    } return -1;
}

int binarySearchAscending(int array[], int size, int searchValue) { // For Ascending
    int low = 0;
    int high = size -1;

    int mid;

    while (low <= high) { // To keep the loop running while searching the user input
        mid = (low + high)/2; // integer division will truncate to make it an integer

        printArray(array, low, mid, high);

        if(searchValue == array[mid]) { // comparing searchvalue with mid
            return mid;
        } else if (searchValue > array[mid]) { // statement if the searchvalue is greater than mid.
            low = mid + 1;
        } else { // statement if the searchValue is lesser than mid.   
            high = mid - 1;
        }
    }
    if (low <= high)
        printArray(array, low, mid, high);

    return -1;
} 

int binarySearchDescending(int array[], int size, int searchValue) { // For Descending
    int low = 0;
    int high = size -1;

    int mid;

    while (low <= high) { // To keep the loop running while searching the user input
        mid = (low + high)/2; // integer division will truncate to make it an integer

        printArray(array, low, mid, high);

        if(searchValue == array[mid]) { // comparing searchvalue with mid
            return mid;
        } else if (searchValue < array[mid]) { // statement if the searchvalue is greater than mid.
            low = mid + 1;
        } else { // statement if the searchValue is lesser than mid. 
            high = mid - 1;
        }
    }
    if (low <= high)
        printArray(array, low, mid, high);


    return -1;
} 

bool con = false;
string sortType = "";


int main(){
    int size;
    int input;
    cout << "Initializing the Array" << endl;
    cout << "......." << endl;
    cout << "Please enter the size of array:" << endl;
    cin >> size;
    int tester[size];
    cout << "Please Enter The Value You Wish To Put In The Array" << endl;

    for (int i = 0; i < size; i++) {
        cin >> tester[i];
    }
    for (int j = 0; j < size; j++) {
        cout << tester[j] << ",";
    } 
    cout << endl;

    start:

    cout << "Welcome To The Main Menu" << endl;
    cout << "Please type the number to indicate which option you would like to do:" << endl;
    cout << "1. Insertion Sort" << endl;
    cout << "2. Searching" << endl;
    cout << "0. Exit The Program" << endl;
    cin >> input;

    switch(input) {
        case 1:
            returning:
            int option;
            cout << "Please Select Which Method Of Sort To Do"<< endl;
            cout << "1. Insertion Sort Ascending" << endl;
            cout << "2. Insertion Sort Descending" << endl;
            cin >> option;
            if (option == 1) {
                InsertionSortAsc(tester, size);
                con = true;
                sortType = "Asc";
                int selection;
                cout << "Which Search Function Would you like to do?" << endl;
                cout << "1. Sequential Search" << endl;
                cout << "2. Binary Search" << endl;
                cin >> selection;

                if (selection == 1) {
                    int userValue;
                    cout << "Please Enter An Integer To Search" << endl; // User Input
                    cin >> userValue;
                    int result = linear(tester,size,userValue);
                    if (result >=0) {
                        cout << "The Number " <<  " " << tester[result]<<  " " << "Was Found at element no. " << result + 1 << endl;
                    } else {
                        cout <<  "The Number " << userValue <<"Was Not Found." << endl;
                    }
                    goto start;

                } else if(selection == 2) {
                    int userValue;

                    cout << "Please Enter An Integer To Search" << endl; // User Input
                    cin >> userValue;

                    int result = binarySearchAscending(tester,size,userValue); // To call binarySearch function

                    if (result >=0) {
                        cout << "The Number " <<  " " << tester[result] <<  " " << "Was Found at element no. " << result + 1 << endl;
                    } else {
                        cout <<  "The Number " << userValue <<"Was Not Found." << endl;
                    }
                    goto start;    

                } else {
                    cout << "The Number you have selected is not available in the menu" << endl;
                    cout << "Please retype the menu" << endl;
                    goto returning;
                }

            } else if(option == 2) {

                InsertionSortDesc(tester, size);
                con = true;
                sortType = "Desc";
                int selection;
                cout << "Which Search Function Would you like to do?" << endl;
                cout << "1. Sequential Search" << endl;
                cout << "2. Binary Search" << endl;
                cin >> selection;

                if (selection == 1) {
                    int userValue;
                    cout << "Please Enter An Integer To Search" << endl; // User Input
                    cin >> userValue;
                    int result = linear(tester,size,userValue);

                    if (result >=0) {
                        cout << "The Number " <<  " " << tester[result]<<  " " << "Was Found at element no. " << result + 1 << endl;
                    } else {
                        cout <<  "The Number " << userValue <<"Was Not Found." << endl;
                    }
                    goto start; 

                } else if(selection == 2) {
                    int userValue;

                    cout << "Please Enter An Integer To Search" << endl; // User Input
                    cin >> userValue;

                    int result = binarySearchDescending(tester,size,userValue); // To call binarySearch function

                    if (result >=0) {
                        cout << "The Number " <<  " " << tester[result]<<  " " << "Was Found at element no. " << result + 1 << endl;
                    } else {
                        cout <<  "The Number " << userValue <<"Was Not Found." << endl;
                    }
                    goto start;
                }

            } else {
                cout << "The option you have entered is not available." << endl;
                cout << "Please try again" << endl;
                cout << "......" << endl;
                cout << "returning to Insertion sort menu" << endl;
                goto returning;
            }
        case 2:
            goback:
            int menuselect;
            cout << "Please Select Which Search Method You Would Like To Do" << endl;
            cout << "1. Sequential Search" << endl;
            cout << "2. Binary Search" << endl;
            cin >> menuselect;

            if (menuselect == 1) {
                int userValue;
                cout << "Please Enter An Integer To Search" << endl; // User Input
                cin >> userValue;
                int result = linear(tester,size,userValue);
                if (result >=0) {
                    cout << "The Number " <<  " " << tester[result]<<  " " << "Was Found at element no. " << result + 1 << endl;
                } else {
                    cout <<  "The Number " << userValue <<"Was Not Found." << endl;
                }
                goto start;
            } else if (menuselect == 2) {
                if (con){
                    if (sortType == "Asc")
                    {
                        int userValue;

                        cout << "Please Enter An Integer To Search" << endl; // User Input
                        cin >> userValue;

                        int result = binarySearchAscending(tester,size,userValue); // To call binarySearch function

                        if (result >=0) {
                            cout << "The Number " <<  " " << tester[result] <<  " " << "Was Found at element no. " << result + 1 << endl;
                        } else {
                            cout <<  "The Number " << userValue <<"Was Not Found." << endl;
                        }
                        goto start;
                    }
                    else {
                        int userValue;

                        cout << "Please Enter An Integer To Search" << endl; // User Input
                        cin >> userValue;

                        int result = binarySearchDescending(tester,size,userValue); // To call binarySearch function

                        if (result >=0) {
                            cout << "The Number " <<  " " << tester[result]<<  " " << "Was Found at element no. " << result + 1 << endl;
                        } else {
                            cout <<  "The Number " << userValue <<"Was Not Found." << endl;
                        }
                        goto start;
                    }
                    
                }
                cout << "Sorry binary Search is not available in an unsorted list" << endl;
                cout << "Please Return to the menu and sort the array first" << endl;
                cout << "..........." << endl;
                cout << "Returning To Main Menu" << endl;
                goto start;
            } else {
                cout << "The Number you have entered is not in the menu" << endl;
                cout << "Please Try Again" << endl;
                goto goback;
            }

        case 0:
            cout << "Thank You For Using This Program" << endl;
            cout << "Hope to see you soon :)" << endl;
    }
}