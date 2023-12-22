#include <iostream>
#include <fstream>
#include <string>


int main() {

    // answer
    int32_t total = 0;

    // parse input file
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        // iterate over lines in file
        std::string current_line;
        while (std::getline(input_file, current_line)) {

            std::string digits_in_string;
            // parse ints from line and create string of digits
            for (const char& c : current_line) {
                if (std::isdigit(c)) {
                    digits_in_string.push_back(c);
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
