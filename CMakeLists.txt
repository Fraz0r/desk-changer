cmake_minimum_required (VERSION 2.6)
project (desk-changer)

# Set our version numbers
set (DESK_CHANGER_VERSION_MAJOR 0)
set (DESK_CHANGER_VERSION_MINOR 0)
set (DESK_CHANGER_VERSION_RELEASE 1)
set (DESK_CHANGER_VERSION "${DESK_CHANGER_VERSION_MAJOR}.${DESK_CHANGER_VERSION_MINOR}.${DESK_CHANGER_VERSION_RELEASE}")

# set our default options
option (ENABLE_DEBUG "Enable debugging features and compile flags" OFF)

# Configure the header file
configure_file (
	"${PROJECT_SOURCE_DIR}/includes/config.h.in"
	"${PROJECT_BINARY_DIR}/includes/config.h"
)

if (ENABLE_DEBUG)
	add_definitions (-g)
endif (ENABLE_DEBUG)

add_definitions (-Wall)
add_subdirectory (src)
