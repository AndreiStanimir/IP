#ifndef __AIRPURIFIER_H__
#define __AIRPURIFIER_H__

#include <algorithm>
#include <vector>

#include <boost/algorithm/string.hpp>

#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>

using namespace std;

class AirPurifier
{
private:
    // asio::io_service io_service_;
    // asio::deadline_timer timerTurnOn;
    enum Power
    {
        Off,
        Low,
        Medium,
        High,
        Auto
    };
    Power airflow_level;
    Power humidity_level;
    bool isOn;
    float waterTank;
    unsigned short air_quality;
    unsigned short air_humidity;

    static AirPurifier *instance;
    AirPurifier()
    {
        airflow_level = Off;
        humidity_level = Off;
        isOn = false;
        air_quality = get_air_quality();
        air_humidity = get_humidity_level();
        waterTank = 0;
    }

public:
    static AirPurifier *getInstance();
    bool switch_power(bool on);

    int fillWaterTank(float water);

    int get_air_quality();
    int get_humidity_level();
    float getWaterTankLevel();
    bool set_humidity(string humidity);
    bool connectToWifi(string ip, string password);

    // Setting the value for one of the settings. Hardcoded for the defrosting option
    int set(std::string name, std::string value);

    // Getter
    string get(std::string name);
    string getAll();
};
#endif // __AIRPURIFIER_H__