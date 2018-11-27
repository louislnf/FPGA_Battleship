/*
 * interruption_handling.h
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#ifndef INTERRUPTION_HANDLING_H_
#define INTERRUPTION_HANDLING_H_

void registerSwitchesInterruptions(void *context);
void registerButtonsInterruptions(void *context);

void switchesInterruptHandler(void* context);
void buttonsInterruptHandler(void* context);


#endif /* INTERRUPTION_HANDLING_H_ */
