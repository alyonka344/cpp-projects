cmake_minimum_required(VERSION 3.22)
project(labwork_7_alyonka344)

set(CMAKE_CXX_STANDARD 20)

add_executable(labwork_7_alyonka344
        bin/main.cpp

        lib/HeaderParse.cpp
        lib/HeaderParse.h

        lib/BasicFrame.cpp
        lib/BasicFrame.h

        lib/TextFrame/TextFrame.cpp
        lib/TextFrame/TextFrame.h

        lib/FileParser.cpp
        lib/FileParser.h

        lib/FrameOfURL/URLFrames.cpp
        lib/FrameOfURL/URLFrames.h

        lib/COMM/COMM.cpp
        lib/COMM/COMM.h

        lib/UFID/UFID.cpp
        lib/UFID/UFID.h

        lib/USER/USER.cpp
        lib/USER/USER.h

        lib/USLT/USLT.cpp
        lib/USLT/USLT.h

        lib/ENCR/ENCR.cpp
        lib/ENCR/ENCR.h

        lib/GRID/GRID.cpp
        lib/GRID/GRID.h

        lib/LINK/LINK.cpp
        lib/LINK/LINK.h

        lib/OWNE/OWNE.cpp
        lib/OWNE/OWNE.h

        lib/PRIV/PRIV.cpp
        lib/PRIV/PRIV.h

        lib/PCNT/PCNT.cpp
        lib/PCNT/PCNT.h

        lib/POPM/POPM.cpp
        lib/POPM/POPM.h

        lib/POSS/POSS.cpp
        lib/POSS/POSS.h

        lib/SEEK/SEEK.cpp
        lib/SEEK/SEEK.h

        lib/COMR/COMR.cpp
        lib/COMR/COMR.h

        lib/RBUF/RBUF.cpp
        lib/RBUF/RBUF.h

        lib/ETCO/ETCO.cpp
        lib/ETCO/ETCO.h

        lib/SYLT/SYLT.cpp
        lib/SYLT/SYLT.h

        lib/GeneralFunctions.cpp
        lib/GeneralFunctions.h)
