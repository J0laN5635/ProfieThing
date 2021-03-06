// ProfieThing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class file
{
private:
    int playerID;
    string playerName;
    int age;

public:

    //Input for creating new file
    void input()
    {
        cout << "\nEnter Player ID:";
        cin >> playerID;

        string strFirst = "";
        string strLast = "";
        cout << "\nEnter first name:";
        cin >> strFirst;
        cout << "\nEnter last name:";
        cin >> strLast;
        playerName = strFirst + " " + strLast; //Takes first and last name into a single variabe

        cout << "Enter age:";
        cin >> age;

    }

    //Record Output
    void output()
    {
        cout << "\nPlayer Details: \n";
        cout << "Player ID:" << playerID << endl;
        cout << "Name:" << playerName << endl;
        cout << "Age:" << age << endl;

    }

    //Variables to return Infomation
    string retplayername()
    {
        return playerName;
    }

    int retplayerID()
    {
        return playerID;
    }

    int retage()
    {
        return age;
    }

};

//Write Details to file
void writetofile(file fobj)
{
    char arr[]= "     ";
    ofstream fout;
    fout.open("PlayerRecords.txt", ios::out | ios::app);
    fout << "id";
    fout << fobj.retplayerID(); fout << arr;
    fout << fobj.retplayername(); fout << arr;
    fout << fobj.retage(); fout << arr;

    fout.close();
}

//List all Players
void showAllRecords()
{
    ifstream readFile;
    readFile.open("PlayerRecords.txt");
    char charsInLine[1024];
    int count = 0;
    cout << "Player Records:\n\n";
    while (!readFile.eof())
    {
        readFile.getline(charsInLine,1024);
        cout << charsInLine << endl;
    }
    readFile.close();

}

//Delete Record
void deleteRecord()
{
    string deleteString;
    cout << "Enter Player ID to delete:\n";
    cin >> deleteString;
    deleteString = "ID" + deleteString;
    cout << "deleteString: " << deleteString << endl;

    ifstream readFile;
    ofstream writeFile("sample.txt");
    
    char charsInLine[1024];

    readFile.open("PlayerRecords.txt");
    int count = 0;
    bool found = false; //checks for ID
    while (!readFile.eof())
    {
        readFile.getline(charsInLine, 1024);
        string strLine(charsInLine); //Converts to String
        cout << count << ": " << charsInLine << endl;
        size_t found = strLine.find(deleteString);

        if (found != string::npos)
        {
            found = true; //Since ID has been found stores the value as true
            break;
        }

        else
        {
            writeFile << charsInLine;
            writeFile << "\n";
        }
        
        count++;
    }

    readFile.close();
    writeFile.close();

    remove("PlayerRecords.txt");
    rename("sample.txt", "PlayerRecords.txt");

    if (found == false)
    {
        cout << "Unknown Player ID\n";
    }
}

void countPlayers()
{
    ifstream readFile;
    char charsInLine[1024];
    int countPlayer = 0;

    readFile.open("PlayerRecords.txt");
    while (!readFile.eof())
    {
        readFile.getline(charsInLine, 1024);
        string strLine(charsInLine);

        size_t found = strLine.find("ID");

        if (found != string::npos)
        {
            countPlayer++;
            cout << charsInLine << endl;
        }
        else
        {
            break;
        }
    }

    cout << "Number of Players in Records: " << countPlayer << endl;
    readFile.close();
}

void searchRecors()
{
    string searchString = "";
    cout << "Enter Player ID:";
    cin >> searchString;
    searchString = "ID" + searchString;
    cout << "Search String: " << searchString << endl;

    ifstream readFile;
    readFile.open("PlayerRecords.txt");
    char charsInLine[1024];
    int count = 0;
    searchString = searchString + " ";

    while (!readFile.eof())
    {
        readFile.getline(charsInLine, 1024);
        
        string strLine(charsInLine);

        size_t found = strLine.find(searchString);

        if (found != string::npos)
        {
            count++;
            cout << "Records " << count << " : " << charsInLine << endl;
        }
    }

    readFile.close();
    if (count == 0)
    {
        cout << "No records found.\n";
    }
    else
    {
        cout << "No. of Records found for " << searchString << ": " << count << endl;
    }
}

void clearDatabase()
{
    int x;
    cout << "Do you want to delete the complete Database?\n Press [1] to confirm:";
    cin >> x;

    if (x == 1)
    {
        remove("PlayersRecord.txt");
        ofstream writeFile("PlayerRecords.txt");
        writeFile.close();
    }
}

int main()
{
    file fileobj;

    while(1)
    {
        int input;
        cout << "\nMenu";
        cout << "\n[1]: Add Player";
        cout << "\n[2]: List Players";
        cout << "\n[3]: Search Player (ID)";
        cout << "\n[4]: Delete Player (ID)";
        cout << "\n[5]: Clear Database";
        cout << "\n[6]: Exit\n";

        cin >> input;

        switch (input)
        {
        case 1: fileobj.input();
            writetofile(fileobj);
            break;
        case 2: showAllRecords();
        case 3: searchRecors();
        case 4: deleteRecord();
        case 5: clearDatabase();
        case 6: cout << "Exiting.\n";
            exit(0);
        default: cout << "Please enter a valid Option.\n";
            break;
        }
    }

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
