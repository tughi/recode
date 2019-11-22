#include "Scanner.h"

#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    Token *token;
    int line = 0;

    while ((token = scan_token())->type != Token::END_OF_FILE) {
        if (token->line != line) {
            if (line > 0) {
                cout << endl;
            }
            line = token->line;
            cout << setw(4) << line << ": ";
        }
        cout << token->lexeme->data << " ";
    }
}
