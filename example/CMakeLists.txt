add_subdirectory(regression)
add_subdirectory(density)

add_custom_target(example DEPENDS
  ex-regression
  ex-density
  )
