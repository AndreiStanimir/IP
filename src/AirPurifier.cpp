#include "include/AirPurifier.h"
AirPurifier *AirPurifier::instance = nullptr;
AirPurifier *AirPurifier::getInstance()
{
    if (instance == nullptr)
        instance = new AirPurifier();
    return instance;
}

bool AirPurifier::switch_power(bool on)
{
    isOn = on;
    return 1;
}

int AirPurifier::get_air_quality()
{
    return 42;
}

int AirPurifier::get_humidity_level()
{
    return 10;
}
float AirPurifier::getWaterTankLevel()
{
    return 2.3;
}

bool AirPurifier::connectToWifi(string name, string password)
{
    cout << "Connected to wifi :" << name;
    return true;
}
int AirPurifier::fillWaterTank(float water)
{
    if (water > 0)
    {
        waterTank += water;
    }
}

int AirPurifier::set(std::string name, std::string value)
{
    boost::algorithm::to_lower(name);
    boost::algorithm::to_lower(value);
    cout << name << endl;
    if (name == "airflow")
    {
        try
        {
            int power_int = stoi(value);
            if (!(power_int >= Off && power_int <= (int)Auto))
                return 0;
            Power power = static_cast<Power>(power_int);
            airflow_level = power;
            return 1;
        }
        catch (exception e)
        {
            cout << "error";
            return 0;
        }
    }
    else if (name == "humiditylevel")
    {
        try
        {
            int power_int = stoi(value);
            if (!(power_int >= Off && power_int <= (int)Auto))
                return 0;
            Power power = static_cast<Power>(power_int);
            humidity_level = power;
            return 1;
        }
        catch (exception e)
        {
            cout << "error";
            return 0;
        }
    }
    else if (name == "shutdown")
    {
        try
        {
            int time_in_seconds = stoi(value);
            if (time_in_seconds <= 0)
            {
                switch_power(0);
                return 1;
            }
            return 1;
        }
        catch (exception e)
        {
            cout << "error";
            return 0;
        }
    }
    else if (name == "poweron")
    {
        // if ()
        switch_power(!isOn);
    }
    else if (name == "addwater")
    {
        fillWaterTank(2);
    }
    return 0;
}

string AirPurifier::get(std::string name)
{
    if (name == "all")
    {
        return getAll();
    }
    else if (name == "airquality")
    {
        return to_string(get_air_quality());
    }
    else if (name == "humidity")
    {
        return to_string(get_humidity_level());
    }
    else
    {
        return "";
    }
}

string AirPurifier::getAll()

{
    string result = "";
    result += to_string(isOn) + "\n" + to_string(airflow_level) + "\n" + to_string(humidity_level) + "\n";
    // result += to_string(isOn) + "\n";
    return result;
}
