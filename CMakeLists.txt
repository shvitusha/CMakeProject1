# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

# Говорим CMake что за проект.
project(args_parse_lab LANGUAGES CXX)

# Добавьте источник в исполняемый файл этого проекта.
#add_executable (CMakeProject1   "args_parse/ArgsParser.cpp" "args_parse/BoolArg.cpp" "args_parse/StringArg.cpp" "demo/main.cpp" "args_parse/IntArg.cpp")

# Назначаем нужный нам стандарт C++.
set(CMAKE_CXX_STANDARD 17)
# Указываем, что нужен именно этот стандарт, на предыдущие откатываться нельзя.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Запрещаем использование нестандартных расширений.
set(CMAKE_CXX_EXTENSIONS OFF)

# Определяем куда будут скидываться результаты компиляции.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
if (MSVC)
    # Строгое следование стандарту.
    add_compile_options(/permissive-)
    # Повышаем уровень предупреждений.
    add_compile_options(/W3)
    # И исходники в UTF-8, и строки в результирующем файле в UTF-8.
    add_compile_options(/utf-8)
endif()

# Подключаем подпроекты.
add_subdirectory(args_parse)
add_subdirectory(demo)
