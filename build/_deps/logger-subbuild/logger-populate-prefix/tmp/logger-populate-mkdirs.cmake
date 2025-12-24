# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-src")
  file(MAKE_DIRECTORY "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-build"
  "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-subbuild/logger-populate-prefix"
  "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-subbuild/logger-populate-prefix/tmp"
  "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-subbuild/logger-populate-prefix/src/logger-populate-stamp"
  "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-subbuild/logger-populate-prefix/src"
  "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-subbuild/logger-populate-prefix/src/logger-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-subbuild/logger-populate-prefix/src/logger-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Student/Desktop/karagodina/vsa/build/_deps/logger-subbuild/logger-populate-prefix/src/logger-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
