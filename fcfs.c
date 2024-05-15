#include<stdio.h> 

// Function to find the waiting time for all 
// processes 
void findWaitingTime(int n, int bt[], int wt[]) 
{ 
	// waiting time for first process is 0 
	wt[0] = 0; 

	// calculating waiting time 
	for (int i = 1; i < n ; i++ ) 
		wt[i] = bt[i-1] + wt[i-1] ; 
} 

// Function to calculate turn around time 
void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) 
{ 
	// calculating turnaround time by adding 
	// bt[i] + wt[i] 
	for (int i = 0; i < n ; i++) 
		tat[i] = bt[i] + wt[i]; 
} 

//Function to calculate average time 
void findavgTime(int n, int bt[]) 
{ 
	int wt[n], tat[n], total_wt = 0, total_tat = 0; 

	//Function to find waiting time of all processes 
	findWaitingTime(n, bt, wt); 

	//Function to find turn around time for all processes 
	findTurnAroundTime(n, bt, wt, tat); 

	//Display processes along with all details 
	printf("Processes Burst time Waiting time Turn around time\n"); 

	// Calculate total waiting time and total turn 
	// around time 
	for (int i=0; i<n; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		printf(" %d ",(i+1));
		printf("	 %d ", bt[i] );
		printf("	 %d",wt[i] );
		printf("	 %d\n",tat[i] ); 
	} 
	float s=(float)total_wt / (float)n;
	float t=(float)total_tat / (float)n;
	printf("Average waiting time = %f",s);
	printf("\n");
	printf("Average turn around time = %f ",t); 

	// Print Gantt Chart
	printf("\n\nGantt Chart:\n");
	printf(" ");
	for (int i = 0; i < n; i++) {
		printf("-------");
	}
	printf("\n|");
	for (int i = 0; i < n; i++) {
		printf("  P%d   |", i + 1);
	}
	printf("\n ");
	for (int i = 0; i < n; i++) {
		printf("-------");
	}
	printf("\n0");
	for (int i = 0; i < n; i++) {
		printf("      %d", tat[i]);
	}
	printf("\n");
} 

// Driver code 
int main() 
{ 
	int n;

	// Ask the user for the number of processes
	printf("Enter the number of processes: ");
	scanf("%d", &n);

	// Initialize arrays to store burst times
	int burst_time[n];

	// Ask the user for burst times of each process
	for (int i = 0; i < n; i++) {
		printf("Enter burst time for process %d: ", i+1);
		scanf("%d", &burst_time[i]);
	}

	// Calculate average waiting time and turn around time
	findavgTime(n, burst_time); 
	return 0; 
}

