#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <iostream>

class Object : public std::enable_shared_from_this<Object> {
public:
    //    Object() = default; // вообще лучше не создавать Object
    virtual ~Object() = default;
};

class Number : public Object {
public:
    Number(int number) : number_(number) {
    }

    int GetValue() const {
        return number_;
    }

private:
    int number_;
};

class Symbol : public Object {
public:
    Symbol(std::string symbol) : symbol_(symbol) {
    }

    const std::string& GetName() const {
        return symbol_;
    }

private:
    std::string symbol_;
};

class Dot : public Object {};
class OpenParenObj : public Object {};
class CloseParenObj : public Object {};

class Cell : public Object {
public:
    std::shared_ptr<Object> first_;
    std::shared_ptr<Object> second_;

    Cell() = default;
    Cell(std::shared_ptr<Object> first, std::shared_ptr<Object> second)
        : first_(first), second_(second) {
    }

    std::shared_ptr<Object> GetFirst() const {
        return first_;
    }
    std::shared_ptr<Object> GetSecond() const {
        return second_;
    }
};

template <class T>
std::shared_ptr<T> As(const std::shared_ptr<Object>& obj) {
    return std::dynamic_pointer_cast<T>(obj);
}

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
    return std::dynamic_pointer_cast<T>(obj) != nullptr;
}