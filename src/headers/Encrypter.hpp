#pragma once

#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

class Encrypter {
    private:
        Encrypter();
    public:
        static Encrypter& GetInstance();
        std::string encrypt(const std::string& plaintext, const std::string& key, std::vector<CryptoPP::byte>& iv) const;
        std::string decrypt(const std::string& ciphertext, const std::string& key, const std::vector<CryptoPP::byte>& iv) const;
        std::string hash(const std::string& input) const;
};