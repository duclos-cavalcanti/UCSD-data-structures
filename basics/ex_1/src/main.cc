#include <iostream>
#include <stack>
#include <string>

struct Bracket {
  Bracket(char type, int position) : type(type), position(position) {}

  char type;
  int position;

  // Checks for matching char bracket with the struct's attribute 'type'.
  bool Matchc(char c) {
    if (type == '[' && c == ']')
      return true;
    if (type == '{' && c == '}')
      return true;
    if (type == '(' && c == ')')
      return true;
    return false;
  }

};

int main() {
  std::string text;
  getline(std::cin, text);

  // Bracket Stack
  std::stack <Bracket> b_stack;

  // loop through captured string
  for (int position = 0; position < text.length(); ++position) {
    char cur = text[position];

    // if opening bracket
    if (cur == '(' || cur == '[' || cur == '{') {
      Bracket open_brack = Bracket(cur, position);
      b_stack.push(open_brack);

    } else {
      // if closing bracket
      if (cur == ')' || cur == ']' || cur == '}') {
        if (b_stack.empty()) {
          // unmatched closing bracket with no opening bracket on the stack
          std::cout << position + 1 << std::endl;
          return -1;
        } else {
          Bracket top = b_stack.top(); // returns top element of stack
          // if current closing bracket DOESNT match to latest opening bracket
          if (!top.Matchc(cur)) {
            // most recent opening bracket does not match this closing bracket
            std::cout << position + 1 << std::endl;
            return -1;
          } else {
            b_stack.pop();
          }
        }
      }
    }
  }

  if (!b_stack.empty()) {
    // In case open brackets werent matched to the end
    Bracket top = b_stack.top(); // returns top element of stack
    std::cout << top.position + 1 << std::endl;
    return -1;
  } else {
    std::cout << "Success" << std::endl;
    return 0;
  }
}
