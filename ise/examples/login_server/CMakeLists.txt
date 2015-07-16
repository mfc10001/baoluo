add_executable(login_server
  login_server.cpp
  )

target_link_libraries(login_server ise ise_utils_json  ise_dbi_mysql)
