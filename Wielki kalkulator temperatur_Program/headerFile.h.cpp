#include "StoreData.cpp"
#ifndef HEADERFILE_H
#define HEADERFILE_H
#define MAX_HISTORY 100


float FtoC(float f);
float FtoK(float f);
float CtoF(float c);
float CtoK(float c);
float KtoC(float k);
float KtoF(float k);
void add_data_to_history(float temperatureInput, float temperatureOutput, char unitInput, char unitOutput);
void show_main_menu();
void show_all_history();
void show_history_menu();
void show_history_by_input_unit(char unitInput);
void remove_data_from_history(int index);
void show_delete_menu();
void show_update_menu();
void add_random_data_to_history();
void update_data_in_history(int historyIndex, float temperatureInput, float temperatureOutput, char unitInput, char unitOutput);

#endif