#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define FILEPATH_SIZE 256

//------------------------------------------------------------
void decrypt(const char* inputFile, const char* outputFile, const char* keyFile) {
    char key;
    FILE* keyIn = fopen(keyFile, "r");
    if (!keyIn) {
        printf("Error opening key file!\n");
        return;
    }
    fscanf(keyIn, "%c", &key);
    fclose(keyIn);

    FILE* inFile = fopen(inputFile, "rb");
    FILE* outFile = fopen(outputFile, "wb");

    if (!inFile || !outFile) {
        printf("Error opening files for decryption!\n");
        if (inFile) fclose(inFile);
        if (outFile) fclose(outFile);
        return;
    }

    int ch;
    while (1) {
        ch = fgetc(inFile);    
        if (ch == EOF) break;  
        
        ch = ch ^ key;       
        fputc(ch, outFile); 
    }

    printf("Decryption complete, Decrypted file: %s\n", outputFile);
    fclose(inFile);
    fclose(outFile);
}
//------------------------------------------------------------

void generateKey(const char* keyFile) {
    char key = 'a' + rand() % 26;

    FILE* outFile = fopen(keyFile, "w");
    if (!outFile) {
        printf("Error writing key file!\n");
        return;
    }

    fprintf(outFile, "%c", key);
    fclose(outFile);

    printf("Key generated successfully and saved to file: %s\n", keyFile);
}

void encrypt(const char* inputFile, const char* outputFile, const char* keyFile) {
    char key;
    FILE* keyIn = fopen(keyFile, "r");

    if (!keyIn) {
        printf("Error opening key file!\n");
        return;
    }

    fscanf(keyIn, "%c", &key);
    fclose(keyIn);

    FILE* inFile = fopen(inputFile, "rb");
    FILE* outFile = fopen(outputFile, "wb");

    if (!inFile || !outFile) {
        printf("Error opening files for encryption!\n");
        if (inFile) fclose(inFile);
        if (outFile) fclose(outFile);
        return;
    }

    int ch;
    while (1) {
        ch = fgetc(inFile);   
        if (ch == EOF) break;  
        
        ch = ch ^ key;     
        fputc(ch, outFile); 
    }

    printf("Encryption complete. Encrypted file: %s\n", outputFile);
    fclose(inFile);
    fclose(outFile);
}

void userChoice(const char* choice, const char* keyFile) {
    char inputFile[FILEPATH_SIZE];
    char outputFile[FILEPATH_SIZE];
    
    if (strcmp(choice, "1") == 0) {
        generateKey(keyFile);
    } 
    else if (strcmp(choice, "2") == 0) {
        printf("Enter input file name: ");
        fgets(inputFile, FILEPATH_SIZE, stdin);
        inputFile[strlen(inputFile) - 1] = '\0';
        
        printf("Enter output file name for encrypted file: ");
        fgets(outputFile, FILEPATH_SIZE, stdin);
        outputFile[strlen(outputFile) - 1] = '\0';

        encrypt(inputFile, outputFile, keyFile);
    } 
    else if (strcmp(choice, "3") == 0) {
        printf("Enter input file name for decryption: ");
        fgets(inputFile, FILEPATH_SIZE, stdin);
        inputFile[strlen(inputFile) - 1] = '\0';

        printf("Enter output file name for decrypted file: ");
        fgets(outputFile, FILEPATH_SIZE, stdin);
        outputFile[strlen(outputFile) - 1] = '\0';

        decrypt(inputFile, outputFile, keyFile);
    } 
    else if(strcmp(choice, "4") == 0) {
        printf("Exiting...\n");
    }
    else {
        printf("Invalid choice. Please try again.\n");
    }
}

int main() {
    char choice[10];
    const char* keyFile = "secret.key";
    
    printf("Welcome to File Encryption Tool\n");
    
    while (1) {
        printf("\n1. Generate Key\n2. Encrypt File\n3. Decrypt File\n4. Exit\n");
        printf("Choose (1-4): ");
        
        fgets(choice, sizeof(choice), stdin);
        int len = strlen(choice);
        if (len > 0 && choice[len - 1] == '\n') {
            choice[len - 1] = '\0';
        }

        if (strcmp(choice, "4") == 0) {
            printf("Exiting...\n");
            break;
        }
        
        userChoice(choice, keyFile);
    }
    return 0;
}