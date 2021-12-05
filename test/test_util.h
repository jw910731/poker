#include <exception>
#include <string>

class test_exception : public std::exception {
  private:
    std::string m_msg;

  public:
    test_exception(const std::string &test_item);
    const char *what() const noexcept;
};
