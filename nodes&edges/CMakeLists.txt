cmake_minimum_required(VERSION 3.10)

project(app_node)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(Qt5_DIR "C:/Qt/5.14.1/msvc2017_64/lib/cmake/Qt5" CACHE PATH "Initial cahe" FORCE)

SET(CMAKE_INSTALL_PREFIX $<TARGET_FILE_DIR:${PROJECT_NAME}> CACHE PATH "Initial cahe" FORCE)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)


set(project_headers
mainwindow.h
edge.h
graphwidget.h
moc_predefs.h
node.h
ui_mainwindow.h)

set(project_sources
main.cpp
mainwindow.cpp
edge.cpp
node.cpp
graphwidget.cpp
moc_graphwidget.cpp
moc_mainwindow.cpp)

set(project_ui
mainwindow.ui)

qt5_wrap_ui(project_headers_wrapped ${project_ui})
qt5_wrap_cpp(project_sources_moc ${project_headers})

add_executable(${PROJECT_NAME} ${project_headers} ${project_sources}
${project_sources_moc} ${project_headers_wrapped})


target_link_libraries(${PROJECT_NAME}
PUBLIC
Qt5::Core
Qt5::Gui
Qt5::Widgets)


install(FILES $<TARGET_FILE:Qt5::Core> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(FILES $<TARGET_FILE:Qt5::Gui> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(FILES $<TARGET_FILE:Qt5::Widgets> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
