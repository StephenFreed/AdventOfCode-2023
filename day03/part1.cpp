#include <iostream>
#include <fstream>
#include <vector>
#include <string>

  
std::vector<std::vector<char>> create_matrix_from_input() {
    std::vector<std::vector<char>> build_matrix;
    std::ifstream input_file;
    input_file.open("input_file");
    if (input_file.is_open()) {

        std::string current_line;
        while (std::getline(input_file, current_line)) {
            std::vector<char> build_matrix_vec;
            for (const char& c : current_line) {
                build_matrix_vec.push_back(c);
            }
            build_matrix.push_back(build_matrix_vec);
        }

    }
    input_file.close();
    return build_matrix;
}

bool check_number_is_valid(const int& line, const int& line_idx, std::vector<std::vector<char>> matrix) {
    // check if out of bounds
    if (line < 0 || line > matrix.size() - 1 || line_idx < 0 || line_idx > matrix[line].size() - 1) {
        return false;
    }
    
    // check not '.' and not digit
    char current_char = matrix[line][line_idx];
    if (current_char != '.' && !std::isdigit(current_char)) {
        return true;
    }

    return false;
}

int main (int argc , char* argv[]) {
    
    // create 2d array from input
    std::vector<std::vector<char>> matrix = create_matrix_from_input();

    // answer
    int total = 0;

    // loop over every line in 2d array
    for (int line = 0; line < matrix.size(); line++) {
        // loop over every char in line 
        for (int idx = 0; idx < matrix[line].size(); idx++) {

            // while loop when digit to create number index array
            std::vector<int> number_index_vec;
            while (idx < matrix[line].size() && std::isdigit(matrix[line][idx])) {
                number_index_vec.push_back(idx);
                idx++;
            } 

            // when there is a number
            if (number_index_vec.size() != 0) {

                // check if valid number
                bool is_valid_number = false;
                for (const int& line_idx : number_index_vec) {
                    // check left and right of number
                    if (check_number_is_valid(line, line_idx - 1, matrix) || check_number_is_valid(line, line_idx + 1, matrix)) {
                        is_valid_number = true;
                    }
                    // check top and bottom of number
                    for (int i = line_idx - 1; i <= line_idx + 1; i++) {
                        if (check_number_is_valid(line-1, i, matrix) || check_number_is_valid(line+1, i, matrix)) {
                            is_valid_number = true;
                        }
                    }
                    // if valid add to total
                    if (is_valid_number) {
                        std::string number_string;
                        for (const int& idx_of_number : number_index_vec) {
                            number_string.push_back(char(matrix[line][idx_of_number]));
                        }
                        total += std::stoi(number_string);
                        break;
                    }
                }
            }

        }
    }
    std::cout << "Total: " << total << std::endl;
}
