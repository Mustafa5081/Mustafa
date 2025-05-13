#include "Result.h"
#include <fstream>
#include <cstring>
using namespace std;

Result::Result() {
    username[0] = '\0';
    quizTitle[0] = '\0';
    score = 0;
    total = 0;
}

void Result::showResult() const {
    cout << "User: " << username
        << " | Quiz: " << quizTitle
        << " | Score: " << score << "/" << total << "\n";
}

bool Result::loadFromFile(ifstream& in) {
    return (in >> username >> quizTitle >> score >> total);
}

const char* Result::getUsername() const {
    return username;
}
