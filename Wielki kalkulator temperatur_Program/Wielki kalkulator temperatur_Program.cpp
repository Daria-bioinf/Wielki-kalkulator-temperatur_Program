#include <cstdio>
#include <cstdlib>
#include "HeaderFile.h.cpp"

using namespace std;

StoreData history[MAX_HISTORY];
int data_counter = 0;

float FtoC(float f) {
    return (f - 32.0) * 5.0 / 9.0;
}
float FtoK(float f) {
    return (f + 459.67) * 5.0 / 9.0;
}
float CtoF(float c) {
    return c * 9.0 / 5.0 + 32.0;
}
float CtoK(float c) {
    return c + 273.15;
}
float KtoC(float k) {
    return k - 273.15;
}
float KtoF(float k) {
    return k * 9.0 / 5.0 - 459.67;
}


void add_data_to_history(float temperatureInput, float temperatureOutput, char unitInput, char unitOutput) {

    if (data_counter == MAX_HISTORY)
    {
        printf("Historia jest pelna. Nie dodano zadnego nowego elementu.\n");
        return;
    }

    StoreData storeData;

    storeData.Update(temperatureInput, temperatureOutput, unitInput, unitOutput);
    storeData.historyIndex = data_counter;

    history[data_counter] = storeData;
    data_counter++;
}

void update_data_in_history(int historyIndex, float temperatureInput, float temperatureOutput, char unitInput, char unitOutput) {

    if (historyIndex < 0 || historyIndex >= data_counter) {
        printf("Invalid index!\n");
        return;
    }

    printf("Stara wartosc: <%d> %.2f%c = %.2f%c\n", history[historyIndex].historyIndex, history[historyIndex].temperatureInput,
        history[historyIndex].unitInput, history[historyIndex].temperatureOutput, history[historyIndex].unitOutput);

    history[historyIndex].Update(temperatureInput, temperatureOutput, unitInput, unitOutput);

    printf("Nowa wartosc: <%d> %.2f%c = %.2f%c\n", history[historyIndex].historyIndex, history[historyIndex].temperatureInput,
        history[historyIndex].unitInput, history[historyIndex].temperatureOutput, history[historyIndex].unitOutput);
}

void remove_data_from_history(const int index) {

    StoreData removed = history[index];
    history[index].Clear();

    for (int i = index; i < data_counter; i++)
    {
        history[i] = history[i + 1];
        history[i].historyIndex--;
    }

    data_counter--;
    printf("Usunienta linia: ");
    printf("<%d> %.2f%c = %.2f%c\n", removed.historyIndex, removed.temperatureInput,
        removed.unitInput, removed.temperatureOutput, removed.unitOutput);
}

void add_random_data_to_history() {

    while(data_counter < MAX_HISTORY)
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

        if(data_counter == MAX_HISTORY)
        {
            system("cls");
            printf("Dane losowe zostaly dodane do historii\n");
            show_history_menu();
        }
    }

}

void show_all_history()
{
    for (int i = 0; i < data_counter; i++)
    {
        printf("<%d> %.2f%c = %.2f%c\n", history[i].historyIndex, history[i].temperatureInput,
            history[i].unitInput, history[i].temperatureOutput, history[i].unitOutput);
    }
}

void show_history_by_input_unit(char unitInput)
{

    bool hasUnitByFilter = false;

    for (int i = 0; i < data_counter; i++)
    {
        if (history[i].unitInput == unitInput)
        {
            hasUnitByFilter = true;

	        printf("<%d> %.2f%c = %.2f%c\n", history[i].historyIndex, history[i].temperatureInput,
			   history[i].unitInput, history[i].temperatureOutput, history[i].unitOutput);
        }
    }

    if(hasUnitByFilter == false)
    {
        printf("Historia nie ma jednostek: %c", unitInput);
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
        printf("5 - Przejdz do menu Delete\n");
        printf("6 - Przejdz do menu Update\n");
        printf("7 - Przejdz do menu Gwolne\n");
        printf("Twoj wybor:\n");

        int choice = 0;
        scanf_s("%d", &choice);

        if (choice < 1 || choice > 7) {
            printf("Nie prawidlowy wybor. Powrot do menu Glownego\n");
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
                printf("Nie prawidwowy wybor.\n");
                break;
            }

            printf("\nNacisnij Enter, aby kontynuowac...");
            getchar();

      
    }
}

void show_delete_menu() {
    if (data_counter == 0) {
        printf("Historia jest pusta. Nie ma nic do usuniеcia.\n");
        return;
    }
    /*system("cls");*/
    int numberToRemove;
    printf("Wprowadz numer linii do usuniecia.(0-%d): ", data_counter);
    scanf_s("%d", &numberToRemove);

    if (numberToRemove < 0 || numberToRemove > data_counter) {
        printf("Nie prawidwowy wybor.\n");
        return;
    }
    remove_data_from_history(numberToRemove);
    
    show_history_menu();
}

void show_update_menu()
{
    if (data_counter == 0) {
        printf("Historia jest pusta. Nie ma nic do aktualizacji.\n");
        return;
    }
    /*system("cls");*/
    int counterToUpdate, choice;
    float temperatureInput;
    printf("Wprowadz numer linii do update.(0-%d)\n", data_counter);
    scanf_s("%d", &counterToUpdate);

    if (counterToUpdate < 0 || counterToUpdate > data_counter) {
        printf("Nie prawidwowy wybor.\n");
        return;
    }

    printf("Wybierz opcje for linii:\n");
    printf("1 - przelicz Fahr -> Celsius\n");
    printf("2 - przelicz Fahr -> Kelwin\n");
    printf("3 - przelicz Celsius -> Fahr\n");
    printf("4 - przelicz Celsius -> Kelwin\n");
    printf("5 - przelicz Kelwin -> Celsius\n");
    printf("6 - przelicz Kelwin -> Fahr\n");

    if (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 8) {
        printf("Nie prawidlowy wybor. Powrot do menu glownego\n");
    }
    while (getchar() != '\n') {}

    switch (choice)
    {
	    case 1:
	    {
	        printf("Podaj temperature w Fahrenheitach: ");
	        scanf_s("%f", &temperatureInput);

	        float temperatureOutput = FtoC(temperatureInput);
	        printf("Wynik: %.2f C\n", temperatureOutput);
	        update_data_in_history(counterToUpdate, temperatureInput, temperatureOutput, 'F', 'C');
	        break;
	    }

	    case 2:
	    {
	        printf("Podaj temperature w Fahrenheitach: ");
	        scanf_s("%f", &temperatureInput);

	        float temperatureOutput = FtoK(temperatureInput);
	        printf("Wynik: %.2f K\n", temperatureOutput);
	        update_data_in_history(counterToUpdate, temperatureInput, temperatureOutput, 'F', 'K');
	        break;
	    }
	    case 3:
	    {
	        printf("Podaj temperature w Celsiuszach: ");
	        scanf_s("%f", &temperatureInput);

	        float temperatureOutput = CtoF(temperatureInput);
	        printf("Wynik: %.2f F\n", temperatureOutput);
	        update_data_in_history(counterToUpdate, temperatureInput, temperatureOutput, 'C', 'F');
	        break;
	    }
	    case 4:
	    {
	        printf("Podaj temperature w Celsiuszach: ");
	        scanf_s("%f", &temperatureInput);

	        float temperatureOutput = CtoK(temperatureInput);
	        printf("Wynik: %.2f K\n", temperatureOutput);
	        update_data_in_history(counterToUpdate, temperatureInput, temperatureOutput, 'C', 'K');
	        break;
	    }
	    case 5:
	    {
	        printf("Podaj temperature w Kelvinach: ");
	        scanf_s("%f", &temperatureInput);

	        float temperatureOutput = KtoC(temperatureInput);
	        printf("Wynik: %.2f C\n", temperatureOutput);
	        update_data_in_history(counterToUpdate, temperatureInput, temperatureOutput, 'K', 'C');
	        break;

	    }
	    case 6:
	    {
	        printf("Podaj temperature w Kelvinach: ");
	        scanf_s("%f", &temperatureInput);

	        float temperatureOutput = KtoF(temperatureInput);
	        printf("Wynik: %.2f F\n", temperatureOutput);
	        update_data_in_history(counterToUpdate, temperatureInput, temperatureOutput, 'K', 'F');
	        break;
	    }

    }

    show_history_menu();
}

void show_main_menu()
{
    int choice;
    float temperatureInput = 0;

	while (true) {
	/*	system("cls");*/ // Clear console

		printf("Wybierz opcje:\n");
		printf("1 - przelicz Fahr -> Celsius\n");
		printf("2 - przelicz Fahr -> Kelwin\n");
		printf("3 - przelicz Celsius -> Fahr\n");
		printf("4 - przelicz Celsius -> Kelwin\n");
		printf("5 - przelicz Kelwin -> Celsius\n");
		printf("6 - przelicz Kelwin -> Fahr\n");
		printf("7 - Dodaj losowe dane do historii\n");
        printf("8 - Pokaz historie przeliczen\n");

		printf("Wybor: ");
        scanf_s("%d", &choice);

        
        while (getchar() != '\n') {}

	switch (choice)
		{
		case 1:
			{
				printf("Podaj temperature w Fahrenheitach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = FtoC(temperatureInput);
				printf("Wynik: %.2f C\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'F', 'C');
				break;
			}

		case 2:
			{
				printf("Podaj temperature w Fahrenheitach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = FtoK(temperatureInput);
				printf("Wynik: %.2f K\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'F', 'K');
				break;
			}
		case 3:
			{
				printf("Podaj temperature w Celsiuszach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = CtoF(temperatureInput);
				printf("Wynik: %.2f F\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'C', 'F');
				break;
			}
		case 4:
			{
				printf("Podaj temperature w Celsiuszach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = CtoK(temperatureInput);
				printf("Wynik: %.2f K\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'C', 'K');
				break;
			}
		case 5:
			{
				printf("Podaj temperature w Kelvinach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = KtoC(temperatureInput);
				printf("Wynik: %.2f C\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'K', 'C');
				break;

			}
		case 6:
			{
				printf("Podaj temperature w Kelvinach: ");
				scanf_s("%f", &temperatureInput);

				float temperatureOutput = KtoF(temperatureInput);
				printf("Wynik: %.2f F\n", temperatureOutput);
				add_data_to_history(temperatureInput, temperatureOutput, 'K', 'F');
				break;
			}
		case 7:
			{
                if(data_counter == MAX_HISTORY)
                {
                    printf("Historia jest pelna");
                    break;
                }
				add_random_data_to_history();
                break;
			}
		case 8:
			if (data_counter == 0) {
				printf("Brak zapisanej historii przeliczen");
				break;
			}
			show_history_menu();
			break;

		default:
			printf("Nieprawidlowy wybor.\n");
			break;
		}

		printf("\nNacisnij Enter, aby kontynuowac...");
		getchar();
		getchar();

	}
}

int main() {
    
    show_main_menu();
    return 0;
}