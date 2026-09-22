#!/usr/bin/env python3
"""Render STATUS.md and NOTES.md into site/ as HTML (progress site)."""
import pathlib, datetime, html
import markdown
root = pathlib.Path(__file__).resolve().parent.parent
site = root / "site"; site.mkdir(exist_ok=True)
CSS = """body{font-family:system-ui,sans-serif;max-width:60rem;margin:2rem auto;padding:0 1rem;line-height:1.5;color:#222}
pre{background:#f4f4f4;padding:.6rem;overflow-x:auto}code{background:#f4f4f4;padding:0 .2rem}
table{border-collapse:collapse}td,th{border:1px solid #ccc;padding:.2rem .5rem}h1,h2{border-bottom:1px solid #ddd}
nav a{margin-right:1rem}small{color:#666}"""
nav = '<nav><a href="index.html">Status</a><a href="notes.html">Notes</a><a href="log.txt">Build log</a></nav>'
for src, dst in (("STATUS.md", "index.html"), ("NOTES.md", "notes.html")):
    p = root / src
    body = markdown.markdown(p.read_text(), extensions=["tables", "fenced_code"]) if p.exists() else "<p>(missing)</p>"
    (site / dst).write_text(f"<!doctype html><meta charset=utf-8><title>bcr-smoke-test: {src}</title><style>{CSS}</style>{nav}{body}<hr><small>rendered {datetime.datetime.now():%Y-%m-%d %H:%M:%S}</small>")
