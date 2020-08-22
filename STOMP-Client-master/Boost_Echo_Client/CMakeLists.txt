cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)
include_directories(src/messeges)

add_executable(Boost_Echo_Client
        include/AbstractFrame.h
        include/Connect.h
        include/Connected.h
        include/connectionHandler.h
        include/Disconnect.h
        include/Message.h
        include/Receipt.h
        include/Send.h
        include/Subscribe.h
        include/MessegeEncoderDecoder.h
        src/MessageEncoderDecoder.cpp
        src/messeges/ClientFrame/Connect.cpp
        src/messeges/ClientFrame/Disconnect.cpp
        src/messeges/ClientFrame/Send.cpp
        src/messeges/ClientFrame/Subscribe.cpp
        src/messeges/ServerFrame/Connected.cpp
        src/messeges/ServerFrame/Message.cpp
        src/messeges/ServerFrame/Receipt.cpp
        src/messeges/AbstractFrame.cpp
        src/connectionHandler.cpp
        src/echoClient.cpp)
