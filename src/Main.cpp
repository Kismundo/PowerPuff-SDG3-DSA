#include <iostream>

using namepsace std;

void Welcome();
void MainMenu();

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
