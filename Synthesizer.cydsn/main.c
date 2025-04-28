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
#include "project.h"
#include <math.h>
#include "Music_Pieces.h"
#include "Helpers.h"




void play_Pice(int pice_id){
    switch (pice_id){
        case 0: Narcotic(); break;
        case 1: Never_Gonna_Give(); break;
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    WaveDAC8_1_Start();
    WaveDAC8_2_Start();
    WaveDAC8_3_Start();
    WaveDAC8_4_Start();
    //CyDelay(3000);
    //WaveDAC8_1_Wave2Setup(WaveDAC8_1_SINE_WAVE,800);
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        if (B1_Read()==0) play_Pice(0);
        else if (B2_Read()==0) play_Pice(1);
        sleep_DACs(3000);
        /*
        count = count + direction;
        if (count==8){ direction = -1; count = 7;}
        else if (count==-1){ direction = 1; count = 0;}
        */
       
    }
}

/* [] END OF FILE */
