#ifndef MIKU_AST_H
#define MIKU_AST_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>

using namespace std;

// --- Data Types ---
enum MikuType {
    TYPE_VOID,
    TYPE_INT,       // leek
    TYPE_FLOAT,     // rin (float/double)
    TYPE_STRING,    // scroll
    TYPE_BOOL,      // code
    TYPE_CLASS,
    TYPE_UNKNOWN
};

// --- Value Wrapper (Part IV) ---
class MikuValue {
public:
    MikuType type;
    int iVal;
    double fVal;
    string sVal;
    bool bVal;

    MikuValue() : type(TYPE_VOID), iVal(0), fVal(0.0), bVal(false) {}
    
    // Helpers for printing and operations
    string toString() const;
};

// --- Symbol Table (Part II) ---
struct SymbolInfo {
    string name;
    MikuType type;
    string customTypeName; // For classes
    MikuValue value;       // Current value
    bool isFunction;
    vector<MikuType> paramTypes; // For functions
};

class SymbolTable {
public:
    string scopeName;
    SymbolTable* parent;
    map<string, SymbolInfo> symbols;

    SymbolTable(string name, SymbolTable* p = nullptr);
    ~SymbolTable();

    bool addSymbol(string name, MikuType type, string customType = "");
    bool addFunction(string name, MikuType returnType, vector<MikuType> params);
    SymbolInfo* lookup(string name);
    void printTable(const string& filename);
};

// --- AST Nodes (Part IV) ---
enum NodeType {
    NODE_CONST,
    NODE_VAR,
    NODE_OP_ADD, NODE_OP_SUB, NODE_OP_MUL, NODE_OP_DIV,
    NODE_OP_GT, NODE_OP_LT, NODE_OP_GE, NODE_OP_LE, NODE_OP_EQ, NODE_OP_NEQ,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_OTHER // For unsupported ops in eval (like func calls in expressions)
};

class ASTNode {
public:
    NodeType nodeType;
    MikuType dataType;
    MikuValue val;          // For constants
    string varName;         // For variables/assign
    ASTNode *left, *right;

    ASTNode(NodeType nt, ASTNode* l = nullptr, ASTNode* r = nullptr);
    virtual ~ASTNode();

    // The Eval function (Part IV)
    MikuValue eval(SymbolTable* scope); 
};

// Helper for type conversion strings
string typeToString(MikuType t);

#endif