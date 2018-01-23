#ifndef COMMON_BASE64_BASE64_H
#define COMMON_BASE64_BASE64_H

namespace Base64 {
    std::string Encode(unsigned char const *bytes_to_encode,
                        unsigned int in_len, bool url);
}

#endif