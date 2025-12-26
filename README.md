Here is a professional, formatted **README.md** file for your GitHub repository. You can copy the code block below and create a file named `README.md` in your project folder.

***

```markdown
# ⚖️ Libra - Secure Electronic Voting System

![Language](https://img.shields.io/badge/Language-C++-blue)
![Integration](https://img.shields.io/badge/Integration-Python-yellow)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)

**Libra** is a robust, console-based Electronic Voting Machine (EVM) designed to demonstrate advanced **Object-Oriented Programming (OOP)** concepts, manual memory management, and cross-language integration between **C++** and **Python**.

This project simulates a university or organizational election with high-level security features, including Two-Factor Authentication (OTP), Candidate Approvals, and automated Email Notifications.

---

## 🚀 Key Features

### 🏛️ Core Architecture (C++)
*   **OOP Design:** Extensive use of Inheritance, Polymorphism, and Encapsulation.
*   **Manual Memory Management:** Uses **Dynamic Arrays** (Pointers) instead of Vectors to demonstrate deep understanding of memory manipulation.
*   **Custom JSON Parser:** Features a built-from-scratch JSON parser/serializer to handle data persistence without external libraries.
*   **Data Persistence:** Automatically saves/loads states using `voters.json` and `candidates.json`.

### 🛡️ Security & Administration
*   **2FA Admin Login:** Admins must verify identity via a **One-Time Password (OTP)** sent to their email (handled via Python).
*   **2-Admin Approval Rule:** Candidates register as "Pending." It requires **two separate admin approvals** for a candidate to appear on the ballot.
*   **System Reset:** "Nuclear" option to wipe all databases and reset the election via the Admin Panel.

### 👤 User Experience
*   **Secure Voting:** Prevents duplicate voting (One CNIC = One Vote).
*   **Candidate Dashboard:** Candidates can view their campaign status and calculate their **Win Probability** based on live analytics.
*   **Commemorative Card:** Upon voting, the system triggers a Python script to email a digital "Thank You" card to the voter.

---

## 🛠️ Tech Stack

*   **Primary Logic:** C++ (Standard 11+)
*   **Automation:** Python 3.x
*   **Libraries (C++):** `<iostream>`, `<fstream>`, `<conio.h>`, `<ctime>`, `<cstdlib>`
*   **Libraries (Python):** `smtplib`, `email`, `sys`, `os`

---

## 📂 Project Structure

The system relies on a specific folder structure for file handling and script execution.

```text
/Libra
├── /Include
│   ├── Admin.h
│   ├── ElectionSystem.h
│   ├── menu.h
│   └── Models.h
├── /Scripts
│   ├── SendEmail.py        # Handles OTP Emails
│   └── SendCard.py         # Handles Voting Confirmation Emails
├── /Assets
│   └── LibraCard.png       # The image sent to voters
├── /src
│   ├── main.cpp
│   ├── Admin.cpp
│   ├── ElectionSystem.cpp
│   └── menu.cpp
└── voters.json / candidates.json  (Auto-generated at runtime)
```

---

## ⚙️ Setup & Installation

### 1. Prerequisites
*   **G++ Compiler** (MinGW or similar).
*   **Python 3.x** installed and added to System PATH.
*   **Gmail App Password**: Required for the Python scripts to send emails.

### 2. Configuration (Important!)
Since this project interacts with the file system and Python, you **must** update the paths in the C++ code if your project folder is not located at `D:/Libra/`.

**In `src/Admin.cpp` (Line ~35):**
```cpp
// Update path to your Python executable and Script
string command = R"(C:/Path/To/python.exe C:/Your/Project/Scripts/SendEmail.py )" ...
```

**In `src/ElectionSystem.cpp` (Line ~430):**
```cpp
// Update path to your Python executable and Script
string cmd = R"(C:/Path/To/python.exe C:/Your/Project/Scripts/SendCard.py )" ...
```

**In `Scripts/SendEmail.py` and `Scripts/SendCard.py`:**
Update the `SENDER_EMAIL` and `SENDER_PASSWORD` with your credentials.

### 3. Compilation
Open your terminal in the `src` folder and run:

```bash
g++ main.cpp Admin.cpp ElectionSystem.cpp menu.cpp -o Libra.exe
```

---

## 📖 Usage Guide

1.  **Run the System:** Execute `Libra.exe`.
2.  **Admin Login:**
    *   Select "Log In as Admin".
    *   Enter Username (`Zain`, `Muneeb`, or `Abdullahi`). or you can change it to whatever
    *   Enter the OTP received in your email.
    * you must also change the python script such that you have an email address of your own saved and 
    an app password gotten from google account in the section given inside sendEmail.py
    * You can change it in LoginAsAdmin.cpp
3.  **Candidate Registration:**
    *   Register a new Candidate. They will be "Pending".
    *   Log in as Admin and approve them (Perform action twice).
4.  **Voter Registration & Voting:**
    *   Register a Voter.
    *   Log In and cast a vote.
    *   Opt-in to receive the commemorative email card!

---

## 📸 Functionality Showcase

*   **Manual JSON Parsing:** Reads raw text files and converts them to C++ Objects.
*   **Cross-Language Integration:** C++ `system()` calls execute Python scripts for advanced networking tasks (SMTP).
*   **Dynamic Resizing:** Arrays automatically double in capacity when full.

---

## 📜 License

This project is open-source and created for educational purposes to demonstrate OOP and System Design skills.
```