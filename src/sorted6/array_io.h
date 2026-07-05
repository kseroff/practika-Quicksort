#ifndef ARRAY_IO_H
#define ARRAY_IO_H

void print_arr(int arr[], int size, const char* message);
void create_manual_array();
void generate_random_array();
void create_identical_array();
void load_from_file();
void save_to_file();
void sort_current_array();
void clear_input();
int read_int(const char* prompt, int* value);

#endif