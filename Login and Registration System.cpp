#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>   //librarries

class UserSystem {
private:
    std::string username;
    std::string password;
    const std::string DATABASE_DIR = "user_database/";  // for database

public:
    void registerUser() {
        std::cout << "=== User Registration ===\n";
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (createUserFile()) {
            std::cout << "Registration successful!\n";
        } else {
            std::cout << "Registration failed. Username may already exist.\n";
        }
    }

    bool loginUser() {
        std::cout << "=== User Login ===\n";
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        return verifyCredentials();
    }

private:
    bool createUserFile() {
        _mkdir(DATABASE_DIR.c_str()); // Create directory if it doesn't exist
        std::string filename = DATABASE_DIR + username + ".txt";

        std::ifstream checkFile(filename.c_str());
        if (checkFile.good()) {
            checkFile.close();
            return false; // File already exists
        }

        std::ofstream file(filename.c_str());
        if (file.is_open()) {
            file << password;
            file.close();
            return true;
        }
        return false;
    }

    bool verifyCredentials() {
        std::string filename = DATABASE_DIR + username + ".txt";
        std::ifstream file(filename.c_str());

        if (file.is_open()) {
            std::string storedPassword;
            std::getline(file, storedPassword);
            file.close();
            return (password == storedPassword);
        }
        return false;
    }
};

int main() {
    UserSystem system;
    int choice;

    do {
        std::cout << "\n1. Register\n2. Login\n3. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.registerUser();
                break;
            case 2:
                if (system.loginUser()) {
                    std::cout << "Login successful!\n";
                } else {
                    std::cout << "Login failed. Invalid credentials.\n";
                }
                break;
            case 3:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}