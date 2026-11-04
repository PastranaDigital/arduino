// C++ code
// Sets up 5 options for connecting LEDs for Props

const int SLOW_PIN = A1;
const int FAST_PIN = A2;
const int RANDOM_PIN = A3;
const int SOLID_PIN = A4;
const int OPP_SLOW_PIN = A5;

// --- Alternating Lights Setup ---
const unsigned long altInterval = 1000; // Alternates every 1000ms (1 sec)
unsigned long previousAltMillis = 0;
bool altState = false;

// --- Random Light Setup ---
unsigned long previousRandomMillis = 0;
unsigned long randomInterval = 100; // Initial random delay
bool randomState = false;

// --- Fast Blinking Setup ---
const unsigned long fastInterval = 400; // Blink every 400ms
unsigned long previousFastMillis = 0;
bool fastState = false;

void setup()
{
  pinMode(SLOW_PIN, OUTPUT);
  pinMode(FAST_PIN, OUTPUT);
  pinMode(RANDOM_PIN, OUTPUT);
  pinMode(SOLID_PIN, OUTPUT);
  pinMode(OPP_SLOW_PIN, OUTPUT);
  randomSeed(analogRead(A0));
  
  digitalWrite(SLOW_PIN, LOW);
  digitalWrite(FAST_PIN, LOW);
  digitalWrite(RANDOM_PIN, LOW);
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
  // TASK 2: Randomly Blink Light
  // ----------------------
  if (currentMillis - previousRandomMillis >= randomInterval) {
    previousRandomMillis = currentMillis;

    // Toggle the random light state
    randomState = !randomState;
    digitalWrite(RANDOM_PIN, randomState ? HIGH : LOW);

    // Pick a new random duration for the state (between 50ms flicker and 600ms hold)
    if (randomState) {
      randomInterval = random(100, 1000);  // How long the light stays ON
    } else {
      randomInterval = random(50, 400); // How long the light stays OFF
    }
  }
  
  // ----------------------
  // TASK 3: Fast Blink Light
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
