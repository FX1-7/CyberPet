#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#define Sleep5Sec std::this_thread::sleep_for(std::chrono::milliseconds(5000))

using namespace std;

int main()
{
    // Starts tracking time since program was run.
    auto start = std::chrono::system_clock::now();

    // Declare the PetName variable to keep track of the pets name, this will be used by other functions
    string PetName = "PetName";
    int FoodStatus = 5;
    int SleepStatus = 5;
    // Happiness is set to 4 as a max default - this is so that the user has incentive to play with the pet,
    // (to get max happiness)
    int Happiness = 4;
    char Choice;
    int Looper = 0;


    // Declare function types
    void StartMenu(string&);
    char MainMenu(string);
    void Activities(string, int&, int&, int&, char&, int&);


    // Call the start menu to get the pets name.
    StartMenu(PetName);


    // Pause for 5 seconds and clear the console.
    Sleep5Sec;
    system("CLS");

    // Call the initial Main Menu screen.
    Choice = MainMenu(PetName);
    system("CLS");

    // Call the activities Function to run the Activity selected by the user.
    // We don't need error checking within this function for the choice selection as this was done in the Main Menu function.
    Activities(PetName, FoodStatus, SleepStatus, Happiness, Choice, Looper);
    Sleep5Sec;
    system("CLS");

    do {
        // Call Main Menu, this is looped so that after every action the main menu screen will show.
        Choice = MainMenu(PetName);
        system("CLS");
        Activities(PetName, FoodStatus, SleepStatus, Happiness, Choice, Looper);
        Sleep5Sec;
        system("CLS");
    } while (Looper == 1);
}

void StartMenu(string& i) {
    cout << "Hi there! Congratulations - You now own a new pet, what will you name it?: ";
    cin >> i;
    if (i != "Your pet") {
        cout << i << " wow, that's a great name!";
    }
    else {
        cout << "No Name selected";
    }
}

char MainMenu(string j) {
    char TempChoice;
    do {
        cout << "\tFood Status: FoodStatus Sleep Status: SleepStatus\t" << endl;
        cout << "\t\tHappiness: Happiness\t\t" << endl;
        cout << "Press F to feed \tPress S to sleep\t Press P to play" << endl;
        cin >> TempChoice;
        if (TempChoice != 'F' && TempChoice != 'S' && TempChoice != 'P' && TempChoice != 'p'
            && TempChoice != 'f' && TempChoice != 's') {
            system("CLS");
            cout << "Incorrect input detected, please try again." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            system("CLS");
        }
    } while (TempChoice != 'F' && TempChoice != 'S' && TempChoice != 'P' && TempChoice != 'p'
        && TempChoice != 'f' && TempChoice != 's');
    return TempChoice;
}

void Activities(string Name, int& FStatus, int& SStatus, int& HStatus, char& TempChoice, int& Loops) {
    if (TempChoice == 'F' || TempChoice == 'f') {
        if (FStatus == 5) {
            cout << Name << " is already full!" << endl;
            Loops = 1;
        }
        else {
            cout << Name << " had a very lovely meal!" << endl;
            cout << endl;
            cout << "(+1 food)" << endl;
            Loops = 1;
            FStatus = FStatus + 1;
        }
    }
    else if (TempChoice == 'S' || TempChoice == 's') {
        if (SStatus == 5) {
            cout << Name << " is already fully rested!" << endl;
            Loops = 1;
        }
        else {
            cout << Name << " had a very nice sleep!" << endl;
            cout << endl;
            cout << "(+1 sleep)" << endl;
            Loops = 1;
            SStatus = SStatus + 1;
        }
    }
    else if (TempChoice == 'P' || TempChoice == 'p') {
        if (HStatus == 5) {
            cout << Name << " is already extremely happy!" << endl;
            Loops = 1;
        }
        else if (HStatus == 4 && FStatus < 5 || SStatus < 5) {
            cout << Name << " doesn't have enough energy to do this right now!"
                "Try feeding them or making sure they are rested enough before trying to play with them again!" << endl;
            Loops = 1;
        }
        else if (HStatus < 4) {
            cout << Name << " isn't happy enough to do this right now!"
                "Try feeding them or making sure they are rested enough before trying to play with them again!" << endl;
            Loops = 1;
        }
        else {
            cout << Name << " had a wonderful time playing with you!" << endl;
            cout << endl;
            cout << "(+1 happiness)" << endl;
            Loops = 1;
            HStatus = HStatus + 1;
        }
    }
}

void TimeKeeping() {

}