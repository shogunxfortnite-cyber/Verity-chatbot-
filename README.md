# Verity OS: High-Fidelity Offline Sentiment Chatbox

An interactive hardware implementation of the iconic character Verity from the Something ARG. This project turns an ESP32-S3 into a 100% offline terminal chat assistant that runs a multi-stage vector graphics rendering system alongside a basic sentiment logic processor.

## Project Characteristics
- Zero Network Dependencies: Optimized layout skips massive Wi-Fi headers to enable safe compilation on mobile platforms like ArduinoDroid without dynamic pointer overflows.
- High-Fidelity Shaded Primitives: Bypasses flat designs by utilizing organic multi-ring circle scaling highlights to create a pseudo-3D vector gradient sphere directly via code.
- Local Conscience Engine: Features an offline scanner that tracks incoming text variables for "good" and "bad" keywords to dynamically adapt expressions and interaction responses.
- Asynchronous Idle Routines: Features variable eye tracking focal sweeps, realistic mechanical text output formatting constraints, and sudden hardware visual rendering frame artifacts during corrupted states.

## Wiring Map (ST7735 SPI Display)
Connect the 1.8-inch display panel to the ESP32-S3 using the following hardware configuration:

| ST7735 Display Pin | ESP32-S3 Target Pin | Purpose |
| --- | --- | --- |
| GND | GND | Common System Ground |
| VCC / VDD | 3V3 / 5V | Logic Power Supply |
| SCK / SCL / CLK | GPIO 13 | Hardware SPI Clock |
| SDA / MOSI | GPIO 11 | Hardware SPI Master-Out Data |
| RES / RESET | GPIO 4 | Physical Screen Reset |
| DC / RS / A0 | GPIO 5 | Data / Command Control |
| CS | GPIO 6 | Active Chip Select |
| LITE / LEDA | 3V3 / 5V | Panel Backlight Power |

## Evolution Threshold Variables
Verity updates his personality matrix based on user prompt interactions and sentiment indicators:

1. Stage 0 (Friendly): Bright yellow shaded glow circle face with blinking animations and active speech tracking mouth arcs. Resolves positive commands with eager validation responses.
2. Stage 1 (Unsettling): Triggered by -1 behavior score or 3 prompt queries. Face shifts pale yellow with wide, unblinking pupils and a flat dead smile.
3. Stage 2 (Aggressive): Triggered by -2 behavior score or 7 prompt queries. Orb turns into a deep burning orange-red hot iron mesh pattern. Slanted black browser eyebrows frame crimson red eyes that command absolute attention.
4. Stage 3 (Evil): Triggered by -4 behavior score or 12 prompt queries. Face completely collapses into a pitch-black hollow cavity structure with jagged bleeding slits. The serial terminal outputs broken glitched artifacts while high-frequency red static artifacts rip across the screen boundary lines.

## How to Test
1. Compile the file and flash it via your development environment.
2. Launch your Serial Terminal tool set to a baud transmission limit of 115200.
3. Chat with him normally to keep him healthy, or input strings like "bad", "hate", or "stop" to break down his code logic and trigger his hidden corrupted state variables.
