#include "User.h"
using namespace std;

User::User() {
    username[0] = '\0';
    password[0] = '\0';
    isAdmin = false;
}

bool User::registerUser() {
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    char role;
    cout << "Are you admin? (y/n): ";
    cin >> role;
    isAdmin = (role == 'y' || role == 'Y');

    ofstream fout("data/users.txt", ios::app);
    if (!fout) {
        cout << "Error opening user file.\n";
        return false;
    }
    fout << username << " " << password << " " << isAdmin << "\n";
    fout.close();
    cout << "Registration successful!\n";
    return true;
}

bool User::loginUser() {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream fin("data/users.txt");
    if (!fin) {
        cout << "Error opening user file.\n";
        return false;
    }

    char tempUser[30], tempPass[30];
    int role;
    while (fin >> tempUser >> tempPass >> role) {
        if (strcmp(username, tempUser) == 0 && strcmp(password, tempPass) == 0) {
            isAdmin = role;
            cout << "Login successful!\n";
            fin.close();
            return true;
        }
    }
    fin.close();
    cout << "Invalid credentials.\n";
    return false;
}

bool User::getIsAdmin() const {
    return isAdmin;
}

const char* User::getUsername() const {
    return username;
}
