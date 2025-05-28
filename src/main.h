#ifndef MAIN.H


#define MAIN.H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 4096; // Number of bytes
#define ROW_SIZE 291; // Number of bytes a single row uses
#define TABLE_SIZE (4096*10); // Number of bytes is 4096, for 10 pages

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

const uint32_t ID_BYTE_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_BYTE_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_BYTE_SIZE = size_of_attribute(Row, email);

const uint32_t ID_OFFSET = 4;
const uint32_t USERNAME_OFFSET = ID_OFFSET + USERNAME_BYTE_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + EMAIL_BYTE_SIZE;
const uint32_t ROW_OFFSET = ID_OFFSET + USERNAME_OFFSET + EMAIL_OFFSET; 

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

typedef struct {
    uint_32t id;
    char[32] username;
    char[255] email; 

    email[31] = "/0"; // select knows when it's gone through a row by reaching an escape character
} Row;

typedef struct{
    void* basePointer; //points to the beginning of the table's memory location
    void* stackPointer; //specifices the last memory locations
} Table;


#endif



/*
SQL uses pages, so one page is 4096, and it'll be named of 100-some pages
*/