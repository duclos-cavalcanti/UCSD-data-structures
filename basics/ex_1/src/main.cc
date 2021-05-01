#include <iostream>
#include <stack>
#include <string>

struct Bracket {
  Bracket(char type, int position) : type(type), position(position) {}

  // Matches char 'c' to a bracket type and the attribute type to a complementing one
  bool Matchc(char c) {
    if (type == '[' && c == ']')
      return true;
    if (type == '{' && c == '}')
      return true;
    if (type == '(' && c == ')')
      return true;
    return false;
  }

  char type;
  int position;
};

int main() {
  std::string text;
  getline(std::cin, text);

  // Template Class for stack
  std::stack<Bracket> opening_brackets_stack;

  for (int position = 0; position < text.length(); ++position) {
    char cur = text[position];

    // Push opening brackets
    if (cur == '(' || cur == '[' || cur == '{') {
      Bracket open_brack = Bracket(cur, position);
      opening_brackets_stack.push(open_brack);
    } else {
      // In case of first closing bracket
      if (opening_brackets_stack.empty()) {
        std::cout << position + 1 << std::endl;
        return -1;
      }

      Bracket top = opening_brackets_stack.top();

      if ((cur == ')' 
            && !top.Matchc(cur)) 
            || (cur == ']' && !top.Matchc(cur)) 
            || (cur == '}' && !top.Matchc(cur))) {

        std::cout << position + 1 << std::endl;
        return -1;
      }
      opening_brackets_stack.pop();
    }
  }

  if (!opening_brackets_stack.empty()) {
    // In case open brackets werent matched to the end
    std::cout << text.length() << std::endl;
    return -1;
  } else {
    std::cout << "Success" << std::endl;
    return 0;
  }
}
