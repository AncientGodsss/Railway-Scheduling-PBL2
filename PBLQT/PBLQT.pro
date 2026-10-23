QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET   = PBLQT
TEMPLATE = app

# Warning: using non-Qt data structures (self-implemented)
# Suppress pedantic warnings that conflict with Qt macros
QMAKE_CXXFLAGS += -Wno-unused-parameter

# Đảm bảo tiếng Việt hiển thị đúng (UTF-8)
QMAKE_CXXFLAGS += -finput-charset=UTF-8 -fexec-charset=UTF-8
DEFINES += QT_USE_QSTRINGBUILDER

SOURCES += \
    main.cpp \
    system/RailwaySystem.cpp \
    service/FileManager.cpp \
    ui/MainWindow.cpp \
    ui/dialogs/TrainDialog.cpp \
    ui/dialogs/StationDialog.cpp \
    ui/dialogs/RouteDialog.cpp \
    ui/dialogs/ScheduleDialog.cpp \
    ui/dialogs/StopDialog.cpp

HEADERS += \
    model/Train.h \
    model/Station.h \
    model/Route.h \
    model/Schedule.h \
    model/Stop.h \
    model/TimeUtils.h \
    model/Operation.h \
    service/ConflictDetector.h \
    service/Dispatcher.h \
    service/EarliestStrategy.h \
    service/FileManager.h \
    service/PriorityStrategy.h \
    service/SchedulingStrategy.h \
    system/RailwaySystem.h \
    data_structure/BST.h \
    data_structure/DoublyLinkedList.h \
    data_structure/Graph.h \
    data_structure/HashTable.h \
    data_structure/MaxHeap.h \
    data_structure/MinHeap.h \
    data_structure/Queue.h \
    data_structure/Stack.h \
    ui/MainWindow.h \
    ui/StyleSheet.h \
    ui/dialogs/TrainDialog.h \
    ui/dialogs/StationDialog.h \
    ui/dialogs/RouteDialog.h \
    ui/dialogs/ScheduleDialog.h \
    ui/dialogs/StopDialog.h

FORMS += \
    ui/forms/MainWindow.ui \
    ui/forms/TrainDialog.ui \
    ui/forms/StationDialog.ui \
    ui/forms/RouteDialog.ui \
    ui/forms/ScheduleDialog.ui \
    ui/forms/StopDialog.ui
