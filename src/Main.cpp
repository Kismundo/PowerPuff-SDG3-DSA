#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <limits>
#include <functional>

using namespace std;

void Welcome();
void LogIn();
void Register();
void SaveRecord(const string &action, const string &username = "");
void SaveUserRecord(const string &username, const string &category, const string &details);
void MainMenu();
void SecMenu(const string& username);
void DailyAssessment(const string& username);
void SymptomsChecker(const string& username);
void BMIChecker(const string& username);
void ViewRecords(const string& username);
string HashPassword(const string &password);
string GetTime();


struct RecordNode {
    string timestamp, category, details;
    RecordNode* next;

    RecordNode(const string& t, const string& c, const string& d) {
        timestamp = t;
        category = c;
        details = d;
        next = nullptr;
    }
};
class TaskQueue { //array-based queue to ha
private:
    string tasks[10];
    int front, rear;

public:
    TaskQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return rear == 9;
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(const string& task) {
        if (isFull()) return;
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear++;
        }
        tasks[rear] = task;
    }

    void dequeue() {
        if (isEmpty()) return;
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "No pending tasks.\n";
            return;
        }
        cout << "Pending Tasks:\n";
        for (int i = front; i <= rear; i++) {
            cout << "- " << tasks[i] << endl;
        }
    }

    void clear() {
        front = rear = -1;
    }
};

TaskQueue PendingTasks;

void bubbleSort(vector<string>& records) {
    int n = (int)records.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (records[j] > records[j + 1]) {
                swap(records[j], records[j + 1]);
            }
        }
    }
}

class User {
private:
    vector<pair<string, string>> adminAccounts;

public:
    User() {
        adminAccounts.push_back({"khiemi", HashPassword("Codeh@n37")});
        adminAccounts.push_back({"Lad", HashPassword("pass123")});
        adminAccounts.push_back({"Jerome", HashPassword("Rico3")});
        adminAccounts.push_back({"Jereyme", HashPassword("Hylo$")});
        adminAccounts.push_back({"Chloe", HashPassword("Dmakaus@d")});
    }

    bool isAdmin(const string &username, const string &passwordHash) {
        for (auto &admin : adminAccounts) {
            if (admin.first == username && admin.second == passwordHash) {
                return true;
            }
        }
        return false;
    }
};

User userSystem;

int main(){
    srand((unsigned)time(nullptr));
    Welcome();
    MainMenu();
    return 0;
}

void Welcome(){
    cout << "=======================================\n";
    cout << "WELCOME TO HEALTH-TRACKER SYSTEM\n";
    cout << "=======================================\n";
}

string HashPassword(const string &password) {
    hash<string> hasher;
    size_t hashed = hasher(password);
    return to_string(hashed);
}

string GetTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    char buffer[40];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d",
             1900 + ltm->tm_year,
             1 + ltm->tm_mon,
             ltm->tm_mday,
             ltm->tm_hour,
             ltm->tm_min);
    return string(buffer);

}

void SaveUserRecord(const string &username, const string &category, const string &details) {
    ofstream file("user_history.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error opening user history file.\n";
        return;
    }
    file << username << "|" << GetTime() << "|" << category << "|" << details << endl;
    file.close();

}

void MainMenu(){
    int choice;
    do {
        cout << "-----------------------------------------------\n";
        cout << "[1.] Log-In" << endl;
        cout << "[2.] Register" << endl;
        cout << "[3.] Exit" << endl;
        cout << "-----------------------------------------------\n";
        cout << "Enter Your Choice Here: ";
        cin >> choice;


        switch (choice) {
            case 1:
                LogIn();
                break;
            case 2:
                Register();
                break;
            case 3:
                cout << "Ending Program.\n";
                exit(0);
            default:
                cout << "[ERROR] Invalid Input! 1-3 Only!\n";
        }
    } while (true);
}

void LogIn() {
    string username, password;
    cout << "\nEnter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string hashedInput = HashPassword(password);

    PendingTasks.clear();

    if (userSystem.isAdmin(username, hashedInput)) {
        cout << "Admin login successful! Welcome back, " << username << ".\n";
        SaveRecord("Admin logged in", username);

        PendingTasks.enqueue("Daily Assessment");
        PendingTasks.enqueue("Symptoms Checker");
        PendingTasks.enqueue("BMI Checker");

        SecMenu(username);
        return;
    }

    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "Error opening users file.\n";
        return;
    }

    string storedName, storedUser, storedPass;
    bool success = false;

    while (file >> storedName >> storedUser >> storedPass) {
        if (storedUser == username && storedPass == hashedInput) {
            success = true;
            cout << "User login successful! Welcome back, " << storedName << ".\n";
            SaveRecord("User logged in", storedUser);
            SaveUserRecord(storedUser, "SYSTEM", "User logged into system");
            file.close();

            PendingTasks.clear();
            PendingTasks.enqueue("Daily Assessment");
            PendingTasks.enqueue("Symptoms Checker");
            PendingTasks.enqueue("BMI Checker");

            SecMenu(storedUser);
            return;
        }
    }

    file.close();

    if (!success) {
        cout << "Login failed. Incorrect username or password.\n";
        SaveRecord("Failed login attempt", username);
    }
}

void Register() {
    string name, username, password;

    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter new username: ";
    cin >> username;

    ifstream checkFile("users.txt");
    if (checkFile.is_open()) {
        string storedName, storedUser, storedPass;
        while (checkFile >> storedName >> storedUser >> storedPass) {
            if (storedUser == username) {
                cout << "\n[ERROR] Username already exists. Registration failed.\n";
                checkFile.close();
                return;
            }
        }
        checkFile.close();
    }

    cout << "Enter new password: ";
    cin >> password;

    string hashedPassword = HashPassword(password);

    ofstream file("users.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error opening users.txt for saving.\n";
        return;
    }

    file << name << " " << username << " " << hashedPassword << endl;
    file.close();

    cout << "Registration successful! You can now log in.\n";
    SaveRecord("Registered new account", username);
}

void SaveRecord(const string &action, const string &username) {
    ofstream log("records.txt", ios::app);
    if (!log.is_open()) {
        cout << "Error opening records file.\n";
        return;
    }

    log << "[" << GetTime() << "] " << action
        << " - User: " << username << endl;

    log.close();
}

void SecMenu(const string& username) {
    int choice;
    do {
        cout << "----------------------------------------------------\n";
        cout << "[1.] Daily Health Assessment" << endl;
        cout << "[2.] Symptoms Checker" << endl;
        cout << "[3.] BMI Checker" << endl;
        cout << "[4.] View My Health History" << endl;
        cout << "[5.] Log-Out" << endl;
        cout << "----------------------------------------------------\n";

        cout << "\nYour Current Task Queue:\n";
        PendingTasks.display();
        cout << endl;

        cout << "Enter Your Chosen Number Here: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERROR] Invalid Input! Please enter a number 1-5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                DailyAssessment(username);
                break;
            case 2:
                SymptomsChecker(username);
                break;
            case 3:
                BMIChecker(username);
                break;
            case 4:
                ViewRecords(username);
                break;
            case 5:
                cout << "Logging out...\n";
                SaveUserRecord(username, "SYSTEM", "User logged out");
                SaveRecord("User logged out", username);
                PendingTasks.clear();
                return;
            default:
                cout << "[Error] Invalid Input! Choose 1-5 only.\n";
        }
    } while (true);
}

void DailyAssessment(const string& username) {
int water, hrsofsleep, minofact;
string assessment;
string overallWellness;

cout << "==============================================================\n";

cout <<"Indicate the number of cups of water you drank today: ";
cin >> water;

cout <<"Specify your sleep hours last night: ";
cin >> hrsofsleep;

cout <<"Minutes of Physical today: ";
cin >> minofact;

cout << "==============================================================\n";
cout << "\nDaily Assessment Summary:\n";


if(water>=8) {
assessment += "Excellent,";
} else if (water >= 5) {
assessment += "Good,";
} else { 
assessment += "Poor,"; }


int excellentCount = 0, goodCount = 0, poorCount = 0;
if (assessment.find("Excellent") != string::npos) excellentCount++;
if (assessment.find("Good") != string::npos) goodCount++;
if (assessment.find("Poor") != string::npos) poorCount++;


if (excellentCount >= 2) {
overallWellness = "Excellent Wellness";
}
else if (excellentCount >= 2 ||(excellentCount >= 1 && goodCount >= 1)) {
overallWellness = "Good Wellness";
} else {
overallWellness = "Poor Wellness";
}

cout <<"\nOVERALL WELLNESS: " << overallWellness << endl;
cout << "==============================================================\n";


SaveUserRecord(username, "DAILY_ASSESSMENT", overallWellness);
SaveRecord("User performed daily assessment", username);

if (!PendingTasks.isEmpty()) PendingTasks.dequeue(); 
}

void SymptomsChecker(const string& username) {
    char soreThroat, headache, cough, chestPain, backPain;
    string symptoms = "";
    string diagnosis = "";

    cout << "Do you have the following symptoms? (Y/N)\n";

    cout << "Sore Throat: ";
    cin >> soreThroat;
    if (soreThroat == 'Y' || soreThroat == 'y') symptoms += "Sore Throat, ";

    cout << "Headache: ";
    cin >> headache;
    if (headache == 'Y' || headache == 'y') symptoms += "Headache, ";

    cout << "Cough: ";
    cin >> cough;
    if (cough == 'Y' || cough == 'y') symptoms += "Cough, ";

    cout << "Chest Pain: ";
    cin >> chestPain;
    if (chestPain == 'Y' || chestPain == 'y') symptoms += "Chest Pain, ";

    cout << "Back Pain: ";
    cin >> backPain;
    if (backPain == 'Y' || backPain == 'y') symptoms += "Back Pain, ";

  
    if (!symptoms.empty()) {
        symptoms = symptoms.substr(0, symptoms.length() - 2);
    }

    if ((cough == 'Y' || cough == 'y') && (soreThroat == 'Y' || soreThroat == 'y')) {
        diagnosis = "Possible flu or viral infection";
        cout << diagnosis << ".\n";
    } else if ((chestPain == 'Y' || chestPain == 'y') && (cough == 'Y' || cough == 'y')) {
        diagnosis = "Warning: Possible respiratory issue. Seek medical attention";
        cout << diagnosis << ".\n";
    } else if ((backPain == 'Y' || backPain == 'y') && (headache == 'Y' || headache == 'y')) {
        diagnosis = "Possible fatigue or stress-related symptoms";
        cout << diagnosis << ".\n";
    } else if ((soreThroat == 'N' || soreThroat == 'n') &&
               (headache == 'N' || headache == 'n') &&
               (cough == 'N' || cough == 'n') &&
               (chestPain == 'N' || chestPain == 'n') &&
               (backPain == 'N' || backPain == 'n')) {
        diagnosis = "No symptoms detected";
        cout << "You have no symptoms. You seem fine.\n";
    } else {
        diagnosis = "Symptoms are mild or unclear. Monitor your condition";
        cout << diagnosis << ".\n";
    }
    

    string details = "Symptoms: " + symptoms + ". Diagnosis: " + diagnosis;
    SaveUserRecord(username, "SYMPTOMS_CHECK", details);
    SaveRecord("User performed symptoms check", username);

   
    if (!PendingTasks.isEmpty()) PendingTasks.dequeue();
}

void BMIChecker(const string& username){

float weight, heightCm, bmi;
string category;

    cout << "\n===============================\n";
    cout << "\t BMI CHECKER\n";
    cout << "===============================\n";

    while (true){
        cout << "Enter your weight (KG): ";
        cin >> weight;

        if (cin.fail() || weight <= 0){
        cin.clear();
        cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid number." ;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    while (true){
        cout << "Enter your height (CM): " ;
        cin >> heightCm;

        if (cin.fail() || heightCm <= 0){
        cin.clear();
        cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid number." ;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }          

    float heightM = heightCm / 100.0;
    bmi = weight / (heightM * heightCm);

    cout << "\nYour BMI is : " << bmi << endl; 

    if (bmi < 18.5){
        category = "Underweight";
        cout << "Category : " << category << "\n";
    }else if (bmi < 24.9){
       category = "Normal Weight";
       cout << "Category : " << category << "\n";
    }else if (bmi < 29.9){
        category = "Overweight";
        cout << "Category : " << category << "\n";
    }else if (bmi < 34.9){
        category = "Obese Class I";
        cout << "Category : " << category << "\n";
    }else if (bmi < 39.9){
        category = "Obese Class II";
        cout << "Category : " << category << "\n";
    }else {
        category = "Obese Class III (Severe)";
        cout << "Category : " << category << "\n";
    }

    cout << "===============================\n";

    string details = "weight: " + to_string(weight) + "kg, Height: " + to_string(heightCm) + "cm,BMI: " + to_string(bmi) + " , Category: " = category;
    SaveUserRecord(username , "BMI_CHECK", details);
    SaveRecord("User performed BMI check", username);

    if (!PendingTasks.isEmpty()) PendingTasks.dequeue();
}

void ViewRecords(const string& username) {
    ifstream file("user_history.txt");
    if (!file.is_open()) {
        cout << "\n===============================================\n";
        cout << "     No health history found for " << username << "\n";
        cout << "  Start tracking your health to build history!\n";
        cout << "===============================================\n";
        return;
    }

    string line;
    RecordNode* head = nullptr;
    RecordNode* tail = nullptr;
    int recordCount = 0;

    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        if (pos1 != string::npos) {
            string recordUsername = line.substr(0, pos1);
            if (recordUsername == username) {
                size_t pos2 = line.find('|', pos1 + 1);
                size_t pos3 = line.find('|', pos2 + 1);

                if (pos2 == string::npos || pos3 == string::npos) continue;

                string timestamp = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string category = line.substr(pos2 + 1, pos3 - pos2 - 1);
                string details = line.substr(pos3 + 1);

                RecordNode* newNode = new RecordNode(timestamp, category, details);
                if (!head) head = tail = newNode;
                else {
                    tail->next = newNode;
                    tail = newNode;
                }
                recordCount++;
            }
        }
    }
    file.close();

    cout << "\n==============================================================\n";
    cout << "              HEALTH HISTORY FOR: " << username << "\n";
    cout << "==============================================================\n";
    
    if (recordCount == 0) {
    cout << "        No records found...\n";
    while (head) {
        RecordNode* temp = head;
        head = head->next;
        delete temp;
    }
    return;
}

    vector<string> sortedRecords;
    RecordNode* current = head;
    while (current) {
        sortedRecords.push_back(current->timestamp + "|" + current->category + "|" + current->details);
        current = current->next;
    }

    current = head;
    while (current) {
        RecordNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;

    bubbleSort(sortedRecords); 

    cout << "+------------------------+------------------+--------------------+\n";
    cout << "|      DATE/TIME         |    CATEGORY      |     DETAILS        |\n";
    cout << "+------------------------+------------------+--------------------+\n";
    
    for (int i = (int)sortedRecords.size() - 1; i >= 0; i--) {
        string entry = sortedRecords[i];
        size_t pos1 = entry.find('|');
        size_t pos2 = entry.find('|', pos1 + 1);

        string timestamp = (pos1 != string::npos) ? entry.substr(0, pos1) : "";
        string category = (pos1 != string::npos && pos2 != string::npos) ? entry.substr(pos1 + 1, pos2 - pos1 - 1) : "";
        string details = (pos2 != string::npos) ? entry.substr(pos2 + 1) : "";

        cout << "| ";
        cout.width(22); cout << left << timestamp;
        cout << " | ";
        cout.width(16); cout << left << category;
        cout << " | ";
        if (details.length() > 18) details = details.substr(0, 15) + "...";
        cout.width(18); cout << left << details;
        cout << " |\n";
        if (i > 0) {
            cout << "+------------------------+------------------+--------------------+\n";
        }
    }
    cout << "+------------------------+------------------+--------------------+\n\n";

    cout << "==================== HEALTH STATISTICS ====================\n";
    
    int dailyCount = 0, symptomCount = 0, bmiCount = 0, systemCount = 0;
    for (const string& rec : sortedRecords) {
        size_t p1 = rec.find('|');
        size_t p2 = rec.find('|', p1 + 1);
        if (p1 != string::npos && p2 != string::npos) {
            string cat = rec.substr(p1 + 1, p2 - p1 - 1);
            if (cat == "DAILY_ASSESSMENT") dailyCount++;
            else if (cat == "SYMPTOMS_CHECK") symptomCount++;
            else if (cat == "BMI_CHECK") bmiCount++;
            else if (cat == "SYSTEM") systemCount++;
        }
    }
    
    cout << "  Daily Assessments: " << dailyCount << " records\n";
    cout << "  Symptoms Checks:   " << symptomCount << " records\n";
    cout << "  BMI Checks:        " << bmiCount << " records\n";
    cout << "  System Activities: " << systemCount << " records\n";
    cout << "  ---------------------------------------\n";
    cout << "  TOTAL RECORDS:     " << recordCount << " records\n";
    cout << "==============================================================\n";
}
