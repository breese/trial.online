add_executable(ex-density-cumulative
  cumulative.cpp
  )
target_link_libraries(ex-density-cumulative trial-online)

add_executable(ex-density-window
  window.cpp
  )
target_link_libraries(ex-density-window trial-online)

add_executable(ex-density-interim
  interim.cpp
  )
target_link_libraries(ex-density-interim trial-online)

add_custom_target(ex-density DEPENDS
  ex-density-cumulative
  ex-density-window
  ex-density-interim
  )
