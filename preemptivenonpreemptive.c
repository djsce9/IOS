#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Process {
int pid, arrival, burst, priority;
int completion, turnaround, waiting, response, start, remaining;
int is_completed;
};
void sortByArrival(struct Process p[], int n) {
struct Process temp;
for (int i=0; i<n-1; i++) {
for (int j=0; j<n-i-1; j++) {
if (p[j].arrival > p[j+1].arrival) {
temp = p[j];
p[j] = p[j+1];
p[j+1] = temp;
}
}
}
}
void printTable(struct Process p[], int n) {
printf("\nProcess\tPri\tAT\tBT\tCT\tTAT\tWT\tRT\n");
for (int i = 0; i < n; i++) {
printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
p[i].pid, p[i].priority, p[i].arrival, p[i].burst, 
p[i].completion,
p[i].turnaround, p[i].waiting, p[i].response);
}
}
void nonPreemptivePriority(struct Process p[], int n) {
sortByArrival(p, n);
int time = 0, completed = 0;
printf("\nGantt Chart:\n|");
while (completed != n) {
int idx = -1;
int highest = INT_MIN;
for (int i = 0; i < n; i++) {
if (p[i].arrival <= time && p[i].is_completed == 0) {
if (p[i].priority > highest) {
highest = p[i].priority;
idx = i;
} else if (p[i].priority == highest) {
if (p[i].arrival < p[idx].arrival)
idx = i;
}
}
}
if (idx != -1) {
p[idx].start = time;
p[idx].completion = time + p[idx].burst;
p[idx].turnaround = p[idx].completion - p[idx].arrival;
p[idx].waiting = p[idx].turnaround - p[idx].burst;
p[idx].response = p[idx].start - p[idx].arrival;
p[idx].is_completed = 1;
completed++;
time = p[idx].completion;
printf(" P%d |", p[idx].pid);
} else {
time++;
}
}
printTable(p, n);
}
void preemptivePriority(struct Process p[], int n) {
sortByArrival(p, n);
int time = 0, completed = 0, prev = -1;
printf("\nGantt Chart:\n|");
while (completed != n) {
int idx = -1;
int highest = INT_MIN;
for (int i = 0; i < n; i++) {
if (p[i].arrival <= time && p[i].is_completed == 0) {
if (p[i].priority > highest) {
highest = p[i].priority;
idx = i;
} else if (p[i].priority == highest) {
if (p[i].arrival < p[idx].arrival)
idx = i;
}
}
}
if (idx != -1) {
if (p[idx].remaining == p[idx].burst)
p[idx].start = time;
p[idx].remaining--;
if (prev != idx)
printf(" P%d |", p[idx].pid);
prev = idx;
time++;
if (p[idx].remaining == 0) {
p[idx].completion = time;
p[idx].turnaround = p[idx].completion - p[idx].arrival;
p[idx].waiting = p[idx].turnaround - p[idx].burst;
p[idx].response = p[idx].start - p[idx].arrival;
p[idx].is_completed = 1;
completed++;
}
} else {
time++;
}
}
printTable(p, n);
}
int main() {
int n, choice;
struct Process *p;
do {
printf("\n\n--- CPU Scheduling Algorithms ---\n");
printf("1. Non-Preemptive Priority Scheduling (Higher number = higher priority)\n");
printf("2. Preemptive Priority Scheduling (Higher number = higher priority)\n");
printf("3. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
if (choice == 1 || choice == 2) {
printf("Enter number of processes: ");
scanf("%d", &n);
p = (struct Process*)malloc(n * sizeof(struct Process));
for (int i = 0; i < n; i++) {
p[i].pid = i + 1;
printf("Process P%d:\n", i + 1);
printf("Arrival Time: ");
scanf("%d", &p[i].arrival);
printf("Burst Time: ");
scanf("%d", &p[i].burst);
printf("Priority (higher number = higher priority): ");
scanf("%d", &p[i].priority);
p[i].remaining = p[i].burst;
p[i].is_completed = 0;
}
if (choice == 1) {
nonPreemptivePriority(p, n);
} else {
preemptivePriority(p, n);
}
free(p);
}
} while (choice != 3);
printf("Exiting...\n");
return 0;
}
