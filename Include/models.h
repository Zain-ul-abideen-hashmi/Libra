#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <iostream>

using namespace std;

// --- Base Class ---
class Person {
protected:
    int id;
    string name;

public:
    Person() : id(0), name("") {} // Default constructor for arrays
    Person(int id, string name) : id(id), name(name) {}
    virtual ~Person() {}
    virtual void displayInfo() const = 0;

    string getName() const { return name; }
    int getId() const { return id; }
};

// --- Voter Class ---
class Voter : public Person {
private:
    string cnic;
    string password;
    bool hasVoted;
    string voteTime;

public:
    Voter() : Person(), cnic(""), password(""), hasVoted(false) {} // Default

    Voter(int id, string name, string cnic, string pwd, bool voted = false, string time = "N/A")
        : Person(id, name), cnic(cnic), password(pwd), hasVoted(voted), voteTime(time) {}

    void displayInfo() const override {
        cout << "Voter [" << id << "] " << name << " | CNIC: " << cnic;
        if(hasVoted) cout << " | Voted At: " << voteTime;
        cout << endl;
    }

    string getCnic() const { return cnic; }
    string getPassword() const { return password; }
    bool checkPassword(string input) const { return input == password; }
    bool getStatus() const { return hasVoted; }
    string getVoteTime() const { return voteTime; }

    void markVoted(string time) {
        hasVoted = true;
        voteTime = time;
    }
};

// --- Candidate Class ---
class Candidate : public Person {
private:
    int age;
    string party;
    string symbol;
    int voteCount;
    string policies[10]; // Fixed Array instead of Vector
    int policyCount;

    // Approval System
    int approvals; // 0 to 2
    bool isApproved;

public:
    Candidate() : Person(), age(0), voteCount(0), policyCount(0), approvals(0), isApproved(false) {}

    Candidate(int id, string name, int age, string party, string symbol, int votes = 0, int app = 0, bool appr = false)
        : Person(id, name), age(age), party(party), symbol(symbol), voteCount(votes), policyCount(0), approvals(app), isApproved(appr) {}

    void addPolicy(string p) {
        if(policyCount < 10) {
            policies[policyCount++] = p;
        }
    }

    // Helper to get raw array access (read-only logic)
    string getPolicy(int index) const {
        if(index >= 0 && index < policyCount) return policies[index];
        return "";
    }
    int getPolicyCount() const { return policyCount; }

    void displayInfo() const override {
        cout << "--------------------------------\n";
        cout << "[" << id << "] " << name << " (" << party << ")\n";
        cout << "    Symbol: " << symbol << " | Votes: " << voteCount;
        if(!isApproved) cout << " [PENDING APPROVAL: " << approvals << "/2]";
        cout << "\n    Policies:\n";
        for(int i=0; i<policyCount; i++) {
            cout << "      - " << policies[i] << "\n";
        }
        cout << "--------------------------------\n";
    }

    void incrementVote() { voteCount++; }
    int getVotes() const { return voteCount; }
    int getAge() const { return age; }
    string getParty() const { return party; }
    string getSymbol() const { return symbol; }

    // Approval Logic
    void addApproval() {
        if(approvals < 2) approvals++;
        if(approvals >= 2) isApproved = true;
    }
    bool getIsApproved() const { return isApproved; }
    int getApprovalCount() const { return approvals; }
};

#endif