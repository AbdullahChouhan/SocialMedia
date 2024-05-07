#include "headers/Encrypter.hpp"

Encrypter::Encrypter() {}

Encrypter& Encrypter::GetInstance() {
    static Encrypter instance;
    return instance;
}

std::string Encrypter::encrypt(const std::string& plaintext, const std::string& key, std::vector<CryptoPP::byte>& iv) const {
    std::string ciphertext;

    if (iv.size() != 16 || iv.empty()) {
        if (iv.size() != 16)
            iv.resize(16);
        CryptoPP::AutoSeededRandomPool prng;
        prng.GenerateBlock(iv.data(), iv.size());
    }
    
    try {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption((CryptoPP::byte*)key.c_str(), 32, (CryptoPP::byte*)iv.data());
        CryptoPP::StringSource(plaintext, true,
            new CryptoPP::StreamTransformationFilter(encryption,
                new CryptoPP::StringSink(ciphertext)
            )
        );
    } catch(const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return ciphertext;
}

std::string Encrypter::decrypt(const std::string& ciphertext, const std::string& key, const std::vector<CryptoPP::byte>& iv) const {
    std::string decryptedText;

    try {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption((CryptoPP::byte*)key.c_str(), 32, (CryptoPP::byte*)iv.data());
        CryptoPP::StringSource(ciphertext, true,
            new CryptoPP::StreamTransformationFilter(decryption,
                new CryptoPP::StringSink(decryptedText)
            )
        );
    } catch(const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return decryptedText;
}

std::string Encrypter::hash(const std::string& input) const {
    std::string hash;

    try {
        CryptoPP::SHA256 sha;
        CryptoPP::StringSource(input, true,
            new CryptoPP::HashFilter(sha,
                new CryptoPP::HexEncoder(
                    new CryptoPP::StringSink(hash)
                )
            )
        );
    } catch(const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return hash;
}