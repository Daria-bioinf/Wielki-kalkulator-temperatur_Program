#ifndef HEADERFILE_H
#define HEADERFILE_H
#define MAX_HISTORY 100

extern float temperatureData[MAX_HISTORY];
extern char temperatureUnits[MAX_HISTORY];
extern int HistoryCounter;

void showMenu();
float FtoC(float F);
float FtoK(float F);
float CtoF(float C);
float CtoK(float C);
float KtoC(float K);
float KtoF(float K);
int check(float temp, char unit);
void storeTemperaturs(float oryginalTemp, float przerobionyTemp, char oryginalUnit, char przerobionyUnit);
void pokazHistorie();

#endif