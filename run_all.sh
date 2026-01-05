#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT_DIR"

OUT_DIR="$ROOT_DIR/out"
TEST_DIR="$ROOT_DIR/tests"

mkdir -p "$OUT_DIR"

red()   { printf "\033[31m%s\033[0m\n" "$*"; }
green() { printf "\033[32m%s\033[0m\n" "$*"; }
yellow(){ printf "\033[33m%s\033[0m\n" "$*"; }

require_file() {
  if [[ ! -f "$1" ]]; then
    red "Missing file: $1"
    exit 1
  fi
}

normalize_newlines() {
  if command -v dos2unix >/dev/null 2>&1; then
    dos2unix "$@" >/dev/null 2>&1 || true
  fi
}

compile_lang() {
  yellow "[1/3] Normalizing newlines..."
  normalize_newlines miku.l miku.y miku_impl.cpp miku_ast.h || true

  yellow "[2/3] Cleaning old build artifacts..."
  rm -f miku.tab.* miku.yy.* lex.yy.* y.tab.* miku

  yellow "[3/3] Building (bison + flex + g++)..."
  bison -d -o miku.tab.cpp --defines=miku.tab.hpp miku.y
  flex  -o miku.yy.cpp miku.l

  g++ -std=c++17 -O2 -Wall -Wextra -o miku \
    miku_impl.cpp miku.tab.cpp miku.yy.cpp

  green "Build OK: ./miku"
}

run_ok_test() {
  local test_name="$1"        # e.g. test_01_ok_basics.miku
  local expected_path="$2"    # e.g. out/expected/test_01_ok_basics.expected

  local test_path="$TEST_DIR/$test_name"
  require_file "$test_path"
  require_file "$expected_path"

  local out_file="$OUT_DIR/${test_name%.miku}.out"
  local err_file="$OUT_DIR/${test_name%.miku}.err"

  if ./miku "$test_path" >"$out_file" 2>"$err_file"; then
    :
  else
    red "FAIL (unexpected non-zero exit): $test_name"
    yellow "stderr:"
    sed -n '1,160p' "$err_file" || true
    exit 1
  fi

  if diff -u --strip-trailing-cr -B -w "$expected_path" "$out_file" >/dev/null; then
    green "PASS: $test_name"
  else
    red "FAIL (output mismatch): $test_name"
    yellow "Diff:"
    diff -u --strip-trailing-cr -B -w "$expected_path" "$out_file" || true
    exit 1
  fi
}

run_fail_test() {
  local test_name="$1"
  local test_path="$TEST_DIR/$test_name"
  require_file "$test_path"

  local out_file="$OUT_DIR/${test_name%.miku}.out"
  local err_file="$OUT_DIR/${test_name%.miku}.err"

  set +e
  ./miku "$test_path" >"$out_file" 2>"$err_file"
  local rc=$?
  set -e

  if [[ $rc -eq 0 ]]; then
    red "FAIL (expected failure but succeeded): $test_name"
    yellow "stdout:"
    sed -n '1,120p' "$out_file" || true
    exit 1
  fi

  if [[ ! -s "$err_file" ]]; then
    red "FAIL (expected error message on stderr, got empty): $test_name"
    exit 1
  fi

  green "PASS (failed as expected): $test_name"
}

write_expected_files() {
  mkdir -p "$OUT_DIR/expected"

  cat >"$OUT_DIR/expected/test_01_ok_basics.expected" <<'EOF'
[Miku Says]: [START]
[Miku Says]: == TEST 01 ==
[Miku Says]: 10
[Miku Says]: 35
[Miku Says]: 3
[Miku Says]: 3.5
[Miku Says]: 3
[Miku Says]: miku
[Miku Says]: false
[Miku Says]: true
[Miku Says]: [END]
EOF

  cat >"$OUT_DIR/expected/test_02_ok_control.expected" <<'EOF'
[Miku Says]: == TEST 02 ==
[Miku Says]: 10
[Miku Says]: sum is 10
[Miku Says]: yes
EOF

  cat >"$OUT_DIR/expected/test_03_ok_functions.expected" <<'EOF'
[Miku Says]: == TEST 03 ==
[Miku Says]: 720
[Miku Says]: 13
EOF

  cat >"$OUT_DIR/expected/test_04_ok_structs.expected" <<'EOF'
[Miku Says]: == TEST 04 ==
[Miku Says]: 
[Miku Says]: 0
[Miku Says]: Miku
[Miku Says]: 16
[Miku Says]: 17
[Miku Says]: Hi Miku !
EOF
 
   cat >"$OUT_DIR/expected/test_1.expected" <<'EOF'
[Miku Says]: === START COMPLEX TEST ===
[Miku Says]: factorial(6)
[Miku Says]: 720
[Miku Says]: fib(7)
[Miku Says]: 13
[Miku Says]: gcd_sub(48,18)
[Miku Says]: 6
[Miku Says]: sum_squares(5)
[Miku Says]: 55
[Miku Says]: Countdown
[Miku Says]: 3
[Miku Says]: 2
[Miku Says]: 1
[Miku Says]: Liftoff
[Miku Says]: x positive
[Miku Says]: x > 5
[Miku Says]: float add
[Miku Says]: 3.5
[Miku Says]: === END COMPLEX TEST ===
EOF

}

# ---------- Main ----------

require_file "miku.y"
require_file "miku.l"
require_file "miku_impl.cpp"
require_file "miku_ast.h"

if [[ ! -d "$TEST_DIR" ]]; then
  red "Missing tests/ directory."
  exit 1
fi

compile_lang
write_expected_files

yellow "Running PASS tests..."
run_ok_test "test_01_ok_basics.miku"     "$OUT_DIR/expected/test_01_ok_basics.expected"
run_ok_test "test_1.miku"                "$OUT_DIR/expected/test_1.expected"
run_ok_test "test_02_ok_control.miku"    "$OUT_DIR/expected/test_02_ok_control.expected"
run_ok_test "test_03_ok_functions.miku"  "$OUT_DIR/expected/test_03_ok_functions.expected"
run_ok_test "test_04_ok_structs.miku"    "$OUT_DIR/expected/test_04_ok_structs.expected"

yellow "Running FAIL tests..."
run_fail_test "test_05_fail_unknown_field.miku"
run_fail_test "test_06_fail_unknown_method.miku"
run_fail_test "test_07_fail_undefined_var.miku"
run_fail_test "test_08_fail_redeclare.miku"
run_fail_test "test_09_fail_mixed_expr.miku"
run_fail_test "test_10_fail_assign_type.miku"
run_fail_test "test_11_fail_param_type.miku"
run_fail_test "test_12_fail_let_in_main.miku"
run_fail_test "test_13_fails_let_inside_if.miku"
run_fail_test "test_14_fails_let_inside_while.miku"

green "ALL TESTS PASSED ✅"
yellow "Logs saved in: $OUT_DIR/"
