#include "SimplexTable.h"
#include <iostream>
#include <iomanip>

SimplexTable::SimplexTable(int **coefficients, const char* signs, int *objective_function,
                           int variables_count, int equations_count, bool is_maximize) {
    this->rows = equations_count + 2;
    this->columns = variables_count;
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
    this->columns_caption = new std::string [this->columns];
    this->rows_caption = new std::string [this->rows];
    this->answer_size = this->columns - 1;
    this->table = new Fraction *[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->table[i] = new Fraction [this->columns];
    }
    this->rows_caption[this->rows - 2] = "Z";
    this->rows_caption[this->rows - 1] = "G";
    this->columns_caption[this->columns - 1] = "b";
    for (int i = 0; i < this->columns - 1; ++i) {
        this->columns_caption[i] = "x" + std::to_string(i + 1);
    }
    for (int i = 0; i < equations_count; ++i) {
        for (int j = 0; j < variables_count - 1; ++j) {
            this->table[i][j] = Fraction(coefficients[i][j], 1);
            this->table[this->rows - 1][j] = Fraction();
        }
        this->table[i][this->columns - 1] = Fraction(coefficients[i][variables_count - 1], 1);
        this->table[this->rows - 1][this->columns - 1] = Fraction();
    }
    for (int i = 0; i < variables_count - 1; ++i)
        this->table[equations_count][i] = Fraction(-objective_function[i], 1);
    this->table[equations_count][this->columns - 1] = Fraction(-objective_function[variables_count - 1], 1);
    int k = 0;
    for (int i = 0; i < equations_count; ++i) {
        if(signs[i] == '>') {
            for (int j = 0; j < this->rows; ++j) {
                if (j == i) {
                    this->table[j][i + variables_count - 1 + k] = Fraction(-1, 1);
                } else {
                    this->table[j][i + variables_count - 1 + k] = Fraction();
                }
            }
            k++;
        }
        for (int j = 0; j < this->rows; ++j) {
            if (j == i) {
                this->table[j][i + variables_count - 1 + k] = Fraction(1, 1);
            } else {
                this->table[j][i + variables_count - 1 + k] = Fraction();
            }
        }
    }
    for (int i = 0; i < equations_count; ++i) {
        for (int j = this->columns - 2; j != 0; --j) {
            if (this->table[i][j] == 1) {
                this->rows_caption[i] = this->columns_caption[j];
                break;
            }
        }
    }
    for (int i = 0; i < equations_count; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if ((signs[i] == '=' || signs[i] == '>') && this->rows_caption[i] != this->columns_caption[j]) {
                this->table[this->rows - 1][j] = this->table[this->rows - 1][j] - this->table[i][j];
            }
        }
    }
}

void SimplexTable::deleteTable(bool is_saved) {
    for (int i = 0; i < this->rows; ++i) {
        delete [] this->table[i];
    }
    delete [] this->table;
    delete [] this->columns_caption;
    if (!is_saved) {
        delete [] this->rows_caption;
    }
}

SimplexTable::~SimplexTable() {
    this->deleteTable(false);
}

void SimplexTable::print_table() {
    for (int i = -1; i < this->columns; ++i) {
        if (i == -1) {
            std::cout << std::setw(8) << "";
        } else {
            std::cout << std::setw(8) << this->columns_caption[i];
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < this->rows; ++i) {
        std::cout << std::setw(8) << this->rows_caption[i];
        for (int j = 0; j < this->columns; ++j) {
            std::cout << std::setw(8) << this->table[i][j];
        }
        std::cout << std::endl;
    }
}

int SimplexTable::find_column() {
    Fraction value(0, 1);
    int index = -1;
    for (int i = 0; i < this->columns - 1; ++i) {
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
    for (int i = 0; i < this->rows - 1 - (int)this->is_first_stage; ++i) {
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
    auto **new_table = new Fraction *[this->rows];
    std::string *new_columns_caption;
    if (this->is_first_stage) {
        new_columns_caption = new std::string [this->columns - 1];
    } else {
        new_columns_caption = new std::string [this->columns];
    }
    for (int i = 0; i < this->rows; ++i) {
        if (this->is_first_stage) {
            new_table[i] = new Fraction [this->columns - 1];
        } else {
            new_table[i] = new Fraction [this->columns];
        }
    }
    int k = 0;
    for (int i = 0; i < columns; ++i) {
        if (this->columns_caption[i] == this->rows_caption[row] && this->is_first_stage) {
            k++;
        } else {
            new_columns_caption[i - k] = this->columns_caption[i];
        }
    }
    for (int i = 0; i < this->rows; ++i) {
        k = 0;
        for (int j = 0; j < this->columns; ++j) {
            if (i == row && j == column) {
                new_table[i][j] = Fraction(1, 1);
            }
            else if (i != row && j == column) {
                new_table[i][j] = Fraction();
            }
            else if (i == row && j != column) {
                if (this->columns_caption[j] == this->rows_caption[row] && this->is_first_stage) {
                    k++;
                } else {
                    Fraction a = this->table[i][j];
                    Fraction b = this->table[row][column];
                    new_table[i][j - k] = a / b;
                }
            } else {
                if (this->columns_caption[j] == this->rows_caption[row] && this->is_first_stage) {
                    k++;
                } else {
                    Fraction a11 = this->table[i][j];
                    Fraction a12 = this->table[row][j];
                    Fraction a21 = this->table[i][column];
                    Fraction a22 = this->table[row][column];
                    new_table[i][j - k] = a11 - a12 * a21 / a22;
                }
            }
        }
    }
    this->rows_caption[row] = this->columns_caption[column];
    this->deleteTable(true);
    if (this->is_first_stage) {
        this->columns -= 1;
    }
    this->table = new_table;
    this->columns_caption = new_columns_caption;
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
    std::cout << "Element: " << this->table[element_row][element_column] <<
        " (" << element_row + 1 << ", " << element_column + 1 << ")" << std::endl;
    this->recalculate(element_row, element_column);
}

bool SimplexTable::can_be_iterated() {
    if (!this->solution_possible) {
        return false;
    }
    bool is_end = false;
    for (int i = 0; i < this->columns - 1; ++i) {
        if (this->is_first_stage) {
            if (Fraction(this->table[this->rows - 1][i]) < 0) {
                return true;
            } else if (Fraction(this->table[this->rows - 1][i]) > 0) {
                is_end = true;
            }
        } else {
            Fraction z = this->table[this->rows - 1][i];
            if (z < 0 && this->is_maximize || z > 0 && !this->is_maximize) {
                return true;
            } else if (z > 0 && this->is_maximize || z < 0 && !this->is_maximize) {
                is_end = true;
            }
        }
    }
    if (this->is_first_stage && this->table[this->rows - 1][this->columns - 1] == 0) {
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
        for (int j = 0; j < this->rows - 1; ++j) {
            if (this->rows_caption[j] == "x" + std::to_string(index)) {
                std::cout << std::setw(8) << this->table[j][this->columns - 1];
                index++;
                break;
            }
        }
        if(last_index == index) {
            std::cout << std::setw(8) << 0;
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