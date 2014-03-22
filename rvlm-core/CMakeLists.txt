add_custom_target(RvlmCore SOURCES
    include/rvlm/core/SolidArray3d.hh)

install(
    DIRECTORY include
    DESTINATION .
    PATTERN *.hh)
