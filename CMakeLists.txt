cmake_minimum_required(VERSION 3.15)
project(SimulatorProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(.)

add_executable(SimulatorProject
        Client.cpp
        Client.h
        Command.h
        CommandClasses.cpp
        CommandClasses.h
        Expression.h
        Interpreter.cpp
        Interpreter.h
        main.cpp
        Operators.cpp
        Operators.h
        Server.cpp
        Server.h
        SymbolTable.cpp
        SymbolTable.h
        utilities.cpp
        utilities.h
        VariableData.cpp
        VariableData.h UpdateSimulator.cpp UpdateSimulator.h)
