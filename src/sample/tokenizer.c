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
} statementType;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} meta_commands;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} prepare_result;

typedef struct { // holds the actual statement select, to verify if the user actually put in a statement. the idea is to make it methodological, break all of it into steps so that you can address the error
    statementType type;
} statement;

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

meta_commands getMetaCommands(inBuffer *inputBuffer){
    if (strcmp(inputBuffer->buffer, ".exit") == 0){
        closeInputBuffer(inputBuffer);
        exit(EXIT_SUCCESS);
    };
    
    return META_COMMAND_SUCCESS;
};


//Acts as the tokenizer -> reads through the different options and sees if user selection matches enum case
prepare_result getPrepareResult(const char* buffer, statement *stmnt){
    fflush(stdout);
    if (strncmp(buffer, ".insert", 6) == 0){
        stmnt->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
                
    } else if (strcmp(buffer, ".select") == 0){
        stmnt->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    
    return PREPARE_UNRECOGNIZED_STATEMENT;
};

void executeCommand(inBuffer *inputBuffer, statement *stmnt){
    switch (stmnt->type){
        case STATEMENT_INSERT:
            printf("%s\n", "User selected insert command");
            break;
            
        case STATEMENT_SELECT:
            printf("%s\n", "User selected select command");
            break;
    }
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


int main(int argc, char* argv[]){
    inBuffer *newBuffer = newInputBuffer();

    while(1){
        printPrompt();
        readInput(newBuffer);
        statement *newStatement;
        
        // switch for meta commands (like .exit)
        if (strncmp(newBuffer->buffer, ".", 1) == 0){
            //printf("%s\n", newBuffer->buffer);
            
            switch(getMetaCommands(newBuffer)) {
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    continue;
                 //   continue; continue jumps to the next iteration of the while loop
                    
                case META_COMMAND_SUCCESS:
            }
            
            //getMetaCommands(newBuffer);
            
            switch(getPrepareResult(newBuffer->buffer, newStatement)) {
                case PREPARE_SUCCESS:
                  //  printf("%s\n","Recognized keyword");
                    executeCommand(newBuffer, newStatement);
                    continue;
                    
                case PREPARE_UNRECOGNIZED_STATEMENT:
                    printf("%s\n",  "Unrecognized keyword");
                    continue;
            }
            
            
        }
    };
        
};
