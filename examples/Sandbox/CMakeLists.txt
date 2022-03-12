add_executable(Sandbox  src/Programm.cpp)

target_include_directories(Sandbox PRIVATE ../../include/)
target_include_directories(Sandbox PRIVATE ../../src/BulletGL/)
target_include_directories(Sandbox PRIVATE src/Sandbox/)

target_link_libraries(Sandbox PRIVATE BulletGL)