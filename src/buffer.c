#include <main.h>
#include <stdio.h>
#include <string.h>

const uint32_t USERNAME_OFFSET = 2;
const uint32_t EMAIL_OFFSET = 36;

inBuffer* newInputBuffer(){
    inBuffer *inputBuffer = malloc(sizeof(inBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->bufferSize = 0;
    inputBuffer->inputLength = 0;
    
    return inputBuffer;
};

void closeInputBuffer(inBuffer *inputBuffer){ // Free the memory allocated to the structure buffer
    free(inputBuffer->buffer); // getline allocates memory so we're responsible for freeing i
    free(inputBuffer);
};