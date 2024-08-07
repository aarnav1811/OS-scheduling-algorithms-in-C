# OS Scheduling Algorithms in C

This project implements various Operating System (OS) scheduling algorithms in C. It takes a matrix as input, where each row represents a process and the columns contain the arrival time, execution time, and service time of the processes. The program outputs the scheduling order, Gantt chart, turnaround time, and waiting time for each algorithm.

## Table of Contents

1. [Introduction](#introduction)
2. [Input Format](#input-format)
3. [Output Format](#output-format)
4. [Implemented Algorithms](#implemented-algorithms)

## Introduction

This project demonstrates the implementation of various OS scheduling algorithms. These algorithms are fundamental in the management of processes in an operating system. The implemented algorithms include:

- First-Come, First-Served (FCFS)
- Longest Remaining Time First (LRTF)
- Round Robin (RR)
- Shortest Remaining Time First (SRTF)
- Shortest Job First (SJF)
- Priority Scheduling (Preemptive)

## Input Format

The input to the program is a matrix where each row corresponds to a process. The columns are:

1. **Arrival Time**: The time at which the process arrives in the ready queue.
2. **Execution Time**: The total time required by the process to execute.
3. **Service Time**: The priority or service time for the process (if applicable).

The input matrix should be provided in a file with each line representing a process, and values separated by spaces or tabs.

## Output Format

The program outputs the scheduling order, Gantt chart, and relevant metrics such as:

- Turnaround Time
- Waiting Time

These metrics help in evaluating the performance of each scheduling algorithm.

## Implemented Algorithms

### 1. First-Come, First-Served (FCFS)

Processes are scheduled in the order they arrive in the ready queue.

### 2. Longest Remaining Time First (LRTF)

Processes with the longest remaining execution time are scheduled next.

### 3. Round Robin (RR)

Processes are scheduled in a cyclic manner, each getting a fixed time slice.

### 4. Shortest Remaining Time First (SRTF)

Processes with the shortest remaining execution time are scheduled next.

### 5. Shortest Job First (SJF)

Processes with the shortest execution time are scheduled next. This can be either preemptive or non-preemptive.

### 6. Priority Scheduling (Preemptive)

Processes are scheduled based on their service time (priority). Lower service time means higher priority.
