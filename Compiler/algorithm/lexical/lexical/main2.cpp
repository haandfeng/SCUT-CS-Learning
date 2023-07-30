//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//const vector<char> bracket_set = { '(', ')', '{', '}', '[', ']', ';', ',', '"' };
//const vector<char> positive_negative_signs_set = { '+', '-' };
//const vector<char> type_identify_set = { '%', '&' };
//const vector<char> monocular_operator_set = { '+', '-', '*', '/', '%', '&', '>', '<', '=' };
//const vector<string> binocular_operator_set = { "+=", "-=", "*=", "/=", "<=", ">=", "==","++", "--" };
//const vector<string> keyword_set = { "main", "float", "return", "if", "else", "do", "while", "for", "scanf", "printf", "sqrt", "abs" };
//const vector<string> type_set = { "int", "double", "short", "char", "void" };
//const vector<string> comment_set = { "/*", "*", "*/", "//" };
//const char underline = '_';
//int line = 1;
//string cur_str;
//string lexical_analysis_result;
//
//
///*
// *Tool function.
// */
//bool is_in_set(vector<char> set, char ch) {
//    // CG don't support.
//    // return set.end() != find(set.begin(), set.end(), ch);
//
//    bool in_set = false;
//    for (vector<char>::iterator it = set.begin(); it != set.end(); it++)
//        if (*it == ch) {
//            in_set = true;
//            break;
//        }
//    return in_set;
//}
//
///*
// * override func is_in_set.
// */
//bool is_in_set(vector<string> set, string str) {
//    // CG don't support.
//    // return set.end() != find(set.begin(), set.end(), ch);
//
//    bool in_set = false;
//    for (vector<string>::iterator it = set.begin(); it != set.end(); it++)
//        if (str.compare(*it) == 0) {
//            in_set = true;
//            break;
//        }
//    return in_set;
//}
//
//bool isNextLine(char ch) {
//    if (ch == '\n') return true;
//    return false;
//}
//
//bool isUnderline(char ch) {
//    if (ch == '_') return true;
//    return false;
//}
//
//bool isEnd(char ch) {
//    if (ch == EOF) return true;
//    return false;
//}
//
//bool printError(int line, string text) {
//    cout << "Error at Line " << line << ": Illegal floating point number \"" << text << "\".\n";
//    return true;
//}
//
//string getFormatStr(string type) {
//    return "line" + to_string(line) + ":(" + type + ", " + cur_str + ")\n";
//}
//
//bool printFormat(string type) {
//    // cout << "line" << line << ":(" << type << ", " << cur_str << ")" << endl;
//    lexical_analysis_result += getFormatStr(type);
//    return true;
//}
//
//bool printRes() {
//    cout << lexical_analysis_result;
//    return true;
//}
//
///*
// * process
// */
//bool float_process() {
//    printFormat("float");
//    cur_str = "";
//    return true;
//}
//
//bool bracket_process() {
//    printFormat("bracket");
//    cur_str = "";
//    return true;
//}
//
//bool operator_process() {
//    printFormat("OPT");
//    cur_str = "";
//    return true;
//}
//
//bool integer_process() {
//    printFormat("integer");
//    cur_str = "";
//    return true;
//}
//
//bool decimal_process() {
//    printFormat("decimal");
//    cur_str = "";
//    return true;
//}
//
//bool identity_process() {
//    printFormat("identify");
//    cur_str = "";
//    return true;
//}
//
//bool keyword_process() {
//    printFormat("keyword");
//    cur_str = "";
//    return true;
//}
//
//bool type_process() {
//    printFormat("type");
//    cur_str = "";
//    return true;
//}
//
//bool type_identify_process() {
//    printFormat("typeidentify");
//    cur_str = "";
//    return true;
//}
//
///*
// * Distinguish among identity type and keyword.
// */
//bool process_identity() {
//
//    if (is_in_set(keyword_set, cur_str))
//        keyword_process();
//    else if (is_in_set(type_set, cur_str))
//        type_process();
//    else
//        identity_process();
//
//    return true;
//}
//
//
//bool lexicalAnalysis() {
//
//    char ch;
//    /*
//     * start state.
//     */
//    ch = getchar();
//start_label:
//    if (isdigit(ch)) goto digit_label;
//    else if (is_in_set(monocular_operator_set, ch)) goto operator_label;
//    else if (isalpha(ch) || isUnderline(ch)) goto identity_label;
//    else if (is_in_set(bracket_set, ch)) goto bracket_label;
//    else if (isEnd(ch)) goto end_label;
//
//    /*
//     * If it is a space or a match that is not a regular expression, then re-acquire the character and jump back to the beginning.
//     */
//    else {
//        ch = getchar();
//        goto start_label;
//    }
//
//identity_label:
//    cur_str += ch;
//    ch = getchar();
//    if (isalpha(ch) || isUnderline(ch) || isdigit(ch)) goto identity_label;
//    else {
//        process_identity();
//        goto start_label;
//    }
//
//type_identify_label:
//    cur_str += ch;
//    type_identify_process();
//    ch = getchar();
//    goto start_label;
//
//
//    /*
//     * do analysis.
//     */
//digit_label:
//    cur_str += ch;
//    ch = getchar();
//    if (isdigit(ch)) goto digit_label;
//    else if (ch == '.') goto decimal_label;
//    /*
//     *If it is a space or a match that is not a regular expression, jump back to the beginning.
//     */
//    else {
//        integer_process();
//        goto start_label;
//    }
//
//decimal_label:
//    cur_str += ch;
//    ch = getchar();
//    if (isdigit(ch)) goto decimal_label;
//    else if (ch == 'e') goto float_label;
//    /*
//     *If it is a space or a match that is not a regular expression, jump back to the beginning.
//     */
//    else {
//        decimal_process();
//        goto start_label;
//    }
//
//float_label:
//    cur_str += ch;
//    ch = getchar();
//    if (isdigit(ch)) goto float_label;
//
//    /*
//     * If a sign appears, the number must appear after the number
//     */
//    else if (is_in_set(positive_negative_signs_set, ch)) {
//        cur_str += ch;
//        ch = getchar();
//        if (isdigit(ch)) goto float_label;
//        else {
//            cur_str += ch;
//            goto error_label;
//        }
//    }
//    else {
//        if (cur_str.length() > 0 && cur_str[cur_str.length() - 1] == 'e')
//            goto error_label;
//
//        float_process();
//        goto start_label;
//    }
//
//operator_label:
//    cur_str += ch;
//    ch = getchar();
//    if (isdigit(ch)) {
//        operator_process();
//        goto digit_label;
//    }
//    /*
//     * do monocular_operator.
//     */
//    else if (is_in_set(monocular_operator_set, ch) && is_in_set(binocular_operator_set, cur_str + ch)) {
//        cur_str += ch;
//        operator_process();
//        ch = getchar();
//        goto start_label;
//    }
//
//    /*
//     * do type_identify_label.
//     */
//    else if (isalpha(ch)) {
//        goto type_identify_label;
//    }
//
//    /*
//     * do comment.
//     */
//    else if (is_in_set(monocular_operator_set, ch) && is_in_set(comment_set, cur_str + ch)) {
//        do {
//            ch = getchar();
//        } while (!isNextLine(ch));
//        line++;
//        cur_str = "";
//        ch = getchar();
//        goto start_label;
//    }
//
//    /*
//     *If it is a space or a match that is not a regular expression, jump back to the beginning.
//     */
//    else {
//        operator_process();
//        goto start_label;
//    }
//
//
//bracket_label:
//    cur_str += ch;
//    ch = getchar();
//
//    bracket_process();
//    if (isNextLine(ch)) line++;
//    goto start_label;
//
//
//error_label:
//    printError(line, cur_str);
//    return false;
//
//end_label:
//    printRes();
//    return true;
//
//}
//
//
//int main() {
//
//    lexicalAnalysis();
//    
//    /*
//    char ch;
//    while (ch != EOF)
//    {
//        ch = getchar();
//        cout << ch;
//    }
//    */
//
//    system("pause");
//    return 0;
//}
