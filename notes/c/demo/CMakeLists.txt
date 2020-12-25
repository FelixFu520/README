cmake_minimum_required(VERSION 3.14)

PROJECT(NEWHELLO)

# add lib
ADD_SUBDIRECTORY(lib)

# add source
ADD_SUBDIRECTORY(src)


# install pkg
INSTALL(TARGETS main_s main_a hello
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib
) 
