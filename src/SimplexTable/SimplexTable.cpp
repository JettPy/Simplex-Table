#include "SimplexTable.h"
#include <iostream>
#include <iomanip>
#include "../Fraction/Fraction.h"

SimplexTable::SimplexTable(int **coefficients, const char* signs, int *objective_function, int variables_count, int equations_count, bool is_maximize) {
    this->rows = 1 + equations_count + 2;
    this->columns = 1 + variables_count;
    this->is_maximize = is_maximize;
    this->is_first_stage = true;
    this->solution_possible = true;
    for (int i = 0; i < equations_count; ++i) {
        if (signs[i] == '=' || signs[i] == '<') {
            this->columns += 1;
        } else if (signs[i] == '>') {
            this->columns += 2;
        } else {
            throw std::invalid_argument("received invalid sign");
        }
    }
    this->answer_size = this->columns - 2;
    this->table = new std::string *[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->table[i] = new std::string [this->columns];
    }
    this->table[this->rows - 2][0] = "Z";
    this->table[this->rows - 1][0] = "G";
    this->table[0][this->columns - 1] = "b";
    for (int i = 1; i < this->columns - 1; ++i) {
        this->table[0][i] = "x" + std::to_string(i);
    }
    for (int i = 0; i < equations_count; ++i) {
        for (int j = 0; j < variables_count - 1; ++j) {
            this->table[i + 1][j + 1] = std::to_string(coefficients[i][j]);
            this->table[this->rows - 1][j + 1] = std::to_string(0);
        }
        this->table[i + 1][this->columns - 1] = std::to_string(coefficients[i][variables_count - 1]);
        this->table[this->rows - 1][this->columns - 1] = std::to_string(0);
    }
    for (int i = 0; i < variables_count - 1; ++i)
        this->table[equations_count + 1][i + 1] = std::to_string(-objective_function[i]);
    this->table[equations_count + 1][this->columns - 1] = std::to_string(-objective_function[variables_count - 1]);
    int k = 0;
    for (int i = 0; i < equations_count; ++i) {
        if(signs[i] == '>') {
            for (int j = 1; j < this->rows; ++j) {
                if (j == i + 1) {
                    this->table[j][i + variables_count + k] = std::to_string(-1);
                } else {
                    this->table[j][i + variables_count + k] = std::to_string(0);
                }
            }
            k++;
        }
        for (int j = 1; j < this->rows; ++j) {
            if (j == i + 1) {
                this->table[j][i + variables_count + k] = std::to_string(1);
            } else {
                this->table[j][i + variables_count + k] = std::to_string(0);
            }
        }
    }
    for (int i = 1; i < equations_count + 1; ++i) {
        for (int j = this->columns - 2; j != 0; --j) {
            if (stoi(this->table[i][j]) == 1) {
                this->table[i][0] = this->table[0][j];
                break;
            }
        }
    }
    for (int i = 0; i < equations_count; ++i) {
        for (int j = 1; j < this->columns; ++j) {
            if ((signs[i] == '=' || signs[i] == '>') && this->table[i + 1][0] != this->table[0][j]) {
                this->table[this->rows - 1][j] = std::to_string(stoi(this->table[this->rows - 1][j]) - stoi(this->table[i + 1][j]));
            }
        }
    }
}

void SimplexTable::deleteTable() {
    for (int i = 0; i < this->rows; ++i) {
        delete [] this->table[i];
    }
    delete [] this->table;
}

SimplexTable::~SimplexTable() {
    this->deleteTable();
}

void SimplexTable::print_table() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            std::cout << std::setw(8);
            std::cout << this->table[i][j];
        }
        std::cout << std::endl;
    }
}

int SimplexTable::find_column() {
    Fraction value(0, 1);
    int index = -1;
    for (int i = 1; i < this->columns - 1; ++i) {
        Fraction fraction(this->table[this->rows - 1][i]);
        if (fraction < value && (this->is_first_stage || this->is_maximize) ||
            fraction > value && !this->is_first_stage && !this->is_maximize) {
            value = fraction;
            index = i;
        }
    }
    return index;
}

int SimplexTable::find_row(int column) {
    Fraction value(-1, 1);
    int index = -1;
    for (int i = 1; i < this->rows - 1 - (int)this->is_first_stage; ++i) {
        Fraction b(this->table[i][columns - 1]);
        Fraction a(this->table[i][column]);
        if ((b >= 0 && a > 0 || b <= 0 && a < 0) && (b / a < value || value < 0)) {
            value = b / a;
            index = i;
        }
    }
    return index;
}

void SimplexTable::recalculate(int row, int column) {
    auto **new_table = new std::string *[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        if (this->is_first_stage) {
            new_table[i] = new std::string [this->columns - 1];
        } else {
            new_table[i] = new std::string [this->columns];
        }
        if (this->table[i][0] == this->table[row][0]) {
            new_table[i][0] = this->table[0][column];
        } else {
            new_table[i][0] = this->table[i][0];
        }
    }
    int k = 0;
    for (int i = 0; i < columns; ++i) {
        if (this->table[0][i] == this->table[row][0] && this->is_first_stage) {
            k++;
        } else {
            new_table[0][i - k] = this->table[0][i];
        }
    }
    for (int i = 1; i < this->rows; ++i) {
        k = 0;
        for (int j = 1; j < this->columns; ++j) {
            if (i == row && j == column) {
                new_table[i][j] = std::to_string(1);
            }
            else if (i != row && j == column) {
                new_table[i][j] = std::to_string(0);
            }
            else if (i == row && j != column) {
                if (this->table[0][j] == this->table[row][0] && this->is_first_stage) {
                    k++;
                } else {
                    Fraction a(this->table[i][j]);
                    Fraction b(this->table[row][column]);
                    new_table[i][j - k] = (a / b).to_string();
                }
            } else {
                if (this->table[0][j] == this->table[row][0] && this->is_first_stage) {
                    k++;
                } else {
                    Fraction a11(this->table[i][j]);
                    Fraction a12(this->table[row][j]);
                    Fraction a21(this->table[i][column]);
                    Fraction a22(this->table[row][column]);
                    new_table[i][j - k] = (a11 - a12 * a21 / a22).to_string();
                }
            }
        }
    }
    this->deleteTable();
    if (this->is_first_stage) {
        this->columns -= 1;
    }
    this->table = new_table;
}

void SimplexTable::iterate() {
    int element_column = this->find_column();
    if (element_column == -1) {
        this->solution_possible = false;
        return;
    }
    int element_row = this->find_row(element_column);
    if (element_row == -1) {
        this->solution_possible = false;
        return;
    }
    std::cout << "Element: " + this->table[element_row][element_column] + " (" << element_row << ", " << element_column << ")" << std::endl;
    this->recalculate(element_row, element_column);
}

bool SimplexTable::can_be_iterated() {
    if (!this->solution_possible) {
        return false;
    }
    bool is_end = false;
    for (int i = 1; i < this->columns - 1; ++i) {
        if (this->is_first_stage) {
            if (Fraction(this->table[this->rows - 1][i]) < 0) {
                return true;
            } else if (Fraction(this->table[this->rows - 1][i]) > 0) {
                is_end = true;
            }
        } else {
            Fraction z(this->table[this->rows - 1][i]);
            if (z < 0 && this->is_maximize || z > 0 && !this->is_maximize) {
                return true;
            } else if (z > 0 && this->is_maximize || z < 0 && !this->is_maximize) {
                is_end = true;
            }
        }
    }
    if (this->is_first_stage && Fraction(this->table[this->rows - 1][this->columns - 1]) == 0) {
        return false;
    }
    if (this->is_first_stage) {
        this->solution_possible = !is_end;
    }
    return false;
}

void SimplexTable::drop_artificial_objective_function() {
    if (!this->is_first_stage) {
        throw std::invalid_argument("artificial objective function is already dropped");
    }
    delete [] this->table[this->rows - 1];
    this->rows--;
    this->is_first_stage = false;
}

void SimplexTable::get_answer() {
    if (!this->solution_possible) {
        std::cout << "No solution" << std::endl;
        return;
    }
    int index = 1;
    int last_index = 1;
    std::cout << "X vector:" << std::endl;
    for (int i = 0; i < this->answer_size; ++i) {
        for (int j = 1; j < this->rows - 1; ++j) {
            if (table[j][0] == "x" + std::to_string(index)) {
                std::cout << std::setw(8);
                std::cout << this->table[j][this->columns - 1];
                index++;
                break;
            }
        }
        if(last_index == index) {
            std::cout << std::setw(8);
            std::cout << 0;
            index++;
        }
        last_index = index;
    }
    std::cout << std::endl;
    if (this->is_maximize) {
        std::cout << "Max Z: ";
    } else {
        std::cout << "Min Z: ";
    }
    std::cout << this->table[this->rows - 1][this->columns - 1] << std::endl;
}

bool SimplexTable::is_solution_possible() const {
    return this->solution_possible;
}