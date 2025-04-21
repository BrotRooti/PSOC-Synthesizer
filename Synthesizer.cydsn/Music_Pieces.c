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
#include <math.h>
#include "project.h"

#include "Music_Pieces.h"
#include "Helpers.h"

int idle_sleep = 10;
void play_Narcotic(){
    init_dacs();
    
    int bpm = 102;
    //int viertel = round(60/bpm*1000);
    int viertel = 450;
    int achtel = round(viertel/2);
    int sechsentel = round(viertel/4);
    
    playTone(1,achtel);
    sleep_DACs(idle_sleep);
    playTone(2,achtel);
    playTone(1,achtel);
    sleep_DACs(idle_sleep);
    playTone(2,achtel);
    playTone(1,achtel);
    sleep_DACs(idle_sleep);
    playTone(2,achtel);
    playTone(1,sechsentel);
    playTone(3,sechsentel);
    playTone(3,achtel);
    playTone(2,achtel);
    sleep_DACs(idle_sleep);
    playTone(3,achtel);
    playTone(2,achtel);
    sleep_DACs(idle_sleep);
    playTone(3,achtel);
    playTone(2,achtel);
    sleep_DACs(idle_sleep);
    playTone(3,achtel);
    playTone(4,sechsentel);
    playTone(5,sechsentel);
    playTone(5,achtel);
    playTone(4,achtel);
    sleep_DACs(idle_sleep);
    playTone(5,achtel);
    playTone(4,achtel);
    sleep_DACs(idle_sleep);
    playTone(5,achtel);
    playTone(4,achtel);
    sleep_DACs(idle_sleep);
    playTone(5,achtel);
    playTone(4,sechsentel);
    playTone(2,sechsentel);
    playTone(2,achtel);
    playTone(1,achtel);
    sleep_DACs(idle_sleep);
    playTone(2,achtel);
    playTone(1,achtel);
    sleep_DACs(idle_sleep);
    //
    playTone(2,viertel);
    playTone(3,viertel);
    playTone(2,viertel);
    //
    for (int rep=0; rep <2; rep++){
    if (rep == 1) sleep_DACs(viertel);
    sleep_DACs(achtel);
    playTone(4,sechsentel);
    playTone(7,sechsentel);
    sleep_DACs(idle_sleep);
    playTone(9,achtel);
    playTone(9,achtel);
    sleep_DACs(idle_sleep);
    playTone(8,achtel);
    playTone(7,sechsentel);
    playTone(8,sechsentel);
    playTone(8,viertel);
    sleep_DACs(achtel);
    playTone(9,achtel);
    sleep_DACs(idle_sleep);
    playTone(10,achtel);
    playTone(9,sechsentel);
    playTone(10,sechsentel);
    playTone(10,sechsentel);
    playTone(9,sechsentel);
    playTone(8,achtel);
    sleep_DACs(idle_sleep);
    playTone(7,viertel);
    //
    sleep_DACs(achtel);
    playTone(7,achtel);
    sleep_DACs(idle_sleep);
    playTone(7,achtel);
    playTone(5,achtel);
    sleep_DACs(idle_sleep);
    playTone(7,achtel);
    playTone(8,sechsentel);
    playTone(9,sechsentel);
    playTone(9,viertel);
    //
    sleep_DACs(viertel*3);
    //
    sleep_DACs(viertel);
    sleep_DACs(achtel);
    playTone(4,sechsentel);
    playTone(7,sechsentel);
    sleep_DACs(idle_sleep);
    playTone(9,achtel);
    playTone(9,achtel);
    sleep_DACs(idle_sleep);
    playTone(8,achtel);
    playTone(7,sechsentel);
    playTone(8,sechsentel);
    playTone(8,viertel);
    sleep_DACs(achtel);
    playTone(9,achtel);
    sleep_DACs(idle_sleep);
    playTone(10,achtel);
    playTone(9,sechsentel);
    playTone(10,sechsentel);
    playTone(10,sechsentel);
    playTone(9,sechsentel);
    playTone(8,achtel);
    sleep_DACs(idle_sleep);
    for (int i=0;i<6;i++){
        playTone(7,achtel);
        if (i==3) sleep_DACs(idle_sleep);
        sleep_DACs(3);
    }
    playTone(10,achtel);
    playTone(9,achtel);
    sleep_DACs(idle_sleep);
    playTone(7,viertel);
    //
    if (rep==0) sleep_DACs(viertel*3);
    //
    }
    
    
    
   
}

