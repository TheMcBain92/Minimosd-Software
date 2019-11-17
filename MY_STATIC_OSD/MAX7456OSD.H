/*
 ==============================================================================================================================
 Defines for the MAX7456 OSD Device.
 Datasheet : http://www.maximintegrated.com/datasheet/index.mvp/id/5516
  
 20/5/2014 -  Added ROW Brightness Registers
 
 ===============================================================================================================================
*/

// I/O Pins on Minim OSD
#define DATAOUT 11	        // MOSI
#define DATAIN  12	        // MISO
#define SPICLOCK 13	        // SCK
#define MAX7456SELECT 6         // SS 
#define MAX7456RESET 10    
#define VSYNC 2                 // PD2 INT0 NOT USED

//MAX7456 opcodes
#define DMM_reg   0x04	        // Datasheet page 28 	
#define DMAH_reg  0x05          //      "    page 31		
#define DMAL_reg  0x06          //      "    page 31
#define DMDI_reg  0x07          //      "    page 32 
#define VM0_reg   0x00          //      "    page 25
#define VM1_reg   0x01          //      "    page 26  
#define HOS_WRITE_ADDR   0x02   //      "    page 26
#define VOS_WRITE_ADDR   0x03   //      "    page 27

// video mode register 0 bits
#define VIDEO_BUFFER_DISABLE 0x01
#define MAX7456_RESET 0x02
#define VERTICAL_SYNC_NEXT_VSYNC 0x04
#define OSD_ENABLE 0x48		// 16/5/2014
#define SYNC_MODE_AUTO 0x00
#define SYNC_MODE_INTERNAL 0x30    
#define SYNC_MODE_EXTERNAL 0x20
#define VIDEO_MODE_PAL 0x40
#define VIDEO_MODE_NTSC 0x00

// video mode register 1 bits
// duty cycle is on_off
#define BLINK_DUTY_CYCLE_50_50 0x00
#define BLINK_DUTY_CYCLE_33_67 0x01
#define BLINK_DUTY_CYCLE_25_75 0x02
#define BLINK_DUTY_CYCLE_75_25 0x03

// Blinking time
#define BLINK_TIME_0 0x00            //  33ms
#define BLINK_TIME_1 0x04            //  67ms
#define BLINK_TIME_2 0x08            // 100ms
#define BLINK_TIME_3 0x0C            // 133ms

// Character white level
#define WHITE_level_80 0x03
#define WHITE_level_90 0x02
#define WHITE_level_100 0x01
#define WHITE_level_120 0x00

// Background mode brightness (as a percentage)
#define BACKGROUND_BRIGHTNESS_0 0x00
#define BACKGROUND_BRIGHTNESS_7 0x01
#define BACKGROUND_BRIGHTNESS_14 0x02
#define BACKGROUND_BRIGHTNESS_21 0x03
#define BACKGROUND_BRIGHTNESS_28 0x04
#define BACKGROUND_BRIGHTNESS_35 0x05
#define BACKGROUND_BRIGHTNESS_42 0x06
#define BACKGROUND_BRIGHTNESS_49 0x07

#define BACKGROUND_NONE 0x00      
#define BACKGROUND_MODE_GRAY 0x80    

#define MAX7456_RB0_R   0x90    // Row 0 Brightness read
#define MAX7456_RB0_W   0x10    // Row 0 Brightness write
#define MAX7456_RB1_R   0x91    // Row 1 Brightness read
#define MAX7456_RB1_W   0x11    // Row 1 Brightness write
#define MAX7456_RB2_R   0x92    // Row 2 Brightness read
#define MAX7456_RB2_W   0x12    // Row 2 Brightness write
#define MAX7456_RB3_R   0x93    // Row 3 Brightness read
#define MAX7456_RB3_W   0x13    // Row 3 Brightness write
#define MAX7456_RB4_R   0x94    // Row 4 Brightness read
#define MAX7456_RB4_W   0x14    // Row 4 Brightness write
#define MAX7456_RB5_R   0x95    // Row 5 Brightness read
#define MAX7456_RB5_W   0x15    // Row 5 Brightness write
#define MAX7456_RB6_R   0x96    // Row 6 Brightness read
#define MAX7456_RB6_W   0x16    // Row 6 Brightness write
#define MAX7456_RB7_R   0x97    // Row 7 Brightness read
#define MAX7456_RB7_W   0x17    // Row 7 Brightness write
#define MAX7456_RB8_R   0x98    // Row 8 Brightness read
#define MAX7456_RB8_W   0x18    // Row 8 Brightness write
#define MAX7456_RB9_R   0x99    // Row 9 Brightness read
#define MAX7456_RB9_W   0x19    // Row 9 Brightness write
#define MAX7456_RB10_R  0x9A    // Row 10 Brightness read
#define MAX7456_RB10_W  0x1A    // Row 10 Brightness write
#define MAX7456_RB11_R  0x9B    // Row 11 Brightness read
#define MAX7456_RB11_W  0x1B    // Row 11 Brightness write
#define MAX7456_RB12_R  0x9C    // Row 12 Brightness read
#define MAX7456_RB12_W  0x1C    // Row 12 Brightness write
#define MAX7456_RB13_R  0x9D    // Row 13 Brightness read
#define MAX7456_RB13_W  0x1D    // Row 13 Brightness write
#define MAX7456_RB14_R  0x9E    // Row 14 Brightness read
#define MAX7456_RB14_W  0x1E    // Row 14 Brightness write
#define MAX7456_RB15_R  0x9F    // Row 15 Brightness read
#define MAX7456_RB15_W  0x1F    // Row 15 Brightness write


//MAX7456 commands
#define CLEAR_display 0x04
#define CLEAR_display_vert 0x06
#define END_string 0xff
#define MAX7456_STAT_R  0xA0      // Status read

// Uncomment For NTSC
//#define ENABLE_display 0x08
//#define ENABLE_display_vert 0x0c
//#define MAX7456_reset 0x02
//#define DISABLE_display 0x00

// with PAL all VM0_reg commands need bit 6 set
#define ENABLE_display 0x48
#define ENABLE_display_vert 0x4c
#define MAX7456_reset 0x42
#define DISABLE_display 0x40

// Uncomment for NTSC 
//#define MAX_screen_size 390
//#define MAX_screen_rows 13

// PAL screen dimensions
#define MAX_screen_size 480
#define MAX_screen_rows 16
int CURSOR_X_MIN =0;
int CURSOR_X_MAX =29;
int CURSOR_Y_MIN =0;
int CURSOR_Y_MAX =12;
