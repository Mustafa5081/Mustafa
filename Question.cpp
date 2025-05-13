#include "Question.h"
#include <fstream>
#include <cstring>
using namespace std;

Question::Question() {
    questionText[0] = '\0';
    for (int i = 0; i < 4; ++i)
        options[i][0] = '\0';
    correctOption = 0;
}

void Question::inputQuestion() {
    cin.ignore();
    cout << "Enter question: ";
    cin.getline(questionText, 200);
    for (int i = 0; i < 4; ++i) {
        cout << "Option " << (i + 1) << ": ";
        cin.getline(options[i], 100);
    }
    cout << "Enter correct option number (1-4): ";
    cin >> correctOption;
}

void Question::displayQuestion() const {
    cout << "\n" << questionText << "\n";
    for (int i = 0; i < 4; ++i) {
        cout << (i + 1) << ". " << options[i] << "\n";
    }
}

bool Question::isCorrect(int userChoice) const {
    return userChoice == correctOption;
}

void Question::saveToFile(ofstream& out) const {
    out << questionText << "\n";
    for (int i = 0; i < 4; ++i)
        out << options[i] << "\n";
    out << correctOption << "\n";
}

bool Question::loadFromFile(ifstream& in) {
    in.getline(questionText, 200);
    if (in.eof()) return false;
    for (int i = 0; i < 4; ++i)
        in.getline(options[i], 100);
    in >> correctOption;
    in.ignore();
    return true;
}
