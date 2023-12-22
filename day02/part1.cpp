#include <iostream>
#include <fstream>
#include <string>

bool check_if_over_limit (const std::string& substring_game, int limit, const std::string& color);

int main (int argc, char* argv[]) {

    // open input file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // loop over lines in file
        int total = 0;
        std::string current_line;
        while (std::getline(input_file, current_line)) {

            // get game number of current_line
            int game_number_idx_start = current_line.find(" ") + 1;
            int game_number_idx_end = current_line.find(":");
            int game_number = stoi(current_line.substr(game_number_idx_start , game_number_idx_end - game_number_idx_start));

            // loop over games inside current_line
            bool all_subgames_work = true;
            std::string current_game;
            int starting_pos = game_number_idx_end + 2;
            while (current_line.find_first_of(";", starting_pos) != std::string::npos) {

                // sub game info
                std::string substring_game = current_line.substr(starting_pos, current_line.find_first_of(";", starting_pos) - starting_pos);
                
                // check game numbers are under allowed limits
                bool red_valid = check_if_over_limit(substring_game, 12, "red");
                bool green_valid = check_if_over_limit(substring_game, 13, "green");
                bool blue_valid = check_if_over_limit(substring_game, 14, "blue");

                // set bool to false so game will not be added to total
                if (red_valid == false || green_valid == false || blue_valid == false) {
                    all_subgames_work = false;
                }

                // update starting_pos and current_game
                starting_pos = current_line.find_first_of(";", starting_pos) + 2;
                current_game = current_line.substr(starting_pos);

            }

            // check game numbers are under allowed limits for last game
            bool red_valid = check_if_over_limit(current_game, 12, "red");
            bool green_valid = check_if_over_limit(current_game, 13, "green");
            bool blue_valid = check_if_over_limit(current_game, 14, "blue");

            // set bool to false so game will not be added to total for last game
            if (red_valid == false || green_valid == false || blue_valid == false) {
                all_subgames_work = false;
            }

            // add game to total if all subgames are valid
            if (all_subgames_work == true) {
                total += game_number;
            }

        }
        std::cout << "Total: " << total << std::endl;
    }
    input_file.close();
}

bool check_if_over_limit (const std::string& substring_game, int limit, const std::string& color) {

    bool is_not_over_limit = true;
    std::string current_substring_game = substring_game;
    int starting_pos = 0;
    while (substring_game.find_first_of(",", starting_pos) != std::string::npos) {

        // get number and color in game
        int delimeter_idx = substring_game.find_first_of(",", starting_pos);
        current_substring_game = substring_game.substr(starting_pos, delimeter_idx - starting_pos);

        // parse number and color
        int number = stoi(current_substring_game.substr(0, current_substring_game.find(" ")));
        std::string current_color = current_substring_game.substr(current_substring_game.find(" ") + 1);

        // if color matches and number is over limit set bool to false
        if (color == current_color && number > limit) {
            is_not_over_limit = false;
        } 

        starting_pos = delimeter_idx + 2;

    }

    // last game
    current_substring_game = substring_game.substr(starting_pos);
    int number = stoi(current_substring_game.substr(0, current_substring_game.find(" ")));
    std::string current_color = current_substring_game.substr(current_substring_game.find(" ") + 1);
    if (color == current_color && number > limit) {
        is_not_over_limit = false;
    } 

    return is_not_over_limit;
}
