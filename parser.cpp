#include "parser.h"

std::shared_ptr<Object> Read(Tokenizer* tokenizer) {
    if (tokenizer->IsEnd()) {
        throw SyntaxError("SyntaxError: IsEnd.");
    }
    auto cur_token = tokenizer->GetToken();

    tokenizer->Next();
    /// https://en.cppreference.com/w/cpp/utility/variant/get_if
    if (const BracketToken* bracket_token = std::get_if<BracketToken>(&cur_token)) {
        return (*bracket_token == BracketToken::CLOSE) ? std::make_shared<CloseParenObj>()
                                                       : ReadList(tokenizer);
    }
    if (const SymbolToken* symbol_token = std::get_if<SymbolToken>(&cur_token)) {
        return std::make_shared<Symbol>(symbol_token->name);
    }
    if (const ConstantToken* constant_token = std::get_if<ConstantToken>(&cur_token)) {
        return std::make_shared<Number>(constant_token->value);
    }
    if (const DotToken* dot_token = std::get_if<DotToken>(&cur_token)*) {
        return std::make_shared<Dot>();
    }
    throw SyntaxError();
}

std::shared_ptr<Object> ReadList(Tokenizer* tokenizer) {
    auto cell = std::make_shared<Cell>();
    auto first_token = Read(tokenizer);
    cell->first_ = first_token;
    if (!Is<Dot>(first_token)) {
        if (Is<CloseParenObj>(first_token)) {
            return nullptr;
        } else {
            cell->second_ = ReadList(tokenizer);
            return cell;
        }
    } else {
        auto first = Read(tokenizer);
        if (Is<CloseParenObj>(Read(tokenizer))) {
            return first;
        } else {
            throw SyntaxError();
        }
    }
}