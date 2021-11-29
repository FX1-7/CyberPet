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
    void TimeKeeping(int&, int&, int&, chrono::system_clock::time_point);


    // Call the start menu to get the pets name.
    StartMenu(PetName);


    // Call timekeeping function so  time is kept as soon as the player names the pet.
    std::thread Time(TimeKeeping, std::ref(FoodStatus), std::ref(SleepStatus), std::ref(Happiness), start);

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

void TimeKeeping(int& FoodStat, int& SleepStat, int& HappinessStat, chrono::system_clock::time_point StartTime) {
    int loop = 1;
    double Diff;

    //              Signing off comments for 29th
    // Not sure how to loop time calc to be useful for the do while loops
    // Also don't think the nested do while loop is right as it may take away more than 1, as it will repeat under every instance that the status is between 2 and 5. 
    // If loop will likely be better here.
    // See if it's possible to get the time as an int instead of double, or a way to extract straight as seconds(?)


    do {
        auto firstEnd = std::chrono::system_clock::now();
        std::chrono::duration <double> firstDiff = firstEnd - StartTime;
        std::ref(Diff) == firstDiff.count();
    } while (loop == 1);

    // Decrease times are in ms
    // The FoodDecrease time is 15mins
    double FoodDecrease = 30.00;
    // The SleepDecrease time is 30mins
    double SleepDecrease = 60.00;
    do {
        cout << "pop1";
        // When the FoodStatus is between 2 and 5 it will check if the time since the program has started 
        do {
            cout << "pop2";
            // Create a time variable that is marked when the FoodStatus is in the range of 2 and 5.
            auto fEnd = std::chrono::system_clock::now();

            // Find the time difference between the start point of the program and the end point created above.
            std::chrono::duration<double> fDiff = fEnd - StartTime;

            // Assign this value to a double variable.
            double fTimeDiff = fDiff.count();

            // If the difference is the same as the decrease time then decrease FoodStatus by 1.
            if (fTimeDiff == FoodDecrease) {
                FoodStat = FoodStat - 1;
                cout << "pop";
            }
        } while (FoodStat >= 2 && FoodStat <= 5);
    } while (Diff < FoodDecrease);

    do {
        // When the SleepStatus is between 2 and 5 it will check if the time since the program has started 
        do {
            // Create a time variable that is marked when the FoodStatus is in the range of 2 and 5.
            auto send = std::chrono::system_clock::now();

            // Find the time difference between the start point of the program and the end point created above.
            std::chrono::duration<double> sdiff = send - StartTime;

            // Assign this value to a double variable.
            double sTimeDiff = sdiff.count();

            // If the difference is the same as the decrease time then decrease SleepStatus by 1.
            if (sTimeDiff == SleepDecrease) {
                SleepStat = SleepStat - 1;
            }
        } while (SleepStat >= 2 && SleepStat <= 5);
    } while (Diff < SleepDecrease);
}