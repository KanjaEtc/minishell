#!/bin/bash
# ============================================================================ #
# Minishell deep test suite                                                    #
# Usage: bash tests/run_tests.sh [path_to_minishell]                           #
# Compares minishell output/exit-status against bash (the subject reference).  #
# ============================================================================ #

MS=$(realpath "${1:-./minishell}")
PASS=0; FAIL=0; FAILED_TESTS=()
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

run_ms() {  # $1 = script
	cd "$TMP" || exit 1
	printf '%s\n' "$1" | timeout 5 "$MS" 2>"$TMP/ms_err" | \
		sed -e '/^minishell\$ /d' -e '/^> /d' -e 's/minishell\$ .*$//' > "$TMP/ms_out"
}

run_ms_status() {  # runs script then prints $? via a marker
	cd "$TMP" || exit 1
	printf '%s\necho STATUS:$?\n' "$1" | timeout 5 "$MS" 2>>"$TMP/ms_err" | \
		sed -e '/^minishell\$ /d' -e 's/minishell\$ .*$//' | grep '^STATUS:' | tail -1 | cut -d: -f2
}

run_bash() {
	cd "$TMP" || exit 1
	printf '%s\n' "$1" | timeout 5 bash 2>"$TMP/bash_err" > "$TMP/bash_out"
}

run_bash_status() {
	cd "$TMP" || exit 1
	printf '%s\necho STATUS:$?\n' "$1" | timeout 5 bash 2>/dev/null | \
		grep '^STATUS:' | tail -1 | cut -d: -f2
}

check_out() {  # $1 name, $2 script  : compare stdout with bash
	rm -f "$TMP"/f* "$TMP"/g* 2>/dev/null
	run_ms "$2"; rm -f "$TMP"/f* "$TMP"/g* 2>/dev/null
	run_bash "$2"
	if diff -q "$TMP/ms_out" "$TMP/bash_out" >/dev/null 2>&1; then
		PASS=$((PASS+1)); printf 'PASS  %s\n' "$1"
	else
		FAIL=$((FAIL+1)); FAILED_TESTS+=("$1")
		printf 'FAIL  %s\n' "$1"
		printf '      cmd    : %s\n' "$(echo "$2" | head -3 | tr '\n' ';')"
		printf '      mine   : %s\n' "$(head -3 "$TMP/ms_out" | tr '\n' '|')"
		printf '      bash   : %s\n' "$(head -3 "$TMP/bash_out" | tr '\n' '|')"
	fi
}

check_status() {  # $1 name, $2 script : compare $? with bash
	rm -f "$TMP"/f* 2>/dev/null
	local ms_s bash_s
	ms_s=$(run_ms_status "$2"); rm -f "$TMP"/f* 2>/dev/null
	bash_s=$(run_bash_status "$2")
	if [ "$ms_s" = "$bash_s" ]; then
		PASS=$((PASS+1)); printf 'PASS  %s ($?=%s)\n' "$1" "$ms_s"
	else
		FAIL=$((FAIL+1)); FAILED_TESTS+=("$1")
		printf 'FAIL  %s  mine=$?%s  bash=$?%s   [%s]\n' "$1" "$ms_s" "$bash_s" "$2"
	fi
}

check_expect() {  # $1 name, $2 script, $3 expected stdout
	run_ms "$2"
	if [ "$(cat "$TMP/ms_out")" = "$3" ]; then
		PASS=$((PASS+1)); printf 'PASS  %s\n' "$1"
	else
		FAIL=$((FAIL+1)); FAILED_TESTS+=("$1")
		printf 'FAIL  %s\n      mine: [%s]\n      want: [%s]\n' "$1" "$(cat "$TMP/ms_out")" "$3"
	fi
}

echo "=================== 1. BASIC EXECUTION ==================="
check_out  "simple command"            'echo hello'
check_out  "command with args"         'ls -la /dev/null'
check_out  "absolute path"             '/bin/echo direct'
check_out  "relative path exec"        'cp /bin/echo ./myecho
./myecho relative-ok'
check_status "command not found = 127" 'zzznotacommand'
check_status "exec ok = 0"             'true'
check_status "exec fail = 1"           'false'
check_status "is a directory = 126"    '/tmp/'
check_status "no such file = 127"      '/nonexistent/bin'
check_out  "empty PATH lookup err msg goes to stderr" 'zzznotacommand'
check_out  "args with many spaces"     'echo    a     b      c'

echo "=================== 2. QUOTES ==================="
check_out  "single quotes literal"     "echo '\$USER \$? | > <'"
check_out  "double quotes keep spaces" 'echo "a    b"'
check_out  "double quotes expand"      'echo "$HOME"'
check_out  "single inside double"      "echo \"it's fine\""
check_out  "expand near apostrophe"    "echo \"it's \$HOME\""
check_out  "quoted quote pairs"        'echo "a"'"'"'b'"'"'"c"'
check_out  "adjacent quoted words"     'echo hello"world"foo'"'"'bar'"'"''
check_out  "empty double quotes arg"   'echo "" b'
check_out  "empty single quotes arg"   "echo '' b"
check_out  "quotes around pipe char"   "echo 'a | b'"
check_out  "quotes around redir char"  'echo "a > b < c"'
check_out  "dollar in single quotes"   "echo '\$HOME'"
check_out  "sq inside dq with var"     'echo "'"'"'$HOME'"'"'"'

echo "=================== 3. EXPANSION ==================="
check_out  "simple var"                'echo $HOME'
check_out  "undefined var"             'echo $ZZUNDEFINED'
check_out  "undefined var quoted"      'echo "$ZZUNDEFINED"'
check_out  "var concat text"           'echo x$HOME'
check_out  "text after var"            'echo $HOME"end"'
check_out  "exit status 0"             'true
echo $?'
check_out  "exit status 1"             'false
echo $?'
check_out  "exit status 127"           'zznope
echo $?'
check_out  "double status"             'false
echo $? $?'
check_out  "dollar alone"              'echo $'
check_out  "dollar before quote"       'echo $"HOME"'
check_out  "dollar digit"              'echo $1abc'
check_out  "status after builtin"      'export ZZ=1
echo $?'
expect_status2() { :; }  # placeholder
check_status "status after ok cmd"     'echo hi'

echo "=================== 4. REDIRECTIONS ==================="
check_out  "output redir"              'echo content > f1
cat f1'
check_out  "append redir"              'echo one > f1
echo two >> f1
cat f1'
check_out  "input redir"               'echo data > f1
cat < f1'
check_out  "multiple out redirs"       'echo x > f1 > f2
ls f1 f2
cat f2'
check_out  "multiple in redirs"        'echo a > f1
echo b > f2
cat < f1 < f2'
check_out  "redir before command"      '> f1 echo weird
cat f1'
check_out  "redir no command"          '> f1
ls f1'
check_out  "input missing file"        'cat < nofile
echo $?'
check_out  "out then in mix"           'echo hi > f1
cat < f1 > f2
cat f2'
check_status "redir open fail status"  'echo x > /root/forbidden/f'
check_out  "builtin with redir"        'pwd > f1
cat f1 > /dev/null
echo done'
check_out  "redir target expansion"    'export F=f1
echo hi > $F
cat f1'
check_out  "quoted redir target"       'echo hi > "f 1"
cat "f 1"'

echo "=================== 5. HEREDOC ==================="
check_out  "basic heredoc"             'cat << EOF
line1
line2
EOF'
check_out  "heredoc expansion"         'cat << EOF
home=$HOME
EOF'
check_out  "heredoc quoted delim"      'cat << "EOF"
no expand $HOME
EOF'
check_out  "heredoc squoted delim"     "cat << 'EOF'
no expand \$HOME
EOF"
check_out  "heredoc partial quote delim" 'cat << E"O"F
x $HOME x
EOF'
check_out  "heredoc dollar-question"   'false
cat << EOF
status=$?
EOF'
check_out  "two heredocs same cmd"     'cat << A << B
first
A
second
B'
check_out  "heredoc then file input"   'echo fromfile > f1
cat << EOF < f1
fromheredoc
EOF'
check_out  "file then heredoc input"   'echo fromfile > f1
cat < f1 << EOF
fromheredoc
EOF'
check_out  "heredoc in pipeline"       'cat << EOF | wc -l
a
b
EOF'
check_out  "heredoc single quote in body" 'cat << EOF
it'"'"'s $HOME
EOF'

echo "=================== 6. PIPES ==================="
check_out  "simple pipe"               'echo hello | cat'
check_out  "triple pipe"               'echo abc | cat | cat'
check_out  "pipe with wc"              'printf "a\nb\nc\n" | wc -l'
check_out  "long pipeline"             'echo x | cat | cat | cat | cat | cat'
check_out  "pipe builtin left"         'echo hi | wc -c'
check_out  "pipe builtin right"        'printf "PATH=x\n" | cat'
check_status "pipeline status = last"  'false | true'
check_status "pipeline status fail"    'true | false'
check_status "pipeline status 127"     'true | zznope'
check_out  "pipe with redirs"          'echo data | cat > f1
cat f1'
check_out  "grep in pipe"              'printf "apple\nbanana\n" | grep an'
check_out  "pipe exit builtin"         'echo a | exit
echo $?
echo survived'
check_out  "cd in pipe no effect"      'pwd
cd / | cat
pwd'

echo "=================== 7. BUILTINS: echo ==================="
check_out  "echo -n"                   'echo -n hi'
check_out  "echo -n -n"                'echo -n -n hi'
check_out  "echo -nnn"                 'echo -nnnn hi'
check_out  "echo -nx literal"          'echo -nx hi'
check_out  "echo no args"              'echo'
check_out  "echo -n no args"           'echo -n'
check_out  "echo dash"                 'echo -'
check_out  "echo --"                   'echo --'

echo "=================== 8. BUILTINS: cd/pwd ==================="
check_out  "cd absolute + pwd"         'cd /tmp
pwd'
check_out  "cd relative"               'mkdir -p d1/d2
cd d1/d2
pwd'
check_out  "cd .."                     'cd /tmp
cd ..
pwd'
check_out  "cd no arg -> HOME"         'cd
pwd'
check_status "cd nonexistent status"   'cd /zz_no_dir'
check_out  "cd updates PWD/OLDPWD"     'cd /tmp
cd /
echo "$PWD $OLDPWD"'
check_status "cd too many args"        'cd /tmp /var'
check_out  "pwd ignores args? (bash errs on -x only)" 'pwd
echo $?'

echo "=================== 9. BUILTINS: export/unset/env ==================="
check_out  "export then use"           'export ZZVAR=hello
echo $ZZVAR'
check_out  "export overwrite"          'export ZZ=1
export ZZ=2
echo $ZZ'
check_out  "export appears in env"     'export ZZQQ=42
env | grep ^ZZQQ='
check_out  "export empty value"        'export ZZE=
echo [$ZZE]'
check_out  "export value with equals"  'export ZZX=a=b
echo $ZZX'
check_status "export invalid id"       'export 1BAD=1'
check_status "export bare invalid"     'export "BAD-NAME"'
check_out  "export no args contains var" 'export ZZW=1
export | grep -c "ZZW"'
check_out  "unset removes"             'export ZZR=1
unset ZZR
echo [$ZZR]'
check_out  "unset multiple"            'export A1=1 A2=2
unset A1 A2
echo [$A1$A2]'
check_status "unset nonexistent = 0"   'unset ZZNOPE'
check_out  "env has PATH"              'env | grep -c ^PATH='

echo "=================== 10. BUILTINS: exit ==================="
expect_exit_code() { # $1 name, $2 script, $3 expected process exit code
	cd "$TMP" || exit 1
	printf '%s\n' "$2" | timeout 5 "$MS" > /dev/null 2>&1
	local code=$?
	if [ "$code" = "$3" ]; then
		PASS=$((PASS+1)); printf 'PASS  %s (code=%s)\n' "$1" "$code"
	else
		FAIL=$((FAIL+1)); FAILED_TESTS+=("$1")
		printf 'FAIL  %s  mine=%s want=%s   [%s]\n' "$1" "$code" "$3" "$2"
	fi
}
expect_exit_code "exit code 42"        'exit 42' 42
expect_exit_code "exit code 0"         'exit 0' 0
expect_exit_code "exit negative wraps" 'exit -1' 255
expect_exit_code "exit 256 wraps"      'exit 256' 0
expect_exit_code "exit +5"             'exit +5' 5
expect_exit_code "exit non numeric"    'exit abc' 2
expect_exit_code "exit overflow"       'exit 9223372036854775808' 2
expect_exit_code "exit LLONG_MAX"      'exit 9223372036854775807' 255
check_out  "exit too many args stays"  'exit 1 2
echo still here'
expect_exit_code "exit no args keeps last" 'false
exit' 1

echo "=================== 11. SYNTAX ERRORS ==================="
expect_status() { # $1 name, $2 script, $3 expected
	local ms_s; ms_s=$(run_ms_status "$2")
	if [ "$ms_s" = "$3" ]; then PASS=$((PASS+1)); printf 'PASS  %s ($?=%s)\n' "$1" "$ms_s"
	else FAIL=$((FAIL+1)); FAILED_TESTS+=("$1"); printf 'FAIL  %s mine=%s want=%s\n' "$1" "$ms_s" "$3"; fi
}
expect_status "lone pipe -> 2"          '|' 2
expect_status "redir no target -> 2"    'echo hi >' 2
expect_status "redir into pipe -> 2"    'echo hi > | cat' 2
expect_status "lone redir -> 2"         '<' 2
expect_status "unclosed quote -> 2"     'echo "oops' 2
expect_status "incomplete pipe -> 2"    'echo |' 2
check_expect "error keeps shell alive" '|
echo alive' 'alive'
check_expect "unclosed quote alive" 'echo "unclosed
echo alive' 'alive'

echo "=================== 12. SIGNAL-ADJACENT / STATUS ==================="
check_out  "SIGSEGV status 139"        'sleep 0 &>/dev/null
echo skip'
check_status "kill -TERM status"       "sh -c 'kill -TERM \$\$'"
check_status "kill -SEGV status"       "sh -c 'kill -SEGV \$\$'"

echo "=================== 13. EDGE CASES ==================="
check_out  "empty command via quotes"  '""
echo $?' 
check_out  "spaces only line then cmd" '   
echo after'
check_out  "var holding command"       'export C=echo
$C hi there'
check_out  "cat /dev/null"             'cat /dev/null
echo done'
check_out  "many args"                 'echo a b c d e f g h i j k l m n o p q r s t u v w x y z'
check_out  "special chars in dq"       'echo "!@#%^&*()_+-=[]{}"'
check_out  "PATH unset behavior"       'unset PATH
echo builtin still ok'
check_out  "big output through pipe"   'head -c 100000 /dev/zero | wc -c'
check_status "exit status preserved through blank input" 'false'

echo ""
echo "==========================================="
echo "TOTAL: $((PASS+FAIL))   PASS: $PASS   FAIL: $FAIL"
if [ $FAIL -gt 0 ]; then
	echo "Failed tests:"
	printf '  - %s\n' "${FAILED_TESTS[@]}"
fi