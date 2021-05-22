// // Defining the class of the AirPurifier. It should model the entire configuration of the AirPurifier

// #include <signal.h>

// #include <src/AirPurifier.h>
// // char *MyGetValue(int v, char *tmp)
// // {
// //     return tmp[v];
// // }
// // #define ENUM_MAP(type, strings)             \
// //     char *getStringValue(const type &T)     \
// //     {                                       \
// //         return MyGetValue((int)T, strings); \
// //     }

// using namespace std;

// class AirPurifier
// {
// private:
//     // enum CommandsCode
//     // {
//     //     airflow,
//     //     humidity
//     // };

//     // const int COMMANDS_LENGTH = 2;
//     // const char *commandsName[2] = {"airflow",
//     //                                "humidity"};

//     // boost::unordered_map<CommandsCode, const char *> MyMap = boost::

//     enum Power
//     {
//         Off,
//         Low,
//         Medium,
//         High,
//         Auto
//     };
//     Power airflow_level;
//     Power humidity_level;

// public:
//     explicit AirPurifier()
//     {
//     }

//     // Setting the value for one of the settings. Hardcoded for the defrosting option
//     int set(std::string name, std::string value)
//     {
//         name = boost::algorithm::to_lower(name);
//         value = boost::algorithm::to_lower(value);
//         if (name == "airflow")
//         {
//             try
//             {
//                 int power_int = stoi(value);
//                 if (!(power_int >= Off && power_int <= (int)Auto))
//                     return 0;
//                 Power power = static_cast<Power>(power_int);
//                 airflow_level = power;
//                 return 1;
//             }
//             catch (exception e)
//             {
//                 cout << "error";
//                 return 0;
//             }
//         }
//         else if (name == "humiditylevel")
//         {
//             try
//             {
//                 int power_int = stoi(value);
//                 if (!(power_int >= Off && power_int <= (int)Auto))
//                     return 0;
//                 Power power = static_cast<Power>(power_int);
//                 humidity_level = power;
//                 return 1;
//             }
//             catch (exception e)
//             {
//                 cout << "error";
//                 return 0;
//             }
//         }
//         return 0;
//     }

//     // Getter
//     string get(std::string name)
//     {
//         if (name == "defrost")
//         {
//             return std::to_string(defrost.value);
//         }
//         else
//         {
//             return "";
//         }
//     }

// private:
//     enum PurifierOptions
//         // Defining and instantiating settings.
//         struct boolSetting
//     {
//         std::string name;
//         bool value;
//     }
//     defrost;
// };
