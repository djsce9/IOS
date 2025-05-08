#include <stdio.h>
void inputBlocks(int blockSize[], int blockAllocated[], int blockData[], int
*numBlocks) {
printf("Enter number of memory blocks: ");
scanf("%d", numBlocks);
printf("Enter sizes of memory blocks:\n");
for(int i = 0; i < *numBlocks; i++) {
scanf("%d", &blockSize[i]);
blockAllocated[i] = 0;
blockData[i] = -1;
}
}
void inputProcesses(int processSize[], int processAllocated[], int
*numProcesses) {
printf("Enter number of processes: ");
scanf("%d", numProcesses);
printf("Enter memory required for each process:\n");
for(int i = 0; i < *numProcesses; i++) {
scanf("%d", &processSize[i]);
processAllocated[i] = -1;
}
}
void resetAllocation(int blockAllocated[], int blockData[], int
processAllocated[], int numBlocks, int numProcesses) {
for(int i = 0; i < numBlocks; i++) {
blockAllocated[i] = 0;
blockData[i] = -1;
}
for(int i = 0; i < numProcesses; i++) {
processAllocated[i] = -1;
}
}
void firstFit(int blockSize[], int blockAllocated[], int blockData[],
int processSize[], int processAllocated[],
int numBlocks, int numProcesses) {
for(int i = 0; i < numProcesses; i++) {
for(int j = 0; j < numBlocks; j++) {
if(!blockAllocated[j] && blockSize[j] >= processSize[i]) {
processAllocated[i] = j;
blockAllocated[j] = 1;
blockData[j] = processSize[i];
break;
}
}
}
}
void bestFit(int blockSize[], int blockAllocated[], int blockData[],
int processSize[], int processAllocated[],
int numBlocks, int numProcesses) {
for(int i = 0; i < numProcesses; i++) {
int bestIdx = -1;
for(int j = 0; j < numBlocks; j++) {
if(!blockAllocated[j] && blockSize[j] >= processSize[i]) {
if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
bestIdx = j;
}
}
if(bestIdx != -1) {
processAllocated[i] = bestIdx;
blockAllocated[bestIdx] = 1;
blockData[bestIdx] = processSize[i];
}
}
}
void worstFit(int blockSize[], int blockAllocated[], int blockData[],
int processSize[], int processAllocated[],
int numBlocks, int numProcesses) {
for(int i = 0; i < numProcesses; i++) {
int worstIdx = -1;
for(int j = 0; j < numBlocks; j++) {
if(!blockAllocated[j] && blockSize[j] >= processSize[i]) {
if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
worstIdx = j;
}
}
if(worstIdx != -1) {
processAllocated[i] = worstIdx;
blockAllocated[worstIdx] = 1;
blockData[worstIdx] = processSize[i];
}
}
}
void displayAllocations(int blockSize[], int blockAllocated[], int
blockData[],
int processSize[], int processAllocated[],
int numBlocks, int numProcesses) {
printf("\n--- Process Allocation ---\n");
printf("Process No.\tSize\tBlock Allocated\n");
for(int i = 0; i < numProcesses; i++) {
printf("%d\t\t%d\t", i+1, processSize[i]);
if(processAllocated[i] != -1)
printf("%d\n", processAllocated[i]+1);
else
printf("Not Allocated\n");
}
printf("\n--- Block Status ---\n");
printf("Block No.\tBlock Size\tData Stored\n");
for(int i = 0; i < numBlocks; i++) {
printf("%d\t\t%d\t\t", i+1, blockSize[i]);
if(blockAllocated[i])
printf("%d\n", blockData[i]);
else
printf("Empty\n");
}
printf("\n--- Unallocated Processes ---\n");
int unallocated = 0;
for(int i = 0; i < numProcesses; i++) {
if(processAllocated[i] == -1) {
printf("Process %d (Size %d) was not allocated.\n", i+1, 
processSize[i]);
unallocated = 1;
}
}
if(!unallocated)
printf("All processes were successfully allocated.\n");
}
int main() {
int blockSize[100], blockAllocated[100], blockData[100];
int processSize[100], processAllocated[100];
int numBlocks, numProcesses;
int choice;
printf("=== Dynamic Memory Allocation ===\n");
inputBlocks(blockSize, blockAllocated, blockData, &numBlocks);
inputProcesses(processSize, processAllocated, &numProcesses);
do {
printf("\nChoose Allocation Strategy:\n");
printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
printf("Enter choice: ");
scanf("%d", &choice);
resetAllocation(blockAllocated, blockData, processAllocated, 
numBlocks, numProcesses);
switch(choice) {
case 1:
firstFit(blockSize, blockAllocated, blockData,
processSize, processAllocated,
numBlocks, numProcesses);
displayAllocations(blockSize, blockAllocated, blockData,
processSize, processAllocated,
numBlocks, numProcesses);
break;
case 2:
bestFit(blockSize, blockAllocated, blockData,
processSize, processAllocated,
numBlocks, numProcesses);
displayAllocations(blockSize, blockAllocated, blockData,
processSize, processAllocated,
numBlocks, numProcesses);
break;
case 3:
worstFit(blockSize, blockAllocated, blockData,
processSize, processAllocated,
numBlocks, numProcesses);
displayAllocations(blockSize, blockAllocated, blockData,
processSize, processAllocated,
numBlocks, numProcesses);
break;
case 4:
printf("Exiting program.\n");
break;
default:
printf("Invalid choice. Try again.\n");
}
} while(choice != 4);
return 0;
}
