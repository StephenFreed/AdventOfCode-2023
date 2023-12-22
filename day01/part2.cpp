#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


int main() {

    // answer
    int32_t total = 0;

    std::unordered_map<std::string, std::string> number_map {
        {"zero", "0"},
        {"one", "1"},
        {"two", "2"},
        {"three", "3"},
        {"four", "4"},
        {"five", "5"},
        {"six", "6"},
        {"seven", "7"},
        {"eight", "8"},
        {"nine", "9"},
    }; 

    // parse input file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // iterate over lines in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {

            // parse ints from line and create string of digits
            std::string digits_in_string;
            for (int i = 0; i < current_line.length(); i++) {

                // add int
                if (std::isdigit(current_line.at(i))) {
                    digits_in_string.push_back(current_line.at(i));
                    continue;
                }

                // add int from word
                std::string current_line_substr = current_line.substr(0,i+1);
                for (const auto& map : number_map) {
                    if (map.first.length() <= i + 1) {
                         std::string end_substr_size_of_key = current_line_substr.substr(current_line_substr.length() - map.first.length());
                         if (map.first == end_substr_size_of_key ) {
                             digits_in_string.append(map.second);
                         }
                    }
                }
            }

            // create string of first and last digit
            std::string first_and_last_digit_string;
            first_and_last_digit_string.push_back(digits_in_string[0]);
            first_and_last_digit_string.push_back(digits_in_string[digits_in_string.length() - 1]);
            total += std::stoi(first_and_last_digit_string);
        }

    }
    input_file.close();
    std::cout << "Total: " << total << std::endl;
}
