/**
 * Assignment: life
 * Name : Bryan Ramirez
 * PID: A16626517
 * Class: UCSD CSE30-WI21
 *
 */
#include "cse30life.h"
#include "board.h"

/**
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - ensure that no border cells are set to alive
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){
	// Allocate memory for the boards_t struct on the heap
	boards_t *newBoard = (boards_t*) malloc(sizeof(boards_t));
	
	newBoard->gen = 0; // Set generation number to zero

	FILE *fp; // a pointer to a file stream

	// Attempt to open the file for reading and assign the file stream to fp
	if((fp = fopen(initFileName, "r")) == NULL){
		return NULL; // if it failed return NULL ptr	
	}
	
	int rows; // Will hold # of rows of the board
	int columns; // Will hold # of columns of the board

	// Read num of rows and columns from file and assign them to local variables rows and columns
	fscanf(fp, "%d", &rows);

	fscanf(fp, "%d", &columns);
	
	// Assign row nums and col nums to board structure
	newBoard->numRows = rows;
	newBoard->numCols = columns;

	// Allocate memory for the struct's bufferA and bufferB
	newBoard->bufferA = (belem*)malloc(sizeof(belem) * (rows * columns));
	newBoard->bufferB = (belem*)malloc(sizeof(belem) * (rows * columns));
	
	// Initialize currentBuffer and nextBuffer to bufferA/bufferB
	newBoard->currentBuffer = newBoard->bufferA;
	newBoard->nextBuffer = newBoard->bufferB;

	//Zero out both buffers
	clearBoards(newBoard);

	// Declare two variables that will hold the coordinates for cells that
	// will be alive at the start
	int yCoord;
	int xCoord;
	
	// Initialize the appropriate cells in currentBuffer to be alive
	while(fscanf(fp, "%d %d", &yCoord, &xCoord) > 0){ 
	
		
		// if-else block to make sure coordinates are within appropriate range
		// before initializing cells
		if(yCoord>(rows-1) || xCoord>(columns-1)){
			printf("Invalid Coordinates");
			return NULL;
		}
		else {
			newBoard->currentBuffer[getIndex(newBoard,yCoord,xCoord)] = 1;
		}	
	}

	// Zero out top and bottom border cells
	for(int i=0; i<columns; i++) {
		newBoard->currentBuffer[i] = 0;
		newBoard->currentBuffer[(rows-1)*columns+i] = 0;
	}
	
	// Zero out left and right border cells
	for(int j=1; j<(rows-1); j++) {
		newBoard->currentBuffer[j*columns] = 0;
		newBoard->currentBuffer[j*columns+(columns-1)] = 0;
	}	

	fclose(fp); // close filestream

	return newBoard; // Return ptr created
}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
	
	// Free bufferA 
	free((*bptrPtr)->bufferA);
	
	// Free bufferB
	free((*bptrPtr)->bufferB);
	
	// Free currentBuffer
	free((*bptrPtr)->currentBuffer);
	
	// Free nextBuffer 
	free((*bptrPtr)->nextBuffer);

	//Free numRows 
	free((*bptrPtr)->numRows);

	//Free numCols
	free((*bptrPtr)->numCols);
	
	// Free gen
	free((*bptrPtr)->gen);

	// Set the pointer to boards_t struct to null
	*bptrPtr = NULL;

}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
 	
	// Determine the size of the buffers
	int size = self->numRows * self->numCols;
	
	// Zero out the elements in all the belems in both buffers
	for(int i=0; i<size; i++) {
		self->bufferA[i] = 0;
		self->bufferB[i] = 0;
		self->currentBuffer[i] = 0;
		self->nextBuffer[i] = 0;
	}
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
	
	// Create a temporary tempBuffer struct
	boards_t *tempBoard = (boards_t*) malloc(sizeof(boards_t));
	
	// Initialize the currentBuffer of tempBuffer to self->currentBuffer
	tempBoard->currentBuffer = self->currentBuffer;
	
	// Swap the currentBuffer and nextBuffer using the temp struct
	self->currentBuffer = self->nextBuffer;
	self->nextBuffer = tempBoard->currentBuffer;

	// Free the temporary board
	free(tempBoard);

}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
	// Initialize index variable for 1D array buffer
	int index = row*(self->numCols) + col;
	
	// Return corresponding index
	return index;
}
  
