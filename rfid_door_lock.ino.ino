#include <SPI.h>
#include <MFRC522.h>

// Pin connections
#define SS_PIN 10
#define RST_PIN 9
#define RELAY_PIN 3
#define BUZZER_PIN 2
#define GREEN_LED 5
#define RED_LED 6
#define EXIT_BUTTON 4
// Raj`s cod
// Timing
#define ACCESS_TIME 2000
#define WRONG_CARD_TIME 1000

// RFID object
MFRC522 rfid(SS_PIN, RST_PIN);
// Raj`s code
// Authorized card UIDs
String allowedCards[] = {
  "XX XX XX XX",  // Replace with your card UID
  "XX XX XX XX",
  "XX XX XX XX"
};

int totalCards = sizeof(allowedCards) / sizeof(allowedCards[0]);
// Raj`s code
void setup() {

  Serial.begin(9600);

  // Start SPI and RFID
  SPI.begin();
  rfid.PCD_Init();

  // Pin modes
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(EXIT_BUTTON, INPUT_PULLUP);

  // Initial states
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.println("RFID Door Lock System Ready");
  Serial.println("Scan your card...");
}

void loop() {

  // Exit button pressed
  if (digitalRead(EXIT_BUTTON) == LOW) {
    openDoor();
    delay(300);
  }

  // Check if card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read card
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Store UID   // Raj`s code
  String cardID = "";

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      cardID += " 0";
    }
    else {
      cardID += " ";
    }

    cardID += String(rfid.uid.uidByte[i], HEX);
  }

  cardID.toUpperCase();

  Serial.print("Card UID : ");
  Serial.println(cardID);

  // Check authorized card   // Raj`s code
  bool accessGranted = false;

  for (int i = 0; i < totalCards; i++) {

    if (cardID.substring(1) == allowedCards[i]) {
      accessGranted = true;
      break;
    }
  }

  // If authorized
  if (accessGranted) {

    Serial.println("Access Granted");
    openDoor();
  }

  // If not authorized
  else {

    Serial.println("Access Denied");

    digitalWrite(RED_LED, HIGH);

    tone(BUZZER_PIN, 1000);

    delay(WRONG_CARD_TIME);

    noTone(BUZZER_PIN);

    digitalWrite(RED_LED, LOW);
  }

  // Stop reading current card  // Raj`s code
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Function to unlock door// Raj`s code
void openDoor() {

  digitalWrite(GREEN_LED, HIGH);

  digitalWrite(RELAY_PIN, LOW);

  delay(ACCESS_TIME);

  digitalWrite(RELAY_PIN, HIGH);

  digitalWrite(GREEN_LED, LOW);
}