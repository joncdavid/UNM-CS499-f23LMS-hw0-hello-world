/* BTMS Board Test Software
   LMS 2023 BTMS V73 Hardware
   Discrete outputs: Name(pin)
    HVI_ADDR0(37), HVI_ADDR1(36), HVI_ADDR2(35), HVI_ADDR3(34)
    HVI1_LOWER_!EN!(19), HVI1_UPPER_!EN!(18)
    HVI2_LOWER_!EN!(14), HVI2_UPPER_!EN!(15)
    HVI3_LOWER_!EN!(40), HVI3_UPPER_!EN!(41)
    HVI4_LOWER_!EN!(17), HVI4_UPPER_!EN!(16)
    HVI5_LOWER_!EN!(22), HVI5_UPPER_!EN!(23)
    BMS_RESET(39)
    IMD_RESET(38)
    CS0(10)
    SCLK0(13)
   Discrete inputs: Name(pin)
    MISO0(12)
    
Progam Instuctions:

1) Use BTMS Test Cable that Jumpers U1-11 (MOSI) to either Upper or Lower MISOs of HVI connector. 
  i.e.: J1-11 or J1-12; J2-11 or J2-12; J3-11 or J3-12; J4-11 or J4-12; J5-11 or J5-12
2) Power BTMS board.
3) Connect BTMS to PC running Serial Monitor
4) Select HVI to test: HVI1U, HVI1L, HVI2U, HVI2L, HVI3U, HVI
4) Test HVIxLOWER_EN, HVIxUPPER_EN; high and low and verify HVIx(LOWER or UPPER)_ADC_CS follows when CSx is low
5) Test HVIx_LOWER_ADC_CS, HVIx_UPPER_ADC_CS; through logic gateby changing CSx high and low 
*6) Test SPI Bus (NOT IMPLEMENTED IN THIS SKETCH)
  a) Connect Oscilloscope CH1 to HVIx_(Upper or Lower)EN, CH2 to HVIx_(Upper or Lower)ADC_CS,  CH3 to SCLKx, CH4 to HVIx_(Upper or Lower)MISO
  b) Setup for communication with: HVI1_Upper, HVI1_Lower, HVI2_Upper, HVI2_Lower, HVI3_Upper, HVI3_Lower, HVI4_Upper, HVI4_Lower, HVI5_Upper, HVI5_Lower
  c) Transmit a pattern on SPI bus and look for correct response
*7) Test CAN Bus (NOT IMPLEMENTED IN THIS SKETCH)
  a) Connect CAN Bus Analyzer to J6
  b) Send out a pattern on CAN Bus and verify on CAN Bus Analyzer
*8) Test Resets (NOT IMPLEMENTED IN THIS SKETCH)
  a) Command BMS_RESET high and low
  b) Command IMD_RESET high and low
 
*/
// ------ Name output pins --------
int HVI_Pwr = 20;
int ADDR0 = 37;
int ADDR1 = 36;
int ADDR2 = 35;
int ADDR3 = 34;
int HVI_LOWER_EN[5] = {19, 14, 40, 17, 22};
int HVI_UPPER_EN[5] = {18, 15, 41, 16, 23};
int HVI_EN[10] = {19, 14, 40, 17, 22, 18, 15, 41, 16, 23};
int HVI1_LOWER_EN = 19;
int HVI1_UPPER_EN = 18;
int HVI2_LOWER_EN = 14;
int HVI2_UPPER_EN = 15;
int HVI3_LOWER_EN = 40;
int HVI3_UPPER_EN = 41;
int HVI4_LOWER_EN = 17;
int HVI4_UPPER_EN = 16;
int HVI5_LOWER_EN = 22;
int HVI5_UPPER_EN = 23;
int BMS_RESET = 39;
int IMD_RESET = 38;
int CS0 = 10;
int SCLK0 = 13;

// ------- Name input pins --------
int MISO0 = 12;

// -------- declare functions ---------
void setHVI (int, bool);
bool setADDR (int);


//  ---- start setup ----------------------------------------------------------
void setup()   {               
  Serial.begin(38400); //Setup Serial (USB) port
  Serial.println("LMS 2023 BTMS Board Test");

  // Configure and initialize ADDR output pins
  pinMode(ADDR0, OUTPUT);
      digitalWrite(ADDR0, LOW);
  pinMode(ADDR1, OUTPUT);
      digitalWrite(ADDR1, LOW);
  pinMode(ADDR2, OUTPUT);
      digitalWrite(ADDR2, LOW);
  pinMode(ADDR3, OUTPUT);
      digitalWrite(ADDR3, LOW);

// Configure and initialize HVI_Pwr output pin. Set output power to ON
// The reason to turn power ON is to avoid turning on the HVx enbales to a HIGH state while the HVI board is powered off
  pinMode(HVI_Pwr, OUTPUT);
      digitalWrite(HVI_Pwr, LOW);  // Turn on HVI board power
      delay(5);                    // Delay 5msec. to allow power to stabilize

// Configure and initialize HVIx_UPPER & LOWER output pins.  
// Set tri-state buffer outputs to high impedance 
  pinMode(HVI1_LOWER_EN, OUTPUT);
      digitalWrite(HVI1_LOWER_EN, HIGH);
  pinMode(HVI1_UPPER_EN, OUTPUT);
       digitalWrite(HVI1_UPPER_EN, HIGH);
  pinMode(HVI2_LOWER_EN, OUTPUT);
       digitalWrite(HVI2_LOWER_EN, HIGH);
  pinMode(HVI2_UPPER_EN, OUTPUT);
         digitalWrite(HVI2_UPPER_EN, HIGH);
  pinMode(HVI3_LOWER_EN, OUTPUT);
       digitalWrite(HVI3_LOWER_EN, HIGH);
  pinMode(HVI3_UPPER_EN, OUTPUT);
         digitalWrite(HVI3_UPPER_EN, HIGH);
  pinMode(HVI4_LOWER_EN, OUTPUT);
       digitalWrite(HVI4_LOWER_EN, HIGH);
  pinMode(HVI4_UPPER_EN, OUTPUT);
         digitalWrite(HVI4_UPPER_EN, HIGH);
  pinMode(HVI5_LOWER_EN, OUTPUT);
       digitalWrite(HVI5_LOWER_EN, HIGH);
  pinMode(HVI5_UPPER_EN, OUTPUT);
         digitalWrite(HVI5_UPPER_EN, HIGH);

// Configure and initialize BMS_RESET & IMD_RESET output pins.  
  pinMode(BMS_RESET, OUTPUT);
         digitalWrite(BMS_RESET, LOW);
  pinMode(IMD_RESET, OUTPUT);
         digitalWrite(IMD_RESET, LOW);
  
 // Configure and initialize CS0 output pin.  
  pinMode(CS0, OUTPUT);
         digitalWrite(CS0, HIGH);
  // pinMode(SCLK0, OUTPUT); // should not need to configure SPI bus pins
  // Configure input pins
  // pinMode(MISO0, INPUT_PULLUP);

// Configure all unused pins as inputs with pullups to avoid meta states and excess power draw
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);

}  // ---- end setup -----------------------------------------------------------------------------

 // -----Start main loop ------------------------------------------------------------------------------
void loop() {  

int SegmentNumber;  // Declare Battery Segment Number variable
int BatteryNumber;  // Declare HVI Battery Number variable
bool Upper;         // Declare HVI Upper or Lower variable

Serial.println(" ");   // Insert a blank line
Serial.println("Select the battery temperature to read. Valid choices are segment (1 through 5) <enter> followed by battery 1 through 18 <enter>");  // Top menu choices
Serial.println("'1 <enter> followed by '7' <enter> will read segment 1, battery 7 ");
Serial.println(" ");   // Insert a blank line

Serial.println(" Enter Segnment number 1 through 5 ");   // Prompt for segment niumber
while (Serial.available() == 0) {} // wait for keyboard entry. Serial.available returns the number of bytes available

// while waiting for the keyboard entry, the HVI enables remain as prevoiusly set to allow circuit probing to verify correct setting

// The following "for" loop disables all the HVI enables in preparation to set the desired one
for (int j = 0; j < 10; j++) {
digitalWrite(HVI_EN[j], HIGH);  
}

SegmentNumber = Serial.parseInt(); // Read keyboard segment number entry
if (SegmentNumber <1 || SegmentNumber > 5) {       // Verify entry is valid
  Serial.println(" Segment Number entry error");
}
else {
  Serial.print(SegmentNumber);
  Serial.println(" entered");
}

Serial.parseInt(); // read the keyboard entry again to clear serial buffer.

Serial.println(" Enter battery number 1 through 18");   // Prompt for battery niumber
while (Serial.available() == 0) {} // wait for keyboard entry. Serial.available returns the number of bytes available
BatteryNumber = Serial.parseInt(); // Read keyboard Battery Number entry
if (BatteryNumber < 1 || BatteryNumber > 18) {   // Verify entry is valid
  Serial.println(" Battery Number entry error");
  }
else {
  Serial.print(BatteryNumber);
  Serial.println(" entered");
}

Serial.parseInt(); // read the keyboard entry again to clear serial buffer.  Without this statement, the Teensy always executes the "while" loop again with an invalid character
Serial.flush();  // wait for Serial output to complete before continuing

Upper = setADDR(BatteryNumber);  // Call the function that sets the 4 address pins to select the input channel of the MUX on the HVI

setHVI(SegmentNumber, Upper);   // Call the function that sets the HVIx enable for the battery segment to be read
 Serial.println("End of Loop");
}   

// --------------- end main loop ---------------------------------------------------------------------------------


//for loop for 9 Mux input channels. --- code example to step through all addresses when converting to automatic reads
//   for (int j = 0; j < 9; j++) {
//   }


// -------------------- start setADDR function -------------------------------------------------------------------
// There are 5 HVI boards, one for each battery section. 
// Each HVI board interfaces to 18 battery.  
// In order to avoid exceeding the temperature sensor's isolation rating, the HVI board is divided into an Upper and Lower halves.
// Each half has 9 cells. BatteryNumber is the number of the cell within the section to be monitored.
// 

bool setADDR (int BatteryNumber) { 
int  addr;
bool Upper;

//  Determine if Upper or Lower half, and then set ADDR lines accordingly. 
  if (BatteryNumber > 9) {  
    Upper = true;
    addr = BatteryNumber - 10;
    }
  else {
    addr = BatteryNumber - 1;
    Upper = false;
    }

  //implementing bitwise AND operation to set ADDRs high and low
  digitalWrite(ADDR0, (addr & 0x01) ? HIGH : LOW);//check with least significant bit
  digitalWrite(ADDR1, (addr & 0x02) ? HIGH : LOW); //checks with second least significant bit
  digitalWrite(ADDR2, (addr & 0x04) ? HIGH : LOW); //checks with third least significant bit
  digitalWrite(ADDR3, (addr & 0x08) ? HIGH : LOW); //checks with fourth least significant bit
 
return Upper;
}  
// --------------- end setADDR function ---------------------------------------------------------------------




// ------------------ start setHVI function -------------------------------------------------------------------
// This function configures the HVIx enables to allow a read of the desired channel
//

void setHVI (int SegmentNumber, bool Upper) { 

  if (SegmentNumber == 1 && Upper == false) {        //  If we are reading an HVI1 Lower channel
    digitalWrite(HVI1_LOWER_EN, LOW);                //  Write a LOW to HVI1_LOWER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 1 && Upper == true) {    //  If we are setting an HVI1_Upper_EN
   digitalWrite(HVI1_UPPER_EN, LOW);                //  Write a LOW to HVI1_UPPER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 2 && Upper == false) {  // 
   digitalWrite(HVI2_LOWER_EN, LOW);                //  Write a LOW to HVI2_LOWER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 2 && Upper == true) {   //  
   digitalWrite(HVI2_UPPER_EN, LOW);                //  Write a LOW to HVI2_UPPER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 3 && Upper == false) {   // 
    digitalWrite(HVI3_LOWER_EN, LOW);                //  Write a LOW to HVI3_LOWER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 3 && Upper == true) {   //  
   digitalWrite(HVI3_UPPER_EN, LOW);                //  Write a LOW to HVI3_UPPER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 4 && Upper == false) {   // 
    digitalWrite(HVI4_LOWER_EN, LOW);                //  Write a LOW to HVI4_LOWER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 4 && Upper == true) {    //  
   digitalWrite(HVI4_UPPER_EN, LOW);                //  Write a LOW to HVI4_UPPER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 5 && Upper == false) {   // 
    digitalWrite(HVI5_LOWER_EN, LOW);                //  Write a LOW to HVI5_LOWER_EN. All others have been set HIGH in Setup or loop function
    }
  else if (SegmentNumber == 5 && Upper == true) {   //  
   digitalWrite(HVI5_UPPER_EN, LOW);                //  Write a LOW to HVI5_UPPER_EN. All others have been set HIGH in Setup or loop function
    }
  else {
    Serial.println("setHVI function error");
  }
return;
}  
// ------------------- end HVI string function -------------------------------------------------------------
