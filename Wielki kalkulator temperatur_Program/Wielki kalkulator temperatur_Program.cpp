#include <stdio.h>
#include <stdlib.h>
#include "headerFile.h.cpp"
#include <cstring>

float temperatureData[MAX_HISTORY];
char temperatureUnits[MAX_HISTORY];
int datacounder = 0;

float FtoC(float F) {
    return (F - 32.0) * 5.0 / 9.0;
}
float FtoK(float F) {
    return (F + 459.67) * 5.0 / 9.0;
}
float CtoF(float C) {
    return C * 9.0 / 5.0 + 32.0;
}
float CtoK(float C) {
    return C + 273.15;
}
float KtoC(float K) {
    return K - 273.15;
}
float KtoF(float K) {
    return K * 9.0 / 5.0 - 459.67;
}

int check(float temp, char unit) {
    if ((unit == 'K' && temp < 0) || (unit == 'C' && temp < -273.15) || (unit == 'F' && temp < -459.67)) {
        return -999.0;
    }
    return 1;
}

void storeTemperaturs(float oryginalTemp, float przerobionyTemp, char oryginalUnit, char przerobionyUnit) {
    if (datacounder + 2 <= MAX_HISTORY) {
        temperatureData[datacounder] = oryginalTemp;
        temperatureUnits[datacounder] = oryginalUnit;
        datacounder++;
        temperatureData[datacounder] = przerobionyTemp;
        temperatureUnits[datacounder] = przerobionyUnit;
        datacounder++;
    }
    else {
        printf("Przekroczono limit historii!\n");
    }

}
struct Conversition {
    char type[10];
    double input;
    double output;
};
struct Conversition history[100];
int history_count = 0;

void add_to_history(const char* type, double input, double output) {
    if (history_count < 100) { // проверка, чтобы не выйти за пределы массива
        strcpy(history[history_count].type, type);
        history[history_count].input = input;
        history[history_count].output = output;
        history_count++;
    } else {
        printf("Historia jest pelna!");
    }

}


void pokazHistorie() {
    if (datacounder == 0) {
        printf("Brak zapisanej historii przeliczeń");
        return;
    }
    printf("Historia przeliczonych temperatur:\n");

    int pageSize = 5;
    int correntPage = 0;
    int totalPages = (datacounder / 2 + pageSize - 1) / pageSize;

    while (1) {
        system("cls");
        printf("Strona %d z %d\n", correntPage + 1, totalPages);

        for (int i = correntPage * pageSize * 2; i < (correntPage + 1)* pageSize * 2 && i < datacounder; i += 2){
            printf("<%d> %.2f%c = %.2f%c\n", (i / 2) + 1,
                temperatureData[i], temperatureUnits[i],
                temperatureData[i + 1], temperatureUnits[i + 1]);
        }
        printf("Wybierz opcje:\n");
        if (correntPage > 0)
            printf("1 - Poprzednia strona\n");
        if (correntPage < totalPages - 1)
            printf("2 - Nasttpna strona\n");
        printf("0 - Powrot do menu glownego\n");

        int choice = 0;
        if (scanf_s("%d", &choice) != 1) {
            printf("Nie prawidwowe dane wejsciowe.\n");
            while (getchar() != '\n');
            continue;
        } if (choice == 0) {
            break;
            } else if (choice == 1 && correntPage > 0) {
            correntPage--;
        } else if (choice == 2 && correntPage < totalPages - 1) {
            correntPage++;
        } else {
            printf("Nie prawidłowa opcja. Spróbuj ponownie.\n");
         }
    }

}

void showMenu() {
    printf("Wybierz opcję:\n");
    printf("1 - przelicz Fahr -> Celsius\n");
    printf("2 - przelicz Fahr -> Kelwin\n");
    printf("3 - przelicz Celsius -> Fahr\n");
    printf("4 - przelicz Celsius -> Kelwin\n");
    printf("5 - przelicz Kelwin -> Celsius\n");
    printf("6 - przelicz Kelwin -> Fahr\n");
    printf("7 - Pokaz historie przeliczen\n");
    printf("-1 - zalonc dzialania programu\n");
}

void showMessageNotSuchTemperature() {
    printf("Nie ma takiej temperatury.\n");
}

int main() {
    int choice;
    float temp;
    int valid;

    while (1) {
        system("cls");
        showMenu();
        printf("Wybór: ");

        if (scanf_s("%d", &choice) != 1) { 
            printf("Nieprawidłowe dane wejściowe. Proszę wpisać numer.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == -1) {
            printf("Zakończono działanie programu.\n");
            return 0;
        } 

        switch (choice) {
        case 1:
            printf("Podaj temperaturę w Fahrenheitach: ");
            if (scanf_s("%f", &temp) != 1) {
                printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
                while (getchar() != '\n');
                break;
            }
            valid = check(temp, 'F');
            if (valid == -999.0) {
                showMessageNotSuchTemperature();
            }
            else {
                float przerobiony = FtoC(temp);
                printf("Wynik: %.2f C\n", przerobiony);
                storeTemperaturs(temp, przerobiony, 'F', 'C');
            }
            break;
             
        case 2:
            printf("Podaj temperaturę w Fahrenheitach: ");
            if (scanf_s("%f", &temp) != 1) {
                printf("Nieprawidlowe dane wejściowe. Proszę wprowadzić prawidlowa temperature.\n");
                while (getchar() != '\n');
                break;
            }
            valid = check(temp, 'F');
            if (valid == -999.0) {
                showMessageNotSuchTemperature();
            }
            else {
                float przerobiony = FtoK(temp);
                printf("Wynik: %.2f K\n", przerobiony);
                storeTemperaturs(temp, przerobiony, 'F', 'K');
            } 
            break;

        case 3:
            printf("Podaj temperaturę w Celsiuszach: ");
            if (scanf_s("%f", &temp) != 1) {
                printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
                while (getchar() != '\n');
                break;
            }
            valid = check(temp, 'C');
            if (valid == -999.0) {
                showMessageNotSuchTemperature();
            }
            else {
                float przerobiony = CtoF(temp);
                printf("Wynik: %.2f F\n", CtoF(temp));
                storeTemperaturs(temp, przerobiony, 'C', 'F');
            }
            break;

        case 4:
            printf("Podaj temperaturę w Celsiuszach: ");
            if (scanf_s("%f", &temp) != 1) {
                printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
                while (getchar() != '\n');
                break;
            }
            valid = check(temp, 'C');
            if (valid == -999.0) {
                showMessageNotSuchTemperature();
            }
            else {
                float przerobiony = CtoK(temp);
                printf("Wynik: %.2f K\n", CtoK(temp));
                storeTemperaturs(temp, przerobiony, 'C', 'K');
            }
            break;

        case 5:
            printf("Podaj temperaturę w Kelvinach: ");
            if (scanf_s("%f", &temp) != 1) {
                printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
                while (getchar() != '\n');
                break;
            }
            valid = check(temp, 'K');
            if (valid == -999.0) {
                showMessageNotSuchTemperature();
            }
            else {
                float przerobiony = KtoC(temp);
                printf("Wynik: %.2f C\n", KtoC(temp));
                storeTemperaturs(temp, przerobiony, 'K', 'C');
            }
            break;

        case 6:
            printf("Podaj temperaturę w Kelvinach: ");
            if (scanf_s("%f", &temp) != 1) {
                printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
                while (getchar() != '\n');
                break;
            }
            valid = check(temp, 'K');
            if (valid == -999.0) {
                showMessageNotSuchTemperature();
            }
            else {
                float przerobiony = KtoF(temp);
                printf("Wynik: %.2f F\n", KtoF(temp));
                storeTemperaturs(temp, przerobiony, 'K', 'F');
            }
            break;
        case 7:
            pokazHistorie();
            break;

        default:
            printf("Nieprawidłowy wybór.\n");
            break;
        }

        printf("Naciśnij Enter, aby kontynować...\n");
        while (getchar() != '\n');
        getchar();
    }

    return 0;
}




