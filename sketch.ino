#include <OneWire.h>
#include <DallasTemperature.h>
#include <TM1637Display.h>

#define ONE_WIRE_BUS 2
#define CLK 4
#define DIO 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  
  delay(1000);
  
  if (sensors.getDeviceCount() == 0) {
    Serial.println("No devices found.");
  } else {
    Serial.println("Device found.");
    display.setBrightness(0x0f, true); // Maximum brightness
  }
}

void loop() {
  sensors.requestTemperatures();
  
  float temperature = sensors.getTempCByIndex(0);
  
  if (temperature == -127.00) {
    Serial.println("Error: Could not read temperature.");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    // Convert the float temperature to an integer to display on the TM1637
    int tempToDisplay = (int)temperature;  // Truncate the decimal part
    
    display.showNumberDec(tempToDisplay, true, 4, 0); // Display integer part only
  }
  
  delay(5000); // Wait for 5 seconds before taking another reading
}
