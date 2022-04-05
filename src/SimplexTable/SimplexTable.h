#ifndef TABLES_SIMPLEXTABLE_H
#define TABLES_SIMPLEXTABLE_H
#include <string>
#include "../Fraction/Fraction.h"


class SimplexTable {
private:
    Fraction **table;
    std::string *columns_caption;
    std::string *rows_caption;
    int rows;
    int columns;
    bool is_maximize;
    bool is_first_stage;
    int answer_size;
    bool solution_possible;

    void deleteTable(bool);
    int find_column();
    int find_row(int);
    void recalculate(int, int);

public:
    SimplexTable(int **, const char *, int *, int, int, bool);
    ~SimplexTable();
    void print_table();
    void iterate();
    bool can_be_iterated();
    void drop_artificial_objective_function();
    void get_answer();
    [[nodiscard]] bool is_solution_possible() const;
};


#endif //TABLES_SIMPLEXTABLE_H
