add_executable(hello_world
  hello_world.cpp
  server_msg.cpp
  ./game_define/Protocol.h
  )

target_link_libraries(hello_world ise ise_utils_json  ise_dbi_mysql)
