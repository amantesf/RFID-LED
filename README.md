# RFID Access Control System

This project is an RFID-based access control system that uses an MFRC522 RFID reader, an LCD display, and LEDs to grant or deny access based on the UID of the scanned RFID card. The project is built using an Arduino.

## Components Used

- Arduino (Uno, Mega, or any compatible board)
- MFRC522 RFID reader
- 16x2 LCD display
- 3 LEDs (Red, Green, Blue)
- Jumper wires
- Breadboard
- Resistors (220 ohms for LEDs)

## Pin Configuration

| Component | Pin    | Arduino Pin |
|-----------|--------|-------------|
| Red LED   | Anode  | 6           |
| Green LED | Anode  | 5           |
| Blue LED  | Anode  | 4           |
| LCD       | RS     | 8           |
|           | E      | 9           |
|           | D4     | 10          |
|           | D5     | 11          |
|           | D6     | 12          |
|           | D7     | 13          |
| MFRC522   | SDA    | 53          |
|           | RST    | 3           |

## Setup and Usage

1. **Wiring**: Connect the components as per the pin configuration table above.
2. **Install Libraries**:
   - Install the `MFRC522` library.
   - Install the `LiquidCrystal` library.
3. **Upload Code**: Upload the provided `RFID_Access_Control.ino` sketch to your Arduino board.
4. **Modify UID**: In the sketch, update the line `if (content.substring(1) == "DE 7E 6D 17")` with the UID(s) of your authorized card(s).
5. **Run**: Open the Serial Monitor, set the baud rate to `9600`, and scan your RFID card.

## How It Works

- When the system is powered on, the LCD displays "Scan card:".
- When an RFID card is presented to the reader, its UID is read and printed on the Serial Monitor.
- If the UID matches the authorized UID, the green LED flashes and "Access Granted" is displayed on the LCD.
- If the UID does not match, the red LED flashes and "Access denied" is displayed on the LCD.

## Functions

- `setup()`: Initializes the LCD, Serial communication, SPI bus, and MFRC522 module. Sets LED pins as outputs and initializes them to LOW.
- `loop()`: Continuously checks for the presence of a new card. Reads the card's UID, checks if it matches the authorized UID, and updates the LCD and LEDs accordingly.
- `pleaseWait()`: Displays a "Please wait" message with a loading effect on the LCD.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributions

Contributions are welcome! Please fork this repository and submit a pull request for any enhancements or bug fixes.

## Acknowledgements

- [MFRC522 Library](https://github.com/miguelbalboa/rfid)
- [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)

## Contact

For any inquiries, please contact me at tesfayee.amanuel@gmail.com
