# Operating System Process Scheduler (FreeRTOS) ⚙️

A systems-level application that simulates and manages operating system process scheduling, integrating the FreeRTOS kernel for real-time process management.

## 📖 About The Project

This project demonstrates core operating system concepts, focusing on process scheduling, state management, and real-time execution. By utilizing the **FreeRTOS kernel**, the application mimics how a real operating system handles multiple process arrivals, prioritizes tasks, and allocates CPU time efficiently. 

It reads process arrival details dynamically from an input file (`giris.txt`) and schedules them using custom scheduler functions (`run_scheduler`).

### Key Features:
* **FreeRTOS Integration:** Uses a real-time operating system kernel for authentic task management and context switching.
* **Dynamic File Parsing:** Reads process attributes (arrival time, priority, execution time) directly from `giris.txt`.
* **Automated Build System:** Configured with a `Makefile` for streamlined compilation and dependency management.
* **Process Lifecycle Management:** Handles process states (Ready, Running, Blocked, Suspended) efficiently using C.

## 🛠️ Tech Stack

* **Language:** C
* **Kernel:** FreeRTOS (Real-Time Operating System)
* **Build Tool:** Make (Makefile)

## 📁 Repository Structure
* `/FreeRTOS-Kernel-main/` - Core RTOS files.
* `/src/` - Source code including the main scheduler logic.
* `/lib/` - Custom libraries and headers.
* `/bin/` - Compiled executable binaries.
* `giris.txt` - Input dataset for process arrivals.
* `makefile` - Build configuration.

## 🚀 Getting Started

### Prerequisites
* GCC (GNU Compiler Collection)
* Make utility

### Installation & Execution
1. Clone the repository:
   ```bash
   git clone [https://github.com/osamaasker30/OSProject.git](https://github.com/osamaasker30/OSProject.git)
