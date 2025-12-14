#ifndef ELECTIONSYSTEM_H
#define ELECTIONSYSTEM_H

#include "Models.h"

class ElectionSystem {
private:
    // DYNAMIC ARRAYS (Replacing Vectors)
    Voter* voters;
    int voterCount;
    int voterCapacity;

    Candidate* candidates;
    int candidateCount;
    int candidateCapacity;

    // Memory Management
    void resizeVoters();
    void resizeCandidates();

    // File Handling
    void loadVoters();
    void saveVoters();
    void loadCandidates();
    void saveCandidates();

    // Helpers
    string getCurrentTime();
    string extractJsonValue(string line, string key);

public:
    ElectionSystem();
    ~ElectionSystem(); // Destructor needed for pointers

    void registerVoter();
    void registerCandidate(); // Sets to Pending
    void voterLogin();

    // Admin features
    void approveCandidates(); // New Logic
    void showAdminMenu();
    void resetElection();
};

#endif