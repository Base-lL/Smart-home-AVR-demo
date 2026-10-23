#include "FreeRTOS.h"
#include "task.h"

#include "std_types.h"
#include "bit_math.h"

#include "DIO_interface.h"
#include "TMR_interface.h"
#include "UART_Interface.h"

#include "LED_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include "MTR_interface.h"
#include "SRV_interface.h"



void SYS_mapInput(u8 u8Input);


/**
 * heartbeat function to check on system state
 */
void vSYS_HeartBeat(void *pvParameters);

/**
 * input signal success feedback
 */
void vSYS_ActionTaken(void *pvParameters);
TaskHandle_t xActionHandler = NULL;


/**
 * LCD TASK SECTION
 */
void vLCDtask(void *pvParameters);
TaskHandle_t xLCDHandler = NULL;

typedef enum LCD_PAGES{
    LCD_PAGE_Idle = 0,

    LCD_PAGE_Lights,
    LCD_PAGE_Fan,
    LCD_PAGE_Door,
    LCD_PAGE_BlueTooth,

    LCD_PAGE_Home
}LCD_Page_t;

LCD_Page_t LCDcurrentPage = LCD_PAGE_Home;

void LCD_vidSwitchToPage(LCD_Page_t copy_LCD_Page);
void LCD_vidPageIdle(void);
void LCD_vidPageHome(void);
void LCD_vidPagelights(void);
void LCD_vidPagefan(void);
void LCD_vidPageBlueTooth(void);
void LCD_vidPagedoors(void);


/*---KEYPAD TASK---*/
void vKPDtask(void *pvParameters);
TaskHandle_t xKPDHandler = NULL;

/*---Bluetooth TASK---*/
void vUARTgetInput(void *pvParamters);
TaskHandle_t xUARThandler = NULL;
u8 UARTbuffer = 0;

/*---HELPER FUNCTIONS---*/
static inline int loop_clamp(int n, int min, int max) {
    if (n > max)
    {
        n = min;
    }
    else if (n < min)
    {
        n = max;
    }
    return n;
}

/*---CONTROLLED TASKS---*/

void CTRL3_Door(u8 u8State);
void CTRL4_Fan(u8 u8State);
void CTRL5_BuzzerWarn(u8 u8State);



/*---INPUT MACROS---*/
#define BUTTON_PAGE_IDLE    1
#define BUTTON_PAGE_TOG     2
#define BUTTON_PAGE_SET     3
#define BUTTON_PAGE_CLR     4

#define BUTTON_PAGE_PREV    5
#define BUTTON_PAGE_NEXT    8
#define BUTTON_PAGE_INCR    7
#define BUTTON_PAGE_DECR    6

#define BUTTON_PAGE_CTRL1   9
#define BUTTON_PAGE_CTRL2   10
#define BUTTON_PAGE_CTRL3   11
#define BUTTON_PAGE_CTRL4   12
#define BUTTON_PAGE_CTRL5   13

/*---SYSTEM SETTINGS---*/
#define ON 1
#define OFF 1

typedef struct {
    u8 SYS_LIGHT1 : 1;
    u8 SYS_LIGHT2 : 1;
    u8 SYS_DOOR: 1;
    u8 SYS_FAN: 1;
    u8 SYS_BLUETOOTH: 1;
    u8 SYS_BUZZER: 1;
    
} SYS_Setting_t;

u8 SYS_UserName[] = "Basil";
SYS_Setting_t SystemSettingsDEF =
{
    .SYS_LIGHT1  = 1,
    .SYS_LIGHT2  = 0,
    .SYS_DOOR = 1,
    .SYS_FAN = 1,
    .SYS_BLUETOOTH = 1,
    .SYS_BUZZER = 0
};


int main(void)
{
    /*---SYSTEM INIT---*/

    //LED array pins
    LED_vidArrayInit();
    LED_vidLightSetState(LED_LIGHT1,SystemSettingsDEF.SYS_LIGHT1);
    LED_vidLightSetState(LED_LIGHT2,SystemSettingsDEF.SYS_LIGHT2);
    
    //LCD init
    LCD_vidInit();

    //Buzzer
    DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT);
    DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);
    DIO_u8SetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
    

    //KeyPad switches port
    KPD_init();            /* Task Handle */

    //Servo init
    SRV_vidInit();
    CTRL3_Door(SystemSettingsDEF.SYS_DOOR);

    // DC Motor init
    MTR_init();
    CTRL4_Fan(SystemSettingsDEF.SYS_FAN);

    //Bluetooth UART init
    UART_Init();
    
    /*---TASK CREATION---*/
    // xTaskCreate(
    //     vSYS_task,                /* Task Function */
    //     "system task",            /* Task Name (for debugging) */
    //     configMINIMAL_STACK_SIZE, /* Stack Depth (bytes on AVR) */
    //     NULL,                     /* Task Parameters */
    //     tskIDLE_PRIORITY,         /* Priority */
    //     &xSYS_Task                /* Task Handle (optional) */
    // );

    xTaskCreate(
        vLCDtask,
        "LCD main task",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY,
        &xLCDHandler
    );

    xTaskCreate(
        vSYS_HeartBeat,
        "Heart Beat",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY+1,
        NULL
    );

    xTaskCreate(
        vSYS_ActionTaken,
        "action taken",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY+2,
        &xActionHandler
    );

    xTaskCreate(
        vKPDtask,
        "keypad task",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY+3,
        &xKPDHandler
    );

    xTaskCreate(
        vUARTgetInput,
        "bluetooth",
        configMINIMAL_STACK_SIZE,
        NULL,                     
        tskIDLE_PRIORITY+3,
        &xUARThandler
    );

    xTaskNotify(xLCDHandler, 0, eSetValueWithOverwrite);

    vTaskStartScheduler();
    while (1);
    return 0;
}

void vSYS_HeartBeat(void *pvParameters)
{
    for (;;)
    {
        LED_vidLightToggle(LED_SYSTEM_STATUS);
        //DIO_u8TogglePinValue(DIO_PORTD,DIO_PIN5);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}



void vSYS_ActionTaken(void *pvParameters)
{
    (void)pvParameters;
    for(;;)
    {
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        
        /*action led flash*/
        LED_vidLightON(LED_SYSTEM_ACTION);
        DIO_u8SetPinValue(DIO_PORTD,DIO_PIN5,DIO_HIGH);
        vTaskDelay(pdMS_TO_TICKS(75));
        LED_vidLightOFF(LED_SYSTEM_ACTION);
        DIO_u8SetPinValue(DIO_PORTD,DIO_PIN5,DIO_LOW);
        vTaskDelay(pdMS_TO_TICKS(75));
    }
}


void SYS_mapInput(u8 u8Input)
{
    
    static TickType_t xLastFastTick = 0;
    static TickType_t xLastBuzTick = 0;
    static u8 lastInput = KPD_NO_PRESSED_KEY;
    static u8 DCmotorState = 0;

    TickType_t xCurrentTick = xTaskGetTickCount();

    switch (u8Input)
    {
        case BUTTON_PAGE_CTRL1:
            if(lastInput != u8Input)
            {
                SystemSettingsDEF.SYS_LIGHT1 = !SystemSettingsDEF.SYS_LIGHT1;
                LED_vidLightToggle(LED_LIGHT1);
            } 
            break;
        case BUTTON_PAGE_CTRL2:
          
                SystemSettingsDEF.SYS_LIGHT2 = !SystemSettingsDEF.SYS_LIGHT2;
                LED_vidLightToggle(LED_LIGHT2);
            
            break;
        case BUTTON_PAGE_CTRL3:
          
                CTRL3_Door(!SystemSettingsDEF.SYS_DOOR); // Can switch to STATE_ON or STATE_OFF if preferred
            
            break;

        case BUTTON_PAGE_CTRL4:
      
                CTRL4_Fan(!SystemSettingsDEF.SYS_FAN);
            break;

        case BUTTON_PAGE_CTRL5:
            CTRL5_BuzzerWarn(!SystemSettingsDEF.SYS_BUZZER);
            break;

        default:    break;
    }

    if (u8Input != KPD_NO_PRESSED_KEY)
    {
        xTaskNotify(xActionHandler, 0, eSetValueWithOverwrite);
        xTaskNotify(xLCDHandler, u8Input, eSetValueWithOverwrite);
    }
    lastInput = u8Input;
}

void vLCDtask(void *pvParameters)
{
    (void)pvParameters;
    volatile u32 inputBuffer;
    static TickType_t xLastNavTick = 0;
    LCD_vidSendString("initializing...");

    //gets notified by main when all other componenets finish their init 
    xTaskNotifyWait(0,0xFFFFFFFF,NULL,portMAX_DELAY);
    LCD_vidSendStringXY(0, 0, "Welcome!       ");
    LCD_vidSendStringXY(0, 1, "->");
    LCD_vidSendString(SYS_UserName);
    vTaskDelay(pdMS_TO_TICKS(3));
    LCD_vidSwitchToPage(LCDcurrentPage);

    for (;;)
    {
        //gets notified from the system mapinput
        xTaskNotifyWait(0,0xFFFFFFFF,&inputBuffer,portMAX_DELAY);

        TickType_t xCurrentTick = xTaskGetTickCount();

        switch (inputBuffer)
        {
            case BUTTON_PAGE_IDLE: if((xCurrentTick - xLastNavTick) > 100) 
            {
                xLastNavTick = xCurrentTick;
                LCD_vidSwitchToPage(LCD_PAGE_Idle);
                
            }   break; 
            case BUTTON_PAGE_PREV: if((xCurrentTick - xLastNavTick) > 300) 
            {
                xLastNavTick = xCurrentTick;
                LCD_vidSwitchToPage(LCDcurrentPage-1);
                
            }   break;
            case BUTTON_PAGE_NEXT:if((xCurrentTick - xLastNavTick) > 300) 
            {
                xLastNavTick = xCurrentTick;
                
                LCD_vidSwitchToPage(LCDcurrentPage+1);
                
            }   break;
            default: LCD_vidSwitchToPage(LCDcurrentPage); break;
        }
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}


void vKPDtask(void *pvParameters)
{
    for(;;)
    {
        u8 rawKey = KPD_u8GetPressedKey();                
        SYS_mapInput(rawKey);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}


void vUARTgetInput(void *pvParameters)
{
    u8 local_rxByte = 0;

    for (;;)
    {
        if (UART_u8IsDataAvailable())
        {
            local_rxByte = UART_u8ReadByteNonBlocking();

            SYS_mapInput(local_rxByte);
        }

        vTaskDelay(pdMS_TO_TICKS(20)); 
    }
}

void LCD_vidSwitchToPage(LCD_Page_t copy_LCD_Page)
{
    LCDcurrentPage = loop_clamp(copy_LCD_Page,1,LCD_PAGE_Home-1);
    LCD_vidClear();
    switch (LCDcurrentPage)
    {
        case LCD_PAGE_Idle:          LCD_vidPageIdle();      break;
        case LCD_PAGE_Lights:        LCD_vidPagelights();    break;
        case LCD_PAGE_Fan:           LCD_vidPagefan();      break;
        case LCD_PAGE_Door:          LCD_vidPagedoors();     break;
        case LCD_PAGE_BlueTooth:     LCD_vidPageBlueTooth(); break;
        default:                     LCD_vidPageIdle();      break;
    }
}

void LCD_vidPageIdle(void)
{
    /*-------------------------|-------------|---*/
    LCD_vidSendStringXY(0, 0, "in idle......");
    LCD_vidSendStringXY(0, 1, "waiting input.."); 
}

void LCD_vidPagelights(void)
{
    /*-------------------------|-------------|---*/
    LCD_vidSendStringXY(0, 0, "Lights Menu    ");
    LCD_vidSendStringXY(0, 1, "1:");
    if(SystemSettingsDEF.SYS_LIGHT1 == ON)
    {
        LCD_vidSendString("ON");
    }
    else
    {
        LCD_vidSendString("OFF");
    }

    LCD_vidSendStringXY(7, 1, "2:");
    if(SystemSettingsDEF.SYS_LIGHT2 == ON)
    {
        LCD_vidSendString("ON");
    }
    else
    {
        LCD_vidSendString("OFF");
    }

}

void LCD_vidPagefan(void)
{
    /*-------------------------|-------------|---*/
    LCD_vidSendStringXY(0, 0, "Fans Menu");
    LCD_vidSendStringXY(0, 1, "state: ");
    if(SystemSettingsDEF.SYS_FAN == ON)
    {
        LCD_vidSendString("ON");
    }
    else
    {
        LCD_vidSendString("OFF");
    }
}

void LCD_vidPagedoors(void)
{
    LCD_vidSendStringXY(0, 0, "Doors Menu");
    LCD_vidSendStringXY(0, 1, "Lock: ");
    if(SystemSettingsDEF.SYS_DOOR == ON)
    {
        LCD_vidSendString("ON");
    }
    else
    {
        LCD_vidSendString("OFF");
    }
    /*-------------------------|-------------|---*/
}

void LCD_vidPageBlueTooth(void)
{
    /*-------------------------|-------------|---*/
    LCD_vidSendStringXY(0, 0, "BlueTooth: ON");
    LCD_vidSendStringXY(0, 1, "ping? ");
    
}

/*-----CONTROL FUNCTIONS-----*/
void CTRL3_Door(u8 u8State)
{
    if (u8State == ON)
    {
        SystemSettingsDEF.SYS_DOOR = ON;
        SRV_CurrentServoAngle = SERVO_HIGH_BOUND;
    } 
    else
    {
        SystemSettingsDEF.SYS_DOOR = OFF;
        SRV_CurrentServoAngle = SERVO_LOW_BOUND;
    } 
    SRV_vidRotateServoAngle(SRV_CurrentServoAngle);
}

void CTRL4_Fan(u8 u8State)
{
    if (u8State == ON)
    {
        SystemSettingsDEF.SYS_FAN = ON;
        MTR_rotateCW();
    } 
    else
    {
        SystemSettingsDEF.SYS_FAN = OFF;
        MTR_stop();
    } 
}

void CTRL5_BuzzerWarn(u8 u8State)
{
    static TickType_t xCurrentTick=0;
    static TickType_t xLastBuzTick=0;
    
    if (u8State == ON)
    {
        xCurrentTick = xTaskGetTickCount();
        if ((xCurrentTick - xLastBuzTick) >= pdMS_TO_TICKS(50))
        {
            xLastBuzTick = xCurrentTick;
            DIO_u8TogglePinValue(DIO_PORTD, DIO_PIN5);
        }
    }
    else
    {
        xCurrentTick = 0;
        xLastBuzTick = 0;
        DIO_u8SetPinValue(DIO_PORTD, DIO_PIN5, DIO_LOW);
    }
}

#if (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook(void)
{
    // Executes when no application tasks are ready to run
}
#endif