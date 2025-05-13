#include "Leaderboard.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

struct ScoreEntry {
    char username[30];
    char quizTitle[50];
    int score;
    int total;
};

bool compareScore(const ScoreEntry& a, const ScoreEntry& b) {
    return a.score > b.score;
}

void Leaderboard::displayTopScores(int topN) {
    ifstream fin("data/results.txt");
    if (!fin) {
        cout << "No results to display.\n";
        return;
    }

    vector<ScoreEntry> entries;
    ScoreEntry e;
    while (fin >> e.username >> e.quizTitle >> e.score >> e.total) {
        entries.push_back(e);
    }
    fin.close();

    sort(entries.begin(), entries.end(), compareScore);

    cout << "\n=== Leaderboard (Top " << topN << ") ===\n";
    for (int i = 0; i < entries.size() && i < topN; ++i) {
        cout << i + 1 << ". " << entries[i].username
            << " | Quiz: " << entries[i].quizTitle
            << " | Score: " << entries[i].score << "/" << entries[i].total << "\n";
    }
}
