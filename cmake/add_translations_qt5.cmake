find_package(Qt5LinguistTools REQUIRED)

include(CMakeParseArguments)

function(add_translations_qt5)
    if(Qt5_LUPDATE_EXECUTABLE)
        set(options ALL VERBOSE)
        set(oneValueArgs TARGET)
        set(multiValueArgs TS_FILES SOURCES LUPDATE_ARGS)
        cmake_parse_arguments("" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

        set(A_ARGS)
        if(NOT _VERBOSE)
            set(A_ARGS -silent)
        endif()

        set(A_ALL)
        if(_ALL)
            set(A_ALL ALL)
        endif()

        if(NOT _TARGET)
            set(_TARGET translations)
        endif()

        if(NOT _SOURCES)
            list(APPEND _SOURCES ${CMAKE_CURRENT_SOURCE_DIR})
            list(APPEND _LUPDATE_ARGS -recursive)
            list(REMOVE_DUPLICATES _LUPDATE_ARGS)
        endif()

        set(_abs_ts_files)
        foreach(_file ${_TS_FILES})
            get_filename_component(_abs_file ${_file} ABSOLUTE)
            get_filename_component(_file_we ${_file} NAME_WE)
            set(_output_file ${_OUTPUT_DIR}/${_file_we}.qm)
            list(APPEND _abs_ts_files ${_abs_file})
        endforeach()

        add_custom_target(
            ${_TARGET} ${A_ALL}
            COMMAND ${Qt5_LUPDATE_EXECUTABLE} ${A_ARGS} ${_LUPDATE_ARGS} ${_SOURCES} -ts ${_abs_ts_files}
            COMMENT "Updating Qt translations files"
        )

        if(Qt5_LRELEASE_EXECUTABLE)
            add_custom_target(
                ${_TARGET}_compile ${A_ALL}
                COMMAND ${Qt5_LRELEASE_EXECUTABLE} ${A_ARGS} ${_abs_ts_files}
                DEPENDS ${_TARGET}
                COMMENT "Compilation Qt translations files"
            )
        else()
            message(WARNING "lrelease not found. Target for lrelease not created.")
        endif()
    else()
        message(WARNING "lupdate not found. Target for lupdate not created.")
    endif()
endfunction()

