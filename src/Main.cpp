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

}


void SymptomsChecker(){
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
