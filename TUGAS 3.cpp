#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10

struct node {
    char data[100];
    struct node *next;
} *hashTable[TABLE_SIZE];

// Mid-Square Method
int midSquareHash(int key) {
    int squared = key * key;
    int mid = (squared / 10) % TABLE_SIZE; // Ambil angka tengah
    return mid;
}

// Division Method
int divisionHash(int key) {
    return key % TABLE_SIZE;
}

// Folding Method
int foldingHash(int key) {
    int part1 = key / 1000; // 4 digit pertama
    int part2 = key % 1000; // 4 digit terakhir
    return (part1 + part2) % TABLE_SIZE;
}

// Digit Extraction Method
int digitExtractionHash(char data[]) {
    return tolower(data[0]) - 'a';
}

// Rotation Method
int rotationHash(int key) {
    int lastDigit = key % 10;
    int remaining = key / 10;
    return (lastDigit * 1000 + remaining) % TABLE_SIZE;
}

// Chaining (Separate Chaining)
void pushBackChaining(int hashKey, char data[]) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    
    if (hashTable[hashKey] == NULL) {
        hashTable[hashKey] = newNode;
    } else {
        struct node *curr = hashTable[hashKey];
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = newNode;
    }
}

// Linear Probing
int linearProbing(int hashKey) {
    while (hashTable[hashKey] != NULL) {
        hashKey = (hashKey + 1) % TABLE_SIZE;
    }
    return hashKey;
}

// Rehashing
int rehash(int key) {
    return (key + 7) % TABLE_SIZE;
}

void viewHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Hash Table Index [%d]: ", i);
        struct node *curr = hashTable[i];
        while (curr != NULL) {
            printf("%s, ", curr->data);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main() {
    char data[100];
    int choice;
    
    printf("Pilih metode hashing:\n");
    printf("1. Mid-Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Rotation\n");
    scanf("%d", &choice);
    getchar();
    
    do {
        printf("Input Data (ketik 'exit' untuk keluar): ");
        scanf("%s", data);
        getchar();
        
        if (strcmp(data, "exit") == 0) break;
        
        int key = 0;
        for (int i = 0; data[i] != '\0'; i++) {
            key += data[i];
        }
        
        int hashKey;
        switch (choice) {
            case 1: hashKey = midSquareHash(key); break;
            case 2: hashKey = divisionHash(key); break;
            case 3: hashKey = foldingHash(key); break;
            case 4: hashKey = digitExtractionHash(data); break;
            case 5: hashKey = rotationHash(key); break;
            default: hashKey = divisionHash(key);
        }
        
        pushBackChaining(hashKey, data);
        
    } while (1);
    
    viewHashTable();
    
    return 0;
}

