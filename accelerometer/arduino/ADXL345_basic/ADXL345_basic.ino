/***************************************************************************
* Example sketch for the ADXL345_WE / ADXL343_WE library
*
* This sketch shows how to get the basic raw and g values 
*  
* Further information can be found on:
* https://wolles-elektronikkiste.de/adxl345-teil-1 (German)
* https://wolles-elektronikkiste.de/en/adxl345-the-universal-accelerometer-part-1 (English)
* 
***************************************************************************/

#include<Wire.h>
#include<ADXL345_WE.h>
#define ADXL345_I2CADDR 0x53 // 0x1D if SDO = HIGH

/* There are several ways to create your ADXL345 object:
 * ADXL345_WE myAcc = ADXL345_WE()                -> uses Wire / I2C Address = 0x53
 * ADXL345_WE myAcc = ADXL345_WE(ADXL345_I2CADDR) -> uses Wire / ADXL345_I2CADDR
 * ADXL345_WE myAcc = ADXL345_WE(&wire2)          -> uses the TwoWire object wire2 / ADXL345_I2CADDR
 * ADXL345_WE myAcc = ADXL345_WE(&wire2, ADXL345_I2CADDR) -> all together
 */
ADXL345_WE myAcc = ADXL345_WE();

void setup(){
  Wire.begin();
  Serial.begin(115200);
  if(!myAcc.init()){
    Serial.println("ADXL345 not connected!");
  }
   
/* Choose the data rate         Hz
    ADXL345_DATA_RATE_3200    3200
    ADXL345_DATA_RATE_1600    1600
    ADXL345_DATA_RATE_800      800
    ADXL345_DATA_RATE_400      400
    ADXL345_DATA_RATE_200      200
    ADXL345_DATA_RATE_100      100
    ADXL345_DATA_RATE_50        50
    ADXL345_DATA_RATE_25        25
    ADXL345_DATA_RATE_12_5      12.5  
    ADXL345_DATA_RATE_6_25       6.25
    ADXL345_DATA_RATE_3_13       3.13
    ADXL345_DATA_RATE_1_56       1.56
    ADXL345_DATA_RATE_0_78       0.78
    ADXL345_DATA_RATE_0_39       0.39
    ADXL345_DATA_RATE_0_20       0.20
    ADXL345_DATA_RATE_0_10       0.10
*/
  myAcc.setDataRate(ADXL345_DATA_RATE_50);
  delay(100);


/* Choose the measurement range
    ADXL345_RANGE_16G    16g     
    ADXL345_RANGE_8G      8g     
    ADXL345_RANGE_4G      4g   
    ADXL345_RANGE_2G      2g
*/ 
  myAcc.setRange(ADXL345_RANGE_4G);
  delay(100);
  
}

/* The LSB of the Data registers is 3.9 mg (milli-g, not milligramm).
    This value is used calculating g from raw. However, this is an ideal
    value which you might want to calibrate. 
*/

void loop() {

  char incomingByte = Serial.read();

  if (incomingByte == 'R') {
    xyzFloat raw;
    xyzFloat g;
    myAcc.getRawValues(&raw);
    myAcc.getGValues(&g);
    
    Serial.print(raw.x);
    Serial.print(",");
    Serial.print(raw.y);
    Serial.print(",");
    Serial.print(raw.z);
    Serial.print("\n");
  }
  // Serial.print("Raw-x = ");
  // Serial.print(raw.x);
  // Serial.print("  |  Raw-y = ");
  // Serial.print(raw.y);
  // Serial.print("  |  Raw-z = ");
  // Serial.println(raw.z);

  // Serial.print("g-x   = ");
  // Serial.print(g.x);
  // Serial.print("  |  g-y   = ");
  // Serial.print(g.y);
  // Serial.print("  |  g-z   = ");
  // Serial.println(g.z);

  // Serial.println();
  
  delay(100);
  
}
