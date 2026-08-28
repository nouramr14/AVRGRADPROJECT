#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdint.h>

#include "LIB/STD_Types.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/DIO/DIO_interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "MCAL/ADC/ADC_Private.h"
#include "HAL/CALLIBRATION/CALLIBRATION_Interface.h"


#define FLASH_CS            PB4
#define DAC_CS              PC7

#define BUTTON_NORMAL       PC3
#define BUTTON_TRAINING     PC4

#define HELLO_START         5856
#define WATER_START         17119
#define FOOD_START          33003
#define HELP_START          53000
#define THANK_START         58978

#define HELLO_LEN           7204
#define WATER_LEN           11363
#define FOOD_LEN            11666
#define HELP_LEN            5978
#define THANK_LEN           5978

#define EEPROM_VALID_START      0
#define EEPROM_GESTURE_START    5
#define EEPROM_MAGIC_KEY        0xBB

#define GESTURE_THRESHOLD  100
volatile uint16_t audio_addr = 0;
volatile uint16_t audio_end = 0;
volatile uint8_t playing = 0;

uint8_t Gesture_Is_Valid(uint8_t word);
uint8_t Load_Gesture(uint8_t word);

u16 ADC_Read(u8 channel)
{
    u16 Local_u16Result = 0;
    ADC_u8GetResultSync(channel, &Local_u16Result);
    return Local_u16Result;
}

static inline uint8_t SPI(uint8_t x)
{
    SPDR = x;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

void SPI_Init(void)
{
    DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7);
    DDRB &= ~(1 << PB6);
    DDRC |= (1 << DAC_CS);

    PORTB |= (1 << FLASH_CS);
    PORTC |= (1 << DAC_CS);

    SPCR = (1 << SPE) | (1 << MSTR);
    SPSR = 0;
}

void Timer_Init(void)
{
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS11);
    OCR1A = 62;
    TIMSK |= (1 << OCIE1A);
}

void Start_Audio(uint16_t start, uint16_t length)
{
    if (playing)
        return;

    audio_addr = start;
    audio_end = start + length;
    playing = 1;
}

ISR(TIMER1_COMPA_vect)
{
    uint8_t sample;
    uint16_t dac;

    if (!playing)
        return;

    if (audio_addr >= audio_end)
    {
        PORTB |= (1 << FLASH_CS);
        dac = 0x3800;
        PORTC &= ~(1 << DAC_CS);
        SPDR = (uint8_t)(dac >> 8);
        while (!(SPSR & (1 << SPIF)));
        SPDR = (uint8_t)dac;
        while (!(SPSR & (1 << SPIF)));
        PORTC |= (1 << DAC_CS);
        playing = 0;
        return;
    }

    PORTB &= ~(1 << FLASH_CS);
    SPDR = 0x03;
    while (!(SPSR & (1 << SPIF)));
    SPDR = 0x00;
    while (!(SPSR & (1 << SPIF)));
    SPDR = (uint8_t)(audio_addr >> 8);
    while (!(SPSR & (1 << SPIF)));
    SPDR = (uint8_t)audio_addr;
    while (!(SPSR & (1 << SPIF)));
    SPDR = 0x00;
    while (!(SPSR & (1 << SPIF)));
    sample = SPDR;
    PORTB |= (1 << FLASH_CS);

    dac = 0x3000 | ((uint16_t)sample << 4);

    PORTC &= ~(1 << DAC_CS);
    SPDR = (uint8_t)(dac >> 8);
    while (!(SPSR & (1 << SPIF)));
    SPDR = (uint8_t)dac;
    while (!(SPSR & (1 << SPIF)));
    PORTC |= (1 << DAC_CS);

    audio_addr++;
}



uint8_t Read_Gesture(void)
{
    uint8_t gesture = 0;

    u16 current;

    u16 difference;


    current = ADC_Read(ADC_CHANNEL_0);

    difference =
        (current > Calibration_Baseline[0]) ?
        (current - Calibration_Baseline[0]) :
        (Calibration_Baseline[0] - current);

    if (difference > GESTURE_THRESHOLD)
        gesture |= (1 << 0);



    current = ADC_Read(ADC_CHANNEL_1);

    difference =
        (current > Calibration_Baseline[1]) ?
        (current - Calibration_Baseline[1]) :
        (Calibration_Baseline[1] - current);

    if (difference > GESTURE_THRESHOLD)
        gesture |= (1 << 1);



    current = ADC_Read(ADC_CHANNEL_2);

    difference =
        (current > Calibration_Baseline[2]) ?
        (current - Calibration_Baseline[2]) :
        (Calibration_Baseline[2] - current);

    if (difference > GESTURE_THRESHOLD)
        gesture |= (1 << 2);



    current = ADC_Read(ADC_CHANNEL_3);

    difference =
        (current > Calibration_Baseline[3]) ?
        (current - Calibration_Baseline[3]) :
        (Calibration_Baseline[3] - current);

    if (difference > GESTURE_THRESHOLD)
        gesture |= (1 << 3);



    current = ADC_Read(ADC_CHANNEL_4);

    difference =
        (current > Calibration_Baseline[4]) ?
        (current - Calibration_Baseline[4]) :
        (Calibration_Baseline[4] - current);

    if (difference > GESTURE_THRESHOLD)
        gesture |= (1 << 4);


    return gesture;
}

uint8_t Gesture_Is_Valid(uint8_t word)
{
    if (EEPROM_Read(EEPROM_VALID_START + word) == EEPROM_MAGIC_KEY)
    {
        return 1;
    }
    return 0;
}

uint8_t Load_Gesture(uint8_t word)
{
    return EEPROM_Read(EEPROM_GESTURE_START + word);
}

void Save_Gesture(uint8_t word, uint8_t gesture)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        if (Gesture_Is_Valid(i) && (Load_Gesture(i) == gesture))
        {
            EEPROM_Write(EEPROM_VALID_START + i, 0x00);
        }
    }

    EEPROM_Write(EEPROM_GESTURE_START + word, gesture);
    EEPROM_Write(EEPROM_VALID_START + word, EEPROM_MAGIC_KEY);
}

void Play_Word(uint8_t word)
{
    LCD_Send_Command(lcd_Clear);

    if (word == 0)
    {
        LCD_GoTo(1, 1);
        LCD_Send_String((u8*)"Hello");
        Start_Audio(HELLO_START, HELLO_LEN);
    }
    else if (word == 1)
    {
        LCD_GoTo(1, 1);
        LCD_Send_String((u8*)"I need water");
        Start_Audio(WATER_START, WATER_LEN);
    }
    else if (word == 2)
    {
        LCD_GoTo(1, 1);
        LCD_Send_String((u8*)"I need food");
        Start_Audio(FOOD_START, FOOD_LEN);
    }
    else if (word == 3)
    {
        LCD_GoTo(1, 1);
        LCD_Send_String((u8*)"Help");
        Start_Audio(HELP_START, HELP_LEN);
    }
    else if (word == 4)
    {
        LCD_GoTo(1, 1);
        LCD_Send_String((u8*)"Thank you");
        Start_Audio(THANK_START, THANK_LEN);
    }
}

uint8_t Old_Normal_Finger(void)
{
    if (ADC_Read(ADC_CHANNEL_0) > 500) return 0;
    if (ADC_Read(ADC_CHANNEL_1) > 500) return 1;
    if (ADC_Read(ADC_CHANNEL_2) > 500) return 2;
    if (ADC_Read(ADC_CHANNEL_3) > 500) return 3;
    if (ADC_Read(ADC_CHANNEL_4) > 500) return 4;

    return 255;
}

void Normal_Mode(void)
{
    uint8_t gesture;
    uint8_t last_gesture = 255;
    uint8_t finger;
    uint8_t last_finger = 255;
    uint8_t word;
    uint8_t found;

    while (!(PINC & (1 << BUTTON_NORMAL)))
    {
        _delay_ms(10);
    }

    LCD_Send_Command(lcd_Clear);
    LCD_GoTo(1, 1);
    LCD_Send_String((u8*)"NORMAL MODE");
    LCD_GoTo(2, 1);
    LCD_Send_String((u8*)"READY...");
    _delay_ms(1000);

    LCD_Send_Command(lcd_Clear);

    while (1)
    {
        gesture = Read_Gesture();
        found = 0;

        for (word = 0; word < 5; word++)
        {
            if (Gesture_Is_Valid(word))
            {
                if (gesture == Load_Gesture(word))
                {
                    found = 1;

                    if (gesture != last_gesture)
                    {
                        last_gesture = gesture;
                        last_finger = 255;

                        while (playing);

                        Play_Word(word);
                    }
                    break;
                }
            }
        }

        if (!found)
        {
            finger = Old_Normal_Finger();

            if (finger == 255)
            {
                last_finger = 255;
                last_gesture = 255;
            }
            else if (finger != last_finger)
            {
                last_finger = finger;
                last_gesture = 255;

                while (playing);

                Play_Word(finger);
            }
        }

        _delay_ms(30);
    }
}

void Show_Word(uint8_t word)
{
    LCD_Send_Command(lcd_Clear);
    LCD_GoTo(1, 1);
    LCD_Send_String((u8*)"SELECT WORD");
    LCD_GoTo(2, 1);

    if (word == 0) LCD_Send_String((u8*)"Hello");
    else if (word == 1) LCD_Send_String((u8*)"I need water");
    else if (word == 2) LCD_Send_String((u8*)"I need food");
    else if (word == 3) LCD_Send_String((u8*)"Help");
    else if (word == 4) LCD_Send_String((u8*)"Thank you");
}

void Train_Word(uint8_t word)
{
    uint8_t gesture;

    LCD_Send_Command(lcd_Clear);
    LCD_GoTo(1, 1);
    LCD_Send_String((u8*)"TRAIN");
    LCD_GoTo(2, 1);

    if (word == 0) LCD_Send_String((u8*)"Hello");
    else if (word == 1) LCD_Send_String((u8*)"I need water");
    else if (word == 2) LCD_Send_String((u8*)"I need food");
    else if (word == 3) LCD_Send_String((u8*)"Help");
    else if (word == 4) LCD_Send_String((u8*)"Thank you");

    _delay_ms(800);

    LCD_Send_Command(lcd_Clear);
    LCD_GoTo(1, 1);
    LCD_Send_String((u8*)"MAKE GESTURE");
    LCD_GoTo(2, 1);
    LCD_Send_String((u8*)"B2 = SAVE");

    while (1)
    {
        gesture = Read_Gesture();

        if (!(PINC & (1 << BUTTON_TRAINING)))
        {
            _delay_ms(50);

            if (!(PINC & (1 << BUTTON_TRAINING)))
            {
                LCD_Send_Command(lcd_Clear);
                LCD_GoTo(1, 1);
                LCD_Send_String((u8*)"SAVING...");

                Save_Gesture(word, gesture);

                LCD_GoTo(1, 1);
                LCD_Send_String((u8*)"SAVED!    ");

                while (!(PINC & (1 << BUTTON_TRAINING)))
                {
                    _delay_ms(10);
                }

                _delay_ms(800);
                return;
            }
        }

        _delay_ms(20);
    }
}

uint8_t Train_Another(void)
{
    LCD_Send_Command(lcd_Clear);
    LCD_GoTo(1, 1);
    LCD_Send_String((u8*)"TRAIN ANOTHER?");
    LCD_GoTo(2, 1);
    LCD_Send_String((u8*)"B1 YES B2 NO");

    _delay_ms(400);

    while (1)
    {
        if (!(PINC & (1 << BUTTON_NORMAL)))
        {
            _delay_ms(50);
            if (!(PINC & (1 << BUTTON_NORMAL)))
            {
                while (!(PINC & (1 << BUTTON_NORMAL)))
                {
                    _delay_ms(10);
                }
                return 1;
            }
        }

        if (!(PINC & (1 << BUTTON_TRAINING)))
        {
            _delay_ms(50);
            if (!(PINC & (1 << BUTTON_TRAINING)))
            {
                while (!(PINC & (1 << BUTTON_TRAINING)))
                {
                    _delay_ms(10);
                }
                return 0;
            }
        }

        _delay_ms(20);
    }
}

void Training_Mode(void)
{
    uint8_t word = 0;
    uint8_t another;

    while (!(PINC & (1 << BUTTON_TRAINING)))
    {
        _delay_ms(10);
    }

    Show_Word(word);

    while (1)
    {
        if (!(PINC & (1 << BUTTON_NORMAL)))
        {
            _delay_ms(50);

            if (!(PINC & (1 << BUTTON_NORMAL)))
            {
                while (!(PINC & (1 << BUTTON_NORMAL)))
                {
                    _delay_ms(10);
                }

                word++;
                if (word >= 5)
                    word = 0;

                Show_Word(word);
            }
        }

        if (!(PINC & (1 << BUTTON_TRAINING)))
        {
            _delay_ms(50);

            if (!(PINC & (1 << BUTTON_TRAINING)))
            {
                Train_Word(word);

                another = Train_Another();

                if (another == 1)
                {
                    word = 0;
                    Show_Word(word);
                }
                else
                {
                    LCD_Send_Command(lcd_Clear);
                    return;
                }
            }
        }

        _delay_ms(20);
    }
}

void Mode_Menu(void)
{
    LCD_Send_Command(lcd_Clear);
    LCD_GoTo(1, 1);
    LCD_Send_String((u8*)"SELECT MODE");
    LCD_GoTo(2, 1);
    LCD_Send_String((u8*)"1=NORMAL 2=TRAIN");
}

int main(void)
{
    MCUCSR |= (1 << JTD);
    MCUCSR |= (1 << JTD);

    SPI_Init();
    ADC_voidInit();
    LCD_Init();
    Timer_Init();

    DDRC &= ~(1 << BUTTON_NORMAL);
    PORTC |= (1 << BUTTON_NORMAL);

    DDRC &= ~(1 << BUTTON_TRAINING);
    PORTC |= (1 << BUTTON_TRAINING);

    DDRC |= (1 << DAC_CS);
    PORTC |= (1 << DAC_CS);

    sei();

    while (1)
    {
        Mode_Menu();

        while (1)
        {
            if (!(PINC & (1 << BUTTON_NORMAL)))
            {
                _delay_ms(50);

                if (!(PINC & (1 << BUTTON_NORMAL)))
                {
                    Normal_Mode();
                    break;
                }
            }

            if (!(PINC & (1 << BUTTON_TRAINING)))
            {
                _delay_ms(50);

                if (!(PINC & (1 << BUTTON_TRAINING)))
                {
                    Training_Mode();
                    break;
                }
            }

            _delay_ms(20);
        }
    }
    if (Calibration_Is_Valid())
    {
        Load_Calibration();
    }
    else
    {
        Start_Calibration();

        Save_Calibration();
    }
}
