//
// Created by YKROPCHIK on 17.06.2020.
//
#include <vector>
#include <map>

#define TURN_ON true
#define TURN_OFF false
#define HUM_SENS 0
#define TEMP_SENS 1
#define PRESS_SENS 2

class Sensor;
class HumiditySensor;
class TemperatureSensor;
class PressureSensor;
class Base;
class EventManager;
class MeasurementListener;
class TempListener;
class HumListener;
class Heater;
class Humidifier;

class Sensor {
protected:
    unsigned int id;
    Base *base;

public:
    virtual unsigned int getId() = 0;
    virtual void setId(unsigned int id) = 0;            // oh, shit, i do not know why i need these methods, but just let them be...
    virtual int measure() = 0;
};

class HumiditySensor : public Sensor {
private:
    unsigned int humidity;                              /// property for simulate measurement

public:
    HumiditySensor(Base *base);
    unsigned int getId() override;
    void setId(unsigned int id) override;
    int measure() override;
};

class TemperatureSensor : public Sensor {
private:
    int temperature;                                  /// property for simulate measurement

public:
    TemperatureSensor(Base *base);
    unsigned int getId() override;
    void setId(unsigned int id) override;
    int measure() override;
};

class PressureSensor : public Sensor {
private:
    unsigned int pressure;                              /// property for simulate measurement

public:
    PressureSensor(Base *base);
    unsigned int getId() override;
    void setId(unsigned int id) override;
    int measure() override;
};

class Base {
private:
    Sensor* sensors[3];

public:
    EventManager *events;
    Base();
    bool addSensor(int type, Sensor* sensor);
    bool removeSensor(int type);
    unsigned int checkHumidity();
    int checkTemperature();
    unsigned int checkPressure();
};

class EventManager {
private:
    std::map<int, MeasurementListener*> listeners;

public:
    void subscribe(int type, MeasurementListener* listener);
    void unsubscribe(int type);
    void notify(int sensorType, int data);
};

class MeasurementListener {
public:
    virtual bool setRequirement(int requirement) = 0;
    virtual int getRequirement() = 0;
    virtual void update(int data) = 0;
};

class TempListener : public MeasurementListener {
private:
    int requirementTemp;
    Heater* heater;

public:
    TempListener(int requirement, Heater* heater);
    bool setRequirement(int requirement) override;
    int getRequirement()override;
    void update(int changedTemp) override;
};

class HumListener : public MeasurementListener {
private:
    unsigned int requirementHum;
    Humidifier* humidifier;

public:
    HumListener(unsigned int requirement, Humidifier* humidifier);
    bool setRequirement(int requirement) override;
    int getRequirement()override;
    void update(int changedHum) override;
};

class Heater {
private:
    bool state;

public:
    Heater();
    void setState(bool state);
    bool getState();
};

class Humidifier {
private:
    bool state;

public:
    Humidifier();
    void setState(bool state);
    bool getState();
};