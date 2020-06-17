//
// Created by YKROPCHIK on 17.06.2020.
//
#include <vector>

#define TURN_ON true
#define TURN_OFF false

class Sensor;
class HumiditySensor;
class TemperatureSensor;
class PressureSensor;
class Base;
class EventManager;
class MeasurmentListener;
class HeaterListener;
class HumidifierListener;
class Heater;
class Humidifier;

class Sensor {
protected:
    unsigned int id;
    Base *base;

public:
    virtual unsigned int getId() = 0;
    virtual void setId(unsigned int id) = 0;
};

class HumiditySensor : virtual public Sensor {
public:
    HumiditySensor(unsigned int id, Base base);
    unsigned int measure();
};

class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(unsigned int id, Base base);
    double measure();
};

class PressureSensor : public Sensor {
public:
    PressureSensor(unsigned int id, Base base);
    unsigned int measure();
};

class Base {
private:
    std::vector<Sensor*> sensors;
    EventManager *events;

public:

    void checkHumidity();
    void checkTemperature();
    void checkPressure();
};

class EventManager {
private:
    std::vector<MeasurmentListener*> listeners;

public:
    void subscribe();
};

class MeasurmentListener {
public:
    virtual void setRequirement(void* data) = 0;
    virtual void* getRequirement() = 0;
    virtual void update(void* data) = 0;
};

class HeaterListener : public MeasurmentListener {
public:
    HeaterListener(double requirement);
};

class HumidifierListener : public MeasurmentListener {
public:
    HumidifierListener(unsigned int requirement);
};

class Heater {
private:
    bool state;

public:
    void setState(bool state);
    bool getState();
};

class Humidifier {
private:
    bool state;

public:
    void setState(bool state);
    bool getState();
};