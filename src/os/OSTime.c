/* Originally from RB3 and OGWS*/
#include <revolution/OS.h>

#define USEC_MAX 1000
#define MSEC_MAX 1000
#define MONTH_MAX 12
#define WEEK_DAY_MAX 7
#define YEAR_DAY_MAX 365

#define SECS_IN_MIN 60
#define SECS_IN_HOUR (SECS_IN_MIN * 60)
#define SECS_IN_DAY (SECS_IN_HOUR * 24)
#define SECS_IN_YEAR (SECS_IN_DAY * 365)

#define BIAS 0xB2575

// End of each month in standard year
static s32 YearDays[MONTH_MAX] = {0,   31,  59,  90,  120, 151,
                                  181, 212, 243, 273, 304, 334};
// End of each month in leap year
static s32 LeapYearDays[MONTH_MAX] = {0,   31,  60,  91,  121, 152,
                                      182, 213, 244, 274, 305, 335};

asm s64 OSGetTime(void) {
    // clang-format off
    #ifdef __MWERKS__
    nofralloc

_start:
    mftbu r3
    mftb r4

    // Check for possible carry from TBL to TBU
    mftbu r5
    cmpw r3, r5
    bne OSGetTime

    blr
    #endif
    // clang-format on
}

asm s32 OSGetTick(void){
    // clang-format off
    #ifdef __MWERKS__
    nofralloc

    mftb r3
    blr
    #endif
    // clang-format on
}



s64 __OSGetSystemTime(void) {
    BOOL enabled = OSDisableInterrupts();
    s64 time = OSGetTime() + OS_SYSTEM_TIME;
    OSRestoreInterrupts(enabled);
    return time;
}

s64 __OSTimeToSystemTime(s64 time) {
    BOOL enabled = OSDisableInterrupts();
    s64 sysTime = OS_SYSTEM_TIME + time;
    OSRestoreInterrupts(enabled);
    return sysTime;
}



inline static BOOL IsLeapYear(s32 year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

inline static s32 GetYearDays(s32 year, s32 mon) {
    return (IsLeapYear(year) ? LeapYearDays : YearDays)[mon];
}

 inline static s32 GetLeapDays(s32 year) {
    if (year < 1) {
        return 0;
    }
    return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

inline static void GetDates(s32 days, OSCalendarTime* cal) {
    s32 year;
    s32 totalDays;
    s32* p_days;
    s32 month;

    cal->week_day = (days + 6) % WEEK_DAY_MAX;

    // WTF??
    for (year = days / YEAR_DAY_MAX;
         days < (totalDays = year * YEAR_DAY_MAX + GetLeapDays(year)); year--) {
        ;
    }
    days -= totalDays;
    cal->year = year;
    cal->year_day = days;

    p_days = IsLeapYear(year) ? LeapYearDays : YearDays;
    for (month = MONTH_MAX; days < p_days[--month];) {
        ;
    }
    cal->month = month;
    cal->month_day = days - p_days[month] + 1;
}

void OSTicksToCalendarTime(s64 ticks, OSCalendarTime* cal) {
    s32 days, secs;
    s64 d;

    d = ticks % OSSecondsToTicks(1);
    if (d < 0) {
        d += OSSecondsToTicks(1);
    }

    cal->usec = OSTicksToMicroseconds(d) % USEC_MAX;
    cal->msec = OSTicksToMilliseconds(d) % MSEC_MAX;
    ticks -= d;

    days = (OSTicksToSeconds(ticks) / SECS_IN_DAY) + BIAS;
    secs = OSTicksToSeconds(ticks) % SECS_IN_DAY;
    if (secs < 0) {
        days -= 1;
        secs += SECS_IN_DAY;
    }

    GetDates(days, cal);
    cal->hour = secs / 60 / 60;
    cal->min = secs / 60 % 60;
    cal->sec = secs % 60;
}
