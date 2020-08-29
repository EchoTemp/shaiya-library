#pragma once

/**
 * A quick function to insert "padding" in the structure - that is
 * unused bytes.
 */
#define CONCATENATE_DIRECT(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_DIRECT(s1, s2)
#define PAD(AMOUNT) std::array<char, AMOUNT> CONCATENATE(pad, __COUNTER__)