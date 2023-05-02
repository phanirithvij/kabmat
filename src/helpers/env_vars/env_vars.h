#include <string>
#include <regex>

// https://stackoverflow.com/questions/1902681/expand-file-names-that-have-environment-variables-in-their-path
void autoExpandEnvironmentVariables(std::string& text) {
    using namespace std;
    static regex envRegex("\\$(\\w+|\\{\\w+\\})", regex::ECMAScript);
    size_t offset = 0;
    const string matchText = text;
    sregex_token_iterator matchIter(matchText.begin(), matchText.end(), envRegex, {0, 1});
    for (sregex_token_iterator end; matchIter != end; ++matchIter) {
        const string match = matchIter->str();
        string envVarName = (++matchIter)->str();
        if (envVarName.front() == '{' && envVarName.back() == '}') {
            envVarName.erase(envVarName.begin());
            envVarName.erase(envVarName.end()-1);
        }
        const char * s = getenv(envVarName.c_str());
        if (s != nullptr) {
            string value(s);
            autoExpandEnvironmentVariables(value);
            size_t pos = text.find(match, offset);
            if (pos != string::npos) {
                text.replace(pos, match.length(), value);
                offset = pos + value.length();
            }
        } else {
            offset += match.length();
        }
    }
}
