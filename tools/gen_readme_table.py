#!/usr/bin/env python3
"""Regenerate the module table in README.md between the table markers.

Columns: rank (by direct dependents in the BCR, boost.* excluded), module, direct dependents,
version pinned in MODULE.bazel, packages in this repo that reference the module, and a note
from tools/module_notes.json (used for modules deliberately left out).
"""
import csv, json, pathlib, re, subprocess

root = pathlib.Path(__file__).resolve().parent.parent
TOP_N = 60
rows = list(csv.DictReader((root / "docs/bcr_direct_dependents.csv").open()))[:TOP_N]
mod_text = (root / "MODULE.bazel").read_text()
versions = dict(re.findall(r'bazel_dep\(name = "([^"]+)", version = "([^"]+)"', mod_text))
notes = json.loads((root / "tools/module_notes.json").read_text())
files = subprocess.run(["git", "ls-files"], cwd=root, capture_output=True, text=True).stdout.split()
build_files = [f for f in files if f.endswith((".bazel", ".bzl", "BUILD")) and not f.startswith("MODULE")]

def packages_using(mod):
    pat = re.compile(r'@' + re.escape(mod) + r'(?=[/"+ ])')
    pkgs = set()
    for f in build_files:
        if pat.search((root / f).read_text()):
            top = f.split("/")[0] if "/" in f else "(root)"
            pkgs.add(top)
    return sorted(pkgs)

lines = ["| # | module | direct dependents | version here | exercised in | note |", "|--:|---|--:|---|---|---|"]
for i, r in enumerate(rows, 1):
    m = r["module_name"]
    v = versions.get(m, "")
    pk = ", ".join(f"`{p}/`" for p in packages_using(m)) if v else ""
    note = notes.get(m, "")
    if not v and not note:
        note = "not included"
    lines.append(f"| {i} | `{m}` | {r['direct_dependents']} | {v or '—'} | {pk} | {note} |")
table = "\n".join(lines)
readme = root / "README.md"
text = readme.read_text()
new = re.sub(r"(<!-- table:start -->\n).*?(\n<!-- table:end -->)", lambda mm: mm.group(1) + table + mm.group(2), text, flags=re.S)
readme.write_text(new)
print(f"wrote table with {len(rows)} rows")
