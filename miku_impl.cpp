#include "miku_ast.h"

// --- Helper ---
string typeToString(MikuType t) {
    switch(t) {
        case TYPE_INT: return "leek";
        case TYPE_FLOAT: return "rin/len";
        case TYPE_STRING: return "scroll";
        case TYPE_BOOL: return "code";
        case TYPE_VOID: return "ghost";
        case TYPE_CLASS: return "class";
        default: return "unknown";
    }
}

// --- MikuValue ---
string MikuValue::toString() const {
    switch(type) {
        case TYPE_INT: return to_string(iVal);
        case TYPE_FLOAT: return to_string(fVal);
        case TYPE_STRING: return sVal;
        case TYPE_BOOL: return bVal ? "angel" : "virus";
        default: return "ghost";
    }
}

// --- SymbolTable ---
SymbolTable::SymbolTable(string name, SymbolTable* p) : scopeName(name), parent(p) {}

SymbolTable::~SymbolTable() {
    // Print table to file on destruction or manual call
    printTable("tables.txt");
}

bool SymbolTable::addSymbol(string name, MikuType type, string customType) {
    if (symbols.find(name) != symbols.end()) return false; // Already exists
    SymbolInfo info;
    info.name = name;
    info.type = type;
    info.customTypeName = customType;
    info.isFunction = false;
    symbols[name] = info;
    return true;
}

bool SymbolTable::addFunction(string name, MikuType returnType, vector<MikuType> params) {
    if (symbols.find(name) != symbols.end()) return false;
    SymbolInfo info;
    info.name = name;
    info.type = returnType;
    info.isFunction = true;
    info.paramTypes = params;
    symbols[name] = info;
    return true;
}

SymbolInfo* SymbolTable::lookup(string name) {
    if (symbols.find(name) != symbols.end()) return &symbols[name];
    if (parent) return parent->lookup(name);
    return nullptr;
}

void SymbolTable::printTable(const string& filename) {
    ofstream out(filename, ios::app);
    out << "=== Symbol Table: " << scopeName << " ===" << endl;
    if (parent) out << "Parent Scope: " << parent->scopeName << endl;
    
    for (auto const& [key, val] : symbols) {
        out << "ID: " << key << " | Type: " << typeToString(val.type);
        if (val.isFunction) {
            out << " | Kind: Function | Params: " << val.paramTypes.size();
        } else {
            out << " | Kind: Variable";
        }
        out << endl;
    }
    out << "======================================" << endl << endl;
    out.close();
}

// --- ASTNode ---
ASTNode::ASTNode(NodeType nt, ASTNode* l, ASTNode* r) 
    : nodeType(nt), left(l), right(r), dataType(TYPE_UNKNOWN) {}

ASTNode::~ASTNode() {
    if(left) delete left;
    if(right) delete right;
}

MikuValue ASTNode::eval(SymbolTable* scope) {
    MikuValue res;
    res.type = dataType;

    // 1. Base Cases (Leafs)
    if (nodeType == NODE_CONST) {
        return val;
    }
    if (nodeType == NODE_VAR) {
        SymbolInfo* sym = scope->lookup(varName);
        if (sym) return sym->value;
        // Default values if not found/init
        if (dataType == TYPE_INT) res.iVal = 0;
        return res;
    }
    if (nodeType == NODE_OTHER) {
        // "Default value for the type"
        if (dataType == TYPE_INT) res.iVal = 0;
        if (dataType == TYPE_FLOAT) res.fVal = 0.0;
        if (dataType == TYPE_BOOL) res.bVal = false;
        if (dataType == TYPE_STRING) res.sVal = "";
        return res;
    }

    // 2. Assignment
    if (nodeType == NODE_ASSIGN) {
        // Evaluate RHS
        MikuValue rhs = right->eval(scope);
        // Update Symbol Table
        SymbolInfo* sym = scope->lookup(left->varName); // left is NODE_VAR
        if (sym) {
            sym->value = rhs;
        }
        return rhs;
    }

    // 3. Print
    if (nodeType == NODE_PRINT) {
        MikuValue v = left->eval(scope);
        cout << "[Miku Says]: " << v.toString() << endl;
        return v;
    }

    // 4. Arithmetic / Boolean Ops
    MikuValue v1 = left->eval(scope);
    MikuValue v2 = (right) ? right->eval(scope) : MikuValue(); // Unary check if needed

    if (nodeType == NODE_OP_ADD) {
        if (v1.type == TYPE_INT) { res.type=TYPE_INT; res.iVal = v1.iVal + v2.iVal; }
        else if (v1.type == TYPE_FLOAT) { res.type=TYPE_FLOAT; res.fVal = v1.fVal + v2.fVal; }
    }
    else if (nodeType == NODE_OP_SUB) {
        if (v1.type == TYPE_INT) { res.type=TYPE_INT; res.iVal = v1.iVal - v2.iVal; }
        else if (v1.type == TYPE_FLOAT) { res.type=TYPE_FLOAT; res.fVal = v1.fVal - v2.fVal; }
    }
    else if (nodeType == NODE_OP_MUL) {
        if (v1.type == TYPE_INT) { res.type=TYPE_INT; res.iVal = v1.iVal * v2.iVal; }
        else if (v1.type == TYPE_FLOAT) { res.type=TYPE_FLOAT; res.fVal = v1.fVal * v2.fVal; }
    }
    else if (nodeType == NODE_OP_DIV) {
        if (v1.type == TYPE_INT) { res.type=TYPE_INT; res.iVal = (v2.iVal!=0 ? v1.iVal / v2.iVal : 0); }
        else if (v1.type == TYPE_FLOAT) { res.type=TYPE_FLOAT; res.fVal = v1.fVal / v2.fVal; }
    }
    // Boolean logic
    else if (nodeType == NODE_OP_GT) { res.type = TYPE_BOOL; res.bVal = v1.iVal > v2.iVal; } // Simplified for int
    else if (nodeType == NODE_OP_LT) { res.type = TYPE_BOOL; res.bVal = v1.iVal < v2.iVal; }
    else if (nodeType == NODE_OP_EQ) { res.type = TYPE_BOOL; res.bVal = v1.iVal == v2.iVal; }

    return res;
}