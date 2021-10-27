#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#define MAX 100000
#define MAX_THREAD 4
using namespace std;

//merge
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 

    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  		// Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

//quick
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] <= pivot) 
        { 
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

//insertion
void insertionSort(int arr[], int n)  
{  
    int i, key, j;  
    for (i = 1; i < n; i++) 
    {  
        key = arr[i];  
        j = i - 1;  
        
        while (j >= 0 && arr[j] > key) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
}  


//driver
int main()
{
	fstream fout , fin;
	int *mArray = new int [MAX];    //merge array
    int *qArray = new int [MAX];    //quick array
    int *iArray = new int [MAX];	//insertion array
    int i, n;
    char order;
    clock_t t1, t2;
        cout << "Enter 1 for Merge Sort" << endl
	         << "Enter 2 for Quick Sort" << endl
	         << "Enter 3 for Insertion Sort:";
    
    cin >> n;
    system("CLS");
    switch(n)
    {
    	case 1:
    	{
    		fin.open("data.txt", ios::in);
            for(i=0; i<MAX; i++)
            {
                fin >> mArray[i];
            }
            fin.close();

            fout.open("Merge_Output.txt", ios::out | ios::app);
            t1 = clock();
            mergeSort(mArray, 0, MAX - 1); 
            t2 = clock();
            double t_time = (double)(t2-t1)/CLOCKS_PER_SEC;
            fout << "Sorted Array: " << endl;
            for(i=0; i<MAX; i++)
            {
                fout << mArray[i] << " ";
            }
            fout << endl;
            fout.precision(10);
            fout << "\t\tTime Elapsed: " << t_time << endl;
            fout.close();
            
			break;	
		}
		
		case 2:
		{
			fin.open("data.txt", ios::in);
            for(i=0; i<MAX; i++)
            {
                fin >> qArray[i];
            }
            fin.close();

            fout.open("Quick_Output.txt", ios::out | ios::app);
            t1 = clock();
            quickSort(qArray, 0, MAX-1);
            t2 = clock();
            double t_time = (double)(t2-t1)/CLOCKS_PER_SEC;
            fout << "Sorted Array: " << endl;
            for(i=0; i<MAX; i++)
            {
                fout << qArray[i] << " ";
            }
            fout << endl;
            fout.precision(10);
            fout << "\t\tTime Elapsed: " << t_time << endl;
            fout.close();
			break;
		}
		
		case 3:
		{
			fin.open("data.txt", ios::in);
            for(i=0; i<MAX; i++)
            {
                fin >> iArray[i];
            }
            fin.close();

            fout.open("Insertion_Output.txt", ios::out | ios::app);
            t1 = clock();
            insertionSort(iArray, MAX);  
            t2 = clock();
            double t_time = (double)(t2-t1)/CLOCKS_PER_SEC;
            fout << "Sorted Array: " << endl;
            for(i=0; i<MAX; i++)
            {
                fout << iArray[i] << " ";
            }
            fout << endl;
            fout.precision(10);
            fout << "\t\tTime Elapsed: " << t_time << endl;
            fout.close();
			break;
			
		}
		
		
		default:
		{
			cout << "Invalid Command Entered" << endl;
			break;
		}
	}
	
	cout << "Output saved in File. Do you want to try more algorithms? (y/n): ";
    cin >> order;
    if(order == 'y' || order == 'Y')
    {
        main();
    }
    else
    {
    	system("CLS");
    	cout << "Thanks, See You !!" << endl;
	}
	return 0;
}
