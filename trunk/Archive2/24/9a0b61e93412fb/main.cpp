#include <cstdint>

typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t U8;

U32 processButtons(U32 toor) {
 
   U32 sw;
   static U16 swold = 0xFFFF;
   static U8 sw_rep = 0, fsw_cnt = 0;
 
   // no footswitch if no TOOR
   if (!toor) {
      fsw_cnt = 0;
   }
   // count if footswitch activated in TOOR
   else if (fsw_cnt > 0 && fsw_cnt < 3 * SPS) {
      ++fsw_cnt;
   }
 
   if ((sw = (getSwitches() & (RFON_BUTTON | FOOTSWITCH))) != 0 && sw == swold) { //error is hit on this line
      if (sw_rep != 255 && ++sw_rep == SPS / 5) {       // got a debounced and delayed hit; adjust number to increase delay
         if (!toor) {
            return sw;                                  // RF ON button or FOOTSWITCH, turn RF ON or OFF
         }
         else if (sw & FOOTSWITCH) {                    // TOOR here
            if (fsw_cnt == 0 || fsw_cnt >= 3 * SPS) {   // first time or after 3 seconds, start over
               fsw_cnt = 1;
            }
            else {
               fsw_cnt = 0;
               return FOOTSWITCH;                       // twice within 3 seconds at TOOR
            }
         }
      }
   }
   // no switch or switch changed
   else {
      // remember last switch code
      swold = sw;
      sw_rep = 0;
   }
 
   return 0;
 
} // end processButtons