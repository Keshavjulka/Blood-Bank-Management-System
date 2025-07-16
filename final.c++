#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>// clear,to generate id
#include <conio.h> //console input and output
#include <windows.h>// sleep
//#include <ctime> // for generating unique IDs

using namespace std;

const int MAX_ROWS = 100;

const int MAX_COLS = 100;

string getPassword()
{
    string password;
    char ch;
    while ((ch = _getch()) != '\r')
    { // '\r' is the Enter key
        if (ch == '\b')
        { // Backspace
            if (!password.empty())
            {
                cout << "\b \b";                     
                password.erase(password.size() - 1); 
            }
        }
        else
        {
            cout << '*';    
            password += ch; 
        }
    }
    cout << endl;
    return password;
}

struct Donor
{
    int id;
    string name;
    int age;
    string bloodGroup;
    string lastDonationDate;
    string contactNumber;
};

struct Receiver
{
    int id;
    string name;
    int age;
    string bloodGroup;
    string contactNumber;
};

class BloodBank
{
private:
    vector<Donor> donors;
    vector<Receiver> receivers;
    int bloodUnitsAvailable;
    bool isAdmin;

public:
    BloodBank() : bloodUnitsAvailable(0), isAdmin(false) {
	}

    bool authenticateUser(const string &username, const string &password)
    {
        const string adminUsername = "admin";
        const string adminPassword = "admin123";
        const string userUsername = "user";
        const string userPassword = "user123";

        if (username == adminUsername && password == adminPassword)
        {
            system("cls");
            cout << "Admin login successful!" << endl;
            isAdmin = true;
            Sleep(3000);
            system("cls");
            return true;
        }
        else if (username == userUsername && password == userPassword)
        {
            system("cls");
            cout << "User login successful!" << endl;
            isAdmin = false;
            Sleep(3000);
            system("cls");
            return true;
        }
        else
        {
            cout << "Invalid username or password. Please try again." << endl;
            return false;
        }
    }

    void login()
    {
        string username, password;
        do
        {
            cout << "Login Page" << endl;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            password = getPassword(); // Modified to hide password input
        } while (!authenticateUser(username, password));
    }


void addDonor(const Donor &donor)
{
    if (isAdmin)
    {
        bool isEligible = checkEligibility(donor);
        if (isEligible)
        {
        	 int id = rand() % 1000 + 1; // Random ID between 1 and 1000

            // Set ID for donor
            Donor newDonor = donor;
            newDonor.id = id;

            donors.push_back(newDonor);
            
            // Save the new donor to CSV
            saveDonorToCSV(newDonor);
        }
        else
        {
            cout << "Donor is not eligible to donate blood. Record not added." << endl;
        }
    }
    else
    {
        cout << "Only admin can add donors." << endl;
    }
}
///////////////////////////////////////////////////////////
bool checkEligibility(const Donor &donor)
{
    string answer;
    cout << "Do you have diabetes? (yes/no): ";
    cin >> answer;
    if (answer == "yes")
    {
        return false;
    }

    cout << "Do you have high blood pressure? (yes/no): ";
    cin >> answer;
    if (answer == "yes")
    {
        return false;
    }

    cout << "Do you intake alcohol? (yes/no): ";
    cin >> answer;
    if (answer == "yes")
    {
        return false;
    }

    cout << "Do you smoke? (yes/no): ";
    cin >> answer;
    if (answer == "yes")
    {
        return false;
    }

    return true;
}


    void addReceiver(const Receiver &receiver)
    {
        if (isAdmin)
        {
        	
        	        // Generate random ID
        int id = rand() % 1000 + 1; // Random ID between 1 and 1000

        // Set ID for receiver
        Receiver newReceiver = receiver;
        newReceiver.id = id;
        receivers.push_back(newReceiver);

        // Save the new receiver to CSVa
        saveReceiverToCSV(newReceiver);
        }
        else
        {
            cout << "Only admin can add receivers." << endl;
        }
    }

    void updateBloodUnits(const string &bloodGroup, int units)
    {
        if (isAdmin)
        {
            bloodUnitsAvailable += units;
            saveBloodUnitsToCSV(bloodGroup, bloodUnitsAvailable);
        }
        else
        {
            cout << "Only admin can update blood units available." << endl;
        }
    }

    void displayBloodUnits()
    {
        ifstream file("blood_units.csv");

        string data[MAX_ROWS][MAX_COLS];
        string line;
        int row = 0;
        // Store the CSV data from the CSV file to the 2D array
        while (getline(file, line) && row < MAX_ROWS)
        {
            stringstream ss(line);
            string cell;
            int col = 0;
            while (getline(ss, cell, ',') && col < MAX_COLS)
            {
                data[row][col] = cell;
                col++;
            }
            row++;
        }
        // close the file after read opeartion is complete
        file.close();

        // Print the data stored in the 2D array
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < MAX_COLS && !data[i][j].empty();
                 j++)
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    void displayMenu()
    {
        // system("cls");
        cout << "Blood Bank Management System Menu" << endl;
        cout << "1. View Donor Records" << endl;
        cout << "2. View Receiver Records" << endl;
        cout << "3. View Blood Units Available" << endl;
        if (isAdmin)
        {
            cout << "4. Add Donor" << endl;
            cout << "5. Add Receiver" << endl;
            cout << "6. Update Blood Units Available" << endl;
            cout << "7. Delete Records" << endl;
        }
        cout << "8. Exit" << endl;
    }

    void executeChoice(int choice)
    {
        switch (choice)
        {
        case 1:
            viewDonorRecords();
            break;
        case 2:
            viewReceiverRecords();
            break;
        case 3:
            displayBloodUnits();
            break;
        case 4:
            if (isAdmin)
                addDonor(getDonorInfo());
            break;
        case 5:
            if (isAdmin)
                addReceiver(getReceiverInfo());
            break;
        case 6:
            if (isAdmin)
                updateBloodUnits(getBloodGroup(), getBloodUnits());
            break;
        case 7:
            if (isAdmin)
                deleteRecords();
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    Donor getDonorInfo()
    {
        Donor donor;
        cout << "Enter donor's name: ";
        cin >> donor.name;
        cout << "Enter donor's age: ";
        cin >> donor.age;
        cout << "Enter donor's blood group: ";
        cin >> donor.bloodGroup;
        cout << "Enter last date of donation (YYYY-MM-DD): ";
        cin >> donor.lastDonationDate; // Collect last donation date
        cout << "Enter donor's contact number: ";
        cin >> donor.contactNumber; // Collect contact number
        return donor;
    }

    Receiver getReceiverInfo()
    {
        Receiver receiver;
        cout << "Enter receiver's name: ";
        cin >> receiver.name;
        cout << "Enter receiver's age: ";
        cin >> receiver.age;
        cout << "Enter receiver's blood group: ";
        cin >> receiver.bloodGroup;
        cout << "Enter receiver's contact number: ";
        cin >> receiver.contactNumber; // Collect contact number
        return receiver;
    }

    string getBloodGroup()
    {
        string bloodGroup;
        cout << "Enter the blood group: ";
        cin >> bloodGroup;
        return bloodGroup;
    }

    int getBloodUnits()
    {
        int units;
        cout << "Enter the number of blood units to update: ";
        cin >> units;
        return units;
    }

void saveDonorToCSV(const Donor &donor)
{
    ofstream file("donors.csv", ios::app);
    if (file.is_open())
    {
    
        file << donor.id << "," << donor.name << "," << donor.age << "," << donor.bloodGroup << "," << donor.lastDonationDate << "," << donor.contactNumber << endl;

        file.close();
    }
    else
    {
        cout << "Unable to open donors.csv for writing." << endl;
    }
}

void saveReceiverToCSV(const Receiver &receiver)
{
    ofstream file("receivers.csv", ios::app);
    if (file.is_open())
    {
        file << receiver.id << "," << receiver.name << "," << receiver.age << "," << receiver.bloodGroup  << "," << receiver.contactNumber<< endl;
        file.close();
    }
    else
    {
        cout << "Unable to open receivers.csv for writing." << endl;
    }
}

    void saveBloodUnitsToCSV(const string &bloodGroup, int units)
    {
        ofstream file("blood_units.csv", ios::app);
        if (file.is_open())
        {
            file << bloodGroup << "," << units << endl;
            file.close();
        }
        else
        {
            cout << "Unable to open blood_units.csv for writing." << endl;
        }
    }

    void viewDonorRecords()
    {
        ifstream file("donors.csv");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open donors.csv for reading." << endl;
        }
    }

    void viewReceiverRecords()
    {
        ifstream file("receivers.csv");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open receivers.csv for reading." << endl;
        }
    }

    void deleteRecords()
    {
        if (!isAdmin)
        {
            cout << "Only admin can delete records." << endl;
            return;
        }

        string bloodGroup; // Move the declaration here

        cout << "Select the records to delete:" << endl;
        cout << "1. Delete Donor's Name" << endl;
        cout << "2. Delete Receiver's Name" << endl;
        cout << "3. Delete Blood Units" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("start cmd /k type donors.csv");
            cout << "Enter the donor's name to delete: ";
            deleteRecord("donors.csv");
            break;
        case 2:
            system("start cmd /k type receivers.csv");
            cout << "Enter the receiver's name to delete: ";
            deleteRecord("receivers.csv");
            break;
        case 3:
            system("start cmd /k type blood_units.csv");
            cout << "Enter the blood group and number of units to delete: ";
            int units;
            cin >> bloodGroup >> units; // Read blood group here
            confirmDeleteBloodUnits(bloodGroup, units);
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    void confirmDeleteBloodUnits(const string &bloodGroup, int units)
    {
        ifstream file("blood_units.csv");
        if (file.is_open())
        {
            string line;
            //getline(file, line); // Read the header line
            bool found = false;
            while (getline(file, line))
            {
                istringstream iss(line);
                string group;
                int count;

                
                if (iss >> group >> count)
                {
                    
                    if (group == bloodGroup && count == units)
                    {
                        cout << "Deleting the blood units record..." << endl;
                        file.close();
                        deleteRecord("blood_units.csv");
                        return ;
                    }
                    else if (group == bloodGroup)
                    {
                        found = true;
                    }
                }
            }
            file.close();
            if (found)
            {
                cout << "Number of units does not match for the blood group. Record not deleted." << endl;
            }
            else
            {
                cout << "Blood group not found. Record not deleted." << endl;
            }
        }
        else
        {
            cout << "Unable to open blood_units.csv for reading." << endl;
        }
    }

    void deleteRecord(const string &filename)
    {
        string name;
        cin >> name;
        ifstream fileIn(filename.c_str());
        ofstream fileOut("temp.csv");

        if (fileIn && fileOut)
        {
            string line;
            while (getline(fileIn, line))
            {
                if (line.find(name) == string::npos)
                { // If the line does not contain the name to delete
                    fileOut << line << endl;
                }
            }
            fileIn.close();
            fileOut.close();
            remove(filename.c_str());             // Remove the original file
            rename("temp.csv", filename.c_str()); // Rename the temporary file to the original filename
            cout << "Record deleted successfully." << endl;
        }
        else
        {
            cout << "Error: Unable to delete record." << endl;
        }
    }
    
};

int main()
{
    BloodBank bloodBank;
    bloodBank.login();

    int choice;
    do
    {
        bloodBank.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            bloodBank.executeChoice(choice);
        }
    } while (choice != 8);

    return 0;
}