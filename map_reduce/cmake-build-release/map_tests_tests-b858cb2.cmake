add_test( [==[Map stl works OK]==] /home/mats/embe/patterns/map/cmake-build-release/map_tests [==[Map stl works OK]==])
set_tests_properties( [==[Map stl works OK]==] PROPERTIES WORKING_DIRECTORY /home/mats/embe/patterns/map/cmake-build-release)
add_test( [==[Map stl parallel works OK]==] /home/mats/embe/patterns/map/cmake-build-release/map_tests [==[Map stl parallel works OK]==])
set_tests_properties( [==[Map stl parallel works OK]==] PROPERTIES WORKING_DIRECTORY /home/mats/embe/patterns/map/cmake-build-release)
add_test( [==[Map parallel stl works OK]==] /home/mats/embe/patterns/map/cmake-build-release/map_tests [==[Map parallel stl works OK]==])
set_tests_properties( [==[Map parallel stl works OK]==] PROPERTIES WORKING_DIRECTORY /home/mats/embe/patterns/map/cmake-build-release)
add_test( [==[Map 2 works OK]==] /home/mats/embe/patterns/map/cmake-build-release/map_tests [==[Map 2 works OK]==])
set_tests_properties( [==[Map 2 works OK]==] PROPERTIES WORKING_DIRECTORY /home/mats/embe/patterns/map/cmake-build-release)
add_test( [==[Map threads works OK]==] /home/mats/embe/patterns/map/cmake-build-release/map_tests [==[Map threads works OK]==])
set_tests_properties( [==[Map threads works OK]==] PROPERTIES WORKING_DIRECTORY /home/mats/embe/patterns/map/cmake-build-release)
add_test( [==[Map 3 works OK]==] /home/mats/embe/patterns/map/cmake-build-release/map_tests [==[Map 3 works OK]==])
set_tests_properties( [==[Map 3 works OK]==] PROPERTIES WORKING_DIRECTORY /home/mats/embe/patterns/map/cmake-build-release)
add_test( [==[TBB Map works OK]==] /home/mats/embe/patterns/map/cmake-build-release/map_tests [==[TBB Map works OK]==])
set_tests_properties( [==[TBB Map works OK]==] PROPERTIES WORKING_DIRECTORY /home/mats/embe/patterns/map/cmake-build-release)
add_test( [==[Time maps]==] /home/mats/embe/patterns/map/cmake-build-release/map_tests [==[Time maps]==])
set_tests_properties( [==[Time maps]==] PROPERTIES WORKING_DIRECTORY /home/mats/embe/patterns/map/cmake-build-release)
set( map_tests_TESTS [==[Map stl works OK]==] [==[Map stl parallel works OK]==] [==[Map parallel stl works OK]==] [==[Map 2 works OK]==] [==[Map threads works OK]==] [==[Map 3 works OK]==] [==[TBB Map works OK]==] [==[Time maps]==])
