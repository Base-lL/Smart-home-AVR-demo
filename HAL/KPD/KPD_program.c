/*
 * KPD_program.c
 *
 *  Created on: Aug 10, 2026
 *      Author: emad.yousry
 */

#include "std_types.h"

#include "DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"

void KPD_init(void)
{
	// 1. SET COLUMNS AS OUTPUTS
	DIO_u8SetPinDirection(KPD_COL_PORT, KPD_COL0, DIO_OUTPUT);
	DIO_u8SetPinDirection(KPD_COL_PORT, KPD_COL1, DIO_OUTPUT);
	DIO_u8SetPinDirection(KPD_COL_PORT, KPD_COL2, DIO_OUTPUT);
	DIO_u8SetPinDirection(KPD_COL_PORT, KPD_COL3, DIO_OUTPUT);

	// 2. SET ROWS AS INPUTS
	DIO_u8SetPinDirection(KPD_ROW_PORT, KPD_ROW0, DIO_INPUT);
	DIO_u8SetPinDirection(KPD_ROW_PORT, KPD_ROW1, DIO_INPUT);
	DIO_u8SetPinDirection(KPD_ROW_PORT, KPD_ROW2, DIO_INPUT);
	DIO_u8SetPinDirection(KPD_ROW_PORT, KPD_ROW3, DIO_INPUT);

	// 3. ACTIVATE INTERNAL PULL-UPS ON THE ROWS (Write HIGH to an Input)
	DIO_u8SetPinValue(KPD_ROW_PORT, KPD_ROW0, DIO_HIGH);
	DIO_u8SetPinValue(KPD_ROW_PORT, KPD_ROW1, DIO_HIGH);
	DIO_u8SetPinValue(KPD_ROW_PORT, KPD_ROW2, DIO_HIGH);
	DIO_u8SetPinValue(KPD_ROW_PORT, KPD_ROW3, DIO_HIGH);

	// 4. SET ALL COLUMNS HIGH INITIALLY (So they aren't triggering anything yet)
	DIO_u8SetPinValue(KPD_COL_PORT, KPD_COL0, DIO_HIGH);
	DIO_u8SetPinValue(KPD_COL_PORT, KPD_COL1, DIO_HIGH);
	DIO_u8SetPinValue(KPD_COL_PORT, KPD_COL2, DIO_HIGH);
	DIO_u8SetPinValue(KPD_COL_PORT, KPD_COL3, DIO_HIGH);
}

u8 KPD_u8GetPressedKey(void)
{
	u8 pressedKey = KPD_NO_PRESSED_KEY;
	u8 rowValue = 0 ;

	u8 colArr[] = {KPD_COL0, KPD_COL1, KPD_COL2, KPD_COL3};
	u8 rowArr[] = {KPD_ROW0, KPD_ROW1, KPD_ROW2, KPD_ROW3};

	u8 switchArr[4][4] = {
			{13,14,15,16},
			{9,10,11,12},
			{5,6,7,8},
			{1,2,3,4}
	};

	for(u8 COL_Index = 0; COL_Index < 4; COL_Index++)
	{
		// activate current column
		DIO_u8SetPinValue(KPD_COL_PORT, colArr[COL_Index] , DIO_LOW);

		for(u8 ROW_Index = 0; ROW_Index < 4; ROW_Index++)
		{

			// read current row
			DIO_u8GetPinValue(KPD_ROW_PORT, rowArr[ROW_Index], &rowValue);

			// check if switch pressed
			if(rowValue == DIO_LOW)
            {
                pressedKey = switchArr[ROW_Index][COL_Index];
                DIO_u8GetPinValue(KPD_ROW_PORT, rowArr[ROW_Index], &rowValue);
            }
		}
		// deactivate current column
		DIO_u8SetPinValue(KPD_COL_PORT, colArr[COL_Index] , DIO_HIGH);

		if(pressedKey != KPD_NO_PRESSED_KEY)
        {
            break; 
        }

	}
	return pressedKey;

}
