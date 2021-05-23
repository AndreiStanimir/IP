#include <algorithm>
#include <vector>

// #include <boost/assign/list_of.hpp>
// #include <boost/unordered_map.hpp>

#include <boost/algorithm/string.hpp>

#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
class AirPurifier
{
private:
    // enum CommandsCode
    // {
    //     airflow,
    //     humidity
    // };

    // const int COMMANDS_LENGTH = 2;
    // const char *commandsName[2] = {"airflow",
    //                                "humidity"};

    // boost::unordered_map<CommandsCode, const char *> MyMap = boost::

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
    unsigned short air_quality;
    unsigned short air_humidity;

public:
    bool switch_power(bool on)
    {
        isOn = on;
        return 1;
    }
    int get_air_quality()
    {
        return 42;
    }
    int get_humidity_level()
    {
        return 42;
    }
    explicit AirPurifier()
    {
        airflow_level = Off;
        humidity_level = Off;
        isOn = false;
        air_quality = get_air_quality();
        air_humidity = get_humidity_level();
    }

    // Setting the value for one of the settings. Hardcoded for the defrosting option
    int set(std::string name, std::string value)
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
        return 0;
    }

    // Getter
    string get(std::string name)
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
    string getAll()
    {
        string result = "";
        result += to_string(isOn) + "\n" + to_string(airflow_level) + "\n" + to_string(humidity_level) + "\n";
        // result += to_string(isOn) + "\n";
        return result;
    }
};