Secure Military Communication System (C)

A console-based secure military communication system built in C, designed to demonstrate coded, non-verbal, and stealth message transmission inspired by military signaling principles.

This project aligns strongly with Theme w-9 (hidden communication) and partially with Theme w-1 (signals and emotional states).

Project Overview

In sensitive environments, spoken communication can be dangerous.
This system allows users to send encrypted messages using signal levels instead of plain language.

Messages are:

Encrypted using a shift-based cipher

Categorized by threat level

Logged securely with timestamps

Decoded only with the correct key

Features

🔐 User Authentication

Username + password protection

Limited login attempts

📡 Signal-Based Communication

Calm (Low priority)

Alert (Medium priority)

Danger (High priority)

🔒 Message Encryption & Decryption

Shift-based encryption

Uppercase transformation for consistency

🗂️ Transmission History

Encrypted messages saved with:

Time

User

Threat level

Shift value

🎨 Color-Based Output

Green terminal output for clarity (Windows)

Signal Mapping
Level	Color	Frequency	Shift
Calm	Blue	300 Hz	+1
Alert	Yellow	600 Hz	+2
Danger	Red	1000 Hz	+4
Technologies Used

Language: C

File Handling

String Manipulation

Time & Date Handling

Console-based UI

How It Works

User logs in using credentials

Selects a signal level

Enters a message

System encrypts the message

Encrypted message is displayed and saved

Authorized users can decrypt messages later

How to Run
Requirements

GCC compiler

Windows / Linux / macOS terminal

Compile
gcc main.c -o military_comm

Run
./military_comm


(Default password: 1234)

Project Structure
├── main.c
├── military_transmissions.txt
└── README.md

Theme Mapping
Theme w-9 (Hidden Communication)

Messages are unreadable without shift keys

No plain-text transmission

Signal-based meaning instead of direct language

Theme w-1 (Signals & Emotion)

Threat levels represent emotional intensity

Colors and frequencies act as non-verbal indicators

Use Cases

Military simulation projects

Hackathon demos

Academic presentations

Secure communication concept proof

Future Improvements

Emergency panic signal

Dynamic encryption keys

Fake decoy transmissions

Hardware integration (Arduino / buttons)

GUI-based interface

Author

Abdullah Al Sadik
Shibli Noman Arnob
Disclaimer

This project is for educational purposes only.
It does not represent real military encryption standards.
