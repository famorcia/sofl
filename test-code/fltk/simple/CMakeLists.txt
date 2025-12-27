add_executable(simple  main.cpp )
#message(FATAL_ERROR ${Coin_LIBRARIES})
target_link_libraries(simple ${fltk_LIBRARIES} GL)