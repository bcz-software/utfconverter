#if !defined(UTFUTILS_H)
#   define UTFUTILS_H

#include "utf-utils-docs.hpp"

/**
 * @file utf_utils.hpp
 * @author bub1ick (Konstantin Smirnov)
 * @author Relisted (Fedor Sheparnev)
 * @brief The main header file for UTF-* string support.
 * @version 0.1
 * @date 2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */

// Standard library
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

#if __cplusplus < 202002L // < c++20
    /**
     * @brief Typedef for char8_t type. Used if and only if C++ standard is less than C++20
     */
    using char8_t = unsigned char;
#endif

//----------------------------------------------------INTERFACE----------------------------------------------------//

/**
 * @namespace utf
 * @brief This is the main namespace that contains everything related to utf-utils library.
 */
namespace utf {
    /**
     * @namespace utf::conversion
     * @brief This namespace contains conversion functions.
     */
    namespace conversion {
        /**
         * @brief Defines return values for conversion functions.
         * @remark Refer to conversion functions' respected documentation for info on #status_e::non_standard_encoding value.
         */
        enum class status_e : int8_t {
            trailing_without_leading = -3, /**< The byte says it is trailing, but doesn't have a leading byte.*/
            character_cut_off = -2, /**< The first byte says it has trailing one/-s, but is, in fact, last in the string.*/
            non_standard_encoding = -1, /**< The encoding is not standard-compliant. */
            undefined_error = 0, /**< There was some error during conversion. */
            success = 1 /**< Everything went smoothly. */
        };

        /**
         * @addtogroup conv_funcs Conversion Functions
         * Functions used to convert between Unicode encodings.
         * @{
         */

        /**
         * @brief This function converts UTF-8 string to UTF-16 string.
         * 
         * @param[in] utf8_sv const reference to a string view representing UTF-8 string.
         * @param[out] utf16_s reference to a string which will hold converted string.
         * @param[in] comply_with_standard should the conversion function comply with Unicode standard. Defaults to @c false.  Refer to "Remarks" for details.
         * @return status specified by #status_e enum.
         * @remarks
         * Judging by this <a href="https://en.wikipedia.org/wiki/UTF-16#U+D800_to_U+DFFF">Wikipedia article</a> the standard does not allow
         * usage of characters with code point from @c U+D800 to @c U+DFFF. Still, as noted by the aforementioned Wikipedia article you @a can
         * convert "characters" in this range, though it is not recommended. By default the conversion is not strict. If you opt in to enable it
         * you also must be able to handle #status_e::non_standard_encoding return value separately.
         */
        status_e utf8_to_utf16(const std::basic_string_view<char8_t>& utf8_sv, std::basic_string<char16_t>& utf16_s, bool comply_with_standard);
        /**
         * @brief This function converts UTF-8 string to UTF-32 string.
         * 
         * @param[in] utf8_sv const reference to a string view representing UTF-8 string.
         * @param[out] utf32_s reference to a string which will hold converted string.
         * @param[in] comply_with_standard should the conversion function comply with Unicode standard. Defaults to @c false.  Refer to "Remarks" for details.
         * @return status specified by #status_e enum.
         * @remarks
         * Judging by this <a href="https://en.wikipedia.org/wiki/UTF-16#U+D800_to_U+DFFF">Wikipedia article</a> the standard does not allow
         * usage of characters with code point from @c U+D800 to @c U+DFFF. Still, as noted by the aforementioned Wikipedia article you @a can
         * convert "characters" in this range, though it is not recommended. By default the conversion is not strict. If you opt in to enable it
         * you also must be able to handle #status_e::non_standard_encoding return value separately.
         */
        status_e utf8_to_utf32(const std::basic_string_view<char8_t>& utf8_sv, std::basic_string<char32_t>& utf32_s, bool comply_with_standard);

        /**
         * @brief This function converts UTF-16 string to UTF-8 string.
         * 
         * @param[in] utf16_sv const reference to a string view representing UTF-16 string.
         * @param[out] utf8_s reference to a string which will hold converted string.
         * @param[in] comply_with_standard should the conversion function comply with Unicode standard. Defaults to @c false.  Refer to "Remarks" for details.
         * @return status specified by #status_e enum.
         * @remarks
         * Judging by this <a href="https://en.wikipedia.org/wiki/UTF-16#U+D800_to_U+DFFF">Wikipedia article</a> the standard does not allow
         * usage of characters with code point from @c U+D800 to @c U+DFFF. Still, as noted by the aforementioned Wikipedia article you @a can
         * convert "characters" in this range, though it is not recommended. By default the conversion is not strict. If you opt in to enable it
         * you also must be able to handle #status_e::non_standard_encoding return value separately.
         */
        status_e utf16_to_utf8(const std::basic_string_view<char16_t>& utf16_sv, std::basic_string<char8_t>& utf8_s, bool comply_with_standard);

        /**
         * @brief This function converts UTF-16 string to UTF-32 string.
         * 
         * @param[in] utf16_sv const reference to a string view representing UTF-16 string.
         * @param[out] utf32_s reference to a string which will hold converted string.
         * @param[in] comply_with_standard should the conversion function comply with Unicode standard. Defaults to @c false.  Refer to "Remarks" for details.
         * @return status specified by #status_e enum.
         * @remarks
         * Judging by this <a href="https://en.wikipedia.org/wiki/UTF-16#U+D800_to_U+DFFF">Wikipedia article</a> the standard does not allow
         * usage of characters with code point from @c U+D800 to @c U+DFFF. Still, as noted by the aforementioned Wikipedia article you @a can
         * convert "characters" in this range, though it is not recommended. By default the conversion is not strict. If you opt in to enable it
         * you also must be able to handle #status_e::non_standard_encoding return value separately.
         */
        status_e utf16_to_utf32(const std::basic_string_view<char16_t>& utf16_sv, std::basic_string<char32_t>& utf32_s, bool comply_with_standard);

        /**
         * @brief This function converts UTF-32 string to UTF-8 string.
         * 
         * @param[in] utf32_sv const reference to a string view representing UTF-32 string.
         * @param[out] utf8_s reference to a string which will hold converted string.
         * @param[in] comply_with_standard should the conversion function comply with Unicode standard. Defaults to @c false.  Refer to "Remarks" for details.
         * @return status specified by #status_e enum.
         * @remarks
         * Judging by this <a href="https://en.wikipedia.org/wiki/UTF-16#U+D800_to_U+DFFF">Wikipedia article</a> the standard does not allow
         * usage of characters with code point from @c U+D800 to @c U+DFFF. Still, as noted by the aforementioned Wikipedia article you @a can
         * convert "characters" in this range, though it is not recommended. By default the conversion is not strict. If you opt in to enable it
         * you also must be able to handle #status_e::non_standard_encoding return value separately.
         */
        status_e utf32_to_utf8(const std::basic_string_view<char32_t>& utf32_sv, std::basic_string<char8_t>& utf8_s, bool comply_with_standard);
        /**
         * @brief This function converts UTF-32 string to UTF-8 string.
         * 
         * @param[in] utf32_sv const reference to a string view representing UTF-32 string.
         * @param[out] utf16_s reference to a string which will hold converted string.
         * @param[in] comply_with_standard should the conversion function comply with Unicode standard. Defaults to @c false.  Refer to "Remarks" for details.
         * @return status specified by #status_e enum.
         * @remarks
         * Judging by this <a href="https://en.wikipedia.org/wiki/UTF-16#U+D800_to_U+DFFF">Wikipedia article</a> the standard does not allow
         * usage of characters with code point from @c U+D800 to @c U+DFFF. Still, as noted by the aforementioned Wikipedia article you @a can
         * convert "characters" in this range, though it is not recommended. By default the conversion is not strict. If you opt in to enable it
         * you also must be able to handle #status_e::non_standard_encoding return value separately.
         */
        status_e utf32_to_utf16(const std::basic_string_view<char32_t>& utf32_sv, std::basic_string<char16_t>& utf16_s, bool comply_with_standard);

        /**
         * @}
         */

    } // namespace conversion
} // namespace utf

//--------------------------------------------------IMPLEMENTATION--------------------------------------------------//
#if defined IMPLEMENT_UTFUTILS

namespace utf {
    /**
     * @internal
     * @brief This namespace contains various constants.
     */
    namespace constants {
        /**
         * @internal
         * @addtogroup constants Constants
         * Constants that are needed for conversion.
         * @{
         */
        /**
         * @internal
         * @brief The 6 starting bits of "high" surrogate placed at the beggining of the two-byte boundary.
         * This is the representation of this value in binary: @c 1101_1000_0000_0000.
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF">Wikipedia article</a> about this value.
         */
        constexpr uint16_t high_surrogate_start       = 0xD800;
        /**
         * @internal
         * @brief The 6 starting bits of "high" surrogate placed at the end of a byte's boundary.
         * This is the representation of this value in binary: @c 0011_0110.
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF">Wikipedia article</a> about this value.
         */
        constexpr uint8_t  high_surrogate_marker      = 0xD800 >> 10;
        /**
         * @internal
         * @brief The 6 starting bits of "low" surrogate placed at the beggining of the two-byte boundary.
         * This is the representation of this value in binary: @c 1101_1100_0000_0000.
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF">Wikipedia article</a> about this value.
         */
        constexpr uint16_t low_surrogate_start        = 0xDC00;
        /**
         * @internal
         * @brief The 6 starting bits of "low" surrogate placed at the end of byte's boundary.
         * This is the representation of this value in binary: @c 0011_0111.
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF">Wikipedia article</a> about this value.
         */
        constexpr uint8_t  low_surrogate_marker       = 0xDC00 >> 10;
        /**
         * @internal
         * @brief Unicode "Supllementary Planes" (1 through 16) offset.
         * @details
         * See <a href="https://en.wikipedia.org/wiki/Plane_(Unicode)">Plane (Unicode) Wikipidia article</a>.
         */
        constexpr uint32_t supplementary_plane_offset = 0x10000;
        /**
         * @internal
         * @brief Code points up to and including this value can be fitted into 1 byte (UTF-8)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-8#Encoding">Wikipedia UTF-8#Encoding</a>.
         */
        constexpr uint8_t  one_byte_boundary          = 0x007F;
        /**
         * @internal
         * @brief Code points up to and including this value can be fitted into 2 bytes (UTF-8)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-8#Encoding">Wikipedia UTF-8#Encoding</a>.
         */
        constexpr uint16_t two_byte_boundary          = 0x07FF;
        /**
         * @internal
         * @brief Code points up to and including this value can be fitted into 3 bytes (UTF-8)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-8#Encoding">Wikipedia UTF-8#Encoding</a>.
         */
        constexpr uint16_t three_byte_boundary        = 0xFFFF;
        /**
         * @internal
         * @brief Code points up to and including this value can be fitted into 4 bytes (UTF-8)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-8#Encoding">Wikipedia UTF-8#Encoding</a>.
         */
        constexpr uint32_t four_byte_boundary         = 0x10FFFF;
        /**
         * @internal
         * @brief These 2 bits are the first in each consecutive byte after the leading one (UTF-8)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-8#Encoding">Wikipedia UTF-8#Encoding</a>.
         */
        constexpr uint8_t trailing_byte_marker        = 0b10;
        /**
         * @internal
         * @brief These 3 bits are the first in first byte in double byte character (UTF-8)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-8#Encoding">Wikipedia UTF-8#Encoding</a>.
         */
        constexpr uint8_t double_byte_marker          = 0b110;
        /**
         * @internal
         * @brief These 4 bits are the first in first byte in double byte character (UTF-8)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-8#Encoding">Wikipedia UTF-8#Encoding</a>.
         */
        constexpr uint8_t triple_byte_marker          = 0b1110;
        /**
         * @internal
         * @brief These 5 bits are the first in first byte in double byte character (UTF-8)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-8#Encoding">Wikipedia UTF-8#Encoding</a>.
         */
        constexpr uint8_t quadruple_byte_marker       = 0b11110;

        /**
         * @}
         */
    } // namespace constants

    /**
     * @internal
     * @addtogroup utils Utility
     * Utility.
     * @{
     */
    /**
     * @internal
     * @brief Checks if UTF-16 character can be first in double character pair
     * @param ch Character to check
     * @return true if character is the first in surrogate pair
     * @return false if character is not the first in surrogate pair
     * @details
     * See <a href="https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF">About surrogates</a>.
     */
    constexpr bool is_high_surrogate(const char16_t ch) {
        return constants::high_surrogate_marker == ch >> 10;
    }
    /**
     * @internal
     * @brief Checks if UTF-16 character can be second in double character pair
     * @param ch Character to check
     * @return true if character is the second in surrogate pair
     * @return false if character is not the first in surrogate pair
     * @details
     * See <a href="https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF">About surrogates</a>.
     */
    constexpr bool is_low_surrogate(const char16_t ch) {
        return constants::low_surrogate_marker == ch >> 10;
    }
    /**
     * @}
     */
}

using namespace utf;
using namespace utf::conversion;
using namespace utf::constants;

status_e utf::conversion::utf8_to_utf32(const std::basic_string_view<char8_t>& utf8_sv, std::basic_string<char32_t>& utf32_s, bool comply_with_standard = false) {
    std::basic_string<char32_t> code_points;

    size_t code_unit_count = utf8_sv.size();
    uint8_t bits_left = 0;
    uint8_t bytes_left = 0;
    for (size_t index = 0; index < code_unit_count; index++) {
        char8_t this_code_unit = utf8_sv[index];
        // if first bit is zero it's ANSI
        if (this_code_unit >> 7 == 0) {
            code_points.push_back(this_code_unit);

            continue;
        }
        // if first byte is "is trailing" for some reason
        if (this_code_unit >> 6 == trailing_byte_marker) {
            return status_e::trailing_without_leading;
        }
        // if first byte denotes double character
        if (this_code_unit >> 5 == double_byte_marker) {
            // get rid of markers
            uint16_t first_bits = static_cast<uint16_t>(this_code_unit << 6);

            // next byte
            if (++index >= code_unit_count) {
                return status_e::character_cut_off;
            }
            // ~next byte

            uint16_t last_bits = static_cast<uint16_t>((utf8_sv[index] << 2) >> 2);
            // create code point
            char16_t code_point = first_bits + last_bits;
            code_points.push_back(code_point);

            continue;
        }
        // if first byte denotes triple character
        if (this_code_unit >> 4 == triple_byte_marker) {
            // get rid of markers
            uint16_t first_bits = static_cast<uint16_t>(this_code_unit) << 12;

            // next byte
            if(++index >= code_unit_count) {
                return status_e::character_cut_off;
            }
            // ~next byte
            uint16_t middle_bits = static_cast<uint16_t>((utf8_sv[index] << 2) >> 2) << 6;

            // next byte
            if(++index >= code_unit_count) {
                return status_e::character_cut_off;
            }
            // ~next byte
            uint16_t last_bits = static_cast<uint16_t>((utf8_sv[index] << 2) >> 2);

            char16_t code_point = first_bits + middle_bits + last_bits;
            code_points.push_back(code_point);
            continue;
        }
        // if first byte denotes quadruple character
        if(this_code_unit >> 3 == quadruple_byte_marker) {
            uint32_t first_bits = this_code_unit << 18;

            // next byte
            if(++index >= code_unit_count) {
                return status_e::character_cut_off;
            }
            // ~next byte
            uint32_t second_bits = static_cast<uint32_t>((utf8_sv[index] << 2) >> 2) << 12;

            // next byte
            if(++index >= code_unit_count) {
                return status_e::character_cut_off;
            }
            // ~next byte
            uint32_t third_bits = static_cast<uint32_t>((utf8_sv[index] << 2) >> 2) << 6;

            // next byte
            if(++index >= code_unit_count) {
                return status_e::character_cut_off;
            }
            // ~next byte
            uint32_t last_bits = static_cast<uint32_t>((utf8_sv[index] << 2) >> 2);


            char32_t code_point = first_bits + second_bits + third_bits + last_bits;
            code_points.push_back(code_point);
            continue;
        }
    }




    return status_e::success;
}

status_e utf::conversion::utf16_to_utf8(const std::basic_string_view<char16_t>& utf16_sv, std::basic_string<char8_t>& utf8_s, bool comply_with_standard = false) {
    // Convert to UTF-32
    std::basic_string<char32_t> code_points;
    status_e status = utf16_to_utf32(utf16_sv, code_points, comply_with_standard);
    if (status < status_e::success) {
        return status;
    }
    // Convert to UTF-8
    std::basic_string<char8_t> result_string;
    status = utf32_to_utf8(code_points, result_string, comply_with_standard);
    if (status < status_e::success) {
        return status;
    }

    utf8_s = result_string;
    return status_e::success;
}

status_e utf::conversion::utf16_to_utf32(const std::basic_string_view<char16_t>& utf16_sv, std::basic_string<char32_t>& utf32_s, bool comply_with_standard = false) {
    // vector of UTF-32 characters (code points)
    std::basic_string<char32_t> code_points;

    bool was_double_character = false;
    for (auto character_it = utf16_sv.begin(); character_it < utf16_sv.end(); character_it++) {
        // skip this character, because we handled it last iteration
        if (was_double_character) {
            was_double_character = false;
            continue;
        }
        // get this character
        char16_t this_character = *character_it;

        // check if this character is the last one
        const bool exists_next_character = (character_it + 1) != utf16_sv.end();
        char16_t next_character;

        // get next character if there is one
        if (exists_next_character) {
            next_character = *(character_it + 1);
        }

        // if can be part of double character
        if (is_high_surrogate(this_character)) {
            // if there is no next character we add this as code point
            if (!exists_next_character) {
                if (!comply_with_standard) {
                    code_points.push_back(this_character);
                    continue;
                }
                return status_e::non_standard_encoding;
            }

            // if next character is not part of the double character we add this as code point
            if (!is_low_surrogate(next_character)) {
                if (!comply_with_standard) {
                    code_points.push_back(this_character);
                    continue;
                }
                return status_e::non_standard_encoding;
            }

            // it turned out we have a double character
            was_double_character = true;

            // do decoding "double UTF-16" -> UTF-32:
            // https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF
            char32_t high_code_point = (this_character - high_surrogate_start) << 10;
            char16_t low_code_point = next_character - low_surrogate_start;
            char32_t code_point = high_code_point + low_code_point + supplementary_plane_offset;
            code_points.push_back(code_point);

            continue;
        }

        // if not a double character add this as next code point
        code_points.push_back(this_character);
    }
    // return resulting string
    utf32_s =  code_points;
    return status_e::success;
}

status_e utf::conversion::utf32_to_utf8(const std::basic_string_view<char32_t>& utf32_sv, std::basic_string<char8_t>& utf8_s, bool comply_with_standard = false) {
    std::basic_string<char8_t> result;

    for (const char32_t this_code_point : utf32_sv) {
        if (this_code_point > four_byte_boundary) {
            return status_e::undefined_error;
        }
        if (this_code_point <= one_byte_boundary) {
            result.push_back(static_cast<char8_t>(this_code_point));
            continue;
        }
        if (this_code_point <= two_byte_boundary) {
            uint16_t cp_16        = static_cast<uint16_t>(this_code_point);

            uint8_t  first_5_bits =  cp_16 >>  6;
            uint8_t  last_6_bits  = (cp_16 << 10) >> 10;

            result.push_back((double_byte_marker << 5) + first_5_bits);
            result.push_back((trailing_byte_marker << 6) + last_6_bits);

            continue;
        }
        if (this_code_point <= three_byte_boundary) {
            uint16_t cp_16      = static_cast<uint16_t>(this_code_point);

            bool wrong_encoding = comply_with_standard           &&
                                  cp_16 < low_surrogate_start    &&
                                  cp_16 > high_surrogate_start;
            if (wrong_encoding) {
                    return status_e::non_standard_encoding;
            }

            uint8_t  first_4_bits  =  cp_16 >> 12;
            uint8_t  middle_6_bits = (cp_16 <<  4) >> 10;
            uint8_t  last_6_bits   = (cp_16 << 10) >> 10;

            result.push_back((triple_byte_marker   << 4) + first_4_bits);
            result.push_back((trailing_byte_marker << 6) + middle_6_bits);
            result.push_back((trailing_byte_marker << 6) + last_6_bits);

            continue;
        }
        if (this_code_point <= four_byte_boundary) {
            uint8_t first_3_bits  =  this_code_point >> 18;
            uint8_t second_6_bits = (this_code_point << 14) >> 26;
            uint8_t third_6_bits  = (this_code_point << 20) >> 26;
            uint8_t last_6_bits   = (this_code_point << 26) >> 26;

            result.push_back((quadruple_byte_marker << 5) + first_3_bits);
            result.push_back((trailing_byte_marker  << 6) + second_6_bits);
            result.push_back((trailing_byte_marker  << 6) + third_6_bits);
            result.push_back((trailing_byte_marker  << 6) + last_6_bits);

            continue;
        }
    }

    return status_e::success;
}


#endif // defined IMPLEMENT_UTFUTILS
#endif // !defined(UTFUTILS_H)