#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#define Sleep5Sec std::this_thread::sleep_for(std::chrono::milliseconds(5000))

using namespace std;

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
        if (input == NoLower || input == NoUpper) {
            std::cout << "No problem! Your pet will be referred to as 'Your pet'";
            i = "Your pet";
        }
        else if (input == YesLower || input == YesUpper) {
            std::cout << "Great! What would you like to name your pet?: ";
            std::cin >> i;
            std::cout << endl << i << " what a great name for a pet!" << endl;
        }
    }
    else if (input != YesUpper || input != YesLower || input != NoUpper || input != NoLower) {
        cout << "Your pet will be referred to as 'Your pet'" << endl;
        i = "Your pet";
    }
}

string FoodStatusEnum(int enum_val) {
    static const char* FoodStatuses[] = { "Dead", "Starving", "Needs food", "Slightly Hungry", "Full" };
    string FoodMenuStatus(FoodStatuses[enum_val]);
    return FoodMenuStatus;
}

string SleepStatusEnum(int enum_val) {
    static const char* SleepStatuses[] = { "Collapsed", "Dozing Off", "Tired", "Awake", "Energetic" };
    string SleepMenuStatus(SleepStatuses[enum_val]);
    return SleepMenuStatus;
}

string HappinessStatusEnum(int enum_val) {
    static const char* HappinessStatuses[] = { "Depressed", "Really Sad", "Upset", "Happy Enough", "Extremely Happy" };
    string HappinessMenuStatus(HappinessStatuses[enum_val]);
    return HappinessMenuStatus;
}

char MainMenu(string j, string FoodEnum, string SleepEnum, string HappinessEnum, int DeathCheck) {
    char TempChoice;
    do {
        cout << "\tFood Status: " << FoodEnum << " Sleep Status: " << SleepEnum << "\t" << endl;
        cout << "\t\tHappiness: " << HappinessEnum << "\t\t" << endl;
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

void Activities(string Name, int& FStatus, int& SStatus, int& HStatus, char& TempChoice, int& Loops){
    if (Loops = 0) {
        return;
    }
    if (TempChoice == 'F' || TempChoice == 'f') {
        if (FStatus == 4) {
            cout << Name << " is already full!" << endl;
            Loops = 0;
        }
        else {
            cout << Name << " had a very lovely meal!" << endl;
            cout << endl;
            cout << "(+1 food)" << endl;
            Loops = 0;
            FStatus = FStatus + 1;
        }
    }
    else if (TempChoice == 'S' || TempChoice == 's') {
        if (SStatus == 4) {
            cout << Name << " is already fully rested!" << endl;
            Loops = 0;
        }
        else {
            cout << Name << " had a very nice sleep!" << endl;
            cout << endl;
            cout << "(+1 sleep)" << endl;
            Loops = 0;
            SStatus = SStatus + 1;
        }
    }
    else if (TempChoice == 'P' || TempChoice == 'p') {
        if (HStatus == 4) {
            cout << Name << " is already extremely happy!" << endl;
            Loops = 0;
        }
        else if (HStatus == 3 && FStatus < 4 || SStatus < 4) {
            cout << Name << " doesn't have enough energy to do this right now!"
                "Try feeding them or making sure they are rested enough before trying to play with them again!" << endl;
            Loops = 1;
        }
        else if (HStatus < 3) {
            cout << Name << " isn't happy enough to do this right now!" << endl;
            cout << "Try feeding them or making sure they are rested enough before trying to play with them again!" << endl;
            Loops = 0;
        }
        else {
            cout << Name << " had a wonderful time playing with you!" << endl;
            cout << endl;
            cout << "(+1 happiness)" << endl;
            Loops = 0;
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

void HappinessStatusDecrease(int& Happiness, int& SleepStat, int& FoodStat) {
    do {
        if (SleepStat == 2 && FoodStat == 2) {
            Happiness = 2;
        }

        if (SleepStat == 1 && FoodStat == 1) {
            Happiness = 1;
        }
        
        if (SleepStat == 0 && FoodStat == 0) {
            Happiness = 0;
        }
    } while (Happiness >= 0);
}

void DeathCheck(int& FoodStat, int& SleepStat, int& HappinessStat, int& Exit) {
    int looper = 0;
    do {
        if (FoodStat == 0 || SleepStat == 0 || HappinessStat == 0) {
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

        // Call timekeeping function so  time is kept as soon as the player names the pet.
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
        MainMenuFoodStatus = FoodStatusEnum(FoodStatus);
        MainMenuSleepStatus = SleepStatusEnum(SleepStatus);
        MainMenuHappinessStatus = HappinessStatusEnum(Happiness);
        Sleep5Sec;
        system("CLS");

        do {
            // Call Main Menu, this is looped so that after every action the main menu screen will show.
            Choice = MainMenu(PetName, MainMenuFoodStatus, MainMenuSleepStatus, MainMenuHappinessStatus, Death);
            system("CLS");
            Activities(PetName, FoodStatus, SleepStatus, Happiness, Choice, Death);
            MainMenuFoodStatus = FoodStatusEnum(FoodStatus);
            MainMenuSleepStatus = SleepStatusEnum(SleepStatus);
            MainMenuHappinessStatus = HappinessStatusEnum(Happiness);
            Sleep5Sec;
            system("CLS");
        } while (Death == 0);
    } while (Death != 1);
    system("CLS");
    cout << "\t\t " << PetName << " died! Better luck next time. \t\t";
    cout << endl;
    cout << endl;
    cout << endl;
    return 0;
}