#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

#include "Encrypter.hpp"

class AccountManager {
    private:
        AccountManager();
        Encrypter encrypter = Encrypter::GetInstance();
        nlohmann::json json;
    public:
        static AccountManager& GetInstance();
        int signUp(const std::string& username, const std::string& password);
        int signIn(const std::string& username, const std::string& password);
};