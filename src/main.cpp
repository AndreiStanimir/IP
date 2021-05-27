/*
   Rares Cristea, 12.03.2021
   Example of a REST endpoint with routing
   using Mathieu Stefani's example, 07 février 2016
*/

#include <algorithm>
#include <fstream>
#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>

#include <boost/algorithm/string.hpp>

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/asio.hpp>

#include <signal.h>

// #include "include/AirPurifier.h"
//#include "include/MqttClientHandler.h"
using namespace std;
using namespace Pistache;

// General advice: pay atetntion to the namespaces that you use in various contexts. Could prevent headaches.

// This is just a helper function to preety-print the Cookies that one of the enpoints shall receive.
void printCookies(const Http::Request &req)
{
    auto cookies = req.cookies();
    std::cout << "Cookies: [" << std::endl;
    const std::string indent(4, ' ');
    for (const auto &c : cookies)
    {
        std::cout << indent << c.name << " = " << c.value << std::endl;
    }
    std::cout << "]" << std::endl;
}

// Some generic namespace, with a simple function we could use to test the creation of the endpoints.
namespace Generic
{

    void handleReady(const Rest::Request &, Http::ResponseWriter response)
    {
        response.send(Http::Code::Ok, "1");
    }

}
namespace gregorian = boost::gregorian;
namespace posix_time = boost::posix_time;
namespace asio = boost::asio;

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
        Maximum
    };
    Power airflow_level;
    Power humidity_level;
    bool isOn;
    bool autoPurify;
    float waterTank;
    unsigned short air_quality;
    unsigned short air_humidity;

#define THRESHOLDS_LENGTH 5
    int PURITY_THRESHOLD[THRESHOLDS_LENGTH] = {95, 80, 50, 30, 5};

    static AirPurifier *instance;

public:
    AirPurifier()
    {
        airflow_level = Off;
        humidity_level = Off;
        isOn = false;
        air_quality = 0;
        air_humidity = get_humidity_level();
        autoPurify = false;
        waterTank = 0;
    }
    Power getAirflow()
    {
        return airflow_level;
    }
    bool isAuto()
    {
        return autoPurify;
    }
    bool updateAutoAirflow()
    {
        int quality = get_air_quality();
        for (int i = 0; i < THRESHOLDS_LENGTH; i++)
        {

            if (quality > PURITY_THRESHOLD[i])
            {
                if (airflow_level != (Power)i)
                {
                    airflow_level = (Power)i;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }

    static AirPurifier &getInstance()
    {
        static AirPurifier i;
        return i;
    }
    bool switch_power(bool on)
    {
        isOn = on;
        return 1;
    }
    int fillWaterTank(float water)
    {
        if (water > 0)
        {
            waterTank += water;
            waterTank = min(5.0f, waterTank);
            return 1;
        }
        return 0;
    }
    int get_air_quality()
    {
        air_quality = air_quality + rand() % 12 - 4;
        air_quality=max(air_quality,(unsigned short)0);
        air_quality=min(air_quality,(unsigned short)100);
        return air_quality;
    }
    int get_humidity_level()
    {
        return 10;
    }
    float getWaterTankLevel()
    {
        return waterTank;
    }

    bool connectToWifi(std::string ip, std::string password)
    {
        cout << "Connected to wifi :" << ip;
        return true;
    }
    // Setting the value for one of the settings. Hardcoded for the defrosting option
    int set(std::string name, std::string value)
    {
        boost::algorithm::to_lower(name);
        boost::algorithm::to_lower(value);
        cout << name << endl;

        if (name == "poweron")
        {
            // if ()
            switch_power(value != "0"); // convert value to bool
            return 1;
        }
        if (!isOn)
        {
            cout << "device is not on\n";
            return 0;
        }
        if (name == "airflow")
        {
            try
            {
                int power_int = stoi(value);
                if (!(power_int >= Off && power_int <= (int)Maximum))
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
                if (!(power_int >= Off && power_int <= (int)Maximum))
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
            return 1;
        }
        else if (name == "addwater")
        {
            try
            {
                fillWaterTank(2);
                return 1;
            }
            catch (exception e)
            {
                cout << "error";
                return 0;
            }
        }
        else if (name == "auto")
        {
            try
            {
                autoPurify = value != "0";
                return 1;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        return 0;
    }
    // Getter
    std::string get(std::string name)
    {
        if (!isOn)
        {
            cout << "device is not on\n";
            return 0;
        }
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

    std::string getAll()
    {
        string result = "";
        result += "power " + to_string(isOn) + "\n" + "airflow power " + to_string(airflow_level) + "\n" +
                  "humidity power " + to_string(humidity_level) + "\n" +
                  "water tank: " + to_string(waterTank) + "\n" +
                  "air quality " + to_string(get_air_quality()) + "\n" +
                  "air humidity " + to_string(get_humidity_level()) + "\n";
        std::fstream fout;
        fout.open("log.txt", std::ios_base::app);
        std::time_t t = std::time(0);
        fout << std::ctime(&t);
        fout << result;
        fout.close();
        return result;
    }
};
class AirPurifierEndpoint
{
public:
    explicit AirPurifierEndpoint(Address addr)
        : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
    {
        airpurifier = AirPurifier::getInstance();
    }

    // Initialization of the server. Additional options can be provided here
    void init(size_t thr = 2)
    {
        auto opts = Http::Endpoint::options()
                        .threads(static_cast<int>(thr));
        httpEndpoint->init(opts);
        // Server routes are loaded up
        setupRoutes();
    }

    // Server is started threaded.
    void start()
    {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serveThreaded();
    }

    // When signaled server shuts down
    void stop()
    {
        httpEndpoint->shutdown();
    }

    AirPurifier &getAirPurifier()
    {
        return airpurifier;
    }

private:
    void setupRoutes()
    {
        using namespace Rest;
        // Defining various endpoints
        // Generally say that when http://localhost:9080/ready is called, the handleReady function should be called.
        Routes::Get(router, "/ready", Routes::bind(&Generic::handleReady));
        Routes::Get(router, "/auth", Routes::bind(&AirPurifierEndpoint::doAuth, this));
        Routes::Post(router, "/settings/:settingName/:value", Routes::bind(&AirPurifierEndpoint ::setSetting, this));
        Routes::Get(router, "/settings/:settingName/", Routes::bind(&AirPurifierEndpoint::getSetting, this));
    }

    void doAuth(const Rest::Request &request, Http::ResponseWriter response)
    {
        // Function that prints cookies
        printCookies(request);
        // In the response object, it adds a cookie regarding the communications language.
        response.cookies()
            .add(Http::Cookie("lang", "en-US"));
        // Send the response
        response.send(Http::Code::Ok);
    }

    // Endpoint to configure one of the AirPurifier's settings.
    void setSetting(const Rest::Request &request, Http::ResponseWriter response)
    {
        // You don't know what the parameter content that you receive is, but you should
        // try to cast it to some data structure. Here, I cast the settingName to string.
        auto settingName = request.param(":settingName").as<std::string>();

        // This is a guard that prevents editing the same value by two concurent threads.
        Guard guard(microwaveLock);

        std::string val = "";
        if (request.hasParam(":value"))
        {
            auto value = request.param(":value");
            val = value.as<string>();
        }

        // Setting the microwave's setting to value
        // airpurifier = AirPurifier::getInstance();
        int setResponse = airpurifier.set(settingName, val);

        // Sending some confirmation or error response.
        if (setResponse == 1)
        {
            response.send(Http::Code::Ok, settingName + " was set to " + val);
        }
        else
        {
            response.send(Http::Code::Not_Found, settingName + " was not found and or '" + val + "' was not a valid value ");
        }
    }

    // Setting to get the settings value of one of the configurations of the AirPurifier
    void getSetting(const Rest::Request &request, Http::ResponseWriter response)
    {
        auto settingName = request.param(":settingName").as<std::string>();

        Guard guard(microwaveLock);
        // airpurifier = AirPurifier::getInstance();
        string valueSetting = airpurifier.get(settingName);

        if (valueSetting != "")
        {

            // In this response I also add a couple of headers, describing the server that sent this response, and the way the content is formatted.
            using namespace Http;
            response.headers()
                .add<Header::Server>("pistache/0.1")
                .add<Header::ContentType>(MIME(Text, Plain));
            cout << valueSetting;
            response.send(Http::Code::Ok, settingName + " is " + valueSetting);
        }
        else
        {
            response.send(Http::Code::Not_Found, settingName + " was not found");
        }
    }

    // Create the lock which prevents concurrent editing of the same variable
    using Lock = std::mutex;
    using Guard = std::lock_guard<Lock>;
    Lock microwaveLock;

    // Instance of the air purifier model

    AirPurifier airpurifier;

    // Defining the httpEndpoint and a router.
    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;
};

void httpServer(AirPurifierEndpoint *airpurifierEndpoint, Address addr, Port port, int thr, sigset_t signals)
{

    // Initialize and start the server
    airpurifierEndpoint->init(thr);
    airpurifierEndpoint->start();

    // Code that waits for the shutdown sinal for the server
    int signal = 0;
    int status = sigwait(&signals, &signal);
    if (status == 0)
    {
        std::cout << "received signal " << signal << std::endl;
    }
    else
    {
        std::cerr << "sigwait returns " << status << std::endl;
    }

    airpurifierEndpoint->stop();
}

void updateAutoAirflowTask(AirPurifierEndpoint *airPurifierEndpoint, sigset_t signals)
{
    AirPurifier &airpurifier = airPurifierEndpoint->getAirPurifier();
    while (true)
    {
        if (airpurifier.isAuto())
        {
            cout << "Current air quality: " << airpurifier.get_air_quality() << "\n";
            bool hasUpdated = airpurifier.updateAutoAirflow();
            if (hasUpdated)
            {
                cout << "Airflow speed updated to " + to_string(airpurifier.getAirflow()) + "\n";
            }
        }
        //sigset_t signals;
        siginfo_t *signal;
        timespec time;
        time.tv_sec = 1;
        time.tv_nsec = 0;
        int status = sigtimedwait(&signals, signal, &time);
        if (status == 0)
        {
            std::cout << "received signal " << signal << std::endl;
            // break;
        }
        else
        {
            //std::cerr << "sigwait returns " << status << std::endl;
            if(status==2)
                break;
        }
        sleep(1);
    }
}
int main(int argc, char *argv[])
{
    AirPurifier::getInstance();

    // This code is needed for gracefull shutdown of the server when no longer needed.
    sigset_t signals;
    if (sigemptyset(&signals) != 0 || sigaddset(&signals, SIGTERM) != 0 || sigaddset(&signals, SIGINT) != 0 || sigaddset(&signals, SIGHUP) != 0 || pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0)
    {
        perror("install signal handler failed");
        return 1;
    }
    // Set a port on which your server to communicate
    Port port(9081);

    // Number of threads used by the server
    int thr = 2;

    if (argc >= 2)
    {
        port = static_cast<uint16_t>(std::stol(argv[1]));

        if (argc == 3)
            thr = std::stoi(argv[2]);
    }

    Address addr(Ipv4::any(), port);

    // Instance of the class that defines what the server can do.
    AirPurifierEndpoint *airPurifier = new AirPurifierEndpoint(addr);

    std::thread thread_htpp(httpServer, airPurifier, addr, port, thr, signals);

    std::thread threadUpdateAutoAirflow(updateAutoAirflowTask, airPurifier,signals);

    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << thr << " threads" << endl;

    thread_htpp.join();
    threadUpdateAutoAirflow.join();
}
