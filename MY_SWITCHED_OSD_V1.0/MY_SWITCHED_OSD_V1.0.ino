/*
  Program : MY_STATIC_OSD.INO
  Version : 1.00
  Date    : 3rd Feb 2018
  Purpose : Simple caption test for OSD modifications as per CQ-DATV Ed.12

*/

#include "MAX7456OSD.H"                   // Register names for MAX7456 device

// MAX7456 SPI pins
#define DATAOUT 		11	  // MOSI
#define DATAIN 			12	  // MISO
#define SPICLOCK 		13	  // SCK
#define MAX7456SELECT 		6         // SS 
#define MAX7456RESET 		10 
#define enabletext  9  // switch for enabling text 
/*#define callswitch	3	// switch for enabling large callsign*/
int callswitch = A2;
int texton = A3;
int swpos = 0;
int swpre = 1;
int swtxtpos = 0;
int swtxtpre = 1;
#define portable  8 // switch for enabling /p 

//--------------------------------------------------------------------------------------------
void setup()
{
  byte spi_junk;                        
  int x;
  int i;

  pinMode(enabletext,INPUT);
  pinMode(A3,INPUT);
  pinMode(portable,INPUT);
  
  pinMode(MAX7456RESET,OUTPUT);
  digitalWrite(MAX7456RESET,HIGH); 
  
  pinMode(MAX7456SELECT,OUTPUT);
  digitalWrite(MAX7456SELECT,HIGH);  		// Disable device

  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);

  // SPCR = 01010000
  //interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
  //sample on leading edge of clk,system clock/4 rate (4 meg)
  SPCR = (1<<SPE)|(1<<MSTR);
  spi_junk=SPSR;
  spi_junk=SPDR;
  delay(250);
  
  // Force soft reset on Max7456
  digitalWrite(MAX7456SELECT,LOW);
  spi_transfer(VM0_reg);
  spi_transfer(MAX7456_RESET);
  digitalWrite(MAX7456SELECT,HIGH);
  delay(500);		

  // Set all rows to same character white level, 90%
  digitalWrite(MAX7456SELECT,LOW);
  for (x = 0; x < MAX_screen_rows; x++)
  {
    spi_transfer(x + 0x10);
    spi_transfer(WHITE_level_90);
  }

  // Make sure the Max7456 is enabled
  spi_transfer(VM0_reg);
  spi_transfer(VERTICAL_SYNC_NEXT_VSYNC|OSD_ENABLE|VIDEO_MODE_PAL);	    	   
  digitalWrite(MAX7456SELECT,HIGH);
  delay(100);			     			    		    

  //OSD_Clear();
  //if (enabletext == HIGH)
  //{
  // Text, X position, Y position, Blink Text, Invert Text
  //OSD_write_to_screen("M5SJM - Stephen - IO93RF", 2, 1, 0, 0);
  //OSD_write_to_screen("2m TalkBack 144.750MHz", 2, 2, 0, 0);
  //}
  // Use the MAX7456Charwizard.JAR character viewer & editor to edit the hex values in the below subroutine!
		  
}  
  
//-------------------------------------------------------------------------------------------- ASCII Table Conversion

void Max7456()
{
  if (analogRead(texton) > 0)
  {
    swtxtpos = 1;
  }
  else
  {
    swtxtpos = 0;
  }
  
  if (swtxtpos == swtxtpre)
    {
    }
    else
    {
      if (swtxtpos == 1)
      {
        OSD_write_to_screen("M5SJM - Stephen - IO93SF", 2, 1, 0, 0);
        OSD_write_to_screen("2m TalkBack 144.750MHz", 2, 2, 0, 0);
        swtxtpre = 1;
      }
      else
      {
        OSD_write_to_screen("                        ", 2, 1, 0, 0);
        OSD_write_to_screen("                      ", 2, 2, 0, 0);
        swtxtpre = 0;
      }
    } 
   
  
  if (analogRead(callswitch) > 0)
  {
    swpos = 1;
  }
  else
  {
    swpos = 0;
  }
  
  if (swpos == swpre)
    {
    }
    else
    {
      if (swpos == 1)
      {
        Callsign(); // Write out message for non ASCII Characters
        swpre = 1;
      }
      else
      {
        OSD_write_to_screen("                        ",1,3,0,0);
        OSD_write_to_screen("                        ",2,3,0,0);
        OSD_write_to_screen("                        ",3,3,0,0);
        OSD_write_to_screen("                        ",4,3,0,0);
        OSD_write_to_screen("                        ",1,4,0,0);
        OSD_write_to_screen("                        ",2,4,0,0);
        OSD_write_to_screen("                        ",3,4,0,0);
        OSD_write_to_screen("                        ",4,4,0,0);
        OSD_write_to_screen("                        ",1,5,0,0);
        OSD_write_to_screen("                        ",2,5,0,0);
        OSD_write_to_screen("                        ",3,5,0,0);
        OSD_write_to_screen("                        ",4,5,0,0);
        OSD_write_to_screen("                        ",1,6,0,0);
        OSD_write_to_screen("                        ",2,6,0,0);
        OSD_write_to_screen("                        ",3,6,0,0);
        OSD_write_to_screen("                        ",4,6,0,0);
        swpre = 0;
      }
    }
  

spi_transfer(VM0_reg);
spi_transfer(VERTICAL_SYNC_NEXT_VSYNC|OSD_ENABLE|SYNC_MODE_AUTO);
digitalWrite(MAX7456SELECT,HIGH); 
}
byte convert_ascii (int character)
{
// ASCII Lookup table 

 byte lookup_char;

  if (character == 32)
    lookup_char = 0x00; // blank space
  else if (character == 48)
    lookup_char = 0x0a; // 0
  else if ((character > 48) && (character < 58))
    lookup_char = (character - 48); // 1-9
  else if ((character > 64) && (character < 91))
    lookup_char = (character - 54); // A-Z
  else if ((character > 96) && (character < 123))
    lookup_char = (character - 60); // a-z
  else if (character == 34)
    lookup_char = 0x48; // "
  else if (character == 39)
    lookup_char = 0x46; // '
  else if (character == 40)
    lookup_char = 0x3f; // (
  else if (character == 41)
    lookup_char = 0x40; // )
  else if (character == 44)
    lookup_char = 0x45; // ,
  else if (character == 45)
    lookup_char = 0x49; // -
  else if (character == 46)
    lookup_char = 0x41; // .
  else if (character == 47)
    lookup_char = 0x47; // /
  else if (character == 58)
    lookup_char = 0x44; // :
  else if (character == 59)
    lookup_char = 0x43; // ;
  else if (character == 60)
    lookup_char = 0x4a; // <
  else if (character == 62)
    lookup_char = 0x4b; // >
  else if (character == 63)
    lookup_char = 0x42; // ?
  else if (character == 64)
    lookup_char = 0x4c; // @
  else
    lookup_char = 0x00; // out of range, blank space

 return (lookup_char);
}

//-------------------------------------------------------------------------------------------- Clear Captions

void OSD_Clear()
{
  digitalWrite(MAX7456SELECT,LOW);
  spi_transfer(DMM_reg);
  spi_transfer(CLEAR_display);      
  digitalWrite(MAX7456SELECT,HIGH);
}

// ============================================================ Write Text string to screen
// Text, X & Y,Blink,Invert

void OSD_write_to_screen(const char s[], byte x, byte y, byte blink, byte invert)
{
  
  unsigned int linepos;
  byte local_count;
  byte settings, char_address_hi, char_address_lo;
  byte screen_char;
  
  local_count = 0;
  
  char_address_hi = 0;
  char_address_lo = 0;
  
  // convert X,Y to line position
  linepos = y*30+x;

  // divide in to hi & lo byte
  char_address_hi = linepos >> 8;
  char_address_lo = linepos;

  settings = B00000001;

  // set blink bit
  if (blink) {
    settings |= (1 << 4);	 // forces nth bit of x to be 1.  all other bits left alone.
  }
  // set invert bit
  if (invert){
    settings |= (1 << 3);	 // forces nth bit of x to be 1.  all other bits left alone.
  }

  digitalWrite(MAX7456SELECT,LOW);

  spi_transfer(DMM_reg);         //dmm
  spi_transfer(settings);

  spi_transfer(DMAH_reg);        // set start address high
  spi_transfer(char_address_hi);

  spi_transfer(DMAL_reg);       // set start address low
  spi_transfer(char_address_lo);

  while(s[local_count]!='\0')   // write out full screen
  {
    screen_char = s[local_count];
    screen_char= convert_ascii(screen_char);
    spi_transfer(DMDI_reg);
    spi_transfer(screen_char);
    local_count++;
  }
  
  spi_transfer(DMDI_reg);
  spi_transfer(END_string);

  spi_transfer(VM0_reg); // turn on screen next vertical. 
  spi_transfer(ENABLE_display_vert);
  digitalWrite(MAX7456SELECT,HIGH);
  
  }

// -------------------------------------------------------------------------------------------- Print MAX7456 NVRAM Character from Hex code
// First byte is the HEX code, X Position, Y Position, Blink Char, Invert Char
// Example: -           
//
//                  printMax7456Char(0xF9,5,6,0,0);    // Speaker Icon


void printMax7456Char(const byte address, byte x, byte y, byte blink, byte inv)
{
	byte ad = address;
	OSD_printchrs(&ad,1,x,y,blink,inv);
}

void OSD_printchrs(byte chars[],byte size, byte x, byte y, byte blink, byte invert)
{
  
  unsigned int linepos;
  byte local_count;
  byte settings, char_address_hi, char_address_lo;
  byte screen_char;
  byte currentCharMax7456;

  local_count = 0;
  
  char_address_hi = 0;
  char_address_lo = 0;
  
  // convert X,Y to line position
  linepos = y*30+x;

  // divide in to hi & lo byte
  char_address_hi = linepos >> 8;
  char_address_lo = linepos;

  settings = B00000001;

  // set blink bit
  if (blink) {
    settings |= (1 << 4);	                 // forces nth bit of x to be 1.  all other bits left alone.
  }
  // set invert bit
  if (invert){
    settings |= (1 << 3);	                // forces nth bit of x to be 1.  all other bits left alone.
  }

  digitalWrite(MAX7456SELECT,LOW);

  spi_transfer(DMM_reg);                       //dmm
  spi_transfer(settings);

  spi_transfer(DMAH_reg);                      // set start address high
  spi_transfer(char_address_hi);

  spi_transfer(DMAL_reg);                     // set start address low
  spi_transfer(char_address_lo);

  for(int i = 0; i < size ; i++)
  {
    currentCharMax7456 = chars[i];
    spi_transfer(DMDI_reg);
    spi_transfer(currentCharMax7456);
  }

  spi_transfer(DMDI_reg);
  spi_transfer(END_string);

  spi_transfer(VM0_reg);                       // turn on screen next vertical. 
  spi_transfer(ENABLE_display_vert);
  digitalWrite(MAX7456SELECT,HIGH);
  }

//--------------------------------------------------------------------------------------------

void spi_writereg(byte r, byte d) {
  spi_transfer(r);
  spi_transfer(d);
}  

//--------------------------------------------------------------------------------------------

byte spi_transfer(volatile byte data)
{
  SPDR = data;			  // Start the transmission
  while (!(SPSR & (1<<SPIF)))     // Wait for the end of transmission
  {
  };
  return SPDR;			  // return the received byte
}


//--------------------------------------------------------------------------------------------
// These characters have no ASCII equivalent.
// Use the MAX7456charwizard.Jar Software to get the Hex code for the character you require 

void Callsign()
{
  //M
   printMax7456Char(0x78,1,3,0,0);      // 2L1
   printMax7456Char(0x79,2,3,0,0);      // 2L1
   printMax7456Char(0x7A,3,3,0,0);      // 2L1
   printMax7456Char(0x7B,4,3,0,0);      // 2L1
   
   printMax7456Char(0x88,1,4,0,0);      // 2L2
   printMax7456Char(0x89,2,4,0,0);      // 2L2
   printMax7456Char(0x8A,3,4,0,0);      // 2L2
   printMax7456Char(0x8B,4,4,0,0);      // 2L2
   
   printMax7456Char(0x98,1,5,0,0);      // 2L3
   printMax7456Char(0x99,2,5,0,0);      // 2L3
   printMax7456Char(0x9A,3,5,0,0);      // 2L3
   printMax7456Char(0x9B,4,5,0,0);      // 2L3
   
   printMax7456Char(0xA8,1,6,0,0);      // 2L4
   printMax7456Char(0xA9,2,6,0,0);      // 2L4
   printMax7456Char(0xAA,3,6,0,0);      // 2L4
   printMax7456Char(0xAB,4,6,0,0);      // 2L4

   //5
   printMax7456Char(0x7C,6,3,0,0);      // EL1
   printMax7456Char(0x7D,7,3,0,0);      // EL1
   printMax7456Char(0x7E,8,3,0,0);      // EL1
   printMax7456Char(0x7F,9,3,0,0);     // EL1
   
   printMax7456Char(0x8C,6,4,0,0);      // EL2
   printMax7456Char(0x8D,7,4,0,0);      // EL2
   printMax7456Char(0x8E,8,4,0,0);      // EL2
   printMax7456Char(0x8F,9,4,0,0);     // EL2
   
   printMax7456Char(0x9C,6,5,0,0);      // EL3
   printMax7456Char(0x9D,7,5,0,0);      // EL3
   printMax7456Char(0x9E,8,5,0,0);      // EL3
   printMax7456Char(0x9F,9,5,0,0);     // EL3
   
   printMax7456Char(0xAC,6,6,0,0);      // EL4
   printMax7456Char(0xAD,7,6,0,0);      // EL4
   printMax7456Char(0xAE,8,6,0,0);      // EL4
   printMax7456Char(0xAF,9,6,0,0);     // EL4

   //S
   printMax7456Char(0xB0,11,3,0,0);     // 0L1
   printMax7456Char(0xB1,12,3,0,0);     // 0L1
   printMax7456Char(0xB2,13,3,0,0);     // 0L1
   printMax7456Char(0xB3,14,3,0,0);     // 0L1
   
   printMax7456Char(0xC0,11,4,0,0);     // 0L2
   printMax7456Char(0xC1,12,4,0,0);     // 0L2
   printMax7456Char(0xC2,13,4,0,0);     // 0L2
   printMax7456Char(0xC3,14,4,0,0);     // 0L2
   
   printMax7456Char(0xD0,11,5,0,0);     // 0L3
   printMax7456Char(0xD1,12,5,0,0);     // 0L3
   printMax7456Char(0xD2,13,5,0,0);     // 0L3
   printMax7456Char(0xD3,14,5,0,0);     // 0L3
   
   printMax7456Char(0xE0,11,6,0,0);     // 0L4
   printMax7456Char(0xE1,12,6,0,0);     // 0L4
   printMax7456Char(0xE2,13,6,0,0);     // 0L4
   printMax7456Char(0xE3,14,6,0,0);     // 0L4

   //J
   printMax7456Char(0xB4,16,3,0,0);     // SL1
   printMax7456Char(0xB5,17,3,0,0);     // SL1
   printMax7456Char(0xB6,18,3,0,0);     // SL1
   printMax7456Char(0xB7,19,3,0,0);     // SL1
   
   printMax7456Char(0xC4,16,4,0,0);     // SL2
   printMax7456Char(0xC5,17,4,0,0);     // SL2
   printMax7456Char(0xC6,18,4,0,0);     // SL2
   printMax7456Char(0xC7,19,4,0,0);     // SL2
   
   printMax7456Char(0xD4,16,5,0,0);     // SL3
   printMax7456Char(0xD5,17,5,0,0);     // SL3
   printMax7456Char(0xD6,18,5,0,0);     // SL3
   printMax7456Char(0xD7,19,5,0,0);     // SL3
   
   printMax7456Char(0xE4,16,6,0,0);     // SL4
   printMax7456Char(0xE5,17,6,0,0);     // SL4
   printMax7456Char(0xE6,18,6,0,0);     // SL4
   printMax7456Char(0xE7,19,6,0,0);     // SL4


  //M
   printMax7456Char(0x78,21,3,0,0);      // 2L1
   printMax7456Char(0x79,22,3,0,0);      // 2L1
   printMax7456Char(0x7A,23,3,0,0);      // 2L1
   printMax7456Char(0x7B,24,3,0,0);      // 2L1
   
   printMax7456Char(0x88,21,4,0,0);      // 2L2
   printMax7456Char(0x89,22,4,0,0);      // 2L2
   printMax7456Char(0x8A,23,4,0,0);      // 2L2
   printMax7456Char(0x8B,24,4,0,0);      // 2L2
   
   printMax7456Char(0x98,21,5,0,0);      // 2L3
   printMax7456Char(0x99,22,5,0,0);      // 2L3
   printMax7456Char(0x9A,23,5,0,0);      // 2L3
   printMax7456Char(0x9B,24,5,0,0);      // 2L3
   
   printMax7456Char(0xA8,21,6,0,0);      // 2L4
   printMax7456Char(0xA9,22,6,0,0);      // 2L4
   printMax7456Char(0xAA,23,6,0,0);      // 2L4
   printMax7456Char(0xAB,24,6,0,0);      // 2L4

// /P
if (portable == HIGH){
   printMax7456Char(0xBC,26,3,0,0);     // ML1
   printMax7456Char(0xBD,27,3,0,0);     // ML1
   printMax7456Char(0xBE,28,3,0,0);     // ML1
   printMax7456Char(0xBF,29,3,0,0);     // ML1
   
   printMax7456Char(0xCC,26,4,0,0);     // ML2
   printMax7456Char(0xCD,27,4,0,0);     // ML2
   printMax7456Char(0xCE,28,4,0,0);     // ML2
   printMax7456Char(0xCF,29,4,0,0);     // ML2
   
   printMax7456Char(0xDC,26,5,0,0);     // ML3
   printMax7456Char(0xDD,27,5,0,0);     // ML3
   printMax7456Char(0xDE,28,5,0,0);     // ML3
   printMax7456Char(0xDF,29,5,0,0);     // ML3
   
   printMax7456Char(0xEC,26,6,0,0);     // ML4
   printMax7456Char(0xED,27,6,0,0);     // ML4
   printMax7456Char(0xEE,28,6,0,0);     // ML4
   printMax7456Char(0xEF,29,6,0,0);     // ML4
   }
}

//--------------------------------------------------------------------------------------------
void loop()
{
   Max7456();
}
