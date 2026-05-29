# 🖥️ Smart Automatic Parking Lot Management System

## 📌 Project Overview
The objective of this project was to modernize and automate the traditional manual process of vehicle parking management. Developed entirely in C, the system replaces paper logs by allowing operators to dynamically manage parking capacity, track vehicle entries and exits, calculate fees based on vehicle classifications, and generate automated receipts.

## ⚙️ Core Engineering Concepts & Software Logic
Unlike standard introductory projects, this system was designed with scalability and memory efficiency in mind:
- **Dynamic Memory Management:** Utilized `malloc` and `free` to allow the system to adapt to different parking lot sizes at runtime.
- **Advanced Data Structures:** Implemented `structs` and `enums` to efficiently store and organize complex vehicle data.
- **Algorithmic Approach:** Applied Linear Search algorithms for quick vehicle retrieval and developed a Recursive function to calculate total potential revenue.
- **Data Persistence:** Integrated File I/O operations to permanently save exit transactions and generate log files (`receipt.txt`).

## 🚀 System Features
- **Live Visual Grid:** Renders a real-time visual representation of the parking slots (Green for Free, Red for Occupied).
- **Strict Input Validation:** Validates license plate formats (e.g., ensuring string length and the inclusion of a '-' character).
- **Automated Billing:** Calculates the precise fee based on the vehicle type and duration of stay, automatically freeing the memory slot upon exit.

## 📁 Files Included
- The core `.c` source code file.
- `Project Report.pdf`: Full documentation, flowcharts, and I/O screenshots.
-
