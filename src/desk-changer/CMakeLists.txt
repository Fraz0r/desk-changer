# Now add the include path
include_directories (
	${PROJECT_BINARY_DIR}/includes/
	${GTK3_INCLUDE_DIRS}
)

link_directories (
	${GTK3_LIBRARY_DIRS}
)

add_executable (desk-changer desk-changer.c)
add_definitions (${GTK3_CFLAGS_OTHER})
target_link_libraries (desk-changer ${GTK3_LIBRARIES})
