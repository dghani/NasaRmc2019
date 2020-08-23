/*
 * Shared codes and for querying status from the control system
 * */
#ifndef CONTROL_CODE_H
#define CONTROL_CODE_H

#include <cstdint>

namespace tfr_utilities
{
    namespace JointAngle
    {
        //NOTES must match up with constants in model
        static const float ARM_TURNTABLE_MAX = 6;
        static const float ARM_TURNTABLE_MIN = -6;
        static const float ARM_LOWER_MAX = 5;
        static const float ARM_LOWER_MIN = 0;
        static const float ARM_UPPER_MAX = 5;
        static const float ARM_UPPER_MIN = 0;
        static const float ARM_SCOOP_MAX = 3;
        static const float ARM_SCOOP_MIN = 0;
        static const float BIN_MAX = 5;
        static const float BIN_MIN = 0;
    }

}
#endif
