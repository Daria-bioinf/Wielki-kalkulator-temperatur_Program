
struct StoreData {

    float TemperatureInput;
    float TemperatureOutput;
    char UnitInput = '\0';
    char UnitOutput = '\0';
    int HistoryIndex = 0;

    void Clear()
    {
        TemperatureInput = 0;
        TemperatureOutput = 0;
        UnitInput = '\0';
        UnitOutput = '\0';
        HistoryIndex = 0;
    }

    void Update(float temperatureInput, float temperatureOutput, char unitInput, char unitOutput)
    {
        TemperatureInput = temperatureInput;
        TemperatureOutput = temperatureOutput;
        UnitInput = unitInput;
        UnitOutput = unitOutput;
    }
};