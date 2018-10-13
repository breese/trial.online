add_subdirectory(regression)

add_custom_target(example DEPENDS
  ex-regression
  )
