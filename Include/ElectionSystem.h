#ifndef ELECTIONSYSTEM_H
#define ELECTIONSYSTEM_H

#include "Models.h"

class ElectionSystem
{
private:
    // DYNAMIC ARRAYS For polymorphism
    Voter* voters;
    int voterCount;
    int voterCapacity;

    Candidate* candidates;
    int candidateCount;
    int candidateCapacity;

    // Memory Managers
    void resizeVoters();
    void resizeCandidates();

    // File Handling
    void loadVoters();
    void saveVoters();
    void loadCandidates();
    void saveCandidates();

    // helpers for functions
    string getCurrentTime();
    string extractJsonValue(string line, string key);

public:
    ElectionSystem();
    ~ElectionSystem(); // Destructor needed for pointers ill explain on sunday



    void registerVoter();
    void registerCandidate();
    void voterLogin();
    void candidateLogin();

    // Admin stuff
    void approveCandidates();
    void resetElection();
    void showAdminMenu();
};

#endif