
---------------------------------------
HEALTH-TRACKING SYSTEM
---------------------------------------
A simple health monitoring system aligned with SDG 3: Good Health and Well-being
This project is a console-based C++ application designed to help users track their 
daily health activities, compute BMI, check symptoms, and view their health history. 
It uses basic Data Structures & Algorithms such as Linked Lists, Queues, and Bubble Sort, 
along with file handling for persistent storage.

---------------------------
FEATURES


User & Admin System

- Register new user
- Secure login system using std::hash
- Built-in admin accounts
-------------------------
-------------------------
HEALTH TOOLS

Daily Assesment

- Ask water intake
- Ask physical activity
- Generate overall rating
-------------------------
-------------------------

Symptoms Checker

- Ask if have sore throat
- Ask if have headache
- Ask if have cough
- Ask if have chest pain
- Ask if haveback pain
- Generate possible basic diagnosis based on symptoms
--------------------------

--------------------------
BMI Checker

- Ask weight(kg)
- Ask height(cm)
- Calcute BMI
- Display categorize bmi status
---------------------------

------------------------------------
RECORD TRACKING
- Save all assesment,symptoms, and BMI results
- Display result in a clean, table-like format
- Uses: 
  - Linked List (for storing records before sorting)
  - Bubble Sort (for sort records by timestamp)
-------------------------------------

-------------------------------------
TASK QUEUE
- Display task to accomplish in queue
- Task are remoove after completion 
-------------------------------------

-------------------------------------
FILE CREATED
- user.txt 
  -Stores registered users with hashed passwords
- ecords.txt
  - System-level log (logins, actions)
- user_history.txt
  - Individual user heaqlth activity history
-------------------------------------

------------------------------------
DATA STRUCTURES & ALGORITHMS USED
- Linked-List
  - Store user records temporary
- Bubble Sort
  - Sort records by timestamp
- Queue(Array-based)
  - Track pending health task
- Hash Funtion
  - Secure password storage using std::hash
-------------------------------------

-------------------------------------
HOW TO RUN

- Compile
  - g++ main.cpp -o health_app
- Run
    - ./health_app




  

















