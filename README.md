# Student Academic Planner System (C) 📅

## Overview
A lightweight, command-line application engineered in the C programming language to assist university students in tracking and organizing academic assignment deadlines. Developed as part of my Program Design coursework, this system replaces manual tracking with an automated, terminal-based planner that guarantees data persistence across system sessions via automated file handling.

## Technical Stack & Concepts
* **Language & Environment:** C, Visual Studio Code, Command-Line Interface (CLI)
* **Core C Concepts:** Custom Data Structures (`struct`), File I/O Operations (`fopen`, `fprintf`, `fscanf`), Pointers, Dynamic Array Shifting
* **System Design:** Input Validation, Buffer Management, Modular Function Architecture

## What is Included in this Repository
* **C Source Code:** The `.c` and `.h` files containing the core logic, menu navigation loops, and automated CSV file-handling scripts.
* **Sample Data Storage:** The external comma-separated values (`.csv`) file used by the application to persistently store student task records.
* **Project Report:** Full coursework documentation detailing the system flowcharts, algorithmic logic, and sample terminal execution outputs.

## Core Architecture & Features
* **Automated Data Persistence:** Automatically reads from and writes to an external `.csv` file upon application startup and modification, ensuring no assignment deadlines are lost when the program closes.
* **Custom Data Structures:** Uses modular C `struct` definitions to cleanly encapsulate student IDs, course titles, assignment names, due dates, and completion status flags.
* **Input Validation & Crash Prevention:** Implements custom buffer clearing and strict input validation to prevent terminal crashes from accidental typos or out-of-bounds user entries.
* **Full Task Management:** Users can add new assignment deadlines, view all tasks formatted in a clean ASCII table, search for specific records by Student ID to update completion status (`Pending` vs `Done`), and delete expired tasks.
