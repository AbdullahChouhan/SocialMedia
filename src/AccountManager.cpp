#include "headers/AccountManager.hpp"

AccountManager::AccountManager() {
    std::ifstream file("../resources/accounts.json");
    if (file.is_open()) {
        nlohmann::json json = nlohmann::json::parse(file);
        for (auto& account : json["accounts"]) {
            accounts.emplace_back(account["username"]);
        }
    }
    file.close();
}

AccountManager& AccountManager::GetInstance() {
    static AccountManager instance;
    return instance;
}

int AccountManager::signUp(const std::string& username, const std::string& password) {
    //verify locally
    for (auto& account : accounts) {
        if (account == username) {
            return -2;
        }
    }
    //send to server
    if (false) //Server responded with account exists
        return -1;

    //Server saved and now save locally
    std::ofstream file("../resources/accounts.json");
    if (file.is_open()) {
        nlohmann::json json = nlohmann::json::parse(file);
        json["accounts"].push_back({{"username", username}});
        file << json.dump();
        file.close();
        return 1;
    }
    return 0;
}

int AccountManager::signIn(const std::string& username, const std::string& password) {
    //verify at server
    if (1) // Server responded with account exists
        return -2;
    if (1) // Server responded with wrong password
        return -1;
    if (true) {
        std::ifstream file("../resources/accounts.json");
        if (file.is_open()) {
            bool found;
            nlohmann::json json = nlohmann::json::parse(file);
            for (auto& account : json["accounts"]) {
                if (account["username"] == username) {
                    found = true;
                }
            }
            if (!found) {
                json["accounts"].push_back({{"username", username}});
                file.close();
                std::ofstream fileout("../resources/accounts.json");
                if (fileout.is_open())
                {
                    fileout << json.dump();
                    fileout.close();
                }
            }
        }
        file.close();
        return 1;
    }
    return 2;
}