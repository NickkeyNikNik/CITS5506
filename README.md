# CITS5506
 
# Smart Cup Coaster - CITS5506 Internet of Things Project

This project, Smart Cup Coaster, was developed as part of the CITS5506 - Internet of Things (IoT) course at The University of Western Australia. The goal of this project was to design and implement a smart IoT-enabled coaster that enhances the beverage consumption experience by providing real-time temperature monitoring, intelligent notifications, and personalized user settings. The Smart Cup Coaster uses sensors to measure the temperature of beverages and alerts users when their drink reaches the desired temperature.

## Project Overview

The Smart Cup Coaster is designed to solve the problem of beverages being consumed at non-ideal temperatures, which often leads to waste. This IoT-enabled device informs users when their drink has reached the optimal temperature, helping to improve user satisfaction and reduce waste by ensuring beverages are consumed at the right temperature.

### Key Features:
- **Real-Time Temperature Monitoring**: The Smart Cup Coaster continuously monitors the temperature of the beverage using an IR temperature sensor.
- **Ultrasonic Sensor**: Detects the presence of a cup on the coaster and triggers the device to start monitoring.
- **LED Indicators**: Three LEDs (blue, yellow, red) provide visual feedback on the temperature: cold, warm, or hot.
- **Mobile Application Integration**: A mobile app, powered by the RemoteXY API, allows users to view temperature readings, customize preferences, and receive notifications.
- **Pushbullet Notifications**: Users receive real-time notifications when their beverage reaches the desired temperature.
- **Customizable Temperature Settings**: Users can define their preferred temperature ranges for cold, warm, and hot beverages, making the experience more personalized.

## Hardware Components
The hardware implementation includes:
1. **Arduino TTGO T-Beam**: The main microcontroller for processing and connectivity.
2. **IR Temperature Sensor**: Measures the temperature of the beverage.
3. **Ultrasonic Sensor**: Detects whether a cup is placed on the coaster.
4. **LEDs (Red, Yellow, Blue)**: Indicate the temperature state of the beverage.
5. **Pushbullet Integration**: Sends notifications to users' smartphones when the beverage reaches the desired temperature.

### Power Requirements
The system operates on 5V power, supplied through a USB cable. It is designed to be energy efficient, with the ability to enter sleep mode when not in use.

## Software Architecture
The software consists of:
- **RemoteXY API**: Provides an intuitive mobile interface where users can monitor the temperature and configure their preferences.
- **Pushbullet API**: Handles notifications to keep users informed about their beverage’s status in real-time.
- **ESP32 Wi-Fi Module**: Enables communication between the mobile app and the Smart Coaster.

### Software Features:
- **Real-Time Monitoring**: Continuously reads temperature data from the IR sensor and updates the mobile app.
- **Visual Feedback**: Uses the LEDs to indicate beverage temperature status.
- **Wi-Fi Connectivity**: Handles connection management for both RemoteXY and Pushbullet notifications.
- **Temperature Settings**: Allows users to define their own thresholds for cold, warm, and hot beverages.
  
## Installation and Usage
1. **Hardware Setup**: Assemble the Smart Coaster hardware, ensuring proper connections between the Arduino board, sensors, and LEDs.
2. **Software Setup**: Load the provided Arduino code onto the TTGO T-Beam using the Arduino IDE. Ensure the RemoteXY and Pushbullet APIs are configured with the correct credentials.
3. **Mobile App**: Download the RemoteXY app and connect it to the Smart Coaster through the Wi-Fi access point created by the device.

### Operation:
1. Place a cup on the coaster.
2. The ultrasonic sensor will detect the cup and begin monitoring its temperature.
3. The LEDs will indicate whether the drink is cold (blue), warm (yellow), or hot (red).
4. When the beverage reaches the user-defined ideal temperature, a Pushbullet notification is sent to the user’s mobile device.

## Challenges and Solutions
- **Hardware Availability**: Initially, the project encountered delays due to the unavailability of key components, particularly the IR sensor. This was resolved by selecting a compatible alternative.
- **Connectivity Issues**: The initial choice of Wi-Fi module, the ESP8266, faced reliability issues. The TTGO T-Beam was selected as a more stable alternative.
- **Notification System**: Pushbullet, though effective for Android, posed challenges for iOS users. Future improvements may include a cross-platform solution.

## Future Enhancements
- **Compact Design**: The current prototype is relatively large. Future iterations could focus on reducing the device size for increased portability.
- **IoT Ecosystem Integration**: The Smart Coaster could be integrated with broader smart home systems, allowing users to control and monitor it alongside other IoT devices.
- **Hydration Monitoring**: Expanding the system to track user hydration levels and offer reminders for regular fluid intake.

## Conclusion
The Smart Cup Coaster represents an innovative approach to enhancing the beverage consumption experience through the application of IoT technology. By combining real-time monitoring, personalized settings, and intelligent notifications, the project successfully bridges the gap between convenience and personalization.
