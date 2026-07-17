import os, pty, time, signal, sys, re

MS = "./minishell"
results = []

def spawn():
    pid, fd = pty.fork()
    if pid == 0:
        os.execv(MS, [MS])
    time.sleep(0.3)
    return pid, fd

def read_all(fd, timeout=1.0):
    out = b""
    end = time.time() + timeout
    while time.time() < end:
        try:
            import select
            r, _, _ = select.select([fd], [], [], 0.1)
            if r:
                chunk = os.read(fd, 4096)
                if not chunk: break
                out += chunk
        except OSError:
            break
    return out.decode(errors="replace")

def check(name, cond, detail=""):
    results.append((name, cond, detail))
    print(("PASS  " if cond else "FAIL  ") + name + ("" if cond else "  | " + detail))

# --- Test 1: ctrl-C at prompt -> new prompt, $? = 130 ---
pid, fd = spawn()
read_all(fd, 0.4)
os.write(fd, b"\x03")            # ctrl-C at empty prompt
time.sleep(0.3)
os.write(fd, b"echo S:$?\n")
out = read_all(fd, 0.8)
check("ctrl-C at prompt -> $?=130", "S:130" in out, repr(out[-120:]))
os.write(fd, b"exit\n"); time.sleep(0.2); os.close(fd); os.waitpid(pid, 0)

# --- Test 2: ctrl-C kills running command ---
pid, fd = spawn()
read_all(fd, 0.4)
os.write(fd, b"sleep 30\n")
time.sleep(0.5)
t0 = time.time()
os.write(fd, b"\x03")            # ctrl-C
time.sleep(0.5)
os.write(fd, b"echo S:$?\n")
out = read_all(fd, 1.0)
dt = time.time() - t0
check("ctrl-C interrupts sleep quickly", dt < 3 and "S:130" in out, f"dt={dt:.1f} out={out[-120:]!r}")
os.write(fd, b"exit\n"); time.sleep(0.2); os.close(fd); os.waitpid(pid, 0)

# --- Test 3: ctrl-\ kills running command with Quit message; nothing at prompt ---
pid, fd = spawn()
read_all(fd, 0.4)
os.write(fd, b"\x1c")            # ctrl-\ at prompt: should do nothing
time.sleep(0.3)
out1 = read_all(fd, 0.3)
os.write(fd, b"sleep 30\n")
time.sleep(0.5)
os.write(fd, b"\x1c")            # ctrl-\ during command
time.sleep(0.5)
os.write(fd, b"echo S:$?\n")
out = read_all(fd, 1.0)
check("ctrl-\\ ignored at prompt", "Quit" not in out1, repr(out1))
check("ctrl-\\ kills cmd, Quit msg, $?=131", "Quit" in out and "S:131" in out, repr(out[-160:]))
os.write(fd, b"exit\n"); time.sleep(0.2); os.close(fd); os.waitpid(pid, 0)

# --- Test 4: ctrl-D exits shell ---
pid, fd = spawn()
read_all(fd, 0.4)
os.write(fd, b"\x04")
time.sleep(0.5)
done, status = os.waitpid(pid, os.WNOHANG)
check("ctrl-D exits shell", done == pid, f"status={status}")
try: os.close(fd)
except OSError: pass

# --- Test 5: ctrl-C during heredoc aborts it ---
pid, fd = spawn()
read_all(fd, 0.4)
os.write(fd, b"cat << STOP\n")
time.sleep(0.4)
os.write(fd, b"partial line\n")
time.sleep(0.2)
os.write(fd, b"\x03")            # ctrl-C in heredoc
time.sleep(0.5)
os.write(fd, b"echo S:$?\n")
out = read_all(fd, 1.0)
check("ctrl-C aborts heredoc, $?=130", "S:130" in out and "partial line\r\npartial line" not in out, repr(out[-200:]))
os.write(fd, b"exit\n"); time.sleep(0.2)
try: os.close(fd); os.waitpid(pid, 0)
except (OSError, ChildProcessError): pass

# --- Test 6: exit prints "exit" interactively ---
pid, fd = spawn()
read_all(fd, 0.4)
os.write(fd, b"exit 7\n")
time.sleep(0.4)
out = read_all(fd, 0.4)
done, status = os.waitpid(pid, 0)
check("interactive 'exit' echo + code 7", "exit" in out and os.WEXITSTATUS(status) == 7, f"out={out!r} code={os.WEXITSTATUS(status)}")
try: os.close(fd)
except OSError: pass

# --- Test 7: ctrl-C in pipeline ---
pid, fd = spawn()
read_all(fd, 0.4)
os.write(fd, b"cat | cat\n")
time.sleep(0.5)
os.write(fd, b"\x03")
time.sleep(0.5)
os.write(fd, b"echo S:$?\n")
out = read_all(fd, 1.0)
check("ctrl-C kills pipeline, $?=130", "S:130" in out, repr(out[-150:]))
os.write(fd, b"exit\n"); time.sleep(0.2)
try: os.close(fd); os.waitpid(pid, 0)
except (OSError, ChildProcessError): pass

fails = sum(1 for _, ok, _ in results if not ok)
print(f"\nPTY tests: {len(results)-fails}/{len(results)} pass")
sys.exit(1 if fails else 0)
