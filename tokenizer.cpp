#include "tokenizer.h"

void Tokenizer::Next() {
    std::string s;
    c_ = static_cast<char>(in_->peek());
    if (c_ == '\xff') {
        cur_token_ = Token(SymbolToken{"\xff"});
        return;
    }
    c_ = static_cast<char>(in_->get());
    while (std::isspace(c_) && c_ != '\xff') {
        if (!std::isspace(in_->peek()) || in_->peek() == EOF) {
            if (in_->peek() == EOF) {
                cur_token_ = SymbolToken{"\xff"};
                return;
            }
            c_ = static_cast<char>(in_->get());
            break;
        }
        c_ = static_cast<char>(in_->get());
    }
    if (c_ == '(') {
        cur_token_ = BracketToken::OPEN;
        return;
    } else if (c_ == ')') {
        cur_token_ = BracketToken::CLOSE;
        return;
    } else if (c_ == '.') {
        cur_token_ = DotToken{};
        return;
    } else if (c_ == '\'') {
        cur_token_ = QuoteToken{};
        return;
    } else if (c_ == '+') {
        cur_token_ = SymbolToken{"+"};
        return;
    } else if (c_ == '-') {
        if (isspace(in_->peek()) || !std::isdigit(in_->peek()) || in_->peek() == EOF) {
            cur_token_ = SymbolToken{"-"};
        } else {
            s += '-';
            while (in_->peek() != EOF && std::isdigit(in_->peek())) {
                c_ = static_cast<char>(in_->get());
                s += c_;
            }
            cur_token_ = Token(ConstantToken{std::stoi(s)});
        }
        return;
    } else if (c_ == '@') {
        throw SyntaxError();
    } else if (std::isdigit(c_)) {
        while (c_ != '\xff' && std::isdigit(c_)) {
            s += c_;
            if (in_->peek() == EOF || !std::isdigit(in_->peek())) {
                break;
            }
            c_ = static_cast<char>(in_->get());
        }
        cur_token_ = Token(ConstantToken{std::stoi(s)});
        return;
    } else {
        while (c_ != '\xff' && !isspace(c_) &&
               (isdigit(c_) || isalpha(c_) || special_characters_.contains(c_))) {
            s += c_;
            if (in_->peek() == EOF || std::isspace(in_->peek())) {
                break;
            }
            c_ = static_cast<char>(in_->get());
        }
        cur_token_ = SymbolToken{s};
        return;
    }
}