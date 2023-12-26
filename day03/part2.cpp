#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

  
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


int get_current_number(const int& line, const std::vector<int>& number_index_vec, const std::vector<std::vector<char>>& matrix) {
    std::string number_string;
    for (const int& idx_of_number : number_index_vec) {
        number_string.push_back(char(matrix[line][idx_of_number]));
    }
    return std::stoi(number_string);
}


int make_gear_key(const int& line, const int& line_idx) {
    std::string gear_string = {""};
    gear_string += std::to_string(line);
    gear_string += std::to_string(line_idx);
    return std::stoi(gear_string);
}


bool check_for_gear(const int& line, const int& line_idx, const std::vector<std::vector<char>>& matrix) {
    // check if out of bounds
    if (line < 0 || line > matrix.size() - 1 || line_idx < 0 || line_idx > matrix[line].size() - 1) {
        return false;
    }
    
    // check is '*'
    char current_char = matrix[line][line_idx];
    if (current_char == '*') {
        return true;
    }

    return false;
}

void add_to_gear_map(const int gear_key, const int current_number, std::unordered_map<int,std::unordered_set<int>>& gear_map) {
    if (gear_map.count(gear_key) == 0) {
        gear_map[gear_key] = {current_number};
    } else {
        auto temp = gear_map[gear_key];
        temp.insert(current_number);
        gear_map[gear_key] = temp;
    }
}

int main (int argc , char* argv[]) {
    
    // create 2d array from input
    std::vector<std::vector<char>> matrix = create_matrix_from_input();

    // answer
    int total = 0;

    // map of numbers connected to gear
    std::unordered_map<int,std::unordered_set<int>> gear_map;

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

                // number as int
                int current_number = get_current_number(line, number_index_vec, matrix);

                // check for gear on each index of number and build gear_map
                // add key(<line><line_idx>) and value set of numbers touching gear
                for (const int& line_idx : number_index_vec) {

                    // check left
                    if (check_for_gear(line, line_idx - 1, matrix)) {
                        int gear_key = make_gear_key(line, line_idx - 1);
                        add_to_gear_map(gear_key, current_number, gear_map);
                    }

                    // check right
                    if (check_for_gear(line, line_idx + 1, matrix)) {
                        int gear_key = make_gear_key(line, line_idx + 1);
                        add_to_gear_map(gear_key, current_number, gear_map);
                    }

                    // check top and bottom of number
                    for (int i = line_idx - 1; i <= line_idx + 1; i++) {
                        // check top
                        if (check_for_gear(line - 1, i, matrix)) {
                            int gear_key_top = make_gear_key(line - 1, i);
                            add_to_gear_map(gear_key_top, current_number, gear_map);
                        }
                        // check bottom
                        if (check_for_gear(line + 1, i, matrix)) {
                            int gear_key_bottom = make_gear_key(line + 1, i);
                            add_to_gear_map(gear_key_bottom, current_number, gear_map);
                        }
                    }

                }

            }

        }
    }

    // loop over map to find values with 2 number 
    for (const auto& [key, value] : gear_map) {
        if (value.size() == 2) {
            std::vector<int> temp;
            temp.insert(temp.end(), value.begin(), value.end());
            // get ratio value
            int ratio_value = temp[0] * temp[1];
            // add ratio_value to total
            total += ratio_value;
        }
    }

    std::cout << "Total: " << total << std::endl;
}
