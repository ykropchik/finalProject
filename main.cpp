#include <iostream>
#include "src/proj.h"

using namespace std;

int main() {
    Heater myBatareya;
    Humidifier myYvlazhnyatel;
    TempListener *tempListener = new TempListener(26, &myBatareya);
    HumListener *humListener = new HumListener(78, &myYvlazhnyatel);

    Base weatherBase;
    weatherBase.addSensor(HUM_SENS, new HumiditySensor(&weatherBase));
    weatherBase.addSensor(TEMP_SENS, new TemperatureSensor(&weatherBase));
    weatherBase.addSensor(PRESS_SENS, new PressureSensor(&weatherBase));
    weatherBase.events->subscribe(TEMP_SENS, tempListener);
    weatherBase.events->subscribe(HUM_SENS, humListener);

    for (int i = 0; i < 12; ++i) {
        cout << "Температура: " << weatherBase.checkTemperature()
             << " Поддерживаемая температура в комнате: " << tempListener->getRequirement()
             << " Состояние обогревателя: " << (myBatareya.getState() ? "ON" : "OFF") << endl;
        cout << "Влажность: " << weatherBase.checkHumidity()
             << " Поддерживаемая влажность в комнате: " << humListener->getRequirement()
             << " Состояние увлажнителя: " << (myYvlazhnyatel.getState() ? "ON" : "OFF") << endl;
        cout << "Давление: " << weatherBase.checkPressure() << endl;
    }

    return 0;
}
