#include "miku_ast.h"

string typeToString(MikuType t) {
    switch(t) {
        case TYPE_INT: return "leek";
        case TYPE_FLOAT: return "rin";
        case TYPE_STRING: return "scroll";
        case TYPE_BOOL: return "code";
        case TYPE_VOID: return "ghost";
        default: return "unknown";
    }
}

string MikuValue::toString() const {
    if (type == TYPE_INT) return to_string(iVal);
    if (type == TYPE_FLOAT) return to_string(fVal);
    if (type == TYPE_STRING) return sVal;
    if (type == TYPE_BOOL) return bVal ? "angel" : "virus";
    return "";
}

SymbolTable::SymbolTable(string name, SymbolTable* p) : scopeName(name), parent(p) {}
SymbolTable::~SymbolTable() { printTable("tables.txt"); }

bool SymbolTable::addSymbol(string name, MikuType type) {
    // In strict mode we might check if it exists, but for now we allow shadowing/redef
    SymbolInfo info; info.name = name; info.type = type; info.isFunction = false;
    symbols[name] = info;
    return true;
}

bool SymbolTable::addFunction(string name, MikuType returnType, vector<MikuType> params, vector<string> paramNames) {
    if (symbols.count(name)) return false;
    SymbolInfo info; 
    info.name = name; 
    info.type = returnType; 
    info.isFunction = true; 
    info.paramTypes = params;
    info.paramNames = paramNames; // FIX: Store names
    symbols[name] = info;
    return true;
}

SymbolInfo* SymbolTable::lookup(string name) {
    if (symbols.count(name)) return &symbols[name];
    if (parent) return parent->lookup(name);
    return nullptr;
}

void SymbolTable::printTable(const string& filename) {
    ofstream out(filename, ios::app);
    out << "=== Scope: " << scopeName << " ===" << endl;
    for (auto const& [key, val] : symbols) {
        out << key << " (" << typeToString(val.type) << ")";
        if(val.isFunction) out << " [FUNC]";
        out << endl;
    }
    out << endl;
    out.close();
}

ASTNode::ASTNode(NodeType nt, ASTNode* l, ASTNode* r, ASTNode* a) 
    : nodeType(nt), left(l), right(r), aux(a), dataType(TYPE_UNKNOWN) {}

ASTNode::~ASTNode() { if(left) delete left; if(right) delete right; if(aux) delete aux; }

MikuValue ASTNode::eval(SymbolTable* scope) {
    MikuValue res; 
    res.type = dataType;

    if (nodeType == NODE_SEQ) {
        if (left) {
            MikuValue v = left->eval(scope);
            if (v.isReturn) return v; // FIX: Propagate return
        }
        if (right) {
            MikuValue v = right->eval(scope);
            if (v.isReturn) return v; // FIX: Propagate return
            return v;
        }
        return res;
    }

    // FIX: New Return Logic
    if (nodeType == NODE_RETURN) {
        if (left) res = left->eval(scope);
        res.isReturn = true;
        return res;
    }

    // FIX: Runtime Declaration
    if (nodeType == NODE_DECL) {
        MikuValue val = right->eval(scope);
        // Add to CURRENT scope (dynamic scoping for locals)
        scope->addSymbol(varName, dataType);
        SymbolInfo* sym = scope->lookup(varName);
        if (sym) sym->value = val;
        return val;
    }

    if (nodeType == NODE_FUNC_CALL) {
        SymbolInfo* fn = scope->lookup(varName);
        if (fn && fn->funcBody) {
            // FIX: Create a FRESH scope for recursion/isolation
            // Parent is the global scope (definitionScope->parent), NOT the caller's scope
            SymbolTable* execScope = new SymbolTable(varName + "_exec", fn->definitionScope->parent);

            // 1. Evaluate Arguments
            vector<MikuValue> args;
            ASTNode* argNode = aux; // We stored arg list in aux
            while (argNode) {
                if (argNode->left) args.push_back(argNode->left->eval(scope));
                argNode = argNode->right;
            }

            // 2. Bind Arguments to Parameters
            for (size_t i = 0; i < fn->paramNames.size() && i < args.size(); ++i) {
                execScope->addSymbol(fn->paramNames[i], fn->paramTypes[i]);
                SymbolInfo* p = execScope->lookup(fn->paramNames[i]);
                if (p) p->value = args[i];
            }

            // 3. Execute
            MikuValue ret = fn->funcBody->eval(execScope);
            
            // Clean up implicit return flag so caller continues
            ret.isReturn = false; 
            
            // Note: In a real lang, we'd delete execScope here, but we leak for simplicity/safety
            return ret; 
        }
        return res; 
    }

    if (nodeType == NODE_IF) {
        MikuValue cond = left->eval(scope);
        if (cond.bVal) {
            if (right) return right->eval(scope); // Propagate return
        } else {
            if (aux) return aux->eval(scope); // Propagate return
        }
        return res;
    }

    if (nodeType == NODE_WHILE) {
        while (true) {
            MikuValue cond = left->eval(scope);
            if (!cond.bVal) break;
            if (right) {
                MikuValue v = right->eval(scope);
                if (v.isReturn) return v; // Allow return inside loops
            }
        }
        return res;
    }

    if (nodeType == NODE_CONST) return val;
    if (nodeType == NODE_VAR) {
        SymbolInfo* sym = scope->lookup(varName);
        return sym ? sym->value : res;
    }
    if (nodeType == NODE_ASSIGN) {
        MikuValue rhs = right->eval(scope);
        SymbolInfo* sym = scope->lookup(left->varName);
        if (sym) sym->value = rhs;
        return rhs;
    }
    if (nodeType == NODE_PRINT) {
        MikuValue v = left->eval(scope);
        cout << "[Miku Says]: " << v.toString() << endl;
        return v;
    }

    MikuValue v1 = (left) ? left->eval(scope) : MikuValue();
    MikuValue v2 = (right) ? right->eval(scope) : MikuValue();

    if (nodeType == NODE_OP_ADD) {
        if (v1.type == TYPE_INT) { res.type=TYPE_INT; res.iVal = v1.iVal + v2.iVal; }
        else { res.type=TYPE_FLOAT; res.fVal = v1.fVal + v2.fVal; }
    }
    else if (nodeType == NODE_OP_SUB) {
        if (v1.type == TYPE_INT) { res.type=TYPE_INT; res.iVal = v1.iVal - v2.iVal; }
        else { res.type=TYPE_FLOAT; res.fVal = v1.fVal - v2.fVal; }
    }
    else if (nodeType == NODE_OP_MUL) {
        if (v1.type == TYPE_INT) { res.type=TYPE_INT; res.iVal = v1.iVal * v2.iVal; }
        else { res.type=TYPE_FLOAT; res.fVal = v1.fVal * v2.fVal; }
    }
    else if (nodeType == NODE_OP_DIV) {
        if (v1.type == TYPE_INT) { res.type=TYPE_INT; res.iVal = (v2.iVal?v1.iVal/v2.iVal:0); }
        else { res.type=TYPE_FLOAT; res.fVal = v1.fVal / v2.fVal; }
    }
    else if (nodeType == NODE_OP_GT) { res.type=TYPE_BOOL; res.bVal = v1.iVal > v2.iVal; }
    else if (nodeType == NODE_OP_LT) { res.type=TYPE_BOOL; res.bVal = v1.iVal < v2.iVal; }
    else if (nodeType == NODE_OP_GE) { res.type=TYPE_BOOL; res.bVal = v1.iVal >= v2.iVal; }
    else if (nodeType == NODE_OP_LE) { res.type=TYPE_BOOL; res.bVal = v1.iVal <= v2.iVal; }
    else if (nodeType == NODE_OP_EQ) { 
        res.type=TYPE_BOOL; 
        if(v1.type == TYPE_INT) res.bVal = v1.iVal == v2.iVal;
        else if (v1.type == TYPE_BOOL) res.bVal = v1.bVal == v2.bVal;
        else res.bVal = false; 
    }
    else if (nodeType == NODE_OP_NEQ){ 
        res.type=TYPE_BOOL; 
        if(v1.type == TYPE_INT) res.bVal = v1.iVal != v2.iVal;
        else if (v1.type == TYPE_BOOL) res.bVal = v1.bVal != v2.bVal;
        else res.bVal = true; 
    }
    
    return res;
}