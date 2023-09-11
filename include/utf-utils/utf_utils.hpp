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
         * @brief The last 16 bit code unit that can be the low part of a surrogate pair.
         * @details
         * See <a href="https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF">Wikipedia article</a> about this value.
         */
        constexpr uint16_t low_surrogate_end          = 0xDFFF;
        /**
         * @internal
         * @brief Unicode "Supllementary Planes" (1 through 16) offset.
         * @details
         * See <a href="https://en.wikipedia.org/wiki/Plane_(Unicode)">Plane (Unicode) Wikipidia article</a>.
         */
        constexpr uint32_t supplementary_plane_offset = 0x10000;
        /**
         * @internal
         * @brief Unicode "Supllementary Planes" (1 through 16) end. Last code unit is -1 from this constant.
         * @details
         * See <a href="https://en.wikipedia.org/wiki/Plane_(Unicode)">Plane (Unicode) Wikipidia article</a>.
         */
        constexpr uint32_t supplementary_plane_end = 0x110000;
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
         * @internal
         * @brief Byte Order Mark (Big-Endian)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/Byte_order_mark">About BOM</a>.
        */
       constexpr uint16_t byte_order_mark             = 0xFEFF;
        /**
         * @internal
         * @brief Byte Order Mark (Little-Endian)
         * @details
         * See <a href="https://en.wikipedia.org/wiki/Byte_order_mark">About BOM</a>.
        */
       constexpr uint16_t reversed_byte_order_mark     = 0xFFFE;
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
     * @brief Defines return value of functions related to endiannes.
    */
    enum class endianness_e : uint8_t {
        unspecified   = 0, /**< The text string doesn't have a BOM.*/
        big_endian    = 1, /**< The text string is big-endian.*/
        little_endian = 2 /**< The text string is little-endian*/
    };

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
     * @internal
     * @brief Checks if UTF-32 character/code point is in right boundaries
     * @param ch Character to check
     * @return true if character is in bounds
     * @return false if character is out of bounds.
     * @details
     * See <a href="https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF">About surrogates</a>.
     */
    constexpr bool is_correct_code_point(const char32_t ch) {
        return ch < constants::high_surrogate_start &&
               ch > constants::low_surrogate_end;
    }
    /**
     * @internal
     * @brief Checks if UTF-8 text has Byte Order Mark
     * @param ch Array of 3 first UTF-8 code units
     * @return true if there is BOM
     * @return false if there is no BOM
     * @details
     * See <a href="https://en.wikipedia.org/wiki/Byte_order_mark">About BOM</a>.
     */
    constexpr bool utf8_has_bom(const char8_t* code_units) {
        return code_units[0] == 0xEF &&
               code_units[1] == 0xBB &&
               code_units[2] == 0xBF;
    }
    constexpr endianness_e utf16_bom(const char16_t ch) {
        switch (ch) {
            case constants::byte_order_mark:
                return endianness_e::big_endian;
            case constants::reversed_byte_order_mark:
                return endianness_e::little_endian;
            default:
                return endianness_e::unspecified;
        }
    }
    constexpr char16_t utf16_reverse_endianness(const char16_t ch) {
        int8_t first_byte  = ch >> 8;
        int8_t second_byte = ch & 0xFF;
        return (second_byte << 8) + first_byte;
    }
    constexpr endianness_e utf32_bom(const char32_t ch) {
        int16_t first_word  = (ch >> 16) & 0xFFFF;
        int16_t second_word =  ch        & 0xFFFF;

        if (first_word == 0 && second_word == constants::byte_order_mark) {
            return endianness_e::big_endian;
        }
        if (first_word == constants::reversed_byte_order_mark && second_word == 0) {
            return endianness_e::little_endian;
        }
        return endianness_e::unspecified;
    }
    constexpr char32_t utf32_reverse_endianness(const char32_t ch) {
        int8_t first_byte  =  ch >> 24;
        int8_t second_byte = (ch >> 16) & 0xFF;
        int8_t third_byte  = (ch >> 8)  & 0xFF;
        int8_t fourth_byte =  ch        & 0xFF;
        return (fourth_byte << 24) + (third_byte << 16) + (second_byte << 8) + first_byte;
    }

    /**
     * @}
     */
}

using namespace utf;
using namespace utf::conversion;
using namespace utf::constants;

status_e utf::conversion::utf8_to_utf16(const std::basic_string_view<char8_t>& utf8_sv, std::basic_string<char16_t>& utf16_s, bool comply_with_standard = false) {
    // Convert to UTF-32
    std::basic_string<char32_t> code_points;
    status_e status = utf8_to_utf32(utf8_sv, code_points, comply_with_standard);
    if (status < status_e::success) {
        return status;
    }
    // Convert to UTF-16
    std::basic_string<char16_t> result_string;
    status = utf32_to_utf16(code_points, result_string, comply_with_standard);
    if (status < status_e::success) {
        return status;
    }
    utf16_s = result_string;
    return status_e::success;
}

status_e utf::conversion::utf8_to_utf32(const std::basic_string_view<char8_t>& utf8_sv, std::basic_string<char32_t>& utf32_s, bool comply_with_standard = false) {
    std::basic_string<char32_t> code_points;
    bool has_bom = false;
    size_t code_unit_count = utf8_sv.size();
    if (code_unit_count >= 3) {
        has_bom = utf8_has_bom(utf8_sv.data());
        if (has_bom) {
            utf32_s.push_back(byte_order_mark);
        }
    }
    // if we have bom, we start from the 4th character in the string as we've handled BOM earlier.
    for (size_t index = has_bom ? 3 : 0; index < code_unit_count; index++) {
        char8_t this_code_unit = utf8_sv[index];
        // if first bit is zero it's ANSI
        if (this_code_unit >> 7 == 0) {
            utf32_s.push_back(this_code_unit);

            continue;
        }
        // if first byte is "is trailing" for some reason
        if (this_code_unit >> 6 == trailing_byte_marker) {
            utf32_s.clear();
            return status_e::trailing_without_leading;
        }
        // if first byte denotes double character
        if (this_code_unit >> 5 == double_byte_marker) {
            // get rid of markers
            uint16_t first_bits = static_cast<uint16_t>(this_code_unit << 6);

            // next byte
            if (++index >= code_unit_count) {
                utf32_s.clear();
                return status_e::character_cut_off;
            }
            // ~next byte

            uint16_t last_bits = static_cast<uint16_t>(utf8_sv[index] & 0x3F);
            // create code point
            char16_t code_point = first_bits + last_bits;
            utf32_s.push_back(code_point);

            continue;
        }
        // if first byte denotes triple character
        if (this_code_unit >> 4 == triple_byte_marker) {
            // get rid of markers
            uint16_t first_bits = static_cast<uint16_t>(this_code_unit) << 12;

            // next byte
            if(++index >= code_unit_count) {
                utf32_s.clear();
                return status_e::character_cut_off;
            }
            // ~next byte
            uint16_t middle_bits = static_cast<uint16_t>(utf8_sv[index] & 0x3F) << 6;

            // next byte
            if(++index >= code_unit_count) {
                utf32_s.clear();
                return status_e::character_cut_off;
            }
            // ~next byte
            uint16_t last_bits = static_cast<uint16_t>(utf8_sv[index] & 0x3F);

            char16_t code_point = first_bits + middle_bits + last_bits;
            utf32_s.push_back(code_point);
            continue;
        }
        // if first byte denotes quadruple character
        if(this_code_unit >> 3 == quadruple_byte_marker) {
            uint32_t first_bits = this_code_unit << 18;

            // next byte
            if(++index >= code_unit_count) {
                utf32_s.clear();
                return status_e::character_cut_off;
            }
            // ~next byte
            uint32_t second_bits = static_cast<uint32_t>(utf8_sv[index] & 0x3F) << 12;

            // next byte
            if(++index >= code_unit_count) {
                utf32_s.clear();
                return status_e::character_cut_off;
            }
            // ~next byte
            uint32_t third_bits = static_cast<uint32_t>(utf8_sv[index] & 0x3F) << 6;

            // next byte
            if(++index >= code_unit_count) {
                utf32_s.clear();
                return status_e::character_cut_off;
            }
            // ~next byte
            uint32_t last_bits = static_cast<uint32_t>(utf8_sv[index] & 0x3F);


            char32_t code_point = first_bits + second_bits + third_bits + last_bits;
            utf32_s.push_back(code_point);
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
    const bool reverse = utf16_bom(utf16_sv[0]) == endianness_e::little_endian;

    bool was_double_character = false;
    for (auto character_it = utf16_sv.begin(); character_it != utf16_sv.end(); character_it++) {
        // skip this character, because we handled it last iteration
        if (was_double_character) {
            was_double_character = false;
            continue;
        }
        // get this character
        const char16_t this_character = reverse ? utf16_reverse_endianness(*character_it) : *character_it;

        // get next character iterator
        const auto next_character_it = character_it + 1;

        // check if this character is the last one
        const bool exists_next_character = next_character_it != utf16_sv.end();
        char16_t next_character;

        // get next character if there is one
        if (exists_next_character) {
            next_character = reverse ? utf16_reverse_endianness(*next_character_it) : *next_character_it;
        }

        // if can be part of double character
        if (is_high_surrogate(this_character)) {
            // if there is no next character we add this as code point
            if (!exists_next_character) {
                if (comply_with_standard) {
                    utf32_s.clear();
                    return status_e::non_standard_encoding;
                }
                utf32_s.push_back(this_character);
                continue;
            }

            // if next character is not part of the double character we add this as code point
            if (!is_low_surrogate(next_character)) {
                if (comply_with_standard) {
                    utf32_s.clear();
                    return status_e::non_standard_encoding;
                }
                utf32_s.push_back(this_character);
                continue;
            }

            // it turned out we have a double character
            was_double_character = true;

            // do decoding "double UTF-16" -> UTF-32:
            // https://en.wikipedia.org/wiki/UTF-16#Code_points_from_U+010000_to_U+10FFFF
            const char32_t high_code_point = (this_character - high_surrogate_start) << 10;
            const char16_t low_code_point  = next_character - low_surrogate_start;
            const char32_t code_point      = high_code_point + low_code_point + supplementary_plane_offset;
            utf32_s.push_back(code_point);

            continue;
        }

        // if not a double character add this as next code point
        utf32_s.push_back(this_character);
    }
    return status_e::success;
}

status_e utf::conversion::utf32_to_utf8(const std::basic_string_view<char32_t>& utf32_sv, std::basic_string<char8_t>& utf8_s, bool comply_with_standard = false) {
    bool reverse = utf32_bom(utf32_sv[0]) == endianness_e::little_endian;

    for (char32_t this_code_point : utf32_sv) {
        if (reverse) {
            this_code_point = utf32_reverse_endianness(this_code_point);
        }
        if (this_code_point > four_byte_boundary) {
            utf8_s.clear();
            return status_e::undefined_error;
        }
        if (this_code_point <= one_byte_boundary) {
            utf8_s.push_back(static_cast<char8_t>(this_code_point));
            continue;
        }
        if (this_code_point <= two_byte_boundary) {
            const uint16_t cp_16       = static_cast<uint16_t>(this_code_point);

            const uint8_t first_5_bits = cp_16 >>  6;
            const uint8_t last_6_bits  = cp_16 & 0x3F;

            utf8_s.push_back((double_byte_marker   << 5) + first_5_bits);
            utf8_s.push_back((trailing_byte_marker << 6) + last_6_bits );

            continue;
        }
        if (this_code_point <= three_byte_boundary) {
            const uint16_t cp_16      = static_cast<uint16_t>(this_code_point);

            const bool wrong_encoding = comply_with_standard        &&
                                        cp_16 < low_surrogate_start ||
                                        cp_16 > high_surrogate_start;
            if (wrong_encoding) {
                utf8_s.clear();
                return status_e::non_standard_encoding;
            }

            const uint8_t  first_4_bits  =  cp_16 >> 12;
            const uint8_t  middle_6_bits = (cp_16 >> 6 ) & 0x3F;
            const uint8_t  last_6_bits   =  cp_16        & 0x3F;

            utf8_s.push_back((triple_byte_marker   << 4) + first_4_bits );
            utf8_s.push_back((trailing_byte_marker << 6) + middle_6_bits);
            utf8_s.push_back((trailing_byte_marker << 6) + last_6_bits  );

            continue;
        }
        if (this_code_point <= four_byte_boundary) {
            const uint8_t first_3_bits  =  this_code_point >> 18;
            const uint8_t second_6_bits = (this_code_point >> 12) & 0x3F;
            const uint8_t third_6_bits  = (this_code_point >> 6 ) & 0x3F;
            const uint8_t last_6_bits   =  this_code_point        & 0x3F;

            utf8_s.push_back((quadruple_byte_marker << 5) + first_3_bits );
            utf8_s.push_back((trailing_byte_marker  << 6) + second_6_bits);
            utf8_s.push_back((trailing_byte_marker  << 6) + third_6_bits );
            utf8_s.push_back((trailing_byte_marker  << 6) + last_6_bits  );

            continue;
        }
    }

    return status_e::success;
}

status_e utf::conversion::utf32_to_utf16(const std::basic_string_view<char32_t>& utf32_sv, std::basic_string<char16_t>& utf16_s, bool comply_with_standard = false) {
    bool reverse = utf32_bom(utf32_sv[0]) == endianness_e::little_endian;
    for (char32_t this_code_point : utf32_sv) {
        if (reverse) {
            this_code_point = utf32_reverse_endianness(this_code_point);
        }
        if (this_code_point >= supplementary_plane_end) {
            utf16_s.clear();
            return status_e::undefined_error;
        }
        if (!is_correct_code_point(this_code_point) && comply_with_standard) {
            utf16_s.clear();
            return status_e::non_standard_encoding;
        }
        if (this_code_point >= supplementary_plane_offset) {
            const int32_t  surrogate_data      = this_code_point - supplementary_plane_offset;

            const int16_t  high_surrogate_data = surrogate_data >> 10;
            const int16_t  low_surrogate_data  = surrogate_data & 0x3FF;

            const char16_t high_surrogate      = high_surrogate_start + high_surrogate_data;
            const char16_t low_surrogate       = low_surrogate_start  + low_surrogate_data;

            utf16_s.push_back(high_surrogate);
            utf16_s.push_back(low_surrogate);

            continue;
        }
        const char16_t character = static_cast<char16_t>(this_code_point);
        utf16_s.push_back(character);
    }
    return status_e::success;
}

#endif // defined IMPLEMENT_UTFUTILS
#endif // !defined(UTFUTILS_H)