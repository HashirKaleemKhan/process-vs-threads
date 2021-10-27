#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<omp.h>
#include<fstream>
#define MAX 100000
#define MAX_THREAD 4
using namespace std;

// merge
void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    int L[n1], R[n2];	// temp arrays for partition in two halves
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 	// initial indexes
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
 
    // copy remaining items of left array
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // copy remaining items of right array
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
 		// Sort first and second halves
        #pragma omp parallel sections num_threads(2) // Two threads are used here
	    {
                #pragma omp section 
                    mergeSort(arr, l, m);
                #pragma omp section
                    mergeSort(arr, m+1, r);
 	    }
        merge(arr, l, m, r);
    }
}

// quick
int partition (int arr[], int low, int high)
{
    int i,j,pivot = arr[high],temp;    // pivot
    i = low - 1;  // Index of smaller element
 
    for(j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot)
        {
            i++;
		    temp = arr[i];
		    arr[i] = arr[j];
		    arr[j] = temp;
        }
    }
    // swap part
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
   
    return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
	    #pragma omp parallel sections num_threads(2)
	    {
		    #pragma omp section 
        	    quickSort(arr, low, pi - 1);
		    #pragma omp section
            	quickSort(arr, pi + 1, high);
	    }
    }
}


// insertion
void insertionSort(int *A, int num)
{
	int k;
	#pragma omp parallel for shared(A) private(k)
	for(int n = 1; n < num; n++)
	{
	    int key = A[n];
	    k = n;
	#pragma omp critical
	
	    for(;k>0 && A[k-1]> key;k--)
	    {
	        A[k] = A[k-1];   
	    }
		A[k] = key;  
	}
}

// driver 
int main()
{
    fstream fin, fout;
    int *mArray = new int [MAX];    //merge array
    int *qArray = new int [MAX];    //quick array
    int *iArray = new int [MAX];	//insertion array
    int i, n;
    char order;
    clock_t t1, t2;
    pthread_t threads[MAX_THREAD]; 

    cout << "Enter 1 for Merge Sort" << endl
         << "Enter 2 for Quick Sort" << endl
         << "Enter 3 for Insertion Sort :";
    
    cin >> n;
    system("CLS");
    switch (n)
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
            fout << "Sorted Array: " <<endl;
            for(i=0; i<MAX; i++)
            {
                fout << qArray[i] << " ";
            }
            fout << endl;
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
            cout << "Invalid command entered" << endl;
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
