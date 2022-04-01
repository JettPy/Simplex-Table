#include <iostream>
#include "SimplexTable.h"

void exit_push() {
    std::cout << "Press any button to close." << std::endl;
    getchar();
    getchar();
}

int main() {
    int variables_count;
    while (true) {
        std::cout << "Enter number of variables:" << std::endl;
        std::cin >> variables_count;
        if (variables_count < 1) {
            std::cout << "Cannot enter a number less than one." << std::endl;
        } else {
            break;
        }
    }
    variables_count++;
    int equations_count;
    while (true) {
        std::cout << "Enter number of equations:" << std::endl;
        std::cin >> equations_count;
        if (equations_count < 1) {
            std::cout << "Cannot enter a number less than one." << std::endl;
        } else {
            break;
        }
    }
    auto *signs = new char[equations_count];
    auto **coefficients = new int *[equations_count];
    auto *z = new int[equations_count];
    for (int i = 0; i < equations_count; ++i) {
        coefficients[i] = new int[variables_count];
    }
    int equation = 0;
    enter:
    for (int i = equation; i < equations_count; ++i) {
        std::cout << "Enter " << variables_count - 1 << " coefficients and equality sign for the equation " << i + 1
                  << " (x1+x2=b):" << std::endl;
        for (int j = 0; j < variables_count - 1; ++j) {
            std::cin >> coefficients[i][j];
        }
        std::cin >> signs[i];
        if (signs[i] != '>' && signs[i] != '<' && signs[i] != '=') {
            std::cout << "Invalid enter, try again. Use numbers for coefficients and one sign(=, >, <)." << std::endl;
            std::cin.clear();
            goto enter;
        }
        std::cin >> coefficients[i][variables_count - 1];
        if(!std::cin) {
            std::cout << "Invalid enter, try again. Use numbers for coefficients and one sign(=, >, <)." << std::endl;
            std::cin.clear();
            goto enter;
        }
        equation++;
    }
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
    function:
    std::cout << "Enter function coefficients and free term (x1+x2+b=0):" << std::endl;
    for (int i = 0; i < variables_count; ++i) {
        std::cin >> z[i];
        if(!std::cin) {
            std::cout << "Invalid enter, try again. Use numbers for coefficients." << std::endl;
            std::cin.clear();
            goto function;
        }
    }
    char choice;
    bool is_maximize;
    while (true) {
        std::cout << "Maximize? (y/n):" << std::endl;
        std::cin >> choice;
        if (choice == 'y') {
            is_maximize = true;
            break;
        } else if (choice == 'n') {
            is_maximize = false;
            break;
        } else {
            std::cout << R"(Only "y" or "n" allowed.)" << std::endl;
        }
    }
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
    if (!table.is_solution_possible()) {
        table.get_answer();
        exit_push();
        return 0;
    }
    table.drop_artificial_objective_function();
    std::cout << "Drop G:" << std::endl;
    table.print_table();
    while (table.can_be_iterated()) {
        std::cout << "Step " << count << ":" << std::endl;
        table.iterate();
        table.print_table();
        count++;
    }
    table.get_answer();
    exit_push();
    return 0;
}