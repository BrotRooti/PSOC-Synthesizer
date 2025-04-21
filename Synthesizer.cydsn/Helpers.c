/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
#include "project.h"
#include "Helpers.h"

//                        c'=0                  d'=1             e'=2                f'=3            g'=4                a'=5            h'=6                c''=7             d''=8           e''=9            f''=10         g''=11            a''=12
int tones[13][4] = {{1515,757,378,189},{1346,673,336,168},{1204,602,301,150},{1130,565,282,141},{1005,502,251,125},{905,452,226,113},{808,404,202,101},{754,377,188,94},{673,336,168,84},{602,301,150,75},{565,282,141,71},{502,251,125,63},{452,226,113,57}};


void playTone(int tone,int time){
    WaveDAC8_1_Wave1Setup(WaveDAC8_1_SINE_WAVE,tones[tone][0]);
    WaveDAC8_2_Wave1Setup(WaveDAC8_2_SINE_WAVE,tones[tone][1]);
    WaveDAC8_3_Wave1Setup(WaveDAC8_3_SINE_WAVE,tones[tone][2]);
    WaveDAC8_4_Wave1Setup(WaveDAC8_4_SINE_WAVE,tones[tone][3]);
    CyDelay(time);
}

void sleep_DACs(int time){
    WaveDAC8_1_Stop();
    WaveDAC8_2_Stop();
    WaveDAC8_3_Stop();
    WaveDAC8_4_Stop();
    CyDelay(time);
    WaveDAC8_1_Start();
    WaveDAC8_2_Start();
    WaveDAC8_3_Start();
    WaveDAC8_4_Start();
}

/*
void fade_out(){
    WaveDAC8_1_
}
*/

void init_dacs(){
    WaveDAC8_1_Init();
    WaveDAC8_2_Init();
    WaveDAC8_3_Init();
    WaveDAC8_4_Init();
}