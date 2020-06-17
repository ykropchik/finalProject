//
// Created by YKROPCHIK on 17.06.2020.
//
#include "proj.h"

/**================================HumiditySensor================================**/
HumiditySensor::HumiditySensor(Base *base) {
    this->id = id;
    this->base = base;
    this->humidity = 25;
}

int HumiditySensor::measure() {
    /** block for simulation of changing humidity (maybe this is a bad way, (heater work, but temp whatever decreases and vice versa) but i think all right)**/
    srand(time(0));
    if (rand() % 2 == 0) {
        humidity += rand() % 50 + 1;
    } else {
        humidity -= rand() % 50 + 1;
    }

    if (humidity < 1) {
        humidity = 1;
    }

    if (humidity > 100) {
        humidity = 100;
    }
    /**============================================**/

    return humidity;
}

unsigned int HumiditySensor::getId() {
    return id;
}

void HumiditySensor::setId(unsigned int id) {
    this->id = id;
}

/**================================TemperatureSensor================================**/
TemperatureSensor::TemperatureSensor(Base *base) {
    this->id = id;
    this->base = base;
    this->temperature = 16;
}

int TemperatureSensor::measure() {
    /** block for simulation of changing temperature **/
    srand(time(0));
    if (rand() % 2 == 0) {
        temperature += rand() % 12;
    } else {
        temperature -= rand() % 12;
    }

    if (temperature < -45) {
        temperature = -45;
    }

    if (temperature > 45) {
        temperature = 45;
    }
    /**============================================**/

    return temperature;
}

unsigned int TemperatureSensor::getId() {
    return id;
}

void TemperatureSensor::setId(unsigned int id) {
    this->id = id;
}

/**==================================PressureSensor===================================**/
PressureSensor::PressureSensor(Base *base) {
    this->id = id;
    this->base = base;
    this->pressure = 760;
}

int PressureSensor::measure() {
    /** block for simulation of changing pressure **/
    srand(time(0));
    if (rand() % 2 == 0) {
        pressure += rand() % 3;
    } else {
        pressure -= rand() % 3;
    }

    if (pressure < 700) {
        pressure = 700;
    }

    if (pressure > 810) {
        pressure = 810;
    }
    /**============================================**/

    return pressure;
}

unsigned int PressureSensor::getId() {
    return id;
}

void PressureSensor::setId(unsigned int id) {
    this->id = id;
}

/**=================================Base=============================================**/
Base::Base() {
    events = new EventManager();

    for (int i = 0; i < 3; ++i) {
        sensors[i] = nullptr;
    }
}

bool Base::addSensor(int type, Sensor* sensor) {
    if ((type < HUM_SENS) || (type > PRESS_SENS)) {
        return false;
    }

    if (sensors[type] != nullptr) {
        return false;
    }

    sensors[type] = sensor;
    return true;
}

bool Base::removeSensor(int type) {
    if ((type < HUM_SENS) || (type > PRESS_SENS)) {
        return false;
    }

    if (sensors[type] == nullptr) {
        return false;
    }

    sensors[type] = nullptr;
}

unsigned int Base::checkHumidity() {
    if (sensors[HUM_SENS] == nullptr){
        return 0;
    }

    int result = sensors[HUM_SENS]->measure();
    events->notify(HUM_SENS, result);
    return result;
}

int Base::checkTemperature() {
    if (sensors[TEMP_SENS] == nullptr){
        return 0;
    }

    int result = sensors[TEMP_SENS]->measure();
    events->notify(TEMP_SENS, result);
    return result;
}

unsigned int Base::checkPressure() {
    if (sensors[PRESS_SENS] == nullptr){
        return 0;
    }

    return sensors[PRESS_SENS]->measure();
}

/**=================================EventManager=====================================**/
void EventManager::subscribe(int type, MeasurementListener* listener) {
    if (listeners[type] != nullptr) {
        return;
    }

    listeners[type] = listener;
}

void EventManager::unsubscribe(int type) {
    if (listeners[type] == nullptr) {
        return;
    }

    listeners.erase(type);
}

void EventManager::notify(int sensorType, int data) {
    if (listeners[sensorType] == nullptr) {
        return;
    }

    listeners[sensorType]->update(data);
}

/**=================================TempListener=====================================**/
TempListener::TempListener(int requirement, Heater* heater) {
    this->requirementTemp = requirement;
    this->heater = heater;
}

bool TempListener::setRequirement(int requirement) {
    if ((requirement < -45) || requirement > 45) {
        return false;
    }

    this->requirementTemp = requirement;
}

int TempListener::getRequirement() {
    return this->requirementTemp;
}

void TempListener::update(int changedTemp) {
    if (changedTemp > requirementTemp) {
        heater->setState(TURN_OFF);
    } else if (changedTemp  < requirementTemp) {
        heater->setState(TURN_ON);
    }
}
/**=================================HumListener====================================**/
HumListener::HumListener(unsigned int requirement, Humidifier* humidifier) {
    this->requirementHum = requirement;
    this->humidifier = humidifier;
}

bool HumListener::setRequirement(int requirement) {
    if ((requirement < 1) || requirement > 100) {
        return false;
    }

    this->requirementHum = requirement;
}

int HumListener::getRequirement() {
    return this->requirementHum;
}

void HumListener::update(int changedTemp) {
    if (changedTemp > requirementHum) {
        humidifier->setState(TURN_OFF);
    } else if (changedTemp < requirementHum) {
        humidifier->setState(TURN_ON);
    }
}
/**=================================Heater====================================**/
Heater::Heater(){
    this->state = TURN_OFF;
}

void Heater::setState(bool state) {
    this->state = state;
}

bool Heater::getState() {
    return state;
}

/**=================================Humidifier====================================**/
Humidifier::Humidifier(){
    this->state = TURN_OFF;
}

void Humidifier::setState(bool state) {
    this->state = state;
}

bool Humidifier::getState() {
    return state;
}
