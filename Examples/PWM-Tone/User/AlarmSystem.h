/*
 * AlarmSystem.h
 *
 *  Created on: 06-Sept-2024
 *      Author: chowdarymanyam
 */

#ifndef USER_ALARMSYSTEM_H_
#define USER_ALARMSYSTEM_H_


#define SYSTEM_CLOCK 48000000  // System clock frequency in Hz (e.g., 48MHz)
#define TONE_DURATION 200      // Duration of each tone in milliseconds

// Define frequencies for the alarm tone pattern
#define ALARM_FREQ_HIGH 3000   // High tone frequency in Hz (e.g., 3kHz)
#define ALARM_FREQ_LOW 1500    // Low tone frequency in Hz (e.g., 1.5kHz)


void Timer_Configuration(uint16_t frequency)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    uint16_t timerPeriod = (SYSTEM_CLOCK / frequency) - 1;  // Calculate timer period for desired frequency

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   // Enable clock for Timer 1

    // Set the timer for the desired frequency
    TIM_TimeBaseInitStructure.TIM_Period = timerPeriod;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;           // No prescaler
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);    // Initialize the timer

    // Configure Timer Output Compare for PWM mode
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;      // PWM mode 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = timerPeriod / 2;       // 50% duty cycle
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);               // Initialize the timer output compare

    TIM_CtrlPWMOutputs(TIM1, ENABLE);                      // Enable PWM output
    TIM_Cmd(TIM1, ENABLE);                                 // Enable the timer
}

void Delay_Milliseconds(uint16_t milliseconds)
{
    // Implement a delay function according to your system's clock
    uint32_t count = (SYSTEM_CLOCK / 1000) * milliseconds / 8;  // Adjust loop count based on system clock
    while (count--)
    {
        __asm("nop");  // Assembly NOP instruction for delay
    }
}




void Play_Alarm_Tone_Jingle_Bells(void)
{
    int melody[] = { 264, 264, 264, 264, 264, 264, 0,
                     264, 264, 264, 264, 264, 264, 0,
                     264, 264, 264, 320, 296, 264, 0,
                     264, 264, 264, 264, 264, 264, 0 };

    int duration = 200; // Duration for each note

    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++)
    {
        Timer_Configuration(melody[i]);
        Delay_Milliseconds(duration);
    }
}




void Play_Alarm_Tone_DJHappy_Birthday(void)
{
    uint16_t frequencies[] = {
        264, 264, 296, 264, 320, 296, 0, // Happy Birthday to you
        264, 264, 296, 264, 320, 296, 0, // Happy Birthday to you
        264, 264, 396, 352, 320, 296, 0, // Happy Birthday dear [Name]
        384, 384, 352, 320, 320, 296, 0  // Happy Birthday to you
    };

    uint16_t durations[] = {
        300, 300, 600, 300, 300, 600, 0, // Durations for the first line
        300, 300, 600, 300, 300, 600, 0, // Durations for the second line
        300, 300, 600, 300, 300, 600, 0, // Durations for the third line
        300, 300, 600, 300, 300, 600, 0  // Durations for the fourth line
    };

    for (int i = 0; i < sizeof(frequencies) / sizeof(frequencies[0]); i++)
    {
        if (frequencies[i] == 0)
        {
            Delay_Milliseconds(durations[i]); // Rest
        }
        else
        {
            // Gradually increase to the note frequency
            for (uint16_t freq = 0; freq <= frequencies[i]; freq += 10)
            {
                Timer_Configuration(freq);
                Delay_Milliseconds(2); // Short delay for a smooth transition
            }

            Delay_Milliseconds(durations[i]); // Hold the note

            // Gradually decrease from the note frequency to silence
            for (uint16_t freq = frequencies[i]; freq > 0; freq -= 10)
            {
                Timer_Configuration(freq);
                Delay_Milliseconds(2); // Short delay for a smooth transition
            }
        }
    }
}


void Play_Alarm_Tone_Happy_Birthday(void)
{
    uint16_t frequencies[] = {
        1275, 1275, 1432, 1275, 1615, 1600, 0,   // "Happy Birthday to you"
        1275, 1275, 1432, 1275, 2130, 1915, 0,   // "Happy Birthday to you"
        1275, 1275, 2550, 2130, 1915, 1700, 1432, // "Happy Birthday dear [Name]"
        1700, 1700, 2130, 1915, 2240, 1915       // "Happy Birthday to you"
    };

    uint16_t durations[] = {
        300, 300, 500, 500, 500, 700, 300,       // First line
        300, 300, 500, 500, 500, 700, 300,       // Second line
        300, 300, 500, 500, 500, 500, 700,       // Third line
        300, 300, 500, 500, 500, 800             // Fourth line
    };

    for (int i = 0; i < sizeof(frequencies) / sizeof(frequencies[0]); i++)
    {
        if (frequencies[i] == 0)
        {
            Timer_Configuration(0);              // Rest
        }
        else
        {
            Timer_Configuration(frequencies[i]); // Play the note
        }
        Delay_Milliseconds(durations[i]);        // Hold each note for the duration
    }
    Timer_Configuration(0); // Turn off the buzzer at the end
}



/*The code alternates between two frequencies (ALARM_FREQ_HIGH and ALARM_FREQ_LOW) to create a dynamic alarm tone.*/
void Play_Alarm_Tone(void)
{
    while (1)
    {
        Timer_Configuration(ALARM_FREQ_HIGH);  // Set high frequency
        Delay_Milliseconds(TONE_DURATION);     // Delay for tone duration

        Timer_Configuration(ALARM_FREQ_LOW);   // Set low frequency
        Delay_Milliseconds(TONE_DURATION);     // Delay for tone duration
    }
}

/*Fast Beeping Pattern
This pattern uses a fast alternation between two frequencies, creating a rapid beeping sound often used in warning systems.*/
void Play_Alarm_Tone_Fast_Beep(void)
{
    while (1)
    {
        Timer_Configuration(3500);  // High frequency (3.5 kHz)
        Delay_Milliseconds(100);    // Short delay for a quick beep

        Timer_Configuration(1000);  // Low frequency (1 kHz)
        Delay_Milliseconds(100);    // Short delay for a quick beep
    }
}


/*Gradual Increase and Decrease Pattern
This pattern simulates a siren-like effect by gradually increasing and then decreasing the frequency, creating a more dramatic sound.*/
void Play_Alarm_Tone_Siren(void)
{
    uint16_t freq;
    while (1)
    {
        // Gradually increase frequency from 500 Hz to 4000 Hz
        for (freq = 500; freq <= 4000; freq += 100)
        {
            Timer_Configuration(freq);
            Delay_Milliseconds(20);  // Short delay for smooth frequency transition
        }

        // Gradually decrease frequency from 4000 Hz to 500 Hz
        for (freq = 4000; freq >= 500; freq -= 100)
        {
            Timer_Configuration(freq);
            Delay_Milliseconds(20);  // Short delay for smooth frequency transition
        }
    }
}


/*Slow Alternating Beep Pattern
This pattern creates a slower alternation between two frequencies, producing a slower warning beep.*/
void Play_Alarm_Tone_Slow_Beep(void)
{
    while (1)
    {
        Timer_Configuration(2500);  // High frequency (2.5 kHz)
        Delay_Milliseconds(400);    // Longer delay for slower beep

        Timer_Configuration(800);   // Low frequency (800 Hz)
        Delay_Milliseconds(400);    // Longer delay for slower beep
    }
}


/*Three-Note Alarm Pattern
This pattern uses three different tones in quick succession, creating a recognizable three-note alarm sound.*/
void Play_Alarm_Tone_Three_Note(void)
{
    while (1)
    {
        Timer_Configuration(1200);  // Tone 1 (1.2 kHz)
        Delay_Milliseconds(150);    // Short delay for the first note

        Timer_Configuration(1800);  // Tone 2 (1.8 kHz)
        Delay_Milliseconds(150);    // Short delay for the second note

        Timer_Configuration(1500);  // Tone 3 (1.5 kHz)
        Delay_Milliseconds(150);    // Short delay for the third note

        Delay_Milliseconds(300);    // Pause between cycles
    }
}


/*Continuous Increasing Pattern
This pattern continuously increases the frequency, producing an escalating alarm sound that doesn't loop back, useful for escalating warning signals.*/
void Play_Alarm_Tone_Continuous_Increase(void)
{
    uint16_t freq = 500;  // Start frequency
    while (1)
    {
        Timer_Configuration(freq);  // Set the current frequency
        Delay_Milliseconds(50);     // Short delay for each step
        freq += 100;                // Gradually increase frequency
        if (freq > 5000)            // Reset frequency to prevent going too high
            freq = 500;
    }
}


/*Random Alarm Pattern
This pattern uses random frequencies to create an unpredictable alarm sound, which can be more attention-grabbing.*/
void Play_Alarm_Tone_Random(void)
{
    while (1)
    {
        uint16_t randomFreq = (rand() % 4000) + 500;  // Generate a random frequency between 500 Hz and 4500 Hz
        Timer_Configuration(randomFreq);
        Delay_Milliseconds(200);  // Random tone duration
    }
}


/*High-Low Alternating Siren
This pattern alternates between a high and low frequency, mimicking a typical vehicle alarm siren.*/
void Play_Alarm_Tone_High_Low_Siren(void)
{
    while (1)
    {
        Timer_Configuration(4000);  // High frequency (4 kHz)
        Delay_Milliseconds(200);    // Hold high frequency for 200ms

        Timer_Configuration(1000);  // Low frequency (1 kHz)
        Delay_Milliseconds(200);    // Hold low frequency for 200ms
    }
}



/*Wailing Siren
This pattern gradually increases and decreases the frequency, creating a "wailing" sound that is often used in police or ambulance sirens.*/
void Play_Alarm_Tone_Wailing_Siren(void)
{
    uint16_t freq;
    while (1)
    {
        // Increase frequency from 800 Hz to 4000 Hz
        for (freq = 800; freq <= 4000; freq += 100)
        {
            Timer_Configuration(freq);
            Delay_Milliseconds(50);  // Short delay for a wailing effect
        }

        // Decrease frequency from 4000 Hz to 800 Hz
        for (freq = 4000; freq >= 800; freq -= 100)
        {
            Timer_Configuration(freq);
            Delay_Milliseconds(50);  // Short delay for a wailing effect
        }
    }
}



/*Rapid Pulsing Alarm
This pattern generates a rapid, pulsing sound that can create a sense of urgency.*/
void Play_Alarm_Tone_Rapid_Pulse(void)
{
    while (1)
    {
        Timer_Configuration(3000);  // Frequency (3 kHz)
        Delay_Milliseconds(100);    // Short burst

        Timer_Configuration(0);     // Silence
        Delay_Milliseconds(100);    // Short silence

        Timer_Configuration(3000);  // Frequency (3 kHz)
        Delay_Milliseconds(100);    // Short burst

        Timer_Configuration(0);     // Silence
        Delay_Milliseconds(300);    // Longer silence
    }
}


/*Distress Signal Pattern
This pattern emits a series of short beeps followed by a longer pause, mimicking an SOS-like distress signal.*/
void Play_Alarm_Tone_Distress_Signal(void)
{
    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            Timer_Configuration(2500);  // Frequency (2.5 kHz)
            Delay_Milliseconds(100);    // Short beep
            Timer_Configuration(0);     // Silence
            Delay_Milliseconds(100);    // Short pause
        }

        Delay_Milliseconds(500);        // Longer pause between sequences
    }
}



/*Continuous Modulated Siren
This pattern creates a continuously modulated sound with a random component to make the alarm less predictable and more attention-grabbing.*/
void Play_Alarm_Tone_Modulated_Siren(void)
{
    uint16_t freq;
    while (1)
    {
        freq = (rand() % 3000) + 1000;  // Random frequency between 1 kHz and 4 kHz
        Timer_Configuration(freq);
        Delay_Milliseconds(100);        // Short delay for modulation effect

        freq = (rand() % 3000) + 1000;  // Another random frequency
        Timer_Configuration(freq);
        Delay_Milliseconds(100);        // Short delay for modulation effect
    }
}



/*Aggressive Beep Pattern
This pattern creates a sharp, aggressive sound by using very short bursts of high frequencies.*/
void Play_Alarm_Tone_Aggressive_Beep(void)
{
    while (1)
    {
        Timer_Configuration(4500);  // High frequency (4.5 kHz)
        Delay_Milliseconds(50);     // Very short burst

        Timer_Configuration(0);     // Silence
        Delay_Milliseconds(50);     // Short pause

        Timer_Configuration(4500);  // High frequency (4.5 kHz)
        Delay_Milliseconds(50);     // Very short burst

        Delay_Milliseconds(200);    // Longer silence to create urgency
    }
}



/*S.O.S. Alarm Tone
 Here's a code snippet to create an S.O.S. (Save Our Souls) alarm pattern, which is widely recognized as a distress signal. The S.O.S. pattern consists of three short signals, three long signals, and three short signals in Morse code.*/
void Play_Alarm_Tone_SOS(void)
{
    while (1)
    {
        // Three short beeps (S)
        for (int i = 0; i < 3; i++)
        {
            Timer_Configuration(2500);  // Frequency (2.5 kHz)
            Delay_Milliseconds(100);    // Short beep (100 ms)
            Timer_Configuration(0);     // Silence
            Delay_Milliseconds(100);    // Short pause (100 ms)
        }

        // Three long beeps (O)
        for (int i = 0; i < 3; i++)
        {
            Timer_Configuration(2500);  // Frequency (2.5 kHz)
            Delay_Milliseconds(300);    // Long beep (300 ms)
            Timer_Configuration(0);     // Silence
            Delay_Milliseconds(100);    // Short pause (100 ms)
        }

        // Three short beeps (S)
        for (int i = 0; i < 3; i++)
        {
            Timer_Configuration(2500);  // Frequency (2.5 kHz)
            Delay_Milliseconds(100);    // Short beep (100 ms)
            Timer_Configuration(0);     // Silence
            Delay_Milliseconds(100);    // Short pause (100 ms)
        }

        // Pause between repetitions of the SOS signal
        Delay_Milliseconds(1000);        // Long pause (1 second) between SOS repetitions
    }
}





#endif /* USER_ALARMSYSTEM_H_ */
