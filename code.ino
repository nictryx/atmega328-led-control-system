#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED1 PC3
#define LED2 PC2
#define LED3 PB1

#define SW1 PD2
#define SW2 PD3
#define SW3 PD1

#define POT PC0

volatile uint8_t led1On = 0;
volatile uint8_t led2On = 0;
volatile uint8_t pwmCounter = 0;

ISR(INT0_vect)
{
    led1On = !(PIND & (1 << SW1));
}

ISR(INT1_vect)
{
    led2On = !(PIND & (1 << SW2));
}

ISR(TIMER2_COMPA_vect)
{
    pwmCounter++;

    if (pwmCounter >= 100)
        pwmCounter = 0;

    uint8_t dimMode = !(PIND & (1 << SW3));
    uint8_t brightness = dimMode ? 35 : 100;

    if (led1On && pwmCounter < brightness)
        PORTC |= (1 << LED1);
    else
        PORTC &= ~(1 << LED1);

    if (led2On && pwmCounter < brightness)
        PORTC |= (1 << LED2);
    else
        PORTC &= ~(1 << LED2);
}

void initADC()
{
    ADMUX = (1 << REFS0);

    ADCSRA =
        (1 << ADEN) |
        (1 << ADPS2) |
        (1 << ADPS1) |
        (1 << ADPS0);
}

uint16_t readADC()
{
    ADMUX = (ADMUX & 0xF0) | 0;

    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));

    return ADC;
}

void initPWM()
{
    DDRB |= (1 << LED3);

    TCCR1A =
        (1 << COM1A1) |
        (1 << WGM10);

    TCCR1B =
        (1 << WGM12) |
        (1 << CS11);

    OCR1A = 0;
}

void initTimer2()
{
    TCCR2A = (1 << WGM21);

    TCCR2B =
        (1 << CS22);

    OCR2A = 24;

    TIMSK2 = (1 << OCIE2A);
}

void initInputs()
{
    DDRD &= ~(
        (1 << SW1) |
        (1 << SW2) |
        (1 << SW3)
    );

    PORTD |=
        (1 << SW1) |
        (1 << SW2) |
        (1 << SW3);

    EICRA =
        (1 << ISC00) |
        (1 << ISC10);

    EIMSK =
        (1 << INT0) |
        (1 << INT1);
}

int main(void)
{
    DDRC |=
        (1 << LED1) |
        (1 << LED2);

    DDRC &= ~(1 << POT);

    initInputs();
    initADC();
    initPWM();
    initTimer2();

    led1On = !(PIND & (1 << SW1));
    led2On = !(PIND & (1 << SW2));

    sei();

    while (1)
    {
        uint16_t adcValue = readADC();

        OCR1A = adcValue >> 2;
    }

    return 0;
}
