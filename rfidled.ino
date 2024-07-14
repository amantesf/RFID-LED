#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

// Define pin numbers for LEDs and RFID module
#define BLUE 4
#define GREEN 5
#define RED 6
#define SS_PIN 53
#define RST_PIN 3

// Create instances for the RFID reader and the LCD display
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() 
{
  // Set LED pins as outputs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  // Initialize LEDs to be off
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  // Initialize the LCD display with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.print("Scan card:"); // Display initial message
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  SPI.begin(); // Start SPI bus
  mfrc522.PCD_Init(); // Initialize the MFRC522 module
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void loop() 
{
  // Check if a new card is present
  if (!mfrc522.PICC_IsNewCardPresent()) 
  {
    return; // If no new card is present, return to the beginning of the loop
  }

  // Attempt to read the card's UID
  if (!mfrc522.PICC_ReadCardSerial()) 
  {
    return; // If the card's UID cannot be read, return to the beginning of the loop
  }

  // Print the card's UID to the serial monitor
  Serial.print("UID tag :");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    // Print each byte of the UID in hexadecimal format
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase(); // Convert the UID to uppercase

  // Clear the LCD display before showing a new message
  lcd.clear();
  pleaseWait();
  pleaseWait();

  // Check if the UID matches an authorized card
  if (content.substring(1) == "DE 7E 6D 17") // Change this UID to match your authorized card(s)
  { 
    lcd.clear();
    lcd.print("Access Granted"); // Display access granted message
    Serial.println("Authorized access");
    // Flash the green LED to indicate authorized access
    for (int i = 0; i < 5; i++) 
    {
      digitalWrite(GREEN, HIGH);
      delay(100);
      digitalWrite(GREEN, LOW);
      delay(100);
    }
  }
  else 
  {
    lcd.clear();
    lcd.print("Access denied"); // Display access denied message
    lcd.setCursor(0, 1);
    lcd.print("Try again:");
    Serial.println("Access denied");
    // Flash the red LED to indicate denied access
    for (int i = 0; i < 5; i++) 
    {
      digitalWrite(RED, HIGH);
      delay(100);
      digitalWrite(RED, LOW);
      delay(100);
    }
  }

  // Halt the card's communication and stop encryption
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// Display a "Please wait" message with a loading effect
void pleaseWait()
{
  lcd.clear();
  lcd.print("Please wait");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
}
