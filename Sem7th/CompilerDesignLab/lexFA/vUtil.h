bool isAlphabet(const char c);
bool isDigit(const char c);
bool isBraces(const char c);
bool isOperator(const char c);

bool isAlphabet(const char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
bool isDigit(const char c) {
    return (c >= '0' && c <= '9');
}
bool isBraces(const char c) {
    return (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']');
}
bool isOperator(const char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '>' || c == '<' || c == '=' || c == '&' || c == '|' || c == '^' || c == '!');
}
