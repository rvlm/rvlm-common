add_custom_target(RvlmCore SOURCES
    include/rvlm/core/NonAssignable.hh
    include/rvlm/core/SolidArray3d.hh
    include/rvlm/core/Math.hh
    include/rvlm/core/Constants.hh)

install(
    DIRECTORY include
    DESTINATION .
    PATTERN *.hh)
