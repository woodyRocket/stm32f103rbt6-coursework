/*
 * support_function.c
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#include <buffer_manip.h>

static uint8_t ledRedIndex 			= 	0;
static uint8_t ledGreenIndex 		= 	1;

uint8_t Get_Bit_Value(uint8_t data, uint8_t index){
	return (data >> index) & 0x01;
}
uint8_t** Create_Copy_Buffer(uint8_t* buffer, uint8_t size, uint8_t numberCopy){
	uint8_t largeIndex, smallIndex;
	uint8_t** copyBuffer = (uint8_t**)malloc(numberCopy);
	for (largeIndex = 0; largeIndex < numberCopy; largeIndex++){
		copyBuffer[largeIndex] = (uint8_t*)malloc(size);
		for (smallIndex = 0; smallIndex < size; smallIndex++){
			copyBuffer[largeIndex][smallIndex] = buffer[smallIndex];
		}
	}
	return copyBuffer;
}
void Free_Copy_Buffer(uint8_t** multipleBuffer, uint8_t numberCopy){
	uint8_t largeIndex;
	for (largeIndex = 0 ; largeIndex < numberCopy; largeIndex++){
		free(multipleBuffer[largeIndex]);
	}
	free(multipleBuffer);
}
void Update_Red_Index(uint8_t size){
	ledRedIndex = (ledRedIndex + SPACE_BETWEEN_SAME_LED) % size;
}
void Update_Green_Index(uint8_t size){
	ledGreenIndex = (ledGreenIndex + SPACE_BETWEEN_SAME_LED) % size;
}
void Rollback_Green_Index(uint8_t size){
	if (ledGreenIndex <= 1)
		ledGreenIndex += size - SPACE_BETWEEN_SAME_LED;
	else
		ledGreenIndex = (ledGreenIndex - SPACE_BETWEEN_SAME_LED) % size;
}
void Rollback_Red_Index (uint8_t size){
	if (ledRedIndex <= 0)
		ledRedIndex += size - SPACE_BETWEEN_SAME_LED;
	else
		ledRedIndex = (ledRedIndex - SPACE_BETWEEN_SAME_LED) % size;
}
void Toggle_Led(uint8_t* state){
	if (*state == LED_ON){
		*state = LED_OFF;
	}
	else {
		*state = LED_ON;
	}
}
uint8_t* Single_Led_Blink(uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	buffer[ledRedIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != ledRedIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	ledRedIndex = (ledRedIndex + 1) % size;
	return buffer;
}
uint8_t* All_Led_On(uint8_t* buffer, uint8_t size){
	for (ledRedIndex = 0; ledRedIndex < size; ledRedIndex++){
		buffer[ledRedIndex] = LED_ON;
	}
	return buffer;
}
uint8_t* All_Red_On(uint8_t* buffer, uint8_t size){
	for (ledRedIndex = 0; ledRedIndex < size; ledRedIndex = ledRedIndex + SPACE_BETWEEN_SAME_LED){
		buffer[ledRedIndex] = LED_ON;
	}
	return buffer;
}
uint8_t* All_Green_On(uint8_t* buffer, uint8_t size){
	for (ledGreenIndex = 1; ledGreenIndex < size; ledGreenIndex = ledGreenIndex + SPACE_BETWEEN_SAME_LED){
		buffer[ledGreenIndex] = LED_ON;
	}
	return buffer;
}
uint8_t* All_Red_Blink(uint8_t* buffer, uint8_t size){
	for (ledRedIndex = 0; ledRedIndex < size; ledRedIndex = ledRedIndex + SPACE_BETWEEN_SAME_LED){
		buffer[ledRedIndex] = (buffer[ledRedIndex] + 1) % NUMBER_OF_LED_STATE;
	}
	return buffer;
}
uint8_t* All_Green_Blink(uint8_t* buffer, uint8_t size){
	for (ledGreenIndex = 1; ledGreenIndex < size; ledGreenIndex = ledGreenIndex + SPACE_BETWEEN_SAME_LED){
		buffer[ledGreenIndex] = (buffer[ledGreenIndex] + 1) % NUMBER_OF_LED_STATE;
	}
	return buffer;
}
uint8_t* Green_Moving_Forward (uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	buffer[ledGreenIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != ledGreenIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	Update_Green_Index(size);
	return buffer;
}
uint8_t* Red_Moving_Forward (uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	buffer[ledRedIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != ledRedIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	Update_Red_Index(size);
	return buffer;
}
uint8_t* Green_Moving_Backward (uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	uint8_t reverseIndex = size - ledGreenIndex;
	buffer[reverseIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != reverseIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	Update_Green_Index(size);
	return buffer;
}
uint8_t* Red_Moving_Backward (uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	uint8_t reverseIndex = size - ledRedIndex - SPACE_BETWEEN_SAME_LED;
	buffer[reverseIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != reverseIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	Update_Red_Index(size);
	return buffer;
}
uint8_t* Red_Backward_Green_Forward (uint8_t* buffer, uint8_t size){
	uint8_t copyIndex;
	uint8_t** copyBuffer = Create_Copy_Buffer(buffer, size, NUMBER_OF_LED_TYPE);
	copyBuffer[0] 	= 	Red_Moving_Backward(copyBuffer[0], size);
	copyBuffer[1] 	= 	Green_Moving_Forward(copyBuffer[1], size);
	for (copyIndex = 0; copyIndex < size; copyIndex++){
		buffer[copyIndex] = copyBuffer[0][copyIndex] | copyBuffer[1][copyIndex];
	}
	Free_Copy_Buffer(copyBuffer, NUMBER_OF_LED_TYPE);
	return buffer;
}
uint8_t* Red_Forward_Green_Backward (uint8_t* buffer, uint8_t size){
	uint8_t copyIndex;
	uint8_t** copyBuffer = Create_Copy_Buffer(buffer, size, NUMBER_OF_LED_TYPE);
	copyBuffer[0] 	= 	Red_Moving_Forward(copyBuffer[0], size);
	copyBuffer[1] 	= 	Green_Moving_Backward(copyBuffer[1], size);
	for (copyIndex = 0; copyIndex < size; copyIndex++){
		buffer[copyIndex] = copyBuffer[0][copyIndex] | copyBuffer[1][copyIndex];
	}
	Free_Copy_Buffer(copyBuffer, NUMBER_OF_LED_TYPE);
	return buffer;
}
uint8_t* Red_Backward_Green_Backward (uint8_t* buffer, uint8_t size){
	uint8_t copyIndex;
	uint8_t** copyBuffer = Create_Copy_Buffer(buffer, size, NUMBER_OF_LED_TYPE);
	copyBuffer[0] 	= 	Red_Moving_Backward(copyBuffer[0], size);
	copyBuffer[1] 	= 	Green_Moving_Backward(copyBuffer[1], size);
	for (copyIndex = 0; copyIndex < size; copyIndex++){
		buffer[copyIndex] = copyBuffer[0][copyIndex] | copyBuffer[1][copyIndex];
	}
	Free_Copy_Buffer(copyBuffer, NUMBER_OF_LED_TYPE);
	return buffer;
}
uint8_t* Red_Forward_Green_Forward (uint8_t* buffer, uint8_t size){
	uint8_t copyIndex;
	uint8_t** copyBuffer = Create_Copy_Buffer(buffer, size, NUMBER_OF_LED_TYPE);
	copyBuffer[0] 	= 	Red_Moving_Forward(copyBuffer[0], size);
	copyBuffer[1] 	= 	Green_Moving_Forward(copyBuffer[1], size);
	for (copyIndex = 0; copyIndex < size; copyIndex++){
		buffer[copyIndex] = copyBuffer[0][copyIndex] | copyBuffer[1][copyIndex];
	}
	Free_Copy_Buffer(copyBuffer, NUMBER_OF_LED_TYPE);
	return buffer;
}
uint8_t* Red_Moving_Middle(uint8_t* buffer, uint8_t size){
	uint8_t copyIndex;
	uint8_t** copyBuffer = Create_Copy_Buffer(buffer, size, NUMBER_OF_LED_TYPE);
	copyBuffer[0] 	= 	Red_Moving_Forward(copyBuffer[0], size);
	Rollback_Red_Index(size);
	copyBuffer[1] 	= 	Red_Moving_Backward(copyBuffer[1], size);
	for (copyIndex = 0; copyIndex < size; copyIndex++){
		buffer[copyIndex] = copyBuffer[0][copyIndex] | copyBuffer[1][copyIndex];
	}
	Free_Copy_Buffer(copyBuffer, NUMBER_OF_LED_TYPE);
	return buffer;
}
uint8_t* Green_Moving_Middle(uint8_t* buffer, uint8_t size){
	uint8_t copyIndex;
	uint8_t** copyBuffer = Create_Copy_Buffer(buffer, size, NUMBER_OF_LED_TYPE);
	copyBuffer[0] 	= 	Green_Moving_Forward(copyBuffer[0], size);
	Rollback_Green_Index(size);
	copyBuffer[1] 	= 	Green_Moving_Backward(copyBuffer[1], size);
	for (copyIndex = 0; copyIndex < size; copyIndex++){
		buffer[copyIndex] = copyBuffer[0][copyIndex] | copyBuffer[1][copyIndex];
	}
	Free_Copy_Buffer(copyBuffer, NUMBER_OF_LED_TYPE);
	return buffer;
}
uint8_t* All_Led_Moving_Middle(uint8_t* buffer, uint8_t size){
	uint8_t copyIndex;
	uint8_t** copyBuffer = Create_Copy_Buffer(buffer, size, NUMBER_OF_LED_TYPE);
	copyBuffer[0] 	= 	Red_Forward_Green_Forward(copyBuffer[0], size);
	Rollback_Green_Index(size);
	Rollback_Red_Index(size);
	copyBuffer[1] 	= 	Red_Backward_Green_Backward(copyBuffer[1], size);
	for (copyIndex = 0; copyIndex < size; copyIndex++){
		buffer[copyIndex] = copyBuffer[0][copyIndex] | copyBuffer[1][copyIndex];
	}
	Free_Copy_Buffer(copyBuffer, NUMBER_OF_LED_TYPE);
	return buffer;
}
uint8_t* Red_Cummulative_Forward (uint8_t* buffer, uint8_t size){
	Toggle_Led(&buffer[ledRedIndex]);
	Update_Red_Index(size);
	return buffer;
}
uint8_t* Red_Cummulative_Backward (uint8_t* buffer, uint8_t size){
	uint8_t reverseIndex = size - ledRedIndex - SPACE_BETWEEN_SAME_LED;
	Toggle_Led(&buffer[reverseIndex]);
	Update_Red_Index(size);
	return buffer;
}
uint8_t* Green_Cummulative_Forward (uint8_t* buffer, uint8_t size){
	Toggle_Led(&buffer[ledGreenIndex]);
	Update_Green_Index(size);
	return buffer;
}
uint8_t* Green_Cummulative_Backward (uint8_t* buffer, uint8_t size){
	uint8_t reverseIndex = size - ledGreenIndex;
	Toggle_Led(&buffer[reverseIndex]);
	Update_Green_Index(size);
	return buffer;
}
uint8_t* Red_Forward_Green_Backward_Cumm(uint8_t* buffer, uint8_t size){
	uint8_t copyIndex;
	uint8_t** copyBuffer = Create_Copy_Buffer(buffer, size, NUMBER_OF_LED_TYPE);
	copyBuffer[0] 	= 	Red_Cummulative_Forward(copyBuffer[0], size);
	copyBuffer[1] 	= 	Green_Cummulative_Backward(copyBuffer[1], size);
	for (copyIndex = 0; copyIndex < size; copyIndex++){
		buffer[copyIndex] = copyBuffer[0][copyIndex] | copyBuffer[1][copyIndex];
	}
	Free_Copy_Buffer(copyBuffer, NUMBER_OF_LED_TYPE);
	return buffer;
}
