#include <iostream>
using namepsace std;
//prototype
void Welcome();
void LogIn();
void Register();
void SaveRecord(const string &action, const string &username = "");
void MainMenu();



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


void Welcome(){
    cout << "=======================================\n";
    cout << "WELCOME TO HEALTH-TRACKER SYSTEM\n";
    cout << "=======================================\n";
}

int main(){
  Welcome();
  MainMenu();
  
  return0;
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

    pendingTasks.clear();

    if (userSystem.isAdmin(username, hashedInput)) {
        cout << "Admin login successful! Welcome back, " << username << ".\n";
        SaveRecord("Admin logged in", username);

        pendingTasks.enqueue("Daily Assessment");
        pendingTasks.enqueue("Symptoms Checker");
        pendingTasks.enqueue("BMI Checker");

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

            pendingTasks.clear();
            pendingTasks.enqueue("Daily Assessment");
            pendingTasks.enqueue("Symptoms Checker");
            pendingTasks.enqueue("BMI Checker");

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

SecMenu(){


    
}


void SymptomsChecker(const string& username){
    char soreThroat, headache, cough, chestPain, backPain;
    string symptoms = "";
    string diagnosis ="";
cout <<"Do you have the following symptoms? (Y/N);

    While (true){
cout<< "soreThroat";
cin<< soreThroat;
soreThroat = toupper(soreThroat);
if (soreThroat == "Y" || soreThroat == "N") break;
cout<< "[ERROR] Not in the given question.\n";
    
}
if (soreThroat == "Y") symptoms += "Sore Throat, "; 

While (true) {
cout<< "Headache: ";
cin >> Headache;
Headache = toupper(Headache);
if (Headache == "Y" || headache == "N") break;
cout << "[ERROR] Not in the given question.\n";
}
if (Headache == "Y" symptoms += "Headache, ";

While (true) {
cout<< "cough: ";
cin >> cough;
cough = toupper(cough);
if (cough == "Y" || cough == "N") break;
cout << "[ERROR] Not in the given question.\n";
}
if (cough == "Y" symptoms += "cough, ";

While (true) {
cout << "chestPain: ";
cin >> chestPain;
chestPain = toupper(chestPain);
if (chestPain == "Y" || chestPain == "N") break;
cout << "[ERROR] Not in the given question.\n";
}
if (chestPain == "Y" symptoms += "chestPain, ";

While (true) {
cout << "backPain: ";
cin >> backPain;
backPain = toupper(backPain);
if (backPain == "Y" || backPain == "N") break;
cout << "[ERROR] Not in the given question.\n";
}
if (backPain == "Y" symptoms += "backPain, ";

if (!symptoms.empty()) { 
symptoms = symptoms.subtr(0, symptoms.length() - 2);

}

if (cough == 'Y' && soreThroat == 'Y') {
        diagnosis = "Possible flu or viral infection";
        cout << diagnosis << ".\n";
    } else if (chestPain == 'Y' && cough == 'Y') {
        diagnosis = "Warning: Possible respiratory issue. Seek medical attention";
        cout << diagnosis << ".\n";
    } else if (backPain == 'Y' && headache == 'Y') {
        diagnosis = "Possible fatigue or stress-related symptoms";
        cout << diagnosis << ".\n";
    } else if (soreThroat == 'N' && headache == 'N' &&
               cough == 'N' && chestPain == 'N' && backPain == 'N') {
        diagnosis = "No symptoms detected";
        cout << "You have no symptoms. You seem fine.\n";
    } else {
        diagnosis = "Symptoms are mild or unclear. Monitor your condition";
        cout << diagnosis << ".\n";
    }

    
    string details = "Symptoms: " + symptoms + ". Diagnosis: " + diagnosis;
    SaveUserRecord(username, "SYMPTOMS_CHECK", details);
}




void BMIChecker(){

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

    float heaightM = heightCm / 100.0;
    bmi = weight / (heightM * heightCm);

    cout << "\nYour BMI is : " << bmi << endl; 

    if (bmi < 18.5){
        category = "Underweight";
        cout << "Category : " << category << \n;
    }else if (bmi < 24.9){
       category = "Normal Weight";
       cout << "Category : " << category << \n;
    }else if (bmi < 29.9){
        category = "Overweight";
        cout << "Category : " << category << \n;
    }else if (bmi < 34.9){
        category = "Obese Class I";
        cout << "Category : " << category << \n;
    }else if (bmi < 39.9){
        category = "Obese Class II";
        cout << "Category : " << category << \n;
    }else {
        category = "Obese Class III (Severe)";
        cout << "Category : " << category << \n;
    }

    cout << "===============================\n";

    string detailes = "weight: " + to_string(weight) + "kg, Height: " + to_string(heightCm) + "cm,BMI: " + to_string(bmi) + " , Category: " = category;
    SaveUserRecord(username , "BMI_CHECK", details);
}
