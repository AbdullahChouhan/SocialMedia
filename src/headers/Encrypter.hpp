#pragma once

#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

class Encrypter {
    private:
        Encrypter();
    public:
        static Encrypter& GetInstance();
        std::string Encrypt(const std::string& plaintext, const std::string& key, std::vector<CryptoPP::byte>& iv) const;
        std::string Decrypt(const std::string& ciphertext, const std::string& key, const std::vector<CryptoPP::byte>& iv) const;
};