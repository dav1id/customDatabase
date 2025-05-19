/*
Goal is to create an inputBuffer that saves the input, sees if the input
is .exit() (or another method to exit the database - will create my own syntax lateer)
Create a system that clears parts of the input (kind of like cin.ignore, cin.clear) by prompting the user
when the input buffer gets too full
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* buffer;
	bufferNode *next;
	size_t bufferSize;
} inBuffer;

typedef struct {
	char data;
	bufferNode *next;
	size_t nodeSize; 
} bufferNode;

inBuffer* createBuffer(data){
    // Create the buffer, return a pointer to go through buffer
	inBuffer *inputBuffer = malloc(inBuffer);
	inputBuffer->data  = this->data;
	inputBuffer->next = nullptr;

	return inputBuffer;
};

bufferNode* createBufferNode(inputBuffer){
	bufferNode *bN = malloc(bufferNode);
	if (inputBuffer->next == nullptr) inputBuffer->next = bn;

	bufferNode *nSelect = inputBuffer->next;

	while (nSelect->next != nullptr){
		nSelect = nSelect->next;
	};
 
	return bufferNode;
};

void readInput(inBuffer* buffer){
    // Read the input sent to the buffer
	bufferNode *select = buffer->next;
	size_t tempSize = 0; size_t nodeSize = select->size;

	while (true){
	
	};
};

void closeInputBuffer(struct inputBuffer* buffer){
// Free allocated memory to buffer (destructor)
	bufferNode *nSelect = inputBuffer->next;

	while (nSelect->next != nullptr){
		bufferNode *temp = nSelect;
		nSelect = nSelect->next;

		free(temp);
	};
};

struct clearBuffer* clearBuffer(struct inputBuffer* buffer){
    // Clears the buffer, returns pointer to buffer

};

void promptDataEntry() {printf("%s", "db > ");} 

int main(int argc, int argv[]){

    return 0; 
}
