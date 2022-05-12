#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Settings.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class DataStorage
{
public:
    json JsonSetting{};

    void getSetting(Settings& settings);
    void saveSetting(Settings settings);
    void saveScore(int value, int row, int col, string timeManager);
    void createFileJson(Settings settings);
    void refreshSetting(Settings& settings);
private:
    const string file = "storege/settings.json";
    const string DefoltFile = "storege/defolt_settings.json";
};
