add_executable(main_server
   main_server.cpp
   client_msg.cpp
   inner_msg.cpp
  ./game_core/ConfigManager.cpp
  ./game_define/BaseType.h
  ./game_define/Protocol.h
  ./game_define/ItemBase.h
  ./game_define/EntryBase.h
  ./bass_class/Entry.h
   ./bass_class/Singleton.h
  ./tools/CommonTools.h
  ./bass_class/Singleton.h
  ./game_core/GamePlayerManager.cpp
  ./game_core/GameItemManager.cpp
  ./game_core/GamePackage.cpp
  ./game_core/GameItem.cpp
  ./game_core/GameItemManager.cpp
  ./game_core/GamePackage.cpp
  ./game_core/GameItem.cpp
  ./game_core/GamePackageManager.cpp
   ./game_core/GameEquipImprove.cpp
  ./game_core/GamePlayer.cpp
  ./game_core/StoreManager.cpp

  )

target_link_libraries(main_server ise ise_utils_json  ise_dbi_mysql ise_utils_cipher)

