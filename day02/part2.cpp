#include <iostream>
#include <fstream>
#include <string>

int check_value (const std::string& substring_game, const std::string& color);

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

            // high values for all games in line
            int red_highest = 0;
            int green_highest = 0;
            int blue_highest = 0;

            // loop over games inside current_line
            std::string current_game;
            int starting_pos = game_number_idx_end + 2;
            while (current_line.find_first_of(";", starting_pos) != std::string::npos) {

                // sub game info
                std::string substring_game = current_line.substr(starting_pos, current_line.find_first_of(";", starting_pos) - starting_pos);
                
                // get high value for current game in line and update if higher
                int red_value = check_value(substring_game, "red");
                if (red_value > red_highest) red_highest = red_value;
                int green_value = check_value(substring_game, "green");
                if (green_value > green_highest) green_highest = green_value;
                int blue_value = check_value(substring_game, "blue");
                if (blue_value > blue_highest) blue_highest = blue_value;

                // update starting_pos and current_game
                starting_pos = current_line.find_first_of(";", starting_pos) + 2;
                current_game = current_line.substr(starting_pos);

            }
            // get high value for current game in line and update if higher for last game
            int red_value = check_value(current_game, "red");
            if (red_value > red_highest) red_highest = red_value;
            int green_value = check_value(current_game, "green");
            if (green_value > green_highest) green_highest = green_value;
            int blue_value = check_value(current_game, "blue");
            if (blue_value > blue_highest) blue_highest = blue_value;

            // get power of highest for all games in line and add to total
            int power_of_line = red_highest * green_highest * blue_highest;
            total += power_of_line;

        }
        // print answer
        std::cout << "Total: " << total << std::endl;
    }
    input_file.close();
}

int check_value (const std::string& substring_game, const std::string& color) {
     
    // high sum for color in game
    int highest_num = 0;

    // loop over cubes in game to get highest of that color
    std::string current_substring_game = substring_game;
    int starting_pos = 0;
    while (substring_game.find_first_of(",", starting_pos) != std::string::npos) {

        // number and color in game
        int delimeter_idx = substring_game.find_first_of(",", starting_pos);
        current_substring_game = substring_game.substr(starting_pos, delimeter_idx - starting_pos);

        // parse number and color
        int number = stoi(current_substring_game.substr(0, current_substring_game.find(" ")));
        std::string current_color = current_substring_game.substr(current_substring_game.find(" ") + 1);

        // set highest number of that color
        if (number > highest_num && color == current_color) highest_num = number;

        starting_pos = delimeter_idx + 2;

    }
    // last substring game
    current_substring_game = substring_game.substr(starting_pos);

    // parse number and color
    int number = stoi(current_substring_game.substr(0, current_substring_game.find(" ")));
    std::string current_color = current_substring_game.substr(current_substring_game.find(" ") + 1);

    // set highest number of that color
    if (number > highest_num && color == current_color) highest_num = number;

    return highest_num;
}
