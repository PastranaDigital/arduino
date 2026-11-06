// C++ code
// Sets up 6 options for connecting LEDs for Props

// Using Digital Pins
const int RANDOM_MOSTLY_ON_PIN = 2;
const int OPP_SLOW_PIN = 3; // PWM Pin if fading is desired in the future
const int RANDOM_MOSTLY_OFF_PIN = 4;
const int FAST_PIN = 5;     // PWM Pin if fading is desired in the future
const int SLOW_PIN = 6;     // PWM Pin if fading is desired in the future
const int SOLID_PIN = 13;

// --- Alternating Lights Setup ---
const unsigned long altInterval = 1000; // Alternates every 1000ms (1 sec)
unsigned long previousAltMillis = 0;
bool altState = false;

// --- Random Mostly On Light Setup ---
unsigned long previousRandomMostlyOnMillis = 0;
unsigned long randomMostlyOnInterval = 100; // Initial random delay
bool randomMostlyOnState = false;

// --- Random Mostly Off Light Setup ---
unsigned long previousRandomMostlyOffMillis = 0;
unsigned long randomMostlyOffInterval = 100; // Initial random delay
bool randomMostlyOffState = false;

// --- Fast Blinking Setup ---
const unsigned long fastInterval = 400; // Blink every 400ms
unsigned long previousFastMillis = 0;
bool fastState = false;

void setup()
{
  pinMode(SLOW_PIN, OUTPUT);
  pinMode(FAST_PIN, OUTPUT);
  pinMode(RANDOM_MOSTLY_ON_PIN, OUTPUT);
  pinMode(SOLID_PIN, OUTPUT);
  pinMode(OPP_SLOW_PIN, OUTPUT);
  randomSeed(analogRead(A0));
  
  digitalWrite(SLOW_PIN, LOW);
  digitalWrite(FAST_PIN, LOW);
  digitalWrite(RANDOM_MOSTLY_ON_PIN, LOW);
  digitalWrite(SOLID_PIN, LOW);
  digitalWrite(OPP_SLOW_PIN, LOW);
}

void loop()
{
  unsigned long currentMillis = millis();
  
  // Solid Light
  digitalWrite(SOLID_PIN, HIGH);
  
  // ----------------------
  // TASK 1: Alternate Lights
  // ----------------------
  if (currentMillis - previousAltMillis >= altInterval) {
    previousAltMillis = currentMillis;
    altState = !altState;

    if (altState) {
      digitalWrite(SLOW_PIN, HIGH);
      digitalWrite(OPP_SLOW_PIN, LOW);
    } else {
      digitalWrite(SLOW_PIN, LOW);
      digitalWrite(OPP_SLOW_PIN, HIGH);
    }
  }
  
  // ----------------------
  // TASK 2: Randomly Blink Light - Mostly On
  // ----------------------
  if (currentMillis - previousRandomMostlyOnMillis >= randomMostlyOnInterval) {
    previousRandomMostlyOnMillis = currentMillis;

    // Toggle the random light state
    randomMostlyOnState = !randomMostlyOnState;
    digitalWrite(RANDOM_MOSTLY_ON_PIN, randomMostlyOnState ? HIGH : LOW);

    // Pick a new random duration for the state (between 50ms flicker and 600ms hold)
    if (randomMostlyOnState) {
      randomMostlyOnInterval = random(100, 1000);  // How long the light stays ON
    } else {
      randomMostlyOnInterval = random(50, 400); // How long the light stays OFF
    }
  }

  // ----------------------
  // TASK 3: Randomly Blink Light - Mostly Off
  // ----------------------
  if (currentMillis - previousRandomMostlyOffMillis >= randomMostlyOffInterval) {
    previousRandomMostlyOffMillis = currentMillis;

    // Toggle the random light state
    randomMostlyOffState = !randomMostlyOffState;
    digitalWrite(RANDOM_MOSTLY_OFF_PIN, randomMostlyOffState ? HIGH : LOW);

    // Pick a new random duration for the state (between 50ms flicker and 600ms hold)
    if (randomMostlyOffState) {
      randomMostlyOffInterval = random(250, 600);  // How long the light stays ON
    } else {
      randomMostlyOffInterval = random(1000, 2500); // How long the light stays OFF
    }
  }
  
  // ----------------------
  // TASK 4: Fast Blink Light
  // ----------------------
  if (currentMillis - previousFastMillis >= fastInterval) {
    previousFastMillis = currentMillis;
    fastState = !fastState;

    if (fastState) {
      digitalWrite(FAST_PIN, HIGH);
    } else {
      digitalWrite(FAST_PIN, LOW);
    }
  }
}
