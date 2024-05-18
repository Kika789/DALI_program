#!/usr/bin/env python3

from pathlib import Path
import re

SCRIPTDIR = Path(__file__).parent.resolve()
ROOTDIR = SCRIPTDIR.parent

# check if all literature is referenced in tex files


# s = r"ahoj te \cite[xxx]:"
# s = r"\noindent Umělé osvětlení dělíme do kategorií podle způsobu instalace a funkce \cite[svetloaosvetlovani]:"


# findall = re.findall(r"\\cite\[(.+?)\]", s)
# print(findall)

# exit()



def get_all_citations(literature_files):
    citation = {}

    for file in literature_files:
        with open(file, "r") as f:
            lines = f.readlines()
            for line in lines:
                if line.startswith("@"):
                    # print(line.strip())
                    splt = line.split("{")
                    key = splt[1].split(",")[0].strip()
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
        while True:
            line = f.readline()
            if not line:
                break
            line = line.strip()
            if line.startswith("%"):
                continue
            if line.startswith(r"\input"):
                splt = line.split()
                file = splt[1]
                # print(file)
                check_references(base_dir, file, citation)
            else:
                recite = re.findall(r"\\cite\[(.+?)\]", line)
                if len(recite) > 0:
                    print(f"{recite}")
                # print(recite)
                for r in recite:
                    if r not in citation:
                        print(f"Reference {r} not found in literature files")
                    else:
                        citation[r] += 1


if __name__ == "__main__":
    # get all literature files
    # literature_files = list(ROOTDIR.glob("*.bib"))
    literature_files = [ROOTDIR / "reference.bib"]

    citation = get_all_citations(literature_files)
    check_references(ROOTDIR, "main", citation)
    print(citation)