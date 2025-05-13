#include "Quiz.h"
#include <windows.h> 

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Quiz::Quiz() {
    quizTitle[0] = '\0';
    totalQuestions = 0;
    timeLimit = 30;
}

bool Quiz::loadQuiz(const char* filename) {
    ifstream fin(filename);
    if (!fin) return false;

    fin.getline(quizTitle, 50);
    fin >> timeLimit;
    fin.ignore();

    totalQuestions = 0;
    while (questions[totalQuestions].loadFromFile(fin)) {
        totalQuestions++;
        if (totalQuestions >= 20) break;
    }

    fin.close();
    return true;
}

int Quiz::conductQuiz(const char* username) {
    system("cls");
    cout << "╔════════════════════════════════════╗\n";
    cout << "║       Starting Quiz: " << quizTitle << "       ║\n";
    cout << "╚════════════════════════════════════╝\n";
    cout << "Time Limit: " << timeLimit << " seconds\n";

    int score = 0;

    int indices[20];
    for (int i = 0; i < totalQuestions; ++i)
        indices[i] = i;

    srand(time(0));
    for (int i = 0; i < totalQuestions; ++i) {
        int r = rand() % totalQuestions;
        swap(indices[i], indices[r]);
    }

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < totalQuestions; ++i) {
        auto now = chrono::steady_clock::now();
        int elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();
        if (elapsed >= timeLimit) {
            setColor(12);
            cout << "\nTime's up!\n";
            setColor(7);
            break;
        }

        cout << "\n-------------------------------------\n";
        cout << "Question " << (i + 1) << ":\n";
        questions[indices[i]].displayQuestion();
        cout << "Enter your answer (1-4): ";
        int userChoice;
        cin >> userChoice;

        if (questions[indices[i]].isCorrect(userChoice)) {
            setColor(10); 
            cout << "Correct!\n";
            score++;
        }
        else {
            setColor(12); 
            cout << "Wrong!\n";
        }
        setColor(7); 
        cout << "Remaining Time: " << (timeLimit - elapsed) << " seconds\n";
        Sleep(800); 
    }

    cout << "\n======================================\n";
    setColor(11);
    cout << "        Quiz Completed!\n";
    setColor(7);
    cout << "Your Score: " << score << " / " << totalQuestions << "\n";
    cout << "======================================\n";

    ofstream fout("data/results.txt", ios::app);
    fout << username << " " << quizTitle << " " << score << " " << totalQuestions << "\n";
    fout.close();

    return score;
}

const char* Quiz::getTitle() const {
    return quizTitle;
}
