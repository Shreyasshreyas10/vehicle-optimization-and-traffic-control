#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <random>
#include <stdexcept>
#include <functional>
#include <map>
#include <queue>
#include <limits>


using namespace std;
const int INF = numeric_limits<int>::max();
// Structure to represent different zones in a city
struct Zone {
    string name; // Name of the zone
    double length; // Length of the zone
    double width;  // Width of the zone
    string type;   // Type of zone (e.g., "Park", "Residential", "Commercial", "Road")
};


std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == std::string::npos || last == std::string::npos)
               ? ""
               : str.substr(first, last - first + 1);

}
double generateRandomSpeed(double min, double max)
{
    return min + (double)rand() / RAND_MAX * (max - min);
}

// Structure to hold parsed data
struct DataEntry {
    vector<string> fields;
};

struct Signal
 {
    string id;
    string status;
};
std::string correctUsername = "admin";
std::string correctPassword = "password123";

// Function to check user credentials
bool authenticateUser(const std::string &username, const std::string &password)
{
    return username == correctUsername && password == correctPassword;
}

string trimWhitespace(string str)
{
    size_t start = 0, end = str.length() - 1;

    // Remove leading whitespace
    while (start < str.length() && isspace(str[start]))
        {
        start++;
    }

    // Remove trailing whitespace
    while (end > start && isspace(str[end]))
        {
        end--;
    }

    return str.substr(start, end - start + 1);
}



string generateRandomID()
{
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string id(5, '0');
    for (int i = 0; i < 5; ++i)
    {
        id[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return id;
}

// Vehicle Class


class Vehicle
{
public:
    string id;
    string type;
    double speed;
    int violations;

    Vehicle(const string& vehicle_id, const string& vehicle_type)
        : id(vehicle_id), type(vehicle_type), speed(0.0), violations(0) {}

    void updateSpeed(double new_speed)
    {
        speed = new_speed;
    }
};

// Traffic Management Class


class TrafficManagement
{
private:
    vector<Vehicle> vehicles;
    unordered_map<string, string> traffic_signals;
    unordered_map<string, int> pedestrian_signals;
    const double speed_limit = 60.0;
    const int max_violations = 5;

public:
    TrafficManagement()
    {
        srand(time(0)); // Seed for random generation
    }

    void addVehicle(const string& vehicle_id, const string& vehicle_type)
    {
        vehicles.emplace_back(vehicle_id, vehicle_type);
    }

    void removeVehicle(const string& vehicle_id)
    {
        vehicles.erase(
            remove_if(vehicles.begin(), vehicles.end(),
                      [&](const Vehicle& v) { return v.id == vehicle_id; }),
            vehicles.end());
    }

    void setSignal(const string& signal_id, const string& status)
    {
        traffic_signals[signal_id] = status;
    }

 void logSignalStatusCheck(const string& signal_id, const string& status)
 {
    ofstream log_file("signal_status_log.txt", ios_base::app); // Open in append mode
    if (log_file.is_open())
        {
        // Log the signal status check
        log_file << "Signal ID: " << signal_id << " | Status: " << status << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        log_file.close();
    }
     else
    {
        cerr << "Unable to open log file" << endl;
    }

    // Validate the signal ID (assuming it should be alphanumeric)


    if (signal_id.empty() || !all_of(signal_id.begin(), signal_id.end(), ::isalnum))
        {
        cerr << "Invalid signal ID: " << signal_id << endl;
        return;
    }

    // Validate the status (assuming valid statuses are "Green", "Yellow", "Red")

    vector<string> valid_statuses = {"Green", "Yellow", "Red"};
    if (find(valid_statuses.begin(), valid_statuses.end(), status) == valid_statuses.end())
        {
        cerr << "Invalid status: " << status << endl;
        return;
    }

    // Log validation results

    ofstream validation_log_file("validation_log.txt", ios_base::app); // Open in append mode
    if (validation_log_file.is_open())
        {
        validation_log_file << "Validation successful for Signal ID: " << signal_id << " with Status: " << status << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        validation_log_file.close();
    }
    else
    {
        cerr << "Unable to open validation log file" << endl;
    }
}

string getSignalStatus(const string& signal_id)
{
    string status;
    if (traffic_signals.find(signal_id) != traffic_signals.end())
    {
        status = traffic_signals[signal_id];
    }
    else
    {
        status = "Signal not found";
    }
   // Log the signal status check

    logSignalStatusCheck(signal_id, status);
    return status;
}
  void logPedestrianSignalChange(const string& signal_id, int state)
  {
    // Open log file

    ofstream log_file("pedestrian_signal_log.txt", ios_base::app); // Open in append mode
    if (log_file.is_open())
        {
        // Log the signal state change

        log_file << "Signal ID: " << signal_id << " | New State: " << (state == 1 ? "Walk" : "Stop") << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        log_file.close();
    }
     else
     {
        cerr << "Unable to open log file" << endl;
    }

    // Validate the signal state

    if (state != 1 && state != 0)
        {
        cerr << "Invalid state: " << state << ". Must be 0 (Stop) or 1 (Walk)." << endl;
        return;
    }

    // Open a detailed log file for additional logging

    ofstream detailed_log_file("detailed_pedestrian_signal_log.txt", ios_base::app); // Open in append mode
    if (detailed_log_file.is_open())
        {
        detailed_log_file << "Detailed Log - Signal ID: " << signal_id << " | State: " << (state == 1 ? "Walk" : "Stop") << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        detailed_log_file.close();
    } else {
        cerr << "Unable to open detailed log file" << endl;
    }

    // Notify the monitoring system (simulated)

    cout << "Monitoring system notified: Signal ID: " << signal_id << " changed to " << (state == 1 ? "Walk" : "Stop") << endl;
}
void setPedestrianSignal(const string& signal_id, int state)
{
    pedestrian_signals[signal_id] = state;
    logPedestrianSignalChange(signal_id, state); // Log the signal change
}


    void addViolation(const string& vehicle_id, const string& violation_type)
     {
    cout << "Violation recorded for Vehicle ID: " << vehicle_id
         << " | Type: " << violation_type << endl;

    // Open log file in append mode

    ofstream log_file("violation_log.txt", ios_base::app);
    if (!log_file.is_open()) {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Get the current time

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    // Log the violation details to the file

    log_file << "Violation recorded for Vehicle ID: " << vehicle_id
             << " | Type: " << violation_type
             << " | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    // Update the violation count for the vehicle

    for (auto& vehicle : vehicles)
    {
        if (vehicle.id == vehicle_id)
            {
            vehicle.violations++;
            log_file << "Vehicle ID: " << vehicle.id << " now has " << vehicle.violations << " violations." << endl;

            // Check if the vehicle exceeded the violation limit

            if (vehicle.violations >= max_violations)
                {
                cout << "Vehicle ID: " << vehicle_id
                     << " exceeded violation limit. Removing from system." << endl;

                log_file << "Vehicle ID: " << vehicle_id
                         << " exceeded violation limit. Removing from system." << endl;

                removeVehicle(vehicle_id);
            }
            break;
        }
    }

    log_file << "---------------------------------------" << endl;
    log_file.close();
}

   void checkSpeedLimit(const string& vehicle_id, double speed)
    {
    ofstream log_file("speed_limit_log.txt", ios_base::app); // Open log file in append mode
    bool vehicle_found = false;

    for (auto& vehicle : vehicles)
    {
        if (vehicle.id == vehicle_id)
            {
            vehicle.updateSpeed(speed);
            vehicle_found = true;

            // Log the speed update

            if (log_file.is_open())
                {
                log_file << "Vehicle ID: " << vehicle_id << " | New Speed: " << speed
                         << " km/h | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
            }
             else
            {
                cerr << "Unable to open log file." << endl;
            }

            if (speed > speed_limit)
                {
                cout << "Vehicle ID: " << vehicle_id
                     << " exceeded speed limit!" << endl;

                // Log the speed violation

                if (log_file.is_open())
                    {
                    log_file << "Violation: Speeding | Vehicle ID: " << vehicle_id
                             << " | Speed: " << speed << " km/h | Speed Limit: " << speed_limit
                             << " km/h | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
                }

                addViolation(vehicle_id, "Speeding");
            }
            break;
        }
    }

    if (!vehicle_found)
        {
        cerr << "Vehicle ID: " << vehicle_id << " not found." << endl;
        if (log_file.is_open())
            {
            log_file << "Error: Vehicle ID " << vehicle_id << " not found | Timestamp: "
                     << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        }
    }

    log_file.close(); // Close the log file
}

    void prioritizeEmergency(const string& vehicle_id)
     {
        cout << "Emergency vehicle detected. Granting priority to Vehicle ID: "<< vehicle_id << endl;
        for (auto& signal : traffic_signals)
            {
            signal.second = "Green"; // Turn all signals green for emergency vehicles
        }
    }

   void simulatePedestrianCrossing(const string& signal_id, int walk_time, int stop_time)
   {
    // Open log file in append mode

    ofstream log_file("pedestrian_crossing_log.txt", ios_base::app);
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Get the current time

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    // Log the start of the pedestrian crossing

    log_file << "Pedestrian Crossing Start | Signal ID: " << signal_id
             << " | Status: Walk | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    setPedestrianSignal(signal_id, 1); // Set pedestrian signal to "Walk"
    for (int i = 0; i < walk_time; i++)
        {
        cout << "Pedestrian Signal ID: " << signal_id
             << " | Status: Walk | Time left: " << (walk_time - i)
             << " seconds" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Log the change to "Stop" signal

    now = chrono::system_clock::now();
    now_c = chrono::system_clock::to_time_t(now);
    log_file << "Pedestrian Signal Change | Signal ID: " << signal_id
             << " | New Status: Stop | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    setPedestrianSignal(signal_id, 0); // Set pedestrian signal to "Stop"
    for (int i = 0; i < stop_time; i++)
        {
        cout << "Pedestrian Signal ID: " << signal_id
             << " | Status: Stop | Time left: " << (stop_time - i)
             << " seconds" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Log the end of the pedestrian crossing

    now = chrono::system_clock::now();
    now_c = chrono::system_clock::to_time_t(now);
    log_file << "Pedestrian Crossing End | Signal ID: " << signal_id
             << " | Status: Stop | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    log_file << "---------------------------------------" << endl;
    log_file.close();
}
    void viewViolations() const
     {
    cout << "Traffic Violations:" << endl;

    // Open log file

    ofstream log_file("violations_log.txt", ios_base::app); // Open in append mode
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file" << endl;
    }

    // Log the start of the view violations process

    if (log_file.is_open())
        {
        log_file << "Starting view violations"
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
    }

    // Create a copy of vehicles to sort by violations

    vector<Vehicle> sorted_vehicles = vehicles;

    // Sort vehicles by number of violations in descending order

    sort(sorted_vehicles.begin(), sorted_vehicles.end(), [](const Vehicle& a, const Vehicle& b)
         {
        return a.violations > b.violations;
    }
    );

    for (const auto& vehicle : sorted_vehicles)
        {
        if (vehicle.violations > 0)
            {
            cout << "Vehicle ID: " << vehicle.id
                 << " | Violations: " << vehicle.violations << endl;

            // Log each vehicle's violations

            if (log_file.is_open())
                {
                log_file << "Vehicle ID: " << vehicle.id
                         << " | Violations: " << vehicle.violations
                         << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
            }
        }
    }

    // Log the end of the view violations process

    if (log_file.is_open())
        {
        log_file << "Completed view violations"
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        log_file.close();
    }
}

    void signalTimer(const string& signal_id, int green_time, int red_time)
     {
    cout << "Starting signal timer for Signal ID: " << signal_id << endl;

    // Open log file in append mode

    ofstream log_file("signal_timer_log.txt", ios_base::app);
    if (!log_file.is_open()) {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Get the current time

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    // Log the start of the signal timer

    log_file << "Signal Timer Start | Signal ID: " << signal_id
             << " | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    // Green signal timer

    for (int i = 0; i < green_time; i++)
        {
        cout << "Signal ID: " << signal_id << " | Status: Green | Time left: "
             << (green_time - i) << " seconds" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    setSignal(signal_id, "Red");

    // Log the change to red signal

    now = chrono::system_clock::now();
    now_c = chrono::system_clock::to_time_t(now);
    log_file << "Signal Change | Signal ID: " << signal_id
             << " | New Status: Red | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    // Red signal timer

    for (int i = 0; i < red_time; i++)
        {
        cout << "Signal ID: " << signal_id << " | Status: Red | Time left: "
             << (red_time - i) << " seconds" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    setSignal(signal_id, "Green");

    // Log the change to green signal

    now = chrono::system_clock::now();
    now_c = chrono::system_clock::to_time_t(now);
    log_file << "Signal Change | Signal ID: " << signal_id
             << " | New Status: Green | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    log_file << "---------------------------------------" << endl;
    log_file.close();
}
void generateReport() const
 {
    cout << "Traffic Report:" << endl;
    cout << "Total Vehicles: " << vehicles.size() << endl;
    cout << "Traffic Signals: " << traffic_signals.size() << endl;
    cout << "Pedestrian Signals: " << pedestrian_signals.size() << endl;
    cout << "Violations: " << endl;
    for (const auto& vehicle : vehicles)
        {
        cout << "Vehicle ID: " << vehicle.id << " | Type: " << vehicle.type
             << " | Speed: " << vehicle.speed << " km/h"
             << " | Violations: " << vehicle.violations << endl;
    }

    // Open log file in append mode

    ofstream log_file("traffic_report_log.txt", ios_base::app);
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Get the current time

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    // Log the report details to the file

    log_file << "Traffic Report | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;
    log_file << "Total Vehicles: " << vehicles.size() << endl;
    log_file << "Traffic Signals: " << traffic_signals.size() << endl;
    log_file << "Pedestrian Signals: " << pedestrian_signals.size() << endl;
    log_file << "Violations: " << endl;
    for (const auto& vehicle : vehicles)
        {
        log_file << "Vehicle ID: " << vehicle.id << " | Type: " << vehicle.type
                 << " | Speed: " << vehicle.speed << " km/h"
                 << " | Violations: " << vehicle.violations << endl;
    }
    log_file << "---------------------------------------" << endl;
    log_file.close();
}

    void simulateTraffic()
    {
    cout << "Simulating traffic flow..." << endl;

    // Open log file in append mode

    ofstream log_file("traffic_simulation_log.txt", ios_base::app);
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Get the current time

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    // Log the start of the simulation

    log_file << "Traffic Simulation | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    // Simulate traffic flow

    for (auto& vehicle : vehicles)
        {
        double speed = generateRandomSpeed(20.0, 120.0); // Random speed between 20 and 120 km/h
        cout << "Vehicle ID: " << vehicle.id << " | Speed: " << speed << " km/h" << endl;

        // Log the vehicle speed

        log_file << "Vehicle ID: " << vehicle.id
                 << " | Speed: " << speed << " km/h"
                 << " | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

        checkSpeedLimit(vehicle.id, speed);
    }

    log_file << "---------------------------------------" << endl;
    log_file.close();
}

  void monitorTrafficDensity()
  {
    cout << "Monitoring traffic density..." << endl;

    // Open log file for traffic density monitoring

    ofstream log_file("traffic_density_log.txt", ios_base::app); // Open in append mode
    if (!log_file.is_open())
        {
        cerr << "Unable to open traffic density log file" << endl;
    }

    // Log the start of the traffic density monitoring

    if (log_file.is_open())
        {
        log_file << "Starting traffic density monitoring"
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
    }

    unordered_map<string, int> vehicle_count;
    for (const auto& vehicle : vehicles)
        {
        vehicle_count[vehicle.type]++;
    }

    for (const auto& entry : vehicle_count)
        {
        cout << "Vehicle Type: " << entry.first << " | Count: " << entry.second << endl;

        // Log each vehicle type count

        if (log_file.is_open())
            {
            log_file << "Vehicle Type: " << entry.first << " | Count: " << entry.second
                     << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        }
    }

    // Notify the monitoring system (simulated)

    cout << "Monitoring system notified about traffic density." << endl;

    // Log the end of the traffic density monitoring

    if (log_file.is_open())
        {
        log_file << "Completed traffic density monitoring"
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        log_file.close();
    }
}

    void trackVehicle(const string& vehicle_id)
    {
    cout << "Tracking Vehicle ID: " << vehicle_id << endl;

    // Open log file in append mode

    ofstream log_file("vehicle_tracking_log.txt", ios_base::app);
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Get the current time

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    for (const auto& vehicle : vehicles)
    {
        if (vehicle.id == vehicle_id)
            {
            // Log to console

            cout << "Vehicle ID: " << vehicle.id << " | Type: " << vehicle.type
                 << " | Speed: " << vehicle.speed << " km/h"
                 << " | Violations: " << vehicle.violations << endl;

            // Log to file

            log_file << "Tracking Vehicle ID: " << vehicle.id
                     << " | Type: " << vehicle.type
                     << " | Speed: " << vehicle.speed << " km/h"
                     << " | Violations: " << vehicle.violations
                     << " | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

            log_file.close();
            return;
        }
    }

    // Log to console if vehicle not found

    cout << "Vehicle ID: " << vehicle_id << " not found." << endl;

    // Log to file if vehicle not found

    log_file << "Vehicle ID: " << vehicle_id << " not found"
             << " | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    log_file.close();
}
   void emergencyServices(const string& vehicle_id)
   {
    cout << "Emergency detected for Vehicle ID: " << vehicle_id << endl;

    // Open log file for emergency services

    ofstream log_file("emergency_services_log.txt", ios_base::app); // Open in append mode
    if (!log_file.is_open())
        {
        cerr << "Unable to open emergency services log file" << endl;
    }

    // Log the start of the emergency services

    if (log_file.is_open())
        {
        log_file << "Emergency detected for Vehicle ID: " << vehicle_id
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
    }

    // Call the function to prioritize the emergency

    prioritizeEmergency(vehicle_id);

    // Log the prioritization action

    if (log_file.is_open())
        {
        log_file << "Emergency prioritized for Vehicle ID: " << vehicle_id
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
    }

    // Notify the monitoring system (simulated)

    cout << "Monitoring system notified: Emergency detected for Vehicle ID: " << vehicle_id << endl;

    // Log the notification action

    if (log_file.is_open())
        {
        log_file << "Monitoring system notified for Vehicle ID: " << vehicle_id
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        log_file.close();
    }

    // Generate an emergency report (simulated)

    cout << "Generating emergency report for Vehicle ID: " << vehicle_id << endl;

    // Log the emergency report generation

    ofstream report_file("emergency_report.txt", ios_base::app); // Open in append mode
    if (report_file.is_open())
        {
        report_file << "Emergency report generated for Vehicle ID: " << vehicle_id
                    << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        report_file.close();
    }
     else
    {
        cerr << "Unable to open emergency report file" << endl;
    }
}
   void dynamicSignalAdjustment()
   {
    cout << "Adjusting signals dynamically based on traffic flow..." << endl;

    // Open log file in append mode

    ofstream log_file("dynamic_signal_adjustment_log.txt", ios_base::app);
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Log the start of the adjustment process

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    log_file << "Dynamic Signal Adjustment | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    // Adjust signals dynamically

    for (auto& signal : traffic_signals)
     {
        if (rand() % 2 == 0)
            {
            signal.second = "Green";
            log_file << "Signal ID: " << signal.first << " | New Status: Green" << endl;
        }
        else
         {
            signal.second = "Red";
            log_file << "Signal ID: " << signal.first << " | New Status: Red" << endl;
        }
    }

    log_file << "---------------------------------------" << endl;
    log_file.close();
}

   void vehicleEntryExitLog()
   {
    cout << "Logging vehicle entry and exit times..." << endl;
    ofstream log_file("vehicle_entry_exit_log.txt", ios_base::app); // Open log file in append mode

    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
        return;
    }

    for (const auto& vehicle : vehicles)
        {
        int hour = rand() % 24;
        int minute = rand() % 60;

        // Log to console

        cout << "Vehicle ID: " << vehicle.id << " entered at "
             << setw(2) << setfill('0') << hour << ":"
             << setw(2) << setfill('0') << minute << endl;

        // Log to file

        log_file << "Vehicle ID: " << vehicle.id << " entered at "
                 << setw(2) << setfill('0') << hour << ":"
                 << setw(2) << setfill('0') << minute << " on "
                 << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
    }

    log_file.close();
}

    void simulateAccidents()
    {
    cout << "Simulating accidents..." << endl;
    if (!vehicles.empty())
        {
        // Randomly select a vehicle index

        int index = rand() % vehicles.size();
        string vehicle_id = vehicles[index].id;

        // Log the accident to the console

        cout << "Accident detected for Vehicle ID: " << vehicle_id << endl;

        // Add the violation for the vehicle

        addViolation(vehicle_id, "Accident");

        // Open the log file in append mode

        ofstream log_file("accident_log.txt", ios_base::app);
        if (!log_file.is_open())
            {
            cerr << "Unable to open log file." << endl;
            return;
        }

        // Get the current time

        auto now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);

        // Log the accident details to the file

        log_file << "Accident detected for Vehicle ID: " << vehicle_id
                 << " | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

        // Close the log file

        log_file.close();
    }
    else
     {
        cout << "No vehicles available to simulate accidents." << endl;
    }
}
  void simulateWeatherConditions()
   {
    cout << "Simulating different weather conditions..." << endl;

    // Extended weather conditions

    vector<string> weather_conditions = {"Clear", "Rainy", "Foggy", "Snowy", "Stormy", "Windy", "Hail"};
    string current_condition = weather_conditions[rand() % weather_conditions.size()];

    // Log the current weather condition to a file

    ofstream log_file("weather_conditions_log.txt", ios_base::app); // Open in append mode
    if (log_file.is_open())
        {
        log_file << "Current weather condition: " << current_condition
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
    }
     else
    {
        cerr << "Unable to open log file." << endl;
    }

    cout << "Current weather condition: " << current_condition << endl;
    for (auto& vehicle : vehicles)
        {
        if (current_condition == "Rainy" || current_condition == "Foggy" || current_condition == "Snowy" ||
            current_condition == "Stormy" || current_condition == "Windy" || current_condition == "Hail")
            {
            double reduced_speed = generateRandomSpeed(10.0, 50.0);
            cout << "Vehicle ID: " << vehicle.id << " | Reduced Speed: " << reduced_speed << " km/h due to " << current_condition << endl;

            // Log the speed reduction to the file

            if (log_file.is_open())
                {
                log_file << "Vehicle ID: " << vehicle.id << " | Reduced Speed: " << reduced_speed << " km/h due to " << current_condition
                         << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
            }

            vehicle.updateSpeed(reduced_speed);
        }
    }

    if (log_file.is_open())
        {
        log_file.close();
    }
}
void manageParking()
{
    cout << "Managing parking spaces..." << endl;

    // Open log file

    ofstream log_file("parking_management_log.txt", ios_base::app); // Open in append mode
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
    }

    unordered_map<string, int> parking;
    int total_spaces_occupied = 0;

    for (const auto& vehicle : vehicles)
        {
        parking[vehicle.type]++;
        total_spaces_occupied++;

        // Log each vehicle's parking information

        if (log_file.is_open())
            {
            log_file << "Vehicle Type: " << vehicle.type << " | Vehicle ID: " << vehicle.id
                     << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        }
    }

    for (const auto& entry : parking)
        {
        cout << "Parking for Vehicle Type: " << entry.first << " | Spaces Occupied: " << entry.second << endl;

        // Log the parking summary for each vehicle type


        if (log_file.is_open())
            {
            log_file << "Parking Summary - Vehicle Type: " << entry.first
                     << " | Spaces Occupied: " << entry.second
                     << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        }
    }

    cout << "Total parking spaces occupied: " << total_spaces_occupied << endl;

    // Log the total parking spaces occupied


    if (log_file.is_open())
        {
        log_file << "Total parking spaces occupied: " << total_spaces_occupied
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        log_file.close();
    }
}
void emergencyVehicleAlert(const string& vehicle_id)
 {
    cout << "Emergency vehicle alert for Vehicle ID: " << vehicle_id << endl;

    // Open log file

    ofstream log_file("emergency_vehicle_log.txt", ios_base::app); // Open in append mode
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
    }

    // Log the emergency alert

    if (log_file.is_open())
        {
        log_file << "Emergency Vehicle ID: " << vehicle_id
                 << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
    }

    for (auto& signal : traffic_signals)
        {
        signal.second = "Green"; // Turn all signals green for emergency vehicles

        // Log the signal change

        if (log_file.is_open())
            {
            log_file << "Signal ID: " << signal.first << " | New State: Green"
                     << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        }
    }

    // Notify about the signal change

    for (const auto& signal : traffic_signals)
        {
        cout << "Signal ID: " << signal.first << " changed to Green due to emergency vehicle alert." << endl;
    }

    // Close log file

    if (log_file.is_open())
        {
        log_file.close();
    }
}

    void simulateTrafficFlow()
    {
    cout << "Simulating traffic flow..." << endl;

    // Open log file

    ofstream log_file("traffic_flow_log.txt", ios_base::app); // Open in append mode
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
    }

    // Initialize variables for metrics

    double total_speed = 0.0;
    int vehicle_count = 0;

    for (const auto& vehicle : vehicles)
        {
        double speed = generateRandomSpeed(20.0, 120.0); // Random speed between 20 and 120 km/h
        cout << "Vehicle ID: " << vehicle.id << " | Speed: " << speed << " km/h" << endl;

        // Log vehicle speed

        if (log_file.is_open())
            {
            log_file << "Vehicle ID: " << vehicle.id << " | Speed: " << speed
                     << " km/h | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        }

        checkSpeedLimit(vehicle.id, speed);

        // Update metrics

        total_speed += speed;
        vehicle_count++;
    }

    // Calculate and log average speed

    if (vehicle_count > 0)
        {
        double average_speed = total_speed / vehicle_count;
        cout << "Average Speed: " << average_speed << " km/h" << endl;

        if (log_file.is_open())
            {
            log_file << "Average Speed: " << average_speed << " km/h"
                     << " | Total Vehicles: " << vehicle_count
                     << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
        }
    }

    // Close log file

    if (log_file.is_open())
        {
        log_file.close();
    }
}
   void analyzeTrafficPatterns()
    {
    cout << "Analyzing traffic patterns..." << endl;
    unordered_map<string, vector<double>> speed_records;

    // Collect speed records for each vehicle type

    for (const auto& vehicle : vehicles)
        {
        speed_records[vehicle.type].push_back(vehicle.speed);
    }

    // Open log file in append mode

    ofstream log_file("traffic_patterns_log.txt", ios_base::app);
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Log analysis results

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    log_file << "Traffic Pattern Analysis | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    // Calculate and log average, max, and min speeds for each vehicle type

    for (const auto& entry : speed_records)
        {
        double avg_speed = accumulate(entry.second.begin(), entry.second.end(), 0.0) / entry.second.size();
        double max_speed = *max_element(entry.second.begin(), entry.second.end());
        double min_speed = *min_element(entry.second.begin(), entry.second.end());

        cout << "Vehicle Type: " << entry.first
             << " | Average Speed: " << avg_speed << " km/h"
             << " | Max Speed: " << max_speed << " km/h"
             << " | Min Speed: " << min_speed << " km/h" << endl;

        log_file << "Vehicle Type: " << entry.first
                 << " | Average Speed: " << avg_speed << " km/h"
                 << " | Max Speed: " << max_speed << " km/h"
                 << " | Min Speed: " << min_speed << " km/h" << endl;
    }

    log_file << "---------------------------------------" << endl;
    log_file.close();
}

    void optimizeSignalTimings()
     {
    cout << "Optimizing signal timings based on traffic density..." << endl;
    unordered_map<string, int> vehicle_count;

    // Count the number of vehicles of each type

    for (const auto& vehicle : vehicles)
        {
        vehicle_count[vehicle.type]++;
    }

    // Open log file in append mode

    ofstream log_file("signal_optimization_log.txt", ios_base::app);
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
        return;
    }

    // Log the start of the optimization process

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    log_file << "Signal Timing Optimization | Timestamp: " << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S") << endl;

    // Optimize signal timings based on vehicle counts

    for (auto& signal : traffic_signals)
    {
        if (vehicle_count["Car"] > 10)
            {
            signal.second = "Green"; // Longer green light for cars
            log_file << "Signal ID: " << signal.first << " | New Status: Green (Longer duration for high car density)" << endl;
        }
         else
        {
            signal.second = "Red"; // Shorter green light for fewer cars
            log_file << "Signal ID: " << signal.first << " | New Status: Red (Shorter duration for low car density)" << endl;
        }
    }

    log_file << "---------------------------------------" << endl;
    log_file.close();
}

  void enforceTrafficLaws()
  {
    cout << "Enforcing traffic laws..." << endl;

    // Open log file

    ofstream log_file("traffic_laws_enforcement_log.txt", ios_base::app); // Open in append mode
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
    }

    for (const auto& vehicle : vehicles)
     {
        if (vehicle.violations > 0)
            {
            cout << "Vehicle ID: " << vehicle.id << " has violations. Taking action." << endl;

            // Log the enforcement action

            if (log_file.is_open())
                {
                log_file << "Vehicle ID: " << vehicle.id << " has violations. Taking action."
                         << " | Violations: " << vehicle.violations
                         << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
            }

            // Issue a fine (simulated)

            double fine_amount = vehicle.violations * 100.0; // Example: $100 per violation
            cout << "Issuing fine of $" << fine_amount << " to Vehicle ID: " << vehicle.id << endl;

            // Log the fine issuance

            if (log_file.is_open())
                {
                log_file << "Issued fine of $" << fine_amount << " to Vehicle ID: " << vehicle.id
                         << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
            }

            // Notify authorities (simulated)

            cout << "Notifying authorities about Vehicle ID: " << vehicle.id << " with violations." << endl;

            // Log the notification

            if (log_file.is_open())
                {
                log_file << "Notified authorities about Vehicle ID: " << vehicle.id
                         << " | Violations: " << vehicle.violations
                         << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
            }
        }
    }

    // Close log file

    if (log_file.is_open())
        {
        log_file.close();
    }
}
void coordinateWithEmergencyServices()
{
    cout << "Coordinating with emergency services..." << endl;

    // Open log file

    ofstream log_file("emergency_services_log.txt", ios_base::app); // Open in append mode
    if (!log_file.is_open())
        {
        cerr << "Unable to open log file." << endl;
    }

    for (const auto& vehicle : vehicles)
     {
        if (vehicle.type == "Emergency")
            {
            cout << "Vehicle ID: " << vehicle.id << " is an emergency vehicle. Coordinating accordingly." << endl;

            // Log the coordination activity

            if (log_file.is_open())
                {
                log_file << "Coordinating with emergency vehicle ID: " << vehicle.id
                         << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
            }

            // Notify emergency services (simulated)

            cout << "Notifying emergency services about Vehicle ID: " << vehicle.id << endl;

            // Log the notification

            if (log_file.is_open())
                {
                log_file << "Notified emergency services about Vehicle ID: " << vehicle.id
                         << " | Timestamp: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << endl;
            }
        }
    }

    // Close log file

    if (log_file.is_open())
        {
        log_file.close();
    }
}

    void saveDataToFile(const string& filename) const
     {
        ofstream file(filename);
        if (!file.is_open())
            {
            cout << "Failed to open file: " << filename << endl;
            return;
        }
        file << "Traffic Report:" << endl;
        file << "Total Vehicles: " << vehicles.size() << endl;
        file << "Traffic Signals: " << traffic_signals.size() << endl;
        file << "Pedestrian Signals: " << pedestrian_signals.size() << endl;
        file << "Violations: " << endl;
        for (const auto& vehicle : vehicles)
            {
            file << "Vehicle ID: " << vehicle.id << " | Type: " << vehicle.type
                 << " | Speed: " << vehicle.speed << " km/h"
                 << " | Violations: " << vehicle.violations << endl;
        }
        file.close();
        cout << "Data saved to file: " << filename << endl;
    }


// Helper function to trim whitespace from both ends of a string


string trim(const string& str)
 {
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Expanded function to split a string by a delimiter


vector<string> split(const string& str, char delimiter, bool trimWhitespace = true, bool includeEmptyTokens = false)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);

    while (getline(tokenStream, token, delimiter))
     {
        if (trimWhitespace)
            {
            token = trim(token);
        }
        if (includeEmptyTokens || !token.empty())
            {
            tokens.push_back(token);
        }
    }
    return tokens;
}

// Example usage of the expanded split function

void exampleUsage()
 {
    string text = "  apple, orange, , banana ,  ";
    char delimiter = ',';

    vector<string> tokens = split(text, delimiter, true, false);

    cout << "Tokens:" << endl;
    for (const auto& token : tokens)
        {
        cout << "[" << token << "]" << endl;
    }
}

// Enhanced function to load data from file


void loadDataFromFile(const string& filename)
 {
    ifstream file(filename);
    if (!file.is_open())
        {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    vector<DataEntry> dataEntries;
    int lineCount = 0;
    int errorCount = 0;

    while (getline(file, line))
        {
        lineCount++;

        // Log the line read

        cout << "Reading line " << lineCount << ": " << line << endl;

        // Parse the line


        vector<string> fields = split(line, ',');
        if (fields.empty())
            {
            cout << "Error parsing line " << lineCount << ": " << line << endl;
            errorCount++;
            continue;
        }

        // Store the parsed data

        DataEntry entry = {fields};
        dataEntries.push_back(entry);
    }

    file.close();

    // Display statistics

    cout << "Finished reading file: " << filename << endl;
    cout << "Total lines read: " << lineCount << endl;
    cout << "Total errors: " << errorCount << endl;
    cout << "Total valid entries: " << dataEntries.size() << endl;
}
};

// Menu Function


void menu()
 {
    cout << "\nTraffic Management System Menu:" << endl;
    cout << "1. Add Vehicle" << endl;
    cout << "2. Remove Vehicle" << endl;
    cout << "3. Set Traffic Signal" << endl;
    cout << "4. View Traffic Signal Status" << endl;
    cout << "5. Add Traffic Violation" << endl;
    cout << "6. View Traffic Violations" << endl;
    cout << "7. Generate Traffic Report" << endl;
    cout << "8. Simulate Traffic" << endl;
    cout << "9. Simulate Pedestrian Crossing" << endl;
    cout << "10. Prioritize Emergency Vehicle" << endl;
    cout << "11. Monitor Traffic Density" << endl;
    cout << "12. Track Vehicle" << endl;
    cout << "13. Emergency Services" << endl;
    cout << "14. Dynamic Signal Adjustment" << endl;
    cout << "15. Vehicle Entry/Exit Log" << endl;
    cout << "16. Simulate Accidents" << endl;
    cout << "17. Simulate Weather Conditions" << endl;
    cout << "18. Manage Parking" << endl;
    cout << "19. Emergency Vehicle Alert" << endl;
    cout << "20. Simulate Traffic Flow" << endl;
    cout << "21. Analyze Traffic Patterns" << endl;
    cout << "22. Optimize Signal Timings" << endl;
    cout << "23. Enforce Traffic Laws" << endl;
    cout << "24. Coordinate with Emergency Services" << endl;
    cout << "25. Save Data to File" << endl;
    cout << "26. Load Data from File" << endl;
    cout << "27. Exit" << endl;
    cout << "Enter your choice: ";
}
void trafficControl()
 {
    TrafficManagement tm;
    int choice;

    do
        {
        menu();
        cin >> choice;
        switch (choice)
         {
            case 1:
                {
                string id, type;
                cout << "Enter Vehicle ID: ";
                cin >> id;
                cout << "Enter Vehicle Type: ";
                cin >> type;
                tm.addVehicle(id, type);
                break;
            }
            case 2:
                 {
                string id;
                cout << "Enter Vehicle ID to Remove: ";
                cin >> id;
                tm.removeVehicle(id);
                break;
            }
            case 3:
                 {
                string id, status;
                cout << "Enter Signal ID: ";
                cin >> id;
                cout << "Enter Signal Status (Green/Red): ";
                cin >> status;
                tm.setSignal(id, status);
                break;
            }
            case 4:
                {
                string id;
                cout << "Enter Signal ID: ";
                cin >> id;
                cout << "Signal Status: " << tm.getSignalStatus(id) << endl;
                break;
            }
            case 5:
                {
                string id, violation;
                cout << "Enter Vehicle ID: ";
                cin >> id;
                cout << "Enter Violation Type: ";
                cin >> violation;
                tm.addViolation(id, violation);
                break;
            }
            case 6:
                {
                tm.viewViolations();
                break;
            }
            case 7:
                {
                tm.generateReport();
                break;
            }
            case 8:
                 {
                tm.simulateTraffic();
                break;
            }
            case 9:
                {
                string id;
                int walk_time, stop_time;
                cout << "Enter Pedestrian Signal ID: ";
                cin >> id;
                cout << "Enter Walk Time (seconds): ";
                cin >> walk_time;
                cout << "Enter Stop Time (seconds): ";
                cin >> stop_time;
                tm.simulatePedestrianCrossing(id, walk_time, stop_time);
                break;
            }
            case 10:
                {
                string id;
                cout << "Enter Emergency Vehicle ID: ";
                cin >> id;
                tm.prioritizeEmergency(id);
                break;
            }
            case 11:
                 {
                tm.monitorTrafficDensity();
                break;
            }
            case 12:
                 {
                string id;
                cout << "Enter Vehicle ID to Track: ";
                cin >> id;
                tm.trackVehicle(id);
                break;
            }
            case 13:
                 {
                string id;
                cout << "Enter Vehicle ID for Emergency Services: ";
                cin >> id;
                tm.emergencyServices(id);
                break;
            }
            case 14:
                {
                tm.dynamicSignalAdjustment();
                break;
            }
            case 15:
                 {
                tm.vehicleEntryExitLog();
                break;
            }
            case 16:
                 {
                tm.simulateAccidents();
                break;
            }
            case 17:
                 {
                tm.simulateWeatherConditions();
                break;
            }
            case 18:
                 {
                tm.manageParking();
                break;
            }
            case 19:
                {
                string id;
                cout << "Enter Emergency Vehicle ID for Alert: ";
                cin >> id;
                tm.emergencyVehicleAlert(id);
                break;
            }
            case 20:
                {
                tm.simulateTrafficFlow();
                break;
            }
            case 21:
                {
                tm.analyzeTrafficPatterns();
                break;
            }
            case 22:
                 {
                tm.optimizeSignalTimings();
                break;
            }
            case 23:
                {
                tm.enforceTrafficLaws();
                break;
            }
            case 24:
                {
                tm.coordinateWithEmergencyServices();
                break;
            }
            case 25:
                 {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 25);

    //return 0;
}

class Resource
 {
private:
    int resourceID;
    std::string resourceName;
    int quantity;
    std::string status;

public:
    Resource() : resourceID(0), resourceName(""), quantity(0), status("Unavailable") {}
    Resource(int id, const std::string& name, int qty, const std::string& stat)
        : resourceID(id), resourceName(name), quantity(qty), status(stat) {}

    int getResourceID() const
     { return resourceID; }
    std::string getResourceName() const
     { return resourceName; }
    int getQuantity() const
    { return quantity; }
    std::string getStatus() const
    { return status; }

    void setQuantity(int qty)
     { quantity = qty; }
    void setStatus(const std::string& stat)
    { status = stat; }

    void displayResource() const
     {
        std::cout << std::setw(10) << resourceID
                  << std::setw(20) << resourceName
                  << std::setw(10) << quantity
                  << std::setw(15) << status << "\n";
    }

    void saveToFile(std::ofstream& outFile) const
     {
        outFile << resourceID << "|"
                << resourceName << "|"
                << quantity << "|"
                << status << "\n";
    }

    static Resource loadFromFile(std::ifstream& inFile)
     {
        int id, qty;
        std::string name, stat;

        inFile >> id;
        inFile.ignore();
        std::getline(inFile, name, '|');
        inFile >> qty;
        inFile.ignore();
        std::getline(inFile, stat);

        return Resource(id, name, qty, stat);
    }
};

class NearbyResource
 {
private:
    int resourceID;
    std::string resourceType; // "Food", "Toilet", "Shelter"
    std::string location;
    std::string availability; // "Available", "Unavailable"
    int capacity; // Number of people it can serve (if applicable)

public:
    NearbyResource(int id, const std::string& type, const std::string& loc, const std::string& avail, int cap)
        : resourceID(id), resourceType(type), location(loc), availability(avail), capacity(cap) {}

    int getResourceID() const
    { return resourceID; }
    std::string getResourceType() const
    { return resourceType; }
    std::string getLocation() const
    { return location; }
    std::string getAvailability() const
    { return availability; }
    int getCapacity() const
    { return capacity; }

    void setAvailability(const std::string& avail)
     { availability = avail; }
    void setCapacity(int cap)
     { capacity = cap; }

    void displayResource() const
    {
        std::cout << std::setw(10) << resourceID
                  << std::setw(15) << resourceType
                  << std::setw(25) << location
                  << std::setw(15) << availability
                  << std::setw(10) << capacity << "\n";
    }

    void saveToFile(std::ofstream& outFile) const
    {
        outFile << resourceID << "|"
                << resourceType << "|"
                << location << "|"
                << availability << "|"
                << capacity << "\n";
    }

    static NearbyResource loadFromFile(std::ifstream& inFile)
     {
        int id, cap;
        std::string type, loc, avail;

        inFile >> id;
        inFile.ignore(); // Ignore separator
        std::getline(inFile, type, '|');
        std::getline(inFile, loc, '|');
        std::getline(inFile, avail, '|');
        inFile >> cap;

        return NearbyResource(id, type, loc, avail, cap);
    }
};

class ResourceManager
 {
private:
    std::vector<Resource> resources;
    std::vector<NearbyResource> nearbyResources;
    const std::string filename = "resources.txt";
    const std::string nearbyFilename = "nearby_resources.txt";

public:
    ResourceManager()
     {
        loadResourcesFromFile();
        loadNearbyResourcesFromFile();
    }

    void addResource()
     {
        int id, qty;
        std::string name, status;

        std::cout << "Enter Resource ID: ";
        std::cin >> id;

        if (std::any_of(resources.begin(), resources.end(),
                        [id]
                        (const Resource& r)
                        { return r.getResourceID() == id; }
        )
        )
            {
            std::cout << "Error: Resource ID already exists.\n";
            return;
        }

        std::cin.ignore();
        std::cout << "Enter Resource Name: ";
        std::getline(std::cin, name);

        std::cout << "Enter Quantity: ";
        std::cin >> qty;

        std::cin.ignore();
        std::cout << "Enter Status (Available/Unavailable): ";
        std::getline(std::cin, status);

        resources.emplace_back(id, name, qty, status);
        saveResourcesToFile();
        std::cout << "Resource added successfully.\n";
    }

    void viewResources() const
    {
        if (resources.empty())
            {
            std::cout << "No resources available.\n";
            return;
        }

        std::cout << "\n--- List of Resources ---\n";
        std::cout << std::setw(10) << "ID"
                  << std::setw(20) << "Name"
                  << std::setw(10) << "Quantity"
                  << std::setw(15) << "Status" << "\n";
        std::cout << std::string(55, '-') << "\n";

        for (const auto& resource : resources)
            {
            resource.displayResource();
        }
    }

    void updateResource()
    {
        int id;
        std::cout << "Enter Resource ID to update: ";
        std::cin >> id;

        auto it = std::find_if(resources.begin(), resources.end(),
                               [id]
                               (const Resource& r)
                               { return r.getResourceID() == id; }
                               );

        if (it == resources.end())
            {
            std::cout << "Error: Resource not found.\n";
            return;
        }

        int newQty;
        std::string newStatus;

        std::cout << "Enter new Quantity: ";
        std::cin >> newQty;

        std::cin.ignore();
        std::cout << "Enter new Status (Available/Unavailable): ";
        std::getline(std::cin, newStatus);

        it->setQuantity(newQty);
        it->setStatus(newStatus);

        saveResourcesToFile();
        std::cout << "Resource updated successfully.\n";
    }

    void deleteResource()
    {
        int id;
        std::cout << "Enter Resource ID to delete: ";
        std::cin >> id;

        auto it = std::remove_if(resources.begin(), resources.end(),
                                 [id]
                                 (const Resource& r)
                                  { return r.getResourceID() == id; }
                                 );

        if (it == resources.end())
            {
            std::cout << "Error: Resource not found.\n";
            return;
        }

        resources.erase(it, resources.end());
        saveResourcesToFile();
        std::cout << "Resource deleted successfully.\n";
    }

    void searchResource() const
    {
        int choice;
        std::cout << "Search by:\n1. ID\n2. Name\nEnter choice: ";
        std::cin >> choice;

        if (choice == 1)
            {
            int id;
            std::cout << "Enter Resource ID: ";
            std::cin >> id;

            auto it = std::find_if(resources.begin(), resources.end(),
                                   [id]
                                   (const Resource& r)
                                   { return r.getResourceID() == id; }
                                   );

            if (it != resources.end())
                {
                it->displayResource();
            }
             else
            {
                std::cout << "Resource not found.\n";
            }
        }
         else if (choice == 2)
         {
            std::string name;
            std::cin.ignore();
            std::cout << "Enter Resource Name: ";
            std::getline(std::cin, name);

            auto it = std::find_if(resources.begin(), resources.end(),
                                   [name]
                                   (const Resource& r)
                                   { return r.getResourceName() == name; }
                                   );

            if (it != resources.end())
                {
                it->displayResource();
            }
             else
             {
                std::cout << "Resource not found.\n";
            }
        }
         else
         {
            std::cout << "Invalid choice.\n";
        }
    }

    void sortResources()
     {
        int choice;
        std::cout << "Sort by:\n1. ID\n2. Name\n3. Quantity\nEnter choice: ";
        std::cin >> choice;

        if (choice == 1)
            {
            std::sort(resources.begin(), resources.end(),
                      [
                      ]
                      (const Resource& a, const Resource& b)
                       { return a.getResourceID() < b.getResourceID(); }
                      );
        }
        else if (choice == 2)
         {
            std::sort(resources.begin(), resources.end(),
                      [
                      ]
                      (const Resource& a, const Resource& b)
                      { return a.getResourceName() < b.getResourceName(); }
                      );
        }
        else if (choice == 3)
         {
            std::sort(resources.begin(), resources.end(),
                      [
                      ](const Resource& a, const Resource& b)
                      { return a.getQuantity() < b.getQuantity(); }
                      );
        }
        else
         {
            std::cout << "Invalid choice.\n";
            return;
        }

        std::cout << "Resources sorted successfully.\n";
        viewResources();
    }

    void exportToCSV() const
    {
        std::ofstream outFile("resources.csv");
        if (!outFile.is_open())
            {
            std::cerr << "Error: Could not open file for exporting.\n";
            return;
        }

        outFile << "ResourceID,ResourceName,Quantity,Status\n";
        for (const auto& resource : resources)
            {
            outFile << resource.getResourceID() << ","
                    << resource.getResourceName() << ","
                    << resource.getQuantity() << ","
                    << resource.getStatus() << "\n";
        }

        outFile.close();
        std::cout << "Resources exported to resources.csv successfully.\n";
    }

    void importFromFile(const std::string& importFilename)
     {
        std::ifstream inFile(importFilename);
        if (!inFile.is_open())
            {
            std::cerr << "Error: Could not open file for importing.\n";
            return;
        }

        std::string line;
        while (std::getline(inFile, line))
            {
            std::istringstream iss(line);
            int id, qty;
            std::string name, status;

            if (iss >> id >> std::ws && std::getline(iss, name, '|') &&
                iss >> qty >> std::ws && std::getline(iss, status))
                {
                if (std::none_of(resources.begin(), resources.end(),
                                 [id]
                                 (const Resource& r)
                                  { return r.getResourceID() == id; }
                                 )
                                 )
                                  {
                    resources.emplace_back(id, name, qty, status);
                }
            }
        }

        inFile.close();
        saveResourcesToFile();
        std::cout << "Resources imported successfully.\n";
    }

    void filterResourcesByStatus(const std::string& status) const
     {
        std::cout << "\n--- Resources with Status: " << status << " ---\n";
        std::cout << std::setw(10) << "ID"
                  << std::setw(20) << "Name"
                  << std::setw(10) << "Quantity"
                  << std::setw(15) << "Status" << "\n";
        std::cout << std::string(55, '-') << "\n";

        bool found = false;
        for (const auto& resource : resources)
         {
            if (resource.getStatus() == status)
                {
                resource.displayResource();
                found = true;
            }
        }

        if (!found)
            {
            std::cout << "No resources found with status: " << status << "\n";
        }
    }

    void generateReport() const
     {
        int totalResources = resources.size();
        int availableResources = std::count_if(resources.begin(), resources.end(),
                                               []
                                               (const Resource& r)
                                               { return r.getStatus() == "Available"; }
                                               );
        int totalQuantity = std::accumulate(resources.begin(), resources.end(), 0,
                                            []
                                            (int sum, const Resource& r)
                                             { return sum + r.getQuantity(); }
                                            );

        std::cout << "\n--- Resource Report ---\n";
        std::cout << "Total Resources: " << totalResources << "\n";
        std::cout << "Available Resources: " << availableResources << "\n";
        std::cout << "Total Quantity: " << totalQuantity << "\n";
    }

    void checkOutResource()
     {
        int id, qty;
        std::cout << "Enter Resource ID to check out: ";
        std::cin >> id;

        auto it = std::find_if(resources.begin(), resources.end(),
                               [id]
                               (const Resource& r)
                                { return r.getResourceID() == id; }
                                );

        if (it == resources.end())
            {
            std::cout << "Error: Resource not found.\n";
            return;
        }

        std::cout << "Enter quantity to check out: ";
        std::cin >> qty;

        if (qty > it->getQuantity())
            {
            std::cout << "Error: Not enough quantity available.\n";
            return;
        }

        it->setQuantity(it->getQuantity() - qty);
        it->setStatus(it->getQuantity() == 0 ? "Unavailable" : "Available");

        saveResourcesToFile();
        std::cout << "Resource checked out successfully.\n";
    }

    void addNearbyResource()
     {
        int id, capacity;
        std::string type, location, availability;

        std::cout << "Enter Resource ID: ";
        std::cin >> id;

        if (std::any_of(nearbyResources.begin(), nearbyResources.end(),
                        [id]
                        (const NearbyResource& nr)
                         { return nr.getResourceID() == id; }
                         )
                         )
                          {
            std::cout << "Error: Resource ID already exists.\n";
            return;
        }

        std::cin.ignore(); // Clear input buffer
        std::cout << "Enter Resource Type (Food/Toilet/Shelter): ";
        std::getline(std::cin, type);

        std::cout << "Enter Location: ";
        std::getline(std::cin, location);

        std::cout << "Enter Availability (Available/Unavailable): ";
        std::getline(std::cin, availability);

        std::cout << "Enter Capacity: ";
        std::cin >> capacity;

        nearbyResources.emplace_back(id, type, location, availability, capacity);
        saveNearbyResourcesToFile();
        std::cout << "Nearby resource added successfully.\n";
    }

    void viewNearbyResources() const
    {
        if (nearbyResources.empty())
            {
            std::cout << "No nearby resources available.\n";
            return;
        }

        std::cout << "\n--- List of Nearby Resources ---\n";
        std::cout << std::setw(10) << "ID"
                  << std::setw(15) << "Type"
                  << std::setw(25) << "Location"
                  << std::setw(15) << "Availability"
                  << std::setw(10) << "Capacity" << "\n";
        std::cout << std::string(75, '-') << "\n";

        for (const auto& nr : nearbyResources)
            {
            nr.displayResource();
        }
    }

    void updateNearbyResource()
    {
        int id;
        std::cout << "Enter Resource ID to update: ";
        std::cin >> id;

        auto it = std::find_if(nearbyResources.begin(), nearbyResources.end(),
                               [id]
                               (const NearbyResource& nr)
                                { return nr.getResourceID() == id; }
                                );

        if (it == nearbyResources.end())
            {
            std::cout << "Error: Resource not found.\n";
            return;
        }

        std::string newAvailability;
        int newCapacity;

        std::cin.ignore(); // Clear input buffer
        std::cout << "Enter new Availability (Available/Unavailable): ";
        std::getline(std::cin, newAvailability);

        std::cout << "Enter new Capacity: ";
        std::cin >> newCapacity;

        it->setAvailability(newAvailability);
        it->setCapacity(newCapacity);
        saveNearbyResourcesToFile();
        std::cout << "Nearby resource updated successfully.\n";
    }

    void deleteNearbyResource()
    {
        int id;
        std::cout << "Enter Resource ID to delete: ";
        std::cin >> id;

        auto it = std::remove_if(nearbyResources.begin(), nearbyResources.end(),
                                 [id](const NearbyResource& nr)
                                  { return nr.getResourceID() == id; });

        if (it == nearbyResources.end())
            {
            std::cout << "Error: Resource not found.\n";
            return;
        }

        nearbyResources.erase(it, nearbyResources.end());
        saveNearbyResourcesToFile();
        std::cout << "Nearby resource deleted successfully.\n";
    }

private:
    void saveResourcesToFile() const
     {
        std::ofstream outFile(filename, std::ios::trunc);
        if (!outFile.is_open())
            {
            std::cerr << "Error: Could not save resources to file.\n";
            return;
        }

        for (const auto& resource : resources)
            {
            resource.saveToFile(outFile);
        }

        outFile.close();
    }

    void loadResourcesFromFile()
    {
        std::ifstream inFile(filename);
        if (!inFile.is_open())
            {
            std::cout << "No existing data found. Starting fresh.\n";
            return;
        }

        resources.clear();
        while (!inFile.eof())
            {
            Resource resource = Resource::loadFromFile(inFile);
            if (!resource.getResourceName().empty())
             {
                resources.push_back(resource);
            }
        }

        inFile.close();
    }

    void saveNearbyResourcesToFile() const
     {
        std::ofstream outFile(nearbyFilename, std::ios::trunc);
        if (!outFile.is_open())
            {
            std::cerr << "Error: Could not save nearby resources to file.\n";
            return;
        }

        for (const auto& nr : nearbyResources)
            {
            nr.saveToFile(outFile);
        }

        outFile.close();
    }

    void loadNearbyResourcesFromFile()
     {
        std::ifstream inFile(nearbyFilename);
        if (!inFile.is_open())
            {
            std::cout << "No existing nearby resources data found. Starting fresh.\n";
            return;
        }

        nearbyResources.clear();
     while (!inFile.eof())
        {
            NearbyResource nr = NearbyResource::loadFromFile(inFile);
            if (!nr.getResourceType().empty())
                {
                nearbyResources.push_back(nr);
            }
        }

        inFile.close();
    }
};

class TrafficSignal
 {
private:
    int signalID;
    std::string location;
    std::string status; // "Working", "Under Maintenance", "Malfunctioning"
    std::string maintenanceDate;

public:
    TrafficSignal(int id, const std::string& loc, const std::string& stat, const std::string& mDate)
        : signalID(id), location(loc), status(stat), maintenanceDate(mDate) {}

    int getSignalID() const
    { return signalID; }
    std::string getLocation() const
     { return location; }
    std::string getStatus() const
     { return status; }
    std::string getMaintenanceDate() const
     { return maintenanceDate; }

    void setStatus(const std::string& stat)
     { status = stat; }
    void setMaintenanceDate(const std::string& mDate)
    { maintenanceDate = mDate; }

    void displaySignal() const
     {
        std::cout << std::setw(10) << signalID
                  << std::setw(20) << location
                  << std::setw(15) << status
                  << std::setw(15) << maintenanceDate << "\n";
    }

    void saveToFile(std::ofstream& outFile) const
    {
        outFile << signalID << "|"
                << location << "|"
                << status << "|"
                << maintenanceDate << "\n";
    }

    static TrafficSignal loadFromFile(std::ifstream& inFile)
     {
        int id;
        std::string loc, stat, mDate;

        inFile >> id;
        inFile.ignore(); // Ignore separator
        std::getline(inFile, loc, '|');
        std::getline(inFile, stat, '|');
        std::getline(inFile, mDate);

        return TrafficSignal(id, loc, stat, mDate);
    }
};

class ConstructionResource
 {
private:
    int resourceID;
    std::string resourceName;
    int quantity; // Available units
    std::string category; // Material, Equipment
    std::string status; // Available, In Use, Under Maintenance

public:
    ConstructionResource(int id, const std::string& name, int qty, const std::string& cat, const std::string& stat)
        : resourceID(id), resourceName(name), quantity(qty), category(cat), status(stat) {}

    int getResourceID() const
    { return resourceID; }
    std::string getResourceName() const
     { return resourceName; }
    int getQuantity() const { return quantity; }
    std::string getCategory() const
    { return category; }
    std::string getStatus() const
     { return status; }

    void setQuantity(int qty)
    { quantity = qty; }
    void setStatus(const std::string& stat)
     { status = stat; }

    void displayResource() const
     {
        std::cout << std::setw(10) << resourceID
                  << std::setw(20) << resourceName
                  << std::setw(10) << quantity
                  << std::setw(15) << category
                  << std::setw(15) << status << "\n";
    }

    void saveToFile(std::ofstream& outFile) const
     {
        outFile << resourceID << "|"
                << resourceName << "|"
                << quantity << "|"
                << category << "|"
                << status << "\n";
    }

    static ConstructionResource loadFromFile(std::ifstream& inFile)
     {
        int id, qty;
        std::string name, cat, stat;

        inFile >> id;
        inFile.ignore(); // Ignore separator
        std::getline(inFile, name, '|');
        inFile >> qty;
        inFile.ignore(); // Ignore separator
        std::getline(inFile, cat, '|');
        std::getline(inFile, stat);

        return ConstructionResource(id, name, qty, cat, stat);
    }
};

class TrafficVolume
 {
private:
    std::string location;
    int vehicleCount; // Number of vehicles passing per hour
    std::string timePeriod; // E.g., "Morning", "Afternoon", "Evening"

public:
    TrafficVolume(const std::string& loc, int count, const std::string& period)
        : location(loc), vehicleCount(count), timePeriod(period) {}

    std::string getLocation() const
     { return location; }
    int getVehicleCount() const
    { return vehicleCount; }
    std::string getTimePeriod() const
     { return timePeriod; }

    void displayVolume() const
    {
        std::cout << std::setw(20) << location
                  << std::setw(15) << vehicleCount
                  << std::setw(15) << timePeriod << "\n";
    }

    void saveToFile(std::ofstream& outFile) const
     {
        outFile << location << "|"
                << vehicleCount << "|"
                << timePeriod << "\n";
    }

    static TrafficVolume loadFromFile(std::ifstream& inFile)
     {
        std::string loc, period;
        int count;

        std::getline(inFile, loc, '|');
        inFile >> count;
        inFile.ignore(); // Ignore separator
        std::getline(inFile, period);

        return TrafficVolume(loc, count, period);
    }
};

class RoadSection
 {
private:
    int sectionID;
    std::string location;
    std::string condition; // "Good", "Under Repair", "Damaged"
    std::string repairDate;

public:
    RoadSection(int id, const std::string& loc, const std::string& cond, const std::string& rDate)
        : sectionID(id), location(loc), condition(cond), repairDate(rDate) {}

    int getSectionID() const
    { return sectionID; }
    std::string getLocation() const
     { return location; }
    std::string getCondition() const
    { return condition; }
    std::string getRepairDate() const
    { return repairDate; }

    void setCondition(const std::string& cond)
    { condition = cond; }
    void setRepairDate(const std::string& rDate)
     { repairDate = rDate; }

    void displaySection() const
     {
        std::cout << std::setw(10) << sectionID
                  << std::setw(20) << location
                  << std::setw(15) << condition
                  << std::setw(15) << repairDate << "\n";
    }

    void saveToFile(std::ofstream& outFile) const
     {
        outFile << sectionID << "|"
                << location << "|"
                << condition << "|"
                << repairDate << "\n";
    }

    static RoadSection loadFromFile(std::ifstream& inFile)
     {
        int id;
        std::string loc, cond, rDate;

        inFile >> id;
        inFile.ignore(); // Ignore separator
        std::getline(inFile, loc, '|');
        std::getline(inFile, cond, '|');
        std::getline(inFile, rDate);

        return RoadSection(id, loc, cond, rDate);
    }
};

class Incident
 {
private:
    int incidentID;
    std::string location;
    std::string description;
    std::string date;

public:
    Incident(int id, const std::string& loc, const std::string& desc, const std::string& d)
        : incidentID(id), location(loc), description(desc), date(d) {}

    int getIncidentID() const
     { return incidentID; }
    std::string getLocation() const
     { return location; }
    std::string getDescription() const
    { return description; }
    std::string getDate() const
     { return date; }

    void displayIncident() const
     {
        std::cout << std::setw(10) << incidentID
                  << std::setw(20) << location
                  << std::setw(30) << description
                  << std::setw(15) << date << "\n";
    }

    void saveToFile(std::ofstream& outFile) const
     {
        outFile << incidentID << "|"
                << location << "|"
                << description << "|"
                << date << "\n";
    }

    static Incident loadFromFile(std::ifstream& inFile)
     {
        int id;
        std::string loc, desc, date;

        inFile >> id;
        inFile.ignore(); // Ignore separator
        std::getline(inFile, loc, '|');
        std::getline(inFile, desc, '|');
        std::getline(inFile, date);

        return Incident(id, loc, desc, date);
    }
};
double calculateArea(double length, double width)
 {
    return length * width;
}

// Function to display zone details
void displayZoneDetails(const Zone& zone)
 {
    cout << "Zone Name: " << zone.name << endl;
    cout << "Type: " << zone.type << endl;
    cout << "Length: " << zone.length << " meters" << endl;
    cout << "Width: " << zone.width << " meters" << endl;
    cout << "Area: " << fixed << setprecision(2) << calculateArea(zone.length, zone.width) << " square meters" << endl;
    cout << "-----------------------------" << endl;
}

// Function to calculate the total area of all zones
double calculateTotalArea(const vector<Zone>& zones)
 {
    double totalArea = 0.0;
    for (const auto& zone : zones)
        {
        totalArea += calculateArea(zone.length, zone.width);
    }
    return totalArea;
}

// Function to find zones of a specific type
vector<Zone> findZonesByType(const vector<Zone>& zones, const string& type)
 {
    vector<Zone> result;
    for (const auto& zone : zones)
     {
        if (zone.type == type)
            {
            result.push_back(zone);
        }
    }
    return result;
}

// Main function
int areacalc() {
    vector<Zone> cityZones;

    // Add main data for city zones
    cityZones.push_back({"Central Park", 500.0, 300.0, "Park"});
    cityZones.push_back({"Main Road", 2000.0, 20.0, "Road"});
    cityZones.push_back({"Residential Block A", 100.0, 150.0, "Residential"});
    cityZones.push_back({"Residential Block B", 120.0, 130.0, "Residential"});
    cityZones.push_back({"Shopping Mall", 250.0, 180.0, "Commercial"});
    cityZones.push_back({"Secondary Road", 800.0, 15.0, "Road"});
    cityZones.push_back({"Community Garden", 50.0, 80.0, "Park"});

    // Display all zones
    cout << "City Zone Details:\n-----------------------------" << endl;
    for (const auto& zone : cityZones) {
        displayZoneDetails(zone);
    }

    // Calculate the total area of the city
    double totalArea = calculateTotalArea(cityZones);
    cout << "Total Area of the City: " << fixed << setprecision(2) << totalArea << " square meters\n";
    cout << "-----------------------------" << endl;

    // Find zones by type
    string searchType = "Residential";
    vector<Zone> residentialZones = findZonesByType(cityZones, searchType);
    cout << "Zones of type: " << searchType << "\n-----------------------------" << endl;
    for (const auto& zone : residentialZones) {
        displayZoneDetails(zone);
    }

    // Add some main calculations for roads, parks, and residential zones
    cout << "\nAdditional Calculations:\n-----------------------------" << endl;
    double roadArea = 0.0, parkArea = 0.0, residentialArea = 0.0, commercialArea = 0.0;

    for (const auto& zone : cityZones) {
        if (zone.type == "Road") {
            roadArea += calculateArea(zone.length, zone.width);
        } else if (zone.type == "Park") {
            parkArea += calculateArea(zone.length, zone.width);
        } else if (zone.type == "Residential") {
            residentialArea += calculateArea(zone.length, zone.width);
        } else if (zone.type == "Commercial") {
            commercialArea += calculateArea(zone.length, zone.width);
        }
    }

    cout << "Total Road Area: " << fixed << setprecision(2) << roadArea << " square meters\n";
    cout << "Total Park Area: " << fixed << setprecision(2) << parkArea << " square meters\n";
    cout << "Total Residential Area: " << fixed << setprecision(2) << residentialArea << " square meters\n";
    cout << "Total Commercial Area: " << fixed << setprecision(2) << commercialArea << " square meters\n";

    // Simulate other calculations (main for extending lines)
    for (int i = 0; i < 10; i++) {
        double tempLength = (i + 1) * 10;
        double tempWidth = (i + 1) * 5;
        double tempArea = calculateArea(tempLength, tempWidth);
        cout << "Simulated Zone " << i + 1 << " - Length: " << tempLength << ", Width: " << tempWidth
             << ", Area: " << tempArea << " square meters\n";
    }

    cout << "\nSimulation Complete! Thank you for using City Area Calculator.\n";

    return 0;
}
void resourceManagement()
{
    ResourceManager manager;
    int choice;

    do
        {
        std::cout << "\n--- Resource Management System ---\n";
        std::cout << "1. Add Resource\n";
        std::cout << "2. View Resources\n";
        std::cout << "3. Update Resource\n";
        std::cout << "4. Delete Resource\n";
        std::cout << "5. Search Resource\n";
        std::cout << "6. Sort Resources\n";
        std::cout << "7. Export Resources to CSV\n";
        std::cout << "8. Import Resources from File\n";
        std::cout << "9. Filter Resources by Status\n";
        std::cout << "10. Generate Report\n";
        std::cout << "11. Check Out Resource\n";
        std::cout << "12. Add Nearby Resource\n";
        std::cout << "13. View Nearby Resources\n";
        std::cout << "14. Update Nearby Resource\n";
        std::cout << "15. Delete Nearby Resource\n";
        std::cout << "16. Manage Traffic Signals\n";
        std::cout << "17. Manage Construction Resources\n";
        std::cout << "18. Manage Traffic Volumes\n";
        std::cout << "19. Manage Road Sections\n";
        std::cout << "20. Manage Incidents\n";
        std::cout << "21. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
         {
            case 1:
                manager.addResource();
                break;
            case 2:
                manager.viewResources();
                break;
            case 3:
                manager.updateResource();
                break;
            case 4:
                manager.deleteResource();
                break;
            case 5:
                manager.searchResource();
                break;
            case 6:
                manager.sortResources();
                break;
            case 7:
                manager.exportToCSV();
                break;
            case 8:
                {
                std::string filename;
                std::cout << "Enter filename to import: ";
                std::cin >> filename;
                manager.importFromFile(filename);
                break;
            }
            case 9:
                 {
                std::string status;
                std::cin.ignore();
                std::cout << "Enter status to filter by (Available/Unavailable): ";
                std::getline(std::cin, status);
                manager.filterResourcesByStatus(status);
                break;
            }
            case 10:
                manager.generateReport();
                break;
            case 11:
                manager.checkOutResource();
                break;
            case 12:
                manager.addNearbyResource();
                break;
            case 13:
                manager.viewNearbyResources();
                break;
            case 14:
                manager.updateNearbyResource();
                break;
            case 15:
                manager.deleteNearbyResource();
                break;
            case 16:
                 {
                int id;
                std::string location, status, maintenanceDate;
                std::cout << "Enter Signal ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter Location: ";
                std::getline(std::cin, location);
                std::cout << "Enter Status (Working/Under Maintenance/Malfunctioning): ";
                std::getline(std::cin, status);
                std::cout << "Enter Maintenance Date: ";
                std::getline(std::cin, maintenanceDate);
                TrafficSignal signal(id, location, status, maintenanceDate);
                std::ofstream outFile("traffic_signals.txt", std::ios::app);
                signal.saveToFile(outFile);
                outFile.close();
                std::cout << "Traffic signal added successfully.\n";
                break;
            }
            case 17:
                {
                int id, qty;
                std::string name, category, status;
                std::cout << "Enter Resource ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter Resource Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Quantity: ";
                std::cin >> qty;
                std::cin.ignore();
                std::cout << "Enter Category (Material/Equipment): ";
                std::getline(std::cin, category);
                std::cout << "Enter Status (Available/In Use/Under Maintenance): ";
                std::getline(std::cin, status);
                ConstructionResource res(id, name, qty, category, status);
                std::ofstream outFile("construction_resources.txt", std::ios::app);
                res.saveToFile(outFile);
                outFile.close();
                std::cout << "Construction resource added successfully.\n";
                break;
            }
            case 18:
                 {
                std::string location, timePeriod;
                int vehicleCount;
                std::cout << "Enter Location: ";
                std::cin.ignore();
                std::getline(std::cin, location);
                std::cout << "Enter Vehicle Count: ";
                std::cin >> vehicleCount;
                std::cin.ignore();
                std::cout << "Enter Time Period (Morning/Afternoon/Evening): ";
                std::getline(std::cin, timePeriod);
                TrafficVolume volume(location, vehicleCount, timePeriod);
                std::ofstream outFile("traffic_volumes.txt", std::ios::app);
                volume.saveToFile(outFile);
                outFile.close();
                std::cout << "Traffic volume added successfully.\n";
                break;
            }
            case 19:
                 {
                int id;
                std::string location, condition, repairDate;
                std::cout << "Enter Section ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter Location: ";
                std::getline(std::cin, location);
                std::cout << "Enter Condition (Good/Under Repair/Damaged): ";
                std::getline(std::cin, condition);
                std::cout << "Enter Repair Date: ";
                std::getline(std::cin, repairDate);
                RoadSection section(id, location, condition, repairDate);
                std::ofstream outFile("road_sections.txt", std::ios::app);
                section.saveToFile(outFile);
                outFile.close();
                std::cout << "Road section added successfully.\n";
                break;
            }
            case 20:
                {
                int id;
                std::string location, description, date;
                std::cout << "Enter Incident ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter Location: ";
                std::getline(std::cin, location);
                std::cout << "Enter Description: ";
                std::getline(std::cin, description);
                std::cout << "Enter Date: ";
                std::getline(std::cin, date);
                Incident incident(id, location, description, date);
                std::ofstream outFile("incidents.txt", std::ios::app);
                incident.saveToFile(outFile);
                outFile.close();
                std::cout << "Incident added successfully.\n";
                break;
            }
            case 21:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
    while (choice != 21);

    //return 0;
}




void findLocation()
{
// Define the places in Karnataka
const string places[10] =
{
    "Bangalore",
    "Mysore",
    "Mangalore",
    "Hubli",
    "Dharwad",
    "Belgaum",
    "Shimoga",
    "Gadag",
    "Chikmagalur",
    "Udupi"
};

// Define the distances between places (in kilometers)
const int distances[10][10] =
 {
    {0, 145, 352, 360, 420, 502, 280, 420, 245, 400}, // Bangalore

    {145, 0, 210, 220, 270, 350, 150, 270, 100, 250},// Mysore

    {352, 210, 0, 220, 300, 400, 150, 300, 150, 200}, // Mangalore

    {360, 220, 220, 0, 80, 150, 100, 150, 200, 300},  // Hubli

    {420, 270, 300, 80, 0, 100, 150, 200, 250, 350},   // Dharwad

    {502, 350, 400, 150, 100, 0, 200, 250, 300, 400},  // Belgaum
    {280, 150, 150, 100, 150, 200, 0, 100, 150, 250},  // Shimoga

    {420, 270, 300, 150, 200, 250, 100, 0, 200, 300},  // Gadag

    {245, 100, 150, 200, 250, 300, 150, 200, 0, 150},  // Chikmagalur

    {400, 250, 200, 300, 350, 400, 250, 300, 150, 0}    // Udupi
};

// Start of the program logic
string startPlace, endPlace;
cout << "Enter the initial place(Bangalore,Mysore,Mangalore,Hubli,Dharwad,Belgaum,Shimoga,Gadag,Chikmagalur, Udupi): ";
cin >> startPlace;
cout << "Enter the final place(Bangalore,Mysore,Mangalore,Hubli,Dharwad,Belgaum,Shimoga,Gadag,Chikmagalur, Udupi): ";
cin >> endPlace;

// Find indices of the places
int startIndex = -1, endIndex = -1;
for (int i = 0; i < 10; i++)
 {
    if (places[i] == startPlace)
        {
        startIndex = i;
    }
    if (places[i] == endPlace)
        {
        endIndex = i;
    }
}

// Check if both places are valid
if (startIndex == -1 || endIndex == -1)
    {
    cout << "Invalid place entered. Please enter valid places from the list." << endl;
}
 else
 {
    // Output the distance
    cout << "Distance between " << startPlace << " and " << endPlace << " is: "
         << distances[startIndex][endIndex] << " km" << endl;
}


}





// Function to simulate finding a hotel
void findHotel()
 {
    // Define the hotels, their locations, and types in Karnataka
const string hotels[15] =
{
    "Taj West End, Bangalore",
    "The Leela Palace, Bangalore",
    "ITC Gardenia, Bangalore",
    "JW Marriott, Bangalore",
    "Radisson Blu, Bangalore",
    "Lemon Tree, Bangalore",
    "Royal Orchid, Bangalore",
    "The Oberoi, Bangalore",
    "Hotel Mysore, Mysore",
    "Radisson Blu, Mysore",
    "Royal Orchid Metropole, Mysore",
    "The Windflower Resort, Mysore",
    "The Gateway Hotel, Mysore",
    "Hotel Deepa Comforts, Mangalore",
    "The Gateway Hotel, Mangalore"
};

// Define the distances from a reference point (Bangalore) to each hotel (in kilometers)
const int distances[100] =
{
    5, 7, 6, 8, 10, 12, 15, 4, // Bangalore Hotels
    145, 140, 142, 138,  // Mysore Hotels
    352, 350,  // Mangalore Hotels
};

// Define the types of hotels
const string hotelTypes[100] =
 {
    "Luxury", "Luxury", "Luxury", "Luxury", "Premium", "Budget", "Premium", "Luxury", // Bangalore Hotels
    "Budget", "Premium", "Luxury", "Luxury", "Budget", "Budget", "Luxury", "Luxury" // Mysore and Mangalore Hotels
};

// Start of the program logic
string initialPlace;
cout << "Enter the initial place (Bangalore, Mysore, Mangalore): ";
cin >> initialPlace;

// Initialize variables to find the nearest hotel
int nearestHotelIndex = -1;
int nearestDistance = numeric_limits<int>::max();

// Determine the nearest hotel based on the initial place
if (initialPlace == "Bangalore")
    {
    for (int i = 0; i < 8; i++)
    {
        // 8 hotels in Bangalore
        if (distances[i] < nearestDistance)
            {
            nearestDistance = distances[i];
            nearestHotelIndex = i;
        }
    }
}
else if (initialPlace == "Mysore")
{
    for (int i = 8; i < 12; i++)
     {
         // 4 hotels in Mysore
        if (distances[i] < nearestDistance)
            {
            nearestDistance = distances[i];
            nearestHotelIndex = i;
        }
    }
}
else if (initialPlace == "Mangalore")
{
    for (int i = 12; i < 15; i++)
        {
            // 3 hotels in Mangalore
        if (distances[i] < nearestDistance)
            {
            nearestDistance = distances[i];
            nearestHotelIndex = i;
        }
    }
}
 else
 {
    cout << "Invalid place entered. Please enter either Bangalore, Mysore, or Mangalore." << endl;
}

// Output the nearest hotel if found
if (nearestHotelIndex != -1)
    {
    cout << "The nearest hotel to " << initialPlace << " is: "
         << hotels[nearestHotelIndex] << " (" << hotelTypes[nearestHotelIndex] << ") with a distance of "
         << nearestDistance << " km." << endl;
}
}

// Function to simulate checking traffic
void checkTraffic()
{
const string cities[5] =
{
"Bangalore",
"Mysore",
"Mangalore",
 "Hubli",
 "Belgaum"
 };
    const string places[5][10] =
    {
        {
            "MG Road",
            "Brigade Road",
             "Cubbon Park",
             "Vidhana Soudha",
            "Lalbagh Botanical Garden",
            "Bangalore Palace",
            "Tipu Sultan's Summer Palace",
             "ISKCON Temple",
            "Nandi Hills",
            "Bannerghatta National Park"
        }
        ,
        {
            "Mysore Palace",
            "Chamundi Hill",
            "Brindavan Gardens",
            "St. Philomena's Church",
            "Jaganmohan Palace",
            "Karanji Lake",
            "Mysore Zoo",
             "Railway Museum",
            "Lalitha Mahal Palace",
            "Krishna Raja Sagara"
        }
        ,
        {
            "Panambur Beach",
             "Mangalore Port",
              "St. Aloysius Chapel",
            "Kadri Manjunath Temple",
            "Sultan Battery",
            "Tannirbhavi Beach",
            "Pilikula Nisargadhama",
            "Mangaladevi Temple",
             "Shree Gokarnanatheshwara Temple",
            "City Centre Mall"
        }
        ,
        {
            "Unkal Lake",
            "Nrupatunga Betta",
             "Chandramouleshwara Temple",
            "Hubli Fort",
             "Indira Gandhi Glass House Garden",
            "Siddharoodha Math",
            "Bhavanishankar Temple",
            "Vijay Nagar",
             "Kittur Rani Chennamma Circle",
             "Gadag"
        }
        ,
        {
            "Fort Belgaum",
            "Belgaum Fort",
            "Kamala Basti",
            "Narasimha Temple",
             "Gokak Falls",
             "Kittur Fort",
            "Rudra Sagar Lake",
             "Shri Ramakrishna Ashram",
            "Mahatma Gandhi Garden",
            "Belgaum Golf Club"
        }
    };

    string selectedCity, selectedPlace;
    bool validInput = false;

    while (!validInput)
        {
        cout << "Enter the city name (Bangalore, Mysore, Mangalore, Hubli, Belgaum): ";
        getline(cin, selectedCity);

        // Trim the input
        selectedCity = trimWhitespace(selectedCity);

        int cityIndex = -1;

        // Find the index of the selected city
        for (int i = 0; i < 5; i++)
         {
            if (cities[i] == selectedCity)
                {
                cityIndex = i;
                break;
            }
        }

        if (cityIndex == -1)
            {
            cout << "Invalid city entered. Please enter a valid city from the list." << endl;
            cout << "Valid cities are: ";
            for (const string& city : cities)
                {
                cout << city << " ";
            }
            cout << endl;
        }
        else
         {
            cout << "Enter the place in " << selectedCity << ": ";
            getline(cin, selectedPlace);

            // Trim the input
            selectedPlace = trimWhitespace(selectedPlace);

            bool placeFound = false;
            for (int j = 0; j < 10; j++)
            {
                if (places[cityIndex][j] == selectedPlace)
                    {
                    placeFound = true;
                    break;
                }
            }

            if (!placeFound)
                {
                cout << "Invalid place entered. Please enter a valid place from the list." << endl;
                cout << "Valid places in " << selectedCity << " are: ";
                for (const string& place : places[cityIndex])
                 {
                    cout << place << " ";
                }
                cout << endl;
            }
            else
             {
                cout << "Tracking traffic in " << selectedPlace << " of " << selectedCity << "..." << endl;
                cout << "Traffic status: Moderate (simulated data)." << endl;
                validInput = true;
            }
        }
    }
}

// Function to simulate finding tourist attractions
void findTouristAttractions()
 {

 // Main Program Start

    string city_name;
    cout << "Enter the name of the city from Karnataka (e.g., Bengaluru, Mysuru,Hubballi,Mangalore,Udupi ): ";
    cin >> city_name;


    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    float usedFloat = 7.5f;
    bool usedBool = true;
    string nodeString = "node";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedChar++;
        usedFloat -= 0.01;
        if (usedVar1 > 50) break;
    }

    if (usedVar2 > 5.0)
        {
        usedVar1--;
    }
     else
    {
        usedVar1++;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedFloat += 0.5;
            break;
    }

    int arr[10];
    for (int i = 0; i < 10; i++)
        {
        arr[i] = i * 2;
    }

    // Even more unnecessary operations
    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 3;
    }

    // Main program logic continues
    if (city_name == "Bengaluru")
        {
        cout << "Tourist Places in Bengaluru and their distance from the bus stand:\n";
        cout << "1. Bangalore Palace - 5 km\n";
        cout << "2. Lalbagh Botanical Garden - 7 km\n";
        cout << "3. Cubbon Park - 8 km\n";
        cout << "4. Vidhana Soudha - 10 km\n";
        cout << "5. M.G. Road - 3 km\n";
        cout << "6. Bannerghatta National Park - 15 km\n";
        cout << "7. ISKCON Temple - 12 km\n";
        cout << "8. Chitrakala Parishath - 6 km\n";
        cout << "9. Vikasa Soudha - 20 km\n";
        cout << "10. Ulsoor Lake - 18 km\n";
    }
    else if (city_name == "Mysuru")
     {
        cout << "Tourist Places in Mysuru and their distance from the bus stand:\n";
        cout << "1. Mysore Palace - 6 km\n";
        cout << "2. Chamundi Hill - 9 km\n";
        cout << "3. Brindavan Gardens - 12 km\n";
        cout << "4. St. Philomena's Church - 7 km\n";
        cout << "5. Jaganmohan Palace - 8 km\n";
        cout << "6. Ranganathittu Bird Sanctuary - 15 km\n";
        cout << "7. Mysore Zoo - 5 km\n";
        cout << "8. Karanji Lake - 10 km\n";
        cout << "9. Srirangapatna - 14 km\n";
        cout << "10. Mysore Railway Station - 16 km\n";
    }
    else if (city_name == "Hubballi")
        {
        cout << "Tourist Places in Hubballi and their distance from the bus stand:\n";
        cout << "1. Unkal Lake - 4 km\n";
        cout << "2. Nuggikeri Bazaar - 8 km\n";
        cout << "3. Bhadravathi - 10 km\n";
        cout << "4. Dharwad Fort - 7 km\n";
        cout << "5. Sadhankeri Park - 6 km\n";
        cout << "6. Iskcon Hubballi - 13 km\n";
        cout << "7. Banashankari Temple - 9 km\n";
        cout << "8. Gurumurtheshwara Temple - 14 km\n";
        cout << "9. Chandramouleshwara Temple - 11 km\n";
        cout << "10. Indira Gandhi Glass House Garden - 18 km\n";
    }
    else if (city_name == "Mangalore")
     {
        cout << "Tourist Places in Mangalore and their distance from the bus stand:\n";
        cout << "1. Panambur Beach - 5 km\n";
        cout << "2. Kudroli Gokarnath Temple - 8 km\n";
        cout << "3. Tannirbhavi Beach - 10 km\n";
        cout << "4. St. Aloysius Chapel - 12 km\n";
        cout << "5. Mangalore University - 7 km\n";
        cout << "6. Sultan Battery - 13 km\n";
        cout << "7. Kateel Durga Parameshwari Temple - 8 km\n";
        cout << "8. Ullal Beach - 9 km\n";
        cout << "9. Mangaladevi Temple - 14 km\n";
        cout << "10. Milagres Church - 11 km\n";
    }
    // node Code continues
    for (int i = 0; i > 20; i++)
        {
        if (i % 2 == 0)
         {
            string tempString = "This is just node code";
            cout << tempString << endl;
        }
    }

    while (false)
        {
        int a = 100;
        if (a == 100) break;
    }

    cout << "Enjoy your trip" << endl;
    for (int i = 0; i < 50; i++)
     {
        for (int j = 0; j < 1000; j++)
            {
            int x = i * j;
        }
    }

    // More unnecessary variables and loops
    for (int i = 0; i < 500; i++)
        {
        int result = (i + 2) * 2;
        result = result / 4;
    }

    if (city_name == "Udupi")
        {
        cout << "Tourist Places in Udupi and their distance from the bus stand:\n";
        cout << "1. Sri Krishna Temple - 3 km\n";
        cout << "2. Udupi Sri Krishna Matha - 6 km\n";
        cout << "3. Malpe Beach - 10 km\n";
        cout << "4. St. Mary's Island - 14 km\n";
        cout << "5. Kaup Beach - 11 km\n";
        cout << "6. Anantheshwara Temple - 15 km\n";
        cout << "7. End Point - 8 km\n";
        cout << "8. Eagle's Nest - 7 km\n";
        cout << "9. Sri Chandramouleeshwar Temple - 9 km\n";
        cout << "10. Manipal University - 16 km\n";
    }

    // node Code end
    cout << "happy journey" << endl;
    //return 0;
}


// Function to simulate finding a hospital
void findHospital()
 {
  string city_name;

    // Introduce the user to the program
    cout << "Welcome to the Karnataka City Hospital Finder Program!" << endl;
    cout << "Please enter the name of the city to find hospitals: "<< endl;
    cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;



    cin >> city_name;

    // node code starts (unnecessary loops, variables, etc.)
    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }

    // Additional used logic
    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }

    // Continue with more useless operations
    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }

    // Now back to the city hospital logic
    if (city_name == "Bengaluru" || city_name == "Bangalore")
        {
        cout << "Hospitals in Bengaluru:\n";
        cout << "1. St. John's Medical College Hospital - 5 km\n";
        cout << "2. Manipal Hospital - 8 km\n";
        cout << "3. Fortis La Femme Hospital - 10 km\n";
        cout << "4. NIMHANS - 12 km\n";
        cout << "5. Sakra Premium Hospital - 15 km\n";
        cout << "6. Cloudnine Hospital - 7 km\n";
        cout << "7. Columbia Asia Referral Hospital - 9 km\n";
        cout << "8. Care Clinic - 6 km\n";
        cout << "9. BMCRI - 20 km\n";
        cout << "10. Venkateshwar Hospital - 18 km\n";
    }
    else if (city_name == "Mysuru")
     {
        cout << "Hospitals in Mysuru:\n";
        cout << "1. JSS Hospital - 6 km\n";
        cout << "2. Columbia Asia Hospital - 8 km\n";
        cout << "3. K.R. Hospital - 10 km\n";
        cout << "4. Cheluvamba Hospital - 12 km\n";
        cout << "5. Sanjeevini Hospital - 7 km\n";
        cout << "6. Vani Vilas Hospital - 9 km\n";
        cout << "7. PK Hospital - 5 km\n";
        cout << "8. Aadhar Hospital - 14 km\n";
        cout << "9. Fortis Healthcare - 15 km\n";
        cout << "10. Ashwini Hospital - 20 km\n";
    }
     else if (city_name == "Hubballi")
     {
        cout << "Hospitals in Hubballi:\n";
        cout << "1. KLE Hospital - 8 km\n";
        cout << "2. Hubli General Hospital - 6 km\n";
        cout << "3. Navodaya Hospital - 9 km\n";
        cout << "4. Mother & Child Hospital - 5 km\n";
        cout << "5. Basava Hospital - 12 km\n";
        cout << "6. Nirmala Hospital - 11 km\n";
        cout << "7. Shree Hospital - 7 km\n";
        cout << "8. Kiran Hospital - 10 km\n";
        cout << "9. Prajwal Hospital - 15 km\n";
        cout << "10. Sadashiv Hospital - 20 km\n";
    }
    else if (city_name == "Mangalore")
     {
        cout << "Hospitals in Mangalore:\n";
        cout << "1. Kasturba Medical College Hospital - 5 km\n";
        cout << "2. Fr. Muller's Hospital - 6 km\n";
        cout << "3. Lady Goshen Hospital - 8 km\n";
        cout << "4. KMC Hospital - 10 km\n";
        cout << "5. Mission Hospital - 7 km\n";
        cout << "6. Dr. M. C. Shetty's Hospital - 9 km\n";
        cout << "7. Kiran Hospital - 12 km\n";
        cout << "8. Kottar Hospital - 15 km\n";
        cout << "9. PVS Hospital - 11 km\n";
        cout << "10. Kanara Hospital - 13 km\n";
    }
    else if (city_name == "Udupi")
     {
        cout << "Hospitals in Udupi:\n";
        cout << "1. Kasturba Hospital - 3 km\n";
        cout << "2. Manipal Hospital - 7 km\n";
        cout << "3. KMC Hospital - 5 km\n";
        cout << "4. Malpe Hospital - 12 km\n";
        cout << "5. Prarthana Hospital - 9 km\n";
        cout << "6. Sushrutha Hospital - 8 km\n";
        cout << "7. Dr. M.R. Pai Hospital - 10 km\n";
        cout << "8. Udupi District Hospital - 11 km\n";
        cout << "9. Karanth Hospital - 6 km\n";
        cout << "10. Manipal Heart Centre - 15 km\n";
    }
    else if (city_name == "Belagavi")
     {
        cout << "Hospitals in Belagavi:\n";
        cout << "1. KLE Hospital - 5 km\n";
        cout << "2. Belagavi District Hospital - 7 km\n";
        cout << "3. Sanjeevani Hospital - 8 km\n";
        cout << "4. Ashwini Hospital - 9 km\n";
        cout << "5. Parijatha Hospital - 10 km\n";
        cout << "6. Gokak Hospital - 11 km\n";
        cout << "7. Dinesh Hospital - 12 km\n";
        cout << "8. Belagavi Multispeciality Hospital - 14 km\n";
        cout << "9. Kittur Rani Channamma Hospital - 13 km\n";
        cout << "10. Basaveshwara Hospital - 15 km\n";
    }
    else if (city_name == "Kalaburagi")
     {
        cout << "Hospitals in Kalaburagi:\n";
        cout << "1. Gulbarga Hospital - 6 km\n";
        cout << "2. Sharana Hospital - 7 km\n";
        cout << "3. Sandeep Hospital - 8 km\n";
        cout << "4. JSS Hospital - 9 km\n";
        cout << "5. Red Cross Hospital - 10 km\n";
        cout << "6. Shivaji Hospital - 12 km\n";
        cout << "7. Basaveshwar Hospital - 14 km\n";
        cout << "8. Kalaburagi Civil Hospital - 15 km\n";
        cout << "9. Lions Hospital - 16 km\n";
        cout << "10. Deshpande Hospital - 17 km\n";
    }
    else if (city_name == "Chikkamagaluru")
     {
        cout << "Hospitals in Chikkamagaluru:\n";
        cout << "1. Chikkamagaluru District Hospital - 5 km\n";
        cout << "2. Civil Hospital - 6 km\n";
        cout << "3. Chikmagalur Heart Hospital - 7 km\n";
        cout << "4. Shraddha Hospital - 8 km\n";
        cout << "5. Karanth Hospital - 10 km\n";
        cout << "6. Vasanth Hospital - 11 km\n";
        cout << "7. Priya Hospital - 12 km\n";
        cout << "8. Nandini Hospital - 14 km\n";
        cout << "9. Giri Hospital - 13 km\n";
        cout << "10. Taluk Hospital - 15 km\n";
    }
     else
     {
        cout << "Sorry, the city is not in our list of hospitals in Karnataka.\n";
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp = temp / 3;
    }

    cout << "The program has completed";
}


void findBank()
 {
     string city_name;


    cout << "Welcome to the Karnataka City Bank Finder Program!" << endl;
    cout << "Please enter the name of the city to find banks: "<< endl;
     cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;

    cin >> city_name;


    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }

    // Additional used logic
    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }

    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }

    // Now back to the city bank logic
    if (city_name == "Bengaluru" || city_name == "Bangalore")
        {
        cout << "Banks in Bengaluru:\n";
        cout << "1. State Bank of India - 5 km\n";
        cout << "2. ICICI Bank - 8 km\n";
        cout << "3. HDFC Bank - 10 km\n";
        cout << "4. Axis Bank - 12 km\n";
        cout << "5. Kotak Mahindra Bank - 15 km\n";
        cout << "6. Canara Bank - 7 km\n";
        cout << "7. Bank of Baroda - 9 km\n";
        cout << "8. IDFC First Bank - 6 km\n";
        cout << "9. Punjab National Bank - 20 km\n";
        cout << "10. Union Bank of India - 18 km\n";
    }
     else if (city_name == "Mysuru")
     {
        cout << "Banks in Mysuru:\n";
        cout << "1. State Bank of India - 6 km\n";
        cout << "2. ICICI Bank - 8 km\n";
        cout << "3. HDFC Bank - 10 km\n";
        cout << "4. Axis Bank - 7 km\n";
        cout << "5. Kotak Mahindra Bank - 12 km\n";
        cout << "6. Canara Bank - 9 km\n";
        cout << "7. Bank of Baroda - 5 km\n";
        cout << "8. IDFC First Bank - 14 km\n";
        cout << "9. Punjab National Bank - 15 km\n";
        cout << "10. Union Bank of India - 16 km\n";
    }
     else if (city_name == "Hubballi")
     {
        cout << "Banks in Hubballi:\n";
        cout << "1. State Bank of India - 8 km\n";
        cout << "2. ICICI Bank - 6 km\n";
        cout << "3. HDFC Bank - 9 km\n";
        cout << "4. Axis Bank - 5 km\n";
        cout << "5. Kotak Mahindra Bank - 12 km\n";
        cout << "6. Canara Bank - 7 km\n";
        cout << "7. Bank of Baroda - 10 km\n";
        cout << "8. IDFC First Bank - 14 km\n";
        cout << "9. Punjab National Bank - 15 km\n";
        cout << "10. Union Bank of India - 18 km\n";
    }
     else if (city_name == "Mangalore")
     {
        cout << "Banks in Mangalore:\n";
        cout << "1. State Bank of India - 5 km\n";
        cout << "2. ICICI Bank - 7 km\n";
        cout << "3. HDFC Bank - 9 km\n";
        cout << "4. Axis Bank - 6 km\n";
        cout << "5. Kotak Mahindra Bank - 10 km\n";
        cout << "6. Canara Bank - 8 km\n";
        cout << "7. Bank of Baroda - 12 km\n";
        cout << "8. IDFC First Bank - 11 km\n";
        cout << "9. Punjab National Bank - 15 km\n";
        cout << "10. Union Bank of India - 14 km\n";
    }
     else if (city_name == "Udupi")
     {
        cout << "Banks in Udupi:\n";
        cout << "1. State Bank of India - 3 km\n";
        cout << "2. ICICI Bank - 6 km\n";
        cout << "3. HDFC Bank - 8 km\n";
        cout << "4. Axis Bank - 7 km\n";
        cout << "5. Kotak Mahindra Bank - 10 km\n";
        cout << "6. Canara Bank - 12 km\n";
        cout << "7. Bank of Baroda - 9 km\n";
        cout << "8. IDFC First Bank - 14 km\n";
        cout << "9. Punjab National Bank - 13 km\n";
        cout << "10. Union Bank of India - 15 km\n";
    }
    else if (city_name == "Belagavi")
     {
        cout << "Banks in Belagavi:\n";
        cout << "1. State Bank of India - 5 km\n";
        cout << "2. ICICI Bank - 7 km\n";
        cout << "3. HDFC Bank - 8 km\n";
        cout << "4. Axis Bank - 9 km\n";
        cout << "5. Kotak Mahindra Bank - 10 km\n";
        cout << "6. Canara Bank - 6 km\n";
        cout << "7. Bank of Baroda - 11 km\n";
        cout << "8. IDFC First Bank - 13 km\n";
        cout << "9. Punjab National Bank - 12 km\n";
        cout << "10. Union Bank of India - 14 km\n";
    }
     else if (city_name == "Kalaburagi")
     {
        cout << "Banks in Kalaburagi:\n";
        cout << "1. State Bank of India - 6 km\n";
        cout << "2. ICICI Bank - 7 km\n";
        cout << "3. HDFC Bank - 9 km\n";
        cout << "4. Axis Bank - 8 km\n";
        cout << "5. Kotak Mahindra Bank - 12 km\n";
        cout << "6. Canara Bank - 10 km\n";
        cout << "7. Bank of Baroda - 11 km\n";
        cout << "8. IDFC First Bank - 15 km\n";
        cout << "9. Punjab National Bank - 14 km\n";
        cout << "10. Union Bank of India - 16 km\n";
    }
    else if (city_name == "Chikkamagaluru")
     {
        cout << "Banks in Chikkamagaluru:\n";
        cout << "1. State Bank of India - 5 km\n";
        cout << "2. ICICI Bank - 6 km\n";
        cout << "3. HDFC Bank - 8 km\n";
        cout << "4. Axis Bank - 7 km\n";
        cout << "5. Kotak Mahindra Bank - 10 km\n";
        cout << "6. Canara Bank - 9 km\n";
        cout << "7. Bank of Baroda - 12 km\n";
        cout << "8. IDFC First Bank - 11 km\n";
        cout << "9. Punjab National Bank - 15 km\n";
        cout << "10. Union Bank of India - 13 km\n";
    }
     else
    {
        cout << "Sorry, the city is not in our list of banks in Karnataka.\n";
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp = temp / 3;
    }

    cout << "The program has completed.\n";

    //return 0;
}


// Function to simulate finding an education firm
void findEducationFirm()
 {
     string city_name;

    // Introduce the user to the program
    cout << "Welcome to the Karnataka City Educational Firm Finder Program!" << endl;
    cout << "Please enter the name of the city to find educational firms: "<< endl;
     cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;
    cin >> city_name;


    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }


    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }

    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }

    // Now back to the city education firm logic
    if (city_name == "Bengaluru" || city_name == "Bangalore")
        {
        cout << "Educational Firms in Bengaluru:\n";
        cout << "1. BYJU'S - 5 km\n";
        cout << "2. Unacademy - 8 km\n";
        cout << "3. Vedantu - 10 km\n";
        cout << "4. Simplilearn - 12 km\n";
        cout << "5. Toppr - 15 km\n";
        cout << "6. TalentSprint - 7 km\n";
        cout << "7. Testbook - 9 km\n";
        cout << "8. Physics Wallah - 6 km\n";
        cout << "9. Aakash Institute - 20 km\n";
        cout << "10. Career Launcher - 18 km\n";
    }
    else if (city_name == "Mysuru")
     {
        cout << "Educational Firms in Mysuru:\n";
        cout << "1. BYJU'S - 6 km\n";
        cout << "2. Unacademy - 8 km\n";
        cout << "3. Vedantu - 10 km\n";
        cout << "4. Simplilearn - 7 km\n";
        cout << "5. Toppr - 12 km\n";
        cout << "6. TalentSprint - 9 km\n";
        cout << "7. Testbook - 5 km\n";
        cout << "8. Physics Wallah - 14 km\n";
        cout << "9. Aakash Institute - 15 km\n";
        cout << "10. Career Launcher - 16 km\n";
    }
    else if (city_name == "Hubballi")
     {
        cout << "Educational Firms in Hubballi:\n";
        cout << "1. BYJU'S - 8 km\n";
        cout << "2. Unacademy - 6 km\n";
        cout << "3. Vedantu - 9 km\n";
        cout << "4. Simplilearn - 5 km\n";
        cout << "5. Toppr - 12 km\n";
        cout << "6. TalentSprint - 7 km\n";
        cout << "7. Testbook - 10 km\n";
        cout << "8. Physics Wallah - 14 km\n";
        cout << "9. Aakash Institute - 15 km\n";
        cout << "10. Career Launcher - 18 km\n";
    }
    else if (city_name == "Mangalore")
     {
        cout << "Educational Firms in Mangalore:\n";
        cout << "1. BYJU'S - 5 km\n";
        cout << "2. Unacademy - 7 km\n";
        cout << "3. Vedantu - 9 km\n";
        cout << "4. Simplilearn - 6 km\n";
        cout << "5. Toppr - 10 km\n";
        cout << "6. TalentSprint - 8 km\n";
        cout << "7. Testbook - 12 km\n";
        cout << "8. Physics Wallah - 11 km\n";
        cout << "9. Aakash Institute - 15 km\n";
        cout << "10. Career Launcher - 14 km\n";
    }
     else if (city_name == "Udupi")
     {
        cout << "Educational Firms in Udupi:\n";
        cout << "1. BYJU'S - 3 km\n";
        cout << "2. Unacademy - 6 km\n";
        cout << "3. Vedantu - 8 km\n";
        cout << "4. Simplilearn - 7 km\n";
        cout << "5. Toppr - 10 km\n";
        cout << "6. TalentSprint - 12 km\n";
        cout << "7. Testbook - 9 km\n";
        cout << "8. Physics Wallah - 14 km\n";
        cout << "9. Aakash Institute - 13 km\n";
        cout << "10. Career Launcher - 15 km\n";
    }
    else if (city_name == "Belagavi")
     {
        cout << "Educational Firms in Belagavi:\n";
        cout << "1. BYJU'S - 5 km\n";
        cout << "2. Unacademy - 7 km\n";
        cout << "3. Vedantu - 8 km\n";
        cout << "4. Simplilearn - 9 km\n";
        cout << "5. Toppr - 10 km\n";
        cout << "6. TalentSprint - 6 km\n";
        cout << "7. Testbook - 11 km\n";
        cout << "8. Physics Wallah - 13 km\n";
        cout << "9. Aakash Institute - 12 km\n";
        cout << "10. Career Launcher - 14 km\n";
    }
    else if (city_name == "Kalaburagi")
     {
        cout << "Educational Firms in Kalaburagi:\n";
        cout << "1. BYJU'S - 6 km\n";
        cout << "2. Unacademy - 7 km\n";
        cout << "3. Vedantu - 9 km\n";
        cout << "4. Simplilearn - 8 km\n";
        cout << "5. Toppr - 12 km\n";
        cout << "6. TalentSprint - 10 km\n";
        cout << "7. Testbook - 11 km\n";
        cout << "8. Physics Wallah - 15 km\n";
        cout << "9. Aakash Institute - 14 km\n";
        cout << "10. Career Launcher - 16 km\n";
    }
    else if (city_name == "Chikkamagaluru")
     {
        cout << "Educational Firms in Chikkamagaluru:\n";
        cout << "1. BYJU'S - 5 km\n";
        cout << "2. Unacademy - 6 km\n";
        cout << "3. Vedantu - 8 km\n";
        cout << "4. Simplilearn - 7 km\n";
        cout << "5. Toppr - 10 km\n";
        cout << "6. TalentSprint - 9 km\n";
        cout << "7. Testbook - 12 km\n";
        cout << "8. Physics Wallah - 11 km\n";
        cout << "9. Aakash Institute - 15 km\n";
        cout << "10. Career Launcher - 13 km\n";
    }
    else
     {
        cout << "Sorry, the city is not in our list of educational firms in Karnataka.\n";
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp = temp / 3;
    }

    cout << "The program has completed.\n";

    //return 0;
}


// Function to simulate finding a police station
void findPoliceStation()
 {
    string city_name;

    // Introduce the user to the program
    cout << "Welcome to the Karnataka City Police Station Finder Program!" << endl;
    cout << "Please enter the name of the city to find police stations: "<< endl;
     cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;
    cin >> city_name;

    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }


    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
    {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }

    // Now back to the city police station logic
    if (city_name == "Bengaluru" || city_name == "Bangalore")
        {
        cout << "Police Stations in Bengaluru:\n";
        cout << "1. Cubbon Park Police Station - 5 km\n";
        cout << "2. Koramangala Police Station - 8 km\n";
        cout << "3. Hennur Police Station - 10 km\n";
        cout << "4. Jayanagar Police Station - 12 km\n";
        cout << "5. Whitefield Police Station - 15 km\n";
        cout << "6. Malleswaram Police Station - 7 km\n";
        cout << "7. Vijayanagar Police Station - 9 km\n";
        cout << "8. Indiranagar Police Station - 6 km\n";
        cout << "9. Shivajinagar Police Station - 20 km\n";
        cout << "10. Basavanagudi Police Station - 18 km\n";
    }
    else if (city_name == "Mysuru")
     {
        cout << "Police Stations in Mysuru:\n";
        cout << "1. Mysuru Police Station - 6 km\n";
        cout << "2. Jayanagar Police Station - 8 km\n";
        cout << "3. Vijayanagar Police Station - 10 km\n";
        cout << "4. Nanjangud Police Station - 7 km\n";
        cout << "5. Hunsur Police Station - 12 km\n";
        cout << "6. Kuvempunagar Police Station - 9 km\n";
        cout << "7. Hebbal Police Station - 5 km\n";
        cout << "8. Bannimantap Police Station - 14 km\n";
        cout << "9. Lashkar Police Station - 15 km\n";
        cout << "10. Bogadi Police Station - 16 km\n";
    }
     else if (city_name == "Hubballi")
    {
        cout << "Police Stations in Hubballi:\n";
        cout << "1. Hubballi Police Station - 8 km\n";
        cout << "2. Vidyanagar Police Station - 6 km\n";
        cout << "3. Gokul Road Police Station - 9 km\n";
        cout << "4. Deshpande Nagar Police Station - 5 km\n";
        cout << "5. Subhash Nagar Police Station - 12 km\n";
        cout << "6. Shree Nagar Police Station - 7 km\n";
        cout << "7. Unkal Police Station - 10 km\n";
        cout << "8. Keshwapur Police Station - 14 km\n";
        cout << "9. BVB Police Station - 15 km\n";
        cout << "10. Kamalapur Police Station - 18 km\n";
    }
    else if (city_name == "Mangalore")
    {
        cout << "Police Stations in Mangalore:\n";
        cout << "1. Mangalore Police Station - 5 km\n";
        cout << "2. Pandeshwar Police Station - 7 km\n";
        cout << "3. Bunder Police Station - 9 km\n";
        cout << "4. Suratkal Police Station - 6 km\n";
        cout << "5. Kankanady Police Station - 10 km\n";
        cout << "6. Kavoor Police Station - 8 km\n";
        cout << "7. Bajal Police Station - 12 km\n";
        cout << "8. Ullal Police Station - 11 km\n";
        cout << "9. Nellikai Police Station - 15 km\n";
        cout << "10. Mulki Police Station - 14 km\n";
    }
     else if (city_name == "Udupi")
     {
        cout << "Police Stations in Udupi:\n";
        cout << "1. Udupi Police Station - 3 km\n";
        cout << "2. Malpe Police Station - 6 km\n";
        cout << "3. Kadiyali Police Station - 8 km\n";
        cout << "4. Padubidri Police Station - 7 km\n";
        cout << "5. Manipal Police Station - 10 km\n";
        cout << "6. Hiriyadka Police Station - 12 km\n";
        cout << "7. Santhekatte Police Station - 9 km\n";
        cout << "8. Brahmavara Police Station - 14 km\n";
        cout << "9. Kota Police Station - 13 km\n";
        cout << "10. Shankarpura Police Station - 15 km\n";
    }
    else if (city_name == "Belagavi")
     {
        cout << "Police Stations in Belagavi:\n";
        cout << "1. Belagavi Police Station - 5 km\n";
        cout << "2. Camp Police Station - 7 km\n";
        cout << "3. Rani Channamma Nagar Police Station - 8 km\n";
        cout << "4. Hidkal Police Station - 9 km\n";
        cout << "5. Kakti Police Station - 10 km\n";
        cout << "6. Shahapur Police Station - 6 km\n";
        cout << "7. Hukeri Police Station - 11 km\n";
        cout << "8. Khanapur Police Station - 14 km\n";
        cout << "9. Savadatti Police Station - 15 km\n";
        cout << "10. Gokak Police Station - 18 km\n";
    }
     else if (city_name == "Kalaburagi")
     {
        cout << "Police Stations in Kalaburagi:\n";
        cout << "1. Kalaburagi Police Station - 6 km\n";
        cout << "2. Aland Police Station - 7 km\n";
        cout << "3. Sedam Police Station - 9 km\n";
        cout << "4. Chincholi Police Station - 8 km\n";
        cout << "5. Jewargi Police Station - 12 km\n";
        cout << "6. Afzalpur Police Station - 10 km\n";
        cout << "7. Wadi Police Station - 11 km\n";
        cout << "8. Shahabad Police Station - 14 km\n";
        cout << "9. Yadgir Police Station - 15 km\n";
        cout << "10. Raichur Police Station - 16 km\n";
    }
    else if (city_name == "Chikkamagaluru")
     {
        cout << "Police Stations in Chikkamagaluru:\n";
        cout << "1. Chikkamagaluru Police Station - 5 km\n";
        cout << "2. Kadur Police Station - 6 km\n";
        cout << "3. Tarikere Police Station - 8 km\n";
        cout << "4. Koppa Police Station - 7 km\n";
        cout << "5. Sringeri Police Station - 10 km\n";
        cout << "6. Mudigere Police Station - 9 km\n";
        cout << "7. N.R. Pura Police Station - 12 km\n";
        cout << "8. Halli Police Station - 11 km\n";
        cout << "9. Aldur Police Station - 15 km\n";
        cout << "10. Chikmagalur City Police Station - 13 km\n";
    }
     else
    {
        cout << "Sorry, the city is not in our list";
}
}

// Function to simulate finding a fire brigade
void findFireBrigade()
 {

    string city_name;

    // Introduce the user to the program by dijkstras algorithm
    cout << "Welcome to the Karnataka City Fire Brigade Finder Program!" << endl;
    cout << "Please enter the name of the city to find fire stations: "<< endl;
     cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;
    cin >> city_name;


    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }


    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }

    // Now back to the city fire brigade logic
    if (city_name == "Bengaluru" || city_name == "Bangalore")
        {
        cout << "Fire Stations in Bengaluru:\n";
        cout << "1. Cubbon Park Fire Station - 5 km\n";
        cout << "2. Koramangala Fire Station - 8 km\n";
        cout << "3. Hennur Fire Station - 10 km\n";
        cout << "4. Jayanagar Fire Station - 12 km\n";
        cout << "5. Whitefield Fire Station - 15 km\n";
        cout << "6. Malleswaram Fire Station - 7 km\n";
        cout << "7. Vijayanagar Fire Station - 9 km\n";
        cout << "8. Indiranagar Fire Station - 6 km\n";
        cout << "9. Shivajinagar Fire Station - 20 km\n";
        cout << "10. Basavanagudi Fire Station - 18 km\n";
    }
    else if (city_name == "Mysuru")
     {
        cout << "Fire Stations in Mysuru:\n";
        cout << "1. Mysuru Fire Station - 6 km\n";
        cout << "2. Jayanagar Fire Station - 8 km\n";
        cout << "3. Vijayanagar Fire Station - 10 km\n";
        cout << "4. Nanjangud Fire Station - 7 km\n";
        cout << "5. Hunsur Fire Station - 12 km\n";
        cout << "6. Kuvempunagar Fire Station - 9 km\n";
        cout << "7. Hebbal Fire Station - 5 km\n";
        cout << "8. Bannimantap Fire Station - 14 km\n";
        cout << "9. Lashkar Fire Station - 15 km\n";
        cout << "10. Bogadi Fire Station - 16 km\n";
    }
    else if (city_name == "Hubballi")
     {
        cout << "Fire Stations in Hubballi:\n";
        cout << "1. Hubballi Fire Station - 8 km\n";
        cout << "2. Vidyanagar Fire Station - 6 km\n";
        cout << "3. Gokul Road Fire Station - 9 km\n";
        cout << "4. Deshpande Nagar Fire Station - 5 km\n";
        cout << "5. Subhash Nagar Fire Station - 12 km\n";
        cout << "6. Shree Nagar Fire Station - 7 km\n";
        cout << "7. Unkal Fire Station - 10 km\n";
        cout << "8. Keshwapur Fire Station - 14 km\n";
        cout << "9. BVB Fire Station - 15 km\n";
        cout << "10. Kamalapur Fire Station - 18 km\n";
    }
    else if (city_name == "Mangalore")
     {
        cout << "Fire Stations in Mangalore:\n";
        cout << "1. Mangalore Fire Station - 5 km\n";
        cout << "2. Pandeshwar Fire Station - 7 km\n";
        cout << "3. Bunder Fire Station - 9 km\n";
        cout << "4. Suratkal Fire Station - 6 km\n";
        cout << "5. Kankanady Fire Station - 10 km\n";
        cout << "6. Kavoor Fire Station - 8 km\n";
        cout << "7. Bajal Fire Station - 12 km\n";
        cout << "8. Ullal Fire Station - 11 km\n";
        cout << "9. Nellikai Fire Station - 15 km\n";
        cout << "10. Mulki Fire Station - 14 km\n";
    }
    else if (city_name == "Udupi")
     {
        cout << "Fire Stations in Udupi:\n";
        cout << "1. Udupi Fire Station - 3 km\n";
        cout << "2. Malpe Fire Station - 6 km\n";
        cout << "3. Kadiyali Fire Station - 8 km\n";
        cout << "4. Padubidri Fire Station - 7 km\n";
        cout << "5. Manipal Fire Station - 10 km\n";
        cout << "6. Hiriyadka Fire Station - 12 km\n";
        cout << "7. Santhekatte Fire Station - 9 km\n";
        cout << "8. Brahmavara Fire Station - 14 km\n";
        cout << "9. Kota Fire Station - 13 km\n";
        cout << "10. Shankarpura Fire Station - 15 km\n";
    }
    else if (city_name == "Belagavi")
     {
        cout << "Fire Stations in Belagavi:\n";
        cout << "1. Belagavi Fire Station - 5 km\n";
        cout << "2. Camp Fire Station - 7 km\n";
        cout << "3. Rani Channamma Nagar Fire Station - 8 km\n";
        cout << "4. Hidkal Fire Station - 9 km\n";
        cout << "5. Kakti Fire Station - 10 km\n";
        cout << "6. Shahapur Fire Station - 6 km\n";
        cout << "7. Hukeri Fire Station - 11 km\n";
        cout << "8. Khanapur Fire Station - 14 km\n";
        cout << "9. Savadatti Fire Station - 15 km\n";
        cout << "10. Gokak Fire Station - 18 km\n";
    }
    else if (city_name == "Kalaburagi")
     {
        cout << "Fire Stations in Kalaburagi:\n";
        cout << "1. Kalaburagi Fire Station - 6 km\n";
        cout << "2. Aland Fire Station - 7 km\n";
        cout << "3. Sedam Fire Station - 9 km\n";
        cout << "4. Chincholi Fire Station - 8 km\n";
        cout << "5. Jewargi Fire Station - 12 km\n";
        cout << "6. Afzalpur Fire Station - 10 km\n";
        cout << "7. Wadi Fire Station - 11 km\n";
        cout << "8. Shahabad Fire Station - 14 km\n";
        cout << "9. Yadgir Fire Station - 15 km\n";
        cout << "10. Raichur Fire Station - 16 km\n";
    }
    else if (city_name == "Chikkamagaluru")
     {
        cout << "Fire Stations in Chikkamagaluru:\n";
        cout << "1. Chikkamagaluru Fire Station - 5 km\n";
        cout << "2. Kadur Fire Station - 6 km\n";
        cout << "3. Tarikere Fire Station - 8 km\n";
        cout << "4. Koppa Fire Station - 7 km\n";
        cout << "5. Sringeri Fire Station - 10 km\n";
        cout << "6. Mudigere Fire Station - 9 km\n";
        cout << "7. N.R. Pura Fire Station - 12 km\n";
        cout << "8. Halli Fire Station - 11 km\n";
        cout << "9. Aldur Fire Station - 15 km\n";
        cout << "10. Chikmagalur City Fire Station - 13 km\n";
    }
    else
     {
        cout << "Sorry, the city in not in list ";
}
}

// Function to simulate finding the nearest transport hub
void findportHub()
{
    string city_name;

    // Introduce the user to the program
    cout << "Welcome to the Karnataka City Ship Port Finder Program!" << endl;
    cout << "Please enter the name of the city to find ship ports: "<< endl;
     cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;
    cin >> city_name;


    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }


    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }

    // Now back to the city ship port logic
    if (city_name == "Mangalore")
        {
        cout << "Ship Ports in Mangalore:\n";
        cout << "1. New Mangalore Port - 5 km\n";
        cout << "2. Old Mangalore Port - 6 km\n";
        cout << "3. Panambur Port - 7 km\n";
        cout << "4. Bunder Port - 9 km\n";
        cout << "5. Surathkal Port - 10 km\n";
        cout << "6. Tannirbhavi Port - 8 km\n";
        cout << "7. Belapu Port - 12 km\n";
        cout << "8. Ullal Port - 14 km\n";
        cout << "9. Nellikai Port - 13 km\n";
        cout << "10. Mulki Port - 15 km\n";
    }
     else if (city_name == "Karwar")
     {
        cout << "Ship Ports in Karwar:\n";
        cout << "1. Karwar Port - 5 km\n";
        cout << "2. Haladi Port - 8 km\n";
        cout << "3. Baithkol Port - 10 km\n";
        cout << "4. Kurumgad Island Port - 12 km\n";
        cout << "5. Majali Port - 9 km\n";
        cout << "6. Honavar Port - 15 km\n";
        cout << "7. Devbagh Port - 18 km\n";
        cout << "8. Tilmatti Port - 16 km\n";
        cout << "9. Malpe Port - 20 km\n";
        cout << "10. Naringana Port - 22 km\n";
    }
    else if (city_name == "Udupi")
     {
        cout << "Ship Ports in Udupi:\n";
        cout << "1. Malpe Port - 5 km\n";
        cout << "2. Padubidri Port - 7 km\n";
        cout << "3. Kadiyali Port - 8 km\n";
        cout << "4. Manipal Port - 10 km\n";
        cout << "5. Santhekatte Port - 9 km\n";
        cout << "6. Brahmavara Port - 12 km\n";
        cout << "7. Kota Port - 13 km\n";
        cout << "8. Shankarpura Port - 15 km\n";
        cout << "9. Malpe Fishing Port - 16 km\n";
        cout << "10. Udupi Port - 14 km\n";
    }
    else if (city_name == "Belagavi")
     {
        cout << "Ship Ports in Belagavi:\n";
        cout << "1. Belagavi Port - 5 km\n";
        cout << "2. Gokak Port - 8 km\n";
        cout << "3. Khanapur Port - 10 km\n";
        cout << "4. Savadatti Port - 12 km\n";
        cout << "5. Kakti Port - 9 km\n";
        cout << "6. Hidkal Port - 15 km\n";
        cout << "7. Belgaum Cargo Port - 13 km\n";
        cout << "8. Chikodi Port - 14 km\n";
        cout << "9. Raibag Port - 16 km\n";
        cout << "10. Gokak River Port - 18 km\n";
    }
    else if (city_name == "Mysuru")
     {
        cout << "Ship Ports in Mysuru:\n";
        cout << "1. Mysuru Port - 5 km\n";
        cout << "2. Nanjangud Port - 8 km\n";
        cout << "3. Hunsur Port - 10 km\n";
        cout << "4. Kuvempunagar Port - 12 km\n";
        cout << "5. Bannimantap Port - 15 km\n";
        cout << "6. Lashkar Port - 14 km\n";
        cout << "7. Bogadi Port - 13 km\n";
        cout << "8. Lashkar Port - 18 km\n";
        cout << "9. T. Narasipur Port - 16 km\n";
        cout << "10. H D Kote Port - 20 km\n";
    }
     else if (city_name == "Bengaluru")
    {
        cout << "Ship Ports in Bengaluru:\n";
        cout << "1. Old Bangalore Port - 10 km\n";
        cout << "2. Yelahanka Port - 12 km\n";
        cout << "3. Whitefield Port - 14 km\n";
        cout << "4. Koramangala Port - 16 km\n";
        cout << "5. Hennur Port - 18 km\n";
        cout << "6. Jayanagar Port - 20 km\n";
        cout << "7. Hebbal Port - 22 km\n";
        cout << "8. Malleswaram Port - 24 km\n";
        cout << "9. Indiranagar Port - 26 km\n";
        cout << "10. Cubbon Park Port - 28 km\n";
    }
    else if (city_name == "Hubballi")
     {
        cout << "Ship Ports in Hubballi:\n";
        cout << "1. Hubballi Port - 8 km\n";
        cout << "2. Gokul Road Port - 9 km\n";
        cout << "3. Deshpande Nagar Port - 5 km\n";
        cout << "4. Unkal Port - 10 km\n";
        cout << "5. Keshwapur Port - 11 km\n";
        cout << "6. Kamalapur Port - 15 km\n";
        cout << "7. Subhash Nagar Port - 12 km\n";
        cout << "8. Vidyanagar Port - 7 km\n";
        cout << "9. BVB Port - 14 km\n";
        cout << "10. Hulagur Port - 18 km\n";
    }
        else
    {
        cout << "Sorry, the city is not in our list of ports." << endl;
    }

    // Final used block of logic
    if (usedVar1 > 10)
        {
        cout << "System reached an used block of code." << endl;
    }

    //return 0;
}

void findairport()
{
 string city_name;

    // Introduce the user to the program
    cout << "Welcome to the Karnataka City Airport Finder Program!" << endl;
    cout << "Please enter the name of the city to find airports: "<< endl;
     cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;
    cin >> city_name;


    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }


    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }


    if (city_name == "Bengaluru")
        {
        cout << "Airports in Bengaluru:\n";
        cout << "1. Kempegowda International Airport - 30 km\n";
        cout << "2. HAL Airport (old) - 12 km\n";
        cout << "3. Devanahalli Airport - 35 km\n";
        cout << "4. Yelahanka Airport - 20 km\n";
        cout << "5. Whitefield Airport - 25 km\n";
        cout << "6. Hebbal Airport - 18 km\n";
        cout << "7. Malleswaram Airport - 22 km\n";
        cout << "8. Koramangala Airport - 15 km\n";
        cout << "9. Jayanagar Airport - 28 km\n";
        cout << "10. Hennur Airport - 30 km\n";
    }
    else if (city_name == "Mysuru")
     {
        cout << "Airports in Mysuru:\n";
        cout << "1. Mysuru Airport - 15 km\n";
        cout << "2. Nanjangud Airport - 12 km\n";
        cout << "3. Hunsur Airport - 18 km\n";
        cout << "4. Kuvempunagar Airport - 9 km\n";
        cout << "5. Bannimantap Airport - 5 km\n";
        cout << "6. Lashkar Airport - 7 km\n";
        cout << "7. Bogadi Airport - 10 km\n";
        cout << "8. H.D. Kote Airport - 20 km\n";
        cout << "9. T. Narasipur Airport - 30 km\n";
        cout << "10. KRS Airport - 25 km\n";
    }
    else if (city_name == "Hubballi")
    {
        cout << "Airports in Hubballi:\n";
        cout << "1. Hubballi Airport - 5 km\n";
        cout << "2. Gokul Road Airport - 8 km\n";
        cout << "3. Deshpande Nagar Airport - 10 km\n";
        cout << "4. Unkal Airport - 12 km\n";
        cout << "5. Keshwapur Airport - 7 km\n";
        cout << "6. Kamalapur Airport - 15 km\n";
        cout << "7. Subhash Nagar Airport - 14 km\n";
        cout << "8. Vidyanagar Airport - 6 km\n";
        cout << "9. BVB Airport - 18 km\n";
        cout << "10. Hulagur Airport - 20 km\n";
    }
    else if (city_name == "Mangalore")
    {
        cout << "Airports in Mangalore:\n";
        cout << "1. Mangalore International Airport - 10 km\n";
        cout << "2. Panambur Airport - 12 km\n";
        cout << "3. Tannirbhavi Airport - 15 km\n";
        cout << "4. Ullal Airport - 18 km\n";
        cout << "5. Surathkal Airport - 20 km\n";
        cout << "6. Belapu Airport - 13 km\n";
        cout << "7. Nellikai Airport - 14 km\n";
        cout << "8. Kankanady Airport - 16 km\n";
        cout << "9. Mulki Airport - 17 km\n";
        cout << "10. Bajal Airport - 19 km\n";
    }
    else if (city_name == "Udupi")
    {
        cout << "Airports in Udupi:\n";
        cout << "1. Udupi Airport - 5 km\n";
        cout << "2. Malpe Airport - 7 km\n";
        cout << "3. Kadiyali Airport - 8 km\n";
        cout << "4. Manipal Airport - 10 km\n";
        cout << "5. Santhekatte Airport - 12 km\n";
        cout << "6. Brahmavara Airport - 14 km\n";
        cout << "7. Shankarpura Airport - 16 km\n";
        cout << "8. Kota Airport - 18 km\n";
        cout << "9. Padubidri Airport - 20 km\n";
        cout << "10. Shirlalu Airport - 22 km\n";
    }
    else if (city_name == "Belagavi")
     {
        cout << "Airports in Belagavi:\n";
        cout << "1. Belagavi Airport - 10 km\n";
        cout << "2. Gokak Airport - 8 km\n";
        cout << "3. Khanapur Airport - 12 km\n";
        cout << "4. Savadatti Airport - 15 km\n";
        cout << "5. Kakti Airport - 18 km\n";
        cout << "6. Hidkal Airport - 14 km\n";
        cout << "7. Belgaum Cargo Airport - 20 km\n";
        cout << "8. Raibag Airport - 22 km\n";
        cout << "9. Gokak River Airport - 25 km\n";
        cout << "10. Konnur Airport - 28 km\n";
    }
    else if (city_name == "Kalaburagi")
     {
        cout << "Airports in Kalaburagi:\n";
        cout << "1. Kalaburagi Airport - 10 km\n";
        cout << "2. Aland Airport - 8 km\n";
        cout << "3. Sedam Airport - 12 km\n";
        cout << "4. Chincholi Airport - 15 km\n";
        cout << "5. Jewargi Airport - 18 km\n";
        cout << "6. Afzalpur Airport - 14 km\n";
        cout << "7. Wadi Airport - 16 km\n";
        cout << "8. Shahabad Airport - 20 km\n";
        cout << "9. Yadgir Airport - 22 km\n";
        cout << "10. Raichur Airport - 25 km\n";
    }
    else if (city_name == "Chikkamagaluru")
     {
        cout << "Airports in Chikkamagaluru:\n";
        cout << "1. Chikkamagaluru Airport - 5 km\n";
        cout << "2. Kadur Airport - 7 km\n";
        cout << "3. Tarikere Airport - 9 km\n";
        cout << "4. Koppa Airport - 10 km\n";
        cout << "5. Sringeri Airport - 15 km\n";
        cout << "6. Mudigere Airport - 13 km\n";
        cout << "7. N.R. Pura Airport - 18 km\n";
        cout << "8. Halli Airport - 20 km\n";
        cout << "9. Aldur Airport - 22 km\n";
        cout << "10. Chikmagalur City Airport - 25 km\n";
    }
     else
     {
        cout << "Sorry, the city is not in our list of airports." << endl;
    }


    if (usedVar1 > 10)
        {
        cout << "System reached an used block of code." << endl;
    }

    //return 0;
}
void findpostoffice()
{
    string city_name;

    // Introduce the user to the program
    cout << "Welcome to the Karnataka City Post Office Finder Program!" << endl;
    cout << "Please enter the name of the city to find post offices: "<< endl;
     cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;
    cin >> city_name;


    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }


    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }

    // Now back to the city post office logic
    if (city_name == "Bengaluru")
        {
        cout << "Post Offices in Bengaluru:\n";
        cout << "1. Malleswaram Post Office - 5 km\n";
        cout << "2. Jayanagar Post Office - 6 km\n";
        cout << "3. Koramangala Post Office - 8 km\n";
        cout << "4. Indiranagar Post Office - 7 km\n";
        cout << "5. Whitefield Post Office - 10 km\n";
        cout << "6. Hebbal Post Office - 12 km\n";
        cout << "7. Yelahanka Post Office - 15 km\n";
        cout << "8. HSR Layout Post Office - 9 km\n";
        cout << "9. Banashankari Post Office - 11 km\n";
        cout << "10. Rajajinagar Post Office - 13 km\n";
    }
 else if (city_name == "Mysuru")
    {
        cout << "Post Offices in Mysuru:\n";
        cout << "1. Mysuru City Post Office - 5 km\n";
        cout << "2. Nanjangud Post Office - 10 km\n";
        cout << "3. Hunsur Post Office - 15 km\n";
        cout << "4. Kuvempunagar Post Office - 7 km\n";
        cout << "5. Bannimantap Post Office - 4 km\n";
        cout << "6. Lashkar Post Office - 9 km\n";
        cout << "7. Bogadi Post Office - 8 km\n";
        cout << "8. H.D. Kote Post Office - 20 km\n";
        cout << "9. T. Narasipur Post Office - 25 km\n";
        cout << "10. KRS Post Office - 22 km\n";
    }
    else if (city_name == "Hubballi")
        {
        cout << "Post Offices in Hubballi:\n";
        cout << "1. Hubballi Main Post Office - 5 km\n";
        cout << "2. Gokul Road Post Office - 7 km\n";
        cout << "3. Deshpande Nagar Post Office - 9 km\n";
        cout << "4. Unkal Post Office - 8 km\n";
        cout << "5. Keshwapur Post Office - 10 km\n";
        cout << "6. Kamalapur Post Office - 12 km\n";
        cout << "7. Subhash Nagar Post Office - 6 km\n";
        cout << "8. Vidyanagar Post Office - 11 km\n";
        cout << "9. BVB Post Office - 15 km\n";
        cout << "10. Hulagur Post Office - 14 km\n";
    }
    else if (city_name == "Mangalore")
    {
        cout << "Post Offices in Mangalore:\n";
        cout << "1. Mangalore City Post Office - 4 km\n";
        cout << "2. Panambur Post Office - 6 km\n";
        cout << "3. Tannirbhavi Post Office - 8 km\n";
        cout << "4. Ullal Post Office - 9 km\n";
        cout << "5. Surathkal Post Office - 10 km\n";
        cout << "6. Belapu Post Office - 11 km\n";
        cout << "7. Nellikai Post Office - 7 km\n";
        cout << "8. Kankanady Post Office - 5 km\n";
        cout << "9. Mulki Post Office - 12 km\n";
        cout << "10. Bajal Post Office - 13 km\n";
    }
    else if (city_name == "Udupi")
        {
        cout << "Post Offices in Udupi:\n";
        cout << "1. Udupi City Post Office - 3 km\n";
        cout << "2. Malpe Post Office - 5 km\n";
        cout << "3. Kadiyali Post Office - 6 km\n";
        cout << "4. Manipal Post Office - 7 km\n";
        cout << "5. Santhekatte Post Office - 8 km\n";
        cout << "6. Brahmavara Post Office - 10 km\n";
        cout << "7. Shankarpura Post Office - 9 km\n";
        cout << "8. Kota Post Office - 12 km\n";
        cout << "9. Padubidri Post Office - 13 km\n";
        cout << "10. Shirlalu Post Office - 15 km\n";
    }
    else if (city_name == "Belagavi")
        {
        cout << "Post Offices in Belagavi:\n";
        cout << "1. Belagavi City Post Office - 5 km\n";
        cout << "2. Gokak Post Office - 8 km\n";
        cout << "3. Khanapur Post Office - 10 km\n";
        cout << "4. Savadatti Post Office - 12 km\n";
        cout << "5. Kakti Post Office - 15 km\n";
        cout << "6. Hidkal Post Office - 14 km\n";
        cout << "7. Belgaum Post Office - 18 km\n";
        cout << "8. Raibag Post Office - 20 km\n";
        cout << "9. Gokak River Post Office - 22 km\n";
        cout << "10. Konnur Post Office - 25 km\n";
    }
    else if (city_name == "Kalaburagi")
        {
        cout << "Post Offices in Kalaburagi:\n";
        cout << "1. Kalaburagi City Post Office - 5 km\n";
        cout << "2. Aland Post Office - 10 km\n";
        cout << "3. Sedam Post Office - 12 km\n";
        cout << "4. Chincholi Post Office - 15 km\n";
        cout << "5. Jewargi Post Office - 20 km\n";
        cout << "6. Afzalpur Post Office - 18 km\n";
        cout << "7. Wadi Post Office - 16 km\n";
        cout << "8. Shahabad Post Office - 20 km\n";
        cout << "9. Yadgir Post Office - 22 km\n";
        cout << "10. Raichur Post Office - 25 km\n";
    }
    else if (city_name == "Chikkamagaluru")
    {
        cout << "Post Offices in Chikkamagaluru:\n";
        cout << "1. Chikkamagaluru City Post Office - 4 km\n";
        cout << "2. Kadur Post Office - 7 km\n";
        cout << "3. Tarikere Post Office - 9 km\n";
        cout << "4. Koppa Post Office - 10 km\n";
        cout << "5. Sringeri Post Office - 12 km\n";
        cout << "6. Mudigere Post Office - 13 km\n";
        cout << "7. N.R. Pura Post Office - 14 km\n";
        cout << "8. Halli Post Office - 15 km\n";
        cout << "9. Aldur Post Office - 16 km\n";
        cout << "10. Chikmagalur Post Office - 18 km\n";
    }
     else
     {
        cout << "Sorry, the city is not in our list of post";
}
}
void findgarden()
{
    string city_name;

    // Introduce the user to the program
    cout << "Welcome to the Karnataka City Garden Finder Program!" << endl;
    cout << "Please enter the name of the city to find gardens: "<<endl;
     cout << "-------list of cities-------"<< endl;
    cout << "Bangalore"<< endl;
    cout << "Mysuru"<< endl;
    cout << "Hubballi"<< endl;
    cout << "Mangalore"<< endl;
    cout << "Udupi"<< endl;
    cout << "Belagavi"<< endl;
    cout << "Kalaburagi"<< endl;
    cout << "Chikkamagaluru"<< endl;
    cin >> city_name;


    int usedVar1 = 0;
    double usedVar2 = 3.14;
    char usedChar = 'A';
    bool usedBool = true;
    string mainString = "This is a main string";

    for (int i = 0; i < 1000; i++)
        {
        usedVar1++;
        usedVar2 *= 1.01;
    }

    while (usedBool)
        {
        usedVar2 -= 0.02;
        usedVar1--;
        if (usedVar1 == 50) break;
    }


    if (usedVar2 > 3.0)
        {
        usedVar1 += 10;
    }

    switch (usedVar1)
     {
        case 0:
            usedBool = false;
            break;
        case 1:
            usedVar2 *= 2;
            break;
        default:
            usedVar1 += 5;
            break;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        {
        arr[i] = arr[i] * 2;
    }


    for (int i = 0; i < 100; i++)
        {
        int temp = i * i;
        temp /= 2;
    }

    // Now back to the city garden logic
    if (city_name == "Bengaluru")
        {
        cout << "Gardens in Bengaluru:\n";
        cout << "1. Lalbagh Botanical Garden - 5 km\n";
        cout << "2. Cubbon Park - 3 km\n";
        cout << "3. Bangalore Palace Gardens - 8 km\n";
        cout << "4. Hebbal Lake Garden - 10 km\n";
        cout << "5. Bannerghatta Biological Park - 12 km\n";
        cout << "6. Nandi Hills Garden - 20 km\n";
        cout << "7. Freedom Park - 7 km\n";
        cout << "8. Jawaharlal Nehru Planetarium Garden - 6 km\n";
        cout << "9. Malleswaram Park - 4 km\n";
        cout << "10. Agara Lake Park - 15 km\n";
    }
    else if (city_name == "Mysuru")
        {
        cout << "Gardens in Mysuru:\n";
        cout << "1. Brindavan Gardens - 30 km\n";
        cout << "2. Karanji Lake Nature Park - 5 km\n";
        cout << "3. St. Philomena's Church Garden - 6 km\n";
        cout << "4. Chamundi Hill Gardens - 12 km\n";
        cout << "5. Mysuru Zoo Garden - 4 km\n";
        cout << "6. Lalitha Mahal Palace Garden - 7 km\n";
        cout << "7. Krishna Raja Sagara Garden - 25 km\n";
        cout << "8. GRS Fantasy Park - 8 km\n";
        cout << "9. KRS Garden - 22 km\n";
        cout << "10. Brindavan Garden - 35 km\n";
    }
    else if (city_name == "Hubballi")
        {
        cout << "Gardens in Hubballi:\n";
        cout << "1. Unkal Lake Garden - 5 km\n";
        cout << "2. Nrupatunga Hill Garden - 7 km\n";
        cout << "3. Keshwapur Garden - 6 km\n";
        cout << "4. Gokul Road Garden - 9 km\n";
        cout << "5. Indira Gandhi Park - 4 km\n";
        cout << "6. Deshpande Nagar Garden - 3 km\n";
        cout << "7. Kamalapur Garden - 10 km\n";
        cout << "8. Chidambar Garden - 11 km\n";
        cout << "9. Anand Nagar Park - 8 km\n";
        cout << "10. Subhash Nagar Garden - 12 km\n";
    }
    else if (city_name == "Mangalore")
        {
        cout << "Gardens in Mangalore:\n";
        cout << "1. Kadri Hill Park - 5 km\n";
        cout << "2. Pilikula Nisargadhama - 10 km\n";
        cout << "3. Tannirbhavi Beach Garden - 7 km\n";
        cout << "4. Sultan Battery Garden - 8 km\n";
        cout << "5. Someshwar Beach Garden - 15 km\n";
        cout << "6. Gurupura Garden - 12 km\n";
        cout << "7. Panambur Beach Garden - 6 km\n";
        cout << "8. Nellikai Garden - 10 km\n";
        cout << "9. Rosario Church Garden - 9 km\n";
        cout << "10. Kankanady Garden - 7 km\n";
    }
    else if (city_name == "Udupi")
        {
        cout << "Gardens in Udupi:\n";
        cout << "1. Malpe Beach Garden - 8 km\n";
        cout << "2. Kadiyali Garden - 4 km\n";
        cout << "3. Manipal Lake Garden - 7 km\n";
        cout << "4. Brahmavara Garden - 9 km\n";
        cout << "5. Shankarpura Garden - 11 km\n";
        cout << "6. Santhekatte Garden - 6 km\n";
        cout << "7. Shirlalu Garden - 13 km\n";
        cout << "8. Padubidri Garden - 10 km\n";
        cout << "9. Udupi Beach Garden - 5 km\n";
        cout << "10. Kota Garden - 12 km\n";
    }
    else if (city_name == "Belagavi")
        {
        cout << "Gardens in Belagavi:\n";
        cout << "1. Belagavi Fort Garden - 4 km\n";
        cout << "2. Gokak Waterfalls Garden - 12 km\n";
        cout << "3. Gokul Road Garden - 7 km\n";
        cout << "4. Khanapur Garden - 9 km\n";
        cout << "5. Savadatti Garden - 13 km\n";
        cout << "6. Hidkal Garden - 10 km\n";
        cout << "7. Kakti Garden - 15 km\n";
        cout << "8. Belgaum Lake Garden - 6 km\n";
        cout << "9. Raibag Garden - 20 km\n";
        cout << "10. Gokak River Garden - 18 km\n";
    }
    else if (city_name == "Kalaburagi")
        {
        cout << "Gardens in Kalaburagi:\n";
        cout << "1. Kalaburagi Lake Garden - 6 km\n";
        cout << "2. Aland Garden - 10 km\n";
        cout << "3. Sedam Garden - 12 km\n";
        cout << "4. Chincholi Garden - 14 km\n";
        cout << "5. Jewargi Garden - 15 km\n";
        cout << "6. Wadi Garden - 18 km\n";
        cout << "7. Shahabad Garden - 20 km\n";
        cout << "8. Yadgir Garden - 22 km\n";
        cout << "9. Raichur Garden - 25 km\n";
        cout << "10. Afzalpur Garden - 11 km\n";
    }
     else if (city_name == "Chikkamagaluru")
        {
        cout << "Gardens in Chikkamagaluru:\n";
        cout << "1. Chikkamagaluru Garden - 5 km\n";
        cout << "2. Kadur Garden - 7 km\n";
        cout << "3. Tarikere Garden - 9 km\n";
        cout << "4. Koppa Garden - 10 km\n";
        cout << "5. Sringeri Garden - 15 km\n";
        cout << "6. Mudigere Garden - 13 km\n";
        cout << "7. N.R. Pura Garden - 14 km\n";
        cout << "8. Halli Garden - 16 km\n";
        cout << "9. Aldur Garden - 18 km\n";
        cout << "10. Chikmagalur Garden - 20 km\n";
    }
    else
     {
        cout << "Sorry, the city is not in our list of gardens." << endl;
    }


    if (usedVar1 > 10)
        {
        cout << "System reached an used block of code." << endl;
    }

   // return 0;

}
void dijkstra(int src, const std::vector<std::vector<std::pair<int, int>>>& graph, std::vector<int>& dist)
{
    int n = graph.size();
    dist.assign(n, INF); // Initialize distances to infinity
    dist[src] = 0;

    // Priority queue to store (distance, vertex), with the smallest distance at the top
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        int currDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // If the distance is greater than the recorded distance, skip this node
        if (currDist > dist[u])
        {
            continue;
        }

        // Iterate over neighbors of vertex `u`
        for (const auto& [v, weight] : graph[u])
        {
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int dijstras()
 {
    int n, m; // Number of vertices and edges
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    // Graph represented as an adjacency list
    // Each pair represents (neighbor, weight)
    vector<vector<pair<int, int>>> graph(n);

    cout << "Enter the edges (u v w):\n";
    for (int i = 0; i < m; ++i)
        {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Comment this line for a directed graph
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    vector<int> dist;
    dijkstra(src, graph, dist);

    cout << "Shortest distances from source " << src << ":\n";
    for (int i = 0; i < n; ++i)
     {
        if (dist[i] == INF)
            {
            cout << "Vertex " << i << ": INF\n";
        }
        else
         {
            cout << "Vertex " << i << ": " << dist[i] << "\n";
        }
    }

    return 0;
}



void navigationOptimization()
 {
    int choice;

    while (true)
        {
        // Display menu options
        cout << "\n--- Navigation System ---\n";
        cout << "1. Find Location\n";
        cout << "2. Find Hotel\n";
        cout << "3. Check Traffic\n";
        cout << "4. Find Tourist Attractions\n";
        cout << "5. Find Hospital\n";
        cout << "6. Find Bank\n";
        cout << "7. Find Education Firm\n";
        cout << "8. Find Police Station\n";
        cout << "9. Find Fire Brigade\n";
        cout << "10. Find  port Hub\n";
        cout << "11. Find Airport Hub\n";
        cout << "12. Find  post office\n";
        cout << "13. Find garden\n";
        cout << "14. Exit\n";
        cout << "Enter your choice (1-14): ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after entering a number

        switch (choice)
         {
            case 1:
                findLocation();
                break;
            case 2:
                findHotel();
                break;
            case 3:
                checkTraffic();
                break;
            case 4:
                findTouristAttractions();
                break;
            case 5:
                findHospital();
                break;
            case 6:
                findBank();
                break;
            case 7:
                findEducationFirm();
                break;
            case 8:
                findPoliceStation();
                break;
            case 9:
                findFireBrigade();
                break;
            case 10:
                findportHub();
                break;
            case 11:
                findairport();
                break;
            case 12:
                findpostoffice();
                break;
            case 13:
                findgarden();
                break;
            case 14:
                cout << "Exiting the program. Goodbye!" << endl;
                break; // Exit the program
            default:
                cout << "Invalid choice! Please choose a valid option.\n";
                break;
        }
    }

    //return 0;
}



// Function to simulate finding a location
void setNewCredentials(const std::string &username, const std::string &password)
 {
    correctUsername = username;
    correctPassword = password;
    std::cout << "Username and password updated successfully.\n";
}

// Function to reset username and password
void resetCredentials()
 {
    correctUsername = "admin";
    correctPassword = "password123";
    std::cout << "Username and password have been reset to default values.\n";
}

// Helper function to get the current timestamp
std::string getCurrentTimestamp()
 {
    time_t now = time(nullptr);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}

// Struct to represent a CO2 log entry
struct CO2LogEntry
 {
    std::string timestamp;
    double co2Level;
    std::string status;

    CO2LogEntry(const std::string& ts, double level, const std::string& st = "")
        : timestamp(ts), co2Level(level), status(st) {}

    // Convert the log entry to a string for file writing
    std::string toString() const
     {
        return timestamp + "," + std::to_string(co2Level) + "," + status;
    }
};

// CO2 Data Logger Class
class CO2DataLogger
{
private:
    std::string logFileName;
    std::vector<CO2LogEntry> logEntries;

public:
    // Constructor to initialize the file name
    CO2DataLogger(const std::string& fileName) : logFileName(fileName)
    {
        // Attempt to create the file if it does not exist
        std::ofstream outFile(logFileName, std::ios::app);
        if (!outFile)
        {
            std::cerr << "Error: Unable to create or open log file: " << logFileName << std::endl;
        }
        outFile.close();
    }

    // Add a new CO2 log entry
    void addLogEntry(double co2Level, const std::string& status)
    {
        CO2LogEntry entry = {getCurrentTimestamp(), co2Level, status};
        logEntries.push_back(entry);
        saveToFile(entry);
        std::cout << "Log entry added: " << entry.toString() << std::endl;
    }

    // Save a single log entry to the file
    void saveToFile(const CO2LogEntry& entry)
    {
        std::ofstream outFile(logFileName, std::ios::app);
        if (outFile.is_open())
        {
            outFile << entry.toString() << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open log file for writing: " << logFileName << std::endl;
        }
        outFile.close();
    }

    // Load all log entries from the file
    void loadFromFile()
    {
        std::ifstream inFile(logFileName);
        std::string line;
        logEntries.clear();

        if (inFile.is_open())
        {
            while (std::getline(inFile, line))
            {
                std::stringstream ss(line);
                std::string timestamp, co2LevelStr, status;

                if (std::getline(ss, timestamp, ',') &&
                    std::getline(ss, co2LevelStr, ',') &&
                    std::getline(ss, status))
                {
                    double co2Level = std::stod(co2LevelStr);
                    CO2LogEntry entry = {timestamp, co2Level, status};
                    logEntries.push_back(entry);
                }
            }
        }
        else
        {
            std::cerr << "Error: Unable to open log file for reading: " << logFileName << std::endl;
        }
        inFile.close();
    }

    // Display all log entries
    void displayLogEntries() const
    {
        std::cout << "CO2 Log Entries:" << std::endl;
        for (const auto& entry : logEntries)
        {
            std::cout << entry.timestamp << " | " << entry.co2Level << " ppm | " << entry.status << std::endl;
        }
    }

    // Clear all log entries (file and memory)
    void clearLog()
    {
        logEntries.clear();
        std::ofstream outFile(logFileName, std::ios::trunc);
        if (outFile.is_open())
        {
            outFile.close();
        }
        else
        {
            std::cerr << "Error: Unable to open log file for clearing." << std::endl;
        }
        std::cout << "Log cleared successfully." << std::endl;
    }

    // Provide access to the log entries
    const std::vector<CO2LogEntry>& getLogEntries() const
    {
        return logEntries;
    }

    // Export log entries to a CSV file
    void exportToCSV(const std::string& exportFileName) const
    {
        std::ofstream outFile(exportFileName);
        if (outFile.is_open())
        {
            outFile << "Timestamp,CO2 Level,Status\n";
            for (const auto& entry : logEntries)
            {
                outFile << entry.toString() << std::endl;
            }
            outFile.close();
            std::cout << "Log entries exported to " << exportFileName << " successfully." << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open export file for writing." << std::endl;
        }
    }

    // Import log entries from a CSV file
    void importFromCSV(const std::string& importFileName)
    {
        std::ifstream inFile(importFileName);
        std::string line;
        logEntries.clear();

        if (inFile.is_open())
        {
            std::getline(inFile, line); // Skip the header line
            while (std::getline(inFile, line))
            {
                std::stringstream ss(line);
                std::string timestamp, co2LevelStr, status;

                if (std::getline(ss, timestamp, ',') &&
                    std::getline(ss, co2LevelStr, ',') &&
                    std::getline(ss, status))
                {
                    double co2Level = std::stod(co2LevelStr);
                    CO2LogEntry entry = {timestamp, co2Level, status};
                    logEntries.push_back(entry);
                }
            }
            inFile.close();
            std::cout << "Log entries imported from " << importFileName << " successfully." << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open import file for reading." << std::endl;
        }
    }

    // Generate a summary report of the CO2 log entries
    void generateReport() const
    {
        std::cout << "CO2 Log Report:" << std::endl;
        std::cout << "-----------------------" << std::endl;

        double avgCO2 = std::accumulate(logEntries.begin(), logEntries.end(), 0.0,
                                        [](double total, const CO2LogEntry& entry)
                                        { return total + entry.co2Level; }) / logEntries.size();
        std::cout << "Average CO2 Level: " << avgCO2 << " ppm" << std::endl;

        auto maxIt = std::max_element(logEntries.begin(), logEntries.end(),
                                      [](const CO2LogEntry& a, const CO2LogEntry& b)
                                      { return a.co2Level < b.co2Level; });
        if (maxIt != logEntries.end())
        {
            std::cout << "Highest CO2 Level: " << maxIt->co2Level << " ppm at " << maxIt->timestamp << std::endl;
        }

        auto minIt = std::min_element(logEntries.begin(), logEntries.end(),
                                      [](const CO2LogEntry& a, const CO2LogEntry& b)
                                      { return a.co2Level < b.co2Level; });
        if (minIt != logEntries.end())
        {
            std::cout << "Lowest CO2 Level: " << minIt->co2Level << " ppm at " << minIt->timestamp << std::endl;
        }
    };
};

// CO2 Sensor Class
class CO2Sensor
 {
protected:
    std::string sensorID;
    double minPPM;
    double maxPPM;
    double lastReading;

public:
    // Constructor for initializing sensor ID and min/max CO2 levels
    CO2Sensor(const std::string& id, double minPPM = 350, double maxPPM = 5000)
        : sensorID(id), minPPM(minPPM), maxPPM(maxPPM), lastReading(0.0) {}

    // Simulate a CO2 reading
    double readCO2()
     {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(minPPM, maxPPM);
        lastReading = dis(gen);
        return lastReading;
    }

    // Get status based on the last CO2 reading
    std::string getStatus() const
     {
        if (lastReading < 1000)
            {
            return "Good air quality";
        }
        else if (lastReading < 2000)
         {
            return "Moderate air quality";
        }
        else
         {
            return "Poor air quality - Take action!";
        }
    }
};

// TempHumiditySensor Class
class TempHumiditySensor
 {
public:
    float readTemperature()
     {
        return 25.5; // Celsius (simulated value)
    }

    float readHumidity()
     {
        return 60.0; // Percent (simulated value)
    }
};

// Function to compensate CO2 reading based on temperature and humidity
float compensateCO2(float co2, float temperature, float humidity)
 {
    // Example compensation formula (simplified)
    float correctionFactor = 1 + 0.01 * (temperature - 25) + 0.02 * (humidity - 50);
    return co2 * correctionFactor;
}

// CO2 Analyzer Class for statistical analysis and forecasting
class CO2Analyzer
 {
private:
    std::vector<CO2LogEntry> logEntries;

public:
    CO2Analyzer()
    {
    }

    // Load CO2 data from log entries
    void loadFromLogEntries(const std::vector<CO2LogEntry>& entries)
     {
        logEntries = entries;
    }

    // Calculate the average CO2 level
    double calculateAverageCO2() const
     {
        if (logEntries.empty())
            {
            std::cerr << "No data available for analysis." << std::endl;
            return 0.0;
        }
        double sum = std::accumulate(logEntries.begin(), logEntries.end(), 0.0,
                                     [
                                     ]
                                     (double total, const CO2LogEntry& entry)
                                     { return total + entry.co2Level; }
                                     );
        return sum / logEntries.size();
    }

    // Find the maximum CO2 level
    CO2LogEntry findMaxCO2() const
     {
        if (logEntries.empty())
            {
            std::cerr << "No data available for analysis." << std::endl;
            return {"N/A", 0.0, ""};
        }
        auto maxIt = std::max_element(logEntries.begin(), logEntries.end(),
                                      [
                                      ]
                                      (const CO2LogEntry& a, const CO2LogEntry& b)
                                       { return a.co2Level < b.co2Level; });
        return *maxIt;
    }

    // Find the minimum CO2 level
    CO2LogEntry findMinCO2() const
     {
        if (logEntries.empty())
            {
            std::cerr << "No data available for analysis." << std::endl;
            return {"N/A", 0.0, ""};
        }
        auto minIt = std::min_element(logEntries.begin(), logEntries.end(),
                                      [
                                      ]
                                      (const CO2LogEntry& a, const CO2LogEntry& b)
                                      { return a.co2Level < b.co2Level; }
                                      );
        return *minIt;
    }

    // Calculate the standard deviation of CO2 levels
    double calculateStandardDeviation() const
     {
        if (logEntries.empty())
            {
            std::cerr << "No data available for analysis." << std::endl;
            return 0.0;
        }

        double average = calculateAverageCO2();

        // Calculate the variance
        double variance = std::accumulate(logEntries.begin(), logEntries.end(), 0.0,
                                          [average](double total, const CO2LogEntry& entry)
                                           {
                                              return total + std::pow(entry.co2Level - average, 2);
                                          }
                                          );

        // Calculate the standard deviation
        return std::sqrt(variance / logEntries.size()
                         );
    }

    // Simple linear regression to predict future CO2 levels
    double linearRegressionPredict(int futureMinutes) const
     {
        if (logEntries.size() < 2)
            {
            throw std::invalid_argument("Not enough data for linear regression analysis.");
        }

        // Prepare the data for linear regression: x = time, y = CO2 level
        std::vector<double> xData;
        std::vector<double> yData;

        // Create x (time) and y (CO2 level) vectors
        for (size_t i = 0; i < logEntries.size(); ++i)
            {
            time_t timestamp = std::stoll(logEntries[i].timestamp);
            xData.push_back(std::difftime(timestamp, std::stoll(logEntries[0].timestamp)) / 60); // Convert time to minutes
            yData.push_back(logEntries[i].co2Level);
        }

        // Calculate the averages of x and y
        double meanX = std::accumulate(xData.begin(), xData.end(), 0.0) / xData.size();
        double meanY = std::accumulate(yData.begin(), yData.end(), 0.0) / yData.size();

        // Calculate the slope (m) of the regression line
        double numerator = 0.0, denominator = 0.0;
        for (size_t i = 0; i < xData.size(); ++i)
            {
            numerator += (xData[i] - meanX) * (yData[i] - meanY);
            denominator += (xData[i] - meanX) * (xData[i] - meanX);
        }
        double slope = numerator / denominator;

        // Calculate the y-intercept (b) of the regression line
        double intercept = meanY - (slope * meanX);

        // Predict the future CO2 level for the given number of minutes in the future
        double futureX = xData.back() + futureMinutes;
        double predictedCO2 = slope * futureX + intercept;

        return predictedCO2;
    }

    // Function to get the trend of CO2 levels based on regression prediction
    std::string predictAndDetermineTrend(int futureMinutes) const
     {
        try
        {
            double predictedCO2 = linearRegressionPredict(futureMinutes);
            std::cout << "Predicted CO2 level after " << futureMinutes << " minutes: " << predictedCO2 << " ppm" << std::endl;

            if (predictedCO2 > calculateAverageCO2())
                {
                return "Predicted CO2 levels are increasing.";
            }
            else if (predictedCO2 < calculateAverageCO2())
            {
                return "Predicted CO2 levels are decreasing.";
            }
            else
                {
                return "Predicted CO2 levels remain stable.";
            }
        }
        catch (const std::exception& e)
         {
            std::cerr << "Error: " << e.what() << std::endl;
            return "Unable to predict trend.";
        }
    }

    // Display the analysis results
    void displayAnalysis() const
     {
        if (logEntries.empty())
            {
            std::cout << "No data available for analysis." << std::endl;
            return;
        }

        std::cout << "CO2 Emission Analysis:" << std::endl;
        std::cout << "-----------------------" << std::endl;

        // Average CO2 Level
        double avgCO2 = calculateAverageCO2();
        std::cout << "Average CO2 Level: " << avgCO2 << " ppm" << std::endl;

        // Max CO2 Level
        CO2LogEntry maxCO2 = findMaxCO2();
        std::cout << "Highest CO2 Level: " << maxCO2.co2Level << " ppm at " << maxCO2.timestamp << std::endl;

        // Min CO2 Level
        CO2LogEntry minCO2 = findMinCO2();
        std::cout << "Lowest CO2 Level: " << minCO2.co2Level << " ppm at " << minCO2.timestamp << std::endl;

        // Standard Deviation
        double stdDev = calculateStandardDeviation();
        std::cout << "Standard Deviation: " << stdDev << " ppm" << std::endl;

        // Linear Regression Prediction
        std::string trend = predictAndDetermineTrend(30);  // Predicting CO2 levels after 30 minutes
        std::cout << "Trend: " << trend << std::endl;
    }

    // Helper function to convert a timestamp to human-readable format
    static std::string formatTimestamp(time_t timestamp)
     {
        struct tm* timeinfo = localtime(&timestamp);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return std::string(buffer);
    }

    // Add new log entry to the list (can be used for real-time data)
    void addLogEntry(const std::string& timestamp, double co2Level, const std::string& status)
     {
        logEntries.push_back(CO2LogEntry(timestamp, co2Level, status));
    }
};

// Structure to store CO2 data with a timestamp for visualization
struct CO2Data
 {
    time_t timestamp;
    double ppm;  // CO2 level in parts per million (ppm)

    CO2Data(time_t t, double p) : timestamp(t), ppm(p) {}
};

// Function to simulate getting CO2 data readings for the last 10 minutes
std::vector<CO2Data> getCO2Data()
 {
    std::vector<CO2Data> data;
    time_t current_time = time(nullptr);

    // Simulate data for the past 10 minutes
    for (int i = 0; i < 10; ++i)
        {
        double ppm = 400 + (rand() % 100); // Simulated CO2 level between 400-500 ppm
        data.push_back(CO2Data(current_time - (i * 60), ppm)); // Decrementing time for past readings
    }

    return data;
}

// Function to calculate the average CO2 level
double calculateAverage(const std::vector<CO2Data>& data)
 {
    double sum = 0;
    for (const auto& entry : data)
        {
        sum += entry.ppm;
    }
    return sum / data.size();
}

// Function to find the maximum CO2 level
double findMaxCO2(const std::vector<CO2Data>& data)
 {
    double max_ppm = data[0].ppm;
    for (const auto& entry : data)
     {
        if (entry.ppm > max_ppm)
            {
            max_ppm = entry.ppm;
        }
    }
    return max_ppm;
}

// Function to find the minimum CO2 level
double findMinCO2(const std::vector<CO2Data>& data)
 {
    double min_ppm = data[0].ppm;
    for (const auto& entry : data)
     {
        if (entry.ppm < min_ppm)
            {
            min_ppm = entry.ppm;
        }
    }
    return min_ppm;
}

// Function to format and print the time (HH:MM:SS format)
std::string formatTime(time_t timestamp)
 {
    struct tm* timeinfo = localtime(&timestamp);
    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    return std::string(buffer);
}

// Function to display the data as a simple text-based graph
void visualizeData(const std::vector<CO2Data>& data)
 {
    const int MAX_HEIGHT = 10; // The maximum height for visualization
    double max_ppm = findMaxCO2(data);

    for (const auto& entry : data)
        {
        int height = static_cast<int>((entry.ppm / max_ppm) * MAX_HEIGHT); // Scale data for visualization
        std::cout << formatTime(entry.timestamp) << " | ";
        for (int i = 0; i < height; ++i)
            {
            std::cout << "#";
        }
        std::cout << " (" << entry.ppm << " ppm)" << std::endl;
    }
}

// Function to generate test data for CO2 analysis
std::vector<CO2LogEntry> generateTestData()
 {
    std::vector<CO2LogEntry> data;

    // Simulate data for the last 10 minutes
    for (int i = 0; i < 10; ++i)
        {
        double co2Level = 400 + (rand() % 100);  // Simulate CO2 level between 400-500 ppm
        std::string timestamp = CO2Analyzer::formatTimestamp(time(nullptr) - (i * 60));  // 1 minute interval
        std::string status = co2Level < 1000 ? "Good air quality" :
                            (co2Level < 2000 ? "Moderate air quality" : "Poor air quality - Take action!");

        data.push_back(CO2LogEntry(timestamp, co2Level, status));
    }

    return data;
}

// Define the CO2 optimization parameters (these can be system-specific)
struct CO2ControlParameters
 {
    double ventilationRate;  // Ventilation rate in cubic meters per minute
    double filterEfficiency; // Efficiency of the CO2 filter (percentage)
    double airExchangeRate;  // Air exchange rate per minute

    // Constructor to initialize parameters
    CO2ControlParameters(double ventRate, double filterEff, double airExchange)
        : ventilationRate(ventRate), filterEfficiency(filterEff), airExchangeRate(airExchange)
         {

        }

    // Function to calculate the CO2 level based on current parameters (simplified model)
    double calculateCO2Level() const
     {
        // A simplified model: CO2 level is inversely proportional to ventilation and filter efficiency
        return 1000.0 - (ventilationRate * 0.5 + filterEfficiency * 0.3 + airExchangeRate * 0.2);
    }

    // Helper function to display the parameters
    void display() const
     {
        std::cout << "Ventilation Rate: " << ventilationRate << " m^3/min\n";
        std::cout << "Filter Efficiency: " << filterEfficiency << " %\n";
        std::cout << "Air Exchange Rate: " << airExchangeRate << " m^3/min\n";
    }

    // Function to return the fitness score: closer to the target CO2 level, better the fitness
    double fitness(double targetCO2) const
     {
        double currentCO2 = calculateCO2Level();
        return exp(-fabs(currentCO2 - targetCO2)); // Exponentially decreasing fitness based on deviation from target
    }
};

// Function to generate a random control parameter within a given range
CO2ControlParameters generateRandomParams()
 {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> ventDist(10.0, 50.0);         // Random ventilation rate between 10 and 50%
    std::uniform_real_distribution<> filterDist(50.0, 100.0);      // Random filter efficiency between 50% and 100%
    std::uniform_real_distribution<> exchangeDist(5.0, 30.0);      // Random air exchange rate between 5 and 30

    return CO2ControlParameters(ventDist(gen), filterDist(gen), exchangeDist(gen));
}

// Crossover function for two parent solutions
CO2ControlParameters crossover(const CO2ControlParameters& parent1, const CO2ControlParameters& parent2)
 {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> crossoverPoint(0.0, 1.0);

    // Crossover the parameters
    double ventRate = (crossoverPoint(gen) < 0.5) ? parent1.ventilationRate : parent2.ventilationRate;
    double filterEff = (crossoverPoint(gen) < 0.5) ? parent1.filterEfficiency : parent2.filterEfficiency;
    double airExchange = (crossoverPoint(gen) < 0.5) ? parent1.airExchangeRate : parent2.airExchangeRate;

    return CO2ControlParameters(ventRate, filterEff, airExchange);
}

// Function to mutate CO2 control parameters
void mutate(CO2ControlParameters& params)
 {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> mutationRate(0.0, 1.0);

    // Introduce small mutations
    if (mutationRate(gen) < 0.1)
        { // 10% chance to mutate
        params.ventilationRate += (rand() % 5 - 2);   // Small mutation to the ventilation rate
        params.ventilationRate = std::max(10.0, std::min(50.0, params.ventilationRate)); // Ensure within bounds
    }
    if (mutationRate(gen) < 0.1)
        {
        params.filterEfficiency += (rand() % 5 - 2);  // Small mutation to the filter efficiency
        params.filterEfficiency = std::max(50.0, std::min(100.0, params.filterEfficiency)); // Ensure within bounds
    }
    if (mutationRate(gen) < 0.1)
        {
        params.airExchangeRate += (rand() % 5 - 2);   // Small mutation to the air exchange rate
        params.airExchangeRate = std::max(5.0, std::min(30.0, params.airExchangeRate)); // Ensure within bounds
    }
}

// Selection function to choose the best solutions
std::vector<CO2ControlParameters> selectBestSolutions(const std::vector<CO2ControlParameters>& population, const std::vector<double>& fitnessScores, size_t selectionSize)
 {
    std::vector<std::pair<double, size_t>> sortedFitness;
    for (size_t i = 0; i < fitnessScores.size(); ++i)
        {
        sortedFitness.push_back({fitnessScores[i], i});
    }
    std::sort(sortedFitness.rbegin(), sortedFitness.rend());  // Sort by fitness in descending order

    std::vector<CO2ControlParameters> selected;
    for (size_t i = 0; i < selectionSize; ++i)
        {
        selected.push_back(population[sortedFitness[i].second]);  // Select the best solutions
    }
    return selected;
}

// Function to run the genetic algorithm
std::vector<CO2ControlParameters> runGeneticAlgorithm(size_t populationSize, size_t generations, double targetCO2, double mutationRate)
 {
    // Initialize the population with random solutions
    std::vector<CO2ControlParameters> population;
    for (size_t i = 0; i < populationSize; ++i)
        {
        population.push_back(generateRandomParams());
    }

    // Evolve the population over generations
    for (size_t gen = 0; gen < generations; ++gen)
        {
        // Calculate fitness for each individual
        std::vector<double> fitnessScores;
        for (const auto& params : population)
            {
            fitnessScores.push_back(params.fitness(targetCO2));
        }

        // Select the best solutions
        std::vector<CO2ControlParameters> selected = selectBestSolutions(population, fitnessScores, populationSize / 2);

        // Create a new population using crossover and mutation
        std::vector<CO2ControlParameters> newPopulation;
        while (newPopulation.size() < populationSize)
            {
            // Randomly pick two parents from the selected population
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, selected.size() - 1);
            CO2ControlParameters parent1 = selected[dist(gen)];
            CO2ControlParameters parent2 = selected[dist(gen)];

            // Crossover the parents
            CO2ControlParameters child = crossover(parent1, parent2);

            // Mutate the child
            mutate(child);

            // Add the child to the new population
            newPopulation.push_back(child);
        }

        // Replace the old population with the new one
        population = newPopulation;

        // Print out the best solution of the current generation
        double bestFitness = *std::max_element(fitnessScores.begin(), fitnessScores.end());
        std::cout << "Generation " << gen + 1 << " - Best Fitness: " << bestFitness << std::endl;
    }

    // Return the best solution after all generations
    std::vector<double> finalFitnessScores;
    for (const auto& params : population)
        {
        finalFitnessScores.push_back(params.fitness(targetCO2));
    }

    size_t bestIndex = std::max_element(finalFitnessScores.begin(), finalFitnessScores.end()) - finalFitnessScores.begin();
    return {population[bestIndex]};
}

// Simulate sensor readings for different gases
class GasSensor
 {
public:
    virtual float readConcentration() = 0;  // Virtual function to be overridden by specific gas sensors
    virtual std::string getGasName() = 0;
};

class CarbonMonoxideSensor : public GasSensor
 {
public:
    float readConcentration() override
     {
        // In reality, this would interface with the sensor to get a reading
        return 45.0; // ppm (simulated value for CO)
    }

    std::string getGasName() override
     {
        return "Carbon Monoxide (CO)";
    }
};

class MethaneSensor : public GasSensor
 {
public:
    float readConcentration() override
     {
        return 0.02; // Percent (simulated value for CH4)
    }

    std::string getGasName() override
     {
        return "Methane (CH4)";
    }
};

class NitrousOxideSensor : public GasSensor
 {
public:
    float readConcentration() override
     {
        return 0.003; // Percent (simulated value for N2O)
    }

    std::string getGasName() override
     {
        return "Nitrous Oxide (N2O)";
    }
};

// Monitor all gases and print readings
class MultiGasMonitor
 {
public:
    void addSensor(GasSensor* sensor)
     {
        sensors.push_back(sensor);
    }

    void displayReadings()
     {
        for (auto& sensor : sensors)
            {
            std::cout << sensor->getGasName() << ": "
                      << sensor->readConcentration() << std::endl;
        }
    }

private:
    std::vector<GasSensor*> sensors;
};

// Additional code for historical data analysis
struct CO2HistoricalData
 {
    double year;
    double emission;
};

// Function to load historical data from a file
std::vector<CO2HistoricalData> loadHistoricalData(const std::string& filename)
 {
    std::vector<CO2HistoricalData> data;
    std::ifstream file(filename);

    if (!file.is_open())
        {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    double year, emission;
    while (file >> year >> emission)
        {
        data.push_back({year, emission});
    }

    file.close();
    return data;
}

// Function to calculate linear regression coefficients
std::pair<double, double> calculateLinearRegression(const std::vector<CO2HistoricalData>& data)
 {
    double n = data.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (const auto& entry : data)
        {
        sumX += entry.year;
        sumY += entry.emission;
        sumXY += entry.year * entry.emission;
        sumX2 += entry.year * entry.year;
    }

    double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double intercept = (sumY - slope * sumX) / n;

    return {slope, intercept};
}

// Function to predict future CO2 levels
std::vector<double> predictFutureCO2(const std::vector<CO2HistoricalData>& data, const std::pair<double, double>& coefficients, int yearsAhead)
 {
    double slope = coefficients.first;
    double intercept = coefficients.second;

    double lastYear = data.back().year;
    std::vector<double> predictions;

    for (int i = 1; i <= yearsAhead; ++i)
        {
        double futureYear = lastYear + i;
        double predictedEmission = slope * futureYear + intercept;
        predictions.push_back(predictedEmission);
    }

    return predictions;
}

// Function to provide actionable insights
void provideActionableInsights(const std::vector<CO2HistoricalData>& data, double reductionTarget)
 {
    double currentEmission = data.back().emission;

    std::cout << "\n=== Actionable Insights ===\n";
    std::cout << "Current CO2 emission: " << currentEmission << " ppm\n";
    std::cout << "Target reduction: " << reductionTarget << " ppm\n";

    std::cout << "Suggested actions to reduce emissions:\n";
    std::cout << "1. Increase renewable energy usage by 20%.\n";
    std::cout << "2. Implement stricter energy efficiency standards.\n";
    std::cout << "3. Reduce transportation emissions by promoting electric vehicles.\n";
    std::cout << "4. Implement carbon capture technologies.\n";
    std::cout << "5. Encourage reforestation and afforestation programs.\n";
}

// Function to save predictions to a file
void savePredictionsToFile(const std::vector<double>& predictions, const std::string& filename)
 {
    std::ofstream file(filename);

    if (!file.is_open())
        {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < predictions.size(); ++i)
        {
        file << "Year " << i + 1 << ": " << std::fixed << std::setprecision(2) << predictions[i] << " ppm\n";
    }

    file.close();
    std::cout << "Predictions saved to " << filename << "\n";
}

// Simulate Wireless Communication Modules
class WiFiModule
 {
public:
    void connect(const std::string& ssid, const std::string& password)
     {
        std::cout << "Connecting to Wi-Fi network '" << ssid << "'...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Wi-Fi connected successfully.\n";
    }

    void sendData(const std::string& data)
     {
        std::cout << "Wi-Fi: Sending data: " << data << "\n";
    }
};

class BluetoothModule
 {
public:
    void pairDevice(const std::string& deviceName)
     {
        std::cout << "Pairing with Bluetooth device '" << deviceName << "'...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Bluetooth device paired successfully.\n";
    }

    void sendData(const std::string& data)
     {
        std::cout << "Bluetooth: Sending data: " << data << "\n";
    }
};

class ZigbeeModule
 {
public:
    void joinNetwork(const std::string& networkId)
     {
        std::cout << "Joining Zigbee network '" << networkId << "'...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Zigbee network joined successfully.\n";
    }

    void sendData(const std::string& data)
     {
        std::cout << "Zigbee: Sending data: " << data << "\n";
    }
};

// CO2 Emission Sensor Class
class CO2EmissionSensor
 {
private:
    double currentReading;
    WiFiModule wifi;
    BluetoothModule bluetooth;
    ZigbeeModule zigbee;

public:
    CO2EmissionSensor() : currentReading(0.0) {}

    void readSensor()
     {
        // Simulate a CO2 sensor reading
        currentReading = 400.0 + (rand() % 100) / 10.0; // Random value between 400-410 ppm
        std::cout << "CO2 Sensor Reading: " << currentReading << " ppm\n";
    }

    void sendData(const std::string& method, const std::string& destination)
     {
        std::string data = "CO2 Level: " + std::to_string(currentReading) + " ppm";

        if (method == "WiFi")
            {
            wifi.connect("MyWiFiNetwork", "password123");
            wifi.sendData(data);
        }
        else if (method == "Bluetooth")
        {
            bluetooth.pairDevice(destination);
            bluetooth.sendData(data);
        }
         else if (method == "Zigbee")
        {
            zigbee.joinNetwork(destination);
            zigbee.sendData(data);
        }
         else
         {
            std::cerr << "Invalid communication method.\n";
        }
    }
};

// Integration with Smart Systems
void integrateWithSmartHome() {
    std::cout << "Integrating with Smart Home system...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "CO2 sensor data is now available in the Smart Home dashboard.\n";
}

void integrateWithIndustrialSystem()
 {
    std::cout << "Integrating with Industrial Control system...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "CO2 sensor data is now integrated with the Industrial Control system.\n";
}

// New EnhancedCO2Sensor class to incorporate compliance checking and report generation
class EnhancedCO2Sensor : public CO2Sensor
 {
private:
    std::vector<CO2Data> emissionData;

    std::string getCurrentTimeString()
     {
        std::time_t now = std::time(nullptr);
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(buffer);
    }

public:
    EnhancedCO2Sensor(const std::string& id, double minPPM = 350, double maxPPM = 5000)
        : CO2Sensor(id, minPPM, maxPPM) {}

    void recordEmission(double emission)
     {
        std::time_t now = std::time(nullptr);
        emissionData.push_back({now, emission});
        std::cout << "Recorded CO2 emission: " << emission << " ppm at " << getCurrentTimeString() << "\n";
    }

    void generateReport(const std::string& filename)
     {
        std::ofstream reportFile(filename);

        if (!reportFile.is_open())
            {
            std::cerr << "Error: Unable to open file for writing: " << filename << "\n";
            return;
        }

        reportFile << "Environmental Compliance Report\n";
        reportFile << "===================================\n";
        reportFile << "Generated on: " << getCurrentTimeString() << "\n\n";
        reportFile << "Timestamp               | CO2 Emission (ppm)\n";
        reportFile << "-----------------------------------\n";

        for (const auto& entry : emissionData)
            {
            char buffer[100];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&entry.timestamp));
            reportFile << std::setw(22) << buffer << " | " << std::setw(17) << entry.ppm << "\n";
        }

        reportFile << "\nSummary:\n";

        double totalEmissions = 0.0;
        for (const auto& entry : emissionData)
            {
            totalEmissions += entry.ppm;
        }

        double averageEmission = emissionData.empty() ? 0 : totalEmissions / emissionData.size();
        reportFile << "Total Records: " << emissionData.size() << "\n";
        reportFile << "Average CO2 Emission: " << std::fixed << std::setprecision(2) << averageEmission << " ppm\n";

        reportFile.close();
        std::cout << "Report generated successfully: " << filename << "\n";
    }

    void complianceCheck(double threshold)
    {
        std::cout << "\nCompliance Check:\n";
        std::cout << "Threshold: " << threshold << " ppm\n";

        for (const auto& entry : emissionData)
        {
            if (entry.ppm > threshold)
                {
                char buffer[100];
                std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&entry.timestamp));
                std::cout << "Non-compliance detected at " << buffer << " with emission: " << entry.ppm << " ppm\n";
            }
        }
    }
};

// Constants for maintenance thresholds
const int CLEANING_THRESHOLD_HOURS = 500; // Example: Sensor should be cleaned every 500 hours
const int REPLACEMENT_THRESHOLD_HOURS = 5000; // Example: Sensor should be replaced every 5000 hours
const int CALIBRATION_THRESHOLD_HOURS = 1000; // Example: Sensor should be calibrated every 1000 hours

// Struct to hold sensor data for maintenance
struct Sensor
{
    std::string id;
    std::chrono::time_point<std::chrono::system_clock> lastCleaning;
    std::chrono::time_point<std::chrono::system_clock> lastReplacement;
    std::chrono::time_point<std::chrono::system_clock> lastCalibration;
};

// Function to check maintenance needs
void checkMaintenance(Sensor& sensor)
{
    auto now = std::chrono::system_clock::now();

    // Calculate hours since last maintenance actions
    auto hoursSinceCleaning = std::chrono::duration_cast<std::chrono::hours>(now - sensor.lastCleaning).count();
    auto hoursSinceReplacement = std::chrono::duration_cast<std::chrono::hours>(now - sensor.lastReplacement).count();
    auto hoursSinceCalibration = std::chrono::duration_cast<std::chrono::hours>(now - sensor.lastCalibration).count();

    // Check for cleaning
    if (hoursSinceCleaning >= CLEANING_THRESHOLD_HOURS)
        {
        std::cout << "Sensor " << sensor.id << " requires cleaning.\n";
    }

    // Check for replacement
    if (hoursSinceReplacement >= REPLACEMENT_THRESHOLD_HOURS)
        {
        std::cout << "Sensor " << sensor.id << " requires replacement.\n";
    }

    // Check for calibration
    if (hoursSinceCalibration >= CALIBRATION_THRESHOLD_HOURS)
        {
        std::cout << "Sensor " << sensor.id << " requires calibration.\n";
    }
    else
        {
        std::cout << "Sensor " << sensor.id << " does not require calibration.\n";
    }
}

// Example usage for maintenance
void maintenanceExample()
{
    // Initialize sensor with last maintenance times
    Sensor sensor =
    {
        "CO2-12345",
        std::chrono::system_clock::now() - std::chrono::hours(600), // Last cleaning was 600 hours ago
        std::chrono::system_clock::now() - std::chrono::hours(5100), // Last replacement was 5100 hours ago
        std::chrono::system_clock::now() - std::chrono::hours(1200) // Last calibration was 1200 hours ago
    };

    // Check the maintenance status of the sensor
    checkMaintenance(sensor);
}

// CO2 Sensor Class with fail operation simulation
class CO2FailSensor : public CO2Sensor
 {
private:
    int threshold;
    std::string logFile;
    int batteryLevel; // Battery level percentage
    int leakThreshold;
    std::vector<int> recentReadings;
    const int maxRecentReadings = 5; // Number of readings to consider for spike detection

    int readCO2Level()
     {
        // Simulate a CO2 sensor reading. Replace this with actual sensor code.
        return rand() % 1701 + 300; // Random ppm value between 300 and 2000.
    }

    void logReading(int co2Level)
    {
        std::ofstream file(logFile, std::ios::app);
        if (file.is_open())
            {
            std::time_t now = std::time(nullptr);
            file << std::ctime(&now) << ", " << co2Level << " ppm\n";
            file.close();
        }
        else
            {
            std::cerr << "Unable to open log file." << std::endl;
        }
    }

    void checkThreshold(int co2Level)
    {
        if (co2Level > threshold)
            {
            triggerAlarm(co2Level);
        }
    }

    void triggerAlarm(int co2Level)
     {
        std::cout << "ALERT! CO2 level is " << co2Level << " ppm, exceeding the threshold of "
                  << threshold << " ppm!" << std::endl;
        // Additional actions, like sending notifications, can be added here.
    }

    void simulateBackupPower()
    {
        std::cout << "Switching to backup power..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate a delay for switching power.
        std::cout << "Backup power is active." << std::endl;
    }

    void checkBatteryLevel()
    {
        // Simulate battery level decrease over time.
        batteryLevel -= rand() % 5; // Random decrease by 0-4%.
        if (batteryLevel < 0) batteryLevel = 0;

        std::cout << "Battery Level: " << batteryLevel << "%" << std::endl;

        if (batteryLevel <= 20)
            {
            notifyLowBattery();
        }

        if (batteryLevel == 0)
            {
            std::cerr << "Battery depleted. Shutting down sensor to preserve data." << std::endl;
            exit(0);
        }
    }

    void notifyLowBattery()
     {
        std::cout << "WARNING: Low battery level. Please recharge or replace the battery." << std::endl;
        // Calculate approximate remaining operating time.
        int remainingTime = batteryLevel * 2; // Assume 2 minutes per 1% battery.
        std::cout << "Estimated remaining operating time: " << remainingTime << " minutes." << std::endl;
    }

    void checkForLeak(int co2Level)
    {
        recentReadings.push_back(co2Level);
        if (recentReadings.size() > maxRecentReadings)
            {
            recentReadings.erase(recentReadings.begin());
        }

        // Calculate the rate of change between the most recent readings
        if (recentReadings.size() == maxRecentReadings)
            {
            int change = recentReadings.back() - recentReadings.front();
            if (change > leakThreshold)
                {
                triggerLeakAlert(change);
            }
        }
    }

    void triggerLeakAlert(int change)
    {
        std::cout << "WARNING: Sudden spike detected! CO2 levels increased by " << change
                  << " ppm over the last few readings. Possible gas leak or abnormal emission."
                  << std::endl;
    }

public:
    CO2FailSensor(const std::string& id, int thresholdValue = 1000, int leakThresholdValue = 300, const std::string& logFileName = "co2_fail_log.txt")
        : CO2Sensor(id), threshold(thresholdValue), leakThreshold(leakThresholdValue), logFile(logFileName), batteryLevel(100) {}

    void run()
    {
        std::cout << "CO2 Sensor started. Monitoring CO2 levels..." << std::endl;
        while (true)
            {
            try
            {
                int co2Level = readCO2Level();
                std::cout << "CO2 Level: " << co2Level << " ppm" << std::endl;
                logReading(co2Level);
                checkThreshold(co2Level);
                checkForLeak(co2Level);
                checkBatteryLevel();
                std::this_thread::sleep_for(std::chrono::seconds(2)); // Delay between readings.
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
                simulateBackupPower();
            }
            catch (...)
            {
                std::cerr << "Unknown error occurred." << std::endl;
                simulateBackupPower();
            }
        }
    }
};

// CO2 Sensor Class with critical alert and evacuation routes
class CO2SensorWithEvacuation : public CO2Sensor
{
private:
    int criticalThreshold;
    std::string logFile;
    std::map<std::string, std::string> evacuationRoutes; // Maps areas to evacuation routes

    int readCO2Level()
     {
        // Simulate a CO2 sensor reading. Replace this with actual sensor code.
        return rand() % 1701 + 300; // Random ppm value between 300 and 2000.
    }

    void logReading(int co2Level)
     {
        std::ofstream file(logFile, std::ios::app);
        if (file.is_open())
            {
            std::time_t now = std::time(nullptr);
            file << std::ctime(&now) << ", " << co2Level << " ppm\n";
            file.close();
        }
         else
            {
            std::cerr << "Unable to open log file." << std::endl;
        }
    }

    void checkCriticalLevel(int co2Level)
     {
        if (co2Level >= criticalThreshold)
            {
            triggerCriticalAlert(co2Level);
            suggestEvacuationRoute();
        }
    }

    void triggerCriticalAlert(int co2Level)
    {
        std::cout << "CRITICAL ALERT: CO2 level is " << co2Level << " ppm, exceeding the critical threshold of "
                  << criticalThreshold << " ppm! Immediate action required!" << std::endl;
    }

    void suggestEvacuationRoute()
    {
        std::cout << "Evacuation Guidance: Please proceed to the nearest safe zone." << std::endl;

        for (const auto& route : evacuationRoutes)
            {
            std::cout << "Area: " << route.first << " -> Evacuation Route: " << route.second << std::endl;
        }
    }

public:
    CO2SensorWithEvacuation(const std::string& id, int criticalThresholdValue = 1200,
                            const std::string& logFileName = "co2_log.txt")
        : CO2Sensor(id), criticalThreshold(criticalThresholdValue), logFile(logFileName)
        {
        // Define evacuation routes
        evacuationRoutes["Room A"] = "Exit through Door 1 and proceed to Assembly Point 1.";
        evacuationRoutes["Room B"] = "Exit through Door 2 and proceed to Assembly Point 2.";
        evacuationRoutes["Main Hall"] = "Exit through Main Gate and proceed to Assembly Point 3.";
    }

    void run()
    {
        std::cout << "CO2 Sensor started. Monitoring CO2 levels..." << std::endl;
        while (true)
            {
            int co2Level = readCO2Level();
            std::cout << "CO2 Level: " << co2Level << " ppm" << std::endl;
            logReading(co2Level);
            checkCriticalLevel(co2Level);
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Delay between readings.
        }
    }
};

// Simulated CO2 sensor data
struct SimulatedCO2Sensor
{
    bool isConnected; // Simulate sensor connectivity
    int lastCO2Level; // Last CO2 level reading
};

// Function to simulate reading CO2 levels from the sensor
int readSimulatedCO2Level(SimulatedCO2Sensor &sensor)
 {
    if (!sensor.isConnected)
        {
        throw std::runtime_error("Sensor disconnected!");
    }
    // Simulate CO2 readings (400–1000 ppm)
    return 400 + rand() % 600;
}

// Function to perform self-diagnostics on the system
bool performDiagnostics(SimulatedCO2Sensor &sensor)
 {
    std::cout << "[Diagnostics] Running self-diagnostics...\n";

    // Check sensor connectivity
    if (!sensor.isConnected)
        {
        std::cout << "[Diagnostics] Error: Sensor is not connected.\n";
        return false;
    }

    // Check last CO2 reading for validity
    if (sensor.lastCO2Level < 0 || sensor.lastCO2Level > 5000)
        {
        std::cout << "[Diagnostics] Error: Invalid CO2 level detected.\n";
        return false;
    }

    // Simulate other checks (e.g., memory, CPU usage)
    std::cout << "[Diagnostics] System health check passed.\n";
    return true;
}

// Function to simulate alerting the user
void alertUser(const std::string &message)
 {
    std::cout << "[ALERT] " << message << std::endl;
}

void userInterface()
{
    std::string username, password;

    // Prompt user for login credentials
    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    // Check if credentials are correct
    if (authenticateUser(username, password))
        {
        std::cout << "Login successful! Access granted to sensitive data.\n";

        // Sensitive data or settings can be accessed here
        CO2DataLogger logger("co2_log.csv");
        TempHumiditySensor tempHumiditySensor;
        CO2Analyzer analyzer;
        MultiGasMonitor monitor;
        EnhancedCO2Sensor complianceSensor("Sensor_1");
        SimulatedCO2Sensor simulatedSensor = {true, 0}; // Start with a connected sensor

        // Simulate CO2 data logging
        for (int i = 0; i < 5; ++i)
            {
                // Reduced log entries to 5
            double co2Reading = complianceSensor.readCO2();
            std::string status = complianceSensor.getStatus();
            float temperature = tempHumiditySensor.readTemperature();
            float humidity = tempHumiditySensor.readHumidity();
            float correctedCO2 = compensateCO2(co2Reading, temperature, humidity);

            logger.addLogEntry(co2Reading, status);
            complianceSensor.recordEmission(co2Reading);
            std::cout << "Temperature: " << temperature << " °C, Humidity: " << humidity << " %, Corrected CO2: " << correctedCO2 << " ppm" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate time passing
        }

        // Load data from the log file and display it
        logger.loadFromFile();
        logger.displayLogEntries();

        // Perform CO2 analysis
        analyzer.loadFromLogEntries(logger.getLogEntries());
        analyzer.displayAnalysis();

        // Visualize the data
        std::vector<CO2Data> data = getCO2Data();
        visualizeData(data);

        // Generate test data for CO2 analysis
        std::vector<CO2LogEntry> testData = generateTestData();

        // Load and analyze test data
        CO2Analyzer testAnalyzer;
        testAnalyzer.loadFromLogEntries(testData);
        testAnalyzer.displayAnalysis();

        // Set parameters for the genetic algorithm
        size_t populationSize = 100;
        size_t generations = 10; // Reduced number of generations
        double targetCO2 = 450.0; // Target CO2 level (e.g., 450 ppm)
        double mutationRate = 0.1; // Mutation rate (10%)

        // Run the genetic algorithm to optimize CO2 levels
        std::vector<CO2ControlParameters> bestSolution = runGeneticAlgorithm(populationSize, generations, targetCO2, mutationRate);

        // Output the best solution
        std::cout << "\nBest Solution (Optimal CO2 Control Parameters):\n";
        bestSolution[0].display();

        // Create a multi-gas monitor
        monitor.addSensor(new CarbonMonoxideSensor());
        monitor.addSensor(new MethaneSensor());
        monitor.addSensor(new NitrousOxideSensor());

        // Display the sensor readings
        monitor.displayReadings();

        // Additional code for historical data analysis
        std::string filename = "historical_data.txt";
        std::vector<CO2HistoricalData> historicalData = loadHistoricalData(filename);

        if (historicalData.empty())
            {
            std::cerr << "No historical data loaded. Exiting.\n";
            return;
        }

        auto coefficients = calculateLinearRegression(historicalData);

        std::cout << "Linear Regression Model:\n";
        std::cout << "Slope: " << coefficients.first << "\n";
        std::cout << "Intercept: " << coefficients.second << "\n\n";

        int yearsAhead = 10;
        std::vector<double> predictions = predictFutureCO2(historicalData, coefficients, yearsAhead);

        std::cout << "Predicted CO2 Levels for the next " << yearsAhead << " years:\n";
        for (size_t i = 0; i < predictions.size(); ++i)
            {
            std::cout << "Year " << historicalData.back().year + i + 1 << ": " << std::fixed << std::setprecision(2) << predictions[i] << " ppm\n";
        }

        double reductionTarget = 50.0; // Example target
        provideActionableInsights(historicalData, reductionTarget);

        std::string outputFilename = "predictions.txt";
        savePredictionsToFile(predictions, outputFilename);

        // Additional code for wireless communication
        CO2EmissionSensor emissionSensor;

        while (true)
            {
            emissionSensor.readSensor();

            std::cout << "Choose Communication Method: [1] WiFi, [2] Bluetooth, [3] Zigbee\n";
            int choice;
            std::cin >> choice;

            if (choice == 1)
                {
                emissionSensor.sendData("WiFi", "");
            }
            else if (choice == 2)
             {
                emissionSensor.sendData("Bluetooth", "Smartphone");
            }
             else if (choice == 3)
            {
                emissionSensor.sendData("Zigbee", "ZigbeeNetwork1");
            }
            else
            {
                std::cout << "Invalid choice.\n";
            }

            std::cout << "Integrate with [1] Smart Home or [2] Industrial System?\n";
            int integrationChoice;
            std::cin >> integrationChoice;

            if (integrationChoice == 1)
                {
                integrateWithSmartHome();
            }
            else if (integrationChoice == 2)
             {
                integrateWithIndustrialSystem();
            }
            else
            {
                std::cout << "Skipping integration.\n";
            }

            std::cout << "Continue? [y/n]: ";
            char cont;
            std::cin >> cont;
            if (cont == 'n' || cont == 'N')
                {
                break;
            }
        }

        // Generate compliance report
        std::string reportFilename = "compliance_report.txt";
        complianceSensor.generateReport(reportFilename);

        // Check compliance against a threshold
        double complianceThreshold = 410.0;
        complianceSensor.complianceCheck(complianceThreshold);

        // Example usage for maintenance
        maintenanceExample();

        // Simulate CO2 sensor with fail operation
        CO2FailSensor failSensor("Sensor_2", 1000, 300);
        std::thread sensorThread(&CO2FailSensor::run, &failSensor);
        sensorThread.detach();

        // Simulate CO2 sensor with evacuation routes
        CO2SensorWithEvacuation sensorWithEvacuation("Sensor_3", 1200);
        std::thread evacuationSensorThread(&CO2SensorWithEvacuation::run, &sensorWithEvacuation);
        evacuationSensorThread.detach();

        // Additional simulation for the SimulatedCO2Sensor
        while (true)
            {
            try
            {
                // Periodically read CO2 levels
                simulatedSensor.lastCO2Level = readSimulatedCO2Level(simulatedSensor);
                std::cout << "Simulated CO2 Level: " << simulatedSensor.lastCO2Level << " ppm\n";

                // Trigger alert if CO2 levels exceed a threshold
                if (simulatedSensor.lastCO2Level > 1000)
                    {
                    alertUser("High CO2 levels detected! Take action.");
                }

                // Perform diagnostics every 10 iterations
                static int diagnosticCounter = 0;
                diagnosticCounter++;
                if (diagnosticCounter >= 10)
                    {
                    diagnosticCounter = 0;
                    if (!performDiagnostics(simulatedSensor))
                        {
                        alertUser("System diagnostics failed! Check the system.");
                    }
                }

            }
            catch (const std::exception &e)
             {
                alertUser(e.what());
                simulatedSensor.isConnected = false; // Simulate sensor disconnection
            }

            // Sleep for 1 second before the next iteration
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // Option to change credentials
        std::string newUsername, newPassword;
        std::cout << "Would you like to change the username and password? [y/n]: ";
        char changeCredentials;
        std::cin >> changeCredentials;
        if (changeCredentials == 'y' || changeCredentials == 'Y')
            {
            std::cout << "Enter new username: ";
            std::cin >> newUsername;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            setNewCredentials(newUsername, newPassword);
        }

        // Option to reset credentials
        std::cout << "Would you like to reset the username and password to default values? [y/n]: ";
        char resetCreds;
        std::cin >> resetCreds;
        if (resetCreds == 'y' || resetCreds == 'Y')
            {
            resetCredentials();
        }
    }
     else
     {
        std::cout << "Login failed. Invalid username or password.\n";
    }
}
void pollutionControl()
 {
    // Run the user interface
    userInterface();
    //return 0;
}

int main()
{
    {
    int choice;

    cout << "Welcome to the Smart System Control Panel\n";
    cout << "Please select an option:\n";
    cout << "1. Traffic Control\n";
    cout << "2. Resource Management\n";
    cout << "3. Navigation Optimization\n";
    cout << "4. Pollution Control\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            trafficControl();
            break;
        case 2:
            resourceManagement();
            break;
        case 3:
            navigationOptimization();
            break;
        case 4:
            pollutionControl();
            break;
        default:
            cout << "Invalid choice! Please select a number between 1 and 4.\n";
            break;
    }

    return 0;

}
}
