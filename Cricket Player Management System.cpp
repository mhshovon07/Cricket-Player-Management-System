#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Player {
public:
    std::string name;
    int age;

    Player(const std::string& playerName, int playerAge) : name(playerName), age(playerAge) {}
};

class CricketTeam {
private:
    std::vector<Player> players;

public:
    void addPlayer(const Player& player) {
        players.push_back(player);
        std::cout << "Player added successfully." << std::endl;
    }

    void removePlayer(int index) {
        if (index >= 0 && index < players.size()) {
            players.erase(players.begin() + index);
            std::cout << "Player removed successfully." << std::endl;
        } else {
            std::cout << "Invalid player index." << std::endl;
        }
    }

    void displayPlayers() {
        std::cout << "Players in the team:" << std::endl;
        for (size_t i = 0; i < players.size(); ++i) {
            std::cout << i << ". " << players[i].name << " (Age: " << players[i].age << ")" << std::endl;
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const Player& player : players) {
                file << player.name << " " << player.age << "\n";
            }
            file.close();
            std::cout << "Player data saved to " << filename << "." << std::endl;
        } else {
            std::cout << "Unable to open file for saving." << std::endl;
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            players.clear();
            std::string playerName;
            int playerAge;
            while (file >> playerName >> playerAge) {
                Player player(playerName, playerAge);
                players.push_back(player);
            }
            file.close();
            std::cout << "Player data loaded from " << filename << "." << std::endl;
        } else {
            std::cout << "Unable to open file for loading." << std::endl;
        }
    }

    int getPlayersCount() const {
        return players.size();
    }

    void editPlayerDetails(int index, const std::string& newName, int newAge) {
        if (index >= 0 && index < players.size()) {
            players[index].name = newName;
            players[index].age = newAge;
            std::cout << "Player details updated successfully." << std::endl;
        } else {
            std::cout << "Invalid player index." << std::endl;
        }
    }
};

bool login(const std::string& username, const std::string& password) {
    // You can customize this function to match your login requirements.
    // For simplicity, we use hardcoded values here.
    return (username == "admin" && password == "password");
}

int main() {
    std::string username, password;

    while (true) {
        std::cout << "Enter Username: ";
        std::cin >> username;
        std::cout << "Enter Password: ";
        std::cin >> password;

        if (login(username, password)) {
            std::cout << "Login successful. Access granted." << std::endl;
            break;  // Exit the login loop if login is successful
        } else {
            std::cout << "Login failed. Please try again." << std::endl;
        }
    }

    CricketTeam team;

    // Load player data from a file (if it exists)
    team.loadFromFile("player_data.txt");

    while (true) {
        std::cout << "1. Add Player" << std::endl;
        std::cout << "2. Remove Player" << std::endl;
        std::cout << "3. Edit Player Details" << std::endl;
        std::cout << "4. Display Players" << std::endl;
        std::cout << "5. Save Players to File" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name;
                int age;
                std::cout << "Enter player name: ";
                std::cin >> name;
                std::cout << "Enter player age: ";
                std::cin >> age;
                Player newPlayer(name, age);
                team.addPlayer(newPlayer);
                break;
            }
            case 2: {
                int index;
                std::cout << "Enter index of player to remove: ";
                std::cin >> index;
                team.removePlayer(index);
                break;
            }
            case 3: {
                int index;
                std::cout << "Enter index of player to edit: ";
                std::cin >> index;
                if (index >= 0 && index < team.getPlayersCount()) {
                    std::string name;
                    int age;
                    std::cout << "Enter updated player name: ";
                    std::cin >> name;
                    std::cout << "Enter updated player age: ";
                    std::cin >> age;
                    team.editPlayerDetails(index, name, age);
                } else {
                    std::cout << "Invalid player index." << std::endl;
                }
                break;
            }
            case 4:
                team.displayPlayers();
                break;
            case 5:
                team.saveToFile("player_data.txt");
                break;
            case 6:
                std::cout << "Exiting program." << std::endl;
                // Save player data to a file before exiting
                team.saveToFile("player_data.txt");
                return 0;
            default:
                std::cout << "Invalid choice. Please select a valid option." << std::endl;
        }
    }

    return 0;
}
