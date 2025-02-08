
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string ExtractCrashInfoByKey(const std::string &crash_report, const std::string &key)
{
    size_t pos = 0;

    // Loop through the string by lines
    while (pos < crash_report.length())
    {
        // Extract a line
        size_t line_end_pos = crash_report.find('\n', pos);
        if (line_end_pos == std::string::npos)
        {
            line_end_pos = crash_report.length();
        }

        std::string line = crash_report.substr(pos, line_end_pos - pos);

        // Check if the line starts with "Error Code:"
        size_t key_pos = line.find(key);
        if (key_pos != std::string::npos)
        {
            // Skip over "Error Code:" and any following spaces
            size_t code_start = key_pos + key.length();

            // Skip any leading spaces after "Error Code:"
            while (code_start < line.length() && std::isspace(line[code_start]))
            {
                code_start++;
            }

            // // Extract the error code, which is the remaining part of the line
            // size_t code_end = line.find_first_of("\n", code_start);  // stop at space or newline
            // if (code_end == std::string::npos) {
            //     code_end = line.length();  // if no space, take until the end of the line
            // }

            // Return the extracted error code
            return line.substr(code_start, line.length() - code_start);
        }

        // Move to the next line
        pos = line_end_pos + 1;
    }

    return "";
}

std::string ConvertEpochToString(const std::string& epoch_string)
{
    std::time_t epochTime = std::stoll(epoch_string);

    std::tm* timeInfo = std::localtime(&epochTime);

    std::ostringstream oss;
    oss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

int main()
{
    std::string crash_report = "Revision: 0\nError Code: 17\nFile Length: 25\nFile Name: comms_esb_basestation.cpp\nLine Number: 782\nEpoch Time: 1728664982\nMessage: Wireless communication error \nCRASH_DATA_TYPE_UNSIGNED_INT12308";

    std::string key("Error Code: ");
    std::cout << key << ExtractCrashInfoByKey(crash_report, key) << std::endl;
    
    key = "Epoch Time:";
    std::cout << key << ExtractCrashInfoByKey(crash_report, key) << std::endl;

    std::cout << "Readable Epoch Time: " << ConvertEpochToString(ExtractCrashInfoByKey(crash_report, key)) << std::endl;

    return 0;
}