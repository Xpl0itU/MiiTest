#include <cstdarg>
#include <memory>
#include <stdexcept>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;

template<typename... Args>
auto string_format(const string& format, Args... args) -> string {
	int size_s = snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
	if (size_s <= 0) { throw runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>(size_s);
	unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args...);
	return string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

std::string utf16_to_utf8(std::u16string const& s)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff,
        std::codecvt_mode::little_endian>, char16_t> cnv;
    std::string utf8 = cnv.to_bytes(s);
    if(cnv.converted() < s.size())
        throw std::runtime_error("incomplete conversion");
    return utf8;
}