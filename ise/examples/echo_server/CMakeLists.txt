add_executable(echo_server
  echo_server.cpp
  client_msg.cpp
    inner_msg.cpp
  ./game_core/ConfigManager.cpp
  ./game_define/BaseType.h
  ./tools/CommonTools.h
  ./bass_class/Singleton.h
  ./game_core/GamePlayer.cpp
  ./game_core/GamePlayerManager.cpp
  )

target_link_libraries(echo_server ise ise_utils_json  ise_dbi_mysql)

