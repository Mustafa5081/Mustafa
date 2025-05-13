#include <iostream>
#include <fstream>
#include <cstring>
#include "User.h"
#include "Quiz.h"
#include "Result.h"
#include "QuizManager.h"
#include "Leaderboard.h"
using namespace std;

void showAdminMenu() {
    cout << "\n=== Admin Panel ===\n";
    cout << "1. Create Quiz\n";
    cout << "2. Delete Quiz\n";
    cout << "3. View All Results\n";
    cout << "4. View Leaderboard\n";
    cout << "0. Logout\n";
}

void showStudentMenu() {
    cout << "\n=== Student Panel ===\n";
    cout << "1. Take Quiz\n";
    cout << "2. View My Results\n";
    cout << "0. Logout\n";
}

int main() {
    User currentUser;
    int choice;

    while (true) {
        cout << "\n===================================";
        cout << "\n|   WELCOME TO QUIZ APPLICATION   |";
        cout << "\n===================================\n";
        cout << "\n1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            currentUser.registerUser();
        }
        else if (choice == 2) {
            if (currentUser.loginUser()) {
                int innerChoice;

                if (currentUser.getIsAdmin()) {
                    do {
                        showAdminMenu();
                        cout << "Enter choice: ";
                        cin >> innerChoice;

                        QuizManager qm;
                        if (innerChoice == 1) {
                            qm.createQuiz();
                        }
                        else if (innerChoice == 2) {
                            qm.deleteQuiz();
                        }
                        else if (innerChoice == 3) {
                            ifstream fin("data/results.txt");
                            if (!fin) {
                                cout << "No results found.\n";
                            }
                            else {
                                Result r;
                                while (r.loadFromFile(fin)) {
                                    r.showResult();
                                }
                                fin.close();
                            }
                        }
                        else if (innerChoice == 4) {
                            Leaderboard lb;
                            lb.displayTopScores();
                        }
                    } while (innerChoice != 0);
                }
                else {
                    do {
                        showStudentMenu();
                        cout << "Enter choice: ";
                        cin >> innerChoice;

                        if (innerChoice == 1) {
                            Quiz quiz;
                            char quizPath[100];
                            cout << "Enter quiz file path (e.g., data/quiz_sample.txt): ";
                            cin >> quizPath;

                            if (quiz.loadQuiz(quizPath)) {
                                quiz.conductQuiz(currentUser.getUsername());
                            }
                            else {
                                cout << "Quiz file not found.\n";
                            }
                        }
                        else if (innerChoice == 2) {
                            ifstream fin("data/results.txt");
                            if (!fin) {
                                cout << "No results found.\n";
                            }
                            else {
                                Result r;
                                bool found = false;

                                while (r.loadFromFile(fin)) {
                                    // Debug print
                                    cout << "DEBUG: Found user in results: " << r.getUsername() << endl;

                                    // Case-insensitive comparison
                                    if (_stricmp(r.getUsername(), currentUser.getUsername()) == 0) {
                                        r.showResult();
                                        found = true;
                                    }
                                }

                                if (!found) {
                                    cout << "No results for your account.\n";
                                }

                                fin.close();
                            }
                        }
                        else if (innerChoice != 0) {
                            cout << "Invalid input. Try again.\n";
                        }

                    } while (innerChoice != 0);
                }
            }
        }
        else if (choice == 0) {
            cout << "Thank you for using the application!\n";
            break;
        }
        else {
            cout << "Invalid input.\n";
        }
    }

    return 0;
}
