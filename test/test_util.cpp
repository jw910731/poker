#include "test_util.h"

#include <sstream>

test_exception::test_exception(const std::string &s) {
    std::stringstream ss;
    ss << "[Fail] Fail in " << s << "test\n";
    m_msg = ss.str();
}

const char *test_exception::what() const noexcept { return m_msg.c_str(); }
