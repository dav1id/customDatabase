#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* buffer;
    size_t bufferSize;
    ssize_t inputLength; // Use of two size variables (bufferSize/inLen)
} inBuffer;

// Typedefs for our meta commands (exterior commands like .exit), and compare_commands to compare the input from the processor (prepare_statement) to be sent to the virtual machine. this reduces the stress on the virtual machine and lets us pinpoint errors
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} statementType

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} meta_commands;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} prepare_result;


inBuffer* newInputBuffer(){
    inBuffer *inputBuffer = malloc(sizeof(inBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->bufferSize = 0;
    inputBuffer->inputLength = 0;
    
    return inputBuffer;
};

meta_commands getMetaCommands(inBuffer *inputBuffer){
    if (strcmp(inputBuffer->buffer, ".exit") == 0){
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    };
    
    return META_COMMAND_SUCCESS;
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
        
        
        // switch for meta commands (like .exit)
        
        if (strncmp(newBuffer->buffer, ".", 1) == 0){
            switch(getMetaCommands(newBuffer->buffer)) {
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("%s\n", "Error reading input");
                    exit(EXIT_FAILURE);
                    
                case META_COMMAND_SUCCESS:
                    continue
            }
        }
        

        // switch for statements like (insert, select, etcetra)
    };
        
};

