# Include paths.
include_directories(
	../include
)

# Test sources.
set (GTEST_SOURCES
	Ant_TEST.cc
	Doodlebug_TEST.cc
	CellMap_TEST.cc
	Environment_TEST.cc
	Cell_TEST.cc
	SimulationRunner_TEST.cc
)

cppcourse_build_tests(${GTEST_SOURCES})