#include <bits/stdc++.h>

using namespace std;

/*
	This function takes last element as pivot, places the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right
	of pivot
*/
int partition (Process process[], int low, int high)
{
	int pivot = process[high].priority;
	// Index of smaller element
	int i = (low - 1);

	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (process[j].priority <= pivot)
		{
			// increment index of smaller element
			i++;
			swap(process[i].priority, process[j].priority);
			swap(process[i].pid, process[j].pid);
			swap(process[i].burst_time, process[j].burst_time);
			swap(process[i].arrival_time, process[j].arrival_time);
			swap(process[i].elapsed_time, process[j].elapsed_time);
			swap(process[i].wait_time, process[j].wait_time);

		}
	}
	swap(process[i + 1].priority, process[high].priority);
	swap(process[i+1].pid, process[high].pid);
	swap(process[i+1].burst_time, process[high].burst_time);
	swap(process[i+1].arrival_time, process[high].arrival_time);
	swap(process[i+1].elapsed_time, process[high].elapsed_time);
	swap(process[i+1].wait_time, process[high].wait_time);
	return (i + 1);
}

/*
	The main function that implements QuickSort
	arr[] --> Array to be sorted,
	low  --> Starting index,
	high  --> Ending index
*/
void quickSort(Process process[], int low, int high)
{
	if (low < high)
	{
		/*
			pi is partitioning index, arr[p] is now
			at right place
		*/
		int pi = partition(process, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(process, low, pi - 1);
		quickSort(process, pi + 1, high);
	}
}
// A function to calculate original arrival time
void original_arrival_time(Process process[], int n)
{
   int temp = 0;
   for(int i = 0; i < n; i++)
   {
		temp+=process[i].arrival_time;
		process[i].arrival_time=temp;
   }
}

void findWaitingTime(Process process[], int n, double waiting_time[])
{
	original_arrival_time(process,n);
	quickSort(process, 0, n - 1);
	//remaining time of processes
	int remaining_time[n];

	// Copy the burst time into remaining_time[]
	for (int i = 0; i < n; i++)
		remaining_time[i] = process[i].burst_time;

	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	bool check = false;

	// Process until all processes gets completed
	while (complete != n)
	{
		// Find process with minimum remaining time among the processes that arrives till the current time
		for (int j = 0; j < n; j++)
		{
			if ((process[j].arrival_time <= t) && (remaining_time[j] < minm) && remaining_time[j] > 0)
			{
				minm = remaining_time[j];
				shortest = j;
				check = true;
			}
		}

		if (check == false)
		{
			t++;
			continue;
		}

		// Reduce remaining time by one
		remaining_time[shortest]--;

		// Update minimum
		minm = remaining_time[shortest];
		if (minm == 0)
			minm = INT_MAX;

		// If a process gets completely executed
		if (remaining_time[shortest] == 0)
		{

			// Increment complete
			complete++;

			// Find finish time of current process
			finish_time = t + 1;

			// Calculate waiting time
			waiting_time[shortest] = finish_time -
						process[shortest].burst_time -
						process[shortest].arrival_time;

			if (waiting_time[shortest] < 0)
				waiting_time[shortest] = 0;
		}
		// Increment time
		t++;
	}
}

double calculateSD(double turn_around_time[] , int n)
{
	double sum = 0.0 , mean , standardDeviation = 0.0;
	int i=0;
	for(i=0;i<n;i++)
	{
		sum += turn_around_time[i];
	}
	mean  = sum/n;
	 for(i=0;i<n;i++)
	 {
		standardDeviation += pow(turn_around_time[i]-mean , 2);
	}
	return sqrt(standardDeviation/n);
}

// Function to calculate turn around time
void findTurnAroundTime(Process process[], int n, double waiting_time[], double turn_around_time[])
{
	// calculating turnaround time by adding burst_time[i] + waiting_time[i]
	for (int i = 0; i < n; i++)
		turn_around_time[i] = process[i].burst_time + waiting_time[i];
}

// Function to calculate average time
void findCompletionTime(Process process[], int n, double turn_around_time[], double completion_time[])
{
	for(int i=0;i<n;i++)
	{
		completion_time[i]=turn_around_time[i]+process[i].arrival_time;
	}
}
void findavgTime(Process process[], int n)
{
	double waiting_time[n], turn_around_time[n],completion_time[n], total_waiting_time = 0,
					total_turn_around_time=0,total_completion_time = 0;

	// Function to find waiting time of all processes
	findWaitingTime(process, n, waiting_time);

	// Function to find turn around time for all processes
	findTurnAroundTime(process, n, waiting_time, turn_around_time);

	//function t find Completion time for all processes
	findCompletionTime(process,n,turn_around_time,completion_time);
	// Display processes along with all details

	cout << "Priority    "
		 << "Processes    "
		<< " Arrival time "
		<< "  Burst time  "
		<< "   Waiting time  "
		<< "   Turn around time\n";

	// Calculate total waiting time and
	// total turnaround time
	for (int i = 0; i < n; i++)
	{
		total_waiting_time = total_waiting_time + waiting_time[i];
		total_turn_around_time = total_turn_around_time + turn_around_time[i];
		total_completion_time+=completion_time[i];
		cout << " " << process[i].priority << "\t\t" << process[i].pid << "\t\t" << process[i].arrival_time << "\t\t"
			<< process[i].burst_time << "\t\t " << waiting_time[i]
			<< "\t\t " << turn_around_time[i] << endl;
	}

	cout << "\nAverage waiting time = "
		<< (float)total_waiting_time / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_turn_around_time / (float)n;
	cout << "\nAverage Completion time = "
		<< (float)total_completion_time / (float)n;
	cout << "\nStandard_Deviation = "
		<< (float)calculateSD(turn_around_time,n);
}
