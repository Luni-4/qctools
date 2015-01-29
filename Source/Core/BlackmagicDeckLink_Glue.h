/*  Copyright (c) BAVC. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license that can
 *  be found in the License.html file in the root of the source tree.
 */

//---------------------------------------------------------------------------
#ifndef BlackmagicDeckLink_Glue_H
#define BlackmagicDeckLink_Glue_H

//---------------------------------------------------------------------------
#if !defined(BLACKMAGICDECKLINK_YES) && !defined(BLACKMAGICDECKLINK_NO)
    #define BLACKMAGICDECKLINK_YES //Default compilation is YES
#endif
//---------------------------------------------------------------------------

#include <string>
#include <vector>

class FFmpeg_Glue;

class BlackmagicDeckLink_Glue
{
public:
    BlackmagicDeckLink_Glue(size_t CardPos);
    ~BlackmagicDeckLink_Glue();

    void                        Start();
    void                        Pause();
    bool                        Stop();
    
    int                         Width_Get();
    int                         Height_Get();

    int                         CurrentTimecode();

    FFmpeg_Glue*                Glue;
    int                         TC_in;
    int                         TC_out;

    enum status
    {
        connecting,
        connected,
        seeking,
        capturing,
        captured,
        aborting,
        aborted,
    };
    status                      Status;

    static std::vector<std::string> CardsList();

private:
    void*                       Handle;
};


//---------------------------------------------------------------------------
// Helpers

#include <cmath>

// convert a BCD timecode to a frame count (does not take into account drop frame timecodes...)
#define GET_FRAME_COUNT(result, tc_bcd, timeScale, frameDuration)    {\
                        (result) = 0;\
                        (result) += (((int)((tc_bcd) >> 28) & 0x0F)*10 + ((int)((tc_bcd) >> 24) & 0x0F))*60;\
                        (result) += ((int)((tc_bcd) >> 20) & 0x0F)*10 + ((int)((tc_bcd) >> 16) & 0x0F);\
                        (result) *= 60;\
                        (result) += ((int)((tc_bcd) >> 12) & 0x0F)*10 + ((int)((tc_bcd) >> 8) & 0x0F);\
                        (result) *= std::ceil(double((timeScale))/(frameDuration));\
                        (result) += ((int)((tc_bcd) >> 4) & 0x0F)*10 + ((int)((tc_bcd) & 0x0F));\
                        }

#endif // BlackmagicDeckLink_Glue_H