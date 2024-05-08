#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

#include "Encrypter.hpp"

class AccountManager {
    private:
        AccountManager();
        nlohmann::json json;
        const std::string key = "mpMaI+W9b+56uF90LNkvr7HKoli77nf3";
    public:
        static AccountManager& GetInstance();
        int signUp(const std::string& username, const std::string& password);
        int signIn(const std::string& username, const std::string& password);
};