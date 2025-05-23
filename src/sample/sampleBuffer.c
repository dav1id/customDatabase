#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* buffer;
    size_t bufferSize;
    ssize_t inputLength; // Use of two size variables (bufferSize/inLen)
} inBuffer;


inBuffer* newInputBuffer(){
    inBuffer *inputBuffer = malloc(sizeof(inBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->bufferSize = 0;
    inputBuffer->inputLength = 0;
    
    return inputBuffer;
};

void printPrompt(){printf("%s","db > "); }

void readInput(inBuffer *inB){
    ssize_t bytesRead = getline(&(inB->buffer), &(inB->bufferSize), stdin); //getline asks for the address of where to store the result, and uses the signed byte type so that you can check if the bytes read are negative (meaning there was an error in its buffer
 
    if (bytesRead <= 1){ // if the bytesRead is negative then exit
        printf("%s\n", "Error reading input");
        exit(EXIT_FAILURE);
    }
    
    inB->inputLength = bytesRead - 1;
    inB->buffer[bytesRead - 1] = 0;
    // the bytes read includes an escape character, or newline character, and you dont want that to be included in the length of the actual buffer. since char* buffer points to the first character in a memory address, you can access the address of the escapeCharacter and set it to 0 (meaning its representing nothing in bytes, so there's nothing at that memory address)
};

void closeInputBuffer(inBuffer *inputBuffer){ // Free the memory allocated to the structure buffer
    free(inputBuffer->buffer); // getline allocates memory so we're responsible for freeing i
    free(inputBuffer);
};

int main(int argc, char* argv[]){
    inBuffer *newBuffer = newInputBuffer();

    while(1){
        printPrompt();
        readInput(newBuffer);
        // printf("%s\n", newBuffer->buffer);
        
        if (strcmp(newBuffer->buffer, ".exit") == 0){
            closeInputBuffer(newBuffer);
            exit(EXIT_SUCCESS);
        };
    };
        
};
