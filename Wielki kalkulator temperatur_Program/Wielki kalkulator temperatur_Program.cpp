#include <cstdio>

#include "HeaderFile.h.cpp"
#include <stdlib.h>

using namespace std;

StoreData history[MAX_HISTORY];
int dataCounter = 0;

char Inits[] = { 'C', 'F', 'K' };

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

void show_message_not_such_temperature() {
    printf("Nie ma takiej temperatury.\n");
}

int check(float temp, char unit) {
    if ((unit == 'K' && temp < 0) || (unit == 'C' && temp < -273.15) || (unit == 'F' && temp < -459.67)) {
        return 0;
    }
    return 1;
}

void add_data_to_history(float temperatureInput, float temperatureOutput, char unitInput, char unitOutput) {

    if (dataCounter == MAX_HISTORY)
    {
        printf("Historia jest pełna. Nie dodano żadnego nowego elementu.\n");
        return;
    }

    StoreData storeData;
    storeData.TemperatureInput = temperatureInput;
    storeData.TemperatureOutput = temperatureOutput;
    storeData.UnitInput = unitInput;
    storeData.UnitOutput = unitOutput;
    storeData.HistoryIndex = dataCounter;

    history[dataCounter] = storeData;
    dataCounter++;
}

static void UpdateDataInHistory(int historyIndex, float temperatureInput, float temperatureOutput, char unitInput, char unitOutput) {

    if (historyIndex < 0 || historyIndex >= dataCounter) {
        printf("Invalid index!\n");
        return;
    }

    StoreData storeData = history[historyIndex];

    storeData.Update(temperatureInput, temperatureOutput, unitInput, unitOutput);
}

static StoreData GetDataByIndexFromHistory(const int index) {
    return history[index];
}

StoreData remove_data_from_history(const int index) {

    /*if (index < 0 || index >= dataCounter) {
        printf("Invalid index!\n");
        return;
    }*/

    StoreData storeData = history[index];
    history[index].Clear();


    for (int i = index; i < dataCounter; i++)
    {
        history[i] = history[i + 1];
        history[i].HistoryIndex--;

        if (history[i].HistoryIndex == 0)
            break;
    }

    dataCounter--;
    return storeData;
}

void add_random_data_to_history() {

    while(dataCounter <= MAX_HISTORY)
    {
        int choiceMin = 1;
        int choiceMax = 6;
        int randChoice = rand() % (choiceMax - choiceMin + 1) + choiceMin;


        int temperaturaMin = -999;
        int temperaturaMax = 999;
        int randTemperatureInput = rand() % (temperaturaMax - temperaturaMin + 1) + temperaturaMin;

        switch (randChoice)
        {
	        case 1:
		        {
			        float temperatureOutput = FtoC(randTemperatureInput);
        			add_data_to_history(randTemperatureInput, temperatureOutput, 'F', 'C');
        			break;
		        }
	        case 2:
		        {
			        float temperatureOutput = FtoK(randTemperatureInput);
        			add_data_to_history(randTemperatureInput, temperatureOutput, 'F', 'K');
        			break;
		        }
	        case 3:
	            {
		            float temperatureOutput = CtoF(randTemperatureInput);
		            add_data_to_history(randTemperatureInput, temperatureOutput, 'C', 'F');
		            break;
	            }
	        case 4:
		        {
		            float temperatureOutput = CtoK(randTemperatureInput);
		            add_data_to_history(randTemperatureInput, temperatureOutput, 'C', 'K');
		            break;
		        }
	        case 5:
		        {
		            float temperatureOutput = KtoC(randTemperatureInput);
		            add_data_to_history(randTemperatureInput, temperatureOutput, 'K', 'C');
		            break;
		        }
	        case 6:
		        {
		            float temperatureOutput = KtoF(randTemperatureInput);
		            add_data_to_history(randTemperatureInput, temperatureOutput, 'K', 'F');
		            break;
		        }

        }

        if(dataCounter == MAX_HISTORY)
        {
            system("cls");
            printf("Ramdom data was added to history\n");
            show_history_menu();
        }
    }

}

void show_history_by_input_unit(char unitInput)
{

    bool hasUnitByFilter = false;

    for (int i = 0; i < dataCounter; i++)
    {
        if (history[i].UnitInput == unitInput)
        {
            hasUnitByFilter = true;
	        printf("<%d> %.2f%c = %.2f%c\n", history[i].HistoryIndex, history[i].TemperatureInput,
			   history[i].UnitInput, history[i].TemperatureOutput, history[i].UnitOutput);
        }
    }

    if(hasUnitByFilter == false)
    {
        printf("History doesn't have units: %c", unitInput);
    }
}


void show_history_menu() {
    while (true)
    {
        printf("Wybierz filtr historii:\n");
        printf("1 - Tylko C -> inne\n");
        printf("2 - Tylko F -> inne\n");
        printf("3 - Tylko K -> inne\n");
        printf("4 - Cala historia\n");
        printf("5 - Go to Delete Menu\n");
        printf("6 - Go to Update Menu\n");
        printf("7 - Go to Main Menu\n");
        printf("Twoj wybor:\n");

        int choice = 0;
        if (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 7) {
            printf("Nie prawidlowy wybor. Powrot do menu glownego\n");
        }
        while (getchar() != '\n');
       
            switch (choice)
            {
            case 1:
                show_history_by_input_unit('C');
                break;
            case 2:
                show_history_by_input_unit('F');
                break;
            case 3:
                show_history_by_input_unit('K');
                break;
            case 4:
                show_all_history();
                break;
            case 5:
                show_delete_menu();
                return;
            case 6:
                show_update_menu();
                return;
            case 7:
                show_main_menu();
                return;

            default:
                printf("Wrong choice\n");
                break;
            }

            printf("\nNaciśnij Enter, aby kontynuować...");
            getchar();

      
    }
}

void show_delete_menu() {
    if (dataCounter == 0) {
        printf("Historia jest pusta. Nie ma nic do usuniеcia.\n");
        return;
    }
    /*system("cls");*/
    int enityToRemove;
    printf("Wprowadz numer linii do usuniecia.(0-%d)", dataCounter);
    scanf_s("%d", &enityToRemove);

    if (enityToRemove < 0 || enityToRemove > dataCounter) {
        printf("Nie prawidwowy wybor.\n");
        return;
    }
    StoreData removed = remove_data_from_history(enityToRemove);
    printf("Usunienta linia: ");
    printf("<%d> %.2f%c = %.2f%c\n", removed.HistoryIndex, removed.TemperatureInput,
        removed.UnitInput, removed.TemperatureOutput, removed.UnitOutput);

    show_history_menu();
}

void show_update_menu()
{
    //input history index for update
    printf("Not Ready!!!\n");
    show_history_menu();
}

void show_all_history()
{
	for(int i=0; i < dataCounter; i++)
	{
        printf("<%d> %.2f%c = %.2f%c\n", history[i].HistoryIndex, history[i].TemperatureInput,
            history[i].UnitInput, history[i].TemperatureOutput, history[i].UnitOutput);
	}
}

void show_main_menu()
{
    int choice;
    float temperatureInput = 0;
    int valid;

	while (true) {
	/*	system("cls");*/ // Clear console

		printf("Wybierz opcję:\n");
		printf("1 - przelicz Fahr -> Celsius\n");
		printf("2 - przelicz Fahr -> Kelwin\n");
		printf("3 - przelicz Celsius -> Fahr\n");
		printf("4 - przelicz Celsius -> Kelwin\n");
		printf("5 - przelicz Kelwin -> Celsius\n");
		printf("6 - przelicz Kelwin -> Fahr\n");
		printf("7 - Add random data to history\n");
        printf("8 - Pokaz historie przeliczen\n");
		printf("-1 - zalonc dzialania programu\n");

		printf("Wybór: ");

        if (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 8) {
            printf("Nie prawidlowy wybor. Powrot do menu glownego\n");
        }
        while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			{
				printf("Podaj temperaturę w Fahrenheitach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = FtoC(temperatureInput);
				printf("Wynik: %.2f C\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'F', 'C');
				break;
			}

		case 2:
			{
				printf("Podaj temperaturę w Fahrenheitach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = FtoK(temperatureInput);
				printf("Wynik: %.2f K\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'F', 'K');
				break;
			}
		case 3:
			{
				printf("Podaj temperaturę w Celsiuszach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = CtoF(temperatureInput);
				printf("Wynik: %.2f F\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'C', 'F');
				break;
			}
		case 4:
			{
				printf("Podaj temperaturę w Celsiuszach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = CtoK(temperatureInput);
				printf("Wynik: %.2f K\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'C', 'K');
				break;
			}
		case 5:
			{
				printf("Podaj temperaturę w Kelvinach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = KtoC(temperatureInput);
				printf("Wynik: %.2f C\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'K', 'C');
				break;

			}
		case 6:
			{
				printf("Podaj temperaturę w Kelvinach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = KtoF(temperatureInput);
				printf("Wynik: %.2f F\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'K', 'F');
				break;
			}
		case 7:
			{
                if(dataCounter == MAX_HISTORY)
                {
                    printf("History is full");
                    break;
                }
				add_random_data_to_history();
                break;
			}
		case 8:
			if (dataCounter == 0) {
				printf("Brak zapisanej historii przeliczeń");
				break;
			}
			show_history_menu();
			break;

		default:
			printf("Nieprawidłowy wybór.\n");
			break;
		}

		printf("\nNaciśnij Enter, aby kontynuować...");
		getchar();
		getchar();

	}
}

int main() {
    
    show_main_menu();
    return 0;
}


/* if (scanf_s("%d", &choice) != 1) {
    printf("Nieprawidłowe dane wejściowe. Proszę wpisać numer.\n");
    while (getchar() != '\n');
    continue;
}

if (choice == -1) {
    printf("Zakończono działanie programu.\n");
    return 0;
}*/

/*switch (choice) {
case 1:
    printf("Podaj temperaturę w Fahrenheitach: ");
    if (scanf_s("%f", &temperatureInput) != 1) {
        printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
        while (getchar() != '\n');
        break;
    }
    valid = check(temperatureInput, 'F');
    if (valid == -999.0) {
        showMessageNotSuchTemperature();
    }
    else {
        float przerobiony = FtoC(temperatureInput);
        printf("Wynik: %.2f C\n", przerobiony);
        storeTemperaturs(temperatureInput, przerobiony, 'F', 'C');
    }
    break;

case 2:
    printf("Podaj temperaturę w Fahrenheitach: ");
    if (scanf_s("%f", &temperatureInput) != 1) {
        printf("Nieprawidlowe dane wejściowe. Proszę wprowadzić prawidlowa temperature.\n");
        while (getchar() != '\n');
        break;
    }
    valid = check(temperatureInput, 'F');
    if (valid == -999.0) {
        showMessageNotSuchTemperature();
    }
    else {
        float przerobiony = FtoK(temperatureInput);
        printf("Wynik: %.2f K\n", przerobiony);
        storeTemperaturs(temperatureInput, przerobiony, 'F', 'K');
    }
    break;

case 3:
    printf("Podaj temperaturę w Celsiuszach: ");
    if (scanf_s("%f", &temperatureInput) != 1) {
        printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
        while (getchar() != '\n');
        break;
    }
    valid = check(temperatureInput, 'C');
    if (valid == -999.0) {
        showMessageNotSuchTemperature();
    }
    else {
        float przerobiony = CtoF(temperatureInput);
        printf("Wynik: %.2f F\n", CtoF(temperatureInput));
        storeTemperaturs(temperatureInput, przerobiony, 'C', 'F');
    }
    break;

case 4:
    printf("Podaj temperaturę w Celsiuszach: ");
    if (scanf_s("%f", &temperatureInput) != 1) {
        printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
        while (getchar() != '\n');
        break;
    }
    valid = check(temperatureInput, 'C');
    if (valid == -999.0) {
        showMessageNotSuchTemperature();
    }
    else {
        float przerobiony = CtoK(temperatureInput);
        printf("Wynik: %.2f K\n", CtoK(temperatureInput));
        storeTemperaturs(temperatureInput, przerobiony, 'C', 'K');
    }
    break;

case 5:
    printf("Podaj temperaturę w Kelvinach: ");
    if (scanf_s("%f", &temperatureInput) != 1) {
        printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
        while (getchar() != '\n');
        break;
    }
    valid = check(temperatureInput, 'K');
    if (valid == -999.0) {
        showMessageNotSuchTemperature();
    }
    else {
        float przerobiony = KtoC(temperatureInput);
        printf("Wynik: %.2f C\n", KtoC(temperatureInput));
        storeTemperaturs(temperatureInput, przerobiony, 'K', 'C');
    }
    break;

case 6:
    printf("Podaj temperaturę w Kelvinach: ");
    if (scanf_s("%f", &temperatureInput) != 1) {
        printf("Nieprawidłowe dane wejściowe. Proszę wprowadzić prawidłową temperaturę.\n");
        while (getchar() != '\n');
        break;
    }
    valid = check(temperatureInput, 'K');
    if (valid == -999.0) {
        showMessageNotSuchTemperature();
    }
    else {
        float przerobiony = KtoF(temperatureInput);
        printf("Wynik: %.2f F\n", KtoF(temperatureInput));
        storeTemperaturs(temperatureInput, przerobiony, 'K', 'F');
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
getchar();*/




//void storeTemperaturs(float oryginalTemp, float przerobionyTemp, char oryginalUnit, char przerobionyUnit) {
//    if (HistoryCounter + 1 < MAX_HISTORY) {
//        temperatureData[HistoryCounter] = oryginalTemp;
//        temperatureUnits[HistoryCounter] = oryginalUnit;
//        HistoryCounter++;
//        temperatureData[HistoryCounter] = przerobionyTemp;
//        temperatureUnits[HistoryCounter] = przerobionyUnit;
//        HistoryCounter++;
//    }
//    else {
//        printf("Przekroczono limit historii!\n");
//    }
//
//}
//struct Conversition {
//    char type[10];
//    double input;
//    double output;
//};
//struct Conversition history[100];
//int history_count = 0;

//static void add_to_history(const char* type, double input, double output) {
//    if (history_count < 100) { // проверка, чтобы не выйти за пределы массива
//        // Копируем строку с усечением, если длина превышает размер поля
//        if (strlen(type) >= sizeof(history[history_count].type)) {
//            printf("Ostrzeżenie: Obcinanie ciągu znaków w celu dopasowania do bufora.\n");
//        }
//        strncpy_s(history[history_count].type, type, sizeof(history[history_count].type) - 1);
//        history[history_count].type[sizeof(history[history_count].type) - 1] = '\0'; // Добавляем завершающий нулевой символ
//
//        // Сохраняем входные и выходные значения
//        history[history_count].input = input;
//        history[history_count].output = output;
//
//        // Увеличиваем счетчик истории
//        history_count++;
//    }
//    else {
//        printf("Historia jest pelna!\n"); // Добавляем перевод строки для читабельности
//    }
//}



//void pokazHistorie() {
//    if (HistoryCounter == 0) {
//        printf("Brak zapisanej historii przeliczeń");
//        return;
//    }
//    int historiaChoise;
//    printf("Wybierz filtr historii:\n");
//    printf("1 - Tylko C -> inne\n");
//    printf("2 - Tylko F -> inne\n");
//    printf("3 - Tylko K -> inne\n");
//    printf("4 - Cala historia\n");
//    printf("Twoj wybor:\n");
//
//    if (scanf_s("%d", &historiaChoise) != 1 || historiaChoise < 1 || historiaChoise > 4) {
//        printf("Nie prawidlpwt wybor. Powrot do menu glownego\n");
//        while (getchar() != '\n'); // отчистка ввода
//        return;
//    }
//    char filterUnits = '\0'; // переменная для фильтрации
//    if (filterUnits == 1)
//        filterUnits = 'C';
//    else if (filterUnits == 2)
//        filterUnits = 'F';
//    else if (filterUnits == 3)
//        filterUnits = 'K';
//    printf("\n Historia przeliczonych temperatur\n"); // ввывод отфильтрованной истории
//
//    int found = 0; // для проверки, есть ли данные
//    for (int i = 0; i < HistoryCounter; i += 2) // i=i+2, обработать одну пару данных за итерацию 
//    {
//        char originalUnit = temperatureUnits[i];
//        char convertedUnit = temperatureUnits[i + 1];
//
//        if (filterUnits != '\0' && originalUnit != filterUnits) // проверка фильтра 
//        {
//            continue; // пропускаем неподходящие записи
//        }
//        printf("<%d> %.2f%c = %.2f%c\n", (i / 2) + 1, temperatureData[i], originalUnit, temperatureData[i + 1], convertedUnit);
//        found = 1; // есть данные
//
//    }
//    if (!found) {
//        printf("Brak danych dla wybranego filtra");
//    }
//
//    printf("Naczisnij ENTER, aby powrocic do menu glownego\n");
//    while (getchar() != '\n'); // отчистка ввода
//    getchar();
//
//
//
//    printf("Historia przeliczonych temperatur:\n");
//
//    int pageSize = 5;
//    int currentPage = 0;
//    int totalPages = (HistoryCounter / 2 + pageSize - 1) / pageSize;
//    StoreData storeData;
//
//    while (1) {
//        system("cls");
//        printf("Strona %d z %d\n", currentPage + 1, totalPages);
//
//        for (int i = currentPage * pageSize * 2; i < (currentPage + 1) * pageSize * 2 && i < HistoryCounter; i += 2) {
//            printf("<%d> %.2f%c = %.2f%c\n", (i / 2) + 1,
//                temperatureData[i], temperatureUnits[i],
//                temperatureData[i + 1], temperatureUnits[i + 1]);
//        }
//        printf("Wybierz opcje:\n");
//        if (currentPage > 0)
//            printf("1 - Poprzednia strona\n");
//        if (currentPage < totalPages - 1)
//            printf("2 - Nasttpna strona\n");
//        printf("0 - Powrot do menu glownego\n");
//
//        int choice = 0;
//        if (scanf_s("%d", &choice) != 1) {
//            printf("Nie prawidwowe dane wejsciowe.\n");
//            while (getchar() != '\n');
//            continue;
//        } if (choice == 0) {
//            break;
//        }
//        else if (choice == 1 && currentPage > 0) {
//            currentPage--;
//        }
//        else if (choice == 2 && currentPage < totalPages - 1) {
//            currentPage++;
//        }
//        else {
//            printf("Nie prawidłowa opcja. Spróbuj ponownie.\n");
//        }
//    }
//
//}
