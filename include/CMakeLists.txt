add_library(Willog INTERFACE ProgBar.hpp Willog.hpp)

set_target_properties(Willog INTERFACE LINKER_LANGUAGE CXX)
#target_sources(Willog)
#target_include_directories(Willog STATIC ${PROJECT_SOURCE_DIR})