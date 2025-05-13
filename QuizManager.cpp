#include "QuizManager.h"

void QuizManager::createQuiz() {
    char filename[100];
    char title[50];
    int timeLimit, n;

    cout << "Enter filename to save quiz (e.g., data/quiz_new.txt): ";
    cin >> filename;
    cin.ignore();
    cout << "Enter quiz title: ";
    cin.getline(title, 50);
    cout << "Enter time limit (seconds): ";
    cin >> timeLimit;
    cout << "Enter number of questions (max 20): ";
    cin >> n;

    ofstream fout(filename);
    if (!fout) {
        cout << "Unable to create quiz file.\n";
        return;
    }

    fout << title << "\n" << timeLimit << "\n";
    for (int i = 0; i < n; ++i) {
        cout << "\nQuestion " << (i + 1) << ":\n";
        Question q;
        q.inputQuestion();
        q.saveToFile(fout);
    }

    fout.close();
    cout << "Quiz saved successfully to " << filename << "\n";
}

void QuizManager::deleteQuiz() {
    char filename[100];
    cout << "Enter quiz filename to delete (e.g., data/quiz_sample.txt): ";
    cin >> filename;
    if (remove(filename) == 0)
        cout << "Quiz deleted successfully.\n";
    else
        cout << "Error deleting quiz. File may not exist.\n";
}
