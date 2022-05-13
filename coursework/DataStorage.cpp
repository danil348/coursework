#include "DataStorage.h"

using json = nlohmann::json;
using namespace std;

void DataStorage::getSetting(Settings& settings)
{
    ifstream writer;
    writer.open(file);
    if (writer.is_open()) {
        writer >> JsonSetting;
    }
    writer.close();

    settings.sound = JsonSetting["game"]["sound"];
    for (int i = 0; i < settings.row; i++) {
        settings.screen[i][2] = 0;
    }
    settings.screen[JsonSetting["game"]["activeScreen"]][2] = 1;

    settings.mana = JsonSetting["player"]["mana"];
    /*JsonSetting["bullet"]["bulletOffsetRadius"] = settings.bulletOffsetRadius;
    JsonSetting["bullet"]["bulletDelay"] = settings.bulletDelay;
    JsonSetting["bullet"]["bulletDamage"] = settings.bulletDamage;
    JsonSetting["bullet"]["type"] = settings.type;
    JsonSetting["bullet"]["manaCost"] = settings.manaCost;
    JsonSetting["bullet"]["cost"] = settings.cost;
    JsonSetting["bullet"]["weaponAngle"] = settings.weaponAngle;
    JsonSetting["bullet"]["totalWeapons"] = settings.totalWeapons;

    JsonSetting["player"]["speed"] = settings.speed;
    JsonSetting["player"]["damage"] = settings.damage;
    JsonSetting["player"]["shotDamage"] = settings.shotDamage;
    JsonSetting["player"]["score"] = settings.score;
    JsonSetting["player"]["hp"] = settings.hp;
    JsonSetting["player"]["armor"] = settings.armor;
    JsonSetting["player"]["mana"] = settings.mana;
    JsonSetting["player"]["offsetX"] = settings.offsetX;
    JsonSetting["player"]["offsetY"] = settings.offsetY;*/
}

void DataStorage::saveSetting(Settings settings)
{
    ofstream writer;
    writer.open(file);

    if (writer.is_open()) {
        JsonSetting["game"]["sound"] = settings.sound;
        for (int i = 0; i < settings.row; i++) {
            if (settings.screen[i][2] == 1) {
                JsonSetting["game"]["activeScreen"] = i;
            }
        }

        JsonSetting["bullet"]["bulletOffsetRadius"] = settings.bulletOffsetRadius;
        JsonSetting["bullet"]["bulletDelay"] = settings.bulletDelay;
        JsonSetting["bullet"]["bulletDamage"] = settings.bulletDamage;
        JsonSetting["bullet"]["type"] = settings.type;
        JsonSetting["bullet"]["manaCost"] = settings.manaCost;
        JsonSetting["bullet"]["cost"] = settings.cost;
        JsonSetting["bullet"]["weaponAngle"] = settings.weaponAngle;
        JsonSetting["bullet"]["totalWeapons"] = settings.totalWeapons;

        JsonSetting["player"]["speed"] = settings.speed;
        JsonSetting["player"]["damage"] = settings.damage;
        JsonSetting["player"]["shotDamage"] = settings.shotDamage;
        JsonSetting["player"]["score"] = settings.score;
        JsonSetting["player"]["hp"] = settings.hp;
        JsonSetting["player"]["armor"] = settings.armor;
        JsonSetting["player"]["mana"] = settings.mana;
        JsonSetting["player"]["offsetX"] = settings.offsetX;
        JsonSetting["player"]["offsetY"] = settings.offsetY;

        writer << JsonSetting.dump(1);
    }
    writer.close();
}

void DataStorage::saveScore(int value, int row, int col, string time)
{
    string tmpNameRekord = to_string(row) + "x" + to_string(col);
    ofstream writer;
    writer.open(file);
    if (writer.is_open()) {
        JsonSetting["rekord"] += { tmpNameRekord, {
            {"value", value},
            {"row", row},
            {"col", col},
            {"time",time}
        } };
        writer << JsonSetting.dump(1);
    }
    writer.close();
}

void DataStorage::createFileJson(Settings settings)
{
    ofstream writer;
    writer.open(file);
    if (writer.is_open()) {
        JsonSetting = {
            {"game" , {
                {"score", settings.score}
            },
            "bullet", {
                {"asdf", settings.score}
            },
            "player" , {
                {"asd", settings.score}
            },}

        };
        writer << JsonSetting.dump(4);
    }

    writer.close();
}

void DataStorage::refreshSetting(Settings& settings)
{
    CopyFile(L"storege/defolt_settings.json", L"storege/settings.json", false);
    /*ifstream writer;
    writer.open(DefoltFile);
    if (writer.is_open()) {
        writer >> JsonSetting;
    }
    writer.close();

    settings.score = JsonSetting["score"];

    ofstream _writer;
    _writer.open(file);

    if (_writer.is_open()) {
        JsonSetting["score"] = settings.score;
        _writer << JsonSetting.dump(1);
    }
    _writer.close();*/
}
