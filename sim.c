/**
 * Assignment: life
 * Name: Bryan Ramirez
 * PID: A16626517
 * Class: UCSD CSE30-WI21
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){
	
	int counter = 0; // Will count how many neighbors are alive
	int deadOrAlive;

	// While-loop that will keep executing until reaching end of the row
	while(srcStart != srcEnd) {
		deadOrAlive = *srcStart; // determine if current cell is dead or alive

		if(*(srcStart + 1) == 1){ // Check if neighbor to the right is alive
			counter++;	
		}
		if(*(srcStart - 1) == 1){ // Check if neighbor to the left is alive
			counter++;
		}
		if(*(srcStart - cols) == 1){ // Check if above neighor is alive
			counter++;
		}
		if(*(srcStart + cols) == 1){ // Check if below neighbor is alive
			counter++;
		}
		if(*(srcStart - (cols - 1)) == 1){ // Check is top right neighor is alive
			counter++;
		}
		if(*(srcStart + (cols + 1)) == 1){ // Check if bottom right neighor is alive
			counter++;
		}
		if(*(srcStart + (cols - 1)) == 1){ // Check if bottom left neighbor is alive
			counter++;
		}
		if(*(srcStart - (cols + 1)) == 1){ // Check if top left neighbor is alive
			counter++;
		}
		
		// Determine if cell will be dead or alive in the next buffer
		if(deadOrAlive == 0){ 
			if(counter == 3){
				*dest = 1;
			}
			else{
				*dest = 0;
			}
		}
		else{
			if(counter == 2 || counter == 3){
				*dest = 1;
			}
			else{
				*dest = 0;
			}
		}
		
		// Move the pointer to the next cell in the row
		srcStart = srcStart + 1;

	}
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
	
	// While loop executes until we have gone through every step
	while(steps > 0){
		for(int i=1; i<((self->numRows)-1); i++){
			// Call do doRow for each row 
			doRow(self->nextBuffer[((self->numCols)*i) + 1], 
			      self->currentBuffer[((self->numCols)*i) + 1],
			      self->currentBuffer[((self->numCols)*i) + ((self->numCols)-2)],
		              self->numCols);
		}	

	// Swap the current and next buffer
	swapBuffers(self);

	// Update the generation
	self->gen = self->gen + 1;
	
	// Update the steps counter
	steps--;

	}


}




