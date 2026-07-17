#!/bin/bash
# torture.sh — the dirty tests evaluators use to break minishell, not to grade it.
# Usage: bash tests/torture.sh ./minishell
# Compares minishell vs bash output where bash is a stable reference,
# and uses fixed expectations where bash versions disagree.

MS=$(realpath "${1:-./minishell}")
[ -x "$MS" ] || { echo "usage: bash tests/torture.sh ./minishell"; exit 1; }
TMP=$(mktemp -d); trap 'rm -rf "$TMP"' EXIT
PASS=0; FAIL=0; FAILED_TESTS=()

filter() { sed -e '/^minishell\$ /d' -e '/^> /d' -e 's/minishell\$ .*$//'; }

vs_bash() { # $1 name, $2 script — full stdout diff vs bash
	rm -rf "$TMP/run"; mkdir "$TMP/run"; cd "$TMP/run" || exit 1
	printf '%s\n' "$2" | timeout 5 "$MS" 2>/dev/null | filter > "$TMP/ms_out"
	rm -rf "$TMP/run"; mkdir "$TMP/run"; cd "$TMP/run" || exit 1
	printf '%s\n' "$2" | timeout 5 bash 2>/dev/null > "$TMP/bash_out"
	cd "$TMP" || exit 1
	if diff -q ms_out bash_out > /dev/null; then
		PASS=$((PASS+1)); echo "PASS  $1"
	else
		FAIL=$((FAIL+1)); FAILED_TESTS+=("$1")
		echo "FAIL  $1"
		echo "      mine: $(tr '\n' '|' < ms_out)"
		echo "      bash: $(tr '\n' '|' < bash_out)"
	fi
}

expect() { # $1 name, $2 script, $3 expected stdout
	cd "$TMP" || exit 1
	printf '%s\n' "$2" | timeout 5 "$MS" 2>/dev/null | filter > ms_out
	printf '%s\n' "$3" > want
	if diff -q ms_out want > /dev/null; then
		PASS=$((PASS+1)); echo "PASS  $1"
	else
		FAIL=$((FAIL+1)); FAILED_TESTS+=("$1")
		echo "FAIL  $1"
		echo "      mine: $(tr '\n' '|' < ms_out)"
		echo "      want: $(tr '\n' '|' < want)"
	fi
}

expect_code() { # $1 name, $2 script, $3 expected process exit code
	cd "$TMP" || exit 1
	printf '%s\n' "$2" | timeout 5 "$MS" > /dev/null 2>&1
	local code=$?
	if [ "$code" = "$3" ]; then PASS=$((PASS+1)); echo "PASS  $1 (code=$code)"
	else FAIL=$((FAIL+1)); FAILED_TESTS+=("$1"); echo "FAIL  $1 mine=$code want=$3"; fi
}

echo "============ QUOTE HELL ============"
vs_bash 'empty quote soup'          'echo ""'"''"'""'"''"'x'
vs_bash 'dollar glued to quotes'    'echo "$"USER "$""$"'
vs_bash 'quotes hiding operators'   'echo "a|b" "c>d" "e<f" "&&"'
vs_bash 'apostrophe in dquotes'     'echo "it'"'"'s fine: $HOME"'
vs_bash 'squotes freeze everything' "echo '\$HOME | > << \$? \"x\"'"
vs_bash 'alternating adjacency'     'echo x""y'"''"'z"a"b'
vs_bash 'empty arg positioning'     'echo start "" end
echo a "" b'
vs_bash 'var value not re-parsed'   'export X="ls -la | wc"
echo $X'
vs_bash 'no re-expansion of value'  "export X='\$USER'
echo \$X"
vs_bash 'multiple spaces preserved' 'export W="a  b   c"
echo "$W"'

echo "============ EXPANSION EDGE ============"
vs_bash 'dollar alone / trailing'   'echo $ a$ "$"'
vs_bash 'status glue everywhere'    'echo $?extra"$?"'"'"'$?'"'"''
vs_bash 'triple var concat'         'echo $HOME$HOME$HOME'
vs_bash 'digit swallow'             'echo $1abc $9def'
vs_bash 'brace expansion'           'export E=mid
echo a${E}z ${HOME} "${E}"'
vs_bash 'brace literal in squotes'  "echo '\${HOME}'"
vs_bash 'undefined vanishes'        'echo a$ZZNOPEb c $ZZNOPE d'
vs_bash 'hash inside value'         'export Q="value with # hash"
echo $Q "$Q"'

echo "============ REDIRECTION ABUSE ============"
vs_bash 'args after redir merge'    'echo a > mid b c
cat mid'
vs_bash 'triple out last wins'      'echo hi > f1 > f2 > f3
cat f3
cat f1 f2'
vs_bash 'first in-redir fails'      'cat < nofile < /etc/hostname
echo st=$?'
vs_bash 'redir before command'      '< /etc/hostname cat'
vs_bash 'append twice'              'echo 1 >> ap
echo 2 >> ap
cat ap'
vs_bash 'redir target from var'     'export F=vfile
echo content > $F
cat vfile'
expect 'syntax >>> rejected'        'echo hi >>> f
echo alive=$?' 'alive=2'
expect 'redir into pipe rejected'   'echo > | cat
echo alive=$?' 'alive=2'

echo "============ HEREDOC ABUSE ============"
vs_bash 'double heredoc last wins'  'cat << A << B
ignored
A
shown
B'
vs_bash 'delim never expanded'      'cat << $USER
body $USER expands though
$USER'
vs_bash 'heredoc beats pipe stdin'  'echo piped | cat << HD
from heredoc
HD'
vs_bash 'empty string delimiter'    'cat << ""
body line

echo after=$?'
vs_bash 'heredoc plus file: order'  'echo filecontent > hf
cat << HD < hf
heredoc ignored
HD'
vs_bash 'file then heredoc: order'  'echo filecontent > hf
cat < hf << HD
file ignored
HD'
vs_bash 'status expands in body'    'false
cat << HD
code=$?
HD'

echo "============ PIPE TORTURE ============"
vs_bash 'sigpipe no garbage'        'yes | head -n 1
echo st=$?'
vs_bash '10 stage pipeline'         'echo a | cat | cat | cat | cat | cat | cat | cat | cat | cat'
vs_bash 'exit inside pipe ignored'  'exit | echo survives
echo st=$?'
vs_bash 'pipe status is last'       'echo hi | exit 5
echo st=$?'
vs_bash 'cd in pipe no effect'      'pwd
cd / | cat
pwd'
vs_bash 'big data through pipe'     'python3 -c '"'"'print("A"*100000)'"'"' | wc -c'
vs_bash 'mid-pipe cmd not found'    'echo a | zznope | wc -l
echo st=$?'

echo "============ PATH & EXEC SABOTAGE ============"
vs_bash 'dotdot is not a command'   '..
echo st=$?'
vs_bash 'permission denied 126'     'echo x > deny
chmod 000 deny
./deny
echo st=$?'
vs_bash 'non-exec with slash 126'   '/etc/hostname
echo st=$?'
vs_bash 'PATH to nowhere'           'export PATH=/nowhere
ls
echo st=$?'
expect 'empty cmd is 127'           '""
echo st=$?' 'st=127'
expect 'spaces cmd is 127'          '"   "
echo st=$?' 'st=127'

echo "============ BUILTIN GARBAGE INPUT ============"
vs_bash 'export chain'              'export A=1 B=2 C=3
echo $A$B$C'
vs_bash 'export =bad'               'export =bad
echo st=$?'
vs_bash 'export digit-lead'         'export 1x=no
echo st=$?'
vs_bash 'export B=C inside value'   'export A=B=C
echo $A'
vs_bash 'unset then reuse'          'export A=x
unset A A A
echo [$A]'
vs_bash 'cd file not dir'           'touch plainfile
cd plainfile
echo st=$?'
vs_bash 'echo the dashes'           'echo - -- -x -n-'
expect_code 'exit numeric check first' 'exit hello world' 2
expect_code 'exit overflow by one'  'exit 9223372036854775808' 2
expect_code 'exit underflow'        'exit -9223372036854775809' 2
expect_code 'exit LLONG_MIN ok'     'exit -9223372036854775808' 0

echo "============ HOSTILE STATE (evaluator specials) ============"
hostile() { # $1 name, $2 command producing output, $3 grep pattern expected
	cd "$TMP" || exit 1
	out=$(eval "$2" 2>&1)
	if echo "$out" | grep -q "$3"; then PASS=$((PASS+1)); echo "PASS  $1"
	else FAIL=$((FAIL+1)); FAILED_TESTS+=("$1"); echo "FAIL  $1"; echo "      got: $(echo "$out" | head -3 | tr '\n' '|')"; fi
}
hostile 'env -i: PWD recreated'    'printf "env\n" | env -i "$MS"' '^PWD='
hostile 'env -i: SHLVL created'    'printf "env\n" | env -i "$MS"' '^SHLVL=1'
hostile 'env -i: export works'     'printf "export N=v\nenv\n" | env -i "$MS"' '^N=v'
hostile 'env -i: no PATH -> 127'   'printf "ls\necho st=\$?\n" | env -i "$MS"' 'st=127'
hostile 'deleted cwd: no segfault' 'printf "mkdir zz\ncd zz\nrm -rf ../zz\npwd\ncd ..\necho ok=\$?\n" | "$MS"' 'ok=0'
hostile 'unset PATH: builtins ok'  'printf "unset PATH\necho alive\npwd\n" | "$MS"' 'alive'
hostile 'unset OLDPWD: cd - errs'  'printf "unset OLDPWD\ncd -\necho st=\$?\n" | "$MS"' 'st=1'
expect_code 'argv ignored, exit 3' 'exit 3' 3
cd "$TMP" || exit 1
"$MS" <&- > /dev/null 2>&1
[ "$?" = "0" ] && { PASS=$((PASS+1)); echo "PASS  closed stdin: clean exit"; } || { FAIL=$((FAIL+1)); FAILED_TESTS+=("closed stdin"); echo "FAIL  closed stdin"; }
printf './minishell_nested_test_placeholder\n' > /dev/null
printf '%s\n%s\n' "$MS" 'exit 42' | "$MS" > /dev/null 2>&1
[ "$?" = "42" ] && { PASS=$((PASS+1)); echo "PASS  nested shell bubbles exit 42"; } || { FAIL=$((FAIL+1)); FAILED_TESTS+=("nested bubble"); echo "FAIL  nested shell bubbles exit 42"; }

echo "============ WHITESPACE & LENGTH ============"
vs_bash 'whitespace-only lines'     '   
	
echo survived'
vs_bash 'monstrous single arg'      'echo aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'
vs_bash 'many args'                 'echo a b c d e f g h i j k l m n o p q r s t u v w x y z 1 2 3 4 5 6 7 8 9 0'

echo ""
echo "==========================================="
echo "TOTAL: $((PASS+FAIL))   PASS: $PASS   FAIL: $FAIL"
if [ "$FAIL" -gt 0 ]; then
	echo "Failed:"; for t in "${FAILED_TESTS[@]}"; do echo "  - $t"; done
fi

cat << 'MANUAL'

============ MANUAL-ONLY (needs a real terminal) ============
These cannot be scripted reliably — run them by hand:

  ./minishell
  sleep 5            then ctrl-C        -> prompt back instantly, echo $? = 130
  sleep 5            then ctrl-\        -> "Quit (core dumped)", echo $? = 131
  cat                then ctrl-C        -> cat dies, shell survives
  cat                then ctrl-D        -> EOF to cat (not to shell!), shell survives
  cat << EOF         then ctrl-C        -> heredoc aborted, echo $? = 130
  type text, then ctrl-C at prompt      -> fresh prompt, buffer discarded, $? = 130
  ctrl-\ at empty prompt                -> absolutely nothing happens
  ctrl-D at empty prompt                -> prints "exit", shell quits
  ./minishell inside ./minishell (x3)   -> ctrl-C only affects innermost; exit unwinds one level
  cat | cat | cat    then ctrl-C        -> whole pipeline dies, one prompt (not three)
  spam ctrl-C 10 times fast             -> 10 clean prompts, no crash, no double prompt

As a NORMAL user (not root — root bypasses permissions):
  mkdir locked && chmod 000 locked
  cd locked                             -> "Permission denied", $? = 1, no crash
  chmod 755 locked && rmdir locked
  env -i ./minishell                    -> then: env shows PWD and SHLVL=1; ls -> 127;
                                           export/unset/cd/pwd/echo all still work

============ KNOWN OUT-OF-SCOPE (be ready to SAY it, not fix it) ============
An evaluator may try these; they are NOT in the mandatory subject:
  cd ~               tilde expansion       -> not required (cd with no arg = HOME is)
  echo $(ls) / `ls`  command substitution  -> not required, stays literal
  echo a && echo b   logical operators     -> bonus only
  echo *             wildcards             -> bonus only
  echo \$HOME        backslash escaping    -> explicitly excluded by subject
  cmd1; cmd2         semicolons            -> explicitly excluded by subject
  A="a b"; echo $A   word splitting        -> known limitation: stays one arg
  .                  source builtin        -> not required; we return 127
MANUAL