#include "StoreData.cpp"
#ifndef HEADERFILE_H
#define HEADERFILE_H
#define MAX_HISTORY 100


void showMenu();
float FtoC(float F);
float FtoK(float F);
float CtoF(float C);
float CtoK(float C);
float KtoC(float K);
float KtoF(float K);
int check(float temp, char unit);
void show_message_not_such_temperature();
void show_main_menu();
void show_all_history();
void show_history_menu();
void show_history_by_input_unit(char unitInput);
StoreData remove_data_from_history(int index);
void show_delete_menu();
void show_update_menu();
void add_random_data_to_history();

#endif