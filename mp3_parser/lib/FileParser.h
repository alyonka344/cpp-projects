#include "COMM/COMM.h"
#include "COMR/COMR.h"
#include "ENCR/ENCR.h"
#include "ETCO/ETCO.h"
#include "FrameOfURL/URLFrames.h"
#include "GRID/GRID.h"
#include "HeaderParse.h"
#include "LINK/LINK.h"
#include "OWNE/OWNE.h"
#include "PCNT/PCNT.h"
#include "POPM/POPM.h"
#include "POSS/POSS.h"
#include "PRIV/PRIV.h"
#include "RBUF/RBUF.h"
#include "SEEK/SEEK.h"
#include "SYLT/SYLT.h"
#include "TextFrame/TextFrame.h"
#include "UFID/UFID.h"
#include "USER/USER.h"
#include "USLT/USLT.h"

#include <filesystem>


class Parser {
public:
    void Parse(int argc, char** argv);

private:
    std::filesystem::path path_to_file_;

    void ParseFrames();
};
