#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void FCFS(){
    FILE *input, *output;
    int pid[100], at[100], bt[100], ct[100], tat[100], wt[100];
    int n, i, j;

    input = fopen("input_FCFS.txt", "r");
    output = fopen("output_FCFS.txt", "w");

    fscanf(input, "%d", &n); //scan number of process
    for (i = 0; i < n; i++) {
        fscanf(input, "%d%d%d", &pid[i], &at[i], &bt[i]); //scan process_id, arrival_time and burst_time
    }

    // FCFS Algorithm
    int time = 0;
    int start[100] = {0};
    printf("Gantt Chart\n-----------\n");
    fprintf(output, "Gantt Chart\n-----------\n");
    for (i = 0; i < n; i++) {
        if (time < at[i]) {
            time = at[i];
        }

        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        time = ct[i];

        // Print the Gantt Chart
        printf("| P%d ", pid[i]);
        if (i == n - 1) {
            printf("|\n");
        }
        fprintf(output, "|P%d|", pid[i]);
    }


    fprintf(output, "\n\nProcess\tArrival_Time\tBurst_Time\tCompletion_Time\tTurnaround_Time\tWait_Time\n");
    for (i = 0; i < n; i++) {
        fprintf(output, "%d\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    fprintf(output, "Average waiting time = %f\n", total_wt / n);
    fprintf(output, "Average turnaround time = %f\n", total_tat / n);

    fclose(input);
    fclose(output);
}

void SJF(){
    FILE * input_file;

    input_file = fopen("input_SJF.txt", "r");

    fseek(input_file, 21, SEEK_CUR);

	int A[100][4];
	int i, j, n, total = 0, index, temp;
	float avg_wt, avg_tat;
	
    fscanf(input_file, "%d", &n);


	fseek(input_file, 14, SEEK_CUR);
	
	for (i = 0; i < n; i++) {
		fscanf(input_file, "%d", &A[i][1]);
		fseek(input_file, 1, SEEK_CUR);
		A[i][0] = i + 1;
	}

	fclose(input_file);

	FILE * output_file;

	output_file = fopen("output_SJF.txt", "w");
	
	// Sorting process according to their Burst Time.
	for (i = 0; i < n; i++) {
		index = i;
		for (j = i + 1; j < n; j++)
			if (A[j][1] < A[index][1])
				index = j;
		temp = A[i][1];
		A[i][1] = A[index][1];
		A[index][1] = temp;

		temp = A[i][0];
		A[i][0] = A[index][0];
		A[index][0] = temp;
	}
	A[0][2] = 0;
	// Calculation of Waiting Times
	for (i = 1; i < n; i++) {
		A[i][2] = 0;
		for (j = 0; j < i; j++)
			A[i][2] += A[j][1];
		total += A[i][2];
	}
	avg_wt = (float)total / n;
	total = 0;
	fputs("P	 BT	 WT	 TAT\n", output_file);
	// Calculation of Turn Around Time and printing the
	// data.
	for (i = 0; i < n; i++) {
		A[i][3] = A[i][1] + A[i][2];
		total += A[i][3];
		fprintf(output_file,"P%d	 %d	 %d	 %d\n", A[i][0],
			A[i][1], A[i][2], A[i][3]);
	}
	avg_tat = (float)total / n;
	fprintf(output_file, "\nAverage Waiting Time = %f", avg_wt);	
	fprintf(output_file, "\nAverage Turnaround Time = %f", avg_tat);

    fprintf(output_file, "\n\nGantt Chart:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < A[i][1]; j++){
            fprintf(output_file, "P%d | ", A[i][0]);
        }
    }
	fclose(input_file);
	fclose(output_file);
}

void RR(){
    FILE *input, *output;
    int pid[100], at[100], bt[100], ct[100], tat[100], wt[100];
    int n, i, j, quantum;

    input = fopen("input_RR.txt", "r");
    output = fopen("output_RR.txt", "w");

    fscanf(input, "%d", &n); //scan number of process
    for (i = 0; i < n; i++) {
        fscanf(input, "%d%d%d", &pid[i], &at[i], &bt[i]); //scan process_id, arrival_time and burst_time
    }
    fscanf(input, "%d", &quantum); //scan time quantum

    // RR Algorithm
    int rt[100];
    for (i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    int flag = 0;
    int time = 0;
    printf("Gantt Chart\n-----------\n");
    fprintf(output, "Gantt Chart\n-----------\n");
    while (1) {
        flag = 0;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                flag = 1;
                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                }
                else {
                    time += rt[i];
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    rt[i] = 0;

                    // Print the Gantt Chart
                    printf("| P%d ", pid[i]);
                    if (i == n - 1) {
                        printf("|\n");
                    }
                    fprintf(output, "|P%d|", pid[i]);
                }
            }
        }
        if (flag == 0) {
            break;
        }
    }
    fprintf(output, "\n\nProcess\tArrival_Time\tBurst_Time\tCompletion_Time\tTurnaround_Time\tWaiting_Time\n");
    for (i = 0; i < n; i++) {
        fprintf(output, "%d\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    fprintf(output, "Average waiting time = %f\n", total_wt / n);
    fprintf(output, "Average turnaround time = %f\n", total_tat / n);

    fclose(input);
    fclose(output);
}

void SRTF(){
    FILE *input, *output;
    int pid[100], at[100], bt[100], rt[100], ct[100], tat[100], wt[100];
    int n, time, smallest, i, j, total_wt = 0, total_tat = 0;

    input = fopen("input_SRTF.txt", "r");
    output = fopen("output_SRTF.txt", "w");

    fscanf(input, "%d", &n); //scan number of process
    for (i = 0; i < n; i++) {
        fscanf(input, "%d%d%d", &pid[i], &at[i], &bt[i]); //scan process_id, arrival_time and burst_time
        rt[i] = bt[i];
    }

    // SRTF Algorithm
    int complete = 0, min_bt = 1000, index = 0;
    int start[100] = {0};
    printf("Gantt Chart\n-----------\n");
    fprintf(output, "Gantt Chart\n-----------\n");
    for (time = 0; complete != n; time++) {
        min_bt = 1000;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] < min_bt && rt[i] > 0) {
                min_bt = rt[i];
                index = i;
            }
        }
        rt[index]--;
        if (rt[index] == 0) {
            complete++;
            ct[index] = time + 1;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
            total_wt += wt[index];
            total_tat += tat[index];
        }

        if (index != j) {
            start[index] = time;
            printf("| P%d ", index);
            fprintf(output, "| P%d ", index);
            j = index;
        } else if (rt[index] == 0) {
            printf("|     ");
            fprintf(output, "|     ");
        }
    }
    printf("|\n");

    fprintf(output, "\n\nProcess\tArrival_Time\tBurst_Time\tCompletion_Time\tTurnaround_Time\tWaiting_Time\n");
    for (i = 0; i < n; i++) {
        fprintf(output, "%d\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    fprintf(output, "Average waiting time = %f\n", (float)total_wt / n);
    fprintf(output, "Average turnaround time = %f\n", (float)total_tat / n);

    fclose(input);
    fclose(output);
}

void Priority_Scheduling(){
    int n, pid[100], bt[100], prior[100];
    int at[100], ct[100], tat[100], wt[100], remaining_bt[100];
    int time = 0, min_prior = 999, min_prior_index = -1, completed = 0;
    int total_tat = 0, total_wt = 0;

    FILE *input = fopen("input_priority_pre.txt", "r");
    FILE *output = fopen("output_prior_pre.txt", "w");

    fscanf(input, "%d", &n); // scan number of processes
    for (int i = 0; i < n; i++)
    {
        fscanf(input, "%d %d %d", &pid[i], &bt[i], &prior[i]); // scan pid, burst time and priority
        at[i] = 0;
        ct[i] = 0;
        tat[i] = 0;
        wt[i] = 0;
        remaining_bt[i] = bt[i];
    }

    fprintf(output, "Gantt Chart:\n");
    fprintf(output, "| ");
    while (completed < n)
    {
        min_prior = 9999;
        min_prior_index = -1;

        for (int i = 0; i < n; i++)
        {
            if (remaining_bt[i] > 0 && prior[i] < min_prior && at[i] <= time)
            {
                min_prior = prior[i];
                min_prior_index = i;
            }
        }

        if (min_prior_index == -1)
        {
            fprintf(output, " | ");
            time++;
            continue;
        }

        remaining_bt[min_prior_index]--;

        if (remaining_bt[min_prior_index] == 0)
        {
            ct[min_prior_index] = time + 1;
            tat[min_prior_index] = ct[min_prior_index] - at[min_prior_index];
            wt[min_prior_index] = tat[min_prior_index] - bt[min_prior_index];
            completed++;
        }

        fprintf(output, "%d | ", pid[min_prior_index]);

        time++;
    }
    fprintf(output, "\n\n");

    fprintf(output, "Process_ID\tArrival_Time\tBurst_Time\tPriority\tCompleted_Time\tTurnaround_Time\tWaiting_Time\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(output, "%d\t\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t\t%d\n", pid[i], at[i], bt[i], prior[i], ct[i], tat[i], wt[i]);
    }

    for (int i = 0; i < n; i++)
    {
        total_tat += tat[i];
        total_wt += wt[i];
    }
    float avg_tat = (float)total_tat / n;
    float avg_wt = (float)total_wt / n;

    fprintf(output, "\nTotal Turnaround Time: %d\n", total_tat);
    fprintf(output, "Total Waiting Time: %d\n", total_wt);
    fprintf(output, "Average Turnaround Time: %.2f\n", avg_tat);
    fprintf(output, "Average Waiting Time: %.2f\n", avg_wt);

    fclose(input);
    fclose(output);
}

void LRTF(){
    struct Process
{
    int Process_ID;
    int Burst_Time;
    int WaitingTime;
    int TurnAroundTime;
};
    FILE * input_file;

    input_file = fopen("input_LRTF.txt", "r");

    fseek(input_file, 21, SEEK_CUR);

    struct Process data[20];
    int n;
    fscanf(input_file, "%d", &n);

    fseek(input_file, 14, SEEK_CUR);

    for (int i = 0; i < n; i++)
    {
        fscanf(input_file, "%d", &data[i].Burst_Time);
        fseek(input_file, 1, SEEK_CUR);
    }

    fseek(input_file, 13, SEEK_CUR);

    for (int i = 0; i < n; i++)
    {
        fscanf(input_file, "%d", &data[i].Process_ID);
        fseek(input_file, 1, SEEK_CUR);
    }
    
    struct Process temp;

    FILE * output_file;

    output_file = fopen("output_LRTF.txt", "w");

    
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < (n - 1-i); j++)
        {
            if (data[j].Burst_Time < data[j + 1].Burst_Time)
            {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            } 
            else if(data[j].Burst_Time == data[j + 1].Burst_Time)
            {
            	if(data[j].Process_ID > data[j + 1].Process_ID)
            	{
            	temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                }
			}
        }
    }

    data[0].WaitingTime=0;

    for(int j=1; j<n; j++)
    {
        data[j].WaitingTime = data[j-1].WaitingTime + data[j-1].Burst_Time;
    }
    
    
    for(int j=0; j<n; j++)
    {
        data[j].TurnAroundTime=data[j].WaitingTime+data[j].Burst_Time;
    }
    
    int i,AvgWaitingTime=0,AvgTurnAroundTime=0;
	int TotalWatingTime=0,TotalTurnAroundTime=0;
    fprintf(output_file, "Student id\tBurst Time\tWaitingTime\tTurnAroundTime"); 
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "\n%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t", data[i].Process_ID, data[i].Burst_Time,data[i].WaitingTime,data[i].TurnAroundTime);
		TotalWatingTime= TotalWatingTime+data[i].WaitingTime;
		TotalTurnAroundTime= TotalTurnAroundTime+data[i].TurnAroundTime;
	}

	fprintf(output_file, "\n\nAverage Waiting Time is: = %d",TotalWatingTime);
	fprintf(output_file, "\nAverage Turn around Time is: = %d\n\n",TotalTurnAroundTime);

    fprintf(output_file, "Gantt Chart:\n");
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<data[i].Burst_Time; j++)
        {
            fprintf(output_file, "P%d | ", data[i].Process_ID);
        }    
    }
}

int main(){
    int key;
    printf("Which algorithm would you like to use?\n\n");
    printf("1.)FCFS\n2.)SJF\n3.)RR\n4.)SRTF\n5.)Priority Scheduling\n6.)LRTF\n\nEnter: ");
    scanf("%d", &key);
    switch (key)
    {
    case 1:
        FCFS();
        break;
    case 2:
        SJF();
        break;
    case 3:
        RR();
        break;
    case 4:
        SRTF();
        break;
    case 5:
        Priority_Scheduling();
        break;
    case 6:
        LRTF();
        break;
    default:
        break;
    }
    return 0;
}