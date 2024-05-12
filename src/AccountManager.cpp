#include "headers/AccountManager.hpp"

AccountManager::AccountManager() {
    std::ifstream file("resources/accounts.json");
    if (file.is_open()) {
        json = nlohmann::json::parse(file);
        file.close();
    }
    else {
        std::cout << "Failed to open accounts.json\n";
    }
}

AccountManager& AccountManager::GetInstance() {
    static AccountManager instance;
    return instance;
}

int AccountManager::signUp(const std::string& username, const std::string& password) {
    //verify locally
    for (auto& account : json["accounts"]) {
        if (account["username"] == username) {
            return -2;
        }
    }
    // //send to server
    // if (false) //Server responded with account exists
    //     return -1;

    //Server saved and now save locally
    std::string hash = encrypter.hash(password);
    if (true) {
        std::ofstream file("resources/accounts.json");
        if (file.is_open()) {
            json["accounts"].push_back({{"username", username}, {"password", hash}});
            file << json.dump();
            file.close();
            return 1;
        }
        else {
            std::cout << "Failed to open accounts.json\n";
        }
    }
    return 0;
}

int AccountManager::signIn(const std::string& username, const std::string& password) {
    std::string hash = encrypter.hash(password);
    //verify at server
    // if (1) // Server responded with account exists
    //     return -2;
    // if (1) // Server responded with wrong password
    //     return -1;
    if (true) {
        for (auto& account : json["accounts"]) {
            if (account["username"] == username && account["password"] == hash) {
                return 1;
            }
        }
    }
    return 2;
}