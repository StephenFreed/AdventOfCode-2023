#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>


int main(int argc, char* argv[]) {

    // answer
    int all_cards_total = 0;

    // get input file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // loop over very line in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {

            // substrings of winning and my numbers
            int colon_idx = current_line.find(":");
            int pipe_idx = current_line.find("|");
            std::string winning_numbers_str = current_line.substr(colon_idx + 2, (pipe_idx - colon_idx) - 2);
            std::string my_numbers_str = current_line.substr(pipe_idx + 2);

            // clear first space for single digit numbers
            if (winning_numbers_str.find(' ') == 0) {
                winning_numbers_str = winning_numbers_str.substr(1);
            }
            if (my_numbers_str.find(' ') == 0) {
                my_numbers_str = my_numbers_str.substr(1);
            }

            // create set of winning numbers
            std::unordered_set<int> winning_numbers_set;
            int winning_current_pos = 0;
            while (winning_numbers_str.find_first_of(' ', winning_current_pos) != std::string::npos) {
                int current_space_idx = winning_numbers_str.find(' ', winning_current_pos);
                std::string current_number = winning_numbers_str.substr(winning_current_pos, current_space_idx - winning_current_pos);
                winning_numbers_set.insert(std::stoi(current_number));
                winning_current_pos = winning_numbers_str.find_first_not_of(' ', current_space_idx);
            }

            // create vector of my numbers
            std::vector<int> my_numbers_vec;
            int my_current_pos = 0;
            while (my_numbers_str.find_first_of(' ', my_current_pos) != std::string::npos) {
                int current_space_idx = my_numbers_str.find(' ', my_current_pos);
                std::string current_number = my_numbers_str.substr(my_current_pos, current_space_idx - my_current_pos);
                my_numbers_vec.push_back(std::stoi(current_number));
                my_current_pos = my_numbers_str.find_first_not_of(' ', current_space_idx);
            }
            // last number
            std::string current_number = my_numbers_str.substr(my_current_pos);
            my_numbers_vec.push_back(std::stoi(current_number));

            // loop over to get matching and add total for card
            bool first_match = true;
            int card_total = 0;
            for (const int& my_number : my_numbers_vec) {
                if (winning_numbers_set.count(my_number) > 0) {
                    if (first_match == true) {
                        card_total = 1;
                        first_match = false;
                        continue;
                    }
                    card_total = card_total * 2;
                }
            }
            all_cards_total += card_total;
        }
    }
    input_file.close();
    std::cout << "Total: " << all_cards_total << std::endl;
}
