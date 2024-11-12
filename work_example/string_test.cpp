#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <sstream>

struct FieldInfo
{
    std::string field_name;
    std::string field_value;
    int field_width;
};

struct HardwareInfo_Layout
{
    std::string head_name;
    int head_width;
    std::vector<std::vector<FieldInfo>> fields;
    std::unordered_map<std::string, std::pair<int, int>> location;
};

HardwareInfo_Layout base_station_layout{
    "BaseStation",
    18,
    {{{"UUID:", "", 19}, {"Serial_Number:", "", 10}, {"Direct_Comm_Status:", "", 46}, {"", "", 0}},
     {{"Sync_Channel:", "", 19}, {"USB_Port:", "", 10}, {"Connected:", "", 20}, {"State:", "", 26}}},

    {{"UUID:", {0, 0}}, {"Serial_Number:", {0, 1}}, {"Direct_Comm_Status:", {0, 2}}, 
    {"Sync_Channel:", {1, 0}}, {"USB_Port:", {1, 1}}, {"Connected:", {1, 2}}, {"State:", {1, 3}}},
};

HardwareInfo_Layout siu_layout{
    "SIU",
    18,
    {{{"UUID:", "", 19}, {"Serial_Number:", "", 28}, {"Data_Channel:", "", 20}, {"Wireless:", "", 26}},
     {{"Sync_Channel:", "", 19}, {"USB_Port:", "", 28}, {"Connected:", "", 20}, {"State:", "", 26}}},

    {{"UUID:", {0, 0}}, {"Serial_Number:", {0, 1}}, {"Data_Channel:", {0, 2}}, {"Wireless:", {0, 3}}, 
    {"Sync_Channel:", {1, 0}}, {"USB_Port:", {1, 1}}, {"Connected:", {1, 2}}, {"State:", {1, 3}}},
};

HardwareInfo_Layout wireless_receiver_layout{
    "WirelessReceiver",
    18,
    {{{"UUID:", "", 19}, {"Serial_Number:", "", 28}, {"Data_Channel:", "", 20}},
     {{"Connected:", "", 19}, {"USB_Port:", "", 28}, {"State:", "", 20}}},
    {
        {"UUID:", {0, 0}},{"Serial_Number:", {0, 1}},{"Data_Channel:", {0, 2}},
        {"Connected:", {1, 0}},{"USB_Port:", {1, 1}},{"State:", {1, 2}},
    },
};

int main(int argc, char *argv[])
{
    // std::string str("UUID:");
    // std::cout << std::left << std::setw(str.length() + 1) << str << ", length: " << str.length() << "\n";

    // std::cout << base_station_layout.head_name << ": " << base_station_layout.head_width << "\n";
    // for (int i = 0; i < base_station_layout.fields.size(); i++)
    // {
    //     for (int j = 0; j < base_station_layout.fields[i].size(); j++)
    //     {
    //         if (0 == base_station_layout.fields[i][j].field_width)
    //         {
    //             continue;
    //         }

    //         std::string field_name(base_station_layout.fields[i][j].field_name);
    //         int filed_width = base_station_layout.fields[i][j].field_width;
    //         std::cout << std::left << std::setw(field_name.length()+1) << field_name
    //                   << std::setw(filed_width - field_name.length() - 1) << filed_width
    //                   ;
    //     }
    //     std::cout << "\n";
    // }

    int uuid = 132945;
    std::string serial_number("3BDSDGFGLE444");
    std::string usb_port_name("/ttyp");
    bool connected = true;
    std::string hardware_state("IDLE");
    int sync_channel = 255;
    std::string direct_comm_status("Try Connect");

    HardwareInfo_Layout print_layout;
    std::pair<int, int> field_location;

    // Set the field value.
    print_layout = base_station_layout;
    field_location = print_layout.location["UUID:"];
    print_layout.fields[field_location.first][field_location.second].field_value = std::to_string(uuid);
    field_location = print_layout.location["Serial_Number:"];
    print_layout.fields[field_location.first][field_location.second].field_value = serial_number;
    field_location = print_layout.location["USB_Port:"];
    print_layout.fields[field_location.first][field_location.second].field_value = usb_port_name;
    field_location = print_layout.location["Connected:"];
    print_layout.fields[field_location.first][field_location.second].field_value = (connected ? "YES" : "NO");
    field_location = print_layout.location["State:"];
    print_layout.fields[field_location.first][field_location.second].field_value = hardware_state;
    field_location = print_layout.location["Sync_Channel:"];
    print_layout.fields[field_location.first][field_location.second].field_value = std::to_string(sync_channel);
    field_location = print_layout.location["Direct_Comm_Status:"];
    print_layout.fields[field_location.first][field_location.second].field_value = direct_comm_status;

    // Adjust the actual print width based on field value.
    int y_num = print_layout.fields[0].size();
    int x_num = print_layout.fields.size();
    for (int k = 0; k < y_num; k++)
    {
        // last column does not adjust.
        if (k + 1 == y_num)
        {
            continue;
        }

        // find the maximum string length of this column.
        int print_width = print_layout.fields[0][k].field_width;
        for (int j = 0; j < x_num; j++)
        {
            // if the next column is empty, no need to consider.
            if (k + 1 < y_num && print_layout.fields[j][k + 1].field_width == 0)
            {
                continue;
            }
            // skip the empty field.
            if (print_layout.fields[j][k].field_width == 0)
            {
                continue;
            }

            int actual_width = print_layout.fields[j][k].field_value.length() + print_layout.fields[j][k].field_name.length() + 1;
            if (print_width < actual_width)
            {
                print_width = actual_width;
            }
        }
        // update the print length of this column.
        for (int j = 0; j < x_num; j++)
        {
            print_layout.fields[j][k].field_width = print_width;
            // print_layout.fields[j][k].field_value = std::to_string(print_width);
        }
    }

    // Set print strings.
    std::vector<std::string> hardware_info_strings;
    std::stringstream temp_stream;
	for (int j = 0; j < print_layout.fields.size(); j++)
	{
		temp_stream.str("");
		if (0 == j)
		{
			temp_stream << std::left << std::setw(print_layout.head_width) << print_layout.head_name; 
		}
		else
		{
			temp_stream << std::left << std::setw(print_layout.head_width) << std::string(" ");
		}
		for (int k = 0; k < print_layout.fields[j].size(); k++)
		{
			int width = print_layout.fields[j][k].field_width;
			std::string value = print_layout.fields[j][k].field_value;
			std::string name = print_layout.fields[j][k].field_name;
			temp_stream << std::left << std::setw(name.length()+1) << name
                        // << std::setw(width - name.length() - 1) << width - name.length() - 1;
						<< std::setw(width - name.length() - 1) << value;
		}
		hardware_info_strings.push_back(temp_stream.str());
	}


    // print the string.
    for (size_t i = 0; i < hardware_info_strings.size(); i++)
    {
        std::cout << hardware_info_strings[i] << "\n";
    }
    

    return 0;
}