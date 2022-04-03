cmake_minimum_required(VERSION 3.20)
project(LabWork_5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Error)
include_directories(mainSM)
include_directories(Marking)
include_directories("Marking/Data Type")
include_directories("Marking/Data Type/Marker")
include_directories("Marking/Data Type/Marker/Access")
include_directories("Marking/Data Type/Marker/Frame state")
include_directories("Marking/Data Type/Msg")
include_directories("Marking/Data Type/Package")
include_directories("Marking/Data Type/Package/Pack")
include_directories("Marking/Data Type/Status")
include_directories("Marking/Data Type/Сropping")
include_directories("Marking/Data Type/Сropping/Frame")
include_directories(Menu)
include_directories("Menu/Menu main")
include_directories("Pseudo Terminal")
include_directories("Pseudo Terminal/Setting")
include_directories(Source)
include_directories("Station Monitor")
include_directories("Thread Control")

add_executable(LabWork_5
        Error/Error.hpp
        mainSM/main.cpp
        "Marking/Data Type/Marker/Access/Access.hpp"
        "Marking/Data Type/Marker/Frame state/FrameState.hpp"
        "Marking/Data Type/Marker/Marker.hpp"
        "Marking/Data Type/Msg/Msg.hpp"
        "Marking/Data Type/Package/Pack/Pack.hpp"
        "Marking/Data Type/Package/Package.cpp"
        "Marking/Data Type/Package/Package.hpp"
        "Marking/Data Type/Status/Status.hpp"
        "Marking/Data Type/Сropping/Frame/Frame.hpp"
        "Marking/Data Type/Сropping/Cropping.hpp"
        "Marking/Data Type/Сropping/Сropping.cpp"
        Marking/Marking.cpp
        Marking/Marking.hpp
        "Menu/Menu main/MenuPS.cpp"
        "Menu/Menu main/MenuPS.hpp"
        Menu/Menu.cpp
        Menu/Menu.hpp
        "Pseudo Terminal/Setting/PseudoterminalSettings.cpp"
        "Pseudo Terminal/Setting/PseudoterminalSettings.hpp"
        "Pseudo Terminal/Pseudoterminal.cpp"
        "Pseudo Terminal/Pseudoterminal.hpp"
        Source/main.cpp
        Source/MenuSM.cpp
        Source/MenuSM.hpp
        "Station Monitor/StationMonitor.cpp"
        "Station Monitor/StationMonitor.hpp"
        "Thread Control/ThreadControl.hpp")
