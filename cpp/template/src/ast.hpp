// ast.hpp
#pragma once

#include <iostream>
#include <memory>
#include <string>

// 所有 AST 的基类
class BaseAST {
 public:
  virtual ~BaseAST() = default;

  // 推荐：在后续阶段用 Dump 输出 Koopa / RISC-V / 或调试信息
  virtual void Dump(std::ostream &os) const = 0;
};

// CompUnit ::= FuncDef
class CompUnitAST  : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_def;

  // void Dump(std::ostream &os) const override {
  //   os << "CompUnitAST { ";
  //   func_def->Dump(os);
  //   os << " }";
  // }
  void Dump(std::ostream &os) const override{
    func_def->Dump(os);
  }
};

// FuncType ::= "int"
class FuncTypeAST  : public BaseAST {
 public:
  void Dump(std::ostream &os) const override {
    // os << "FuncTypeAST { int }";
    os << "i32";
  }
};

// Number ::= INT_CONST
class NumberAST  : public BaseAST {
 public:
  int value = 0;

  void Dump(std::ostream &os) const override {
    // os << "NumberAST { " << value << " }";
    os << value;
  }
};

// Stmt ::= "return" Number ";"
class ReturnStmtAST  : public BaseAST {
 public:
  std::unique_ptr<BaseAST> number;  // 实际会是 NumberAST

  void Dump(std::ostream &os) const override {
    // os << "StmtAST { ";
    // number->Dump(os);
    // os << " }";
    os << " ret ";
    number->Dump(os);
    os << "\n";
  }
};

// Block ::= "{" Stmt "}"
class BlockAST  : public BaseAST {
 public:
  std::unique_ptr<BaseAST> stmt;  // 实际会是 ReturnStmtAST

  void Dump(std::ostream &os) const override {
    // os << "BlockAST { ";
    // stmt->Dump(os);
    // os << " }";
    os << "%entry:\n";
    stmt->Dump(os);
  }
};

// FuncDef ::= FuncType IDENT "(" ")" Block
class FuncDefAST  : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_type;  // FuncTypeAST
  std::string ident;                   // IDENT 的文本，比如 "main"
  std::unique_ptr<BaseAST> block;      // BlockAST

  void Dump(std::ostream &os) const override {
    // os << "FuncDefAST { ";
    // func_type->Dump(os);
    // os << ", " << ident << ", ";
    // block->Dump(os);
    // os << " }";
    os << "fun @" << ident << "(): ";
    func_type->Dump(os);
    os << " {\n";
    block->Dump(os);
    os << "}\n";
  }
};
