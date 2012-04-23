#! /usr/bin/env python
# -*- conding: utf-8 -*-

import argparse
import os
import sys
import re

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description = "Expand all environment variables in the file")
    parser.add_argument("file", metavar="<var>", help="input file")
    args = parser.parse_args()

    if not os.path.isfile(args.file):
        print("Error: " + args.file + " is not a regular file")
        sys.exit(1)

    content = open(args.file).read()

    vars = re.findall("\${([^}]+)}", content)
    vars = list(set(vars))

    for var in vars:
        value = os.getenv(var)
        if value:
            content = re.sub("\${" + var + "}", value, content)

    print(content)
