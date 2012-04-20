cmake_minimum_required (VERSION 2.6)
project (desk-changer)

# Set our version numbers
set (DESK_CHANGER_VERSION_MAJOR 0)
set (DESK_CHANGER_VERSION_MINOR 0)
set (DESK_CHANGER_VERSION_RELEASE 1)
set (DESK_CHANGER_VERSION_BUILD "-dev")

# Configure the header file
configure_file (
	"${PROJECT_SOURCE_DIR}/includes/desk-changer.h.in"
	"${PROJECT_BINARY_DIR}/includes/desk-changer.h"
)

# Now add the include path
include_directories (
	"${PROEJECT_BINARY_DIR}/includes/"
)

add_subdirectory (src)
