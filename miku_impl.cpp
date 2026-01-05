#include "miku_ast.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>

extern int yyparse(void);
extern FILE* yyin;

// must be provided by parser/driver
Program* miku_get_program();

/* ---------------- tables.txt dump ---------------- */

static void dump_tables(const Program& p, const char* path = "tables.txt") {
    std::ofstream out(path);
    if (!out) throw RuntimeError("Cannot open tables.txt for writing");

    out << "=== SYMBOL TABLES ===\n\n";

    // Global scope
    out << "[SCOPE] global\n";
    out << "  structs:\n";
    for (const auto& s : p.structs) {
        out << "    - " << s->name << "\n";
    }

    out << "  functions:\n";
    for (const auto& f : p.funcs) {
        out << "    - " << f->name << "(";
        for (size_t i = 0; i < f->params.size(); i++) {
            out << f->params[i].name << ":" << type_name(f->params[i].ty);
            if (i + 1 < f->params.size()) out << ", ";
        }
        out << ") -> " << type_name(f->ret) << "\n";
    }
    out << "\n";

    // Struct scopes
    for (const auto& s : p.structs) {
        out << "[SCOPE] struct " << s->name << "\n";

        out << "  fields:\n";
        for (const auto& fld : s->fields) {
            out << "    - " << fld.name << " : " << type_name(fld.ty) << "\n";
        }

        out << "  methods:\n";
        for (const auto& kv : s->methods) {
            const Function* m = kv.second.get();
            out << "    - " << m->name << "(";
            for (size_t i = 0; i < m->params.size(); i++) {
                out << m->params[i].name << ":" << type_name(m->params[i].ty);
                if (i + 1 < m->params.size()) out << ", ";
            }
            out << ") -> " << type_name(m->ret) << "\n";
        }
        out << "\n";
    }

    out << "=== END ===\n";
}

/* ---------------- run ---------------- */

static void run_program(Program& p) {
    p.index();

    auto it = p.func_map.find("world_is_mine");
    if (it == p.func_map.end()) {
        throw RuntimeError("No entry function: world_is_mine");
    }

    Ctx ctx;
    ctx.prog = &p;

    // Entry has 0 args by spec (your tests call run_tests from main)
    const Function& entry = *it->second;
    std::vector<Value> args;
    (void)call_function(ctx, entry, args, /*line*/0, std::nullopt);
}

int main(int argc, char** argv) {
    const char* path = (argc >= 2) ? argv[1] : "test.miku";

    yyin = std::fopen(path, "rb");
    if (!yyin) {
        std::perror("fopen");
        return 1;
    }

    try {
        int rc = yyparse();
        std::fclose(yyin);
        yyin = nullptr;

        if (rc != 0) {
            std::cerr << "Parse failed.\n";
            return 1;
        }

        Program* p = miku_get_program();
        if (!p) {
            std::cerr << "Internal error: program is null.\n";
            return 1;
        }

        // build maps
        p->index();

        // write tables.txt
        dump_tables(*p, "tables.txt");

        // run
        run_program(*p);

    } catch (const RuntimeError& e) {
        std::cerr << "[RUNTIME] " << e.what() << "\n";
        return 2;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << "\n";
        return 3;
    }

    return 0;
}
