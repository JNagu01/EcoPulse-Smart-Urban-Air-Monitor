# EcoPulse: Smart Urban Air Monitor

A 100% simulated IoT environmental monitoring prototype designed for smart city micro-climates. This project leverages an ESP32 microcontroller simulation to track real-time atmospheric metrics and stream data directly to a cloud web dashboard.

## 🚀 System Architecture
- **Simulation Layer:** Wokwi IoT Emulator
- **Cloud Dashboard & Database:** ThingSpeak IoT Platform
- **Microcontroller Core:** ESP32 programmed via Arduino IDE Frameworks

## 📊 Core Features
- **Real-Time Data Streams:** Tracks AQI (via simulated potentiometer), Temperature (°C), and Humidity (%).
- **Threshold-Driven Alerts:** Auto-activates a physical LED and cloud indicator flag when the AQI score crosses the safe threshold (400+).
- **Cloud Architecture Deployment:** Features continuous data logging with automatic time-stamping for historical trend logs.
