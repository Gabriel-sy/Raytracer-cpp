# CMakeList.txt: projeto de CMake para Raytracer2, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Raytracer2")

# Adicione a origem ao executável deste projeto.
add_executable (Raytracer2 "Raytracer2.cpp" "Raytracer2.h" "vec3.h" "color.h" "ray.h")

add_custom_command(TARGET Raytracer2
                   POST_BUILD
                   COMMAND Raytracer2 > output.ppm
                   COMMENT "Generating PPM image...")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Raytracer2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
