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
    void FoodStatusDecrease(int&, chrono::system_clock::time_point);
    void SleepStatusDecrease(int&, chrono::system_clock::time_point);


    // Call the start menu to get the pets name.
    StartMenu(PetName);

    // Call timekeeping function so  time is kept as soon as the player names the pet.
    std::thread FoodTime(FoodStatusDecrease, std::ref(FoodStatus), start);
    std::thread SleepTime(SleepStatusDecrease, std::ref(FoodStatus), start);

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
    string input;
    string YesUpper = "Yes";
    string YesLower = "yes";
    string NoUpper = "No";
    string NoLower = "no";

    std::cout << "Hi there! Congratulations - You now own a new pet, do you want to give it a name?" << endl;
    std::cout << "Yes or No: ";
    std::cin >> input;
    if (input == YesUpper || input == YesLower || input == NoUpper || input == NoLower) {
        if (input == NoLower | input == NoUpper) {
            std::cout << "No problem! Your pet will be referred to as 'Your pet'";
            i = "Your pet";
        }
        else if (input == YesLower || input == YesUpper) {
            std::cout << "Great! What would you like to name your pet?: ";
            std::cin >> i;
            std::cout << endl << i << " what a great name for a pet!" << endl;
        }
    }
}

//string FoodStatusEnum(int enumVal) {
    //enum FoodStatus{Dead, Starving, NeedsFood, SlightlyHungry, Full};
    //static const char* FoodStatuses[] = { "Dead", "Starving", "Needs food", "Slightly Hungry", "Full" };
    //string FoodMenuStatus(FoodStatuses[FoodStatus]);
    //enum SleepStatus{Collapsed, DozingOff, Tired, Awake, Energetic};
    //static const char* SleepStatus[] = { "Collapsed", "Dozing off", "Tired", "Awake", "Energetic" };
    //enum Happiness{Depressed, ReallySad, Upset, Happy, VeryHappy};
    //static const char* Happiness[] = { "Depressed", "Really Sad", "Upset", "Happy", "Very Happy" };
    //string TheValue(Status[enumVal]);
    //return FoodMenuStatus;
//}

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

void FoodStatusDecrease(int& FoodStat, chrono::system_clock::time_point StartTime) {
    double fTimeDiff = 0.00000;
    double fTimeTally = 0.00000;

    // When the FoodStatus is between 2 and 5 it will check if the time since the program has started
    do {
        // Create a time variable that is marked when the FoodStatus is in the range of 2 and 5.
        auto fEnd = std::chrono::system_clock::now();

        // Find the time difference between the start point of the program and the end point created above.
        std::chrono::duration<double> fDiff = fEnd - StartTime;

        // Assign this value to a double variable.
        fTimeDiff = fDiff.count();
        fTimeDiff = fTimeDiff - fTimeTally;

        // If the difference is the same as the decrease time then decrease FoodStatus by 1.
        if (fTimeDiff != 0.00000 && fTimeDiff >= 30.00000 && fTimeDiff < 30.00001) {
            FoodStat = FoodStat - 1;
            fTimeTally = fTimeTally + fTimeDiff;
            fDiff = std::chrono::seconds::zero();
            fTimeDiff = 0.00000;
        }
    } while (FoodStat >= 2 && FoodStat <= 5);
}

void SleepStatusDecrease(int& SleepStat, chrono::system_clock::time_point StartTime) {
    double sTimeDiff = 0.00000;
    double sTimeTally = 0.00000;

    // When the SleepStatus is between 2 and 5 it will check if the time since the program has started 
    do {
        // Create a time variable that is marked when the FoodStatus is in the range of 2 and 5.
        auto sEnd = std::chrono::system_clock::now();

        // Find the time difference between the start point of the program and the end point created above.
        std::chrono::duration<double> sDiff = sEnd - StartTime;

        // Assign this value to a double variable.
        sTimeDiff = sDiff.count();
        sTimeDiff = sTimeDiff - sTimeTally;

        // If the difference is the same as the decrease time then decrease SleepStatus by 1.
        if (sTimeDiff != 0 && sTimeDiff >= 30.00000 && sTimeDiff < 30.00001) {
            SleepStat = SleepStat - 1;
            sTimeTally = sTimeTally + sTimeDiff;
            sDiff = std::chrono::seconds::zero();
            sTimeDiff = 0.00000;
        }
    } while (SleepStat >= 2 && SleepStat <= 5);
}