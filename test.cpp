#include "include/utf-utils/utf_utils.hpp"

int main()
{
    const char8_t* Old_Uyghur_Letter_Aleph = u8"\U00010348";
    std::basic_string_view<char8_t> Old_Uyghur_Letter_Aleph_8(Old_Uyghur_Letter_Aleph);
    std::basic_string<char32_t> Old_Uyghur_Letter_Aleph_32;
    utf8_to_utf32(Old_Uyghur_Letter_Aleph_8, Old_Uyghur_Letter_Aleph_32);

}