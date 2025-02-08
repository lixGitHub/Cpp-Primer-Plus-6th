#include <iostream>
#include <string>
#include <ostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <typeinfo>


std::string EpochToDateTime(const std::string& epoch_string)
{
    if (epoch_string.empty())
    {
        return "";
    }
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "epoch time: " << epoch_string << std::endl;

    std::time_t epoch_time = std::stoll(epoch_string);


    std::tm* time = std::localtime(&epoch_time);
    // std::mktime(time);
    // std::ostringstream oss1;
    // oss1 << std::put_time(time, "%Y-%m-%d %H:%M:%S UTC%z %Z");
    std::cout << "[DEBUG] ----- local time: " << std::put_time(time, "%Y-%m-%d %H:%M:%S UTC%z %Z") << std::endl;


    // Convert to UTC-0 time
    std::tm* utc_time = std::gmtime(&epoch_time);
    // std::mktime(time);
    std::cout << "[DEBUG] ----- UTC-0 time: " << std::put_time(utc_time, "%Y-%m-%d %H:%M:%S UTC-0") << std::endl;


    // Check if it's daylight saving time (DST) for Central Time
    // Central Time is UTC-6 in standard time, UTC-5 during DST
    std::tm central_time = *utc_time;
    std::cout << "before mktime, tm_isdst:" << central_time.tm_isdst << std::endl;
    std::cout << "               :time:   " << std::put_time(&central_time, "%Y-%m-%d %H:%M:%S") << std::endl;

    std::time_t epoch_time_bk = std::mktime(&central_time);

    std::cout << "after mktime,  tm_isdst:" << central_time.tm_isdst << std::endl;
    std::cout << "               :time:   " << std::put_time(&central_time, "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "             epoch time:" << epoch_time_bk << " diff: " << epoch_time_bk - epoch_time << std::endl;

    // epoch time is UTC-0, convert to UTC-6
    epoch_time -= 3600 * 6;
    std::tm* cst = std::gmtime(&epoch_time);
    std::cout << "[DEBUG] ----- UTD-6 time: " << std::put_time(cst, "%Y-%m-%d %H:%M:%S UTC-6") << std::endl;
    // 
    std::mktime(cst);
    std::cout << "[DEBUG] -----adjust time: " << std::put_time(cst, "%Y-%m-%d %H:%M:%S") << std::endl;

    // if (central_time.tm_isdst)
    // {
    //     central_time.tm_hour -= 6;
    // }
    // else
    // {
    //     central_time.tm_hour -= 5;
    // }
    

    // // central_time.tm_hour -= (central_time.tm_mon >= 2 && central_time.tm_mon <= 10) ? 5 : 6; // DST: UTC-5, otherwise UTC-6
    // std::mktime(&central_time); // Normalize the time structure

    // Format the time as a string
    std::ostringstream oss;
    oss << std::put_time(&central_time, "%Y-%m-%d %H:%M:%S");

    std::cout << "[DEBUG] ----- US central time: " << oss.str() << " daytime saving: " << central_time.tm_isdst << std::endl;

    return oss.str();
}

bool IsDST(const std::tm* central_time) {
    int month = central_time->tm_mon + 1;  // tm_mon is 0-11
    int day = central_time->tm_mday;
    int wday = central_time->tm_wday;      // 0 = Sunday
    int hour = central_time->tm_hour;

    // DST begins on the second Sunday in March at 2:00 AM
    // DST ends on the first Sunday in November at 2:00 AM


    // Always DST during April through October
    if (month > 3 && month < 11) {
        return true;
    }

    // March: DST starts on second Sunday at 2:00 AM
    if (3 == month)
    {
        // Calculate the day of 2nd sunday.
        int sunday_2nd = (1 - std::floor((day - wday) / 7.0)) * 7 + (day - wday);
        std::cout << "sunday_2nd: " << sunday_2nd << std::endl;

        if (day < sunday_2nd)
        {
            return false;
        }
        else if (day == sunday_2nd && hour < 2)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // November: DST ends on first Sunday at 2:00 AM
    if (11 == month) {

        // Find the first Sunday in November.
        int sunday_1st =  (day - wday) - ((std::floor((day - wday) / 7.0)) * 7);
        std::cout << "sunday_1st: " << sunday_1st  << "  calculate: " << (std::floor((day - wday) / 7.0)) << std::endl;

        if (day < sunday_1st)
        {
            return true;
        }
        else if (day == sunday_1st && hour < 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Not DST during December, January, February
    if (month < 3 || month > 11) {
        return false;
    }
    return false;

    // // Find the Most close Sunday of this month.
    // int close_sunday = ((day - wday)%7);

    // // Calculate 这月第一天是周几
    // int week_num = (day / 7);
    // int wday_1st_day = (wday - (day - week_num * 7) + 1) % 7;


    // // Calculate the day of 2nd sunday.
    // int sunday_2nd = (1 - std::floor((day - wday) / 7)) * 7 + (day - wday);
}

std::string EpochToUSCentralTime(const std::string& epoch_string)
{
    if (epoch_string.empty())
    {
        return "";
    }
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "epoch time: " << epoch_string << std::endl;

    std::time_t epoch_time = std::stoll(epoch_string);

    std::tm* utc_time = std::gmtime(&epoch_time);
    std::mktime(utc_time);
    std::cout << "[DEBUG] ----- UTC-0 time: " << std::put_time(utc_time, "%Y-%m-%d %H:%M:%S UTC-0") << std::endl;


     std::tm* time = std::localtime(&epoch_time);
    std::cout << "[DEBUG] ----- local time: " << std::put_time(time, "%Y-%m-%d %H:%M:%S UTC%z %Z")  << " daylight: " << time->tm_isdst << std::endl;

    // epoch time is UTC+0000 (GMT), convert to UTC-0600 (CST)
    epoch_time -= 3600 * 6;
    std::tm* central_time = std::gmtime(&epoch_time);
    std::cout << "[DEBUG] ----- CST   time: " << std::put_time(central_time, "%Y-%m-%d %H:%M:%S UTC-0600 CST") << std::endl;

    // Change to UTC-0500 (CDT) if it is during daylight saving.
    // std::mktime(central_time); // this is not reliable, if I change the time zone of computer to europe, it will not consider CDT.
    bool is_CDT = IsDST(central_time);
    std::cout << "is CDT: " << is_CDT << std::endl;
    if (is_CDT)
    {
        epoch_time += 3600;
        central_time = std::gmtime(&epoch_time);
        central_time->tm_isdst = 1;
    }
    
    
    std::cout << "[DEBUG] ----- Central time: " << std::put_time(central_time, "%Y-%m-%d %H:%M:%S ");
    std::cout << (is_CDT? "CDT" : "CST") << std::endl;

    
    std::ostringstream oss;
    oss << std::put_time(central_time, "%Y-%m-%d %H:%M:%S ")
        << (is_CDT? "CDT" : "CST") ;

    return oss.str();
}

std::string EpochToUTC6(const std::string& epoch_string)
{
    std::time_t epoch_time;
    try
    {
        epoch_time = std::stoll(epoch_string);
    }
    catch (std::invalid_argument const& ex)
    {
        std::cerr << "Failed to convert " << epoch_string << " to time. Error: invalid argument." << std::endl;
        return "";
    }
    catch (std::out_of_range const& ex)
    {
        std::cerr << "Failed to convert " << epoch_string << " to time. Error: out of range." << std::endl;
        return "";
    }

    if (epoch_string.empty())
    {
        return "";
    }
    std::cout << "pass try catch, result: " << epoch_time << std::endl; 
    
    char x;
    std::cout << "type of one char: " << typeid(epoch_string[0]).name() << std::endl;
    std::cout << "type of one character of string: " << typeid(epoch_string[0]).name() << std::endl;
    std::cout << "type of one character of string: " << typeid(*epoch_string.begin()).name() << std::endl;

    std::cout << "std::stoll converted " << epoch_string << " to " << epoch_time << std::endl;

    // bool valid = std::all_of(epoch_string.begin(), epoch_string.end(), [](char c) { return std::isdigit(c); });
    bool valid = (epoch_string[0] == '-' || std::isdigit(epoch_string[0])); // &&
    bool valid2 = std::all_of(epoch_string.begin() + 1, epoch_string.end(), [](char c)
                             { return std::isdigit(c); });
    // if (!valid)
    // {
    //     std::cout << "not valid\n";
    //     return "";
    // }
    std::cout << "valid: " << valid << std::endl;
    std::cout << "valid2: " << valid2 << std::endl;

    // std::time_t epoch_time = std::stoll(epoch_string);
    std::cout << "converted epoch time: " << epoch_time << std::endl;

    // epoch time is based on UTC+0, convert to UTC-6 (CST)
    epoch_time -= 3600 * 6;
    std::tm* central_time = std::gmtime(&epoch_time);

    std::ostringstream oss;
    oss << std::put_time(central_time, "%Y-%m-%d %H:%M:%S UTC-6");

    return oss.str();
}


std::string EpochIntToUSCentralTime(int64_t epoch_time_int)
{
    std::time_t epoch_time = epoch_time_int;

    // epoch time is based on UTC+0, convert to UTC-6 (CST)
    epoch_time -= 3600 * 6;
    std::tm* central_time = std::gmtime(&epoch_time);

    std::ostringstream oss;
    oss << std::put_time(central_time, "%Y-%m-%d %H:%M:%S UTC-6");

    return oss.str();
}

std::string EpochStrToUSCentralTime(const std::string& epoch_string)
{
    // QString epoch_qstr = QString::fromStdString(epoch_string);
    // std::string trimmed_string = epoch_qstr.trimmed().toStdString();
    std::string trimmed_string = epoch_string;

    // Strings such as " 4568543gfASE" will be partially converted by std::stoll without throwing an exception.
    bool valid = (trimmed_string[0] == '-' || std::isdigit(trimmed_string[0])) &&
                 std::all_of(trimmed_string.begin() + 1, trimmed_string.end(), [](char c)
                             { return std::isdigit(c); });
    if (!valid)
    {
        std::cout << "Failed to convert to time. invalid argument: " << trimmed_string << std::endl;
        return "";
    }
    
    int64_t epoch_time_int;
    try
    {
        epoch_time_int = std::stoll(trimmed_string);
    }
    catch (std::invalid_argument const& ex)
    {
        std::cout << "Failed to convert  to time. Error: invalid argument: " << trimmed_string << std::endl;
        return "";
    }
    catch (std::out_of_range const& ex)
    {
         std::cout << "Failed to convert {} to time. Error: out of range: " << trimmed_string << std::endl;
        return "";
    }

    // epoch time is based on UTC+0, convert to UTC-6 (CST)
    return EpochIntToUSCentralTime(epoch_time_int);
}


int main(int argc, char *argv[])
{
    // std::string epoch_time = "dfw4245./)&#";
    // std::string epoch_time = "";
    // std::string epoch_time = "  14568543ASE"; // this will not have exception
    std::string epoch_time = "-156878453"; // this will not have exception

    std::cout << "time: " << EpochStrToUSCentralTime(epoch_time) << std::endl;

    int64_t epoch_time_int = -1234566;
    std::cout << epoch_time_int << " time: " << EpochStrToUSCentralTime(epoch_time) << std::endl;

    return 0;

    // 1710054000   03-10-2024 01:00
    // 1710057600   03-10-2024 02:00  
    // 1710057600   03-10-2024 03:00
    // 1710061200   03-10-2024 04:00 

    // 1730610000   11-02-2024 24:00
    // 1730613600   11-03-2024 01:00
    // 1730617200   11-03-2024 01:00
    // 1730620800   11-03-2024 02:00
    // 1730624400   11-03-2024 03:00
    
    std::vector<std::string> time_list{
        "1709632800",   // 03-05-2024 01:00
        "1710028800",
        "1710032400",
        "1710035999",   // not daytime
        "1710036000",   // daytime
        "1710039600",
        "1710050400",
        "1710054000",   // 03-10-2024 01:00
        "1710057599",   // 03-10-2024 01:59
        "1710057600",   // 03-10-2024 02:00  
        "1710061200",   // 03-10-2024 04:00 

        "1730584800",
        "1730588400",
        "1730592000",
        "1730595599",   // day time
        "1730595600",   // not daytime
        "1730599200",
        "1730602800",
        "1730606400",
        "1730610000",   // 11-02-2024 24:00
        "1730613600",   // 11-03-2024 01:00
        "1730617199",   // 11-03-2024 01:00
        "1730617200",   // 11-03-2024 01:00
        "1730620800",   // 11-03-2024 02:00
    };

    for (size_t i = 0; i < time_list.size(); i++)
    {
        // EpochToDateTime(time_list[i]);
        EpochToUSCentralTime(time_list[i]);
    }
    
    // epoch_time = "1730610000";
    // EpochToDateTime(epoch_time);

    // epoch_time = "1730613600";
    // EpochToDateTime(epoch_time);

    // epoch_time = "1730617200";
    // EpochToDateTime(epoch_time);

    // epoch_time = "1730620800";
    // EpochToDateTime(epoch_time);

    // epoch_time = "1730624400";
    // EpochToDateTime(epoch_time);

}
