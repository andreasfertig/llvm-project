#include <optional>

struct NotTriviallyDestructible {
  ~NotTriviallyDestructible() {}
};

int main()
{
  std::optional<int>                      o{};
  std::optional<NotTriviallyDestructible> o2{};
}
