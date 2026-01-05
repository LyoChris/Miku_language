#ifndef MIKU_AST_H
#define MIKU_AST_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>

using namespace std;

enum MikuType {
    TYPE_VOID, TYPE_INT, TYPE_FLOAT, TYPE_STRING, TYPE_BOOL, TYPE_CLASS, TYPE_UNKNOWN
};

class MikuValue {
public:
    MikuType type;
    int iVal;
    double fVal;
    string sVal;
    bool bVal;
    bool isReturn; // FIX: Flag to propagate return values up the AST

    MikuValue() : type(TYPE_VOID), iVal(0), fVal(0.0), bVal(false), isReturn(false) {}
    string toString() const;
};

// Forward declaration
class ASTNode;
class SymbolTable; 

struct SymbolInfo {
    string name;
    MikuType type;
    MikuValue value;
    bool isFunction;
    vector<MikuType> paramTypes;
    vector<string> paramNames; // FIX: Store parameter names to bind arguments
    
    ASTNode* funcBody = nullptr; 
    SymbolTable* definitionScope = nullptr; 
};

class SymbolTable {
public:
    string scopeName;
    SymbolTable* parent;
    map<string, SymbolInfo> symbols;

    SymbolTable(string name, SymbolTable* p = nullptr);
    ~SymbolTable();

    bool addSymbol(string name, MikuType type);
    bool addFunction(string name, MikuType returnType, vector<MikuType> params, vector<string> paramNames);
    SymbolInfo* lookup(string name);
    void printTable(const string& filename);
};

enum NodeType {
    NODE_CONST, NODE_VAR, 
    NODE_OP_ADD, NODE_OP_SUB, NODE_OP_MUL, NODE_OP_DIV,
    NODE_OP_GT, NODE_OP_LT, NODE_OP_GE, NODE_OP_LE, NODE_OP_EQ, NODE_OP_NEQ,
    NODE_ASSIGN, NODE_PRINT, 
    
    NODE_SEQ,       
    NODE_IF,        
    NODE_WHILE,     
    NODE_FUNC_CALL, 
    NODE_OTHER,
    
    NODE_RETURN,    // FIX: New node for 'offer'
    NODE_DECL,      // FIX: New node for 'let' (runtime declaration)
    NODE_ARG_LIST   // FIX: New node to chain arguments
};

class ASTNode {
public:
    NodeType nodeType;
    MikuType dataType;
    MikuValue val;
    string varName;
    
    ASTNode *left, *right, *aux; 

    ASTNode(NodeType nt, ASTNode* l = nullptr, ASTNode* r = nullptr, ASTNode* a = nullptr);
    virtual ~ASTNode();

    MikuValue eval(SymbolTable* scope); 
};

string typeToString(MikuType t);

#endif