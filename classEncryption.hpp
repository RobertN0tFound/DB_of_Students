#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <random>
#include <fstream>

class fileEnc
{
private:
    std::string pass;
    std::string generate_password()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 2);

        std::string password;
        for (int i = 0; i < 64; ++i) {
            switch (dis(gen)) {
                case 0:
                    password += static_cast<char>(std::uniform_int_distribution<>('0', '9')(gen));
                    break;
                case 1:
                    password += static_cast<char>(std::uniform_int_distribution<>('A', 'Z')(gen));
                    break;
                case 2:
                    password += static_cast<char>(std::uniform_int_distribution<>('a', 'z')(gen));
                    break;
            }
        }
        return password;
    }

public:
    void Crypt()
    {
        pass = generate_password();
        std::string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in database.txt -out database.txt.enc -pass pass:";
        command += pass;
        system(command.c_str());

        if (remove("database.txt") != 0) {
            std::cout << "[ERROR] - deleting file" << std::endl;
        }

        std::ofstream file;
        file.open("key.txt", std::ios::binary);
        file.write(pass.c_str(), 65);
        file.close();

        command = "openssl\\bin\\openssl.exe pkeyutl -encrypt -inkey rsa.public -pubin -in key.txt -out key.enc";
        system(command.c_str());
        if (remove("key.txt") != 0) {
            std::cout << "[ERROR] - deleting file" << std::endl;
        }
    }

    void Decrypt()
    {
        std::string command = "openssl\\bin\\openssl.exe pkeyutl -decrypt -inkey rsa.private -in key.enc -out key.txt";
        system(command.c_str());

        if (remove("key.enc") != 0) {
            std::cout << "[ERROR] - deleting file" << std::endl;
        }

        char* buffer = new char[64];
        std::ifstream file;
        file.open("key.txt", std::ios::binary);
        file.read(buffer, 65);
        pass = buffer;
        file.close();

        if (remove("key.txt") != 0) {
            std::cout << "[ERROR] - deleting file" << std::endl;
        }

        command = "openssl\\bin\\openssl.exe enc -d -aes-256-cbc -in database.txt.enc -out database.txt -pass pass:";
        command += pass;
        system(command.c_str());

        if (remove("database.enc") != 0) {
            std::cout << "[ERROR] - deleting file" << std::endl;
        }
    }
};