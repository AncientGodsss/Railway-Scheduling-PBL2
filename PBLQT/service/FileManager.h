#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

class RailwaySystem;

 
class FileManager
{
public:
    static bool saveAll(
        const RailwaySystem& system,
        const std::string& folder = "data/"
    );

    static bool loadAll(
        RailwaySystem& system,
        const std::string& folder = "data/"
    );
};

#endif

