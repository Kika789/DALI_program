#!/usr/bin/env python3

from pathlib import Path
import re

SCRIPTDIR = Path(__file__).parent.resolve()
ROOTDIR = SCRIPTDIR.parent

# check if all literature is referenced in tex files


def get_all_citations(literature_files):
    citation = {}

    for file in literature_files:
        with open(file, "r") as f:
            lines = f.readlines()
            for line in lines:
                if line.startswith("@"):
                    # print(line.strip())
                    splt = line.split("{")
                    key = splt[1].split(",")[0]
                    citation[key] = 0
    print(citation)
    return citation


def check_references(base_dir, filename, citation):
    if filename in ["ctustyle3"]:
        return
    file_tex = base_dir / filename
    file_tex = file_tex.with_suffix(".tex")
    print(f"*** Checking {file_tex} ***")
    with open(file_tex , "r") as f:
        lines = f.readlines()
        for line in lines:
            line = line.strip()
            if line.startswith(r"\input"):
                splt = line.split()
                file = splt[1]
                print(file)
                check_references(base_dir, file, citation)



if __name__ == "__main__":
    # get all literature files
    # literature_files = list(ROOTDIR.glob("*.bib"))
    literature_files = [ROOTDIR / "reference.bib"]

    citation = get_all_citations(literature_files)
    check_references(ROOTDIR, "main", citation)