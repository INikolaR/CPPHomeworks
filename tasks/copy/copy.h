#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    for (U it = src_begin; it != src_end; ++it) {
        *dest = *it;
        ++dest;
    }
    return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    for (U it = src_end; it != src_begin;) {
        --it;
        --dest;
        *dest = *it;
    }
    return dest;
}
