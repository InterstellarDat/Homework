#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Company structure
struct Company {
    string name;
    string profit_tax;
    string address;
};

// HashTable node for separate chaining
struct HashNode {
    Company company;
    HashNode* next;
    HashNode(const Company& c) : company(c), next(nullptr) {}
};

// HashTable structure
struct HashTable {
    vector<HashNode*> table;
    int size;
    HashTable(int s) : size(s) {
        table.resize(s, nullptr);
    }
    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            HashNode* current = table[i];
            while (current) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

// Read companies from file
vector<Company> readCompanyList(string file_name) {
    vector<Company> companies;
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error opening file: " << file_name << endl;
        return companies;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;

        Company company;
        company.name = line.substr(0, pos1);
        company.profit_tax = line.substr(pos1 + 1, pos2 - pos1 - 1);
        company.address = line.substr(pos2 + 1);
        companies.push_back(company);
    }
    file.close();
    return companies;
}

// Hash function
long long hashString(string company_name) {
    const int p = 31;
    const int m = 2000;
    string s = company_name.length() > 20 ? company_name.substr(company_name.length() - 20) : company_name;

    long long hash = 0;
    long long power = 1;
    for (char c : s) {
        hash = (hash + (c * power) % m) % m;
        power = (power * p) % m;
    }
    return (hash + m) % m; // Ensure positive
}

// Create hash table
HashTable* createHashTable(vector<Company> list_company) {
    HashTable* hash_table = new HashTable(2000);
    for (const auto& company : list_company) {
        long long index = hashString(company.name);
        HashNode* new_node = new HashNode(company);
        new_node->next = hash_table->table[index];
        hash_table->table[index] = new_node;
    }
    return hash_table;
}

// Insert company into hash table
void insert(HashTable* hash_table, Company company) {
    long long index = hashString(company.name);
    HashNode* new_node = new HashNode(company);
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
}

// Search for company by name
Company* search(HashTable* hash_table, string company_name) {
    long long index = hashString(company_name);
    HashNode* current = hash_table->table[index];
    while (current) {
        if (current->company.name == company_name) {
            return &(current->company);
        }
        current = current->next;
    }
    return nullptr;
}

// Main function to process input and output
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " MST.txt input.txt output.txt" << endl;
        return 1;
    }

    string mst_file = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];

    // Read companies and create hash table
    vector<Company> companies = readCompanyList(mst_file);
    HashTable* hash_table = createHashTable(companies);

    // Read input queries
    ifstream input(input_file);
    ofstream output(output_file);
    string company_name;
    while (getline(input, company_name)) {
        Company* result = search(hash_table, company_name);
        if (result) {
            output << result->name << "|" << result->profit_tax << "|" << result->address << endl;
        } else {
            output << "Not found" << endl;
        }
    }

    input.close();
    output.close();
    delete hash_table;
    return 0;
}
