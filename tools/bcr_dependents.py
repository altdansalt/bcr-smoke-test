#!/usr/bin/env python3
"""Rank BCR modules by how many other modules' latest versions directly depend on them.

Usage: bcr_dependents.py <path-to-bazel-central-registry-clone> [--exclude-prefix boost.]
Writes CSV to stdout: module_name,direct_dependents

"Direct dependents" = number of *other* modules whose latest (non-yanked) version's
MODULE.bazel contains a non-dev `bazel_dep(name = "<module>", ...)`.
"""
import argparse, json, pathlib, re, collections

ap = argparse.ArgumentParser()
ap.add_argument("registry")
ap.add_argument("--exclude-prefix", action="append", default=[])
args = ap.parse_args()
modules = pathlib.Path(args.registry) / "modules"
dep_re = re.compile(r'bazel_dep\((.*?)\)', re.S)
counts = collections.Counter()
for mdir in sorted(modules.iterdir()):
    meta = json.loads((mdir / "metadata.json").read_text())
    yanked = set(meta.get("yanked_versions", {}))
    versions = [v for v in meta["versions"] if v not in yanked]
    if not versions or any(mdir.name.startswith(p) for p in args.exclude_prefix):
        continue
    text = (mdir / versions[-1] / "MODULE.bazel").read_text()
    seen = set()
    for call in dep_re.findall(text):
        if "dev_dependency = True" in call:
            continue
        m = re.search(r'name\s*=\s*"([^"]+)"', call)
        if m and m.group(1) != mdir.name:
            seen.add(m.group(1))
    for d in seen:
        counts[d] += 1
print("module_name,direct_dependents")
for name, n in sorted(counts.items(), key=lambda kv: (-kv[1], kv[0])):
    print(f"{name},{n}")
