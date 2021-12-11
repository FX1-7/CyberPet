#include <iostream>
#include <string>
#include <chrono>
#include <thread>
// Definition, just to make the code look a little neater :)
#define Sleep5Sec std::this_thread::sleep_for(std::chrono::milliseconds(5000))

using namespace std;

// Start menu, this will ask the user if they want to name their pet or not.
void StartMenu(string& i) {
    // Declare variables
    string input;
    string YesUpper = "Yes";
    string YesLower = "yes";
    string NoUpper = "No";
    string NoLower = "no";

    // Get user input.
    std::cout << "Hi there! Congratulations - You now own a new pet, do you want to give it a name?" << endl;
    std::cout << "Yes or No: ";
    std::cin >> input;
    // Checking how they responded
    if (input == YesUpper || input == YesLower || input == NoUpper || input == NoLower) {
        // If no, tell them how the pet will be referred to and set the pat variable to "Your pet".
        if (input == NoLower || input == NoUpper) {
            cout << "No problem! Your pet will be referred to as 'Your pet'";
            i = "Your pet";
        }
        // If Yes, ask them what they would like it to be called.
        else if (input == YesLower || input == YesUpper) {
            cout << "Great! What would you like to name your pet?: ";
            // Set the pet variable to their name.
            cin >> i;
            // Show it has been saved.
            cout << endl << i << " what a great name for a pet!" << endl;
        }
    }
    // If no input or any incorrect input entered then just refer to it as "Your pet" for ease.
    else if (input != YesUpper || input != YesLower || input != NoUpper || input != NoLower) {
        cout << "Your pet will be referred to as 'Your pet'" << endl;
        i = "Your pet";
    }
}

// Converting the int status of the pet to string values that can be used in the Main Menu.
string FoodStatusEnum(int enum_val) {
    static const char* FoodStatuses[] = { "Dead", "Starving", "Needs food", "Slightly Hungry", "Full" };
    string FoodMenuStatus(FoodStatuses[enum_val]);
    // Return the string value for use in Main menu.
    return FoodMenuStatus;
}

// Converting the int status of the pet to string values that can be used in the Main Menu.
string SleepStatusEnum(int enum_val) {
    static const char* SleepStatuses[] = { "Collapsed", "Dozing Off", "Tired", "Awake", "Energetic" };
    string SleepMenuStatus(SleepStatuses[enum_val]);
    // Return the string value for use in Main menu.
    return SleepMenuStatus;
}

// Converting the int status of the pet to string values that can be used in the Main Menu.
string HappinessStatusEnum(int enum_val) {
    static const char* HappinessStatuses[] = { "Depressed", "Really Sad", "Upset", "Happy Enough", "Extremely Happy" };
    string HappinessMenuStatus(HappinessStatuses[enum_val]);
    // Return the string value for use in Main menu.
    return HappinessMenuStatus;
}

// This is the MainMenu where the user can select actions to do with the pet.
char MainMenu(string j, string FoodEnum, string SleepEnum, string HappinessEnum, int DeathCheck) {
    // Variable to hold their choice, this is used in the activities function.
    char TempChoice;
    do {
        // Show each status 
        cout << "\tFood Status: " << FoodEnum << "\t Sleep Status: " << SleepEnum << "\t" << endl;
        cout << "\t\tHappiness: " << HappinessEnum << "\t\t" << endl;
        cout << endl;
        cout << "Press F to feed \tPress S to sleep\t Press P to play" << endl;
        // Get the user input
        cin >> TempChoice;
        // Error checking for input that isn't one of the above options
        if (TempChoice != 'F' && TempChoice != 'S' && TempChoice != 'P' && TempChoice != 'p'
            && TempChoice != 'f' && TempChoice != 's') {
            system("CLS");
            // Tell the user that it is incorrect, pause for 3 seconds and get them to try again.
            cout << "Incorrect input detected, please try again." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            system("CLS");
        }
    // Do while loop so that the error checking returns to the mainmenu if an inaccurate value is entered.
    } while (TempChoice != 'F' && TempChoice != 'S' && TempChoice != 'P' && TempChoice != 'p'
        && TempChoice != 'f' && TempChoice != 's');
    // Return the users choice.
    return TempChoice;
}

// This function will check user input and perform actions accordingly.
void Activities(string Name, int& FStatus, int& SStatus, int& HStatus, char& TempChoice, int& Loops){
    // If the pet is dead then break out of this function
    if (Loops == 1) {
        return;
    }
    // If the user wants to feed the pet then carry out these actions.
    if (TempChoice == 'F' || TempChoice == 'f') {
        // If the foodstatus is 4 then the pet is already full!
        if (FStatus == 4) {
            cout << Name << " is already full!" << endl;
            Loops = 0;
        }
        // If the pet is not full then they can eat.
        else {
            cout << Name << " had a very lovely meal!" << endl;
            cout << endl;
            cout << "(+1 food)" << endl;
            Loops = 0;
            FStatus = FStatus + 1;
        }
    }
    // The user wants the pet to sleep
    else if (TempChoice == 'S' || TempChoice == 's') {
        // If the sleepstat is at 4 then it is already full rested
        if (SStatus == 4) {
            cout << Name << " is already fully rested!" << endl;
            Loops = 0;
        }
        // Otherwise it can sleep.
        else {
            cout << Name << " had a very nice sleep!" << endl;
            cout << endl;
            cout << "(+1 sleep)" << endl;
            Loops = 0;
            SStatus = SStatus + 1;
        }
    }
    // The user wants to play with the pet.
    else if (TempChoice == 'P' || TempChoice == 'p') {
        // If it's already at max happiness then let the user know.
        if (HStatus == 4) {
            cout << Name << " is happy by themselves right now!" << endl;
            cout << "(Already at max happiness!)" << endl;
            Loops = 0;
        }
        // If the pet needs fed or rested then it doesn't have enough energy to play.
        else if (HStatus == 3 && FStatus < 4 || SStatus < 4) {
            cout << Name << " doesn't have enough energy to do this right now!" << endl;
            cout << "Try feeding them or making sure they are rested enough before trying to play with them again!" << endl;
            Loops = 1;
        }
        else {
            cout << Name << " had a wonderful time playing with you!" << endl;
            cout << endl;
            cout << "(+1 happiness)" << endl;
            Loops = 0;
            // Add 1 to happiness
            HStatus = HStatus + 1;
        }
    }
}

void FoodStatusDecrease(int& FoodStat, chrono::system_clock::time_point StartTime) {
    double fTimeDiff = 0.00000;
    double fTimeTally = 0.00000;

    // When the FoodStatus is between 1 and 4 it will check if the time since the program has started
    do {
        // Create a time variable that is marked when the FoodStatus is in the range of 1 and 4.
        auto fEnd = std::chrono::system_clock::now();

        // Find the time difference between the start point of the program and the end point created above.
        std::chrono::duration<double> fDiff = fEnd - StartTime;

        // Assign this value to a double variable.
        fTimeDiff = fDiff.count();
        fTimeDiff = fTimeDiff - fTimeTally;

        // If the difference is the same as the decrease time then decrease FoodStatus by 1.
        if (fTimeDiff != 0.00000 && fTimeDiff >= 40.00000 && fTimeDiff < 40.000001) {
            FoodStat--;
            cout << "bing" << endl;
            cout << FoodStat << endl;
            fTimeTally = fTimeTally + fTimeDiff;
            fDiff = std::chrono::seconds::zero();
            fTimeDiff = 0.00000;
        }
    } while (FoodStat >= 1 && FoodStat <= 4);
}

void SleepStatusDecrease(int& SleepStat, chrono::system_clock::time_point StartTime, int FoodStat, int& Happiness) {
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
        if (sTimeDiff != 0 && sTimeDiff >= 40.00000 && sTimeDiff < 40.00001) {
            SleepStat = SleepStat - 1;
            sTimeTally = sTimeTally + sTimeDiff;
            sDiff = std::chrono::seconds::zero();
            sTimeDiff = 0.00000;
        }
    } while (SleepStat >= 1 && SleepStat <= 4);
}

// This function will decrease the Happiness stat accordingly.
// Happiness starts at 3 and can be increased to 4 if played with.
// But the Happiness stat will only decrease if the Sleep or Food stat drops below 3.
void HappinessStatusDecrease(int& Happiness, int& SleepStat, int& FoodStat) {
    // A do while loop is necessary here so that we are constantly checking.
    do {
        // If Sleep or Food are 2 then adjust Happiness accordingly
        if (SleepStat == 2 || FoodStat == 2) {
            Happiness = 2;
        }
        // If Sleep or Food are 1 then adjust Happiness accordingly
        if (SleepStat == 1 || FoodStat == 1) {
            Happiness = 1;
        }
        // If Sleep or Food are 0 then adjust Happiness accordingly
        if (SleepStat == 0 || FoodStat == 0) {
            Happiness = 0;
        }
    } while (Happiness >= 0);
}

// This function will check to see if any stats have reached 0, if they have then it will make the pet dead via changing the Death variable.
void DeathCheck(int& FoodStat, int& SleepStat, int& HappinessStat, int& Exit) {
    int looper = 0;
    // A do while loop here so it is constantly checked.
    do {
        // If loop to check the stats
        if (FoodStat == 0 || SleepStat == 0 || HappinessStat == 0) {
            // if the pet is dead, change the Death variable.
            Exit = 1;
        }
    } while (looper = 0);
}

int main()
{

    // Starts tracking time since program was run.
    auto start = std::chrono::system_clock::now();

    // Declare the PetName variable to keep track of the pets name, this will be used by other functions
    int FoodStatus = 4;
    int SleepStatus = 4;
    int Death = 0;
    string PetName = "Your pet";

    // Happiness is set to 3 as a max default - this is so that the user has incentive to play with the pet,
    // (to get max happiness)
    int Happiness = 3;
    char Choice;

    do {
        // Call the start menu to get the pets name.
        StartMenu(PetName);
        
        // Time Keeping daemon threads which will run continuously as the program is being run.
        std::thread FoodTime(FoodStatusDecrease, std::ref(FoodStatus), start);
        std::thread SleepTime(SleepStatusDecrease, std::ref(SleepStatus), start, FoodStatus, std::ref(Happiness));
        std::thread HappinessTime(HappinessStatusDecrease, std::ref(Happiness), std::ref(SleepStatus), std::ref(FoodStatus));
        std::thread DeathTime(DeathCheck, std::ref(FoodStatus), std::ref(SleepStatus), std::ref(Happiness), std::ref(Death));
        DeathTime.detach();
        HappinessTime.detach();
        FoodTime.detach();
        SleepTime.detach();

        // Pause for 5 seconds and clear the console.
        Sleep5Sec;
        system("CLS");

        // Call the initial Main Menu screen.
        string MainMenuFoodStatus = FoodStatusEnum(FoodStatus);
        string MainMenuSleepStatus = SleepStatusEnum(SleepStatus);
        string MainMenuHappinessStatus = HappinessStatusEnum(Happiness);
        Choice = MainMenu(PetName, MainMenuFoodStatus, MainMenuSleepStatus, MainMenuHappinessStatus, Death);
        system("CLS");

        // Call the activities Function to run the Activity selected by the user.
        // We don't need error checking within this function for the choice selection as this was done in the Main Menu function.
        Activities(PetName, FoodStatus, SleepStatus, Happiness, Choice, Death);
        // Enum the int status values to string values for the Main Menu output
        MainMenuFoodStatus = FoodStatusEnum(FoodStatus);
        MainMenuSleepStatus = SleepStatusEnum(SleepStatus);
        MainMenuHappinessStatus = HappinessStatusEnum(Happiness);
        // Pause for 5 seconds
        Sleep5Sec;
        system("CLS");

        do {
            // Call Main Menu, this is looped so that after every action the main menu screen will show.
            Choice = MainMenu(PetName, MainMenuFoodStatus, MainMenuSleepStatus, MainMenuHappinessStatus, Death);
            system("CLS");
            Activities(PetName, FoodStatus, SleepStatus, Happiness, Choice, Death);
            // Enum the int status values to string values for the Main Menu output
            MainMenuFoodStatus = FoodStatusEnum(FoodStatus);
            MainMenuSleepStatus = SleepStatusEnum(SleepStatus);
            MainMenuHappinessStatus = HappinessStatusEnum(Happiness);
            // Pause for 5 seconds
            Sleep5Sec;
            system("CLS");
        } while (Death == 0);
    } while (Death != 1);
    system("CLS");
    // Tell the user the pet died
    cout << "\t\t " << PetName << " died! Better luck next time. \t\t";
    cout << endl;
    cout << endl;
    cout << endl;
    return 0;
}