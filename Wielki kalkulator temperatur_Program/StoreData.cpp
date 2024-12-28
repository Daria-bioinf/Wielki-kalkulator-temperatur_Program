
struct StoreData {
    float temperatureInput = 0.0f;
    float temperatureOutput = 0.0f;
    char unitInput = '\0';
    char unitOutput = '\0';
    int historyIndex = 0;

    bool is_empty = temperatureInput == 0.0f && temperatureOutput == 0.0f && unitInput == '\0' && unitOutput == '\0' && historyIndex == 0;

    void Clear() {
        temperatureInput = 0.0f;
        temperatureOutput = 0.0f;
        unitInput = '\0';
        unitOutput = '\0';
        historyIndex = 0;
    }

    void Update(float tempInput, float tempOutput, char unitIn, char unitOut) {
        temperatureInput = tempInput;
        temperatureOutput = tempOutput;
        unitInput = unitIn;
        unitOutput = unitOut;
    }
};
