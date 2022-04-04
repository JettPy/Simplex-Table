#include <iostream>
#include <vector>
#include "SimplexTable/SimplexTable.h"

void get_integer(int& num) {
    std::string buffer;
    while (true) {
        std::cout << "Enter number of variables:" << std::endl;
        std::getline(std::cin, buffer);
        try {
            if (stoi(buffer) < 1) {
                std::cout << "Cannot enter a number less than one." << std::endl;
            } else {
                num = stoi(buffer);
                break;
            }
        } catch (std::invalid_argument&) {
            std::cout << "Enter number." << std::endl;
        }
    }
}

void parse_string(std::vector<std::string>& enter, const std::string& str) {
    std::string separator(" ");
    size_t prev = 0;
    size_t next;
    size_t delta = separator.length();
    while((next = str.find(separator, prev)) != std::string::npos ){
        enter.push_back(str.substr( prev, next-prev ) );
        prev = next + delta;
    }
    enter.push_back(str.substr(prev));
}

void get_equation(int** coefficients, char* signs, int variables_count, int pos) {
    std::string buffer;
    enter_line:
    std::cout << "Enter " << variables_count - 1 << " coefficients and equality sign for the equation " << pos + 1
              << " (x1+x2=b):" << std::endl;
    std::getline(std::cin, buffer);
    std::vector<std::string> enter;
    parse_string(enter, buffer);
    if (enter.size() < variables_count + 1) {
        std::cout << "Too few arguments. Try again." << std::endl;
        goto enter_line;
    }
    if (enter.size() > variables_count + 1) {
        std::cout << "Too many arguments. Try again." << std::endl;
        goto enter_line;
    }
    for (int i = 0; i < variables_count - 1; ++i) {
        try {
            coefficients[pos][i] = stoi(enter[i]);
        } catch (std::invalid_argument&) {
            std::cout << "Invalid enter, try again. Use numbers for coefficients." << std::endl;
            goto enter_line;
        }
    }
    if (enter[variables_count - 1] != ">" &&
        enter[variables_count - 1] != "<" &&
        enter[variables_count - 1] != "=") {
        std::cout << "Invalid enter, try again. Use one sign(=, >, <)." << std::endl;
        goto enter_line;
    }
    signs[pos] = enter[variables_count - 1][0];
    try {
        coefficients[pos][variables_count - 1] = stoi(enter[variables_count]);
    } catch (std::invalid_argument&) {
        std::cout << "Invalid enter, try again. Use numbers for coefficients." << std::endl;
        goto enter_line;
    }
}

void get_objective_function(int* objective_function, int variables_count) {
    std::string buffer;
    function:
    std::cout << "Enter function coefficients and free term (x1+x2+b=0):" << std::endl;
    std::getline(std::cin, buffer);
    std::vector<std::string> enter;
    parse_string(enter, buffer);
    if (enter.size() < variables_count) {
        std::cout << "Too few arguments. Try again." << std::endl;
        goto function;
    }
    if (enter.size() > variables_count) {
        std::cout << "Too many arguments. Try again." << std::endl;
        goto function;
    }
    for (int i = 0; i < variables_count; ++i) {
        try {
            objective_function[i] = stoi(enter[i]);
        } catch (std::invalid_argument&) {
            std::cout << "Invalid enter, try again. Use numbers for coefficients." << std::endl;
            goto function;
        }
    }
}

bool get_task() {
    char choice;
    while (true) {
        std::cout << "Maximize? (y/n):" << std::endl;
        std::cin >> choice;
        if (choice == 'y') {
            return true;
        } else if (choice == 'n') {
            return false;
        } else {
            std::cout << R"(Only "y" or "n" allowed.)" << std::endl;
        }
    }
}

void check_equations(int **coefficients, char* signs, int variables_count, int equations_count) {
    for (int i = 0; i < equations_count; ++i) {
        if (coefficients[i][variables_count - 1] < 0) {
            for (int j = 0; j < variables_count; ++j) {
                coefficients[i][j] = -coefficients[i][j];
            }
            if (signs[i] == '>') {
                signs[i] = '<';
            } else if (signs[i] == '<') {
                signs[i] = '>';
            }
        }
    }
}

void print_left_part(int* coefficients, int variables_count) {
    for (int i = 0; i < variables_count; ++i) {
        if (i == 0 || coefficients[i] < 0) {
            if (coefficients[i] == -1) {
                std::cout << "-" << "x" + std::to_string(i + 1);
            } else if (coefficients[i] == 1) {
                std::cout << "x" + std::to_string(i + 1);
            } else {
                std::cout << coefficients[i] << "x" + std::to_string(i + 1);
            }
        } else {
            if (coefficients[i] == 1) {
                std::cout << "+" << "x" + std::to_string(i + 1);
            } else {
                std::cout << "+" << coefficients[i] << "x" + std::to_string(i + 1);
            }
        }
    }
}

void print_enter(int **coefficients, const char* signs, int *objective_function, int variables_count, int equations_count, bool is_maximize) {
    std::cout << "Entered:" << std::endl;
    for (int i = 0; i < equations_count; ++i) {
        print_left_part(coefficients[i], variables_count - 1);
        std::cout << signs[i] << coefficients[i][variables_count - 1] << std::endl;
    }
    std::cout << "Z(x)=";
    print_left_part(objective_function, variables_count - 1);
    if (objective_function[variables_count - 1] < 0) {
        std::cout << objective_function[variables_count - 1];
    } else {
        std::cout << "+" << objective_function[variables_count - 1];
    }
    if (is_maximize) {
        std::cout << " -> max" << std::endl;
    } else {
        std::cout << " -> min" << std::endl;
    }
}

int main() {
    int variables_count;
    get_integer(variables_count);
    variables_count++;
    int equations_count;
    get_integer(equations_count);
    auto *signs = new char[equations_count];
    auto **coefficients = new int *[equations_count];
    auto *z = new int[equations_count];
    for (int i = 0; i < equations_count; ++i) {
        coefficients[i] = new int[variables_count];
    }
    for (int i = 0; i < equations_count; ++i) {
        get_equation(coefficients, signs, variables_count, i);
    }
    get_objective_function(z, variables_count);
    bool is_maximize = get_task();
    print_enter(coefficients, signs, z, variables_count, equations_count, is_maximize);
    check_equations(coefficients, signs, variables_count, equations_count);
    SimplexTable table(coefficients, signs, z, variables_count, equations_count, is_maximize);
    delete [] signs;
    delete [] z;
    for (int i = 0; i < equations_count; ++i) {
        delete [] coefficients[i];
    }
    delete [] coefficients;
    std::cout << "Initial:" << std::endl;
    table.print_table();
    int count = 1;
    while (table.can_be_iterated()) {
        table.iterate();
        if (!table.is_solution_possible()) {
            break;
        }
        std::cout << "Step " << count << ":" << std::endl;
        table.print_table();
        count++;
    }
    if (table.is_solution_possible()) {
        table.drop_artificial_objective_function();
        std::cout << "Drop G:" << std::endl;
        table.print_table();
    }
    while (table.can_be_iterated()) {
        std::cout << "Step " << count << ":" << std::endl;
        table.iterate();
        table.print_table();
        count++;
    }
    table.get_answer();
    return 0;
}