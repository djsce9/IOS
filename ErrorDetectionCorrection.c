#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Utility Functions
int countOnes(const char* data) {
    int count = 0;
    for (int i = 0; data[i]; i++) {
        if (data[i] == '1') count++;
    }
    return count;
}

void generateParityBit(const char* data, char* parityBit) {
    int count = countOnes(data);
    parityBit[0] = (count % 2 == 0) ? '0' : '1';
    parityBit[1] = '\0';
}

int detectParityError(const char* sent, const char* received) {
    char sentParity[2], recvParity[2];
    generateParityBit(sent, sentParity);
    generateParityBit(received, recvParity);
    return strcmp(sentParity, recvParity) != 0;
}

void performParityCheck() {
    char sentData[MAX], recvData[MAX], parityBit[2];
    printf("Enter sent data (binary): ");
    scanf("%s", sentData);
    generateParityBit(sentData, parityBit);
    printf("Parity Bit: %s\n", parityBit);
    printf("Enter received data (binary): ");
    scanf("%s", recvData);
    if (detectParityError(sentData, recvData)) {
        printf("Error Detected!\n");
    } else {
        printf("No Error Detected.\n");
    }
}

// CRC
void xorDivision(char* dividend, const char* divisor, char* remainder) {
    int dlen = strlen(dividend);
    int glen = strlen(divisor);
    
    // Perform XOR division
    for (int i = 0; i <= dlen - glen; ) {
        // If the first bit is 1, XOR with divisor
        if (dividend[i] == '1') {
            for (int j = 0; j < glen; j++) {
                if (dividend[i + j] == divisor[j])
                    dividend[i + j] = '0';
                else
                    dividend[i + j] = '1';
            }
        }
        i++;
    }
    
    // Copy remainder to output
    strncpy(remainder, &dividend[dlen - glen + 1], glen - 1);
    remainder[glen - 1] = '\0';
}

void performCRCCheck() {
    char sentData[MAX], generator[MAX], receivedData[MAX], crc[MAX], extendedData[MAX], codeword[MAX];
    
    printf("Enter sent data (binary): ");
    scanf("%s", sentData);
    
    printf("Enter generator polynomial (binary): ");
    scanf("%s", generator);
    
    // Create extended data by appending zeros
    strcpy(extendedData, sentData);
    int genLen = strlen(generator);
    for (int i = 0; i < genLen - 1; i++) 
        strcat(extendedData, "0");
    
    // Make a copy for division
    char tempData[MAX];
    strcpy(tempData, extendedData);
    
    // Calculate CRC
    xorDivision(tempData, generator, crc);
    printf("CRC (remainder): %s\n", crc);
    
    // Generate codeword (data + CRC)
    strcpy(codeword, sentData);
    strcat(codeword, crc);
    printf("Codeword (data + CRC): %s\n", codeword);
    
    printf("Enter received data (binary): ");
    scanf("%s", receivedData);
    
    // Check for errors
    char tempReceived[MAX];
    strcpy(tempReceived, receivedData);
    char recvRemainder[MAX];
    xorDivision(tempReceived, generator, recvRemainder);
    
    // Check if remainder is all zeros
    int isError = 0;
    for (int i = 0; recvRemainder[i]; i++) {
        if (recvRemainder[i] == '1') {
            isError = 1;
            break;
        }
    }
    
    if (isError) {
        printf("Error Detected!\n");
    } else {
        printf("No Error Detected.\n");
    }
}

// Hamming Code
void performHammingCodeCorrection() {
    char code[MAX];
    printf("Enter received Hamming Code (format: d7,d6,d5,p4,d3,p2,p1): ");
    scanf("%s", code);
    int len = strlen(code);
    
    // Calculate parity bits
    int p1 = 0, p2 = 0, p4 = 0;
    
    // Check P1 (positions 1,3,5,7)
    if (code[6] == '1') p1 ^= 1; // P1
    if (code[4] == '1') p1 ^= 1; // D3
    if (code[2] == '1') p1 ^= 1; // D5
    if (code[0] == '1') p1 ^= 1; // D7
    
    // Check P2 (positions 2,3,6,7)
    if (code[5] == '1') p2 ^= 1; // P2
    if (code[4] == '1') p2 ^= 1; // D3
    if (code[1] == '1') p2 ^= 1; // D6
    if (code[0] == '1') p2 ^= 1; // D7
    
    // Check P4 (positions 4,5,6,7)
    if (code[3] == '1') p4 ^= 1; // P4
    if (code[2] == '1') p4 ^= 1; // D5
    if (code[1] == '1') p4 ^= 1; // D6
    if (code[0] == '1') p4 ^= 1; // D7
    
    // Calculate error position
    int errorPos = p4 * 4 + p2 * 2 + p1;
    
    if (errorPos > 0 && errorPos <= len) {
        printf("Error Detected at position %d!\n", errorPos);
        // Correct the error (positions are 1-indexed but array is 0-indexed)
        int pos = len - errorPos;
        code[pos] = (code[pos] == '0') ? '1' : '0';
        printf("Corrected Code: %s\n", code);
    } else if (errorPos == 0) {
        printf("No Error Detected.\n");
    } else {
        printf("Multiple errors detected, cannot correct.\n");
    }
}
//2D Parity Checker
void performTwoDParity() {
    int rows, cols;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    char data[10][11];         // Input data, up to 10 rows of 10 bits (+1 for '\0')
    char rowParity[10];        // Row parity bits
    char colParity[11];        // Column parity bits (+1 for row parity parity)
    int i, j;

    // Input the original data
    printf("Enter binary data row-wise:\n");
    for (i = 0; i < rows; i++) {
        scanf("%s", data[i]);
        if (strlen(data[i]) != cols) {
            printf("Error: Row %d doesn't have %d columns\n", i+1, cols);
            return;
        }
    }

    // Calculate row parities
    for (i = 0; i < rows; i++) {
        int count = 0;
        for (j = 0; j < cols; j++) {
            if (data[i][j] == '1') count++;
        }
        rowParity[i] = (count % 2 == 0) ? '0' : '1';
    }
    rowParity[rows] = '\0';

    // Calculate column parities
    for (j = 0; j < cols; j++) {
        int count = 0;
        for (i = 0; i < rows; i++) {
            if (data[i][j] == '1') count++;
        }
        colParity[j] = (count % 2 == 0) ? '0' : '1';
    }
    // Calculate parity for row parity bits (bottom-right corner)
    int count = 0;
    for (i = 0; i < rows; i++) {
        if (rowParity[i] == '1') count++;
    }
    colParity[cols] = (count % 2 == 0) ? '0' : '1';
    colParity[cols+1] = '\0';

    // Display codeword (data + parity bits)
    printf("\nTransmitted Data with Parity:\n");
    for (i = 0; i < rows; i++) {
        printf("%s %c\n", data[i], rowParity[i]);
    }
    printf("%s\n", colParity);

    // Receiver side: input received data with row parities and received column parity
    char receivedData[10][12];
    char receivedColParity[12];
    printf("\nEnter received data with row parity (row-wise):\n");
    for (i = 0; i < rows; i++) {
        scanf("%s", receivedData[i]);
        if (strlen(receivedData[i]) != cols + 1) {
            printf("Error: Row %d should have %d data bits plus parity bit\n", i+1, cols);
            return;
        }
    }
    printf("Enter received column parity: ");
    scanf("%s", receivedColParity);
    if (strlen(receivedColParity) != cols + 1) {
        printf("Error: Column parity should have %d bits (including parity for row parities)\n", cols + 1);
        return;
    }

    // Check row parities
    int error = 0;
    for (i = 0; i < rows; i++) {
        int ones = 0;
        for (j = 0; j < cols; j++) {
            if (receivedData[i][j] == '1') ones++;
        }
        char expectedParity = (ones % 2 == 0) ? '0' : '1';
        if (expectedParity != receivedData[i][cols]) {
            error = 1;
            break;
        }
    }

    // Check column parities
    if (!error) {
        for (j = 0; j < cols; j++) {
            int ones = 0;
            for (i = 0; i < rows; i++) {
                if (receivedData[i][j] == '1') ones++;
            }
            char expectedParity = (ones % 2 == 0) ? '0' : '1';
            if (expectedParity != receivedColParity[j]) {
                error = 1;
                break;
            }
        }
    }

    // Check parity of row parity bits (bottom-right corner)
    if (!error) {
        int ones = 0;
        for (i = 0; i < rows; i++) {
            if (receivedData[i][cols] == '1') ones++;
        }
        char expectedParity = (ones % 2 == 0) ? '0' : '1';
        if (expectedParity != receivedColParity[cols]) {
            error = 1;
        }
    }

    if (!error) {
        printf("\nNo errors detected. Data accepted. Discarding redundant parity bits:\n");
        for (i = 0; i < rows; i++) {
            receivedData[i][cols] = '\0'; // Remove row parity
            printf("%s\n", receivedData[i]);
        }
    } else {
        printf("\nError detected! Data is corrupted and will not be accepted.\n");
    }
}


// Checksum
void performChecksum() {
    int blocks, bits;
    char data[10][20], result[20];
    printf("Enter number of blocks: ");
    scanf("%d", &blocks);
    printf("Enter number of bits per block: ");
    scanf("%d", &bits);
    printf("Enter data blocks:\n");
    for (int i = 0; i < blocks; i++) scanf("%s", data[i]);

    int sum = 0;
    for (int i = 0; i < blocks; i++) sum += strtol(data[i], NULL, 2);

    while (sum >> bits) sum = (sum & ((1 << bits) - 1)) + (sum >> bits);

    int checksum = ~sum & ((1 << bits) - 1);
    printf("Checksum: ");
    for (int i = bits - 1; i >= 0; i--) printf("%d", (checksum >> i) & 1);
    printf("\n");

    // Receiver side validation
    printf("\nAt receiver side:\n");
    printf("Enter received blocks (including checksum):\n");
    char receivedData[11][20];
    for (int i = 0; i <= blocks; i++) scanf("%s", receivedData[i]);
    
    int receivedSum = 0;
    for (int i = 0; i <= blocks; i++) receivedSum += strtol(receivedData[i], NULL, 2);
    
    while (receivedSum >> bits) receivedSum = (receivedSum & ((1 << bits) - 1)) + (receivedSum >> bits);
    
    int finalCheck = ~receivedSum & ((1 << bits) - 1);
    
    if (finalCheck == 0)
        printf("No Error Detected.\n");
    else
        printf("Error Detected in received data.\n");
}

// Main menu
int main() {
    int choice;
    while (1) {
        printf("\n--- Error Detection and Correction ---\n");
        printf("1. Parity Check\n");
        printf("2. CRC (Cyclic Redundancy Check)\n");
        printf("3. Hamming Code\n");
        printf("4. Two-Dimensional Parity Check\n");
        printf("5. Checksum\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: performParityCheck(); break;
            case 2: performCRCCheck(); break;
            case 3: performHammingCodeCorrection(); break;
            case 4: performTwoDParity(); break;
            case 5: performChecksum(); break;
            case 6: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
