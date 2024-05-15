#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

int referenceString[MAX_PAGES];
int numPages, numFrames;

// Function to find if a page exists in frames
bool isInFrames(int page, int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to find the index of the page in frames
int indexOfPage(int page, int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

// FIFO Page Replacement Algorithm
int FIFO(int referenceString[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int frameIndex = 0;

    for (int i = 0; i < numPages; i++) {
        if (!isInFrames(referenceString[i], frames, numFrames)) {
            pageFaults++;
            frames[frameIndex] = referenceString[i];
            frameIndex = (frameIndex + 1) % numFrames;
        }
    }

    return pageFaults;
}

// LRU Page Replacement Algorithm
int LRU(int referenceString[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int recentUsed[MAX_FRAMES] = {0}; // to keep track of recent usage of pages

    for (int i = 0; i < numPages; i++) {
        if (!isInFrames(referenceString[i], frames, numFrames)) {
            pageFaults++;
            int min = recentUsed[0];
            int minIndex = 0;
            for (int j = 1; j < numFrames; j++) {
                if (recentUsed[j] < min) {
                    min = recentUsed[j];
                    minIndex = j;
                }
            }
            frames[minIndex] = referenceString[i];
            recentUsed[minIndex] = i + 1;
        } else {
            int index = indexOfPage(referenceString[i], frames, numFrames);
            recentUsed[index] = i + 1;
        }
    }

    return pageFaults;
}

// Optimal Page Replacement Algorithm
int Optimal(int referenceString[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        if (!isInFrames(referenceString[i], frames, numFrames)) {
            pageFaults++;
            int replaceIndex = -1;
            for (int j = 0; j < numFrames; j++) {
                int k;
                for (k = i + 1; k < numPages; k++) {
                    if (frames[j] == referenceString[k]) {
                        break;
                    }
                }
                if (k == numPages) {
                    replaceIndex = j;
                    break;
                }
            }
            if (replaceIndex == -1) {
                replaceIndex = 0;
                for (int j = 1; j < numFrames; j++) {
                    int k;
                    for (k = i + 1; k < numPages; k++) {
                        if (frames[j] == referenceString[k]) {
                            break;
                        }
                    }
                    if (k > replaceIndex) {
                        replaceIndex = j;
                    }
                }
            }
            frames[replaceIndex] = referenceString[i];
        }
    }

    return pageFaults;
}

int main() {
    printf("Enter the number of pages in reference string: ");
    scanf("%d", &numPages);

    printf("Enter the reference string: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &referenceString[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    int fifoFaults = FIFO(referenceString, numPages, numFrames);
    int lruFaults = LRU(referenceString, numPages, numFrames);
    int optimalFaults = Optimal(referenceString, numPages, numFrames);

    printf("\nNumber of page faults for FIFO: %d\n", fifoFaults);
    printf("Number of page faults for LRU: %d\n", lruFaults);
    printf("Number of page faults for Optimal: %d\n", optimalFaults);

    return 0;
}

