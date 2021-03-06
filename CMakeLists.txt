project(QLogo)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS OpenGLWidgets REQUIRED)

set(QLOGO_SOURCES qlogo_main.cpp mainwindow.cpp canvas.cpp console.cpp)

set(QLOGO_HEADERS mainwindow.h canvas.h console.h constants.h)

set(QLOGO_UI mainwindow.ui)

add_executable(QLogo ${QLOGO_SOURCES} ${QLOGO_HEADERS} ${QLOGO_UI})

target_link_libraries(QLogo Qt6::Widgets Qt6::OpenGLWidgets)



set(LOGO_SOURCES datum.cpp parser.cpp turtle.cpp vars.cpp kernel.cpp propertylists.cpp kernel_datastructureprimitives.cpp kernel_communication.cpp kernel_arithmetic.cpp kernel_graphics.cpp kernel_workspacemanagement.cpp workspace.cpp procedurehelper.cpp help.cpp kernel_controlstructures.cpp error.cpp library.cpp datum_word.cpp datum_astnode.cpp datum_list.cpp datum_array.cpp datum_datump.cpp datum_iterator.cpp logo_main.cpp qlogocontroller.cpp logocontroller.cpp controller.cpp inputqueue.cpp)

set(LOGO_HEADERS datum.h parser.h turtle.h vars.h kernel.h propertylists.h workspace.h procedurehelper.h help.h error.h constants.h qlogocontroller.h logocontroller.h controller.h library.h inputqueue.h)

add_definitions(-DLOGOVERSION="0.93" -DCONTROLLER_HEADER="logo_controller.h")

if(APPLE)
  add_definitions(-DLOGOPLATFORM="OSX")
elseif(WIN32 OR MINGW OR MSYS OR CYGWIN)
  add_definitions(-DLOGOPLATFORM="WINDOWS")
else()
  add_definitions(-DLOGOPLATFORM="UNIX")
endif()

add_executable(logo ${LOGO_SOURCES} ${LOGO_HEADERS})

target_link_libraries(logo Qt6::Core Qt6::Widgets)

install(TARGETS QLogo logo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
