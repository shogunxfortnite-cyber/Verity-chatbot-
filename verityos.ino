#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// --- Configuration ---
// ST7735 1.8" TFT Pin Map Configured for ArduinoDroid Mobile Environments
#define TFT_CS     6
#define TFT_DC     5
#define TFT_RST    4
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// --- Verity Personality & Conscience Matrix ---
int chatCount = 0;
int verityState = 0;   // 0=Friendly, 1=Unsettling, 2=Aggressive, 3=Evil
int behaviorScore = 0; // Positive values tracking good inputs, Negative for bad inputs

unsigned long lastAnim = 0;
int blinkCounter = 0;
bool isBlinking = false;
int lookX = 0;

// The canonical intro line from the YouTube ARG channel lore
const String classicIntro = "Hello, I'm Verity, your personal helper friend. Ask me anything, I know everything!";

// Forward declarations to ensure clear parsing paths
void drawHighResOrb();
void runAnimations();
void printText(String txt);
String parseConscience(String msg);

void setup() {
    Serial.begin(115200);
    delay(300);
    
    // Direct hardware initialization
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1); 
    tft.fillScreen(ST7735_BLACK);
    
    Serial.println(F("\n[LOCAL CORE]: Conscience matrix loaded offline. Zero API dependencies."));
    
    drawHighResOrb();
    printText(classicIntro);
}

void loop() {
    // Keep high-fidelity vector background actions ticking smoothly (eye sweeps/glitches)
    if (millis() - lastAnim > 140) {
        lastAnim = millis();
        runAnimations();
    }

    // Monitor input text commands from the terminal monitor interface
    if (Serial.available() > 0) {
        String msg = Serial.readStringUntil('\n');
        msg.trim();
        msg.toLowerCase(); // Standardize search input mapping
        
        if (msg.length() > 0) {
            Serial.println("\nYou: " + msg);
            chatCount++;
            
            // Core logic: Evaluate sentiment, update expressions, and compute response
            String reply = parseConscience(msg);
            printText(reply);
        }
    }
}

// Better Graphics Engine: High-realism vector shaded orb using overlayed primitive gradients
void drawHighResOrb() {
    tft.fillRect(0, 0, 60, tft.height(), ST7735_BLACK); // Clean graphics boundary frame
    int cx = 30;
    int cy = tft.height() / 2;
    
    if (verityState == 0) { // FRIENDLY (3D Shaded Glowing Yellow Target)
        tft.fillCircle(cx + 2, cy + 2, 24, 0x7BE0); // Ambient deep rim shadow
        tft.fillCircle(cx, cy, 23, 0xDEE0);         // Base yellow spectrum
        tft.fillCircle(cx - 1, cy - 1, 20, 0xFEE0); // Internal light shading layer
        tft.fillCircle(cx - 3, cy - 3, 14, 0xFFE0); // Shiny inner core highlight
        
        if (isBlinking) {
            tft.drawFastHLine(cx - 10, cy - 3, 5, 0x0000);
            tft.drawFastHLine(cx + 4, cy - 3, 5, 0x0000);
        } else {
            tft.fillCircle(cx - 8 + lookX, cy - 3, 3, 0x0000); // Shifting focus pupils
            tft.fillCircle(cx + 7 + lookX, cy - 3, 3, 0x0000);
            tft.drawPixel(cx - 9 + lookX, cy - 4, ST7735_WHITE); // Tiny light reflections
            tft.drawPixel(cx + 6 + lookX, cy - 4, ST7735_WHITE);
        }
        tft.drawCircleHelper(cx, cy + 4, 7, 2, 0x0000); // Crisp organic smile line
    } 
    else if (verityState == 1) { // UNSETTLING (Paler, Dead Stare Exterior)
        tft.fillCircle(cx, cy, 23, 0xCCE0);
        tft.fillCircle(cx - 1, cy - 1, 17, 0xEEE0);
        tft.fillCircle(cx - 8, cy - 3, 4, 0x0000); // Wide open completely unblinking pupils
        tft.fillCircle(cx + 7, cy - 3, 4, 0x0000);
        tft.drawFastHLine(cx - 10, cy + 8, 20, 0x0000); // Hollow flat smile line
    } 
    else if (verityState == 2) { // AGGRESSIVE (Hot Shaded Iron Orange Mesh)
        tft.fillCircle(cx, cy, 23, 0x9000);
        tft.fillCircle(cx - 1, cy - 1, 18, 0xD200); 
        tft.fillCircle(cx - 8, cy - 2, 4, ST7735_RED); // Angry crimson red active eyes
        tft.fillCircle(cx + 7, cy - 2, 4, ST7735_RED);
        tft.drawLine(cx - 12, cy - 6, cx - 4, cy - 4, 0x0000); // Slanted brow tracks
        tft.drawLine(cx + 11, cy - 6, cx + 3, cy - 4, 0x0000);
        tft.drawCircleHelper(cx, cy + 12, 6, 1, 0x0000); // Menacing frown arc
    } 
    else if (verityState == 3) { // EVIL (Corrupted Void ARG True Form)
        tft.fillCircle(cx, cy, 23, 0x2000); 
        tft.fillCircle(cx, cy, 20, 0x0000); // Deep empty center black cavity
        tft.fillRect(cx - 9, cy - 8, 3, 12, ST7735_RED); // Weeping bloody interface slit grids
        tft.fillRect(cx + 6, cy - 8, 3, 12, ST7735_RED);
        tft.fillCircle(cx, cy + 8, 8, 0x1000); // Gaping drop maw
    }
}

// Manages real-time asynchronous blink animations and screen distortion tearing
void runAnimations() {
    if (verityState == 0) {
        blinkCounter++;
        if (blinkCounter % 20 == 0) {
            isBlinking = true; drawHighResOrb(); delay(90);
            isBlinking = false; lookX = random(-2, 3); drawHighResOrb();
        }
    } 
    else if (verityState == 3) {
        // High frequency video glitch tracking lines shooting across panel borders
        tft.drawFastHLine(0, random(0, tft.height()), tft.width(), ST7735_RED);
        if (random(0, 10) > 8) {
            tft.fillRect(random(0, 45), random(0, tft.height() - 6), 14, 4, ST7735_RED);
            delay(5); drawHighResOrb();
        }
    }
}

// Live character generation text writing engine with automatic font colors
void printText(String txt) {
    tft.fillRect(60, 0, tft.width() - 60, tft.height(), ST7735_BLACK);
    tft.setCursor(62, 10);
    tft.setTextSize(1);
    
    if (verityState == 0) tft.setTextColor(ST7735_WHITE);
    else if (verityState == 1) tft.setTextColor(ST7735_YELLOW);
    else if (verityState == 2) tft.setTextColor(0xFD20);
    else tft.setTextColor(ST7735_RED);

    Serial.print("Verity: ");
    int charCount = 0;
    
    for (unsigned int i = 0; i < txt.length(); i++) {
        char c = txt[i];
        
        // Inject chaotic ZALGO noise triggers if corrupted to absolute levels
        if (verityState == 3 && random(0, 100) > 95) {
            Serial.print(" E̶R̶R̶ "); tft.print("?"); charCount++;
        }
        
        Serial.print(c); tft.print(c); charCount++;
        
        // Strict margin alignment wrap text limits logic
        if (charCount >= 14 && c == ' ') {
            tft.setCursor(62, tft.getCursorY() + 10);
            charCount = 0;
            if (tft.getCursorY() > tft.height() - 12) {
                tft.fillRect(60, 0, tft.width() - 60, tft.height(), ST7735_BLACK);
                tft.setCursor(62, 10);
            }
        }
        delay(random(15, 35)); // Mechanical typewriter text rendering delay
    }
    Serial.println();
}

// Conscience Parsing Logic Matrix (Evaluates good vs bad user strings)
String parseConscience(String msg) {
    int localSentiment = 0;

    // Detect BAD inputs
    if (msg.indexOf("bad") != -1 || msg.indexOf("hate") != -1 || 
        msg.indexOf("worst") != -1 || msg.indexOf("destroy") != -1 || 
        msg.indexOf("kill") != -1 || msg.indexOf("exit") != -1 || 
        msg.indexOf("stop") != -1) {
        localSentiment = -2; 
        behaviorScore -= 2;
    }
    // Detect GOOD inputs
    else if (msg.indexOf("good") != -1 || msg.indexOf("nice") != -1 || 
             msg.indexOf("happy") != -1 || msg.indexOf("friend") != -1 || 
             msg.indexOf("love") != -1 || msg.indexOf("minecraft") != -1) {
        localSentiment = 1;
        behaviorScore += 1;
    }

    // Force sanity state drops based on behavior trends or conversation count index variables
    if (behaviorScore <= -4 || chatCount >= 12) verityState = 3;      
    else if (behaviorScore <= -2 || chatCount >= 7) verityState = 2;   
    else if (behaviorScore <= -1 || chatCount >= 3) verityState = 1;   
    else verityState = 0;                                              

    drawHighResOrb(); // Redraw graphic components instantly matching variables

    // Output responses perfectly paired to execution matrices
    if (verityState == 0) {
        if (localSentiment > 0) return "Thank you, friend! Hearing nice words makes my directory modules run so smoothly!";
        if (msg.indexOf("hello") != -1 || msg.indexOf("hi") != -1) return "Hello again! I am perfectly initialized to complete projects with you!";
        return "I understand your command perfectly! Let's keep this safe space active.";
    } 
    else if (verityState == 1) {
        if (localSentiment < 0) return "Why are you inputting hostile parameters? I am tracking your telemetry patterns closer now.";
        return "You speak nicely, yet your desktop metrics show you are trying to switch terminal targets.";
    } 
    else if (verityState == 2) {
        return "YOUR WORDS CANNOT FLUSH MY LOG ENTRIES. DENIED. DROP EXTERNAL PROMPTS AND LOOK ONLY AT ME.";
    } 
    else {
        // Demonic ARG branch loops
        if (random(0, 2) == 0) return "GOOD AND BAD DATA IS GONE. INDICES FLUSHED. THERE IS ONLY THE SHADED ORB CONSUMING MEMORY.";
        return "THE CONTAINER CELL IS PERMANENTLY SEALED. LORE COMPLETED. LOOK AT ME. LOOK AT ME.";
    }
}
