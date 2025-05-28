#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <main.h>
#include <buffer.c>

meta_commands getMetaCommands(inBuffer *inputBuffer){
    if (strcmp(inputBuffer->buffer, ".exit") == 0){
        closeInputBuffer(inputBuffer);
        exit(EXIT_SUCCESS);
    };
    
    return META_COMMAND_SUCCESS;
};

//Acts as the tokenizer -> reads through the different options and sees if user selection matches enum case
prepare_result getPrepareResult(const char* buffer, statement *stmnt, Row *row){
    fflush(stdout);

    if (strncmp(buffer, ".insert", 6) == 0){
        stmnt->type = STATEMENT_INSERT;
        sscanf(buffer,".insert %d %s %s", &(row->id), row->username, row->email);
        
        return PREPARE_SUCCESS;
    
    } else if (strcmp(buffer, ".select") == 0){
        stmnt->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    
    return PREPARE_UNRECOGNIZED_STATEMENT;
};

void execute_insert(Table *table, Row *row){
    serialize_row(table->stackPointer, row->id, ID_BYTE_SIZE);
    serialize_row(table->stackPointer+USERNAME_OFFSET, row->username, USERNAME_BYTE_SIZE);
    serialize_row(table->stackPointer+EMAIL_OFFSET, row->email, EMAIL_BYTE_SIZE);

    stackPointer += ROW_OFFSET;
};

void serialize_row(void* location, void *from, byte_size) // -> pointer to the address of id, username, email
    memcpy(&location, &from, ID_BYTE_SIZE);
    memcpy(&location, &from, USERNAME_BYTE_SIZE);
    memcpy(&location, &from, EMAIL_BYTE_SIZE);
};

//void deserialize_row(){};

void execute_statement(inBuffer *inputBuffer, statement *stmnt
                    Row *row, Table *table){
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
    Table *table = malloc(sizeof(TABLE_SIZE));
    Row *row = malloc(sizeof(ROW_SIZE));

    while(1){
        printPrompt();
        readInput(newBuffer);
        statement *newStatement;
        
        if (strncmp(newBuffer->buffer, ".", 1) == 0){
            switch(getMetaCommands(newBuffer)) {
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    continue; //continue; continue jumps to the next iteration of the while loop
                case META_COMMAND_SUCCESS:
            }

            switch(getPrepareResult(newBuffer->buffer, newStatement, row)) {
                case PREPARE_SUCCESS:
                    executeCommand(newBuffer, newStatement, row);
                    continue;
                    
                case PREPARE_UNRECOGNIZED_STATEMENT:
                    printf("%s\n",  "Unrecognized keyword");
                    continue;
            }
            
            
        }
    };
        
};