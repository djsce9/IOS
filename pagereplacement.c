#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// Function to check if a page exists in frames
int isPresent(int frames[], int numFrames, int page) {
for (int i = 0; i < numFrames; i++) {
if (frames[i] == page) {
return 1;
}
}
return 0;
}
// Function to print frames with hit or fault status
void printFrames(int frames[], int numFrames, int isFault) {
printf("| ");
for (int i = 0; i < numFrames; i++) {
if (frames[i] == -1)
printf(" - | ");
else
printf("%2d | ", frames[i]);
}
printf(" [%s]\n", isFault ? "Fault" : "Hit");
}
// FIFO Page Replacement Algorithm
void FIFO(int pages[], int n, int numFrames) {
int frames[numFrames], index = 0, faults = 0, hits = 0;
for (int i = 0; i < numFrames; i++) frames[i] = -1;
printf("\nFIFO Page Replacement:\n");
printf("+------+---------------------------+\n");
printf("| Page | Frame Table |\n");
printf("+------+---------------------------+\n");
for (int i = 0; i < n; i++) {
int isFault = !isPresent(frames, numFrames, pages[i]);
if (isFault) {
frames[index] = pages[i];
index = (index + 1) % numFrames;
faults++;
} else {
hits++;
}
printf("| %2d ", pages[i]);
printFrames(frames, numFrames, isFault);
}
printf("+------+---------------------------+\n");
printf("Total Page Hits (FIFO): %d\n", hits);
printf("Total Page Faults (FIFO): %d\n", faults);
}
// LRU Page Replacement Algorithm
void LRU(int pages[], int n, int numFrames) {
int frames[numFrames], lastUsed[numFrames], faults = 0, hits = 0;
for (int i = 0; i < numFrames; i++) {
frames[i] = -1;
lastUsed[i] = -1;
}
printf("\nLRU Page Replacement:\n");
printf("+------+---------------------------+\n");
printf("| Page | Frame Table |\n");
printf("+------+---------------------------+\n");
for (int i = 0; i < n; i++) {
int found = 0, lruIndex = -1, oldest = INT_MAX;
for (int j = 0; j < numFrames; j++) {
if (frames[j] == pages[i]) {
found = 1;
hits++;
lastUsed[j] = i;
break;
}
}
if (!found) {
for (int j = 0; j < numFrames; j++) {
if (frames[j] == -1) {
lruIndex = j;
break;
}
if (lastUsed[j] < oldest) {
oldest = lastUsed[j];
lruIndex = j;
}
}
frames[lruIndex] = pages[i];
lastUsed[lruIndex] = i;
faults++;
}
printf("| %2d ", pages[i]);
printFrames(frames, numFrames, !found);
}
printf("+------+---------------------------+\n");
printf("Total Page Hits (LRU): %d\n", hits);
printf("Total Page Faults (LRU): %d\n", faults);
}
// Optimal Page Replacement Algorithm
void Optimal(int pages[], int n, int numFrames) {
int frames[numFrames], faults = 0, hits = 0;
for (int i = 0; i < numFrames; i++) frames[i] = -1;
printf("\nOptimal Page Replacement:\n");
printf("+------+---------------------------+\n");
printf("| Page | Frame Table |\n");
printf("+------+---------------------------+\n");
for (int i = 0; i < n; i++) {
int found = 0, replaceIndex = -1, farthest = -1;
for (int j = 0; j < numFrames; j++) {
if (frames[j] == pages[i]) {
found = 1;
hits++;
break;
}
}
if (!found) {
for (int j = 0; j < numFrames; j++) {
if (frames[j] == -1) {
replaceIndex = j;
break;
}
int nextUse = INT_MAX;
for (int k = i + 1; k < n; k++) {
if (frames[j] == pages[k]) {
nextUse = k;
break;
}
}
if (nextUse > farthest) {
farthest = nextUse;
replaceIndex = j;
}
}
frames[replaceIndex] = pages[i];
faults++;
}
printf("| %2d ", pages[i]);
printFrames(frames, numFrames, !found);
}
printf("+------+---------------------------+\n");
printf("Total Page Hits (Optimal): %d\n", hits);
printf("Total Page Faults (Optimal): %d\n", faults);
}
int main() {
int n, numFrames, choice;
printf("Enter the number of pages: ");
scanf("%d", &n);
int pages[n];
printf("Enter the reference string: ");
for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
printf("Enter the number of frames: ");
scanf("%d", &numFrames);
printf("\nChoose Page Replacement Policy:\n");
printf("1. FIFO\n2. LRU\n3. Optimal\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
FIFO(pages, n, numFrames);
break;
case 2:
LRU(pages, n, numFrames);
break;
case 3:
Optimal(pages, n, numFrames);
break;
default:
printf("Invalid choice!\n");
}
return 0;
}
