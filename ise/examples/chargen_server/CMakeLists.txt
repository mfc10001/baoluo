add_executable(login_server
  login.cpp
  )

target_link_libraries(chargen_server ise ise_utils_json  ise_dbi_mysql)
