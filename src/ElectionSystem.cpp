#include "../Include/ElectionSystem.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <cstdlib> // For system()

using namespace std;

// --- Helper Functions ---
string ElectionSystem::getCurrentTime()
{
    time_t now = time(0);
    string dt = ctime(&now);
    if(dt.length() > 0) dt.pop_back();
    return dt;
}

string ElectionSystem::extractJsonValue(string line, string key)
{
    string search = "\"" + key + "\":";
    size_t pos = line.find(search);
    if (pos == string::npos) return "";
    pos += search.length();
    while (line[pos] == ' ') pos++;
    if (line[pos] == '"')
    {
        size_t end = line.find("\"", pos + 1);
        return line.substr(pos + 1, end - pos - 1);
    } else if (line[pos] == '[')
    {
        size_t end = line.find("]", pos);
        return line.substr(pos, end - pos + 1);
    } else
    {
        size_t end = line.find_first_of(",}", pos);
        return line.substr(pos, end - pos);
    }
}

// Memory Manage using arrays
ElectionSystem::ElectionSystem()
{
    voterCapacity = 10;
    voterCount = 0;
    voters = new Voter[voterCapacity];

    candidateCapacity = 5;
    candidateCount = 0;
    candidates = new Candidate[candidateCapacity];

    loadCandidates();
    loadVoters();
}

ElectionSystem::~ElectionSystem()
{
    delete[] voters;
    delete[] candidates;
}

void ElectionSystem::resizeVoters()
{
    voterCapacity *= 2;
    Voter* temp = new Voter[voterCapacity];
    for(int i=0; i<voterCount; i++) temp[i] = voters[i];
    delete[] voters;
    voters = temp;
}

void ElectionSystem::resizeCandidates()
{
    candidateCapacity *= 2;
    Candidate* temp = new Candidate[candidateCapacity];
    for(int i=0; i<candidateCount; i++) temp[i] = candidates[i];
    delete[] candidates;
    candidates = temp;
}

// json file
void ElectionSystem::saveVoters()
{
    ofstream file("voters.json");
    file << "[\n";
    for (int i = 0; i < voterCount; i++)
    {
        file << "  {\n";
        file << "    \"id\": " << voters[i].getId() << ",\n";
        file << "    \"name\": \"" << voters[i].getName() << "\",\n";
        file << "    \"cnic\": \"" << voters[i].getCnic() << "\",\n";
        file << "    \"password\": \"" << voters[i].getPassword() << "\",\n";
        file << "    \"hasVoted\": " << (voters[i].getStatus() ? "true" : "false") << ",\n";
        file << "    \"timestamp\": \"" << voters[i].getVoteTime() << "\"\n";
        file << "  }" << (i < voterCount - 1 ? "," : "") << "\n";
    }
    file << "]";
    file.close();
}

void ElectionSystem::loadVoters()
{
    voterCount = 0;
    ifstream file("voters.json");
    if (!file) return;
    string line;
    while (getline(file, line))
    {
        if (line.find("{") != string::npos)
        {
            string block = "";
            while(getline(file, line) && line.find("}") == string::npos) block += line;

            if(voterCount == voterCapacity) resizeVoters();

            int id = stoi(extractJsonValue(block, "id"));
            string name = extractJsonValue(block, "name");
            string cnic = extractJsonValue(block, "cnic");
            string pass = extractJsonValue(block, "password");
            bool hasVoted = (extractJsonValue(block, "hasVoted") == "true");
            string time = extractJsonValue(block, "timestamp");

            voters[voterCount++] = Voter(id, name, cnic, pass, hasVoted, time);
        }
    }
    file.close();
}

void ElectionSystem::saveCandidates()
{
    ofstream file("candidates.json");
    file << "[\n";
    for (int i = 0; i < candidateCount; i++)
    {
        file << "  {\n";
        file << "    \"id\": " << candidates[i].getId() << ",\n";
        file << "    \"name\": \"" << candidates[i].getName() << "\",\n";
        file << "    \"age\": " << candidates[i].getAge() << ",\n";
        file << "    \"party\": \"" << candidates[i].getParty() << "\",\n";
        file << "    \"symbol\": \"" << candidates[i].getSymbol() << "\",\n";
        file << "    \"password\": \"" << candidates[i].getPassword() << "\",\n"; // <--- SAVING PASSWORD
        file << "    \"votes\": " << candidates[i].getVotes() << ",\n";
        file << "    \"approvals\": " << candidates[i].getApprovalCount() << ",\n";
        file << "    \"isApproved\": " << (candidates[i].getIsApproved() ? "true" : "false") << ",\n";
        file << "    \"policies\": [";
        for(int p=0; p < candidates[i].getPolicyCount(); p++)
        {
            file << "\"" << candidates[i].getPolicy(p) << "\"" << (p < candidates[i].getPolicyCount()-1 ? ", " : "");
        }
        file << "]\n";
        file << "  }" << (i < candidateCount - 1 ? "," : "") << "\n";
    }
    file << "]";
    file.close();
}

void ElectionSystem::loadCandidates()
{
    candidateCount = 0;
    ifstream file("candidates.json");
    if (!file) return;
    string line;
    while (getline(file, line))
    {
        if (line.find("{") != string::npos)
        {
            string block = "";
            while(getline(file, line))
            {
                block += line;
                if(line.find("}") != string::npos) break;
            }

            if(candidateCount == candidateCapacity) resizeCandidates();

            int id = stoi(extractJsonValue(block, "id"));
            string name = extractJsonValue(block, "name");
            int age = stoi(extractJsonValue(block, "age"));
            string party = extractJsonValue(block, "party");
            string symbol = extractJsonValue(block, "symbol");
            string pwd = extractJsonValue(block, "password"); // <--- LOADING PASSWORD
            int votes = stoi(extractJsonValue(block, "votes"));
            int apps = stoi(extractJsonValue(block, "approvals"));
            bool isApp = (extractJsonValue(block, "isApproved") == "true");

            // Update Constructor Call
            candidates[candidateCount] = Candidate(id, name, age, party, symbol, pwd, votes, apps, isApp);

            string polArr = extractJsonValue(block, "policies");
            string temp = "";
            bool insideQuote = false;
            for(char c : polArr) {
                if(c == '"') {
                    if(insideQuote) { candidates[candidateCount].addPolicy(temp); temp = ""; }
                    insideQuote = !insideQuote;
                } else if (insideQuote) { temp += c; }
            }
            candidateCount++;
        }
    }
    file.close();
}
// Main functions

void ElectionSystem::registerCandidate()
{
    string name, party, symbol, pwd; //pwd stands for passwqrd btw
    int age;
    cout << "\n--- CANDIDATE REGISTRATION ---\n";
    cout << "Name: "; cin.ignore(); getline(cin, name);
    cout << "Age: "; cin >> age;
    cout << "Party: "; cin.ignore(); getline(cin, party);
    cout << "Symbol: "; getline(cin, symbol);
    cout << "Create Login Password: "; cin >> pwd; // <--- INPUT

    if(candidateCount == candidateCapacity) resizeCandidates();


    candidates[candidateCount] = Candidate(candidateCount + 1, name, age, party, symbol, pwd, 0, 0, false);


    candidates[candidateCount].addPolicy("Economic Growth");
    candidates[candidateCount].addPolicy("Better Education");
    candidates[candidateCount].addPolicy("Healthcare Reform");

    candidateCount++;
    saveCandidates();
    cout << "Candidate Registered! Login ID is: " << candidateCount << "\n";
    _getch();
}

void ElectionSystem::approveCandidates()
{
    system("cls");
    cout << "\n--- PENDING APPROVALS ---\n";
    bool foundPending = false;

    for(int i=0; i<candidateCount; i++)
    {
        if(!candidates[i].getIsApproved())
        {
            foundPending = true;
            candidates[i].displayInfo();

            char choice;
            cout << "Approve this candidate? (y/n): "; cin >> choice;
            if(choice == 'y' || choice == 'Y')
            {


                int approvalsNeeded = 2 - candidates[i].getApprovalCount();
                cout << "Current Approvals: " << candidates[i].getApprovalCount() << "/2\n";
                cout << "Need " << approvalsNeeded << " more unique admin login(s) to approve.\n";

                // Simulate Admin Approval
                string adminName;
                cout << "Enter Admin Name to sign off: "; cin >> adminName;

                candidates[i].addApproval();
                cout << "Approval added!\n";

                if(candidates[i].getIsApproved()) {
                    cout << ">>> CANDIDATE IS NOW LIVE! <<<\n";
                }
                saveCandidates();
            }
        }
    }

    if(!foundPending) cout << "No pending candidates.\n";
    _getch();
}

void ElectionSystem::voterLogin()
{
    string cnic, pwd;
    cout << "\n--- VOTER LOGIN --\n";
    cout << "Enter CNIC: "; cin >> cnic;

    bool found = false;
    for (int i = 0; i < voterCount; i++)
    {
        if (voters[i].getCnic() == cnic)
        {
            found = true;
            cout << "Password: "; cin >> pwd;
            if (voters[i].checkPassword(pwd))
            {
                if (voters[i].getStatus())
                {
                    cout << "Error: You already voted on " << voters[i].getVoteTime() << "!\n";
                } else {
                    // --- VOTING PROCESS ---
                    system("cls");
                    cout << "\n--- OFFICIAL BALLOT ---\n";
                    bool candidatesAvailable = false;
                    for (int c = 0; c < candidateCount; c++) {
                        if(candidates[c].getIsApproved()) {
                            candidates[c].displayInfo();
                            candidatesAvailable = true;
                        }
                    }

                    if(!candidatesAvailable) {
                        cout << "No approved candidates yet.\n";
                        _getch(); return;
                    }

                    int choiceID;
                    cout << "\nEnter Candidate ID: "; cin >> choiceID;

                    bool voted = false;
                    for(int c=0; c<candidateCount; c++) {
                        if(candidates[c].getId() == choiceID && candidates[c].getIsApproved()) {
                            candidates[c].incrementVote();
                            voters[i].markVoted(getCurrentTime());
                            voted = true;

                            // --- PYTHON EMAIL SURPRISE ---
                            char wantEmail;
                            cout << "\nVote Cast! Do you want a commemorative card? (y/n): ";
                            cin >> wantEmail;
                            if(wantEmail == 'y' || wantEmail == 'Y') {
                                string email;
                                cout << "Enter Email: "; cin >> email;
                                cout << "Generating Card (please wait)...\n";

                                // Call Python
                                string cmd = R"(D:/Libra/Scripts/activate_this.py D:/Libra/Scripts/GenerateCard.py )" + email;
                                system(cmd.c_str());
                            }
                            break;
                        }
                    }

                    if(voted)
                    {
                        saveCandidates();
                        saveVoters();
                    } else
                    {
                        cout << "Invalid ID.\n";
                    }
                }
            }
            else
            {
                cout << "Wrong Password.\n";
            }
            break;
        }
    }
    if (!found) cout << "CNIC not registered.\n";
    _getch();
}


void ElectionSystem::candidateLogin()
{
    int id;
    string pwd;
    cout << "\n--- CANDIDATE LOGIN --\n";
    cout << "Enter Candidate ID: "; cin >> id;

    int index = -1;

    for(int i=0; i<candidateCount; i++)
    {
        if(candidates[i].getId() == id)
        {
            index = i;
            break;
        }
    }

    if(index == -1) {
        cout << "Candidate ID not found.\n";
        _getch(); return;
    }

    cout << "Enter Password: "; cin >> pwd;
    if(candidates[index].getPassword() != pwd) {
        cout << "Incorrect Password.\n";
        _getch(); return;
    }


    while(true) {
        system("cls");
        cout << "=== WELCOME " << candidates[index].getName() << " ===\n";
        cout << "Party: " << candidates[index].getParty() << "\n\n";
        cout << "1. View Campaign Status & Win Probability\n";
        cout << "2. Log Out\n";
        cout << "Choice: ";

        int choice; cin >> choice;

        if(choice == 1)
            {
            system("cls");
            cout << "\n--- CAMPAIGN ANALYTICS ---\n";


            cout << "Approval Status: ";
            if(candidates[index].getIsApproved()) cout << "[APPROVED] (Live for voting)\n";
            else cout << "[PENDING] (Approvals: " << candidates[index].getApprovalCount() << "/2)\n";


            int myVotes = candidates[index].getVotes();
            cout << "Current Votes:   " << myVotes << "\n";


            int totalVotes = 0;
            for(int i=0; i<candidateCount; i++)
            {
                totalVotes += candidates[i].getVotes();
            }

            cout << "Win Probability: ";
            if(totalVotes == 0)
            {
                cout << "0% (No votes cast yet)\n";
            } else
            {
                float prob = ((float)myVotes / totalVotes) * 100.0f;
                cout << prob << "% ";


                if(prob > 50) cout << "(Strong Lead for now)";
                else if(prob > 20) cout << "(Its aight)";
                else cout << "(your not winning )";
                cout << "\n";
            }
            cout << "\n---------------------------\n";
            _getch();
        }
        else
        {
            break;
        }
    }
}

void ElectionSystem::registerVoter()
{

    if(voterCount == voterCapacity) resizeVoters();

    string name, cnic, pwd;
    cout << "\n--- VOTER REGISTRATION ---\n";
    cout << "Name: "; cin.ignore(); getline(cin, name);
    cout << "CNIC: "; cin >> cnic;

    for(int i=0; i<voterCount; i++)
    {
        if(voters[i].getCnic() == cnic)
        {
            cout << "Duplicate CNIC.\n";
             _getch(); return;
        }
    }

    cout << "Password: "; cin >> pwd;
    voters[voterCount++] = Voter(voterCount + 1, name, cnic, pwd);
    saveVoters();
    cout << "Registered.\n";
    _getch();
}

void ElectionSystem::showAdminMenu()
{
    while(true)
    {
        system("cls");
        cout << "--- ADMIN PANEL ---\n";
        cout << "1. Approve Pending Candidates\n";
        cout << "2. View Live Results\n";
        cout << "3. End Election (Reset System)\n"; // <--- Updated Option
        cout << "4. Exit\n";

        int c;
        cout << "Choice: ";
        cin >> c;

        if(c == 1) approveCandidates();
        else if(c == 2)
        {
            cout << "\n--- LIVE STANDINGS ---\n";
            bool dataFound = false;
            for(int i=0; i<candidateCount; i++)
            {
                if(candidates[i].getIsApproved())
                {
                    cout << candidates[i].getName() << " (" << candidates[i].getParty() << "): "
                         << candidates[i].getVotes() << " votes\n";
                    dataFound = true;
                }
            }
            if(!dataFound) cout << "No approved candidates to show.\n";
            _getch();
        }
        else if(c == 3)
        {
            resetElection(); // <--- Call the new function
        }
        else break;
    }
}

void ElectionSystem::resetElection()
{
    char confirm;
    system("cls");
    cout << "\n=======================================================\n";
    cout << "!!! DANGER: ENDING ELECTION !!!";
    cout << "\n=======================================================\n";
    cout << "This action will:\n";
    cout << "1. DELETE all registered Voter data.\n";
    cout << "2. DELETE all Candidate data and policies.\n";
    cout << "3. DELETE all Vote counts.\n";
    cout << "4. Reset the system for a fresh start.\n";
    cout << "\nAre you sure you want to proceed? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y')
    {

        voterCount = 0;
        candidateCount = 0;


        ofstream vFile("voters.json", ios::trunc);
        vFile << "[]";
        vFile.close();

        ofstream cFile("candidates.json", ios::trunc);
        cFile << "[]";
        cFile.close();

        cout << "\n> Election Ended.\n> All Data Wiped.\n> System Reset Successfully.\n";
        _getch();
    }
    else
    {
        cout << "\nAction Cancelled. Data is safe.\n";
        _getch();
    }
}