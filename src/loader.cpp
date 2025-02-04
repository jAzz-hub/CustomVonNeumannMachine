

#include"./memory/MAINMEMORY.h"

const int MEMORY_SIZE = 2048*2048; // 32-bit address space

std::string padName(const std::string& name) {
    return name + std::string(16 - name.length(), '#');
}

void loadProgramInRam(const std::string& inputFile, MainMemory & ram) {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::unordered_map<std::string, int> labelAddresses;
    std::unordered_map<std::string, int> variableAddresses;
    std::vector<std::string> instructions;
    int address = 0;

    std::string line;

    // Read instructions and data
    while (std::getline(file, line)) {
      std::string trimmedLine = line;
      trimmedLine.erase(trimmedLine.find_last_not_of(" \n\r\t") + 1);
        
      // data section
      if (trimmedLine.find(".data") != std::string::npos) {
        while (std::getline(file, line)) {
            std::istringstream dataStream(line);
            std::string variableName;
            std::string values;
            std::string value;

          // Extract variable name and value from the format "var: value"
          if (dataStream >> variableName) {
            size_t colonPos = variableName.find(':');
            if (colonPos != std::string::npos) {
                variableName = variableName.substr(0, colonPos); 
                variableAddresses[padName(variableName)] = address;

                std::getline(dataStream, values);
                std::istringstream valueStream(values);

                while (std::getline(valueStream, value, ',')) {
                    if (address >= MEMORY_SIZE) {
                        std::cerr << "Memory overflow while allocating vector data." << std::endl;
                        return;
                    }
                    // Convert the value to int and store it in memory
                    int intValue = std::stoi(value);
                    ram.WriteMem(address,intValue);

                    address += 1; 
                }
            }
          }    
        }
      // break if at the end of the data section
      break; 
    }
    // Check for labels
    else if (trimmedLine.find(":") != std::string::npos) {
        size_t colonPos = trimmedLine.find(":");
        std::string label = trimmedLine.substr(0, colonPos);
        labelAddresses[padName(label)] = address; 

         //std::cout << "Label: " << padName(label) << " Address: " << labelAddresses[padName(label)] << std::endl;
         if (std::getline(file, line)) {
            instructions.push_back(line); // Store instruction
            address += 1; 
        }
    }
    // Regular instruction
    else {
        instructions.push_back(trimmedLine);
        address += 1; 
      }
    }

    // No vector instructions eu tenho as instruções
    // Vem de linha em linha
    // PROCESS[1].instructions comparar PROCESS[2].instructions


    // Substitute addresses in instructions
    int memAddress = 0;
    for (auto instruction : instructions) {
        for (const auto& [label, addr] : labelAddresses) {
            size_t pos = instruction.find(label);
            if (pos != std::string::npos) {
                // Substitute label with address
                instruction.replace(pos, label.length(), std::bitset<16>(addr).to_string());
            }
        }
        for (const auto& [varName, addr] : variableAddresses) {
            size_t pos = instruction.find(varName);
            if (pos != std::string::npos) {
                // Substitute variable with address
                instruction.replace(pos, varName.length(), std::bitset<16>(addr).to_string());
            }
        }
        
        size_t pos = instruction.find("#");
        if (pos != std::string::npos) {
            std::cerr << "Can't resolve symbol at instruction: " << instruction << std::endl; 
        }

        // Convert instruction string to binary and store in memory
        try {
            ram.WriteMem(memAddress, std::stoul(instruction, nullptr, 2));
        } catch (const std::exception& e) {
            std::cerr << "Conversion error at: " << instruction << std::endl;
        }
        memAddress++;
    }

}

void loadProgramInCache(const std::string& inputFile, Cache & mem) {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::unordered_map<std::string, int> labelAddresses;
    std::unordered_map<std::string, int> variableAddresses;
    std::vector<std::string> instructions;
    int address = 0;

    std::string line;

    // Read instructions and data
    while (std::getline(file, line)) {
      std::string trimmedLine = line;
      trimmedLine.erase(trimmedLine.find_last_not_of(" \n\r\t") + 1);
        
      // data section
      if (trimmedLine.find(".data") != std::string::npos) {
        while (std::getline(file, line)) {
            std::istringstream dataStream(line);
            std::string variableName;
            std::string values;
            std::string value;

          // Extract variable name and value from the format "var: value"
          if (dataStream >> variableName) {
            size_t colonPos = variableName.find(':');
            if (colonPos != std::string::npos) {
                variableName = variableName.substr(0, colonPos); 
                variableAddresses[padName(variableName)] = address;

                std::getline(dataStream, values);
                std::istringstream valueStream(values);

                while (std::getline(valueStream, value, ',')) {
                    if (address >= MEMORY_SIZE) {
                        std::cerr << "Memory overflow while allocating vector data." << std::endl;
                        return;
                    }
                    // Convert the value to int and store it in memory
                    int intValue = std::stoi(value);
                    mem.WriteMem(address,intValue);

                    address += 1; 
                }
            }
          }    
        }
      // break if at the end of the data section
      break; 
    }
    // Check for labels
    else if (trimmedLine.find(":") != std::string::npos) {
        size_t colonPos = trimmedLine.find(":");
        std::string label = trimmedLine.substr(0, colonPos);
        labelAddresses[padName(label)] = address; 

         //std::cout << "Label: " << padName(label) << " Address: " << labelAddresses[padName(label)] << std::endl;
         if (std::getline(file, line)) {
            instructions.push_back(line); // Store instruction
            address += 1; 
        }
    }
    // Regular instruction
    else {
        instructions.push_back(trimmedLine);
        address += 1; 
      }
    }

    // No vector instructions eu tenho as instruções
    // Vem de linha em linha
    // PROCESS[1].instructions comparar PROCESS[2].instructions


    // Substitute addresses in instructions
    int memAddress = 0;
    for (auto instruction : instructions) {
        for (const auto& [label, addr] : labelAddresses) {
            size_t pos = instruction.find(label);
            if (pos != std::string::npos) {
                // Substitute label with address
                instruction.replace(pos, label.length(), std::bitset<16>(addr).to_string());
            }
        }
        for (const auto& [varName, addr] : variableAddresses) {
            size_t pos = instruction.find(varName);
            if (pos != std::string::npos) {
                // Substitute variable with address
                instruction.replace(pos, varName.length(), std::bitset<16>(addr).to_string());
            }
        }
        
        size_t pos = instruction.find("#");
        if (pos != std::string::npos) {
            std::cerr << "Can't resolve symbol at instruction: " << instruction << std::endl; 
        }

        // Convert instruction string to binary and store in memory
        try {
            mem.WriteMem(memAddress, std::stoul(instruction, nullptr, 2));
        } catch (const std::exception& e) {
            std::cerr << "Conversion error at: " << instruction << std::endl;
        }
        memAddress++;
    }

}

