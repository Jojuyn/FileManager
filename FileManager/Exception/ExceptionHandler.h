//
// Created by Jojuyn Jostar on 2025/7/17.
//

#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <stdexcept>

using namespace std;

namespace Exception {

class ExceptionHandler {
public:
    static void handleException(const exception& e);
};

constexpr string_view log_path = "";

class Logger
{
public:
    static void log(const string& message);
};

class InvalidPath : public runtime_error {};

class FileOccupied : public runtime_error {};

class NoPermission : public runtime_error {};

};





#endif //EXCEPTIONHANDLER_H
