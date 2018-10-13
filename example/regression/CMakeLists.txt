add_executable(ex-regression
  cumulative.cpp
  )
target_link_libraries(ex-regression trial-online)

add_executable(ex-regression-window
  window.cpp
  )
target_link_libraries(ex-regression-window trial-online)
