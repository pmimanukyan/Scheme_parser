#pragma once
#include "error.h"
#include <variant>
#include <optional>
#include <istream>
#include <unordered_set>

struct SymbolToken {
    std::string name;

    bool operator==(const SymbolToken& other) const {
        return name == other.name;
    }
};

struct QuoteToken {
    bool operator==(const QuoteToken&) const {
        return true;
    }
};

struct DotToken {
    bool operator==(const DotToken&) const {
        return true;
    }
};

enum class BracketToken { OPEN, CLOSE };

struct ConstantToken {
    int value;

    bool operator==(const ConstantToken& other) const {
        return value == other.value;
    }
};

using Token = std::variant<ConstantToken, BracketToken, SymbolToken, QuoteToken, DotToken>;

class Tokenizer {
    std::istream* in_;
    Token cur_token_;
    char c_;
    std::unordered_set<char> special_characters_ = {'<', '=', '>', '*', '/', '#', '?', '!', '-'};

public:
    Tokenizer(std::istream* in) : in_(in) {
        Next();
    }

    bool IsEnd() {
        return cur_token_ == Token(SymbolToken{"\xff"});
    }

    void Next(); // tokenizer.cpp

    Token GetToken() {
        return cur_token_;
    }
};