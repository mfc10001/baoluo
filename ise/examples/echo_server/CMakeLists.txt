add_executable(echo_server
  echo_server.cpp
  ./game_core/ConfigManager.cpp
  ./game_define/BaseType.h
  ./tools/CommonTools.h
  ./bass_class/Singleton.h
  )

target_link_libraries(echo_server ise ise_utils_json)

