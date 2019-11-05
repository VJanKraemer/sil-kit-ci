// Copyright (c) Vector Informatik GmbH. All rights reserved.

#include "NamedPipe.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstring>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <exception>
#include <iostream>

namespace ib {
namespace sim {
namespace eth {

class NamedPipeLinux: public NamedPipe
{
public:
    // ----------------------------------------
    // Constructors and Destructor
    NamedPipeLinux(const std::string &name)
    :_name(name)
    {
        int err = ::mkfifo(_name.c_str(), 0644);
        if(err == -1)
        {
            std::stringstream ss;
            ss  << "Error creating pipe \"" << _name << "\""
                << ": errno: " << err
                << ": " << strerror(errno)
                ;

            throw std::runtime_error(ss.str());
        }
        _file.open(_name, std::ios_base::out|std::ios_base::binary);
        if(!_file.good())
        {
            std::stringstream ss;
            ss << "fstream open \"" << _name << "\" failed!";

            throw std::runtime_error(ss.str());
        }
        _isOwner = true;
    }
    ~NamedPipeLinux()
    {
        if(_isOwner)
        {
            int err = ::unlink(_name.c_str());
            if(err == -1)
            {
                std::cerr  << "Error deleting pipe \"" << _name << "\""
                    << ": errno: " << err
                    << ": " << strerror(errno)
                    ;

            }
        }
    }

public:
    // ----------------------------------------
    // Public interface methods
    bool Write(const char *buffer, size_t bufferSize) override
    {
        _file.write(buffer, bufferSize);
        _file.flush();
        return _file.good();
    }
    
private:
    // ----------------------------------------
    // private members
    std::string _name;
    std::fstream _file;
    bool _isOwner{false};

    int _fd = -1;
};

std::unique_ptr<NamedPipe> NamedPipe::Create(const std::string& name)
{
    return std::make_unique<NamedPipeLinux>(name);
}

} //namespace ib
} //namespace sim
} //namespace eth
