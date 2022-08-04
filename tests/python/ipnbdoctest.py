#!/usr/bin/env python
"""
simple example script for running and testing notebooks.

Usage: `ipnbdoctest.py foo.ipynb [bar.ipynb [...]]`

Each cell is submitted to the kernel, and the outputs are compared
with those stored in the notebook.
"""

# Derived from https://gist.github.com/minrk/2620735

from __future__ import print_function

import os
import sys
import time
import base64
import re
import pprint
import random
from difflib import unified_diff as diff

from collections import defaultdict
try:
    from queue import Empty
except ImportError:
    print('Python 3.x is needed to run this script.')
    sys.exit(77)

import importlib.util
try:
    importlib.util.find_spec('IPython')
except:
    print('IPython is needed to run this script.')
    sys.exit(77)

try:
    from jupyter_client import KernelManager
except ImportError:
    try:
        from IPython.kernel import KernelManager
    except ImportError:
        try:
            from IPython.zmq.blockingkernelmanager \
                import BlockingKernelManager as KernelManager
        except:
            print('IPython is needed to run this script.')
            sys.exit(77)

# Until Debian Stable ships IPython >3.0, we stick to the v3 format.
try:
    from nbformat import v4 as nbformat
except ImportError:
    from IPython.nbformat import v4 as nbformat


def compare_png(a64, b64):
    """compare two b64 PNGs (incomplete)"""
    try:
        import Image
    except ImportError:
        pass
    adata = base64.decodestring(a64)
    bdata = base64.decodestring(b64)
    return True


def canonicalize(s, type, ignores):
    """sanitize a string for comparison.

    fix universal newlines, strip trailing newlines, and normalize likely
    random values (memory addresses and UUIDs)
    """
    if not isinstance(s, str):
        return s
    # normalize newline:
    s = s.replace('\r\n', '\n')

    # ignore trailing newlines (but not space)
    s = s.rstrip('\n')

    # remove hex addresses:
    s = re.sub(r'at 0x[a-f0-9]+', 'object', s)

    # normalize UUIDs:
    s = re.sub(r'[a-f0-9]{8}(\-[a-f0-9]{4}){3}\-[a-f0-9]{12}', 'U-U-I-D', s)

    # class from spot.impl. may be redefined in spot. without notice.
    s = re.sub(r'<spot.impl.', '<spot.', s)

    # normalize graphviz version
    s = re.sub(r'Generated by graphviz version.*', 'VERSION', s)

    # remove Spins verbose output version
    s = re.sub(r'SpinS Promela Compiler.*Written C .* to .*pml.spins.c',
               'SpinS output', s, flags=re.DOTALL)
    s = re.sub(r'Compiled C code to PINS .*pml.spins',
               'SpinS output', s, flags=re.DOTALL)

    # %%file writes `Writing`, or `Overwriting` if the file exists.
    s = re.sub(r'^Overwriting ', 'Writing ', s)

    # SVG generated by graphviz may put note at different positions
    # depending on the graphviz build.  Let's just strip anything that
    # look like a position.
    s = re.sub(r'<path[^/]* d="[^"]*"', '<path', s)
    s = re.sub(r'points="[^"]*"', 'points=""', s)
    s = re.sub(r'x="[0-9.-]+"', 'x=""', s)
    s = re.sub(r'y="[0-9.-]+"', 'y=""', s)
    s = re.sub(r'width="[0-9.]+pt"', 'width=""', s)
    s = re.sub(r'height="[0-9.]+pt"', 'height=""', s)
    s = re.sub(r'viewBox="[0-9 .-]*"', 'viewbox=""', s)
    s = re.sub(r'transform="[^"]*"', 'transform=""', s)
    s = re.sub(r'id="edge[^"]*"', 'id="edge"', s)
    s = re.sub(r'text-anchor="[^"]*"', 'text-anchor=""', s)
    # The following patterns from graphviz 2.40 are rewritten as they used to
    # be in 2.38.
    s = re.sub(r'"#000000"', '"black"', s)
    s = re.sub(r'"#ffffff"', '"white"', s)
    s = re.sub(r'"#ffff00"', '"yellow"', s)
    s = re.sub(r'"#00ffff"', '"cyan"', s)
    s = re.sub(r'"#ffc0cb"', '"pink"', s)
    s = re.sub(r'"#00ff00"', '"green"', s)
    s = re.sub(r'"#ff0000"', '"red"', s)
    s = re.sub(r'"#c0c0c0"', '"grey"', s)
    s = re.sub(r'"#ffa500"', '"orange"', s)
    s = re.sub(r'"gray"', '"grey"', s)
    s = re.sub(r' fill="black"', '', s)
    s = re.sub(r' stroke="transparent"', ' stroke="none"', s)
    s = re.sub(r'><title>', '>\n<title>', s)
    # At some point Fedora changed the default font-familly from
    # Times,serif to Times-Roman.
    s = re.sub(r'"Times[^"]+"', '"Times"', s)
    # tooltips with a ", " are likely to have \n which was not
    # well supported by 2.38.
    s = re.sub(r'<a xlink:title=".*?, .*?">\n', '<a xlink:title="...">\n', s,
               flags=re.DOTALL)
    # Different Pandas versions produce different CSS styles (when there is a
    # style).
    s = re.sub(r'<style[ a-z]*>.*</style>\n', '', s, flags=re.DOTALL)
    # Table that contains enc.user are log from the SAT-solver.  They contain
    # timing result we cannot compare between runs.
    s = re.sub(r'<table.*dataframe.*?enc.user.*?</table>', '<table></table>', s,
               flags=re.DOTALL)

    for n, p in enumerate(ignores):
        s = re.sub(p, 'IGN{}'.format(n), s)
    return s


def canonical_dict(dict, ignores):
    '''Neutralize gratuitous differences in a Jupyter dictionary.

    For instance, neutralize different Graphviz layouts in SVG.
    '''

    if 'text' in dict:
        dict['text'] = canonicalize(dict['text'], 'text', ignores)

    if 'data' in dict:
        d = dict['data']
        if "text/html" in d and "text/plain" in d:
            del d["text/plain"]
        for k in d:
            d[k] = canonicalize(d[k], k, ignores)

    if ('ename' in dict and
            dict['ename'] == 'SystemExit' and dict['evalue'] == '77'):
        # sys.exit(77) is used to Skip the test.
        sys.exit(77)

    if 'ename' in dict and dict['ename'] == 'CalledProcessError':
        # CalledProcessError message has a final dot in Python 3.6
        dict['evalue'] = \
            re.sub(r"(' returned non-zero exit status \d+)\.", r'\1',
                   dict['evalue'])

    if ('ename' in dict and dict['ename'] == 'ModuleNotFoundError' and
            'pandas' in dict['evalue']):
        sys.exit(77)

    if 'transient' in dict:
        del dict['transient']
    if 'execution_count' in dict:
        del dict['execution_count']
    if 'traceback' in dict:
        del dict['traceback']
    return dict


def keep_dict(dict):
    # pandas imports Matplotlib, which can display a message about building the
    # the font cache if it does not exist, and if doing so takes more than 5
    # seconds.   Just ignore those.
    if ('name' in dict and dict['name'] == 'stderr' and
        type(dict['text']) is str and
        dict['text'].startswith("Matplotlib is building the font cache")):
        return False
    return True


def compare_outputs(ref, test, ignores=[]):
    '''Check that two lists of outputs are equivalent and report the
    result.'''

    cref = [canonical_dict(d, ignores) for d in ref if keep_dict(d)]
    ctest = [canonical_dict(d, ignores) for d in test if keep_dict(d)]

    ok = True

    if len(cref) != len(ctest):
        print("output length mismatch (expected {}, got {})".format(
            len(cref), len(ctest)))
        ok = False
    # There can be several outputs.  For instance wnen the cell both
    # prints a result (goes to "stdout") and displays an automaton
    # (goes to "data").
    exp = pprint.pformat(cref, width=132)
    eff = pprint.pformat(ctest, width=132)
    if exp[:-1] != '\n':
        exp += '\n'
    if eff[:-1] != '\n':
        eff += '\n'
    if exp == eff:
        return ok
    else:
        print(''.join(diff(exp.splitlines(1), eff.splitlines(1),
                           fromfile='expected', tofile='effective')))
        return False


def _wait_for_ready_backport(kc):
    """Backport BlockingKernelClient.wait_for_ready from IPython 3"""
    # Wait for kernel info reply on shell channel
    kc.kernel_info()
    while True:
        msg = kc.get_shell_msg(block=True, timeout=30)
        if msg['msg_type'] == 'kernel_info_reply':
            break
    # Flush IOPub channel
    while True:
        try:
            msg = kc.get_iopub_msg(block=True, timeout=1)
        except Empty:
            break


def run_cell(kc, cell):
    kc.execute(cell.source)
    outs = []

    while True:
        try:
            msg = kc.get_iopub_msg(timeout=1)
        except Empty:
            if not kc.is_alive():
                raise RuntimeError("Kernel died")
            continue

        msg_type = msg['msg_type']
        content = msg['content']

        if msg_type == 'status' and content['execution_state'] == 'idle':
            break
        if msg_type in ('status', 'pyin', 'execute_input',
                        'comm_open', 'comm_msg'):
            continue
        if msg_type == 'stream':
            if 'Widget' in content['text']:
                continue
            # If the last stream had the same name, then outputs are
            # appended.
            if outs:
                last = outs[-1]
                if last['output_type'] == 'stream' and \
                   last['name'] == content['name']:
                    last['text'] += content['text']
                    continue
        elif msg_type == 'clear_output':
            outs = []
            continue

        content['output_type'] = msg_type
        outs.append(content)
    # Flush shell channel
    while True:
        try:
            kc.get_shell_msg(timeout=0.1)
        except Empty:
            if not kc.is_alive():
                raise RuntimeError("Kernel died")
            break
    return outs


def test_notebook(ipynb):
    with open(ipynb, encoding='utf-8') as f:
        nb = nbformat.reads_json(f.read())
    km = KernelManager()
    # Do not save the history to disk, as it can yield spurious lock errors.
    # See https://github.com/ipython/ipython/issues/2845
    km.start_kernel(extra_arguments=['--HistoryManager.hist_file=:memory:',
                                     '--quiet'])

    kc = km.client()
    kc.start_channels()

    try:
        kc.wait_for_ready(timeout=30)
    except AttributeError:
        _wait_for_ready_backport(kc)

    successes = 0
    failures = 0
    errors = 0
    for i, cell in enumerate(nb.cells):
        if cell.cell_type != 'code' or cell.source.startswith('%timeit'):
            continue
        try:
            outs = run_cell(kc, cell)
        except Exception as e:
            print("failed to run cell:", repr(e))
            print(cell.input)
            errors += 1
            continue

        failed = False
        if not compare_outputs(cell.outputs, outs):
            failed = True
        print("cell %d: " % i, end="")
        if failed:
            print("FAIL")
            failures += 1
        else:
            print("OK")
            successes += 1

    print("tested notebook %s" % ipynb)
    print("    %3i cells successfully replicated" % successes)
    if failures:
        print("    %3i cells mismatched output" % failures)
    if errors:
        print("    %3i cells failed to complete" % errors)
    kc.stop_channels()
    km.shutdown_kernel()
    del km
    if failures | errors:
        sys.exit(1)


if __name__ == '__main__':
    for ipynb in sys.argv[1:]:
        tries=3
        while tries:
            print("testing %s" % ipynb)
            try:
                test_notebook(ipynb)
                break
            except RuntimeError as e:
                # If the Kernel dies, try again.  It seems we have spurious
                # failures when multiple instances of jupyter start in parallel.
                if 'Kernel died' in str(e):
                    tries -= 1
                    if tries:
                        s = random.randint(1, 5)
                        print("trying again in", s, "seconds...")
                        time.sleep(s)
                else:
                    raise e
